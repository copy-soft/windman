/* TinyWM is written by Nick Welch <nick@incise.org> in 2005 & 2011.
 *
 * This software is in the public domain
 * and is provided AS IS, with NO WARRANTY. */

#include "windman.h"
//g++ -o windman -lX11 windman.cpp


#define MAX(a, b) ((a) > (b) ? (a) : (b))

class D;



D::D(){

//dpy = XOpenDisplay(0x0);






         XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F11")), Mod1Mask,
                                             DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
         XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F12")), Mod1Mask,
                                             DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
         XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F3")), Mod1Mask,
                                             DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
         XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F4")), Mod1Mask,
                                             DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
         XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F5")), Mod1Mask,
                                             DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
         XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F6")), Mod1Mask,
                                             DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);


         XGrabKey (dpy, XKeysymToKeycode(dpy,XK_Tab), Mod1Mask, DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);




         XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("F7")), Mod1Mask,
                         DefaultRootWindow(dpy), True, GrabModeAsync, GrabModeAsync);
         XGrabButton(dpy, 1, Mod1Mask, DefaultRootWindow(dpy), True,
                       ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);
         XGrabButton(dpy, 3, Mod1Mask, DefaultRootWindow(dpy), True,
                       ButtonPressMask|ButtonReleaseMask|PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None);

                        start.subwindow = None;


for(;;)
{
  XNextEvent(dpy, &ev);



  if(ev.type == KeyPress){




   if(ev.xkey.keycode==XKeysymToKeycode(dpy,XK_Tab)){
   XSync(dpy, True);
   XQueryTree(dpy, DefaultRootWindow(dpy), &root, &parent, &wins, &nwins);
   if (nwins <= 1) exit;
   Rotation r = (argc == 1) ? bottom_to_top : top_to_bottom;
   x_alt_tab(r, dpy, wins, nwins);}


//if (ev.xkey.keycode==XKeysymToKeycode(dpy, XStringToKeysym("F11"))) { }



if (ev.xkey.keycode==69) {
pid_t pid0 = fork();//create copy of current process
if (pid0 == 0) {//if child
const char *argv[] ={"st",NULL,NULL,NULL,NULL};
execvp(argv[0], const_cast<char *const *>(argv));
pid0=NULL;}
}

if (ev.xkey.keycode==71) {
pid_t pid = fork();//create copy of current processr
if (pid == 0) {//if child
const char *argv1[] ={"browser",NULL,NULL,NULL, NULL};
execvp(argv1[0], const_cast<char *const *>(argv1));
pid=NULL;}
}
}

if(ev.type == ButtonPress && ev.xbutton.subwindow != None)
{

XRaiseWindow(dpy, ev.xkey.subwindow);
XSetInputFocus(dpy, ev.xkey.subwindow, RevertToNone, CurrentTime);
XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
start = ev.xbutton;
}
else if(ev.type == MotionNotify && start.subwindow != None)
{
int xdiff = ev.xbutton.x_root - start.x_root;
int ydiff = ev.xbutton.y_root - start.y_root;
XMoveResizeWindow(dpy, start.subwindow,
attr.x + (start.button==1 ? xdiff : 0),
attr.y + (start.button==1 ? ydiff : 0),
MAX(1, attr.width + (start.button==3 ? xdiff : 0)),
MAX(1, attr.height + (start.button==3 ? ydiff : 0)));
}
else if(ev.type == ButtonRelease)
start.subwindow = None;
}
}
void D::run(){}


void D::x_alt_tab(Rotation r, Display *dpy, Window *wins, unsigned int nwins) {
      Window *viewables[nwins], *w = 0;
      unsigned int vc = 0;

      //  make list of viewable windows
      for (w = wins; w - wins < nwins; w++) {
      XWindowAttributes attr;

      if (! XGetWMHints(dpy, *w))
      continue;
      if (! XGetWindowAttributes(dpy, *w, &attr))
      continue;
      if (attr.override_redirect)
      continue;
      if (attr.map_state != IsViewable)
      continue;
      viewables[vc++] = w;
      }
      viewables[vc] = NULL;
      // promote the bottom to top, or demote top to bottom and raise 2nd
      if (r == bottom_to_top)
      w = viewables[0];
      else {
      XLowerWindow(dpy, *(viewables[vc - 1]));
      w = viewables[vc - 2];
      }
      XRaiseWindow(dpy, *w);
      XSetInputFocus(dpy, *w, RevertToPointerRoot, CurrentTime);
      XSync(dpy, True);
}




int main(void) {


  D *d= new D();

  d->run();

}


