#include "iceball.h"
#include "main.h"
#include <math.h>

Iceball::Iceball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    this->iceball_bbox.height = 2;
    this->iceball_bbox.width = 2;
    this->iceball_bbox.x = x;
    this->iceball_bbox.y = y;
    this->flag = 1;

    int n = 100;
    
    double theta = (2 * M_PI)/n;
    int j = 0;
    GLfloat vertex_buffer_data[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data[j++] =  0.0f;
        vertex_buffer_data[j++] = 0.0f;
        vertex_buffer_data[j++] = 0.0f;
        
        vertex_buffer_data[j++] = cos(i*theta) * 1.0f;
        vertex_buffer_data[j++] = sin(i*theta) * 1.0f;
        vertex_buffer_data[j++] = 0.0f;
        
        vertex_buffer_data[j++] = cos((i+1)*theta) * 1.0f;
        vertex_buffer_data[j++] = sin((i+1)*theta)  * 1.0f;
        vertex_buffer_data[j++] = 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data, color, GL_FILL);
}

void Iceball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(flag == 1)
        draw3DObject(this->object);
}

void Iceball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Iceball::tick() {
    this->position.x += 0.5;
    // printf("Iceball- %f %f\n", this->Iceball_bbox.x, this->Iceball_bbox.y);
    this->iceball_bbox.x = this->position.x;
    this->iceball_bbox.y = this->position.y;
}