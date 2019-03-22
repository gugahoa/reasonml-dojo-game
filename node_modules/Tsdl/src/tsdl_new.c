#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <caml/fail.h>

#include "SDL2/SDL.h"

CAMLprim value TSDL_GL_SetAttribute(value a, value v) {
  CAMLparam2(a, v);
  CAMLreturn(Val_int(SDL_GL_SetAttribute(Int_val(a), Int_val(v))));
}

// SDL_AudioFormat of files
#define AUDIO_FORMAT AUDIO_S16LSB

// Frequency of the file
#define AUDIO_FREQUENCY 44100

// 1 mono, 2 stereo, 4 quad, 6 (5.1)
#define AUDIO_CHANNELS 2

// Specifies a unit of audio data to be used at a time. Must be a power of 2
#define AUDIO_SAMPLES 4096

// Max number of sounds that can be in the audio queue at anytime
#define AUDIO_MAX_SOUNDS 25
#define SDL_AUDIO_ALLOW_CHANGES SDL_AUDIO_ALLOW_ANY_CHANGE


typedef struct sound
{
    uint32_t length;
    uint32_t lengthTrue;
    uint8_t * bufferTrue;
    uint8_t * buffer;
    uint8_t loop;
    uint8_t fade;
    uint8_t free;
    uint8_t volume;

    SDL_AudioSpec audio;

    struct sound * next;
} Audio;

typedef struct privateAudioDevice
{
    SDL_AudioDeviceID device;
    SDL_AudioSpec want;
    uint8_t audioEnabled;
} PrivateAudioDevice;

static inline void audioCallback(void * userdata, uint8_t * stream, int len){
  Audio * audio = (Audio *) userdata;
  Audio * previous = audio;
  int tempLength;
  uint8_t music = 0;

  /* Silence the main buffer */
  SDL_memset(stream, 0, len);

  /* First one is place holder */
  audio = audio->next;

  while(audio != NULL){
    if(audio->length > 0){
      if(audio->fade == 1 && audio->loop == 1){
        music = 1;

        if(audio->volume > 0) {
            audio->volume--;
        } else {
            audio->length = 0;
        }
      }

      if (music && audio->loop == 1 && audio->fade == 0) {
        tempLength = 0;
      } else {
        tempLength = ((uint32_t) len > audio->length) ? audio->length : (uint32_t) len;
      }

      SDL_MixAudioFormat(stream, audio->buffer, AUDIO_FORMAT, tempLength, audio->volume);

      audio->buffer += tempLength;
      audio->length -= tempLength;

      previous = audio;
      audio = audio->next;
    } else if(audio->loop == 1 && audio->fade == 0) {
      audio->buffer = audio->bufferTrue;
      audio->length = audio->lengthTrue;
    } else {
      previous->next = audio->next;

      audio->next = NULL;
      Audio * temp;
      while(audio != NULL)
      {
          if(audio->free == 1)
          {
              SDL_FreeWAV(audio->bufferTrue);
          }

          temp = audio;
          audio = audio->next;

          free(temp);
      }

      audio = previous->next;
    }
  }
}


PrivateAudioDevice* initAudio(){
  PrivateAudioDevice * gDevice = calloc(1, sizeof(PrivateAudioDevice));

  if(!(SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO)) {
      fprintf(stderr, "[%s: %d]Error: SDL_INIT_AUDIO not initialized\n", __FILE__, __LINE__);
      caml_failwith("SDL_INIT_AUDIO not initialized");
  }

  (gDevice->want).freq = AUDIO_FREQUENCY;
  (gDevice->want).format = AUDIO_FORMAT;
  (gDevice->want).channels = AUDIO_CHANNELS;
  (gDevice->want).samples = AUDIO_SAMPLES;
  (gDevice->want).callback = audioCallback;
  (gDevice->want).userdata = calloc(1, sizeof(Audio));

  if((gDevice->device = SDL_OpenAudioDevice(NULL, 0, &(gDevice->want), NULL, SDL_AUDIO_ALLOW_CHANGES)) == 0) {
      fprintf(stderr, "[%s: %d]Warning: failed to open audio device: %s\n", __FILE__, __LINE__, SDL_GetError());
  } else {
      /* Set audio device enabled global flag and unpause */
      gDevice->audioEnabled = 1;
      SDL_PauseAudioDevice(gDevice->device, 0);
  }

  return gDevice;
}

