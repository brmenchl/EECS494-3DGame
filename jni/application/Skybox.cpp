//
//  Skybox.cpp
//  game
//
//  Created by Bradley Menchl on 10/29/13.
//
//

#include "Skybox.h"
#include <zenilib.h>

using namespace Zeni;

Skybox::Skybox(const Point3f &corner_,
               const Vector3f &scale_,
               const Quaternion &rotation_)
                : Game_Object(corner_, scale_, rotation_)
{
    
    if(!m_instance_count){
        m_model = new Model("models/skybox.3ds");
        ++m_instance_count;
    }
}

void Skybox::boxRender(Point3f player_pos) {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    m_model->set_translate(Point3f(4500, 4500, 0.0f));
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    m_model->render();
}

Skybox::~Skybox() {
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0l;
    }
}

Model * Skybox::m_model = 0;
unsigned long Skybox::m_instance_count = 0lu;