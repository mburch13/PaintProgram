//  McKenzie Burch
//  sketch.h
//  Date: Noveber 10, 2017
//

#ifndef sketch_h
#define sketch_h

#ifdef __APPLE__
#  include <OpenGL/gl.h>  // definitions for GL graphics routines
#  include <OpenGL/glu.h> // definitions for GL input device handling
#  include <GLUT/glut.h>  // deginitions for the GLUT utility toolkit
#else
#  include <GL/gl.h>      // definitions for GL graphics routines
#  include <GL/glu.h>     // definitions for GL input device handling
#  include <GL/glut.h>    // deginitions for the GLUT utility toolkit
#endif

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define WIDTH       900          // window dimensions
#define HEIGHT      800

#define MENUWIDTH   100          // menu dimensions
#define TOOLHEIGHT   (HEIGHT/10)
#define NCOLORS     8            // number of colors
#define BOXHEIGHT   (HEIGHT / NCOLORS)

#define RGBRED      1, 0, 0      // RGB Colors for menu
#define RGBGREEN    0, 1, 0
#define RGBBLUE     0, 0, 1
#define RGBYELLOW   1, 1, 0
#define RGBWHITE    1, 1, 1
#define RGBMAGENTA  1, 0, 1
#define RGBGREY    .5,.5,.5
#define RGBCYAN     0, 1, 1

#define RGBBLACK    0, 0, 0      // black for screen background

#define R    0
#define G    1
#define B    2

#define PI 3.1415926536


static float colormenu[][3] = {{RGBRED}, {RGBYELLOW}, {RGBGREEN}, {RGBCYAN}, {RGBBLUE}, {RGBMAGENTA}, {RGBGREY}, {RGBWHITE}};

struct Point{
    int x;
    int y;
};

struct Endpoint{
    Point pt1;
    Point pt2;
};

struct Circle{
    Point center;
    int radius;
};

union Tool{
    Endpoint endpoints;
    Circle circle;
};

struct Object {
    short int colorType;
    short int toolType;
    Tool tool;
};

class Sketch {
private:
    Object objects[10000];
    int n;
    
public:
    Sketch();
    void createObject(short int, short int, int, int, int, int); //rectangle
    void createObject(short int,  short int, int, int, int);  //circle
    void updateObject(int, int);
    void draw();
    void drawLine(int, int, int, int);
    void drawRectangle(GLint, int, int, int, int);
    void drawCircle(GLint, int, int, int);
    void clear();
    bool load();
    void save();
    void quit();
};


#endif /* sketch_h */

