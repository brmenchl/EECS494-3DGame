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

#define MIDDLE_TO_NOSE 10
#define MIDDLE_TO_TAIL 55
#define MIDDLE_TO_WING 60
Vector3f Player::WING_Z=Vector3f(0,0,5.0f);
Vector3f Player::WING_X=Vector3f(15.0f,0,0);
Vector3f Player::WING_SPAN=Vector3f(0,150.0f,0);

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

Point3f Player::get_front(){
    return m_position+MIDDLE_TO_NOSE*m_forward_vec;
}

Point3f Player::get_back() {
    return m_position-MIDDLE_TO_TAIL*m_forward_vec;
}

Point3f Player::get_wing_corner(){
    return m_position+MIDDLE_TO_WING*(m_up_vec%m_forward_vec);
}

float get_radius(){
    return 5.0f;
}

const std::pair<Zeni::Collision::Capsule, Zeni::Collision::Parallelepiped> & Player::get_player_body() const{
    return m_body;
}

bool Player::is_crashing(list<Game_Object*> &objects){
    std::list<Game_Object*>::iterator it;
    for(it = objects.begin(); it != objects.end(); it++){
        if(Player::get_player_body().first.intersects((*it)->get_body()) || Player::get_player_body().second.intersects((*it)->get_body())){
            return true;
        }
    }
    return false;
}

void Player::create_body() {
    m_body.first = Capsule(get_front(), get_back(), get_radius());
    m_body.second = Parallelepiped(get_wing_corner(),
                             m_rotation * WING_X,
                             m_rotation * WING_SPAN,
                             m_rotation * WING_Z);
    m_source->set_position(m_position + m_rotation * m_scale / 2.0f);
}
