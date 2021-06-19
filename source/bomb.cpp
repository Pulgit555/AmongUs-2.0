#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.2;
    this->d=0;
    this->status=0;
    // this->speed = speed;
    // yspeed = 0;

    GLfloat vertex_buffer_data[500]; 
    int sides = 50;
    float angle = (2*3.14159)/sides;

    for(int i =0; i < sides;i++)
    {
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i + 1] = 0.0f;  
        vertex_buffer_data[9*i + 2] = 0.0f;
        vertex_buffer_data[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data[9*i + 4] = radius*sin(i*angle) ;
        vertex_buffer_data[9*i + 5] = 0.0f; 
        vertex_buffer_data[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data[9*i + 8] = 0.0f;
    }
    vertex_buffer_data[450] = 0.05f;
    vertex_buffer_data[451] = 0.2f;
    vertex_buffer_data[452] = 0.0f;
    vertex_buffer_data[453] = -0.05f;
    vertex_buffer_data[454] = 0.2f;
    vertex_buffer_data[455] = 0.0f;
    vertex_buffer_data[456] = 0.05f;
    vertex_buffer_data[457] = 0.25f;
    vertex_buffer_data[458] = 0.0f;

    vertex_buffer_data[459] = -0.05f;
    vertex_buffer_data[460] = 0.2f;
    vertex_buffer_data[461] = 0.0f;
    vertex_buffer_data[462] = 0.05f;
    vertex_buffer_data[463] = 0.25f;
    vertex_buffer_data[464] = 0.0f;
    vertex_buffer_data[465] = -0.05f;
    vertex_buffer_data[466] = 0.25f;
    vertex_buffer_data[467] = 0.0f;

    this->object = create3DObject(GL_TRIANGLES, 3*sides+6, vertex_buffer_data, color, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
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

void Bomb::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Bomb::set_value(int z) {
    this->status = 1;
}

void Bomb::tick() {
    this->rotation += speed;
    // this->position.x -= this->speed;
    // this->position.y -= this->speed;
}

int Bomb::collision(Character character,Mirror mirror)
{
    float x = this->position.x;
    float y = this->position.y;
    float pl_x_min = character.position.x-0.2;
    float pl_x_max = character.position.x+0.25;
    float pl_y_min = character.position.y-0.5;
    float pl_y_max = character.position.y+0.2;
    if((x+0.2>=pl_x_min&&x+0.2<=pl_x_max)||(x-0.2>=pl_x_min&&x-0.2<=pl_x_max))
    {
        if((y+0.2>=pl_y_min&&y+0.2<=pl_y_max)||(y-0.2>=pl_y_min&&y-0.2<=pl_y_max))
        {
            this->status=1;
            return 1;
            // character.change_hel();
        }
    }
    return 0;
}