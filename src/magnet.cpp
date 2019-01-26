#include "magnet.h"
#include "main.h"
#include <math.h>

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    this->magnet_bbox.height = 40;
    this->magnet_bbox.width = 20;
    this->magnet_bbox.x = x;
    this->magnet_bbox.y = y;
    this->flag = 1;
    this->count = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        0.0f, 0.0f, 0.0f, // triangle 1 : begin
        0.0f, 2.0f, 0.0f,
        4.0f, 2.0f, 0.0f, // triangle 1 : end
        4.0f, 2.0f, 0.0f, // triangle 2 : begin
        0.0f, 0.0f, 0.0f,
        4.0f, 0.0f, 0.0f, // triangle 2 : end

    };

    static const GLfloat vertex_buffer_data2[] = {
        4.0f, 0.0f, 0.0f, // triangle 1 : begin
        8.0f, 2.0f, 0.0f,
        4.0f, 2.0f, 0.0f, // triangle 1 : end
        4.0f, 0.0f, 0.0f, // triangle 2 : begin
        8.0f, 2.0f, 0.0f,
        8.0f, 0.0f, 0.0f, // triangle 2 : end

    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_NAVY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    count++;
    if (this->count == 360)
    {
        this->count = 0;
        flag = 1;
    }
    if(this->count > 240)
        flag = 0;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(flag == 1)
    {
        draw3DObject(this->object1);
        draw3DObject(this->object2);
    }
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    this->magnet_bbox.x = this->position.x;
    this->magnet_bbox.y = this->position.y;
}