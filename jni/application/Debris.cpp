//
//  Debris.cpp
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#include "Debris.h"
#include <zenilib.h>
#include <iostream>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Debris::Debris(const Point3f &corner_,
             const Vector3f &scale_,
             const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    if(!m_instance_count)
        m_model = new Model("models/debris.3ds");
    ++m_instance_count;
    
    create_body();
}

Debris::Debris(const Debris &rhs)
: Game_Object(rhs),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    ++m_instance_count;
    
    create_body();
}

Debris & Debris::operator=(const Debris &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Debris::~Debris() {
    delete m_source;
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Debris::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_position);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Debris::step(const float &time_step) {
    m_position += time_step * m_velocity;
    create_body();
}

void Debris::collide() {
    if(!m_source->is_playing())
        m_source->play();
}

Model * Debris::m_model = 0;
unsigned long Debris::m_instance_count = 0lu;