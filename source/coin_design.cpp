#include "coin_design.h"
#include "main.h"

Coin_design::Coin_design(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.05;
    this->d=0;
    this->status=0;
    // this->speed = speed;
    // yspeed = 0;

    GLfloat vertex_buffer_data[1000]; 
    int sides = 50;
    float angle = (2*3.14159)/sides;

    for(int i =0; i < sides;i++)
    {
        vertex_buffer_data[9*i] = -0.1f;
        vertex_buffer_data[9*i + 1] = 0.1f;  
        vertex_buffer_data[9*i + 2] = 0.0f;
        vertex_buffer_data[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data[9*i + 4] = radius*sin(i*angle) ;
        vertex_buffer_data[9*i + 5] = 0.0f; 
        vertex_buffer_data[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data[9*i + 8] = 0.0f;
    }
    for(int i =50; i < 50+sides;i++)
    {
        vertex_buffer_data[9*i] = 0.1f;
        vertex_buffer_data[9*i + 1] = 0.1f;  
        vertex_buffer_data[9*i + 2] = 0.0f;
        vertex_buffer_data[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data[9*i + 4] = radius*sin(i*angle) ;
        vertex_buffer_data[9*i + 5] = 0.0f; 
        vertex_buffer_data[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data[9*i + 8] = 0.0f;
    }
    vertex_buffer_data[900] = 0.05f;
    vertex_buffer_data[901] = -0.1f;
    vertex_buffer_data[902] = 0.0f;
    vertex_buffer_data[903] = 0.05f;
    vertex_buffer_data[904] = -0.15f;
    vertex_buffer_data[905] = 0.0f;
    vertex_buffer_data[906] = -0.05f;
    vertex_buffer_data[907] = -0.1f;
    vertex_buffer_data[908] = 0.0f;

    vertex_buffer_data[909] = 0.05f;
    vertex_buffer_data[910] = -0.15f;
    vertex_buffer_data[911] = 0.0f;
    vertex_buffer_data[912] = -0.05f;
    vertex_buffer_data[913] = -0.1f;
    vertex_buffer_data[914] = 0.0f;
    vertex_buffer_data[915] = -0.05f;
    vertex_buffer_data[916] = -0.15f;
    vertex_buffer_data[917] = 0.0f;

    this->object = create3DObject(GL_TRIANGLES, 3*2*sides+6, vertex_buffer_data, color, GL_FILL);
}

void Coin_design::draw(glm::mat4 VP) {
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

void Coin_design::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin_design::set_value(int z) {
    this->status = 1;
}

void Coin_design::tick() {
    this->rotation += speed;
    // this->position.x -= this->speed;
    // this->position.y -= this->speed;
}
