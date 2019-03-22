open Bsb_internals;

let ( +/ ) = Filename.concat;

/* SOIL library */
gcc("lib" +/ "image_helper.o",  ["SOIL" +/ "src" +/ "image_helper.c"]);
gcc("lib" +/ "stb_image_aug.o", ["SOIL" +/ "src" +/ "stb_image_aug.c"]);
gcc("lib" +/ "image_DXT.o",     ["SOIL" +/ "src" +/ "image_DXT.c"]);
gcc(~includes=["glad" +/ "include"], "lib" +/ "SOIL.o", ["SOIL" +/ "src" +/ "SOIL.c"]);


gcc("lib" +/ "soil_wrapper.o",  ["src" +/ "soil_wrapper.c"]);

gcc(~includes=["glad" +/ "include"], "lib" +/ "glad.o",     ["glad" +/ "src" +/ "glad.c"]);

gcc(~includes=["glad" +/ "include"], "lib" +/ "tgls_new.o", ["src" +/ "tgls_new.c"], ~flags=["-std=c99"]);
