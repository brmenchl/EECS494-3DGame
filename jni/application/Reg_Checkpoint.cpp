//
//  Reg_Checkpoint.cpp
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#include "Reg_Checkpoint.h"
#include <zenilib.h>
#include <iostream>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

#define RADIUS 150
#define THICKNESS 25

Reg_Checkpoint::Reg_Checkpoint(float time_value_,
                                           const Point3f &corner_,
                                           const Vector3f &scale_,
                                           const Quaternion &rotation_)
: Checkpoint(time_value_,
             corner_,
             scale_,
             rotation_)
{
    load_model();
    
    create_body();
}

void Reg_Checkpoint::load_model() {
    if(!m_instance_count)
        m_model = new Model("models/checkpoint.3ds");
    ++m_instance_count;
    
}

Reg_Checkpoint::~Reg_Checkpoint() {
    delete m_source;
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Reg_Checkpoint::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_position);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    m_model->render();
}

Model * Reg_Checkpoint::m_model = 0;
unsigned long Reg_Checkpoint::m_instance_count = 0lu;