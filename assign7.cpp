//
//  assign7.cpp
//
//
//  Created by McKenzie on 12/13/17.
//
#include "sketch.h"

Sketch mySketch;
short int currentColor = 0;
short int currentTool = 0;
static int tracking = 0;
float prev_x;
float prev_y;

int inwindow(int x, int y) {

    return (x > MENUWIDTH && x < WIDTH - MENUWIDTH && y > 0 && y < HEIGHT);
}
int incolormenu(int x, int y) {

    return (x >= 0 && x <= MENUWIDTH && y >= 0 && y <= HEIGHT);
}
int intoolmenu(int x, int y) {
    
    return (x >= WIDTH - MENUWIDTH && x <= WIDTH && y >= 0 && y <= HEIGHT);
}
int colormenuindex(int x, int y) {

    if(!incolormenu(x, y))
        return -1;
    else
        return(y / BOXHEIGHT);
}
int toolmenuindex(int x, int y) {
    
    if(!intoolmenu(x, y))
        return -1;
    else
        return (y/TOOLHEIGHT);
}

void drawMenu() {
    
    int i;
    
    // clear window
//    glClear(GL_COLOR_BUFFER_BIT);
    
    // draw the color menu
    for(i = 0; i < NCOLORS; i++){
        glColor3f(colormenu[i][R], colormenu[i][G], colormenu[i][B]);
        glRecti(1, BOXHEIGHT * i + 1,
                MENUWIDTH - 1, BOXHEIGHT * (i + 1) - 1);
    }
    glFlush();
}


