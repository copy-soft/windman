all:
	g++ -c -o libwindman.so windman.cpp -lX11

exe:
	g++ -lwindman -L. -o windman main.cpp -lX11
