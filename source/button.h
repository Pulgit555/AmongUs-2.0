#include "main.h"
#include "mirror.h"

#ifndef BUTTON_H
#define BUTTON_H


class Button {
public:
    Button() {}
    Button(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    int collision(Mirror mirror); 
    void set_value(int z);
    void tick();
    double speed;
    double radius;
    int status;
    int d;
private:
    VAO *object;
};

#endif // coins_H
