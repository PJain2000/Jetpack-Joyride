#include "beams.h"
#include "main.h"
#include <math.h>

Beams::Beams(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    this->dir = 1;
    this->flag = 1;
    this->count = 0;
    this->beams_bbox.height = 2;
    this->beams_bbox.width = 80;
    this->beams_bbox.x = x;
    this->beams_bbox.y = y;
    int n = 100;
    
    double theta = (2 * M_PI)/n;
    int j = 0;
    GLfloat vertex_buffer_data1[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data1[j++] =  0.0f;
        vertex_buffer_data1[j++] = 0.0f;
        vertex_buffer_data1[j++] = 0.0f;
        
        vertex_buffer_data1[j++] = cos(i*theta) * 1.0f;
        vertex_buffer_data1[j++] = sin(i*theta) * 1.0f;
        vertex_buffer_data1[j++] = 0.0f;
        
        vertex_buffer_data1[j++] = cos((i+1)*theta) * 1.0f;
        vertex_buffer_data1[j++] = sin((i+1)*theta)  * 1.0f;
        vertex_buffer_data1[j++] = 0.0f;
    }

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data2[] = {
        1.0f, 1.0f, 0.0f, // triangle 1 : begin
        1.0f, -1.0f, 0.0f,
        77.0f, 1.0f, 0.0f, // triangle 1 : end
        1.0f, -1.0f , 0.0f, // triangle 2 : begin
        77.0f, 1.0f, 0.0f,
        77.f, -1.0f, 0.0f, // triangle 2 : end

    };

    int k = 0;
    GLfloat vertex_buffer_data3[9*n];
    for (int i = 0; i < n; i++) 
    {
        vertex_buffer_data3[k++] =  78.0f;
        vertex_buffer_data3[k++] = 0.0f;
        vertex_buffer_data3[k++] = 0.0f;
        
        vertex_buffer_data3[k++] =  78 + cos(i*theta) * 1.0f;
        vertex_buffer_data3[k++] = sin(i*theta) * 1.0f;
        vertex_buffer_data3[k++] = 0.0f;
        
        vertex_buffer_data3[k++] =  78 + cos((i+1)*theta) * 1.0f;
        vertex_buffer_data3[k++] = sin((i+1)*theta)  * 1.0f;
        vertex_buffer_data3[k++] = 0.0f;
    }

    

    this->object1 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data1, COLOR_BROWN, GL_FILL);

    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_ORANGE, GL_FILL);

    this->object3 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data3, COLOR_BROWN, GL_FILL);
}

void Beams::draw(glm::mat4 VP) {
    this->count++;
    if (this->count == 360)
    {
        this->count = 0;
        flag = 1;
    }
    if(this->count > 120)
        flag = 0;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    if (flag == 1)
        draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Beams::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Beams::tick() {
    this->position.x += 0.05;
    this->beams_bbox.x = this->position.x;
    this->beams_bbox.y = this->position.y;
    if(this->dir == 1)
    {
        this->position.y += 0.125;
    }
    else
    {
        this->position.y -= 0.125;
    }

    if(this->position.y == 40)
            this->dir = 0;

    if(this->position.y == 20)
            this->dir = 1;
}