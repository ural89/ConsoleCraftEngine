#include <vector>
#include "RopeParticle.h"
#include "Core/Scene.h"
#include <string>
class Softbody
{
public:
    struct Vector
    {
        float x;
        float y;
    };
    double magnitude(Vector a)
    {
        double m = sqrt(a.x * a.x + a.y * a.y);
        return m;
    }
    Vector unit(Vector a)
    {
        Vector b;
        double m = magnitude(a);
        if (m == 0)
            return {0, 0};
        b.x = a.x / m;
        b.y = a.y / m;
        return b;
    }
    double dot(Vector a, Vector b)
    {
        double d = a.x * b.x + a.y * b.y;
        return d;
    }
    ~Softbody()
    {
        particles.clear();
    }
    Softbody(float restitution, float spring_constant, float damping, Scene &scene)
    {
        this->scene = &scene;
        e = restitution;
        k = spring_constant;
        c = damping;
    }
    void appendPoint(int x, int y)
    {
        Vector newVertex = {x, y};
        soft_body.push_back(newVertex);
        Vector zero = {0, 0};
        velocity.push_back(zero);
        force.push_back(zero);
        auto particle = new RopeParticle(*scene);
        particles.push_back(particle);
        scene->AddGameObject(new RopeParticle(*scene), Vector2(x, y));
        for (int i = 0; i < soft_body.size(); ++i)
        {
            for (int j = 0; j < soft_body.size(); ++j)
            {
                if (i != j)
                {
                    Vector d = {(soft_body[j].x - soft_body[i].x) / 100.f, (soft_body[j].y - soft_body[i].y) / 100.f};
                    sprlen[i < j ? i : j][i < j ? j : i] = magnitude(d);
                }
            }
        }
    }
    void acceleratePoints()
    {
        std::vector<Vector> soft_body_copy = soft_body;
        std::vector<Vector> velocity_copy = velocity;
        // Vector centroid_copy=centroid;
        // Vector cv_copy=cv;
        for (int i = 0; i < soft_body.size(); ++i)
        {
            force[i] = {0, 0};
            for (int j = 0; j < soft_body.size(); ++j)
            {
                if (j != i) // j==i-1||j==i+1||(j==soft_body.size()-1&&i==0)||(i==soft_body.size()-1&&j==0))
                {
                    Vector d = {(soft_body[j].x - soft_body[i].x) / 100.f, (soft_body[j].y - soft_body[i].y) / 100.f};
                    if (magnitude(d) != 0)
                    {
                        float t = atan2(d.y, d.x);
                        float m = magnitude(d);
                        float disp = m - sprlen[i < j ? i : j][i < j ? j : i];
                        Vector anew = {(k * disp * cos(t)) / 10000.f, (k * disp * sin(t)) / 10000.f};
                        force[i].x += anew.x;
                        force[i].y += anew.y;
                        force[i].x -= c * magnitude(d) * (velocity[i].x - velocity[j].x) / 100.f;
                        force[i].y -= c * magnitude(d) * (velocity[i].y - velocity[j].y) / 100.f;
                         //std::cout<<c*unit(d).x*(velocity[i].x-velocity[j].x)/100.f<<std::endl;
                    }
                }
            }
            velocity_copy[i].x += force[i].x;
            velocity_copy[i].y += force[i].y + 1.098;
           
            soft_body_copy[i].x += velocity_copy[i].x;
            soft_body_copy[i].y += velocity_copy[i].y;
        }
        soft_body = soft_body_copy;
        velocity = velocity_copy;
        std::cout << std::to_string(velocity[0].y);
    }
    void checkCollision()
    {
        for (int k = 0; k < soft_body.size(); ++k)
        {
            if (soft_body[k].x >= SCREENWIDTH - 1 || soft_body[k].x <= 0)
            {
                velocity[k].x *= -e;
                soft_body[k].x = soft_body[k].x > SCREENWIDTH / 2 ? SCREENWIDTH - 1 : 1;
                
            }
            if (soft_body[k].y >= SCREENHEIGHT - 1 || soft_body[k].y <= 0)
            {
                velocity[k].y *= -e;
                soft_body[k].y = soft_body[k].y > SCREENHEIGHT / 2 ? SCREENHEIGHT - 1 : 1;
            }
        }
        /*if(cv.x>=SCREENWIDTH-1||cv.x<=0)
        {
            cv.x*=-e;
                //soft_body[k].x=soft_body[k].x>SCREENWIDTH/2?SCREENWIDTH-1:1;
        }
        if(cv.y>=SCREENHEIGHT-1||cv.y<=0)
        {
            cv.y*=-e;
                //soft_body[k].y=soft_body[k].y>SCREENHEIGHT/2?SCREENHEIGHT-1:1;
        }*/
    }
    void drag(int x, int y)
    {
        Vector mouse = {x - soft_body[0].x, y - soft_body[0].y};
        mouse = unit(mouse);
        for (int q = 0; q < 1; ++q)
        {
            Vector d = {soft_body[q].x - mouse.x, soft_body[q].y - mouse.y};
            d = unit(d);
            velocity[q].x += 2 * mouse.x; //+fabs(d.x/10);
            velocity[q].y += 2 * mouse.y; //+fabs(d.y/10);
        }
    }
    void DrawBody()
    {
        //[0]->transform.MovePosition(30, 30);
         //std::cout<< std::to_string(particles[0]->transform.Position.X);
        // for (int z = 0; z < soft_body.size(); ++z)
        // {
        //     std::cout<< std::to_string(soft_body[0].x* 5);
        //   //  particles[z]->transform.MovePosition(soft_body[z].x * 5, soft_body[z].y * 5);
        // }
    }
    // void drawBody(Display &display, SDL_Color c, SDL_Color d)
    // {
    //     for (int z = 0; z < soft_body.size(); ++z)
    //     {
    //         display.renderTexture(soft_body[z].x, soft_body[z].y);
    //         display.drawLine(soft_body[z], soft_body[(z + 1) % soft_body.size()], c);
    //     }
    //     /*display.renderTexture(centroid.x,centroid.y);
    //     for(int r=0;r<soft_body.size();++r)
    //     {
    //         display.drawLine(centroid,soft_body[r],d);
    //     }*/
    // }
    Vector returnDrag()
    {
        return (soft_body[0]);
    }

    std::vector<Vector> soft_body;

private:
    std::vector<Vector> velocity;
    std::vector<Vector> force;
    std::vector<RopeParticle *> particles;
    float sprlen[200][200];
    // Vector centroid;
    // Vector cv;
    // float natural_length=50;
    Scene *scene;
    float e;
    float k;
    float c;
};
