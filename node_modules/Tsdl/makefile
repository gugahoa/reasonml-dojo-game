lib: tsdl_new.o

tsdl_new.o: src/tsdl_new.c
	ocamlopt.opt -c -ccopt -I -ccopt ../sdl2/include/ src/tsdl_new.c

# test:
# 	~/Desktop/reprocessing/node_modules/bs-platform/bin/ocamlopt.opt -c -ccopt -I -ccopt ~/Desktop/reprocessing/node_modules/sdl2/include/ src/tsdl_new.c
# 	time ~/Desktop/reprocessing/node_modules/bs-platform/bin/ocamlopt.opt -ccopt -L -ccopt ~/Desktop/reprocessing/node_modules/sdl2/ -ccopt -lSDL2 tsdl_new.o src/tsdl_new.cmx
