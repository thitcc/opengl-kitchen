#ifndef ANIMATION_FILE
#define ANIMATION_FILE

float doorAngle = 0.0f;

void doorAnimation(int increment) {
  for(int i = 0; i < 90; i++) {
    doorAngle += increment;
  }
}

#endif