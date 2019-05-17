CFLAGS = -pthread -m64 -Wno-deprecated -I src/
CFLAGS += $(shell root-config --cflags --libs)

all : GlauberMC GlauberMC_R1R2

GlauberMC : src/GlauberMC.cxx src/Nucleus.cc src/Nucleon.cc src/Event.cc src/Minitree.cc
	g++ ${CFLAGS} src/GlauberMC.cxx src/Nucleus.cc src/Nucleon.cc src/Event.cc src/Minitree.cc -o GlauberMC

GlauberMC_R1R2 : src/GlauberMC_R1R2.cxx src/Nucleus.cc src/Nucleon.cc src/Event.cc src/Minitree.cc
	g++ ${CFLAGS} src/GlauberMC_R1R2.cxx src/Nucleus.cc src/Nucleon.cc src/Event.cc src/Minitree.cc -o GlauberMC_R1R2
