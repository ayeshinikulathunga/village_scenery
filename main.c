#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Set background color to white
    glMatrixMode(GL_PROJECTION);           // Switch to projection matrix
    glLoadIdentity();                      // Reset the projection matrix
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);      // Set up an orthographic projection
}

float sunX = 0.9f;  // Initialize sunX to 0.5f (center of the screen)
bool moveSun = false;  // Initialize moveSun to false
float boatX = 0.0f; // Initial boat position
float paddleAngle = 0.0f; // Initial paddle rotation angle
bool moveBoat = false;
bool movePaddle = false;
bool moveHorse = false;
bool moveTail = false;
float horseX = 0.0f; // Initial horse position
float tailRotation = 0.0f; // Initial tail rotation
float fishScaleFactor = 1.0f;
float flowerScaleFactor = 1.0f;
float rightPlantsScaleFactor = 1.0;

void drawSun() {
    int numSegments = 100;
    float radius = 0.08f;
    float y = 0.9f;  // Assuming the sun is at y = 0.0f

    glColor3f(1.0f, 0.8f, 0.0f);  // Yellow color for the sun
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(sunX, y);  // Center of the sun
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * 2.0f * 3.14159f / numSegments;  // 360 degrees in radians
        glVertex2f(sunX + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}


void timer(int value) {
    if (moveSun) {
        sunX -= 0.01f;  // Move the sun 0.01f units to the left
        if (sunX < -1.0f) {  // If the sun moves off the left edge of the screen
            sunX = 1.0f;  // Wrap the sun around to the right edge
        }
    }
    glutPostRedisplay();  // Request a redraw
    if (moveSun) {
        glutTimerFunc(60, timer, 0);  // Call the timer function again after 60 milliseconds
    }
}

void timer1(int value) {
    if (moveBoat) {
        boatX += 0.1f; // Move boat to the right
        if (boatX > 1.0f) {
            boatX = -1.0f;
        }
    }
    glutPostRedisplay();
    if (moveBoat) {
        glutTimerFunc(100, timer1, 0);
    }
}

void timer2(int value) {
    if (movePaddle) {
        paddleAngle -= 1.0f; // Move paddle up (appears to move backward due to perspective)
        if (paddleAngle < -20.0f) {
            paddleAngle = 0.0f; // Limit paddle movement
        }
    }
    glutPostRedisplay();
    if (movePaddle) {
        glutTimerFunc(100, timer2, 0);
    }
}

void timer3(int value) {
    if (moveHorse) {
        horseX -= 0.1f; // Move horse to the left
        if (horseX < -1.0f) {
            horseX = 1.0f; // Wrap around to the right side of the screen
        }
    }
    glutPostRedisplay();
    if (moveHorse) {
        glutTimerFunc(50, timer3, 0);
    }
}

void timer4(int value) {
    if (moveTail) {
        tailRotation += 10.0f; // Rotate tail clockwise
        if (tailRotation > 360.0f) {
            tailRotation = 0.0f;
        }
        glutPostRedisplay();
        if (moveTail) {
            glutTimerFunc(100, timer4, 0);
        }
    }
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ' ':
        moveSun = !moveSun;
        if (moveSun) {
            glutTimerFunc(0, timer, 0);  // Start the timer
        }
        break;
    case 'b':
    case 'B':
        moveBoat = !moveBoat;
        if (moveBoat) {
            glutTimerFunc(0, timer1, 0);
        }
        break;
    case 'w':
    case 'W':
        movePaddle = !movePaddle;
        if (movePaddle) {
            glutTimerFunc(0, timer2, 0);
        }
        break;
    case 'f':
    case 'F':
        moveHorse = !moveHorse;
        if (moveHorse) {
            glutTimerFunc(0, timer3, 0);
        }
        break;
    case 'r':
    case 'R':
        moveTail = !moveTail;
        if (moveTail) {
            glutTimerFunc(0, timer4, 0);
        }
        break;
    case 'u':
    case 'U':
        fishScaleFactor *= 1.5f;
        flowerScaleFactor += 1.5f;
        glutPostRedisplay();
        break;
    case 'S':
    case 's':
        rightPlantsScaleFactor /= 2;
        glutPostRedisplay();
        break;
    }
}

