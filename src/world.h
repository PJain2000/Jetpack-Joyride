#include "main.h"

#ifndef WORLD_H
#define WORLD_H


class World {
public:
	World() {}
    World(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // WORLD_H