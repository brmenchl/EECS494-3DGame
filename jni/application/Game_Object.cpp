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

Game_Object::Game_Object(const Point3f &position_,
             const Vector3f &scale_,
             const Quaternion &rotation_)
: m_position(position_),
m_scale(scale_),
m_rotation(rotation_),
m_forward_vec(Vector3f(1,0,0)),
m_up_vec(Vector3f(0,0,1)),
m_velocity(Vector3f(0,0,0))
{
    if(!m_instance_count)
        //m_model = new Model("models/crate.3ds");
    ++m_instance_count;
    
    //create_body();
}

Game_Object::Game_Object(const Game_Object &rhs)
: m_position(rhs.m_position),
m_scale(rhs.m_scale),
m_rotation(rhs.m_rotation)
{
    ++m_instance_count;
    
    //create_body();
}

Game_Object & Game_Object::operator=(const Game_Object &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    //create_body();
    return *this;
}

Game_Object::~Game_Object() {
    
    if(!--m_instance_count) {
//        delete m_model;
//        m_model = 0lu;
    }
}

void Game_Object::step(const float &time_step) {
    m_position += time_step * m_velocity;
    //create_body();
}

void Game_Object::adjust_vectors() {
    m_forward_vec = m_rotation * Vector3f(1,0,0).normalized();
    m_up_vec = m_rotation * Vector3f(0,0,1).normalized();
    m_left_vec = m_rotation * Vector3f(0,1,0).normalized();
}

Vector3f Game_Object::get_forward_vec(){
    return m_forward_vec;
}

Vector3f Game_Object::get_up_vec(){
    return m_up_vec;
}

Vector3f Game_Object::get_left_vec() {
    return m_left_vec;
}

unsigned long Game_Object::m_instance_count = 0lu;
