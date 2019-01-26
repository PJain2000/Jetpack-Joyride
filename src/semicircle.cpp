#include "semicircle.h"
#include "main.h"
#include <math.h>

Semicircle::Semicircle(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    this->semicircle_bbox.height = 14;
    this->semicircle_bbox.width = 14;
    this->semicircle_bbox.x = x;
    this->semicircle_bbox.y = y;
    this->flag = 1;

    int n = 100;
    
    double theta = (2 * M_PI)/n;
    int j = 0;
    GLfloat vertex_buffer_data1[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data1[j++] =  0.0f;
        vertex_buffer_data1[j++] = 0.0f;
        vertex_buffer_data1[j++] = 0.0f;
        
        vertex_buffer_data1[j++] = cos(i*theta) * 10.0f;
        vertex_buffer_data1[j++] = sin(i*theta) * 10.0f;
        vertex_buffer_data1[j++] = 0.0f;
        
        vertex_buffer_data1[j++] = cos((i+1)*theta) * 10.0f;
        vertex_buffer_data1[j++] = sin((i+1)*theta)  * 10.0f;
        vertex_buffer_data1[j++] = 0.0f;
    }
    int k = 0;
    GLfloat vertex_buffer_data2[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data2[k++] =  0.0f;
        vertex_buffer_data2[k++] = 0.0f;
        vertex_buffer_data2[k++] = 0.0f;
        
        vertex_buffer_data2[k++] = cos(i*theta) * 9.0f;
        vertex_buffer_data2[k++] = sin(i*theta) * 9.0f;
        vertex_buffer_data2[k++] = 0.0f;
        
        vertex_buffer_data2[k++] = cos((i+1)*theta) * 9.0f;
        vertex_buffer_data2[k++] = sin((i+1)*theta)  * 9.0f;
        vertex_buffer_data2[k++] = 0.0f;
    }
    this->object1 = create3DObject(GL_TRIANGLES, 50*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 50*3, vertex_buffer_data2, COLOR_BACKGROUND, GL_FILL);
}

void Semicircle::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
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

void Semicircle::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Semicircle::tick() {
    this->position.x += 0.5;
    // printf("Semicircle- %f %f\n", this->Semicircle_bbox.x, this->Semicircle_bbox.y);
    this->semicircle_bbox.x = this->position.x;
    this->semicircle_bbox.y = this->position.y;
}