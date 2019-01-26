#include "dragon.h"
#include "main.h"
#include <math.h>

Dragon::Dragon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    this->dir = 1;
    this->flag = 1;
    this->count = 0;
    this->dragon_bbox.height = 10;
    this->dragon_bbox.width = 16;
    this->dragon_bbox.x = x;
    this->dragon_bbox.y = y;
    this->health = 10000;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        0.0f, 8.0f, 0.0f, // triangle 1 : begin
        4.0f, 0.0f, 0.0f,
        8.0f, 4.0f, 0.0f, // triangle 1 : end
        0.0f, 8.0f , 0.0f, // triangle 2 : begin
        8.0f, 4.0f, 0.0f,
        7.2f, 6.4f, 0.0f, // triangle 2 : end
        0.0f, 10.0f, 0.0f,
        -2.0f, 7.0f, 0.0f,
        0.0f, 6.0f, 0.0f,
        7.4f, 5.2f, 0.0f,
        8.0f, 4.0f, 0.0f,
        14.4f,6.2f, 0.0f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data1, color, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    // this->count++;
    // if (this->count == 360)
    // {
    //     this->count = 0;
    //     flag = 1;
    // }
    // if(this->count > 120)
    //     flag = 0;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if (flag == 1)
        draw3DObject(this->object1);
}
void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick() {
    if(flag == 1)
        this->position.x += 0.05;
    this->dragon_bbox.x = this->position.x;
    this->dragon_bbox.y = this->position.y;
    if(this->dir == 1)
    {
        this->position.y += 0.125;
    }
    else
    {
        this->position.y -= 0.125;
    }

    if(this->position.y == 55)
            this->dir = 0;

    if(this->position.y == 0)
            this->dir = 1;

    if(this->health == 0)
    {
        this->flag = 0;
    }
}