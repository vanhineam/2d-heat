#include <stdio.h> 
#include <stdlib.h> 
#include <X11/Xlib.h> // X11 library headers 
#include <X11/Xutil.h> 
#include <X11/Xos.h> 
#define X_RESN 800 // x resolution 
#define Y_RESN 800 // y resolution 
int main (int argc, char **argv ) { 
/* --------------------------- X11 graphics setup ------------------------------ */ 
	Window win; // initialization for a window 
	unsigned int width, height, // window size */ 
	win_x,win_y, // window position 
	border_width, // border width in pixels 
	display_width, display_height, // size of screen 
	screen; // which screen 
	char *window_name = "My graphics program", *display_name = NULL; 
	GC gc; 
	unsigned long valuemask = 0; 
	XGCValues values; 
	Display *display; 
	Pixmap bitmap; 
	XPoint points[800]; 
	FILE *fp, *fopen (); 
	char str[100]; 

	XSetWindowAttributes attr[1]; 

	if ( (display = XOpenDisplay (display_name)) == NULL ) { // connect to Xserver 
		fprintf (stderr, "Cannot connect to X server %s\n",XDisplayName (display_name) ); 
		exit (-1); 
	} 
	screen = DefaultScreen (display); // get screen size, not used here 
	display_width = DisplayWidth (display, screen); 
	display_height = DisplayHeight (display, screen); 
	width = X_RESN; // set window size 
	height = Y_RESN; 
	win_x = 0; win_y = 0; // set window position 
	border_width = 4; // create opaque window 
	win = XCreateSimpleWindow (display, RootWindow (display, screen), 
	win_x, win_y, width, height, border_width, 
	BlackPixel (display, screen), WhitePixel (display, screen)); 
	XStoreName(display, win, window_name); 
	gc = XCreateGC (display, win, valuemask, &values); // create graphics context 
	XSetBackground (display, gc, WhitePixel (display, screen)); 
	XSetForeground (display, gc, BlackPixel (display, screen)); 
	XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound); 
	XMapWindow (display, win); 
	XSync(display, 0); 
	/* ---------- End of X11 graphics setup, continue with application code, sample given here ------- */ 
	usleep(100000); // some delay appears necessary 3
	XClearWindow(display, win); // clear window for next drawing 
	XSetForeground(display,gc,(long) 0xDC143C); // color of foreground (applies to object to be drawn) 
	//XDrawPoint (display, win, gc, 400, 400); // draw point at location x, y in window 

	XFillArc (display,win,gc,400,400,50,50,0,23040); // draw circle of size 50x50 at location 400,400 

	XFlush(display); // necessary to write to display 

	usleep(10000000); // provide a delay beween each drawing 
	return 0; 
} 