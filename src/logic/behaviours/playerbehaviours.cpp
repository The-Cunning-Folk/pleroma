#include "playerbehaviours.h"

#include <gameobject.h>
#include <game.h>

using namespace BQ;

PlayerBehaviours::PlayerBehaviours()
{
    baseSpeed = 100.0;
    facing = "d";

    //roll properties

    startRoll = false;
    rolling = false;
    rollCooled = true;
    rollDuration = 0.5;
    rollCooldown = 0.5;
    rollBoost = 2.5;

    //set the attack area polygons

    attackScaleFactor = 0.5F;

    ConvexPolygon c;

    c.addPoint(10,8);
    c.addPoint(25,20);
    c.addPoint(20,30);
    c.addPoint(6,12);


    attackFrames.push_back(c);
    c.clearPoints();

    c.addPoint(12,0);
    c.addPoint(30,0);
    c.addPoint(25,20);
    c.addPoint(10,8);

    attackFrames.push_back(c);
    c.clearPoints();

    c.addPoint(10,-8);
    c.addPoint(25,-20);
    c.addPoint(30,0);
    c.addPoint(12,0);

    attackFrames.push_back(c);
    c.clearPoints();

    c.addPoint(6,-12);
    c.addPoint(20,-30);
    c.addPoint(25,-20);
    c.addPoint(10,-8);

    attackFrames.push_back(c);
    c.clearPoints();






    //set the attack properties

    attackDuration = 0.5;
    attackCooldown = 0.05;
    startAttack = false;
    attackCooled = false;
    attacking = false;
    attackMom = 2000;
}

std::string PlayerBehaviours::getFacing(float dx, float dy)
{
    direction.x = dx;
    direction.y = dy;
    if(direction.x == 0) {
        if(direction.y < 0){
            facing = "u";
        }
        else if (direction.y > 0)
        {
            facing = "d";
        }
    }
    else
    {
        float dirRatio = direction.y/direction.x;
        float absRatio = fabs(dirRatio);

        if(absRatio <= 0.41)
        {
            if(direction.x > 0)
            {
                facing = "r";
            }
            else
            {
                facing = "l";
            }
        }
        else if(absRatio > 0.41 && absRatio <= 2.41)
        {
            facing = "";

            if(direction.y > 0)
            {
                facing += "d";
            }
            else
            {
                facing += "u";
            }

            if(direction.x > 0)
            {
                facing += "r";
            }
            else
            {
                facing += "l";
            }
        }
    }
    return facing;
}

sf::Vector2f PlayerBehaviours::getOctDirection()
{
    sf::Vector2f octDir;
    if(compare(facing,"l"))
    {
        octDir = sf::Vector2f(-1,0);
    }
    else if(compare(facing,"ul"))
    {
        octDir = sf::Vector2f(-1,-1);
    }
    else if(compare(facing,"u"))
    {
        octDir = sf::Vector2f(0,-1);
    }
    else if(compare(facing,"ur"))
    {
        octDir = sf::Vector2f(1,-1);
    }
    else if(compare(facing,"r"))
    {
        octDir = sf::Vector2f(1,0);
    }
    else if(compare(facing,"dr"))
    {
        octDir = sf::Vector2f(1,1);
    }
    else if(compare(facing,"d"))
    {
        octDir = sf::Vector2f(0,1);
    }
    else if(compare(facing,"dl"))
    {
        octDir = sf::Vector2f(-1,1);
    }
    octDir = game->math.unit(octDir);
    return octDir;
}

void PlayerBehaviours::checkInputLogic()
{
    if(startRoll && !attacking)
    {
        rolling = true;
        startRoll = false;
        rollDirection = game->math.mag(direction) > 0.01f
                ? direction
                : getOctDirection();
    }
    if(rolling)
    {

        if(rollTimer.asSeconds() >= rollDuration)
        {
            rolling = false;
        }
    }
    if(!rolling && !rollCooled)
    {
        if(rollTimer.asSeconds() > rollDuration + rollCooldown)
        {
            rollCooled = true;
        }
    }

    if(startAttack && !rolling)
    {
        attacking = true;
        startAttack = false;
        attackDirection = getOctDirection();
    }
    if(attacking)
    {
        if(attackTimer.asSeconds() >= attackDuration)
        {
            attacking = false;
        }
    }
    if(!attacking && !attackCooled)
    {
        if(attackTimer.asSeconds() > attackDuration + attackCooldown)
        {
            attackCooled = true;
        }
    }
}

void PlayerBehaviours::collisionWith(GameObject &o, std::string me, std::string them)
{
    if(compare(me,"attack"))
    {

        std::vector<int> rs = game->componentLoader.getRigidBodiesFromObject(o);
        for(int i=0; i<rs.size(); i++)
        {
            RigidBody & r = game->componentLoader.getRigidBody(rs[i]);
            r.momentum += attackMom*attackDirection;
        }
    }
}

void PlayerBehaviours::beforeEvents()
{
    speed = baseSpeed;
    dx = 0;
    dy = 0;
}

