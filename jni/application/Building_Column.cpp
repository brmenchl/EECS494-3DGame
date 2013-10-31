//
//  Building_Column.cpp
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#include "Building_Column.h"
#include <zenilib.h>
#include <iostream>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Building_Column::Building_Column(const Point3f &corner_,
                     const Vector3f &scale_,
                     const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    if(!m_instance_count)
        m_model = new Model("models/building1col.3ds");
    ++m_instance_count;
    
    create_body();
}

Building_Column::Building_Column(const Building_Column &rhs)
: Game_Object(rhs),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    ++m_instance_count;
    
    create_body();
}

Building_Column & Building_Column::operator=(const Building_Column &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Building_Column::~Building_Column() {
    delete m_source;
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Building_Column::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_position);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Building_Column::step(const float &time_step) {
    m_position += time_step * m_velocity;
    create_body();
}

void Building_Column::create_body() {
    Vector3f new_scale = m_scale + Vector3f(1400, 600, 500);
    m_my_body = Collision::Parallelepiped(m_position,
                                          m_rotation * new_scale.get_i(),
                                          m_rotation * new_scale.get_j(),
                                          m_rotation * new_scale.get_k());
    
    
}

Collision::Parallelepiped & Building_Column::get_body() {
    return m_my_body;
}

void Building_Column::collide() {
    if(!m_source->is_playing())
        m_source->play();
}

Model * Building_Column::m_model = 0;
unsigned long Building_Column::m_instance_count = 0lu;