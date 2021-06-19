#include "world.h"
#include "main.h"
#include <queue>
using namespace std;

World::World(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    this->light = 0;
    this->task = 2;
    this->button1 = 0;
    this->button2 = 0;
    this->finish =0;
    this->power =0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    for (int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            this->a[i][j]=0;
            this->b[i][j]=0;
        }
    }
    this->a[0][7]=1;
    int ac =0;
    int ab = rand()%3;
    float x1,x2,y1,y2;
    if(ab ==0)
    {
        x1= -4;
        x2= -3;
        y1= 3;
        y2= 3;
        this->b[0][1]=1;
        ac++;
    }
    else if(ab==1)
    {
        x1= -3;
        x2= -3;
        y1= 3;
        y2= 4;
        this->a[0][1]=1;
        ac++;
    }
    else
    {
        x1= -2;
        x2= -3;
        y1= 3;
        y2= 3;
        this->b[0][2]=1;
        ac++;
    }
    ab = rand()%2;
    float x3,x4,y3,y4,x5,x6,y5,y6,x7,x8,y7,y8,x9,x10,y9,y10,x11,x12,y11,y12;
    if(ab==0)
    {
        x3 = -1;
        x4 = -1;
        y3 = 2;
        y4 = 1;
        this->a[2][3]=1;
        ac++;
    }
    else
    {
        x3 = -1;
        x4 = -1;
        y3 = -2;
        y4 = -1;
        this->a[5][3]=1;
        ac++;
    }
    ab = rand()%2;
    if(ab==0)
    {
        x5 = 1;
        x6 = 1;
        y5 = -1;
        y6 = -2;
        this->a[5][5]=1;
        ac+=1;
    }
    else
    {
        x5 = 1;
        x6 = 1;
        y5 = 1;
        y6 = 2;
        this->a[2][5]=1;
        ac+=1;
    }
    ab = rand()%2;
    if(ab==0)
    {
        x7 = -2;
        x8 = -2;
        y7 = 0;
        y8 = 1;
        this->a[3][2]=1;
        ac+=1;
    }
    else
    {
        x7 = -2;
        x8 = -2;
        y7 = 0;
        y8 = -1;
        this->a[4][2]=1;
        ac+=1;
    }
    ab = rand()%2;
    if(ab==0)
    {
        x9 = 2;
        x10 = 2;
        y9 = 0;
        y10 = 1;
        this->a[3][6]=1;
        ac+=1;
    }
    else
    {
        x9 = 2;
        x10 = 2;
        y9 = 0;
        y10 = -1;
        this->a[4][6]=1;
        ac+=1;
    }
    ab = rand()%2;
    if(ab==0)
    {
        x11 = -3;
        x12 = -2;
        y11 = -3;
        y12 = -3;
        this->b[6][2]=1;
        ac+=1;
    }
    else
    {
        x11 = 0;
        x12 = 1;
        y11 = -3;
        y12 = -3;
        this->b[6][5]=1;
        ac+=1;
    }
    for(int i=1;i<=6;i++)
    {
        this->a[i][1] = 1;
        this->a[i][7] = 1;
        if(i!=3&&i!=4)
        {
            this->a[i][2] = 1;
            this->a[i][6] = 1;
        }
        else
        {
            this->a[i][3] = 1;
            this->a[i][5] = 1;
        }
        if(i<4)
        {
            this->a[i][4] = 1;
        }
    }
    this->a[0][6] = 1;
    this->a[0][3] = 1;
    this->a[0][4] = 1;
    this->a[7][5] = 1;
    this->b[0][3] = 1;this->b[0][6] = 1;
    this->b[4][8] = 1;this->b[6][3] = 1;
    this->b[6][4] = 1;this->b[6][6] = 1;
    for(int i=0;i<64;i++)
    {
        int x_,y_;
        x_= i/8;
        y_= i%8 + 1;
        if(x_>0)
        {
            if(this->b[x_-1][y_]==0)
            {
                this->connected[i].push_back((x_-1)*8+y_-1);
            }
        }
        if(x_<7)
        {
            if(this->b[x_][y_]==0)
            {
                this->connected[i].push_back((x_+1)*8+y_-1);
            }
        }
        if(y_>1)
        {
            if(this->a[x_][y_-1]==0)
            {
                this->connected[i].push_back((x_)*8+y_-1-1);
            }
        }
        if(y_<8)
        {
            if(this->a[x_][y_]==0)
            {
                this->connected[i].push_back((x_)*8+y_-1+1);
            }
        }
    }
    // for(int i=63;i<64;i++)
    // {
    //     for(int j=0;j<(int)connected[i].size();j++)
    //     {
    //         cout<<connected[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    static const GLfloat vertex_buffer_data[] = {
        -3.0f, 3.0f, 0.0f, //1
        -3.0f, -3.0f, 0.0f,

        -2.0f, 3.0f, 0.0f,//2
        -2.0f, 1.0f, 0.0f,

        -2.0f, -3.0f, 0.0f,//3
        -2.0f, -1.0f, 0.0f,

        -2.0f, 3.0f, 0.0f,//4
        -1.0f, 3.0f, 0.0f,

        -2.0f, -3.0f, 0.0f,//5
        0.0f, -3.0f, 0.0f,

        -1.0f, 1.0f, 0.0f,//6
        -1.0f, -1.0f, 0.0f,

        -1.0f, 4.0f, 0.0f,//7
        -1.0f, 3.0f, 0.0f,

        0.0f, 4.0f, 0.0f,//16
        0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 0.0f,//8
        1.0f, -1.0f, 0.0f,

        1.0f, -4.0f, 0.0f,//9
        1.0f, -3.0f, 0.0f,

        1.0f, -3.0f, 0.0f,//10
        2.0f, -3.0f, 0.0f,

        1.0f, 3.0f, 0.0f,//11
        2.0f, 3.0f, 0.0f,

        2.0f, 4.0f, 0.0f,//12
        2.0f, 1.0f, 0.0f,

        2.0f, -1.0f, 0.0f,//13
        2.0f, -3.0f, 0.0f,

        3.0f, 3.0f, 0.0f,//14
        3.0f, -3.0f, 0.0f,

        3.0f, -1.0f, 0.0f,//15
        4.0f, -1.0f, 0.0f,

        3.0f, 3.0f, 0.0f,//23
        4.0f, 3.0f, 0.0f,

        x1, y1, 0.0f,//17
        x2, y2, 0.0f,

        x3, y3, 0.0f,//18
        x4, y4, 0.0f,

        x5, y5, 0.0f,//19
        x6, y6, 0.0f,

        x7, y7, 0.0f,//20
        x8, y8, 0.0f,

        x9, y9, 0.0f,//21
        x10, y10, 0.0f,

        x11, y11, 0.0f,//22
        x12, y12, 0.0f
    };

    this->object = create3DObject(GL_LINES, 34+2*ac, vertex_buffer_data, color, GL_FILL);
}

