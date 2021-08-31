#ifndef BUILD_FILE
#define BUILD_FILE

const float KITCHEN_WIDTH = 20;
const float KITCHEN_HEIGHT = 10;
const float KITCHEN_DEPTH = 1;

const float DOOR_WIDTH = 2.8f;
const float DOOR_HEIGHT = 6;
const float DOOR_DEPTH = 1;

const float WINDOW_WIDTH = 4;
const float WINDOW_HEIGHT = 3;
const float WINDOW_DEPTH = 1;

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
  glVertex3f(0.0f, height, depth);
  glVertex3f(0.0f, height, 0.0f);
  glVertex3f(width, height, 0.0f);
  glVertex3f(width, height, depth);

  // Bottom
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(width, 0.0f, 0.0f);
  glVertex3f(width, 0.0f, depth);
  glVertex3f(0.0f, 0.0f, depth);
}

void buildFrontWall() {
  glColor3f(RED);

  glBegin(GL_QUADS);
    buildWall(KITCHEN_WIDTH, KITCHEN_HEIGHT, KITCHEN_DEPTH);
  glEnd();
}

void buildBackWall() {
  glColor3f(GREEN);

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, KITCHEN_WIDTH);

    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH, KITCHEN_HEIGHT, KITCHEN_DEPTH);
    glEnd();
  glPopMatrix();

  glFlush();
}

void buildLeftWall() {
  glColor3f(BLUE);

  glPushMatrix();
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH + KITCHEN_DEPTH, KITCHEN_HEIGHT, KITCHEN_DEPTH);
    glEnd();
  glPopMatrix();

  glFlush();
}

void buildRightWall() {
  glColor3f(RED);

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
      buildWall(DOOR_WIDTH, DOOR_HEIGHT, 0.2f);
    glEnd();

    glPushMatrix();
      glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(0.2f, DOOR_HEIGHT, 0.2);
      glEnd();
    glPopMatrix();

  glPopMatrix();

  glFlush();
}

void buildFloor() {
  glColor3f(PURPLE);

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
  glColor3f(CYAN);

  glPushMatrix();
    glTranslatef(0.0f, KITCHEN_HEIGHT, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH - 1, KITCHEN_HEIGHT * 2 - 1, 0.0f);
    glEnd();
  glPopMatrix();

  glFlush();
}
#endif