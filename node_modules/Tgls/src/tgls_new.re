[@noalloc] external gladLoadGL : unit => unit = "gladLoadGL";

type programT;

[@noalloc] external createProgram : unit => programT = "TglCreateProgram";

type shaderT;

let gl_vertex_shader = 35633;

let gl_fragment_shader = 35632;

[@noalloc] external createShader : int => shaderT = "TglCreateShader";

[@noalloc] external attachShader : (~program: programT, ~shader: shaderT) => unit =
  "TglAttachShader";

[@noalloc] external deleteShader : shaderT => unit = "TglDeleteShader";

external shaderSource : (shaderT, array(string)) => unit = "TglShaderSource";

[@noalloc] external compileShader : shaderT => unit = "TglCompileShader";

[@noalloc] external linkProgram : programT => unit = "TglLinkProgram";

[@noalloc] external useProgram : programT => unit = "TglUseProgram";

type bufferT;

let gl_array_buffer = 34962;

let gl_element_array_buffer = 34963;

let gl_pixel_pack_buffer = 35051;

let gl_pixel_unpack_buffer = 35052;

[@noalloc] external bindBuffer : (~target: int, ~buffer: bufferT) => unit = "TglBindBuffer";

/* might not work because passing stack pointer instead of heap pointer (see warning) */
external genBuffers : int => array(bufferT) = "TglGenBuffers";

[@noalloc] external genBuffer : unit => bufferT = "TglGenBuffer";

[@noalloc]
external clearColor : (~red: float, ~green: float, ~blue: float, ~alpha: float) => unit =
  "TglClearColor";

type textureT;

/* might not work because passing stack pointer instead of heap pointer (see warning) */
external genTextures : int => array(textureT) = "TglGenTextures";

[@noalloc] external genTexture : unit => textureT = "TglGenTexture";

type framebufferT;

external genFramebuffers : int => array(framebufferT) = "TglGenFramebuffers";

[@noalloc] external genFramebuffer : unit => framebufferT = "TglGenFramebuffer";

let gl_framebuffer = 36160;

let gl_color_attachment0 = 36064;

[@noalloc] external bindFramebuffer : int => framebufferT => unit = "TglBindFramebuffer";

[@noalloc] external bindDefaultFramebuffer : int => unit = "TglBindDefaultFramebuffer";

[@noalloc] external framebufferTexture2D : (~target:int, ~attachment:int, ~texTarget:int, ~texture:textureT, ~level:int) => unit = "TglFramebufferTexture2D";


let gl_texture0 = 33984;

let gl_texture1 = 33985;

let gl_texture2 = 33986;

let gl_texture3 = 33987;

let gl_texture4 = 33988;

let gl_texture5 = 33989;

let gl_texture6 = 33990;

let gl_texture7 = 33991;

let gl_texture8 = 33992;

let gl_texture9 = 33993;

let gl_texture10 = 33994;

let gl_texture11 = 33995;

let gl_texture12 = 33996;

let gl_texture13 = 33997;

let gl_texture14 = 33998;

let gl_texture15 = 33999;

let gl_texture16 = 34000;

let gl_texture17 = 34001;

let gl_texture18 = 34002;

let gl_texture19 = 34003;

let gl_texture20 = 34004;

let gl_texture21 = 34005;

let gl_texture22 = 34006;

let gl_texture23 = 34007;

let gl_texture24 = 34008;

let gl_texture25 = 34009;

let gl_texture26 = 34010;

let gl_texture27 = 34011;

let gl_texture28 = 34012;

let gl_texture29 = 34013;

let gl_texture30 = 34014;

let gl_texture31 = 34015;

[@noalloc] external activeTexture : int => unit = "TglActiveTexture";

let gl_texture_1d = 3552;

let gl_texture_2d = 3553;

let gl_texture_3d = 32879;

let gl_texture_cube_map = 34067;

[@noalloc] external bindTexture : (~target: int, ~texture: textureT) => unit = "TglBindTexture";

external texSubImage2D :
  (
    ~target: int,
    ~level: int,
    ~xoffset: int,
    ~yoffset: int,
    ~width: int,
    ~height: int,
    ~format: int,
    ~type_: int,
    ~pixels: Bigarray.Array1.t('a, 'b, Bigarray.c_layout)
  ) =>
  unit =
  "TglTexSubImage2D_bytecode" "TglTexSubImage2D_native";

