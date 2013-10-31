//
//  Building_2_piece.cpp
//  game
//
//  Created by Bradley Menchl on 10/30/13.
//
//

#include "Building_2_piece.h"
#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Building_2_piece::Building_2_piece(const String &texture, const Point3f &corner_,
                                 const Vector3f &scale_,
                                 const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    //if(!m_instance_count)
        m_model = new Model(texture);
    ++m_instance_count;
    level = texture.c_str()[17]-'0';
    create_body();
}

Building_2_piece::Building_2_piece(const Building_2_piece &rhs)
: Game_Object(rhs),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    ++m_instance_count;
    
    create_body();
}

Building_2_piece & Building_2_piece::operator=(const Building_2_piece &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Building_2_piece::~Building_2_piece() {
    delete m_source;
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Building_2_piece::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_position);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Building_2_piece::step(const float &time_step) {
    create_body();
}

void Building_2_piece::create_body() {
    Vector3f new_scale;
    switch(level){
        case 1:
            new_scale = m_scale + Vector3f(860, 860, 865);
            break;
        case 2:
            new_scale = m_scale + Vector3f(570, 570, 873);
            break;
        case 3:
            new_scale = m_scale + Vector3f(360, 360, 522);
            break;
        case 4:
            new_scale = m_scale + Vector3f(250, 250, 430);
            break;
    }
    
    m_my_body = Collision::Parallelepiped(m_position,
                                          m_rotation * new_scale.get_i(),
                                          m_rotation * new_scale.get_j(),
                                          m_rotation * new_scale.get_k());
}

Collision::Parallelepiped & Building_2_piece::get_body() {
    return m_my_body;
}

void Building_2_piece::collide() {
    if(!m_source->is_playing())
        m_source->play();
}

//Model * Building_2_piece::m_model = 0;
unsigned long Building_2_piece::m_instance_count = 0lu;