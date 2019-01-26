#include "main.h"

#ifndef FLYING1_H
#define FLYING1_H


class Flying1 {
public:
	Flying1() {}
    Flying1(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t flying1_bbox;
    void tick();
    int flag;
    double velocity;
private:
    VAO *object;
};

#endif // FLYING1_H