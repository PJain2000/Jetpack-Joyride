#include "main.h"

#ifndef DISPLAY_H
#define DISPLAY_H


class Display {
public:
	Display() {}
    Display(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void tick();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    int number;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;

};

#endif // DISPLAY_H