let gl_texture_mag_filter = 10240;

let gl_texture_min_filter = 10241;

let gl_texture_wrap_s = 10242;

let gl_texture_wrap_t = 10243;

let gl_texture_min_lod = 33082;

let gl_texture_max_lod = 33083;

let gl_texture_base_level = 33084;

let gl_texture_max_level = 33085;

let gl_texture_wrap_r = 32882;

let gl_texture_priority = 32870;

let gl_texture_compare_mode = 34892;

let gl_texture_compare_func = 34893;

/* last 2 are part of glext, not sure if this is actually available in webgl. */
let gl_depth_texture_mode = 34891;

let gl_generate_mipmap = 33169;

[@noalloc] external texParameteri : (~target: int, ~pname: int, ~param: int) => unit =
  "TglTexParameteri";

let gl_alpha_test = 3008;

let gl_auto_normal = 3456;

let gl_blend = 3042;

let gl_clip_plane0 = 12288;

let gl_clip_plane1 = 12289;

let gl_clip_plane2 = 12290;

let gl_clip_plane3 = 12291;

let gl_clip_plane4 = 12292;

let gl_clip_plane5 = 12293;

let gl_color_logic_op = 3058;

let gl_color_material = 2903;

let gl_color_sum = 33880;

let gl_color_table = 32976;

let gl_convolution_1d = 32784;

let gl_convolution_2d = 32785;

let gl_cull_face = 2884;

let gl_depth_test = 2929;

let gl_dither = 3024;

let gl_fog = 2912;

let gl_histogram = 32804;

let gl_index_logic_op = 3057;

let gl_light0 = 16384;

let gl_light1 = 16385;

let gl_light2 = 16386;

let gl_light3 = 16387;

let gl_light4 = 16388;

let gl_light5 = 16389;

let gl_light6 = 16390;

let gl_light7 = 16391;

let gl_lighting = 2896;

let gl_line_smooth = 2848;

let gl_line_stipple = 2852;

let gl_map1_color_4 = 3472;

let gl_map1_index = 3473;

let gl_map1_normal = 3474;

let gl_map1_texture_coord_1 = 3475;

let gl_map1_texture_coord_2 = 3476;

let gl_map1_texture_coord_3 = 3477;

let gl_map1_texture_coord_4 = 3478;

let gl_map1_vertex_3 = 3479;

let gl_map1_vertex_4 = 3480;

let gl_map2_color_4 = 3504;

let gl_map2_index = 3505;

let gl_map2_normal = 3506;

let gl_map2_texture_coord_1 = 3507;

let gl_map2_texture_coord_2 = 3508;

let gl_map2_texture_coord_3 = 3509;

let gl_map2_texture_coord_4 = 3510;

let gl_map2_vertex_3 = 3511;

let gl_map2_vertex_4 = 3512;

let gl_minmax = 32814;

let gl_multisample = 32925;

let gl_normalize = 2977;

let gl_point_smooth = 2832;

/* only in glext */
let gl_point_sprite = 34913;

let gl_polygon_offset_fill = 32823;

let gl_polygon_offset_line = 10754;

let gl_polygon_offset_point = 10753;

let gl_polygon_smooth = 2881;

let gl_polygon_stipple = 2882;

let gl_post_color_matrix_color_table = 32978;

let gl_post_convolution_color_table = 32977;

let gl_rescale_normal = 32826;

let gl_sample_alpha_to_coverage = 32926;

let gl_sample_alpha_to_one = 32927;

let gl_sample_coverage = 32928;

let gl_separable_2d = 32786;

let gl_scissor_test = 3089;

let gl_stencil_test = 2960;

let gl_texture_gen_s = 3168;

let gl_texture_gen_t = 3169;

let gl_texture_gen_r = 3170;

let gl_texture_gen_q = 3171;

/* only in glext */
let gl_vertex_program_point_size = 34370;

/* only in glext */
let gl_vertex_program_two_side = 34371;

[@noalloc] external enable : int => unit = "TglEnable";

