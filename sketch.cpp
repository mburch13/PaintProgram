//  McKenzie Burch
//  sketch.cpp
//  Date: Noveber 10, 2017
//

#include "sketch.h"

//helper function
float distance(int x1, int y1, int x2, int y2){
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}


//----------------------------------
//Constructor
Sketch::Sketch(){
    n = 0;
}
//----------------------------------
//Creates rectangles and lines
void Sketch::createObject(short int c, short int t, int x1, int y1, int x2, int y2){
        objects[n].colorType = c;
        objects[n].toolType = t;
        objects[n].tool.endpoints.pt1.x = x1;
        objects[n].tool.endpoints.pt1.y = y1;
        objects[n].tool.endpoints.pt2.x = x2;
        objects[n].tool.endpoints.pt2.y = y2;
        n++;
}
//----------------------------------
//Creates circles
void Sketch::createObject(short int c, short int t, int cx, int cy, int r){
    objects[n].colorType = c;
    objects[n].toolType = t;
    objects[n].tool.circle.center.x = cx;
    objects[n].tool.circle.center.y = cy;
    objects[n].tool.circle.radius = r;
    n++;
}
//----------------------------------
//update the radius or x2 y2
void Sketch::updateObject(int x, int y){
    if(objects[n-1].toolType == 2 || objects[n-1].toolType == 3){
        int cx = objects[n-1].tool.circle.center.x;
        int cy = objects[n-1].tool.circle.center.y;
        objects[n-1].tool.circle.radius = distance(cx, cy, x, y);
    }
    else{
        //create rectangles and lines
        objects[n-1].tool.endpoints.pt2.x = x;
        objects[n-1].tool.endpoints.pt2.y = y;
    }
}
//----------------------------------

//draw
void Sketch::draw(){
    //extrapulate information
    for(int i = 0; i < n; i++){
        int c;
        int t;
        c = objects[i].colorType;
        glColor3f(colormenu[c][R],colormenu[c][G],colormenu[c][B]);
        t = objects[i].toolType;

        switch(t){
            case 0:
                //unfilled rectangle
                drawRectangle(GL_LINE_LOOP, objects[i].tool.endpoints.pt1.x, objects[i].tool.endpoints.pt1.y, objects[i].tool.endpoints.pt2.x, objects[i].tool.endpoints.pt2.y);
            break;

            case 1:
                //filled rectangle
                drawRectangle(GL_POLYGON, objects[i].tool.endpoints.pt1.x, objects[i].tool.endpoints.pt1.y, objects[i].tool.endpoints.pt2.x, objects[i].tool.endpoints.pt2.y);
            break;

            case 2:
                //unfilled circle
                drawCircle(GL_LINE_LOOP, objects[i].tool.circle.center.x, objects[i].tool.circle.center.y, objects[i].tool.circle.radius);
            break;

            case 3:
                //filled circle
                drawCircle(GL_POLYGON, objects[i].tool.circle.center.x, objects[i].tool.circle.center.y, objects[i].tool.circle.radius);
            break;

            case 4:
            case 5:
                drawLine(objects[i].tool.endpoints.pt1.x, objects[i].tool.endpoints.pt1.y, objects[i].tool.endpoints.pt2.x, objects[i].tool.endpoints.pt2.y);
                break;
        }
    }
}

//----------------------------------
//Draw rectangle
void Sketch::drawRectangle(GLint drawType, int x1, int y1, int x2, int y2){
    glBegin(drawType);

    glVertex2i(x1,y1);  //4 of these
    glVertex2i(x2,y1);
    glVertex2i(x2,y2);
    glVertex2i(x1,y2);

    glEnd();
}
//----------------------------------
//Draw line
void Sketch::drawLine(int x1, int y1, int x2, int y2){
    glBegin(GL_LINES);

    glVertex2i(x1, y1);
    glVertex2i(x2,y2);

    glEnd();
}
//----------------------------------
//Draw Circle
void Sketch::drawCircle(GLint drawType, int cx, int cy, int r){
    int k;
    float angle, ainc;

    ainc = 2 * PI/72;

    glBegin(drawType);
    for(k = 0; k < 72; k++){
        angle = k * ainc;
        glVertex2f(cx + r*cos(angle), cy + r*sin(angle));
    }
    glEnd();
}
//----------------------------------

void Sketch::clear(){
    n = 0;
}

//----------------------------------
bool Sketch::load(){
    string filename;
    ifstream inputFile;
    int i;
    
    cout << "Enter a file to read: ";
    cin >> filename;
    
    inputFile.open(filename.c_str());
    if(inputFile.is_open()){
        inputFile >> n;
        for(i = 0; i < n; i++){
            inputFile >> objects[i].colorType >> objects[i].toolType;
            
            if(objects[i].toolType == 2 || objects[i].toolType == 3){
                inputFile >> objects[i].tool.circle.center.x;
                inputFile >> objects[i].tool.circle.center.y;
                inputFile >> objects[i].tool.circle.radius;
            }
            else{
                inputFile >> objects[i].tool.endpoints.pt1.x;
                inputFile >> objects[i].tool.endpoints.pt1.y;
                inputFile >> objects[i].tool.endpoints.pt2.x;
                inputFile >> objects[i].tool.endpoints.pt2.y;
            }
        }
        inputFile.close();
        return true;
    }
    else{
        return false;
    }
}

//----------------------------------
void Sketch::save(){
    string filename;
    ofstream outputFile;
    int i;
    
    cout << "Enter a file to save: ";
    cin >> filename;
    
    outputFile.open(filename.c_str());
    if(outputFile.is_open()){
        outputFile << n << endl;
        for(i = 0; i < n; i++){
            outputFile << objects[i].colorType << " " << objects[i].toolType << " ";
            
            if(objects[i].toolType == 2 || objects[i].toolType == 3){
                outputFile << objects[i].tool.circle.center.x << " ";
                outputFile << objects[i].tool.circle.center.y << " ";
                outputFile << objects[i].tool.circle.radius << endl;
            }
            else{
                outputFile << objects[i].tool.endpoints.pt1.x << " ";
                outputFile << objects[i].tool.endpoints.pt1.y << " ";
                outputFile << objects[i].tool.endpoints.pt2.x << " ";
                outputFile << objects[i].tool.endpoints.pt2.y << endl;
            }
        }
        outputFile.close();
    }
}

//----------------------------------
void Sketch::quit(){
    exit(0);
}
