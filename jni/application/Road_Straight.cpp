//
//  Road_Straight.cpp
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#include "Road_Straight.h"
#include <zenilib.h>
#include <iostream>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Road_Straight::Road_Straight(const Point3f &corner_,
             const Vector3f &scale_,
             const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    if(!m_instance_count)
        m_model = new Model("models/roadstraight.3ds");
    ++m_instance_count;
    
    create_body();
}

Road_Straight::Road_Straight(const Road_Straight &rhs)
: Game_Object(rhs),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    ++m_instance_count;
    
    create_body();
}

Road_Straight & Road_Straight::operator=(const Road_Straight &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Road_Straight::~Road_Straight() {
    delete m_source;
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Road_Straight::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_position);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Road_Straight::step(const float &time_step) {
    create_body();
}

void Road_Straight::create_body() {
    Vector3f new_scale = m_scale + Vector3f(800, 800, 1);
    m_body = Parallelepiped(m_position,
                            m_rotation * new_scale.get_i(),
                            m_rotation * new_scale.get_j(),
                            m_rotation * new_scale.get_k());

}

void Road_Straight::collide() {
    if(!m_source->is_playing())
        m_source->play();
}

Model * Road_Straight::m_model = 0;
unsigned long Road_Straight::m_instance_count = 0lu;