void drawHouseOne(float x, float y) {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.1f, 0.4f); //dark purple - wall
    glVertex2f(x - 0.15f, y);         // Bottom-left
    glVertex2f(x + 0.14f, y);         // Bottom-right
    glVertex2f(x + 0.14f, y + 0.35f);  // Top-right
    glVertex2f(x - 0.15f, y + 0.35f);  // Top-left
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); //red - roof
    glVertex2f(x - 0.18f, y + 0.3f); // Bottom-left
    glVertex2f(x + 0.17f, y + 0.3f); // Bottom-right
    glVertex2f(x + 0.13f, y + 0.45f);  // Top-right
    glVertex2f(x - 0.14f, y + 0.45f);  // Top-left
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.6f, 0.0f); //light orange - door
    glVertex2f(x - 0.06f, y);         // Bottom-left
    glVertex2f(x + 0.05f, y);         // Bottom-right
    glVertex2f(x + 0.05f, y + 0.20f); // Top-right
    glVertex2f(x - 0.06f, y + 0.20f); // Top-left
    glEnd();
    glPopMatrix();
}

void drawHouseTwo(float x, float y) {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.3f, 0.5f); //dark pink - wall
    glVertex2f(x - 0.15f, y);         // Bottom-left
    glVertex2f(x + 0.14f, y);         // Bottom-right
    glVertex2f(x + 0.14f, y + 0.35f);  // Top-right
    glVertex2f(x - 0.15f, y + 0.35f);  // Top-left
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); //red - roof
    glVertex2f(x - 0.18f, y + 0.3f); // Bottom-left
    glVertex2f(x + 0.17f, y + 0.3f); // Bottom-right
    glVertex2f(x + 0.13f, y + 0.45f);  // Top-right
    glVertex2f(x - 0.14f, y + 0.45f);  // Top-left
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.6f, 0.0f); //light orange - door
    glVertex2f(x - 0.06f, y);         // Bottom-left
    glVertex2f(x + 0.05f, y);         // Bottom-right
    glVertex2f(x + 0.05f, y + 0.20f); // Top-right
    glVertex2f(x - 0.06f, y + 0.20f); // Top-left
    glEnd();
    glPopMatrix();
}

void drawfruit() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.56, 0.09, 0.0);
    glScalef(rightPlantsScaleFactor, rightPlantsScaleFactor, 0.0);
    glTranslatef(-0.56, -0.09, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f); // red color
    float radius2 = 0.019f;
    int numSegments1 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments1; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments1;
        float x = radius2 * cosf(angle);
        float y = radius2 * sinf(angle);
        glVertex2f(x + 0.48f, y + 0.34f);
    }
    glEnd();

    float radius3 = 0.019f;
    int numSegments2 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments2; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments2;
        float x = radius3 * cosf(angle);
        float y = radius3 * sinf(angle);
        glVertex2f(x + 0.64f, y + 0.34f);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.01, 0.15, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f); // red color
    float radius4 = 0.019f;
    int numSegments3 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments3; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments3;
        float x = radius4 * cosf(angle);
        float y = radius4 * sinf(angle);
        glVertex2f(x - 0.01f, y + 0.19f);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-0.14, 0.15, 0.0);
    glColor3f(1.0f, 0.0f, 0.0f); // red color
    float radius5 = 0.019f;
    int numSegments4 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments4; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments4;
        float x = radius5 * cosf(angle);
        float y = radius5 * sinf(angle);
        glVertex2f(x - 0.01f, y + 0.19f);
    }
    glEnd();
    glPopMatrix();
}

void drawStem(float x, float y) { //tree trunks
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.25f, 0.0f);
    glVertex2f(x, 0.35f);
    glVertex2f(x, 0.4f - y);
    glEnd();
}

void drawTree(float x, float y) {
    // Brown color
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f); //brown color
    glVertex2f(x - 0.02f, y);        // Bottom-left
    glVertex2f(x + 0.02f, y);        // Bottom-right
    glVertex2f(x + 0.02f, y + 0.3f); // Top-right
    glVertex2f(x - 0.02f, y + 0.3f); // Top-left
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.5f, 0.0f); // Green color
    glVertex2f(x - 0.18f, y + 0.3f); // Bottom-left
    glVertex2f(x + 0.18f, y + 0.3f); // Bottom-right
    glVertex2f(x, y + 0.6f);         // Top-center
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.5f, 0.0f); // Green color
    glVertex2f(x - 0.15f, y + 0.45f); // Bottom-left
    glVertex2f(x + 0.15f, y + 0.45f); // Bottom-right
    glVertex2f(x, y + 0.7f);         // Top-center
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.5f, 0.0f); // Green color
    glVertex2f(x - 0.10f, y + 0.60f); // Bottom-left
    glVertex2f(x + 0.10f, y + 0.60f); // Bottom-right
    glVertex2f(x, y + 0.85f);         // Top-center
    glEnd();
}