[@noalloc] external disable : int => unit = "TglDisable";

let gl_zero = 0;

let gl_one = 1;

let gl_src_color = 768;

let gl_one_minus_src_color = 769;

let gl_src_alpha = 770;

let gl_one_minus_src_alpha = 771;

let gl_dst_alpha = 772;

let gl_one_minus_dst_alpha = 773;

let gl_dst_color = 774;

let gl_one_minus_dst_color = 775;

let gl_src_alpha_saturate = 776;

let gl_constant_color = 32769;

let gl_one_minus_constant_color = 32770;

let gl_constant_alpha = 32771;

let gl_one_minus_constant_alpha = 32772;

[@noalloc] external blendFunc : (~sfactor: int, ~dfactor: int) => unit = "TglBlendFunc";

external readPixels_RGBA :
  (~x: int, ~y: int, ~width: int, ~height: int) =>
  Bigarray.Array1.t(int, Bigarray.int8_unsigned_elt, Bigarray.c_layout) =
  "TglReadPixels_RGBA";

let gl_proxy_texture_2d = 32868;

let gl_texture_cube_map_positive_x = 34069;

let gl_texture_cube_map_negative_x = 34070;

let gl_texture_cube_map_positive_y = 34071;

let gl_texture_cube_map_negative_y = 34072;

let gl_texture_cube_map_positive_z = 34073;

let gl_texture_cube_map_negative_z = 34074;

let gl_proxy_texture_cube_map = 34075;

let gl_alpha = 6406;

let gl_alpha4 = 32827;

let gl_alpha8 = 32828;

let gl_alpha12 = 32829;

let gl_alpha16 = 32830;

let gl_compressed_alpha = 34025;

let gl_compressed_luminance = 34026;

let gl_compressed_luminance_alpha = 34027;

let gl_compressed_intensity = 34028;

let gl_compressed_rgb = 34029;

let gl_compressed_rgba = 34030;

let gl_depth_component = 6402;

let gl_depth_component16 = 33189;

let gl_depth_component24 = 33190;

let gl_depth_component32 = 33191;

let gl_luminance = 6409;

let gl_luminance4 = 32831;

let gl_luminance8 = 32832;

let gl_luminance12 = 32833;

let gl_luminance16 = 32834;

let gl_luminance4_alpha4 = 32835;

let gl_luminance6_alpha2 = 32836;

let gl_luminance8_alpha8 = 32837;

let gl_luminance12_alpha4 = 32838;

let gl_luminance12_alpha12 = 32839;

let gl_luminance16_alpha16 = 32840;

let gl_intensity = 32841;

let gl_intensity4 = 32842;

let gl_intensity8 = 32843;

let gl_intensity12 = 32844;

let gl_intensity16 = 32845;

let gl_r3_g3_b2 = 10768;

let gl_rgb4 = 32847;

let gl_rgb5 = 32848;

let gl_rgb8 = 32849;

let gl_rgb10 = 32850;

let gl_rgb12 = 32851;

let gl_rgb16 = 32852;

let gl_rgba2 = 32853;

let gl_rgba4 = 32854;

let gl_rgb5_a1 = 32855;

let gl_rgba8 = 32856;

let gl_rgb10_a2 = 32857;

let gl_rgba12 = 32858;

let gl_rgba16 = 32859;

let gl_sluminance_alpha = 35908;

let gl_sluminance8_alpha8 = 35909;

let gl_sluminance = 35910;

let gl_sluminance8 = 35911;

let gl_srgb = 35904;

let gl_srgb8 = 35905;

let gl_srgb_alpha = 35906;

let gl_srgb8_alpha8 = 35907;

[@noalloc]
external texImage2D_null :
  (
    ~target: int,
    ~level: int,
    ~width: int,
    ~height: int,
    ~border: int
  ) =>
  unit =
  "TglTexImage2D_null";

[@noalloc]
external texImage2D_RGBA :
  (
    ~target: int,
    ~level: int,
    ~width: int,
    ~height: int,
    ~border: int,
    ~data: Bigarray.Array1.t('a, 'b, Bigarray.c_layout)
  ) =>
  unit =
  "TglTexImage2D_RGBA_bytecode" "TglTexImage2D_RGBA_native";

