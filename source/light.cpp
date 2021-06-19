#include "light.h"
#include "main.h"

Light::Light(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.2;
    this->d=0;
    this->status=0;
    // this->speed = speed;
    // yspeed = 0;

    static const GLfloat vertex_buffer_data[] = {
        x-8, y+8, 0.0f,//1
        x+8, y+8, 0.0f,
        x+8, y+0.5f, 0.0f,

        x-8, y+8, 0.0f,//2
        x+8, y+0.5f, 0.0f,
        x-8, y+0.5f, 0.0f,

        x+8, y-8, 0.0f,//3
        x+8, y-0.5f, 0.0f,
        x-8, y-0.5f, 0.0f,

        x+8, y-8, 0.0f,//4
        x-8, y-8, 0.0f,
        x-8, y-0.5f, 0.0f,

        x+8, y-8, 0.0f,//5
        x+8, y+8, 0.0f,
        x+0.5f, y+8, 0.0f,

        x+8, y-8, 0.0f,//6
        x+0.5f, y+8, 0.0f,
        x+0.5f, y-8, 0.0f,

        x-8, y+8, 0.0f,//7
        x-0.5f, y+8, 0.0f,
        x-0.5f, y-8, 0.0f,

        x-8, y+8, 0.0f,//8
        x-8, y-8, 0.0f,
        x-0.5f, y-8, 0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 3*8, vertex_buffer_data, color, GL_FILL);
}

void Light::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Light::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
