#ifndef TEXTURE_FILE
#define TEXTURE_FILE

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct Texture {
  int id;
  int width;
  int height;
  unsigned char *data;
} Texture;

Texture wall_texture;
Texture tile_texture;
Texture ceiling_texture;
Texture door_texture;
Texture wood_texture;
Texture window_texture;
Texture cabinet_door_texture;
Texture metal_texture;
Texture metal_matte_texture;
Texture stove_front_texture;
Texture stove_up_texture;
Texture fridge_texture;

void loadTexture(char* filePath, Texture* texture) {
  int nrChannels;

  texture->data = stbi_load(filePath, &texture->width, &texture->height, &nrChannels, 0);

  if (texture->data) {
    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);
  } else {
    printf("Falha ao carregar textura: %s\n", filePath);
    exit(1);
  }

  stbi_image_free(texture->data);
}

void initTextures() {
  loadTexture("./textures/wall_black.jpg", &wall_texture);
  loadTexture("./textures/tile.jpg", &tile_texture);
  loadTexture("./textures/wall_white.jpg", &ceiling_texture);
  loadTexture("./textures/door.png", &door_texture);
  loadTexture("./textures/wood.jpg", &wood_texture);
  loadTexture("./textures/window.jpg", &window_texture);
  loadTexture("./textures/wood2.jpg", &cabinet_door_texture);
  loadTexture("./textures/metal.jpg", &metal_texture);
  loadTexture("./textures/metal_matte.jpg", &metal_matte_texture);
  loadTexture("./textures/stove_front.jpg", &stove_front_texture);
  loadTexture("./textures/stove_up.jpg", &stove_up_texture);
  loadTexture("./textures/fridge.jpg", &fridge_texture);
}

#endif