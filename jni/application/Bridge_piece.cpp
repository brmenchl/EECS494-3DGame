//
//  Bridge_piece.cpp
//  game
//
//  Created by Bradley Menchl on 10/31/13.
//
//

#include "Bridge_piece.h"
//
//  Bridge_piece.cpp
//  game
//
//  Created by Bradley Menchl on 10/30/13.
//
//

#include "Bridge_piece.h"
#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Bridge_piece::Bridge_piece(const String &texture, const Point3f &corner_,
                                   const Vector3f &scale_,
                                   const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    //if(!m_instance_count)
    m_model = new Model(texture);
    ++m_instance_count;
    leg = texture.c_str()[13] == 'l';
    create_body();
}

Bridge_piece::Bridge_piece(const Bridge_piece &rhs)
: Game_Object(rhs),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    ++m_instance_count;
    
    create_body();
}

Bridge_piece & Bridge_piece::operator=(const Bridge_piece &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Bridge_piece::~Bridge_piece() {
    delete m_source;
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Bridge_piece::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_position);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Bridge_piece::step(const float &time_step) {
    m_position += time_step * m_velocity;
    create_body();
}

void Bridge_piece::create_body() {
    Vector3f new_scale;
    if(leg){
        new_scale = Vector3f(350.0f,100.0f,280.0f);
        m_my_body = Collision::Parallelepiped(m_position,
                                              m_rotation * new_scale.get_i(),
                                              m_rotation * new_scale.get_j(),
                                              m_rotation * new_scale.get_k());
    }
    else{
        new_scale = Vector3f(370,1980,80);
        m_my_body = Collision::Parallelepiped(m_position+Vector3f(0,0,80),
                                              m_rotation * new_scale.get_i(),
                                              m_rotation * new_scale.get_j(),
                                              m_rotation * new_scale.get_k());
    }
    

}

Collision::Parallelepiped & Bridge_piece::get_body() {
    return m_my_body;
}

void Bridge_piece::collide() {
    if(!m_source->is_playing())
        m_source->play();
}

//Model * Bridge_piece::m_model = 0;
unsigned long Bridge_piece::m_instance_count = 0lu;