void drawBoatManAndBoat() {
    //boat
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(boatX - 0.5f, -0.7f);
    glVertex2f(boatX + 0.5f, -0.7f);
    glVertex2f(boatX + 0.3f, -0.85f);
    glVertex2f(boatX - 0.3f, -0.85f);
    glEnd();

    glPushMatrix();  //lower part
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(boatX - 0.35, -0.7);
    glVertex2f(boatX - 0.20, -0.7);
    glVertex2f(boatX - 0.25, -0.60);
    glVertex2f(boatX - 0.35, -0.60);
    glEnd();
    glPopMatrix();

    glPushMatrix();  //upper part
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(boatX - 0.35, -0.7);
    glVertex2f(boatX - 0.25, -0.50);
    glVertex2f(boatX - 0.35, -0.50);
    glEnd();
    glPopMatrix();

    glPushMatrix();  //face
    glLoadIdentity();
    glColor3f(1.0, 0.48, 0.42);
    glBegin(GL_POLYGON);
    glVertex2f(boatX - 0.34, -0.50);
    glVertex2f(boatX - 0.28, -0.50);
    glVertex2f(boatX - 0.28, -0.40);
    glVertex2f(boatX - 0.34, -0.40);
    glEnd();
    glPopMatrix();

    glPushMatrix();  //nose
    glLoadIdentity();
    glColor3f(1.0, 0.48, 0.42);
    glBegin(GL_TRIANGLES);
    glVertex2f(boatX - 0.28, -0.45);
    glVertex2f(boatX - 0.26, -0.45);
    glVertex2f(boatX - 0.28, -0.43);
    glEnd();
    glPopMatrix();

    glPushMatrix();  //hair
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(boatX - 0.34, -0.40);
    glVertex2f(boatX - 0.28, -0.40);
    glVertex2f(boatX - 0.27, -0.36);
    glVertex2f(boatX - 0.33, -0.38);
    glEnd();
    glPopMatrix();
}

void drawBoatPaddle() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(boatX - 0.25, -0.6, 0.0);
    glRotatef(paddleAngle, 0.0, 0.0, 1.0);
    glTranslatef(0.25 - boatX, 0.6, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(boatX - 0.40f, -0.90f);
    glVertex2f(boatX - 0.32f, -0.87f);
    glVertex2f(boatX - 0.25f, -0.60);
    glVertex2f(boatX - 0.26f, -0.60f);
    glEnd();
    glPopMatrix();

}

void drawRightSideBottomFish() {
    glPushMatrix();
    glLoadIdentity();
    // Increase the scale factor for the fish
    glTranslatef(0.6, -0.8, 0.0);
    glScalef(fishScaleFactor, fishScaleFactor, 1.0f);
    glTranslatef(-0.6, 0.8, 0.0);
    //right side bottom fish
   //body
    glBegin(GL_QUADS);
    glColor3f(0.35f, 0.05f, 0.55f);
    glVertex2f(0.5f, -0.8f);
    glVertex2f(0.6f, -0.85f);
    glVertex2f(0.7f, -0.8f);
    glVertex2f(0.6f, -0.75f);
    glEnd();

    glBegin(GL_TRIANGLES); //tail
    glColor3f(0.9f, 0.5f, 0.7f);
    glVertex2f(0.7f, -0.8f);
    glVertex2f(0.75f, -0.85f);
    glVertex2f(0.75f, -0.75f);
    glEnd();

    glBegin(GL_TRIANGLES); //upper fin
    glColor3f(0.9f, 0.5f, 0.7f);
    glVertex2f(0.6f, -0.75f);
    glVertex2f(0.58f, -0.70f);
    glVertex2f(0.63f, -0.70f);
    glEnd();

    glBegin(GL_TRIANGLES); //lower fin
    glColor3f(0.9f, 0.5f, 0.7f);
    glVertex2f(0.58f, -0.90f);
    glVertex2f(0.63f, -0.90f);
    glVertex2f(0.6f, -0.85f);
    glEnd();
    glPopMatrix();
}

