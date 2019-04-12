CFLAGS = -pthread -m64 -Wno-deprecated -I src/
CFLAGS += $(shell root-config --cflags --libs)

all : Tracklet_analysis

Tracklet_analysis : src/Tracklet_analysis.cxx src/Hit.cc src/Layer.cc
	g++ ${CFLAGS} src/Tracklet_analysis.cxx src/Hit.cc src/Layer.cc -o Tracklet_analysis