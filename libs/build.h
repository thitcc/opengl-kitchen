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

void buildWall(float width, float height, float depth, float texCoordH, float texCoordV) {
  // Front
  glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

  glTexCoord2f(0.0f, texCoordV);
    glVertex3f(0.0f, height, 0.0f);

  glTexCoord2f(texCoordH, texCoordV);
    glVertex3f(width, height, 0.0f);

  glTexCoord2f(texCoordH, 0.0f);
    glVertex3f(width, 0.0f, 0.0f);

  // Back
  glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, depth);

  glTexCoord2f(texCoordH, 0.0f);
    glVertex3f(width, 0.0f, depth);

  glTexCoord2f(texCoordH, texCoordV);
    glVertex3f(width, height, depth);

  glTexCoord2f(0.0f, texCoordV);
    glVertex3f(0.0f, height, depth);

  // Top
  glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0f, height, 0.0f);

  glTexCoord2f(texCoordH, 0.0);
    glVertex3f(0.0f, height, depth);

  glTexCoord2f(texCoordH, texCoordV);
    glVertex3f(width, height, depth);
  
  glTexCoord2f(0.0, texCoordV);
    glVertex3f(width, height, 0.0f);

  // Bottom
  glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0f, 0.0f, 0.0f);

  glTexCoord2f(0.0, texCoordV);
    glVertex3f(width, 0.0f, 0.0f);

  glTexCoord2f(texCoordH, texCoordV);
    glVertex3f(width, 0.0f, depth);
  
  glTexCoord2f(texCoordH, 0.0);
    glVertex3f(0.0f, 0.0f, depth);

  // Right
  glTexCoord2f(0.0, 0.0);
    glVertex3f(width, 0.0f, 0.0f);

  glTexCoord2f(0.0, texCoordV);
    glVertex3f(width, height, 0.0f);

  glTexCoord2f(texCoordH, texCoordV);
    glVertex3f(width, height, depth);

  glTexCoord2f(texCoordH, 0.0);
    glVertex3f(width, 0.0f, depth);

  // left
  glTexCoord2f(texCoordH, 0.0f);
    glVertex3f(0.0f, 0.0f, depth);

  glTexCoord2f(texCoordH, texCoordV);
    glVertex3f(0.0f, height, depth);

  glTexCoord2f(0.0f, texCoordV);
    glVertex3f(0.0f, height, 0.0f);

  glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
}

