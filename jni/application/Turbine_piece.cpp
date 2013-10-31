//
//  Turbine_piece.cpp
//  game
//
//  Created by Bradley Menchl on 10/31/13.
//
//


#include "Turbine_piece.h"
#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Turbine_piece::Turbine_piece(const String &texture, const Point3f &corner_,
                           const Vector3f &scale_,
                           const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_),
wing(false),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    //if(!m_instance_count)
    m_model = new Model(texture);
    if(texture.c_str()[14] == 'w'){
        wing = true;
    }
    ++m_instance_count;
    create_body();
}

Turbine_piece::Turbine_piece(const Turbine_piece &rhs)
: Game_Object(rhs),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    ++m_instance_count;
    
    create_body();
}

Turbine_piece & Turbine_piece::operator=(const Turbine_piece &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Turbine_piece::~Turbine_piece() {
    delete m_source;
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Turbine_piece::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_position);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Turbine_piece::step(const float &time_step) {
    m_rotation *= Quaternion(0,time_step*4,0);
    create_body();
}

void Turbine_piece::create_body() {
    Vector3f new_scale;
    if(wing){
        new_scale = Vector3f(180,180,3000);
        m_my_body = Collision::Parallelepiped(m_position,
                                              m_rotation * new_scale.get_i(),
                                              m_rotation * new_scale.get_j(),
                                              m_rotation * new_scale.get_k());
    }
    else{
        new_scale = Vector3f(180,180,5100);
        m_my_body = Collision::Parallelepiped(m_position,
                                              m_rotation * new_scale.get_i(),
                                              m_rotation * new_scale.get_j(),
                                              m_rotation * new_scale.get_k());
    }
}

Collision::Parallelepiped & Turbine_piece::get_body() {
    return m_my_body;
}

void Turbine_piece::collide() {
    if(!m_source->is_playing())
        m_source->play();
}

//Model * Turbine_piece::m_model = 0;
unsigned long Turbine_piece::m_instance_count = 0lu;