#include "main.h"
#include "character.h"
#include "mirror.h"
#include <vector>
using namespace std;

#ifndef WORLD_H
#define WORLD_H


class World {
public:
    World() {}
    World(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int detect_collision_l(Character character, Mirror mirror, Character imposter, Mirror im_mirror);
    int detect_collision_r(Character character, Mirror mirror, Character imposter, Mirror im_mirror);
    int detect_collision_u(Character character, Mirror mirror, Character imposter, Mirror im_mirror);
    int detect_collision_d(Character character, Mirror mirror, Character imposter, Mirror im_mirror);
    int enemy_collision(Character character, Character imposter);
    int movement(Character character, Character imposter);
    int exit_collision(Character character, Mirror mirror);
    double speed;
    vector <int> connected[100];//1->up,2->down,3->left,4->right.
    int light;
    int task;
    int button1;
    int button2;
    int finish;
    int power;
    int a[9][9];
    int b[9][9];
private:
    VAO *object;
};

#endif // WORLD_H