void buildFrontWall(Texture* texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glBegin(GL_QUADS);
    buildWall(KITCHEN_WIDTH, KITCHEN_HEIGHT, KITCHEN_DEPTH, 1.0f, 1.0f);
  glEnd();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildBackWall(Texture* texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, KITCHEN_WIDTH);

    // Left
    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH - 5, KITCHEN_HEIGHT, KITCHEN_DEPTH, 1.0f, 1.0f);
    glEnd();

    // Right
    glPushMatrix();
      glTranslatef(15.0f, 0.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(5.0f, 6.0f, KITCHEN_DEPTH, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();

    // Right-Top
    glPushMatrix();
      glTranslatef(18.0f, 6.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(2.0f, WINDOW_HEIGHT + 2, KITCHEN_DEPTH, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();

    //Left-Top
    glPushMatrix();
      glTranslatef(15.0f, 8.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(3.0f, 2.0f, KITCHEN_DEPTH, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildWindow(float curvature_angle, Texture* texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glPushMatrix();
    glTranslatef(15.0f, 8.0f, KITCHEN_WIDTH + WINDOW_DEPTH);
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(0.0f + curvature_angle, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
      buildWall(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_DEPTH, 1.0f, 1.0f);
    glEnd();
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildLeftWall(Texture* texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glPushMatrix();
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH + KITCHEN_DEPTH, KITCHEN_HEIGHT, KITCHEN_DEPTH, 1.0f, 1.0f);
    glEnd();
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildRightWall(Texture* texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glPushMatrix();
    glTranslatef(KITCHEN_WIDTH, 0.0f, KITCHEN_DEPTH);
    glRotatef(270.0f, 0.0f, 1.0f, 0.0f);

    // Left
    glBegin(GL_QUADS);
      buildWall(8.0f, DOOR_HEIGHT, 1, 1.0f, 1.0f);
    glEnd();

    // Right
    glPushMatrix();
      glTranslatef(11.0f, 0.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(8.0f, DOOR_HEIGHT, 1, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();

    // Top
    glPushMatrix();
      glTranslatef(0.0f, DOOR_HEIGHT, 0.0f);
      glBegin(GL_QUADS);
        buildWall(KITCHEN_WIDTH - 1, KITCHEN_HEIGHT - DOOR_HEIGHT, 1, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildDoor(float curvature_angle, Texture* texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glPushMatrix();
    glTranslatef(KITCHEN_WIDTH - 0.8, 0.0f, 9.2f);
    glRotatef(270.0f - curvature_angle, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(DOOR_WIDTH, DOOR_HEIGHT, DOOR_DEPTH, 1.0f, 1.0f);
    glEnd();

    glPushMatrix();
      glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(0.2f, DOOR_HEIGHT, DOOR_DEPTH, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();

  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildFloor(Texture* texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH - 1, KITCHEN_HEIGHT * 2 - 1, 0.0f, 3.0f, 3.0f);
    glEnd();
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildCeiling(Texture* texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glPushMatrix();
    glTranslatef(0.0f, KITCHEN_HEIGHT, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
      buildWall(KITCHEN_WIDTH - 1, KITCHEN_HEIGHT * 2 - 1, 0.0f, 1.0f, 1.0f);
    glEnd();
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildSink(Texture* wood_texture, Texture* metal_texture, Texture* metal_matte_texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, wood_texture->id);

  glPushMatrix();
    glTranslatef(8.0f, 3.5f, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    // Bottom
    glPushMatrix();
      glTranslatef(0.5f, 0.0f, 0.5f);
      glColor3f(BROWN);
      glBegin(GL_QUADS);
        buildWall(4.0f, 3.0f, 3.0f, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, metal_matte_texture->id);

    // Top
    glBegin(GL_QUADS);
      buildWall(5.0f, 3.0f, 0.5f, 1.0f, 1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, metal_texture->id);

    // Water Tap
    glPushMatrix();
      glTranslatef(2.0f, 0.0f, -1.8f);
      glColor3f(GREY);
      glBegin(GL_QUADS);
        buildWall(0.5f, 1.0f, 0.2f, 1.0f, 1.0f);
      glEnd();

      glTranslatef(0.0f, 1.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(0.5f, 0.5f, 0.5f, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildSinkUpperCabinet(Texture* wood_texture, Texture* cabinet_door_texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, wood_texture->id);

  glPushMatrix();
    glTranslatef(7.5f, 6.5f, 1.0f);

    glBegin(GL_QUADS);
      buildWall(6.0f, 3.0f, 2.0f, 1.0f, 1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, cabinet_door_texture->id);

    glTranslatef(0.0f, 0.0f, 2.0f);
    glBegin(GL_QUADS);
      buildWall(2.9f, 3.0f, 0.1f, 1.0f, 1.0f);
    glEnd();

    glTranslatef(3.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
      buildWall(2.9f, 3.0f, 0.1f, 1.0f, 1.0f);
    glEnd();

  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildFridge(Texture* metal_texture, Texture* fridge_texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, metal_texture->id);

  glPushMatrix();
    glTranslatef(0.0f, 0.0f, KITCHEN_WIDTH - 3.0f);
    glBegin(GL_QUADS);
      buildWall(4.0f, 8.0f, 3.0f, 1.0f, 1.0f);
    glEnd();
  
    glBindTexture(GL_TEXTURE_2D, fridge_texture->id);

    glPushMatrix();
      glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
      glTranslatef(-4.0f, -8.0f, -0.1f);
      glBegin(GL_QUADS);
        buildWall(4.0f, 8.0f, 0.1f, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildStove(Texture* metal_texture, Texture* stove_front_texture, Texture* stove_up_texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, metal_texture->id);

  glPushMatrix();
    glTranslatef(KITCHEN_WIDTH - 5.0f, 0.0f, 1.0f);

    // Body
    glBegin(GL_QUADS);
      buildWall(4.0f, 3.5f, 3.0f, 1.0f, 1.0f);
    glEnd();
  
    glBindTexture(GL_TEXTURE_2D, stove_up_texture->id);

    // Top
    glPushMatrix();
      glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
      glTranslatef(-3.0f, 3.51f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(3.0f, 0.0f, 4.0f, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, stove_front_texture->id);

    // Front
    glPushMatrix();
      glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
      glTranslatef(-3.8f, -3.0f, 3.0f);
      glBegin(GL_QUADS);
        buildWall(3.5f, 2.5f, 0.1f, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();

  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildCabinet(Texture* wood_texture, Texture* cabinet_door_texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, wood_texture->id);

  glPushMatrix();
    glTranslatef(14.0f, 0.0f, KITCHEN_WIDTH - 3.0f);
    glBegin(GL_QUADS);
      buildWall(5.0f, 5.0f, 3.0f, 1.0f, 1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, cabinet_door_texture->id);

    // Doors
    glPushMatrix();
      glColor3f(SOFTERWHITE);
      glTranslatef(0.0f, 0.0f, -0.2f);
      glBegin(GL_QUADS);
        buildWall(2.5f, 5.0f, 0.2f, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();

    glPushMatrix();
      glColor3f(SOFTWHITE);
      glTranslatef(2.5f, 0.0f, -0.1f);
      glBegin(GL_QUADS);
        buildWall(2.5f, 5.0f, 0.1f, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildTable(Texture* wood_texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, wood_texture->id);

  glPushMatrix();
    glTranslatef(8.0f, 3.0f, 8.0f);

    // Top
    glBegin(GL_QUADS);
      buildWall(4.0f, 0.2f, 5.0f, 1.0f, 1.0f);
    glEnd();

    // Legs
    glPushMatrix();
      glTranslatef(0.0f, -3.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(0.2f, 3.0f, 0.2f, 1.0f, 1.0f);
      glEnd();
      
      glTranslatef(3.8f, 0.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(0.2f, 3.0f, 0.2f, 1.0f, 1.0f);
      glEnd();

      glTranslatef(0.0f, 0.0f, 4.8f);
      glBegin(GL_QUADS);
        buildWall(0.2f, 3.0f, 0.2f, 1.0f, 1.0f);
      glEnd();

      glTranslatef(-3.8f, 0.0f, 0.0f);
      glBegin(GL_QUADS);
        buildWall(0.2f, 3.0f, 0.2f, 1.0f, 1.0f);
      glEnd();
    glPopMatrix();
  
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}

void buildCeilingFan(float rotation_angle, Texture* texture) {
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glPushMatrix();
    glTranslatef(10.0f, KITCHEN_HEIGHT - 2.0f, 10.5f);

    // Support Column
    glBegin(GL_QUADS);
      buildWall(0.2f, 2.0f, 0.2f, 1.0f, 1.0f);
    glEnd();

    float offset = 0.1f;

    // Helixes
    glPushMatrix();
      glTranslatef(offset, 0.0f, offset);

      glRotatef(rotation_angle, 0.0f, 0.1f, 0.0f);

      glTranslatef(-offset, 0.0f, -offset);
      
      glTranslatef(0.0f, 0.0f, 0.2f);
      glBegin(GL_QUADS);
        buildWall(0.2f, 0.2f, 0.4f, 1.0f, 1.0f);
      glEnd();

      glTranslatef(-0.2f, 0.0f, 0.4f);
      glBegin(GL_QUADS);
        buildWall(0.6f, 0.2f, 2.5f, 1.0f, 1.0f);
      glEnd();

      glPushMatrix();
        glTranslatef(0.2f, 0.0f, -1.0f);
        glBegin(GL_QUADS);
          buildWall(0.2f, 0.2f, 0.4f, 1.0f, 1.0f);
        glEnd();

        glTranslatef(-0.2f, 0.0f, -2.5f);
        glBegin(GL_QUADS);
          buildWall(0.6f, 0.2f, 2.5f, 1.0f, 1.0f);
        glEnd();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-0.2f, 0.0f, -0.6f);
        glBegin(GL_QUADS);
          buildWall(0.4f, 0.2f, 0.2f, 1.0f, 1.0f);
        glEnd();

        glTranslatef(-2.5f, 0.0f, -0.2f);
        glBegin(GL_QUADS);
          buildWall(2.5f, 0.2f, 0.6f, 1.0f, 1.0f);
        glEnd();
      glPopMatrix();

      glPushMatrix();
        glTranslatef(0.4f, 0.0f, -0.6f);
        glBegin(GL_QUADS);
        buildWall(0.4f, 0.2f, 0.2f, 1.0f, 1.0f);
        glEnd();

        glTranslatef(0.4f, 0.0f, -0.2f);
        glBegin(GL_QUADS);
          buildWall(2.5f, 0.2f, 0.6f, 1.0f, 1.0f);
        glEnd();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  glFlush();
  glDisable(GL_TEXTURE_2D);
}
#endif