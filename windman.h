/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include <X11/Xlib.h>
#include<stdio.h>
#include<sys/types.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
//g++ -o windman -lX11 windman.cpp


int argc =0;
typedef enum RotationEnum { bottom_to_top, top_to_bottom } Rotation;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
class task;
class Окна{
Display *dpy = XOpenDisplay(0x0);
	public:
   	Окна();

	void откр();

	std::vector<task> vt;
void x_alt_tab(Rotation r, Display *dpy, Window *wins, unsigned int nwins);

//Display *dpy = XOpenDisplay(0x0);
XWindowAttributes attr;
XButtonEvent start;
XEvent ev;
unsigned int nwins = 0;
Window root, parent, *wins = 0;

Display *getDisplay(){return dpy;}

//thread terminal



};


class task{
	public:
task(){/*lunch*/}
~task(){/*kill*/}
};
//std::vector<task> vt;






