#ifndef BUILD_FILE
#define BUILD_FILE

const float KITCHEN_WIDTH = 20;
const float KITCHEN_HEIGHT = 10;
const float KITCHEN_DEPTH = 1;

const float DOOR_WIDTH = 4;
const float DOOR_HEIGHT = 6;
const float DOOR_DEPTH = 1;

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
  glVertex3f(0.0f, 0.0f, depth);
  glVertex3f(width, 0.0f, depth);
  glVertex3f(width, 0.0f, 0.0f);
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
  glColor3f(YELLOW);

  glPushMatrix();
    glTranslatef(KITCHEN_WIDTH, 0.0f, KITCHEN_DEPTH);
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH - KITCHEN_DEPTH, KITCHEN_HEIGHT, KITCHEN_DEPTH);
    glEnd();
  glPopMatrix();

  glFlush();
}


#endif