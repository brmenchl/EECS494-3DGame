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
        m_model = new Model("models/plane.3ds");
    ++m_instance_count;
    
    create_body();
}

Player::Player(const Player &rhs)
: Game_Object(rhs),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    ++m_instance_count;
    
    create_bounding_box();
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

Point3f get_front(){
    //These points are arbitrary, were going to have to figure out the dimensions of the plane in-game
    return Point3f(0.0f,0.0f,0.0f);
}
Point3f get_back() {
    return Point3f(0.0f,0.0f,0.0f);
}
Point3f get_wing_corner(){
    return Point3f(0.0f,0.0f,0.0f);
}
float get_radius(){
    return 3.0f;
}

void Player::create_bounding_box() {
    m_fuselage = Capsule(get_front(), get_back(), get_radius());
    m_wings = Parallelepiped(get_wing_corner(),
                             m_rotation * m_scale.get_i(),
                             m_rotation * m_scale.get_j(),
                             m_rotation * m_scale.get_k());
    m_source->set_position(m_position + m_rotation * m_scale / 2.0f);
}
