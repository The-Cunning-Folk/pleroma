#include "rigidbodypattern.h"

using namespace BQ;

RigidBodyPattern::RigidBodyPattern()
{
    mass = 1;
    restitution = 1;
    friction = 0;
    momentum.x = momentum.y = 0;
}


void BQ::RigidBodyPattern::parse(const rapidjson::Value & json)
{
    mass = json.HasMember("mass") ? json["mass"].GetFloat() : 1;
    restitution = json.HasMember("restitution") ? json["restitution"].GetFloat() : 1;
    friction = json.HasMember("friction") ? json["friction"].GetFloat() : 0;
    momentum.x = json.HasMember("momentum_x") ? json["momentum_x"].GetFloat() : 0;
    momentum.y = json.HasMember("momentum_y") ? json["momentum_y"].GetFloat() : 0;
}