void World::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void World::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

int World::detect_collision_l(Character character, Mirror mirror, Character imposter, Mirror im_mirror) {
    float x_value = character.position.x - 0.2 - 0.05;
    float y_value = character.position.y;
    if (x_value < -4)
        return 1;
    else
    {
        int d=0;
        int ii=-3;
        // for (int i=-3;i<=4;i++)
        if(this->button1 == 0)
        {
            if(x_value+0.25>=imposter.position.x+0.2&&x_value<=imposter.position.x+0.2)
            {
                if((y_value+0.2<=imposter.position.y+0.2&&y_value+0.2>=imposter.position.y-0.5)||(y_value-0.5<=imposter.position.y+0.2&&y_value+0.5>=imposter.position.y-0.5))
                {
                    // character.d = 1;
                    // std::cout<<"hey"<<std::endl;
                    return 2;
                }
            }
        }
        while(ii<=4)
        {
            if(x_value+0.25>=ii&&x_value<=ii)
            {
                d= 4+ii;
                break;
            }
            ii++;
        }
        // int d = 4.0 + x_value; 
        for (int i=0;i<8;i++)
        {
            if(this->a[i][int(d)]==1)
            {
                int e = 4-i;
                if((e>=y_value-0.5&&e<=y_value+0.2)||((e-1)>=y_value-0.5&&(e-1)<=y_value+0.2)||(e>=y_value+0.2&&(e-1)<=y_value-0.5)) 
                {
                    // std::cout<<x_value<<" "<<d<<" "<<e<<" "<<y_value<<std::endl;
                    return 1;
                }
            }
        }
        for(int i=0;i<8;i++)
        {
            if(this->b[i][int(d)]==1)
            {
                int e = 4-i-1;
                if((e>=y_value-0.5&&e<=y_value+0.2)) 
                {
                    // std::cout<<x_value<<" "<<d<<" "<<e<<" "<<y_value<<std::endl;
                    return 1;
                }
            }
        }
        return 0;
    }
}
int World::detect_collision_r(Character character, Mirror mirror, Character imposter, Mirror im_mirror) {
    float x_value = character.position.x + 0.25 + 0.05;
    float y_value = character.position.y;
    if (x_value > 4)
        return 1;
    else
    {
        int d=0;
        // for (int i=-3;i<=4;i++)
        int ii=-3;
        if(this->button1 == 0)
        {
            if(x_value-0.3<=imposter.position.x+0.25&&x_value>=imposter.position.x+0.25)
            {
                if((y_value+0.2<=imposter.position.y+0.2&&y_value+0.2>=imposter.position.y-0.5)||(y_value-0.5<=imposter.position.y+0.2&&y_value+0.5>=imposter.position.y-0.5))
                {
                    // character.d = 1;
                    // std::cout<<"hey"<<std::endl;
                    return 2;
                }
            }
        }
        while(ii<=4)
        {
            if(x_value-0.3<=ii&&x_value>=ii)
            {
                d= 4+ii;
                break;
            }
            ii++;
        }
        // int d = 4.0 + x_value; 
        for (int i=0;i<8;i++)
        {
            if(this->a[i][int(d)]==1)
            {
                int e = 4-i;
                if((e>=y_value-0.5&&e<=y_value+0.2)||((e-1)>=y_value-0.5&&(e-1)<=y_value+0.2)||(e>=y_value+0.2&&(e-1)<=y_value-0.5)) 
                {
                    // std::cout<<x_value<<" "<<d<<" "<<e<<" "<<y_value<<std::endl;
                    return 1;
                }
            }
        }
        for(int i=0;i<8;i++)
        {
            if(this->b[i][int(d)+1]==1)
            {
                int e = 4-i-1;
                if((e>=y_value-0.5&&e<=y_value+0.2)) 
                {
                    // std::cout<<x_value<<" "<<d<<" "<<e<<" "<<y_value<<std::endl;
                    return 1;
                }
            }
        }
        return 0;
    }
}
int World::detect_collision_u(Character character, Mirror mirror, Character imposter, Mirror im_mirror) {
    float x_value = character.position.x;
    float y_value = character.position.y +0.2 +0.05;
    if (y_value > 4)
    {
        return 1;
    }
    else
    {
        int d=8;
        // for (int i=-3;i<=4;i++)
        if(this->button1 == 0)
        {
            if(y_value-0.25<=imposter.position.y-0.5&&y_value>=imposter.position.y-0.5)
            {
                if((x_value+0.25<=imposter.position.x+0.2&&x_value+0.25>=imposter.position.x-0.25)||(x_value-0.2<=imposter.position.x+0.2&&x_value-0.2>=imposter.position.x-0.25))
                {
                    return 2;
                }
            }
        }
        int ii=-4;
        while(ii<=3)
        {
            if(y_value-0.25<=ii&&y_value>=ii)
            {
                d= 4-ii-1;
                break;
            }
            ii++;
        }
        // int d = 4.0 + x_value; 
        for (int i=1;i<=8;i++)
        {
            if(this->b[int(d)][i]==1)
            {
                int e = i-4;
                if((e>=x_value-0.2&&e<=x_value+0.25)||((e-1)>=x_value-0.2&&(e-1)<=x_value+0.25)||(e>=x_value+0.25&&(e-1)<=x_value-0.2)) 
                {
                    // std::cout<<y_value<<" "<<d<<" "<<e<<" "<<x_value<<std::endl;
                    return 1;
                }
            }
        }
        for(int i=1;i<=8;i++)
        {
            if(this->a[int(d)][i]==1)
            {
                int e = i-4;
                if((e>=x_value-0.2&&e<=x_value+0.25)) 
                {
                    // std::cout<<y_value<<" "<<d<<" "<<e<<" "<<x_value<<std::endl;
                    return 1;
                }
            }
        }
        return 0;
    }
}
int World::detect_collision_d(Character character, Mirror mirror, Character imposter, Mirror im_mirror) {
    float x_value = character.position.x;
    float y_value = character.position.y -0.5 -0.05;
    if (y_value < -4)
    {
        return 1;
    }
    else
    {
        int d=8;
        // for (int i=-3;i<=4;i++)
        int ii=-4;
        if(this->button1 == 0)
        {
            if(y_value+0.55>=imposter.position.y+0.2&&y_value<=imposter.position.y+0.2)
            {
                if((x_value+0.25<=imposter.position.x+0.2&&x_value+0.25>=imposter.position.x-0.25)||(x_value-0.2<=imposter.position.x+0.2&&x_value-0.2>=imposter.position.x-0.25))
                {
                    return 2;
                }
            }
        }
        while(ii<=3)
        {
            if(y_value+0.55>=ii&&y_value<=ii)
            {
                d= 4-ii-1;
                break;
            }
            ii++;
        }
        // int d = 4.0 + x_value; 
        for (int i=1;i<=8;i++)
        {
            if(this->b[int(d)][i]==1)
            {
                int e = i-4;
                if((e>=x_value-0.2&&e<=x_value+0.25)||((e-1)>=x_value-0.2&&(e-1)<=x_value+0.25)||(e>=x_value+0.25&&(e-1)<=x_value-0.2)) 
                {
                    // std::cout<<y_value<<" "<<d<<" "<<e<<" "<<x_value<<std::endl;
                    return 1;
                }
            }
        }
        for(int i=1;i<=8;i++)
        {
            if(this->a[int(d)+1][i]==1)
            {
                int e = i-4;
                if((e>=x_value-0.2&&e<=x_value+0.25)) 
                {
                    // std::cout<<y_value<<" "<<d<<" "<<e<<" "<<x_value<<std::endl;
                    return 1;
                }
            }
        }
        return 0;
    }
}
int World::exit_collision(Character character, Mirror mirror)
{
    float x_value = character.position.x + 0.25 + 0.05;
    float y_value = character.position.y;
    if (x_value > 4)
    {
        if((y_value+0.2<=4&&y_value+0.2>=3)||(y_value-0.5<=4&&y_value-0.5>=3))
        {
            return 1;
        }
    }
    return 0;
}
void World::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