type uniformT;

[@noalloc] external uniform1i : (~location: uniformT, ~value: int) => unit = "TglUniform1i";

[@noalloc] external uniform1f : (~location: uniformT, ~value: float) => unit = "TglUniform1f";

[@noalloc] external uniform2f : (~location: uniformT, ~v1: float, ~v2: float) => unit =
  "TglUniform2f";

[@noalloc] external uniform3f : (~location: uniformT, ~v1: float, ~v2: float, ~v3: float) => unit =
  "TglUniform3f";

[@noalloc]
external uniform4f : (~location: uniformT, ~v1: float, ~v2: float, ~v3: float, ~v4: float) => unit =
  "TglUniform4f";

let gl_stream_draw = 35040;

let gl_stream_read = 35041;

let gl_stream_copy = 35042;

let gl_static_draw = 35044;

let gl_static_read = 35045;

let gl_static_copy = 35046;

let gl_dynamic_draw = 35048;

let gl_dynamic_read = 35049;

let gl_dynamic_copy = 35050;

[@noalloc]
external bufferData :
  (~target: int, ~data: Bigarray.Array1.t('a, 'b, Bigarray.c_layout), ~usage: int) => unit =
  "TglBufferData";

[@noalloc] external viewport : (~x: int, ~y: int, ~width: int, ~height: int) => unit =
  "TglViewport";

let gl_color_buffer_bit = 16384;

let gl_depth_buffer_bit = 256;

let gl_accum_buffer_bit = 512;

let gl_stencil_buffer_bit = 1024;

[@noalloc] external clear : int => unit = "TglClear";

external getUniformLocation : (~program: programT, ~name: string) => uniformT =
  "TglGetUniformLocation";

type attribT;

external getAttribLocation : (~program: programT, ~name: string) => attribT =
  "TglGetAttribLocation";

external enableVertexAttribArray : attribT => unit = "TglEnableVertexAttribArray";

let gl_byte = 5120;

let gl_unsigned_byte = 5121;

let gl_short = 5122;

let gl_unsigned_short = 5123;

let gl_int = 5124;

let gl_unsigned_int = 5125;

let gl_float = 5126;

let gl_double = 5130;

external vertexAttribPointer :
  (~index: attribT, ~size: int, ~typ: int, ~normalize: bool, ~stride: int, ~offset: int) => unit =
  "TglVertexAttribPointer_bytecode" "TglVertexAttribPointer_native";

external vertexAttribDivisor : (~attribute: attribT, ~divisor: int) => unit =
  "TglVertexAttribDivisor_byte";

let gl_shader_type = 35663;

let gl_delete_status = 35712;

let gl_compile_status = 35713;

let gl_link_status = 35714;

let gl_validate_status = 35715;

let gl_info_log_length = 35716;

let gl_attached_shaders = 35717;

let gl_active_uniforms = 35718;

let gl_active_uniform_max_length = 35719;

let gl_shader_source_length = 35720;

let gl_active_attributes = 35721;

let gl_active_attribute_max_length = 35722;

[@noalloc] external getProgramiv : (~program: programT, ~pname: int) => int = "TglGetProgramiv";

[@noalloc] external getShaderiv : (~shader: shaderT, ~pname: int) => int = "TglGetShaderiv";

external getShaderInfoLog : shaderT => string = "TglGetShaderInfoLog";

external getProgramInfoLog : programT => string = "TglGetProgramInfoLog";

external getShaderSource : shaderT => string = "TglGetShaderSource";

let gl_points = 0;

let gl_lines = 1;

let gl_line_loop = 2;

let gl_line_strip = 3;

let gl_triangles = 4;

let gl_triangle_strip = 5;

let gl_triangle_fan = 6;

let gl_quads = 7;

let gl_quad_strip = 8;

let gl_polygon = 9;

[@noalloc] external drawArrays : (~mode: int, ~first: int, ~count: int) => unit = "TglDrawArrays";

[@noalloc] external drawElements : (~mode: int, ~count: int, ~typ: int, ~offset: int) => unit =
  "TglDrawElements";

