#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
	Boomerang() {}
    Boomerang(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t boomerang_bbox;
    void tick();
    int flag;
    double velocity;
private:
    VAO *object;
};

#endif // BOOMERANG_H