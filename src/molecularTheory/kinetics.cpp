#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>

const int PARTICLES = 99;
const float MAX_VELOCITY = 5.0f;
const float MIN_VELOCITY = 0.1f;
const float RADIUS = 0.02;
const float ENERGY_CHANGE = 0.2f;

class Particle {
    public:
        float red, green, blue;
        float intensity;
        float x, y, z;
        float velocityX, velocityY, velocityZ;
        float radius;
        float energy;
    
    Particle() {}

    Particle(const Particle& p){
        red = p.red;
        green = p.green;
        blue = p.blue;
        intensity = p.intensity;
        x = p.x;
        y = p.y;
        z = p.z;
        velocityX = p.velocityX;
        velocityY = p.velocityY;
        velocityZ = p.velocityZ;
        radius = p.radius;
        energy = p.energy;
    }
};

std::vector<Particle> particles;
float totalEnergy = 10.0f;
std::random_device device;
std::mt19937 engine(device());
std::uniform_real_distribution<float> distribution(-1, 1);

void getTHermalColour(float velocity, float &red, float& green, float& blue, float& intensity ){

    if ((MAX_VELOCITY - MIN_VELOCITY) == 0) return;
    float normalizedSpeed = (velocity - MIN_VELOCITY) / (MAX_VELOCITY - MIN_VELOCITY);

    if (normalizedSpeed > 1.0f) normalizedSpeed = 1.0f;
    if (normalizedSpeed < 0.0f) normalizedSpeed = 0.0f;

    float baseIntensity = 0.5f;
    intensity = baseIntensity + (0.5f * normalizedSpeed);

    if (normalizedSpeed < 0.5) {

        red = normalizedSpeed * 2.0f;
        green = 0.0f;
        blue = 1.0f;
        // std::cout<<"cold;"<<std::endl;
    } else {
        // std::cout<<"hot"<<std::endl;
        red = 1.0f;
        green = 0.0f;
        blue = 0.0f;
    }

    red = red * intensity;
    green = green * intensity;
    blue = blue * intensity;
    
}

void initParticles() {

    particles.clear();

    for (int i = 0; i <  PARTICLES; i++) {
        Particle p;

        p.x = distribution(engine);
        p.y = distribution(engine);
        p.velocityX = distribution(engine) * 0.5f;
        p.velocityY = distribution(engine) * 0.5f;

        p.radius = RADIUS;
        p.energy = totalEnergy / PARTICLES;

        p.red = 0.0f;
        p.green = 0.0f;
        p.blue = 0.5f;
        p.intensity = 0.5f;

        particles.push_back(p);
    }
}

void limitVelocity(Particle &p) {

    float resultantVelocity = sqrt(p.velocityX * p.velocityX + p.velocityY * p.velocityY);

    if (resultantVelocity > MAX_VELOCITY) {
        p.velocityX = (p.velocityX / resultantVelocity) * MAX_VELOCITY;
        p.velocityY = (p.velocityY / resultantVelocity) * MAX_VELOCITY;
    } else if (resultantVelocity < MIN_VELOCITY) {
        p.velocityX = (p.velocityX / resultantVelocity) * MIN_VELOCITY;
        p.velocityY = (p.velocityY / resultantVelocity) * MIN_VELOCITY;
    }
}

float ecludianDistance(const Particle &p1, const Particle &p2) {
    float deltaX = pow((p1.x - p2.x), 2);
    float deltaY = pow((p1.y - p2.y), 2);
    
    return sqrt(deltaX + deltaY);
}

bool checkCollisions(const Particle &p1, const Particle &p2) {
    float distance = ecludianDistance(p1, p2);

    return distance < (p1.radius + p2.radius);
}

void resolveCollisionForces(Particle &p1, Particle &p2) {

    float distance = ecludianDistance(p1, p2); 

    if (distance == 0) return;

    float normalX = (p2.x - p1.x) / distance;
    float normalY = (p2.y - p1.y) / distance;

    float relativeVelocityX = p2.velocityX - p1.velocityX;
    float relativeVelocityY = p2.velocityY - p1.velocityY;

    float normalVelocity = relativeVelocityX * normalX + relativeVelocityY * normalY;

    if (normalVelocity > 0) {
        return;
    }

    float elasticity = 0.9f;

    // impulse=−(1+e)⋅v 
    float impactVelocity = -(1.0f + elasticity) * normalVelocity;
    impactVelocity /= 2.0f;

    p1.velocityX = p1.velocityX - (impactVelocity * normalX);
    p1.velocityY = p1.velocityY - (impactVelocity * normalY);
    p2.velocityX = p2.velocityX + (impactVelocity * normalX);
    p2.velocityY = p2.velocityY + (impactVelocity * normalY);

}