void drawTools(){
    int i;
    for(i = 0; i < 10; i++){
        glColor3f(colormenu[6][R], colormenu[6][G], colormenu[6][B]);
        glRecti(WIDTH, TOOLHEIGHT * i + 1,
                WIDTH - MENUWIDTH, TOOLHEIGHT * (i + 1) - 1);
    }
    glFlush();
    
    double dx = WIDTH - MENUWIDTH/2;
    glColor3f(0,0,0);
    
    //unfilled rectangle
    double dy = 0*TOOLHEIGHT + TOOLHEIGHT/2;
    glPushMatrix();
    glTranslated(dx,dy,0);
    glScalef(25, 25, 1);
    mySketch.drawRectangle(GL_LINE_LOOP, -1, -1, 1, 1);
    glPopMatrix();
    
    //filled rectangle
    dy = 1*TOOLHEIGHT + TOOLHEIGHT/2;
    glPushMatrix();
    glTranslated(dx, dy, 0);
    glScalef(25, 25, 1);
    mySketch.drawRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();
 
    //unfilled circle
    dy = 2*TOOLHEIGHT + TOOLHEIGHT/2;
    glPushMatrix();
    glTranslated(dx, dy, 0);
    glScalef(25, 25, 1);
    mySketch.drawCircle(GL_LINE_LOOP, 0, 0, 1);
    glPopMatrix();
    
    //filled circle
    dy = 3*TOOLHEIGHT + TOOLHEIGHT/2;
    glPushMatrix();
    glTranslated(dx, dy, 0);
    glScalef(25, 25, 1);
    mySketch.drawCircle(GL_POLYGON, 0, 0, 1);;
    glPopMatrix();
    
    //line
    dy = 4*TOOLHEIGHT + TOOLHEIGHT/2;
    glPushMatrix();
    glTranslated(dx, dy, 0);
    glScalef(25, 25, 1);
    mySketch.drawLine(-1, -1, 1, 1);
    glPopMatrix();
    
    //freeform line
    dy = 5*TOOLHEIGHT + TOOLHEIGHT/2;
    glPushMatrix();
    glTranslated(dx, dy+5, 0);
    glScalef(8, 25, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1, -1);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(-1, -1);
    glVertex2f(0, -1.5);
    glVertex2f(1, -1);
    glEnd();
    glPopMatrix();
    
    //clear
    dy = 6*TOOLHEIGHT + TOOLHEIGHT/2;
    glPushMatrix();
    glTranslated(dx-15, dy-20, 0);
    glScalef(3, 15, 1);
    mySketch.drawRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(dx, dy-20, 0);
    glScalef(8, 15, 1);
    mySketch.drawRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(dx+15,dy-20, 0);
    glScalef(3, 15, 1);
    mySketch.drawRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(dx, dy, 0);
    glScalef(20, 3, 1);
    mySketch.drawRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(dx, dy+20, 0);
    glScalef(5, 15, 1);
    mySketch.drawRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();
    
    //save
    dy = 7*TOOLHEIGHT + TOOLHEIGHT/2;
    glPushMatrix();
    glTranslated(dx, dy, 0);
    glScalef(25,25,1);
    mySketch.drawRectangle(GL_LINE_LOOP, -1, -1, 1, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(dx, dy, 1);
    glScalef(15,25,1);
    mySketch.drawRectangle(GL_LINE_LOOP, -1, 0, 1, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(dx+5, dy+15, 1);
    glScalef(3,8,1);
    mySketch.drawRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();
    
    //load
    dy = 8*TOOLHEIGHT + TOOLHEIGHT/2;
    glPushMatrix();
    glTranslated(dx, dy-25, 0);
    glScalef(20, 3, 1);
    mySketch.drawRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(dx, dy+25, 0);
    glScalef(20, 3, 1);
    mySketch.drawRectangle(GL_POLYGON, -1, -1, 1, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(dx, dy, 0);
    glScalef(15,22, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1, 1);
    glVertex2f(0, 0);
    glVertex2f(1, 1);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(dx, dy, 0);
    glScalef(7.5,11, 1);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 1);
    glVertex2f(0, 0);
    glVertex2f(1, 1);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(dx, dy, 0);
    glScalef(15,-22, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1, 1);
    glVertex2f(0, 0);
    glVertex2f(1, 1);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(dx, dy-11, 0);
    glScalef(7.5, -11, 1);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 1);
    glVertex2f(0, 0);
    glVertex2f(1, 1);
    glEnd();
    glPopMatrix();
    
    //quit
    dy = 9*TOOLHEIGHT + TOOLHEIGHT/2;
    glPushMatrix();
    glTranslated(dx, dy, 0);
    glScalef(25, 18, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1, -1);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(1.5, 0);
    glVertex2f(1, -1);
    glEnd();
    glScalef(.5, .5, 1);
    mySketch.drawLine(-1, -1, 1, 1);
    mySketch.drawLine(1, -1, -1, 1);
    glPopMatrix();
}
void drawScene(){
    glClear(GL_COLOR_BUFFER_BIT);
    mySketch.draw();
    drawMenu();
    drawTools();
    glutSwapBuffers();
}

void m_Motion(int x, int y) {

    y = HEIGHT - y;

    if(tracking && inwindow(x, y)) {
        if(currentTool == 5){
            mySketch.createObject(currentColor, currentTool, prev_x, prev_y, x, y);
            prev_x = x;
            prev_y = y;
    }
        else{
            mySketch.updateObject(x,y);
        }
        glutPostRedisplay();
    }
}

void handleButton(int button, int state, int x, int y){

    static int toolIndex;
    
    y = HEIGHT - y;   // reverse y, so zero at bottom, and max at top

    if(button != GLUT_LEFT_BUTTON)   // ignore all but left button
        return;
    if(state == GLUT_DOWN){
        if(incolormenu(x, y)){
            currentColor = colormenuindex(x, y);
            cout << "Current Color " << currentColor << endl;
        }
        if(intoolmenu(x, y)){
            toolIndex = toolmenuindex(x, y);
            if(toolIndex >= 6){
                switch(toolIndex){
                    case 6:
                        mySketch.clear();
                        glutPostRedisplay();
                        break;
                        
                    case 7:
                        mySketch.save();
                        break;
                        
                    case 8:
                        mySketch.load();
                        break;
                        
                    case 9:
                        mySketch.quit();
                        break;
                }
            }
            else{
                currentTool = toolIndex;
            }
            cout << "Current Tool: " << toolIndex << endl;
        }
        if(inwindow(x, y)) {
                switch (currentTool) {
                    case 0:
                    case 1:
                    case 4:
                        mySketch.createObject(currentColor, currentTool, x, y, x, y);
                        break;

                    case 2:
                    case 3:
                        mySketch.createObject(currentColor, currentTool, x, y, 0);
                        break;

                    case 5:
                        prev_x = x;
                        prev_y = y;
                        break;
                }
            tracking = 1;
        }
        else {
            tracking = 0;
        }
   }
}

int main(int argc, char* argv[]) {
    
    glutInit(&argc, argv);
    
    // open window and establish coordinate system on it
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Paint");
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    
    // register display and mouse-button callback routines
    glutDisplayFunc(drawScene);
    glutMotionFunc(m_Motion);         // mouse movement event callback
    glutMouseFunc(handleButton);
    
    // Set up to clear screen to black
    glClearColor(RGBBLACK, 1);
    
    glutMainLoop();
    
    return 0;
}
