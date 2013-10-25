//
//  Player.cpp
//  game
//
//  Created by David Zilli on 10/21/13.
//
//

#include "Player.h"
#include <zenilib.h>
#include "Game_Object.h"


using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Player::Player(const Point3f &corner_,
             const Vector3f &scale_,
             const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    if(!m_instance_count)
        m_model = new Model("models/crate.3ds");
    ++m_instance_count;
    
    create_body();
}

Player::Player(const Player &rhs)
: Game_Object(rhs),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    ++m_instance_count;
    
    create_body();
}

Player & Player::operator=(const Player &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Player::~Player() {
    delete m_source;
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Player::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_position);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    
    m_model->render();
}

void Player::step(const float &time_step) {
    m_position += time_step * m_velocity;
    create_body();
}

void Player::collide() {
    if(!m_source->is_playing())
        m_source->play();
}

Model * Player::m_model = 0;
unsigned long Player::m_instance_count = 0lu;