[@noalloc]
external drawElementsInstanced :
  (~mode: int, ~count: int, ~type_: int, ~indices: int, ~primcount: int) => unit =
  "TglDrawElementsInstanced";

[@noalloc]
external uniformMatrix4fv : (~location: uniformT, ~transpose: bool, ~value: array(float)) => unit =
  "TglUniformMatrix4fv";

type imageT = {
  width: int,
  height: int,
  channels: int,
  data: Bigarray.Array1.t(int, Bigarray.int8_unsigned_elt, Bigarray.c_layout)
};

/***
 * Internal dep on SOIL. This helps us load a bunch of different formats of image and get a `unsigned char*`
 * which we transform into an `array int` and then a bigarray before passing it to tgls.
 *
 * This is very unefficient as we end we 3 copies of the data (1 original and 2 copies). We should be able
 * to pass in the C `char*` directly to tgls if we can figure out how ctypes works.
 */
external soilLoadImage : (~filename: string, ~loadOption: int) => option(imageT) = "load_image";

/* Load image from a binary blob */
external soilLoadImageFromMemory : (~data: string, ~loadOption: int) => option(imageT) = "load_image_from_memory";

/*{
    module Sdl = Tsdl_new;
    let create_window gl::(maj, min) => {
      let (>>=) = Sdl.(>>=);
      let w_atts = Sdl.Window.(opengl + resizable);
      let w_title = Printf.sprintf "OpenGL %d.%d (core profile)" maj min;
      let set a v => Sdl.Gl.gl_set_attribute a v;
      set Sdl.Gl.context_profile_mask Sdl.Gl.context_profile_compatibility >>= (
        fun () =>
          set Sdl.Gl.context_major_version maj >>= (
            fun () =>
              set Sdl.Gl.context_minor_version min >>= (
                fun () =>
                  set Sdl.Gl.doublebuffer 1 >>= (
                    fun () =>
                      Sdl.create_window
                        title::w_title
                        x::Sdl.Window.pos_centered
                        y::Sdl.Window.pos_centered
                        w::640
                        h::480
                        flags::w_atts
                  )
              )
          )
      )
    };
    let getProgram ::vertexShaderSource ::fragmentShaderSource :option programT => {
      let vertexShader = createShader gl_vertex_shader;
      shaderSource vertexShader [|vertexShaderSource|];
      compileShader vertexShader;
      let compiledCorrectly = getShaderiv shader::vertexShader pname::gl_compile_status == 1;
      if compiledCorrectly {
        let fragmentShader = createShader gl_fragment_shader;
        shaderSource fragmentShader [|fragmentShaderSource|];
        compileShader fragmentShader;
        let compiledCorrectly = getShaderiv shader::fragmentShader pname::gl_compile_status == 1;
        if compiledCorrectly {
          let program = createProgram ();
          attachShader ::program shader::vertexShader;
          deleteShader vertexShader;
          attachShader ::program shader::fragmentShader;
          deleteShader fragmentShader;
          linkProgram program;
          let linkedCorrectly = getProgramiv ::program pname::gl_link_status == 1;
          if linkedCorrectly {
            Some program
          } else {
            print_endline @@ "Linking error: " ^ getProgramInfoLog ::program;
            None
          }
        } else {
          print_endline @@ "Fragment shader error: " ^ getShaderInfoLog shader::fragmentShader;
          None
        }
      } else {
        print_endline @@ "Vertex shader error: " ^ getShaderInfoLog shader::vertexShader;
        None
      }
    };
    let e = Sdl.Init.init Sdl.Init.everything;
    assert (e == 0);
    let w = create_window gl::(2, 1);
    let gl = Sdl.gl_create_context w;
    let e = Sdl.gl_make_current w gl;
    assert (e == 0);
    viewport x::(-1) y::(-1) width::640 height::480;
    clearColor red::0. green::0. blue::1. alpha::1.;
    enable gl_blend;
    blendFunc gl_src_alpha gl_one_minus_src_alpha;
    let vertexShaderSource = {|
        attribute vec4 aVertexPosition;
        attribute vec4 aColor;

        varying vec4 v_v4FillColor;

        void main() {
          v_v4FillColor = aColor;
          gl_Position = aVertexPosition;
        }
      |};
    let fragmentShaderSource = {|
        varying vec4 v_v4FillColor;

        void main() {
          gl_FragColor = v_v4FillColor;
        }
      |};
    switch (getProgram ::vertexShaderSource ::fragmentShaderSource) {
    | None => failwith "what the heck"
    | Some program =>
      let positionAttrib = getAttribLocation ::program name::"aVertexPosition";
      enableVertexAttribArray positionAttrib;
      let colorAttrib = getAttribLocation ::program name::"aColor";
      enableVertexAttribArray colorAttrib;
      let bothBuffers = genBuffers 2;
      let vertexBuffer = bothBuffers.(0);
      let vertexData = Bigarray.Array1.create Bigarray.Float32 Bigarray.c_layout 12;
      vertexData.{0} = 0.0;
      vertexData.{1} = 0.5;
      vertexData.{2} = 0.0;
      vertexData.{3} = 1.0;
      vertexData.{4} = (-0.5);
      vertexData.{5} = (-0.5);
      vertexData.{6} = 0.0;
      vertexData.{7} = 1.0;
      vertexData.{8} = 0.5;
      vertexData.{9} = (-0.5);
      vertexData.{10} = 0.0;
      vertexData.{11} = 1.0;
      /*bindBuffer target::gl_array_buffer buffer::vertexBuffer;
        bufferData target::gl_array_buffer data::vertexData usage::gl_static_draw;*/
      let colorData = Bigarray.Array1.create Bigarray.Float32 Bigarray.c_layout 12;
      colorData.{0} = 1.0;
      colorData.{1} = 0.0;
      colorData.{2} = 0.0;
      colorData.{3} = 1.0;
      colorData.{4} = 0.0;
      colorData.{5} = 1.0;
      colorData.{6} = 0.0;
      colorData.{7} = 1.0;
      colorData.{8} = 0.0;
      colorData.{9} = 1.0;
      colorData.{10} = 0.0;
      colorData.{11} = 1.0;
      let colorBuffer = bothBuffers.(1);
      /*bindBuffer target::gl_array_buffer buffer::colorBuffer;
        bufferData target::gl_array_buffer data::colorData usage::gl_static_draw;*/
      print_endline "test";
      let shouldRun = ref true;

      /** main loop */
      while !shouldRun {
        switch (Sdl.Event.poll_event ()) {
        | None => ()
        | Some e =>
          if (Sdl.Event.typ e == Sdl.Event.keydown) {
            if (Sdl.Event.keyboard_keycode e == 27) {
              print_endline "pressed escape!";
              shouldRun := false
            }
          }
        };

        /** main draw calls */
        clear (gl_color_buffer_bit + gl_depth_buffer_bit);
        useProgram program;

        /** vertices */
        bindBuffer target::gl_array_buffer buffer::vertexBuffer;
        bufferData target::gl_array_buffer data::vertexData usage::gl_stream_draw;
        vertexAttribPointer
          index::positionAttrib size::4 typ::gl_float normalize::false stride::0 offset::0;

        /** colors */
        bindBuffer target::gl_array_buffer buffer::colorBuffer;
        bufferData target::gl_array_buffer data::colorData usage::gl_static_draw;
        vertexAttribPointer
          index::colorAttrib size::4 typ::gl_float normalize::false stride::0 offset::0;
        drawArrays mode::gl_triangles first::0 count::3;
        Sdl.gl_swap_window w
      }
    };
    Sdl.destroy_window w;
    /*};*/
    /*)*/
    /*);*/
    Sdl.quit ()
  };
  */

[@noalloc] external checkFramebufferStatus : unit => int = "TglCheckFramebufferStatus";
type renderBufferT;
[@noalloc] external genRenderbuffers : unit => renderBufferT = "TglGenRenderbuffers";
[@noalloc] external bindRenderbuffer : renderBufferT => unit = "TglBindRenderbuffer";
[@noalloc] external bindDefaultRenderbuffer : unit => unit = "TglBindDefaultRenderbuffer";
[@noalloc] external renderbufferStorage : int => int => unit = "TglRenderbufferStorage";
[@noalloc] external framebufferRenderbuffer : renderBufferT => unit = "TglFramebufferRenderbuffer";
