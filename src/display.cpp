#include "display.h"
#include "main.h"
#include <math.h>
using namespace std;

Display::Display(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->number = 0;
    this->rotation = 0;
    static GLfloat vertex_buffer_data1[] = {
        -0.8f, -0.2f, 0.0f,
        -0.8f,  0.2f, 0.0f,
         0.8f,  0.2f, 0.0f,
         0.8f,  0.2f, 0.0f,
        -0.8f, -0.2f, 0.0f,
         0.8,  -0.2f, 0.0f,
    };
    static GLfloat vertex_buffer_data2[] = {
        -0.8f, -0.2f+2.0f, 0.0f,
        -0.8f,  0.2f+2.0f, 0.0f,
         0.8f,  0.2f+2.0f, 0.0f,
         0.8f,  0.2f+2.0f, 0.0f,
        -0.8f, -0.2f+2.0f, 0.0f,
         0.8,  -0.2f+2.0f, 0.0f,
    };
    static GLfloat vertex_buffer_data3[] = {
        -0.8f, -0.2f-2.0f, 0.0f,
        -0.8f,  0.2f-2.0f, 0.0f,
         0.8f,  0.2f-2.0f, 0.0f,
         0.8f,  0.2f-2.0f, 0.0f,
        -0.8f, -0.2f-2.0f, 0.0f,
         0.8,  -0.2f-2.0f, 0.0f,
    };
    static GLfloat vertex_buffer_data4[] = {
        -0.2f-1.1f, -0.8f+1.0f, 0.0f,
         0.2f-1.1f, -0.8f+1.0f, 0.0f,
         0.2f-1.1f,  0.8f+1.0f, 0.0f,
         0.2f-1.1f,  0.8f+1.0f, 0.0f,
        -0.2f-1.1f, -0.8f+1.0f, 0.0f,
        -0.2f-1.1f,  0.8f+1.0f,  0.0f,
    };
    static GLfloat vertex_buffer_data5[] = {
        -0.2f+1.1f, -0.8f+1.0f, 0.0f,
         0.2f+1.1f, -0.8f+1.0f, 0.0f,
         0.2f+1.1f,  0.8f+1.0f, 0.0f,
         0.2f+1.1f,  0.8f+1.0f, 0.0f,
        -0.2f+1.1f, -0.8f+1.0f, 0.0f,
        -0.2f+1.1f,  0.8f+1.0f,  0.0f,
    };
    static GLfloat vertex_buffer_data6[] = {
        -0.2f-1.1f, -0.8f-1.0f, 0.0f,
         0.2f-1.1f, -0.8f-1.0f, 0.0f,
         0.2f-1.1f,  0.8f-1.0f, 0.0f,
         0.2f-1.1f,  0.8f-1.0f, 0.0f,
        -0.2f-1.1f, -0.8f-1.0f, 0.0f,
        -0.2f-1.1f,  0.8f-1.0f,  0.0f,
    };
    static GLfloat vertex_buffer_data7[] = {
        -0.2f+1.1f, -0.8f-1.0f, 0.0f,
         0.2f+1.1f, -0.8f-1.0f, 0.0f,
         0.2f+1.1f,  0.8f-1.0f, 0.0f,
         0.2f+1.1f,  0.8f-1.0f, 0.0f,
        -0.2f+1.1f, -0.8f-1.0f, 0.0f,
        -0.2f+1.1f,  0.8f-1.0f,  0.0f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data3, color, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data4, color, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data5, color, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data6, color, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data7, color, GL_FILL);

}

void Display::draw(glm::mat4 VP) {
    // printf("draw display\n");
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->number==2||this->number==3||this->number==4||this->number==5||this->number==6||this->number==8||this->number==9)
        draw3DObject(this->object1);
    if(this->number==0||this->number==2||this->number==3||this->number==5||this->number==6||this->number==7||this->number==8||this->number==9)
        draw3DObject(this->object2);
    if(this->number==0||this->number==2||this->number==3||this->number==5||this->number==6||this->number==8||this->number==9)
        draw3DObject(this->object3);
    if(this->number==0||this->number==4||this->number==5||this->number==6||this->number==8||this->number==9)
        draw3DObject(this->object4);
    if(this->number==0||this->number==1||this->number==2||this->number==3||this->number==4||this->number==7||this->number==8||this->number==9)
        draw3DObject(this->object5);
    if(this->number==0||this->number==2||this->number==6||this->number==8)
        draw3DObject(this->object6);
    if(this->number==0||this->number==1||this->number==3||this->number==4||this->number==5||this->number==6||this->number==7||this->number==8||this->number==9)
        draw3DObject(this->object7);
}

void Display::set_position(float x, float y) {
    // printf("set position display\n");
    this->position = glm::vec3(x, y, 0);
}

void Display::tick() {
    this->position.x += 0.05;
}