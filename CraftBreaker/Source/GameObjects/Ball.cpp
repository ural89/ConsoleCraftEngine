#include "Ball.h"

void Ball::Update(float deltaTime)
{
	collideTimer += deltaTime;
	transform.MovePosition(velocity.X * deltaTime, velocity.Y * deltaTime);
	if (transform.Position.X >= (SCREENWIDTH / 2.5f) - 1 || transform.Position.X <= 1)
	{
		velocity.X *= -1;
	}
	if (transform.Position.Y >= SCREENHEIGHT -1|| transform.Position.Y <= 1)
	{
		velocity.Y *= -1;
	}

}

void Ball::OnCollided(const GameObject& other)
{
    if(other.name == "Particle") return;
    if(collideTimer < 0.5f)
    {
        return;
    }
    collideTimer = 0;
    if(other.name == "Breaker") 
    {
        if(other.transform.Position.Y - transform.Position.Y > 0)
        {
            if(other.transform.Position.X - transform.Position.X > 0) //ball is on the left 
            {
       
                velocity.X -= 2;
                velocity.Y *= -1;
                std::cout << velocity.X << '\n';
                return;
            }
            else
            {
              std::cout << "sdsadsa" << '\n';//TODO: fix always right
                velocity.X += 2;
                velocity.Y *= -1;
                return;
            }
        }
    }
    else
	//Destroy();
	{
        velocity.X *= -1;
	velocity.Y *= -1;
    }
}
