#include "ball.h"
#include "main.h"
#include <math.h>
Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->velocity = 0;
    this->ball_bbox.height = 9.5;
    this->ball_bbox.width = 4.5;
    this->ball_bbox.x = x;
    this->ball_bbox.y = y;
    this->magnet = 0;
    this->got_hit = 0;
    this->lives = 3;
    this->health = 10000;
    this->fire = 0;
    this->flag_flying1 = 0;
    this->move_semicircle = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        0.0f, 0.0f, 0.0f, // triangle 1 : begin
        2.5f, 0.0f, 0.0f,
        2.5f, 5.0f, 0.0f, // triangle 1 : end
        0.0f, 0.0f, 0.0f, // triangle 2 : begin
        2.5f, 5.0f, 0.0f,
        0.0f, 5.0f, 0.0f, // triangle 2 : end
        0.0f, 0.0f, 0.0f, // triangle 3 : begin
        0.0f, -2.5f, 0.0f,
        1.0f, 0.0f, 0.0f, // triangle 3 : end
        0.0f, -2.5f, 0.0f, // triangle 4 : begin
        1.0f, -2.5f, 0.0f,
        1.0f, 0.0f, 0.0f, // triangle 4 : end
        1.5f, 0.0f, 0.0f, // triangle 5 : begin
        2.5f, 0.0f, 0.0f,
        1.5f, -2.5f, 0.0f, // triangle 5 : end
        2.5f, 0.0f, 0.0f, // triangle 6 : begin
        1.5f, -2.5f, 0.0f,
        2.5f, -2.5f, 0.0f, // triangle 6 : end
        1.0f, 5.0f, 0.0f, // triangle 7 : begin
        1.0f, 6.0f, 0.0f,
        1.5f, 6.0f, 0.0f, // triangle 7 : end
        1.0f, 5.0f, 0.0f, // triangle 8 : begin
        1.5f, 5.0f, 0.0f,
        1.5f, 6.0f, 0.0f, // triangle 8 : end
        0.0f, 6.0f, 0.0f, // triangle 9 : begin
        0.0f, 7.0f, 0.0f,
        2.5f, 7.0f, 0.0f, // triangle 9 : end
        2.5f, 7.0f, 0.0f, // triangle 10 : begin
        2.5f, 6.0f, 0.0f,
        0.0f, 6.0f, 0.0f, // triangle 10 : end


    }; 

    static const GLfloat vertex_buffer_data2[] = {
        -2.0f, 4.0f, 0.0f, // triangle 1 : begin
        0.0f, 4.0f, 0.0f,
        -2.0f, 1.0f, 0.0f, // triangle 1 : end
        -2.0f, 1.0f, 0.0f, // triangle 2 : begin
        0.0f, 1.0f, 0.0f,
        0.0f, 4.0f, 0.0f, // triangle 2 : end

    };
    static const GLfloat vertex_buffer_data3[] = {
        0.0f, 1.0f, 0.0f, // triangle 1 : begin
        -1.0f, 1.0f, 0.0f,
        -0.5f, -2.0f, 0.0f, // triangle 1 : end
        -1.0f, 1.0f, 0.0f, // triangle 2 : begin
        -2.0f, 1.0f, 0.0f,
        -1.5f, -1.0f, 0.0f, // triangle 2 : end

    };
    this->object1 = create3DObject(GL_TRIANGLES, 10*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_NAVY, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_ORANGE, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    if(fire == 1)
        draw3DObject(this->object3);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::move_right() {
    this->position.x += speed;
}

void Ball::move_left() {
    this->position.x -= speed;
}

void Ball::jump() {
    this->velocity = 1;
    this->fire = 1;
}

void Ball::tick()
{
    // if(move_semicircle == 1)
    // {
    //     printf("Move semicircle\n");
    //     printf("%f %f\n", this->position.x, this->position.y);
    //     this->position.y = 40 + sqrt(81 + pow((this->position.x - 40),2));
    //     this->position.x += 0.5;
    // }
    // move_semicircle = 0;
    fire = 0;
    if(magnet == 0)
    {
        speed = 0.2;
    }
    else
        speed = 0.05;
    magnet = 0;

    this->ball_bbox.x = this->position.x + 1.25;
    this->ball_bbox.y = this->position.y + 4.75;

    if(this->velocity > 0 && this->position.y >= 0)
    {
        this->position.y += this->velocity;
        this->velocity -= 0.25;
    }

    if(this->velocity == 0 && this->position.y > 0)
    {
        this->velocity = -1 ;
    }

    if(this->velocity <= 0 && this->position.y > 0)
    {
        this->position.y += this->velocity;
        this->velocity += 0.25;
    }

    if(this->position.y < 0.25)
    {
        this->position.y = 0;
    }

    if(flag_flying1 == 1)
    {
        printf("Powerup 1\n");
    }
    // if(got_hit == 1)
    //     lives --;

    // got_hit = 0;
    flag_flying1 = 0;
}