CAMLprim value TSDL_LoadAudioFile(value window, value pathVal){
  CAMLparam2(window, pathVal);
  PrivateAudioDevice * gDevice = (PrivateAudioDevice*)Field(window, 1);
  char* path = String_val(pathVal);

  Audio * new = calloc(1, sizeof(Audio));
  new->next = NULL;
  new->fade = 0;
  new->free = 0;
  new->volume = SDL_MIX_MAXVOLUME;

  if(SDL_LoadWAV(path, &(new->audio), &(new->bufferTrue), &(new->lengthTrue)) == NULL) {
    fprintf(stderr, "[%s: %d]Warning: failed to open wave file: %s error: %s\n", __FILE__, __LINE__, path, SDL_GetError());
    free(new);
    caml_failwith("Failed to open wav file");
  }

  CAMLlocal1(ret);
  ret = caml_alloc_small(1, Abstract_tag);
  Field(ret, 0) = (long)new;
  CAMLreturn(ret);
}

void TSDL_PlayAudio(value window, value soundVal, value volumeVal, value loopVal) {
  CAMLparam4(window, soundVal, volumeVal, loopVal);
  Audio * sound;
  sound = malloc(sizeof(Audio));
  memcpy(sound, (Audio*)Field(soundVal, 0), sizeof(Audio));
  PrivateAudioDevice * gDevice = (PrivateAudioDevice*)Field(window, 1);

  sound->buffer = sound->bufferTrue;
  sound->length = sound->lengthTrue;
  sound->volume = SDL_MIX_MAXVOLUME * Double_val(volumeVal);
  sound->loop = Bool_val(loopVal);
  (sound->audio).callback = NULL;
  (sound->audio).userdata = NULL;

  SDL_LockAudioDevice(gDevice->device);

  Audio * root = (Audio *) (gDevice->want).userdata;
  while(root->next != NULL) {
    root = root->next;
  }

  root->next = sound;

  SDL_UnlockAudioDevice(gDevice->device);
  CAMLreturn0;
}

CAMLprim value TSDL_CreateWindow_native(value title, value x, value y, value w, value h, value flags) {
  CAMLparam5(title, x, y, w, h);
  CAMLxparam1(flags);
  CAMLlocal1(ret);
  SDL_Window *window = SDL_CreateWindow(String_val(title), Int_val(x), Int_val(y), Int_val(w), Int_val(h), Int_val(flags));
  if (window == NULL) {
    const char *sdl_error =  SDL_GetError();
    char err[512 + strlen(sdl_error)];
    sprintf(err, "[%s: %d]Error: Failed to create SDL window: %s\n", __FILE__, __LINE__, sdl_error);
    caml_failwith(err);
  }
  PrivateAudioDevice * device = initAudio();
  ret = caml_alloc_small(2, Abstract_tag);
  Field(ret, 0) = (long)window;
  Field(ret, 1) = (long)device;
  CAMLreturn(ret);
}

