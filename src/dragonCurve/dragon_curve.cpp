//src/dragonCurve/dragon_curve.cpp
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <cmath>

int iterations = 13;  
float scale = 1.0f;   
float angleForRotation = 0.0f;

class Point {
    public:
        float x, y;
        Point(float xCoordinate, float yCoordinate) : x(xCoordinate), y(yCoordinate) {}
        ~Point(){};
};


std::vector<Point> dragonDataPoints;


void createColouredDragonCurve(int iterations){
    dragonDataPoints.clear();
    

    dragonDataPoints.push_back(Point(0.0f, 0.0f));
    dragonDataPoints.push_back(Point(1.0f, 0.0f));
    
    for(int i = 0; i < iterations; i++){

        std::vector<Point> newPoints;
        
        newPoints.push_back(dragonDataPoints[0]);

        int size = dragonDataPoints.size();

        for(size_t j = 1; j <size ; j++) {

            float x1 = dragonDataPoints[j-1].x;

            float y1 = dragonDataPoints[j-1].y;
            float x2 = dragonDataPoints[j].x;
            float y2 = dragonDataPoints[j].y;
            
            float middleX = (x1 + x2) * 0.5f;

            float middleY = (y1 + y2) * 0.5f;
            
            float changeX = x2 - x1;
            float changeY = y2 - y1;
            
            if(j % 2 == 1) {

                float x = middleX + changeY * 0.5f;
                float y = middleY - changeX * 0.5f;
                
                newPoints.push_back(Point(   x, y ));

            } else{

                float x = middleX - changeY * 0.5f;
                float y = middleY + changeX * 0.5f;
                newPoints.push_back(Point(
                    x,
                    y
                 ));
            }
            
            newPoints.push_back(dragonDataPoints[j]);
        }
        
        dragonDataPoints = newPoints;
    }
}

void init() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    
    createColouredDragonCurve(iterations);
}

void displayDragonData(const float x, const float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (auto character : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, character);
    }
}
void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(angleForRotation, 0.0f, 0.0f, 1.0f);
    glScalef(scale, scale, 1.0f);
    
   
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 1.0f, 0.0f); 
    
    unsigned int numberOfPoints = dragonDataPoints.size();

    for (size_t i = 0; i < numberOfPoints; i++) {
        float gradientValue = (float)i / float(numberOfPoints - 1);

        float red = 1.0f - gradientValue;
        float blue = gradientValue;

        glColor3f(red, 0.0f, blue);

        glVertex2f(dragonDataPoints[i].x, dragonDataPoints[i].y);
    }
    
    
    glEnd();
    glColor3f(0.0f, 1.0f, 0.0f); 

    std::string info = "Press R to rotate";
    displayDragonData(-1, 1, info);
    displayDragonData(-1, 0.95, "Press - and + to change Iterations");
    displayDragonData(-1, 0.90, "Press S to zoom");

    glutSwapBuffers();
}

void reshape(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aRatio = (float)w / (float)h;

    if(w >= h) {
        float left = -2.0 * aRatio;
        float right = 2.0 * aRatio;
        float bottom = -2.0;
        float top = 2.0;

        gluOrtho2D(left, right, bottom, top);
    } else{

        float left = -2.0;
        float right = 2.0;
        float bottom = -2.0 / aRatio;
        float top = 2.0 / aRatio;

        gluOrtho2D(left, bottom, bottom, top);
    }
}

void keyboardEventListeners(unsigned char k, int x, int y) {

    switch(k) {
        case '+':  

            if(iterations < 15){
                iterations++;

                createColouredDragonCurve(iterations);

                glutPostRedisplay();
            }
            break;
        case '-':  
            if(iterations > 1) {

                iterations--;
                createColouredDragonCurve(iterations);

                glutPostRedisplay();
            }
            break;
        case 'r': 
            angleForRotation  += 5.0f;
            glutPostRedisplay();
            break;
            
        case 'R':  
            angleForRotation -= 5.0f;
            glutPostRedisplay();
            break;

        case 's':  
            scale *= 1.1f;
            glutPostRedisplay();

            break;

        case 'S':  
            scale *= 0.9f;
            glutPostRedisplay();
            break;

        case 27:   
            exit(0);
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(800, 800);
    glutCreateWindow("Dragon Curve");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardEventListeners);
    
    glutMainLoop();
    return 0;
}