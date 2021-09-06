#ifndef BUILD_FILE
#define BUILD_FILE

const float KITCHEN_WIDTH = 20;
const float KITCHEN_HEIGHT = 10;
const float KITCHEN_DEPTH = 1;

const float DOOR_WIDTH = 2.8;
const float DOOR_HEIGHT = 6;
const float DOOR_DEPTH = 0.2;

const float WINDOW_WIDTH = 3;
const float WINDOW_HEIGHT = 2;
const float WINDOW_DEPTH = 0.2;

void buildWall(float width, float height, float depth) {
  // Front
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, height, 0.0f);
  glVertex3f(width, height, 0.0f);
  glVertex3f(width, 0.0f, 0.0f);

  // Back
  glVertex3f(0.0f, 0.0f, depth);
  glVertex3f(width, 0.0f, depth);
  glVertex3f(width, height, depth);
  glVertex3f(0.0f, height, depth);

  // left
  glVertex3f(0.0f, 0.0f, depth);
  glVertex3f(0.0f, height, depth);
  glVertex3f(0.0f, height, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);

  // Right
  glVertex3f(width, 0.0f, 0.0f);
  glVertex3f(width, height, 0.0f);
  glVertex3f(width, height, depth);
  glVertex3f(width, 0.0f, depth);

  // Top
  glVertex3f(0.0f, height, 0.0f);
  glVertex3f(0.0f, height, depth);
  glVertex3f(width, height, depth);
  glVertex3f(width, height, 0.0f);

  // Bottom
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(width, 0.0f, 0.0f);
  glVertex3f(width, 0.0f, depth);
  glVertex3f(0.0f, 0.0f, depth);
}

void buildFrontWall() {
  glColor3f(FRONTWALL);

  glBegin(GL_QUADS);
    buildWall(KITCHEN_WIDTH, KITCHEN_HEIGHT, KITCHEN_DEPTH);
  glEnd();
}