void updateState() {
    //new position=old position+velocity×Δt
    float deltaT = 0.01f;

    for (Particle &p : particles){

        p.x = p.x + (p.velocityX * deltaT);
        p.y = p.y + (p.velocityY * deltaT);

        float rightWall = p.x + p.radius;
        float leftWall = p.x - p.radius;
        float topWall = p.y + p.radius;
        float bottomWall = p.y - p.radius;

        if (rightWall > 1.0f) {
            p.x = 1.0f - p.radius;
            p.velocityX *= -1.0f;
        }
        if (leftWall < -1.0f) {
            p.x = -1.0f + p.radius;
            p.velocityX *= -1.0f;
        }
        if (topWall > 1.0f) {
            p.y = 1.0f - p.radius;
            p.velocityY *= -1.0f;
        }
        if (bottomWall < -1.0f) {
            p.y = -1.0f + p.radius;
            p.velocityY *= -1.0f;
        }


        float randomForcesX = distribution(engine) * 0.1f;
        float randomForcesY = distribution(engine) * 0.1f;

        p.velocityX = p.velocityX + randomForcesX;
        p.velocityY = p.velocityY + randomForcesY;

        limitVelocity(p);  
        p.energy = 0.5f * (p.velocityX * p.velocityX + p.velocityY * p.velocityY);

        float resultantVelecity = sqrt((p.velocityX * p.velocityX) + (p.velocityY * p.velocityY));
        getTHermalColour(resultantVelecity, p.red, p.green, p.blue, p.intensity);
    }

    for (int i = 0; i < particles.size(); i++) {
        for (int j = i + 1; j < particles.size(); j++){
            if (checkCollisions(particles[i], particles[j])){
                resolveCollisionForces(particles[i], particles[j]);
            }
        }
    }
}

void timer(int t){
    updateState();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void reshape(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    
    if (w <= h) {
        glOrtho(-1.0, 1.0, -1.0/aspect, 1.0/aspect, -1.0, 1.0);
    } else {
        glOrtho(-1.0*aspect, 1.0*aspect, -1.0, 1.0, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
}

void writeText(const float x, const float y, const std::string& text) {
    glRasterPos2f(x, y);

    for (auto character : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, character);
    }
}

void drawEnergyBar() {

    float barWidth = 0.3f;
    float barHeight = 0.05f;
    float startXposition = -0.9f;
    float startYposition = -0.9f;
    float barThickness = startYposition + barHeight;

    glBegin(GL_QUAD_STRIP);
    
    glColor3f(0.0f, 0.0f, 1.0f);  
    glVertex2f(startXposition, startYposition);
    glVertex2f(startXposition, barThickness);
    
    float orangeX= startXposition + barWidth/2;
    glColor3f(1.0f, 0.0f, 1.0f);  
    glVertex2f(orangeX, startYposition);
    glVertex2f(orangeX, barThickness);
    
    float redX = startXposition + barWidth;
    glColor3f(1.0f, 0.0f, 0.0f);  
    glVertex2f( redX, startYposition);
    glVertex2f(redX, barThickness);
    
    glEnd();
    
    glColor3f(1.0f, 1.0f, 1.0f);  
    writeText(startXposition, startYposition - 0.05f, "cold");
    writeText(startXposition + barWidth - 0.1f, startYposition - 0.05f, "hot");
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    for (const Particle &p : particles) {
        glColor3f(p.red, p.green, p.blue );
        glPushMatrix();
        glTranslatef(p.x, p.y, 0.0f);
        glutSolidSphere(p.radius, 50, 50);
        glPopMatrix();
    }

    drawEnergyBar();

    float totalEnergy = 0.0f;
    float maxVelocity = 0.0f;

    for (const Particle &p : particles) {
        totalEnergy += p.energy;
        float velocityMagnitude = sqrt((p.velocityX * p.velocityX) + (p.velocityY * p.velocityY));

        if (velocityMagnitude > maxVelocity) {
            maxVelocity = velocityMagnitude;
        }
    }

    totalEnergy = totalEnergy/ particles.size();

    glColor3f(1.0f, 1.0f, 1.0f);
    std::string energyInfo = "Average Energy: " + std::to_string(totalEnergy);
    std::string velocityInfo = "Max Velocity: " + std::to_string(maxVelocity) + " / " + std::to_string(MAX_VELOCITY);

    writeText(-1.0, 0.95, energyInfo);
    writeText(-1.0, 0.9, velocityInfo);
    writeText(-1.0f, 0.8f, "Press w or + to increase energy");
    writeText(-1.0f, 0.75f, "Press arrow s or - to decrease energy");
    writeText(-1.0f, 0.70f, "Press esc to EXit");

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    
    for (Particle& p : particles) {
        switch (key) {
            case '+':
            case 'W':
            case 'w': {
                float currentParticleV = sqrt(p.velocityX * p.velocityX + p.velocityY * p.velocityY);

                if (currentParticleV < MAX_VELOCITY) {
                    
                    p.velocityX = p.velocityX * (1.0f + ENERGY_CHANGE);
                    p.velocityY = p.velocityY * (1.0f + ENERGY_CHANGE);
                }
                break;
            }
            case '-':
            case 'S':
            case 's': {
                float currentParticleVe = sqrt(p.velocityX * p.velocityX + p.velocityY * p.velocityY);

                if (currentParticleVe > MIN_VELOCITY) {
                    p.velocityX = p.velocityX * (1.0f - ENERGY_CHANGE);
                    p.velocityY = p.velocityY * (1.0f - ENERGY_CHANGE);
                }
                break;
            }
    
            case 27:
                std::cout<<"You have closed the simulation"<<std::endl;
                exit(0);
                break;
            default:
            break;
           
        }
    }
}


int main(int argc, char **argv)
{
    try
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(800, 800);

        glutCreateWindow("Welcome to the brownian motion");

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutTimerFunc(0, timer, 0);
        
        glutKeyboardFunc(keyboard); 
        // glutSpecialFunc(specialKeys);
        initParticles();
        glutMainLoop();  
    }
    catch(const std::exception& e) {
        std::cout << e.what() << std::endl;;
    }

    return 0;
}