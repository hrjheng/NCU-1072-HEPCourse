CFLAGS = -pthread -m64 -Wno-deprecated -I src/
CFLAGS += $(shell root-config --cflags --libs)

all : ReadToTree

ReadToTree : src/ReadToTree.cxx src/Minitree.cc src/Event.cc
	g++ ${CFLAGS} src/ReadToTree.cxx src/Minitree.cc src/Event.cc -o ReadToTree
