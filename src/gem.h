#include "main.h"

#ifndef GEM_H
#define GEM_H


class Gem {
public:
	Gem() {}
    Gem(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double score;
    bounding_box_t gem_bbox;
    int flag;
private:
    VAO *object;
};

#endif // GEM_H