int World::movement(Character character, Character imposter)
{
    int abc,dist[64],visited[64],parent[64];
    queue <int>array;
    int ii=-3,d,e,f,g,dest;
    while(ii<=4)
    {
        if(imposter.position.y<=ii&&imposter.position.y>=ii-1)
        {
            d= 4-ii;
            break;
        }
        ii++;
    }
    ii=-3;
    while(ii<=4)
    {
        if(imposter.position.x<=ii&&imposter.position.x>=ii-1)
        {
            e= 4+ii;
            break;
        }
        ii++;
    }
    ii=-3;
    while(ii<=4)
    {
        if(character.position.y<=ii&&character.position.y>=ii-1)
        {
            f= 4-ii;
            break;
        }
        ii++;
    }
    ii=-3;
    while(ii<=4)
    {
        if(character.position.x<=ii&&character.position.x>=ii-1)
        {
            g= 4+ii;
            break;
        }
        ii++;
    }
    abc = 8*d+e-1;
    dest = 8*f+g-1;
    // cout<<imposter.position.y<<" "<<d<<" "<<e<<endl;
    // cout<<abc<<" "<<dest<<endl;
    array.push(abc);
    for(int i=0;i<64;i++)
    {
        dist[i]=0;
        visited[i]=0;
        parent[i]=i;
    }
    while(array.empty()==0)
	{
		int p=array.front();
		array.pop();
		visited[p]=1;
		for(int j=0;j<(int)this->connected[p].size();j++)
		{
			int q=connected[p][j];
			if(visited[q]==1)
				continue;
			if(visited[q]==0)
			{
				dist[q]=dist[p]+1;
				array.push(q);
				visited[q]=1;
                parent[q]=p;
			}
        }
	}
    int ad = dest,cd=ad;
    while(parent[ad]!=ad)
    {
        cd=ad;
        ad=parent[ad];
    }
    // cout<<cd<<endl;
    if(cd==abc+1)
    {
        return 4;
    }
    else if(cd==abc-1)
    {
        return 3;
    }
    else if(cd>abc)
    {
        return 2;
    }   
    else
    {
        return 1;
    }
}

int World::enemy_collision(Character character, Character imposter)
{
    float pl_minx = character.position.x-0.2;
    float pl_maxx = character.position.x+0.25;
    float pl_miny = character.position.y-0.5;
    float pl_maxy = character.position.y+0.2;
    float im_minx = imposter.position.x-0.25;
    float im_maxx = imposter.position.x+0.2;
    float im_miny = imposter.position.y - 0.5;
    float im_maxy = imposter.position.y +0.2;
    if((pl_minx<=im_maxx&&pl_minx>=im_minx)||(pl_maxx<=im_maxx&&pl_maxx>=im_minx))
    {
        if((pl_miny<=im_maxy&&pl_miny>=im_miny)||(pl_maxy<=im_maxy&&pl_maxy>=im_miny))
        {
            return 2;
        }
    } 
    return 0;
}