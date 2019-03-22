lib: tgls_new.o

tgls_new.o: src/tgls_new.c
	ocamlopt.opt -c src/tgls_new.c

# ocamlopt.opt -ccopt -L  -ccopt /opt/X11/lib -ccopt -lGLESv2 bigarray.cmxa tgls_new.o src/tgls_new.cmx
# ocamlopt.opt -ccopt -L  -ccopt /System/Library/Frameworks/OpenGL.framework/Libraries -ccopt -lGL -ccopt -L -ccopt ~/Desktop/reprocessing/node_modules/sdl2/ -ccopt -lSDL2 bigarray.cmxa ~/Desktop/tsdl/tsdl_new.o ~/Desktop/tsdl/src/tsdl_new.cmx tgls_new.o src/tgls_new.cmx

# all:
# 	ocamlc.opt -c src/tgls_new.c
# 	ocamlc.opt -c -pp '~/Desktop/reprocessing/node_modules/bs-platform/bin/refmt.exe -p binary' -impl src/tgls_new.re 2>&1 | berror
# 	# ocamlc.opt -ccopt -L  -ccopt /opt/X11/lib -ccopt -lGLESv2 bigarray.cmxa tgls_new.o src/tgls_new.cmx
# 	ocamlc.opt -ccopt -L  -ccopt /opt/X11/lib -ccopt -lGLESv2 bigarray.cma tgls_new.o src/tgls_new.cmo