void drawRightSideTopFish() {
    // right top fish
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.2, 0.18, 0.0);
    glTranslatef(0.6, -0.8, 0.0);
    glScalef(fishScaleFactor, fishScaleFactor, 0.0f);
    glTranslatef(-0.6, 0.8, 0.0);
    glBegin(GL_QUADS);
    glColor3f(0.35f, 0.05f, 0.55f);
    glVertex2f(0.5f, -0.8f);
    glVertex2f(0.6f, -0.85f);
    glVertex2f(0.7f, -0.8f);
    glVertex2f(0.6f, -0.75f);
    glEnd();

    glBegin(GL_TRIANGLES); //tail
    glColor3f(0.9f, 0.5f, 0.7f);
    glVertex2f(0.7f, -0.8f);
    glVertex2f(0.75f, -0.85f);
    glVertex2f(0.75f, -0.75f);
    glEnd();

    glBegin(GL_TRIANGLES); //upper fin
    glColor3f(0.9f, 0.5f, 0.7f);
    glVertex2f(0.6f, -0.75f);
    glVertex2f(0.58f, -0.70f);
    glVertex2f(0.63f, -0.70f);
    glEnd();

    glBegin(GL_TRIANGLES); //lower fin
    glColor3f(0.9f, 0.5f, 0.7f);
    glVertex2f(0.58f, -0.90f);
    glVertex2f(0.63f, -0.90f);
    glVertex2f(0.6f, -0.85f);
    glEnd();
    glPopMatrix();
}

void drawLeftFlowers() {
    glPushMatrix();      //upper pot
    glLoadIdentity();
    glTranslatef(-0.70, -0.30, 0.0);
    glScalef(flowerScaleFactor, flowerScaleFactor, 0.0f);
    glTranslatef(0.70, 0.30, 0.0);
    glColor3f(1.0f, 0.5f, 0.0f); // light brown color
    glBegin(GL_QUADS);
    glVertex2f(-0.64, -0.30);
    glVertex2f(-0.61, -0.30);
    glVertex2f(-0.59, -0.25);
    glVertex2f(-0.66, -0.25);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f); // light brown color
    glBegin(GL_QUADS);
    glVertex2f(-0.78, -0.40);
    glVertex2f(-0.75, -0.40);
    glVertex2f(-0.73, -0.35);
    glVertex2f(-0.80, -0.35);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.63, -0.25);
    glVertex2f(-0.62, -0.25);
    glVertex2f(-0.62, -0.17);
    glVertex2f(-0.63, -0.17);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-0.66, -0.21);
    glVertex2f(-0.62, -0.23);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-0.58, -0.18);
    glVertex2f(-0.62, -0.20);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.77, -0.35);
    glVertex2f(-0.76, -0.35);
    glVertex2f(-0.76, -0.27);
    glVertex2f(-0.77, -0.27);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-0.83, -0.30);
    glVertex2f(-0.77, -0.32);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-0.73, -0.28);
    glVertex2f(-0.77, -0.30);
    glEnd();

    glColor3f(0.96, 0.78, 0.98); //rose pink
    float radius2 = 0.022f;
    int numSegments1 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments1; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments1;
        float x = radius2 * cosf(angle);
        float y = radius2 * sinf(angle);
        glVertex2f(x - 0.625f, y - 0.16f);
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); //red
    float radius3 = 0.022f;
    int numSegments2 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments2; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments2;
        float x = radius3 * cosf(angle);
        float y = radius3 * sinf(angle);
        glVertex2f(x - 0.68f, y - 0.21f);
    }
    glEnd();

    glColor3f(0.5f, 0.0f, 1.0f); //purple
    float radius4 = 0.022f;
    int numSegments3 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments3; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments3;
        float x = radius4 * cosf(angle);
        float y = radius4 * sinf(angle);
        glVertex2f(x - 0.57f, y - 0.18f);
    }
    glEnd();

    glColor3f(0.96, 0.78, 0.98); //rose pink
    float radius5 = 0.022f;
    int numSegments4 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments4; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments4;
        float x = radius5 * cosf(angle);
        float y = radius5 * sinf(angle);
        glVertex2f(x - 0.765f, y - 0.26f);
    }
    glEnd();

    glColor3f(1.0, 0.0, 0.0); //red
    float radius6 = 0.022f;
    int numSegments5 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments5; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments5;
        float x = radius6 * cosf(angle);
        float y = radius6 * sinf(angle);
        glVertex2f(x - 0.82f, y - 0.31f);
    }
    glEnd();

    glColor3f(0.5, 0.0, 1.0); //purple
    float radius7 = 0.022f;
    int numSegments6 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments6; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments6;
        float x = radius7 * cosf(angle);
        float y = radius7 * sinf(angle);
        glVertex2f(x - 0.71f, y - 0.28f);
    }
    glEnd();
    glPopMatrix();

}

