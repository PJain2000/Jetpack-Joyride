#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
	Dragon() {}
    Dragon(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t dragon_bbox;
    double speed;
    double dir;
    double flag;
    int count;
    int health;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // DRAGON_H