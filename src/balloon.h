#include "main.h"

#ifndef BALLOON_H
#define BALLOON_H


class Balloon {
public:
	Balloon() {}
    Balloon(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t balloon_bbox;
    void tick();
    double speed;
    int flag;
private:
    VAO *object;
};

#endif // BALLOON_H