CAMLprim value TSDL_CreateWindow_bytecode( value * argv, int argn ) {
  return TSDL_CreateWindow_native(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

void TSDL_DestroyWindow(value window) {
  CAMLparam1(window);
  SDL_DestroyWindow((SDL_Window *)Field(window, 0));
  CAMLreturn0;
}

CAMLprim value TSDL_GetWindowSize(value window) {
  CAMLparam1(window);
  CAMLlocal1(ret);
  int w;
  int h;
  SDL_GetWindowSize((SDL_Window *)Field(window, 0), &w, &h);
  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = Val_int(w);
  Field(ret, 1) = Val_int(h);
  CAMLreturn(ret);
}

void TSDL_SetWindowSize(value window, value w, value h) {
  CAMLparam3(window, w, h);
  SDL_SetWindowSize((SDL_Window *)Field(window, 0), Int_val(w), Int_val(h));
  CAMLreturn0;
}

void TSDL_SetWindowTitle(value window, value title) {
  CAMLparam2(window, title);
  SDL_SetWindowTitle((SDL_Window *)Field(window, 0), String_val(title));
  CAMLreturn0;
}

CAMLprim value TSDL_Init(value flags) {
  CAMLparam1(flags);
  CAMLreturn(Val_int(SDL_Init(Int_val(flags))));
}

CAMLprim value TSDL_GL_CreateContext(value window) {
  CAMLparam1(window);
  CAMLlocal1(ret);
  ret = caml_alloc_small(1, Abstract_tag);
  void *context = SDL_GL_CreateContext((SDL_Window *)Field(window, 0));
  if (context == NULL) {
    const char *sdl_error =  SDL_GetError();
    char err[512 + strlen(sdl_error)];
    sprintf(err, "[%s: %d]Error: Failed to create SDL context: %s\n", __FILE__, __LINE__, sdl_error);
    caml_failwith(err);
  }
  Field(ret, 0) = (long)context;
  CAMLreturn(ret);
}

CAMLprim value TSDL_GL_MakeCurrent(value window, value context) {
  CAMLparam2(window, context);
  CAMLreturn(Val_int(SDL_GL_MakeCurrent((SDL_Window *)Field(window, 0), (SDL_GLContext)Field(context, 0))));
}

CAMLprim value TSDL_PollEvent() {
  CAMLparam0();
  CAMLlocal2(ret, wrapped);
  SDL_Event e;
  int eventAvailable = SDL_PollEvent(&e);
  if (eventAvailable == 0) {
    CAMLreturn(Val_int(0));
  }
  // typ: int,
  //   mouse_button_button: int,
  //   mouse_button_x: int,
  //   mouse_button_y: int,
  //   mouse_motion_x: int,
  //   mouse_motion_y: int,
  //   keyboard_repeat: int,
  //   keyboard_keycode: int32
  //   window_event_enum: int
  ret = caml_alloc_small(9, Abstract_tag);
  Field(ret, 0) = Val_int(e.type);
  Field(ret, 1) = Val_int(e.button.button);
  Field(ret, 2) = Val_int(e.button.x);
  Field(ret, 3) = Val_int(e.button.y);
  Field(ret, 4) = Val_int(e.motion.x);
  Field(ret, 5) = Val_int(e.motion.y);
  Field(ret, 6) = Val_int(e.key.repeat);
  Field(ret, 7) = caml_copy_int32(e.key.keysym.sym);
  Field(ret, 8) = Val_int(e.window.event);

  wrapped = caml_alloc_small(1, 0);
  Field(wrapped, 0) = ret;
  CAMLreturn(wrapped);
}

value TSDL_GetPerformanceCounter() {
  return SDL_GetPerformanceCounter();
}

CAMLprim value TGetTimeDiff(value prevTime, value curTime) {
  CAMLparam2(prevTime, curTime);
  CAMLreturn(caml_copy_double((double) (((uint64_t)curTime - (uint64_t)prevTime) * 1000) / SDL_GetPerformanceFrequency()));
}

void TSDL_GL_SwapWindow(value window) {
  SDL_GL_SwapWindow((SDL_Window *)Field(window, 0));
}

void TSDL_Delay(value delay) {
  CAMLparam1(delay);
  SDL_Delay(Int_val(delay));
  CAMLreturn0;
}

void TSDL_Quit() {
  CAMLparam0();
  SDL_Quit();
  CAMLreturn0;
}

CAMLprim value TSDL_GetWindowSurface(value window) {
  CAMLparam1(window);
  CAMLlocal1(ret);
  ret = caml_alloc_small(1, Abstract_tag);
  SDL_Surface *s = SDL_GetWindowSurface((SDL_Window *)Field(window, 0));
  if (s == NULL) {
    const char *sdl_error =  SDL_GetError();
    char err[512 + strlen(sdl_error)];
    sprintf(err, "[%s: %d]Error: Failed to get the SDL surface: %s\n", __FILE__, __LINE__, sdl_error);
    caml_failwith(err);
  }
  Field(ret, 0) = (long)s;
  CAMLreturn(ret);
}

CAMLprim value TSDL_LoadBMP(value bmp_name) {
  CAMLparam1(bmp_name);
  CAMLlocal1(ret);
  ret = caml_alloc_small(1, Abstract_tag);
  Field(ret, 0) = (long)SDL_LoadBMP(String_val(bmp_name));
  CAMLreturn(ret);
}

CAMLprim value TSDL_BlitSurface(value surf1, value surf2) {
  CAMLparam2(surf1, surf2);
  int error = SDL_BlitSurface((SDL_Surface *)Field(surf1, 0), NULL, (SDL_Surface *)Field(surf2, 0), NULL);
  CAMLreturn(Val_int(error));
}

CAMLprim value TSDL_UpdateWindowSurface(value window) {
  CAMLparam1(window);
  int error = SDL_UpdateWindowSurface((SDL_Window *)Field(window, 0));
  CAMLreturn(Val_int(error));
}

CAMLprim value TSDL_GetError() {
  CAMLparam0();
  CAMLlocal1(ret);
  ret = caml_copy_string(SDL_GetError());
  CAMLreturn(ret);
}

CAMLprim value T_or(value a, value b) {
  CAMLparam2(a, b);
  CAMLreturn(Val_int(Int_val(a) | Int_val(b)));
}

CAMLprim value TSDL_GL_GetDrawableSize(value window) {
  CAMLparam1(window);
  CAMLlocal1(ret);
  int w, h;
  SDL_GL_GetDrawableSize((SDL_Window *)Field(window, 0), &w, &h);

  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = Val_int(w);
  Field(ret, 1) = Val_int(h);

  CAMLreturn(ret);
}

CAMLprim value TSDL_GetDisplayDPI(value window) {
  CAMLparam1(window);
  CAMLlocal1(ret);

  float ddpi, hdpi, vdpi;
  int index = SDL_GetWindowDisplayIndex((SDL_Window *)Field(window, 0));
  SDL_GetDisplayDPI(index, &ddpi, &hdpi, &vdpi);

  ret = caml_alloc_small(3, Double_array_tag);
  Double_field(ret, 0) = ddpi;
  Double_field(ret, 1) = hdpi;
  Double_field(ret, 2) = vdpi;

  CAMLreturn(ret);
}

CAMLprim value TSDL_GetWindowMaximumSize(value window) {
  CAMLparam1(window);
  CAMLlocal1(ret);
  int w, h;
  SDL_GetWindowMaximumSize((SDL_Window *)Field(window, 0), &w, &h);

  ret = caml_alloc_small(2, 0);
  Field(ret, 0) = Val_int(w);
  Field(ret, 1) = Val_int(h);

  CAMLreturn(ret);
}

CAMLprim value TSDL_ShowCursor(value toggle) {
  CAMLparam1(toggle);
  int visible = SDL_ShowCursor(Int_val(toggle));
  CAMLreturn(Val_int(visible));
}

CAMLprim value TSDL_CreateColorCursor(value surface, value hot_x, value hot_y) {
  CAMLparam3(surface, hot_x, hot_y);
  CAMLlocal1(ret);
  ret = caml_alloc_small(1, Abstract_tag);
  Field(ret, 0) = (long)SDL_CreateColorCursor((SDL_Surface *)Field(surface, 0), Int_val(hot_x), Int_val(hot_y));
  CAMLreturn(ret);
}

void TSDL_SetCursor(value cursor) {
  CAMLparam1(cursor);
  SDL_SetCursor((SDL_Cursor *)Field(cursor, 0));
  CAMLreturn0;
}
