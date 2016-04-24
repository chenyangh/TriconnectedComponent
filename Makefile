all: triconnect

triconnect: main.o Tricomp.o Tools.o
	g++ -std=c++11 main.o Tricomp.o Tools.o	

main.o: main.cppfile:///home/chenyang/projects/triconnected_comp_Tsin/499_brand_new/Makefile
	g++ -std=c++11 main.cpp

Tricomp.o: Tricomp.h Tricomp.cpp
	g++ -std=c++11 -c Tricomp.h Tricomp.cpp

Tools.o: Tools.h
	g++ -std=c++11 -c Tools.h