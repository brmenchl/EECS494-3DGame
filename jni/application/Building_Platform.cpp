//
//  Building_Platform.cpp
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#include "Building_Platform.h"
#include <zenilib.h>
#include <iostream>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Building_Platform::Building_Platform(const Point3f &corner_,
                     const Vector3f &scale_,
                     const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    if(!m_instance_count)
        m_model = new Model("models/building1plat.3ds");
    ++m_instance_count;
    
    create_body();
}

Building_Platform::Building_Platform(const Building_Platform &rhs)
: Game_Object(rhs),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    ++m_instance_count;
    
    create_body();
}

Building_Platform & Building_Platform::operator=(const Building_Platform &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Building_Platform::~Building_Platform() {
    delete m_source;
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Building_Platform::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_position);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Building_Platform::step(const float &time_step) {
    m_position += time_step * m_velocity;
    create_body();
}

void Building_Platform::create_body() {
    Vector3f new_scale = m_scale + Vector3f(2900, 2900, 250);
    m_my_body = Collision::Parallelepiped(m_position,
                                          m_rotation * new_scale.get_i(),
                                          m_rotation * new_scale.get_j(),
                                          m_rotation * new_scale.get_k());
}

Collision::Parallelepiped & Building_Platform::get_body() {
    return m_my_body;
}

void Building_Platform::collide() {
    if(!m_source->is_playing())
        m_source->play();
}

Model * Building_Platform::m_model = 0;
unsigned long Building_Platform::m_instance_count = 0lu;
