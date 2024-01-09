#pragma once
#include <vector>
#include <math.h>
#include "RopeParticle.h"
#include "../Scene.h"
#include "../../CoreStructs/Vector.h"
float const GRAVITY = 9.81; 
float const TIMESTEP = 0.01;
unsigned const JAKOBSEN_ITERATIONS = 50;

class Rope
{
public:
    Rope(float x1, float y1, float x2, float y2, unsigned nParticles, Scene &scene)
    {
        for (unsigned i = 0; i < nParticles; i++)
        {

            float w = (float)i / (nParticles - 1);

            float x = w * x2 + (1 - w) * x1;
            float y = w * y2 + (1 - w) * y1;

            auto particle = new RopeParticle(scene);
            particle->isFixed = i == 0; // || i == nParticles-1;

            scene.AddGameObject(particle, Vector2(x, y));
            particle->transform.RopePreviousPosition = Vector2(x, y);

            _particles.push_back(particle);
        }

      
        unsigned numberOfSegments = nParticles - 1;
        float ropeLength = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

        _desiredDistance = ropeLength / numberOfSegments;
    }
    void step(float deltaTime)
    {
        verletIntegration(deltaTime);
        enforceConstraints();
    }

    std::vector<RopeParticle *> _particles;
    void MoveFirstParticle(float deltaTime, Vector2 targetPosition)
    {
        Vector2 moveDirection = targetPosition -_particles[0]->transform.Position;
        moveDirection.Normalize();
        moveDirection = moveDirection * deltaTime * 8;
        _particles[0]->transform.MovePosition(moveDirection.X, moveDirection.Y);
        //_particles[_particles.size()-1]->transform.MovePosition(-deltaTime, 0);
    }
    GameObject &GetFirstParticle()
    {
        return *_particles[0];
    }

private:



    float _desiredDistance;
    void verletIntegration(float deltaTime)
    {
        for (auto &p : _particles)
        {
            if (p->isFixed)
                continue; 

            float xCopy = p->transform.Position.X;
            float yCopy = p->transform.Position.Y;

     
            float velocityX = p->transform.Position.X - p->transform.RopePreviousPosition.X;
            float velocityY = p->transform.Position.Y - p->transform.RopePreviousPosition.Y;

   
            velocityX *= 0.9998f;
            velocityY *= 0.9998f;


            p->transform.SetPosition( p->transform.Position.X + velocityX +  deltaTime * deltaTime, 
            p->transform.Position.Y + velocityY + GRAVITY * deltaTime * deltaTime);


            p->transform.RopePreviousPosition.X = xCopy;
            p->transform.RopePreviousPosition.Y = yCopy;
        }
    }
    void enforceConstraints()
    {
       
        for (unsigned iteration = 0; iteration < JAKOBSEN_ITERATIONS; iteration++)
        {

            for (size_t i = 1; i < _particles.size(); i++)
            {
                auto &p1 = _particles[i - 1];
                auto &p2 = _particles[i];

   
                float distance = Vector2::Distance(p1->transform.Position, p2->transform.Position); //(pow(p1->transform.Position.X - p2->transform.Position.X, 2) + pow(p1->transform.Position.Y - p2->transform.Position.Y, 2));
                float distanceError = distance - _desiredDistance;

                float xDifference = p2->transform.Position.X - p1->transform.Position.X;
                float yDifference = p2->transform.Position.Y - p1->transform.Position.Y;

      
                float xDirection = xDifference / sqrt(pow(xDifference, 2) + pow(yDifference, 2));
                float yDirection = yDifference / sqrt(pow(xDifference, 2) + pow(yDifference, 2));


                if (p1->isFixed && !p2->isFixed)
                {
                    p2->transform.Position.X -= xDirection * distanceError;
                    p2->transform.Position.Y -= yDirection * distanceError;
                }
                else if (p2->isFixed && !p1->isFixed)
                {
                    p1->transform.Position.X += xDirection * distanceError;
                    p1->transform.Position.Y += yDirection * distanceError;
                }
                else if (!p1->isFixed && !p2->isFixed)
                {
                    p2->transform.Position.X -= 0.5 * xDirection * distanceError;
                    p2->transform.Position.Y -= 0.5 * yDirection * distanceError;
                    p1->transform.Position.X += 0.5 * xDirection * distanceError;
                    p1->transform.Position.Y += 0.5 * yDirection * distanceError;
                }
            }
        }
    }
};
