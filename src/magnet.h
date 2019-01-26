#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
	Magnet() {}
    Magnet(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t magnet_bbox;
    double speed;
    int count;
    int flag;
private:
    VAO *object1;
    VAO *object2;
};

#endif // MAGNET_H