void drawRightFlowers() {
    float x = 1.2;
    float y = 0.0;

    glPushMatrix();      //upper pot
    glLoadIdentity();
    glTranslatef(x, y, 0.0);
    glTranslatef(-0.70, -0.30, 0.0);
    glScalef(rightPlantsScaleFactor, rightPlantsScaleFactor, 0.0f);
    glTranslatef(0.70, 0.30, 0.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.63, -0.25);
    glVertex2f(-0.62, -0.25);
    glVertex2f(-0.62, -0.17);
    glVertex2f(-0.63, -0.17);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-0.66, -0.21);
    glVertex2f(-0.62, -0.23);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-0.58, -0.18);
    glVertex2f(-0.62, -0.20);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.77, -0.35);
    glVertex2f(-0.76, -0.35);
    glVertex2f(-0.76, -0.27);
    glVertex2f(-0.77, -0.27);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-0.83, -0.30);
    glVertex2f(-0.77, -0.32);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-0.73, -0.28);
    glVertex2f(-0.77, -0.30);
    glEnd();

    glColor3f(0.96, 0.78, 0.98); //rose pink
    float radius2 = 0.022f;
    int numSegments1 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments1; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments1;
        float x = radius2 * cosf(angle);
        float y = radius2 * sinf(angle);
        glVertex2f(x - 0.625f, y - 0.16f);
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); //red
    float radius3 = 0.022f;
    int numSegments2 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments2; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments2;
        float x = radius3 * cosf(angle);
        float y = radius3 * sinf(angle);
        glVertex2f(x - 0.68f, y - 0.21f);
    }
    glEnd();

    glColor3f(0.5f, 0.0f, 1.0f); //purple
    float radius4 = 0.022f;
    int numSegments3 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments3; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments3;
        float x = radius4 * cosf(angle);
        float y = radius4 * sinf(angle);
        glVertex2f(x - 0.57f, y - 0.18f);
    }
    glEnd();

    glColor3f(0.96, 0.78, 0.98); //rose pink
    float radius5 = 0.022f;
    int numSegments4 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments4; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments4;
        float x = radius5 * cosf(angle);
        float y = radius5 * sinf(angle);
        glVertex2f(x - 0.765f, y - 0.26f);
    }
    glEnd();

    glColor3f(1.0, 0.0, 0.0); //red
    float radius6 = 0.022f;
    int numSegments5 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments5; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments5;
        float x = radius6 * cosf(angle);
        float y = radius6 * sinf(angle);
        glVertex2f(x - 0.82f, y - 0.31f);
    }
    glEnd();

    glColor3f(0.5, 0.0, 1.0); //purple
    float radius7 = 0.022f;
    int numSegments6 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments6; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments6;
        float x = radius7 * cosf(angle);
        float y = radius7 * sinf(angle);
        glVertex2f(x - 0.71f, y - 0.28f);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();
}

