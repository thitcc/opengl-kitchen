#ifndef ANIMATION_FILE
#define ANIMATION_FILE

enum OBJECT_STATE { OPEN, CLOSE, IDLE };

typedef struct Object {
  float angle;
  enum OBJECT_STATE state;
} Object;

Object door = { 0.0f, IDLE };
Object window = { 0.0f, IDLE };

void doorAnimation() {
  if (door.state != IDLE) {
    door.angle += door.state == OPEN ? 1.0f : -1.0f;

    if (door.angle == 0.0f || door.angle == 90.0f) { door.state = IDLE; }
  }
}

void windowAnimation() {
  if (window.state != IDLE) {
    window.angle += window.state == OPEN ? 1.0f : -1.0f;

    if (window.angle == 0.0f || window.angle == 60.0f) { window.state = IDLE; }
  }
}

void changeDoorState() { door.state = door.angle == 0.0f ? OPEN : CLOSE; }

void changeWindowState() { window.state = window.angle == 0.0f ? OPEN : CLOSE; }

#endif