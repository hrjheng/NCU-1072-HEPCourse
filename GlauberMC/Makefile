CFLAGS = -pthread -m64 -Wno-deprecated -I src/
CFLAGS += $(shell root-config --cflags --libs)

all : GlauberMC

GlauberMC : src/GlauberMC.cxx src/Nucleus.cc src/Nucleon.cc src/Event.cc src/Minitree.cc
	g++ ${CFLAGS} src/GlauberMC.cxx src/Nucleus.cc src/Nucleon.cc src/Event.cc src/Minitree.cc -o GlauberMC