void PlayerBehaviours::resolveEvent(Event & event)
{
    std::string action = event.parsedScript["action"];

    if(compare(action,"move_right"))
    {
        dx += 1;
    }
    else if(compare(action,"move_up"))
    {
        dy -= 1;
    }
    else if(compare(action,"move_left"))
    {
        dx -= 1;
    }
    else if(compare(action,"move_down"))
    {
        dy += 1;
    }
    else if(compare(action,"attack") || compare(action,"pad_X"))
    {
        if(attackCooled)
        {
            startAttack = true;
            attackCooled = false;
            attackClock.restart();
        }
    }
    else if(compare(action,"roll") || compare(action,"pad_A"))
    {
        if(rollCooled)
        {
            startRoll = true;
            rollCooled = false;
            rollClock.restart();
        }
    }
    else if(compare(action,"X"))
    {
        float deltaX = std::stof(event.parsedScript["val"])*0.01;
        dx += deltaX;
    }
    else if(compare(action,"Y"))
    {
        float deltaY = std::stof(event.parsedScript["val"])*0.01;
        dy += deltaY;
    }
}


void PlayerBehaviours::update()
{
    GameObjectLoader & gameObjectLoader = game->gameObjectLoader;
    ComponentLoader & componentLoader = game->componentLoader;
    GameObject& g = gameObjectLoader.loadGameObject(parent);
    Transform & transform = componentLoader.getTransform(g.transform);
    sf::Vector2f direction(dx,dy);
    if(game->math.mag(direction) > 1.0)
    {
        direction = game->math.unit(direction);
    }
    sf::Vector2f velocity = speed*direction;
    facing = getFacing(direction.x,direction.y);

    SpriteRenderer & spr = componentLoader.getSpriteRendererFromObject(g,"sprite");

    if(attacking)
    {
        if(spr.spritesheet != "clo_attack")
        {
            spr.animation.stop();
            spr.update();
            spr.spritesheet = "clo_attack";
            spr.clip = "attack_down";

            if(facing[0] == 'd'){spr.clip = "attack_down";}
            else if(facing[0] == 'u'){spr.clip = "attack_up";}
            else if(facing[0] == 'r'){spr.clip = "attack_right";}
            else if(facing[0] == 'l'){spr.clip = "attack_left";}

            spr.animation.rate = 1.0;
            spr.animation.spf = attackDuration/8.0;
            spr.animation.play();
        }

    }
    else if(rolling)
    {
        if(spr.spritesheet != "clo_roll")
        {
            spr.animation.stop();
            spr.update();
            spr.spritesheet = "clo_roll";
            spr.animation.rate = 1.0;
        }

        if(facing[0] == 'd')
        {
            spr.clip = "roll_down";
        }
        else if(facing[0] == 'u')
        {
            spr.clip = "roll_up";
        }
        else if(facing[0] == 'r')
        {
            spr.clip = "roll_right";
            spr.offset.x = 8;
        }
        else if(facing[0] == 'l')
        {
            spr.clip = "roll_left";
            spr.offset.x = -8;
        }
        spr.animation.spf = rollDuration/8.0;
        spr.animation.play();
    }
    else if(game->math.mag(velocity) < 0.01f)
    {
        spr.spritesheet = "clo_walk";
        spr.offset.x = 0;
        if(facing[0] == 'd')
            spr.clip = "stand_down";
        else if(facing[0] == 'u')
            spr.clip = "stand_up";
        else if(facing[0] == 'r')
            spr.clip = "stand_right";
        else if(facing[0] == 'l')
            spr.clip = "stand_left";
        spr.animation.stop();
    }
    else
    {
        spr.offset.x = 0;
        spr.spritesheet = "clo_walk";
        if(facing[0] == 'd')
            spr.clip = "walk_down";
        else if(facing[0] == 'u')
            spr.clip = "walk_up";
        else if(facing[0] == 'r')
            spr.clip = "walk_right";
        else if(facing[0] == 'l')
            spr.clip = "walk_left";
        spr.animation.rate = 2*game->math.mag(velocity)/speed;
        spr.animation.play();
    }


    rollTimer = rollClock.getElapsedTime();    
    attackTimer = attackClock.getElapsedTime();

    checkInputLogic();

    if(rolling)
    {
        velocity = rollBoost*baseSpeed*rollDirection;
    }
    if(attacking)
    {
        attackFrame = (int) floor((attackFrames.size())*(attackTimer.asSeconds()/(attackDuration*0.3)));
        if(attackFrame < 0) {attackFrame = 0;}
        if(attackFrame >= attackFrames.size()) {attackFrame = attackFrames.size()-1;}
        velocity.x = 0;
        velocity.y = 0;
        Collidable & attack = componentLoader.getCollidableFromObject(gameObjectLoader.loadGameObject(parent),"attack");
        ConvexPolygon scaled = game->math.scale(attackFrames[attackFrame],attackScaleFactor);
        scaled = game->math.rotateClockwise(scaled,game->math.getBearing(attackDirection));
        scaled.position = attack.polygon.position;
        attack.polygon = scaled;

    }
    else
    {
        Collidable & attack = componentLoader.getCollidableFromObject(gameObjectLoader.loadGameObject(parent),"attack");
        attack.polygon.clearPoints();
    }

    //transform.move(velocity);
    transform.velocity += velocity;
}


