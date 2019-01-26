#include "main.h"

#ifndef FLYING2_H
#define FLYING2_H


class Flying2 {
public:
	Flying2() {}
    Flying2(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t flying2_bbox;
    void tick();
    int flag;
    double velocity;
private:
    VAO *object;
};

#endif // FLYING2_H