void drawRightFlowerPots() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.435, -0.3, 0.0);
    glTranslatef(0.0,0.06,0.0);
    glScalef(rightPlantsScaleFactor, rightPlantsScaleFactor, 1.0f);
    glTranslatef(0.0,-0.06,0.0);
    glColor3f(1.0, 0.5, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(-0.02, -0.08);
    glVertex2f(0.02, -0.08);
    glVertex2f(0.02, -0.04);
    glVertex2f(-0.02, -0.04);
    glEnd();
    glTranslatef(0.0, -0.05, 0.0);
    glScalef(1.0, 0.6, 0.0);
    float radius4 = 0.022f;
    int numSegments3 = 100;
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments3; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments3;
        float x = radius4 * cosf(angle);
        float y = radius4 * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1);

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.435, -0.3, 0.0);
    glTranslatef(0.0,0.06,0.0);
    glScalef(rightPlantsScaleFactor, rightPlantsScaleFactor, 1.0f);
    glTranslatef(0.0,-0.06,0.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.02, -0.08);
    glVertex2f(0.02, -0.08);
    glVertex2f(0.02, -0.04);
    glVertex2f(-0.02, -0.04);
    glEnd();
    glTranslatef(0.0, -0.05, 0.0);
    glScalef(1.0, 0.6, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments3; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments3;
        float x = radius4 * cosf(angle);
        float y = radius4 * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.58, -0.2, 0.0);
    glTranslatef(0.0,0.06,0.0);
    glScalef(rightPlantsScaleFactor, rightPlantsScaleFactor, 1.0f);
    glTranslatef(0.0,-0.06,0.0);
    glColor3f(1.0, 0.5, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(-0.02, -0.08);
    glVertex2f(0.02, -0.08);
    glVertex2f(0.02, -0.04);
    glVertex2f(-0.02, -0.04);
    glEnd();
    glTranslatef(0.0, -0.05, 0.0);
    glScalef(1.0, 0.6, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments3; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments3;
        float x = radius4 * cosf(angle);
        float y = radius4 * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(1);

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.58, -0.2, 0.0);
    glTranslatef(0.0,0.06,0.0);
    glScalef(rightPlantsScaleFactor, rightPlantsScaleFactor, 1.0f);
    glTranslatef(0.0,-0.06,0.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.02, -0.08);
    glVertex2f(0.02, -0.08);
    glVertex2f(0.02, -0.04);
    glVertex2f(-0.02, -0.04);
    glEnd();
    glTranslatef(0.0, -0.05, 0.0);
    glScalef(1.0, 0.6, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments3; i++) {
        float angle = 2.0f * 3.1415926f * i / numSegments3;
        float x = radius4 * cosf(angle);
        float y = radius4 * sinf(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawHorse() {
    //body
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(horseX, 0.0f, 0.0f); // Move horse to the left
    glColor3f(0.65f, 0.45f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(-0.20, -0.30);
    glVertex2f(0.02, -0.30);
    glVertex2f(0.02, -0.20);
    glVertex2f(-0.20, -0.20);
    glEnd();
    glPopMatrix();

    //head
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(horseX, 0.0f, 0.0f); // Move horse to the left
    glColor3f(0.65f, 0.45f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.20, -0.20);
    glVertex2f(-0.16, -0.20);
    glVertex2f(-0.20, -0.05);
    glVertex2f(-0.24, -0.13);
    glVertex2f(-0.28, -0.12);
    glVertex2f(-0.28, -0.16);
    glVertex2f(-0.20, -0.12);
    glEnd();
    glPopMatrix();

    //eye
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(horseX, 0.0f, 0.0f); // Move horse to the left
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(-0.22, -0.13);
    glEnd();
    glPopMatrix();

    //line on horse
    glPushMatrix();
    glTranslatef(horseX, 0.0f, 0.0f); // Move horse to the left
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.24, -0.13);
    glVertex2f(-0.24, -0.175);
    glEnd();
    glPopMatrix();

    //legs
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(horseX, 0.0f, 0.0f); // Move horse to the left
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(-0.19, -0.30);
    glVertex2f(-0.19, -0.38);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(horseX, 0.0f, 0.0f); // Move horse to the left
    glTranslatef(0.19, -0.0, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2f(-0.19, -0.30);
    glVertex2f(-0.19, -0.38);
    glEnd();
    glPopMatrix();

    //mane
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(horseX, 0.0f, 0.0f); // Move horse to the left
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.16, -0.20);
    glVertex2f(-0.10, -0.20);
    glVertex2f(-0.20, -0.05);
    glEnd();
    glPopMatrix();

    //tail
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(horseX, 0.0f, 0.0f); // Move horse to the left
    glTranslatef(0.02, -0.20, 0.0f); // Move tail
    glRotatef(tailRotation, 1.0f, 0.0f, 0.0f); // Rotate tail on the origin point
    glTranslatef(-0.02, 0.20, 0.0f); //
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.02, -0.20);
    glVertex2f(0.06, -0.20);
    glVertex2f(0.04, -0.35);
    glEnd();
    glPopMatrix();
}


void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 0.0f); //half yellow background
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);  // Blue color (river)
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);  // Green color background - grassland
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.5f); //bottom left
    glVertex2f(1.0f, -0.5f); //bottom right
    glVertex2f(1.0f, 0.0f); //top right
    glVertex2f(-1.0f, 0.0f); //top left
    glVertex2f(-0.75f, 0.10f);
    glVertex2f(-0.55f, 0.15f); //second top
    glVertex2f(-0.35f, 0.20f); //third top
    glVertex2f(0.35f, 0.15f); //fourth top
    glVertex2f(0.65f, 0.10f); //fifth top
    glVertex2f(0.85f, 0.05f);
    glVertex2f(0.95f, 0.0f);
    glEnd();

    //left fish one  - body
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(-0.7f, -0.60f);
    glVertex2f(-0.6f, -0.65f);
    glVertex2f(-0.5f, -0.60f);
    glVertex2f(-0.6f, -0.55f);
    glEnd();

    glPointSize(3); //fish eye
    glBegin(GL_POINTS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.63f, -0.60f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.6f, -0.65f);
    glVertex2f(-0.6f, -0.55f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.55f, -0.57f);
    glVertex2f(-0.55f, -0.70f);
    glEnd();

    //left fish one - fins
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES); //tail
    glVertex2f(-0.5f, -0.60f);
    glVertex2f(-0.45f, -0.65f);
    glVertex2f(-0.45f, -0.55f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);   //upper fin
    glVertex2f(-0.6f, -0.55f);
    glVertex2f(-0.55f, -0.57f);
    glVertex2f(-0.53f, -0.50f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES); //lower fin
    glVertex2f(-0.6f, -0.65f);
    glVertex2f(-0.55f, -0.70f);
    glVertex2f(-0.55f, -0.62f);
    glEnd();

    //left fish two - body
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(-0.9f, -0.70f);
    glVertex2f(-0.8f, -0.75f);
    glVertex2f(-0.7f, -0.70f);
    glVertex2f(-0.8f, -0.65f);
    glEnd();

    glPointSize(3); //fish eye
    glBegin(GL_POINTS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.76f, -0.70f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.8f, -0.75f);
    glVertex2f(-0.8f, -0.65f);
    glEnd();

    //left fish two - fins
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);   //tail
    glVertex2f(-0.95f, -0.75f);
    glVertex2f(-0.9f, -0.70f);
    glVertex2f(-0.95f, -0.65f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES); //upper fin
    glVertex2f(-0.85f, -0.68f);
    glVertex2f(-0.8f, -0.65f);
    glVertex2f(-0.90f, -0.60f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES); //lower fin
    glVertex2f(-0.85f, -0.72f);
    glVertex2f(-0.8f, -0.75f);
    glVertex2f(-0.90f, -0.80f);
    glEnd();

    drawSun();
    drawHouseOne(-0.20f, 0.07f);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.56, 0.09, 0.0);
    glScalef(rightPlantsScaleFactor, rightPlantsScaleFactor, 0.0);
    glTranslatef(-0.56, -0.09, 0.0);
    drawTree(0.56f, 0.09f); //tree near house two
    glPopMatrix();
    drawHouseTwo(0.15f, 0.04f);
    drawTree(-0.8f, -0.1f);  // tree without deco
    drawTree(-0.07f, 0.08f); //tree in the middle of the houses
    drawfruit();
    drawStem(0.0f, 0.0f);
    drawStem(-0.15f, 0.0f);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.56, 0.09, 0.0);
    glScalef(rightPlantsScaleFactor, rightPlantsScaleFactor, 0.0);
    glTranslatef(-0.56, -0.09, 0.0);
    drawStem(0.48f, 0.0f);
    drawStem(0.64f, 0.0f);
    glPopMatrix();
    drawLeftFlowers();
    drawHorse();
    drawBoatManAndBoat();
    drawBoatPaddle();
    drawRightFlowers();
    drawRightFlowerPots();
    drawBoatPaddle();
    drawRightSideBottomFish();
    drawRightSideTopFish();
    glutSwapBuffers();
}

void reshape(int w, int h) {   //reshape function calculates the aspect ratio of the window and adjusts the projection matrix accordingly, so that the scene is not distorted when the window is resized.
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)w / (float)h;
    if (aspect > 1.0) {
        gluOrtho2D(-aspect, aspect, -1.0, 1.0);
    }
    else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Village Scene");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);  // Register the keyboard callback function
    glutTimerFunc(60, timer, 0);  // Start the timer
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