void buildBackWall() {
  glColor3f(BACKWALL);

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, KITCHEN_WIDTH);

    // Left
    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH - 5, KITCHEN_HEIGHT, KITCHEN_DEPTH);
    glEnd();

    // Right
    glPushMatrix();
      glTranslatef(15.0f, 0.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(5.0f, 6.0f, KITCHEN_DEPTH);
      glEnd();
    glPopMatrix();

    // Right-Top
    glPushMatrix();
      glTranslatef(18.0f, 6.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(2.0f, WINDOW_HEIGHT + 2, KITCHEN_DEPTH);
      glEnd();
    glPopMatrix();

    //Left-Top
    glPushMatrix();
      glTranslatef(15.0f, 8.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(3.0f, 2.0f, KITCHEN_DEPTH);
      glEnd();
    glPopMatrix();
  glPopMatrix();

  glFlush();
}

void buildWindow(float curvature_angle) {
  glColor3f(SOFTBLUE);
  glPushMatrix();
    glTranslatef(15.0f, 8.0f, KITCHEN_WIDTH + WINDOW_DEPTH);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(0.0f + curvature_angle, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
      buildWall(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_DEPTH);
    glEnd();
  glPopMatrix();
}

void buildLeftWall() {
  glColor3f(LEFTWALL);

  glPushMatrix();
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH + KITCHEN_DEPTH, KITCHEN_HEIGHT, KITCHEN_DEPTH);
    glEnd();
  glPopMatrix();

  glFlush();
}

void buildRightWall() {
  glColor3f(RIGHTWALL);

  glPushMatrix();
    glTranslatef(KITCHEN_WIDTH, 0.0f, KITCHEN_DEPTH);
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);

    // Left
    glBegin(GL_QUADS);
      buildWall(8.0f, DOOR_HEIGHT, 1);
    glEnd();

    // Right
    glPushMatrix();
      glTranslatef(11.0f, 0.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(8.0f, DOOR_HEIGHT, 1);
      glEnd();
    glPopMatrix();

    // Top
    glPushMatrix();
      glTranslatef(0.0f, DOOR_HEIGHT, 0.0f);
      glBegin(GL_QUADS);
        buildWall(KITCHEN_WIDTH - 1, KITCHEN_HEIGHT - DOOR_HEIGHT, 1);
      glEnd();
    glPopMatrix();
  glPopMatrix();

  glFlush();
}

void buildDoor(float curvature_angle) {
  glColor3f(BROWN);

  glPushMatrix();
    glTranslatef(KITCHEN_WIDTH - 0.8, 0.0f, 9.2f);
    glRotatef(270.0f - curvature_angle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(DOOR_WIDTH, DOOR_HEIGHT, DOOR_DEPTH);
    glEnd();

    glPushMatrix();
      glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(0.2f, DOOR_HEIGHT, DOOR_DEPTH);
      glEnd();
    glPopMatrix();

  glPopMatrix();

  glFlush();
}

void buildFloor() {
  glColor3f(GREY);

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH - 1, KITCHEN_HEIGHT * 2 - 1, 0.0f);
    glEnd();
  glPopMatrix();

  glFlush();
}

void buildCeiling() {
  glColor3f(GREY);

  glPushMatrix();
    glTranslatef(0.0f, KITCHEN_HEIGHT, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH - 1, KITCHEN_HEIGHT * 2 - 1, 0.0f);
    glEnd();
  glPopMatrix();

  glFlush();
}

void buildSink() {
  glColor3f(DARKGREY);

  glPushMatrix();
    glTranslatef(8.0f, 3.5f, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    // Top
    glBegin(GL_QUADS);
      buildWall(5.0f, 3.0f, 0.5f);
    glEnd();

    // Bottom
    glPushMatrix();
      glTranslatef(0.5f, 0.0f, 0.5f);
      glColor3f(BROWN);
      glBegin(GL_QUADS);
        buildWall(4.0f, 3.0f, 3.0f);
      glEnd();
    glPopMatrix();

    // Water Tap
    glPushMatrix();
      glTranslatef(2.0f, 0.0f, -1.8f);
      glColor3f(GREY);
      glBegin(GL_QUADS);
        buildWall(0.5f, 1.0f, 0.2f);
      glEnd();

      glTranslatef(0.0f, 1.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(0.5f, 0.5f, 0.5f);
      glEnd();
    glPopMatrix();
  glPopMatrix();

  glFlush();
}

void buildSinkUpperCabinet() {
  glColor3f(BROWN);

  glPushMatrix();
    glTranslatef(7.5f, 6.5f, 1.0f);

    glBegin(GL_QUADS);
      buildWall(6.0f, 3.0f, 2.0f);
    glEnd();

  glPopMatrix();

  glFlush();
}

void buildFridge() {
  glColor3f(DARKGREY);

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, KITCHEN_WIDTH - 3.0f);
    glBegin(GL_QUADS);
      buildWall(4.0f, 8.0f, 3.0f);
    glEnd();

    glPushMatrix();
      glColor3f(SOFTGREY);
      glTranslatef(0.0f, 0.0f, -0.1f);
      glBegin(GL_QUADS);
        buildWall(4.0f, 5.5f, 0.1f);
      glEnd();
    glPopMatrix();
    
    glPushMatrix();
      glColor3f(MEDIUMGREY);
      glTranslatef(0.0f, 5.5f, -0.1f);
      glBegin(GL_QUADS);
        buildWall(4.0f, 2.5f, 0.1f);
      glEnd();
    glPopMatrix();
  glPopMatrix();

  glFlush();
}

void buildStove() {
  glColor3f(SOFTGREY);

  glPushMatrix();
    glTranslatef(KITCHEN_WIDTH - 5.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
      buildWall(4.0f, 3.5f, 3.0f);
    glEnd();

    glPushMatrix();
      glTranslatef(0.3f, 0.3f, 3.0f);
      glColor3f(BLACK);
      glBegin(GL_QUADS);
        buildWall(3.5f, 2.5f, 0.1f);
      glEnd();
    glPopMatrix();

  glPopMatrix();

  glFlush();
}

void buildCabinet() {
  glColor3f(WHITE);

  glPushMatrix();
    glTranslatef(7.0f, 0.0f, KITCHEN_WIDTH - 3.0f);
    glBegin(GL_QUADS);
      buildWall(5.0f, 5.0f, 3.0f);
    glEnd();

    glPushMatrix();
      glColor3f(SOFTERWHITE);
      glTranslatef(0.0f, 0.0f, -0.2f);
      glBegin(GL_QUADS);
        buildWall(2.5f, 5.0f, 0.2f);
      glEnd();
    glPopMatrix();

    glPushMatrix();
      glColor3f(SOFTWHITE);
      glTranslatef(2.5f, 0.0f, -0.1f);
      glBegin(GL_QUADS);
        buildWall(2.5f, 5.0f, 0.1f);
      glEnd();
    glPopMatrix();
  glPopMatrix();

  glFlush();
}
#endif