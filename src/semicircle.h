#include "main.h"

#ifndef SEMICIRCLE_H
#define SEMICIRCLE_H


class Semicircle {
public:
	Semicircle() {}
    Semicircle(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t semicircle_bbox;
    void tick();
    double speed;
    int flag;
private:
    VAO *object1;
    VAO *object2;
};

#endif // SEMICIRCLE_H