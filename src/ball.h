#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void move_left();
    void move_right();
    void jump();
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bounding_box_t ball_bbox;
    void tick();
    double speed;
    double velocity;
    double magnet;
    double lives;
    int fire;
    int flag_flying1;
    void shoot(); 
    int got_hit;
    int health;
    int move_semicircle;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    
};

#endif // BALL_H
