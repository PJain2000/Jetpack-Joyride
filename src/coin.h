#include "main.h"

#ifndef COIN_H
#define COIN_H


class Coin {
public:
	Coin() {}
    Coin(float x, float y, color_t color);
    float rotation;
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t coin_bbox;
    void tick();
    double speed;
    double score;
    int flag;
private:
    VAO *object;
};

#endif // COIN_H