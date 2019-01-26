#include "main.h"

#ifndef LINES_H
#define LINES_H


class Lines {
public:
	Lines() {}
    Lines(float x, float y, color_t color, int angle);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double dir;
    bounding_box_t lines_bbox;
    int flag;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // LINES_H