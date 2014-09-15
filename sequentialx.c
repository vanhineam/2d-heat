#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#define X_RESN 800
#define Y_RESN 800

void getInput(int*, int*);

int main(int arc, char* argv) {
    clock_t begin,end;
    double time_spent;
    int iteration, i, j, current, next, N, T;

    getInput(&N, &T);

    //initaialize the array
    double h[2][N][N];

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            h[0][i][j] = 0;
            h[1][i][j] = 0;
        }
    }
    // Set all the walls to 20C degrees
    for(i = 0; i < N; i++) {
        h[0][0][i] = 20.0;
        h[0][i][0] = 20.0;
        h[0][N-1][i] = 20.0;
        h[0][i][N-1] = 20.0;
    }

    // Set the starting point and the ending point of the fireplace
    double fp_start, fp_end;
    fp_start = 0.3 * N;
    fp_end = (0.7 * N);

    // Initialize the values of the location of the fireplacee to 100C
    for(i = fp_start; i < fp_end; i++) {
        h[0][0][i] = 100.0;
    }

    // Get the start time of the program
    begin = clock();

    // The actual calculation of the temperature of the room.
    current = 0;
    next = 1;
    for (iteration = 0; iteration < T; iteration++) {
        for( i = 1; i < N-1; i++) {
            for( j = 1; j < N-1; j++) {
                h[next][i][j] = 0.25 * (h[current][i-1][j] + h[current][i+1][j]+ h[current][i][j-1] + h[current][i][j+1]);
            }
        }
        current = next;
        next = (current + 1) % 2;
    }

    // Get the end time
    end = clock();
    // Calculate the time spent
    time_spent = (double)(end-begin) /CLOCKS_PER_SEC;

    // Print an 8x8 array the N/8 x N/8 positions of the room.
    for(i = 0; i < N; i+= N/8) {
        for(j = 0; j < N; j+= N/8) {
            printf("%.2f ", h[0][i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Print the time in seconds that the program took to run
    printf("The program took %f seconds to run.\n", time_spent);

    Window win;
    unsigned int width, height,
    win_x, win_y,
    border_width,
    display_width, display_height,
    screen;
    char *window_name = "2d-heat program", *display_name = NULL;
    GC gc;
    unsigned long valuemask = 0;
    XGCValues values;
    Display *display;
    Pixmap bitmap;
    XPoint points[800];
    FILE *fp, *fopen();
    char str[100];

    XSetWindowAttributes attr[1];

    if( (display = XOpenDisplay(display_name)) == NULL) { // connect to Xserver
        fprintf(stderr, "Cannot connect to X server %s\n", XDisplayName(display_name));
        exit(-1);
    }

    screen = DefaultScreen(display); // get screen sized
    display_width = DisplayWidth(display, screen);
    display_height = DisplayHeight(display, screen);

    width = X_RESN;
    height = Y_RESN;
    win_x = 0;
    win_y = 0;

    border_width = 4;
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

    int counter = 0;
    int blue = 0x0054A6;
    int cyan_blue = 0x0072BC;
    int cyan = 0x00AEEF;
    int green_cyan = 0x00A99D;
    int green = 0x00A651;
    int yellow_green = 0x39B54A;
    int yellow = 0xFFF200;
    int yellow_orange = 0xF7941D;
    int orange = 0xF26522;
    int red = 0xED1C24;

    usleep(100000);
    XClearWindow(display,win);
    XSetForeground(display,gc, (long) 0xDC143C);
    int x_counter, y_counter = 0;
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++){
            if(h[0][i][j] >= 0.0 && h[0][i][j] <= 5.0){
                XSetForeground(display,gc, (long) blue);
            }
            if(h[0][i][j] > 5.0 && h[0][i][j] <= 10.0){
                XSetForeground(display,gc, (long) cyan);
            }
            else if(h[0][i][j] > 10.0 && h[0][i][j] <= 20.0){
                XSetForeground(display,gc, (long) green);
            }
            else if(h[0][i][j] > 20.0 && h[0][i][j] <= 30.0){
                XSetForeground(display,gc, (long) yellow_green);
            }
            else if(h[0][i][j] > 30.0 && h[0][i][j] <= 40.0){
                XSetForeground(display,gc, (long) yellow);
            }
            else if(h[0][i][j] > 40.0 && h[0][i][j] <= 50.0){
                XSetForeground(display,gc, (long) yellow);
            }
            else if(h[0][i][j] > 50.0 && h[0][i][j] <= 60.0){
                XSetForeground(display,gc, (long) orange);
            }
            else if(h[0][i][j] > 60.0 && h[0][i][j] <= 70.0){
                XSetForeground(display,gc, (long) orange);
            }
            else if(h[0][i][j] > 70.0 && h[0][i][j] <= 80.0){
                XSetForeground(display,gc, (long) orange);
            }
            else if(h[0][i][j] > 80.0 && h[0][i][j] <= 90.0){
                XSetForeground(display,gc, (long) orange);
            }
            else if(h[0][i][j] > 90.0 && h[0][i][j] <= 100.0){
                XSetForeground(display,gc, (long) red);
            }
            XFillArc(display,win,gc,x_counter, y_counter,5,5,0,23040);
            x_counter += 10;
        }
        x_counter = 0;
        y_counter += 10;
    }


    XFlush(display);
    usleep(10000000);
    return 0;

}

void getInput(int* N, int* T) {
    // Get the size of the matrix
    int valid = 0;
    while(!valid) {
        printf("Please enter matrix size(NxN): ");
        scanf("%d", N);
        if(N) {
            valid = 1;
        }
    }

    // Get the number of iterations
    valid = 0;
    while(!valid) {
        printf("Please enter the number of iterations: ");
        scanf("%d", T);
        if(N) {
            valid = 1;
        }
    }
}