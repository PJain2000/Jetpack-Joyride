#include "main.h"

#ifndef BEAMS_H
#define BEAMS_H


class Beams {
public:
	Beams() {}
    Beams(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t beams_bbox;
    double speed;
    double dir;
    double flag;
    int count;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // BEAMS_H