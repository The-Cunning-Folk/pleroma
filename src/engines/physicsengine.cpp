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
        PhysicalCollision & p = collisions[i];


            RigidBody & rA = os.rigidBodies[p.rigidBodyA];
            RigidBody & rB = os.rigidBodies[p.rigidBodyB];

            //do momentum transfer here

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

            if(maths->dot(pA-pB,mA) > 0.0){
            rA.momentum = (massA/(massA + massB))*(tA1+tA2);
            }

            if(maths->dot(pB-pA,mB) > 0.0){
            rB.momentum = (massB/(massA + massB))*(tB1+tB2);
            }

    }
    for(unsigned int j=0; j<activeComponents.size(); j++)
    {
        int i = activeComponents[j];
        RigidBody& r = os.rigidBodies[i];
        componentLoader->getTransform(r.transform).setVelocity(r.getInvmass()*r.momentum);
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
    collisions.clear();
}

void PhysicsEngine::finish()
{

}

void PhysicsEngine::addCollision(const PhysicalCollision & c)
{
    collisions.push_back(c);
}
