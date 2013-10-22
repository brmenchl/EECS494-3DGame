//
//  Game_Object.cpp
//  game
//
//  Created by David Zilli on 10/22/13.
//
//

#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;

Game_Object::Game_Object(const Point3f &corner_,
             const Vector3f &scale_,
             const Quaternion &rotation_)
: m_corner(corner_),
m_scale(scale_),
m_rotation(rotation_),
m_velocity(Vector3f(0,0,0))
{
    if(!m_instance_count)
        //m_model = new Model("models/crate.3ds");
    ++m_instance_count;
    
    create_body();
}

Game_Object::Game_Object(const Game_Object &rhs)
: m_corner(rhs.m_corner),
m_scale(rhs.m_scale),
m_rotation(rhs.m_rotation)
{
    ++m_instance_count;
    
    create_body();
}

Game_Object & Game_Object::operator=(const Game_Object &rhs) {
    m_corner = rhs.m_corner;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Game_Object::~Game_Object() {
    
    if(!--m_instance_count) {
//        delete m_model;
//        m_model = 0lu;
    }
}

void Game_Object::step(const float &time_step) {
    m_corner += time_step * m_velocity;
    create_body();
}


void Game_Object::create_body() {
    m_body = Parallelepiped(m_corner,
                            m_rotation * m_scale.get_i(),
                            m_rotation * m_scale.get_j(),
                            m_rotation * m_scale.get_k());
}

unsigned long Game_Object::m_instance_count = 0lu;