module Gl = {
  let red_size = 0;
  let green_size = 1;
  let blue_size = 2;
  let alpha_size = 3;
  let buffer_size = 4;
  let doublebuffer = 5;
  let depth_size = 6;
  let stencil_size = 7;
  let accum_red_size = 8;
  let accum_green_size = 9;
  let accum_blue_size = 10;
  let accum_alpha_size = 11;
  let stereo = 12;
  let multisamplebuffers = 13;
  let multisamplesamples = 14;
  let accelerated_visual = 15;
  let context_major_version = 17;
  let context_minor_version = 18;
  let context_egl = 19;
  let context_flags = 20;
  let context_profile_mask = 21;
  let share_with_current_context = 22;
  let framebuffer_srgb_capable = 23;
  let context_debug_flag = 1;
  let context_forward_compatible_flag = 2;
  let context_robust_access_flag = 4;
  let context_reset_isolation_flag = 8;
  let context_profile_core = 1;
  let context_profile_compatibility = 2;
  let context_profile_es = 4;
  external gl_set_attribute : (~attr: int, ~value: int) => int = "TSDL_GL_SetAttribute";
};

module Window = {
  external (+) : (int, int) => int = "T_or";
  let windowed = 0;
  let fullscreen = 1;
  let fullscreen_desktop = 4097;
  let opengl = 2;
  let shown = 4;
  let hidden = 8;
  let borderless = 16;
  let resizable = 32;
  let minimized = 64;
  let maximized = 128;
  let input_grabbed = 256;
  let input_focus = 512;
  let mouse_focus = 1024;
  let foreign = 2048;
  let allow_highdpi = 8192;
  let pos_centered = 805240832;
  let pos_undefined = 536805376;
};

/* flags should technically be a full uint32 */
type windowT;

type soundT;

external load_audio : (windowT, string) => soundT = "TSDL_LoadAudioFile";

external play_audio : (windowT, soundT, ~volume: float, ~loop: bool) => unit = "TSDL_PlayAudio";

external create_window :
  (~title: string, ~x: int, ~y: int, ~w: int, ~h: int, ~flags: int) => windowT =
  "TSDL_CreateWindow_bytecode" "TSDL_CreateWindow_native";

external destroy_window : windowT => unit = "TSDL_DestroyWindow";

type glContextT;

external get_drawable_size : windowT => (int, int) = "TSDL_GL_GetDrawableSize";

external get_window_max_size : windowT => (int, int) = "TSDL_GetWindowMaximumSize";

external get_window_size : windowT => (int, int) = "TSDL_GetWindowSize";

external set_window_size : (windowT, ~width: int, ~height: int) => unit = "TSDL_SetWindowSize";

external set_window_title : (windowT, ~width: string) => unit = "TSDL_SetWindowTitle";

type dpiT = {
  ddpi: float,
  hdpi: float,
  vdpi: float
};

external get_window_dpi : windowT => dpiT = "TSDL_GetDisplayDPI";

type surfaceT;
type cursorT;

external show_cursor : int => int = "TSDL_ShowCursor";
external set_cursor : cursorT => unit = "TSDL_SetCursor";
external create_color_cursor : (surfaceT, int, int) => cursorT = "TSDL_CreateColorCursor";

module Init = {
  let timer = 1;
  let audio = 16;
  let video = 32;
  let joystick = 512;
  let haptic = 4096;
  let gamecontroller = 8192;
  let events = 16384;
  let everything = 29233;
  let noparachute = 1048576;
  external init : int => int = "TSDL_Init";
};

external gl_create_context : windowT => glContextT = "TSDL_GL_CreateContext";

external gl_make_current : (windowT, glContextT) => int = "TSDL_GL_MakeCurrent";

module Event = {
  let windowevent = 512;
  let syswmevent = 513;
  let keydown = 768;
  let keyup = 769;
  let textediting = 770;
  let textinput = 771;
  let mousemotion = 1024;
  let mousebuttondown = 1025;
  let mousebuttonup = 1026;
  let mousewheel = 1027;
  let quit = 256;
  type eventT = {
    typ: int,
    mouse_button_button: int,
    mouse_button_x: int,
    mouse_button_y: int,
    mouse_motion_x: int,
    mouse_motion_y: int,
    keyboard_repeat: int,
    keyboard_keycode: Int32.t,
    window_event_enum: int
  };
  external poll_event : unit => option(eventT) = "TSDL_PollEvent";
  let window_shown = 1;
  let window_hidden = 2;
  let window_exposed = 3;
  let window_moved = 4;
  let window_resized = 5;
  let window_size_changed = 6;
  let window_minimized = 7;
  let window_maximized = 8;
  let window_restored = 9;
  let window_enter = 10;
  let window_leave = 11;
  let window_focus_gained = 12;
  let window_focus_lost = 13;
  let window_close = 14;
};

type int64T;

[@noalloc] external get_performance_counter : unit => int64T = "TSDL_GetPerformanceCounter";

external get_time_diff : (int64T, int64T) => float = "TGetTimeDiff";

[@noalloc] external gl_swap_window : windowT => unit = "TSDL_GL_SwapWindow";

external get_window_surface : windowT => surfaceT = "TSDL_GetWindowSurface";

external load_bmp : string => surfaceT = "TSDL_LoadBMP";

external blit_surface : (surfaceT, surfaceT) => int = "TSDL_BlitSurface";

external update_window : windowT => int = "TSDL_UpdateWindowSurface";

external error : unit => string = "TSDL_GetError";

external delay : int => unit = "TSDL_Delay";

external quit : unit => unit = "TSDL_Quit";

let sdl_query = -1;
let sdl_disable = 0;
let sdl_ignore = 0;
let sdl_enable = 1;

let a = 10;

let (>>=) = (t, f) =>
  switch t {
  | 0 => f()
  | _ => failwith @@ error()
  };
/*
 /** Main */
 let create_window gl::(maj, min) => {
   let w_atts = Window.(opengl + resizable);
   let w_title = Printf.sprintf "OpenGL %d.%d (core profile)" maj min;
   let set a v => gl_set_attribute a v;
   set Gl.context_profile_mask Gl.context_profile_compatibility >>= (
     fun () =>
       set Gl.context_major_version maj >>= (
         fun () =>
           set Gl.context_minor_version min >>= (
             fun () =>
               set Gl.doublebuffer 1 >>= (
                 fun () =>
                   create_window
                     title::w_title
                     x::Window.pos_centered
                     y::Window.pos_centered
                     w::640
                     h::480
                     flags::w_atts
               )
           )
       )
   )
 };

 Init.init Init.everything;

 let w = create_window gl::(4, 5);

 let windowSurface = get_window_surface w;

 let img = load_bmp "test.bmp";

 blit_surface img windowSurface >>= (
   fun () =>
     update_window w >>= (
       fun () => {
         let shouldRun = ref true;
         while !shouldRun {
           switch (Event.poll_event ()) {
           | None => ()
           | Some e =>
             if (Event.typ e == Event.keydown) {
               if (Event.keyboard_keycode e == 27) {
                 print_endline "pressed escape!";
                 shouldRun := false
               }
             }
           }
         };
         destroy_window w
       }
     )
 );

 quit ();
 */
