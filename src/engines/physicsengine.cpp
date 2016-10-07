#include "physicsengine.h"

#include<game.h>

using namespace BQ;

PhysicsEngine::PhysicsEngine()
{
    placeholder = "auto_phys_";
    grav = 1;
}

void PhysicsEngine::wake()
{

}

void PhysicsEngine::start()
{

}

void PhysicsEngine::run()
{
    GameObjectStore & os = game->getCurrentLevel().objects;

    for(int i=0; i<collisions.size(); i++)
    {
        PhysicalExchange & p = collisions[i];

        if(p.rigidBodyA >=0 && p.rigidBodyB >=0)
        {
            RigidBody & rA = os.rigidBodies[p.rigidBodyA];
            RigidBody & rB = os.rigidBodies[p.rigidBodyB];
            //two bodies involved
            resolveTwoBodyCollision(rA,rB);
        }
        else if(p.rigidBodyA >=0)
        {
            //one body and a solid non-physical wall
            RigidBody & rA = os.rigidBodies[p.rigidBodyA];
            resolveReflection(rA,p.reflectionAxis);
        }
        else if(p.rigidBodyB >=0)
        {
            //one body and a solid non-physical wall
            RigidBody & rB = os.rigidBodies[p.rigidBodyB];
            resolveReflection(rB,p.reflectionAxis);
        }

    }
    for(unsigned int j=0; j<activeComponents.size(); j++)
    {
        int i = activeComponents[j];
        RigidBody& r = os.rigidBodies[i];
        componentLoader->getTransform(r.transform).velocity += (r.getInvmass()*r.momentum);
        if(r.friction > 1E-12) //floating point inprecision check
        {
            float fric = delta*r.friction*r.getMass()*grav;

            float mMom = maths->mag(r.momentum);
            if(fric > mMom && mMom > 0)
            {
               sf::Vector2f uMom = maths->unit(r.momentum);
               r.momentum -= fric*uMom;
            }
            else
            {
                r.momentum.x = 0;
                r.momentum.y = 0;
            }
        }
    }

}

void PhysicsEngine::finish()
{
    collisions.clear();
}

void PhysicsEngine::addCollision(const PhysicalExchange & c)
{
    collisions.push_back(c);
}

void PhysicsEngine::resolveTwoBodyCollision(RigidBody & rA, RigidBody & rB)
{
    sf::Vector2f mA = rA.momentum;
    sf::Vector2f mB = rB.momentum;
    sf::Vector2f vA = rA.getInvmass()*rA.momentum;
    sf::Vector2f vB = rB.getInvmass()*rB.momentum;
    float massA = rA.getMass();
    float massB = rB.getMass();
    float restA =rA.restitution*rB.restitution*massB;
    float restB = rB.restitution*rA.restitution*massA;

    sf::Vector2f tA1 = (mA + mB);
    sf::Vector2f tA2 = restA*(vB - vA);

    sf::Vector2f tB1 = (mA + mB);
    sf::Vector2f tB2 = restB*(vA - vB);

    sf::Vector2f pA = componentLoader->getTransform(rA.transform).position;
    sf::Vector2f pB = componentLoader->getTransform(rA.transform).position;

    sf::Vector2f diff = pA-pB;

    rA.momentum = (massA/(massA + massB))*(tA1+tA2);
    rB.momentum = (massB/(massA + massB))*(tB1+tB2);

}

void PhysicsEngine::resolveReflection(RigidBody & rA, sf::Vector2f axis)
{
    sf::Vector2f dir = maths->unit((maths->dot(rA.momentum,axis)*(rA.momentum - axis)));
    sf::Vector2f newDir = maths->mag(rA.momentum)*dir;
    if (fabs(axis.x) > fabs(axis.y))
    {
       rA.momentum.x = rA.restitution*newDir.x;
       rA.momentum.y = rA.restitution*rA.momentum.y;
    }
    else if (fabs(axis.y) > fabs(axis.x))
    {
        rA.momentum.x = rA.restitution*rA.momentum.x;
        rA.momentum.y = rA.restitution*newDir.y;
    }
    else
    {
        rA.momentum.x = rA.restitution*newDir.x;
        rA.momentum.y = rA.restitution*newDir.y;
    }
}
