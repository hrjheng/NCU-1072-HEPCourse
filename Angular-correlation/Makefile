CFLAGS = -pthread -m64 -Wno-deprecated -I src/
CFLAGS += $(shell root-config --cflags --libs)

all : ReadToTree Correlation

ReadToTree : src/ReadToTree.cxx src/Event.cc src/Minitree.cc
	g++ ${CFLAGS} src/ReadToTree.cxx src/Event.cc src/Minitree.cc -o ReadToTree
    
Correlation : src/Correlation.cxx src/Event.cc src/Minitree.cc
	g++ ${CFLAGS} src/Correlation.cxx src/Event.cc src/Minitree.cc -o Correlation