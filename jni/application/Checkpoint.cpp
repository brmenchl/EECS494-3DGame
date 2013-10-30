//
//  Checkpoint.cpp
//  game
//
//  Created by David Zilli on 10/28/13.
//
//

#include "Checkpoint.h"
#include <zenilib.h>
#include <iostream>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

#define RADIUS 150
#define THICKNESS 25

Checkpoint::Checkpoint(float time_value_,
                       const Point3f &corner_,
             const Vector3f &scale_,
             const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_),
m_source(new Sound_Source(get_Sounds()["collide"])),
m_is_active(false),
m_is_victory_checkpoint(false),
m_time_value(time_value_),
m_keyframe(0.0f),
next_checkpoints()
{
    if(!m_instance_count)
        m_model = new Model("models/checkpoint.3ds");
    ++m_instance_count;
    
    create_body();
}

Checkpoint::Checkpoint(const Checkpoint &rhs)
: Game_Object(rhs),
m_source(new Sound_Source(get_Sounds()["collide"]))
{
    ++m_instance_count;
    
    create_body();
}

Checkpoint & Checkpoint::operator=(const Checkpoint &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Checkpoint::~Checkpoint() {
    delete m_source;
    
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Checkpoint::render() {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    
    m_model->set_translate(m_position);
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
//    if(m_keyframe > 100)
//        m_keyframe = 0;
//    m_model->set_keyframe(m_keyframe);
    m_model->render();
}

void Checkpoint::step(const float &time_step) {
    if (m_is_active) {;
        m_rotation *= Quaternion(time_step, 0, 0);
    }
    adjust_vectors();
    create_body();
}

float Checkpoint::get_time_value() {
    return m_time_value;
}

void Checkpoint::collide() {
    if(!m_source->is_playing())
        m_source->play();
}

bool Checkpoint::get_is_active() {
    return m_is_active;
}
void Checkpoint::set_is_active(bool flag) {
    m_is_active = flag;
}

void Checkpoint::add_next_checkpoint(Checkpoint* next) {
    next_checkpoints.push_back(next);
}

void Checkpoint::activate_next_checkpoints() {
    std::list<Checkpoint*>::iterator check_it;
    for(check_it = next_checkpoints.begin(); check_it != next_checkpoints.end(); check_it++){
        (*check_it)->set_is_active(true);
    }
}

void Checkpoint::set_as_victory_checkpoint() {
    m_is_victory_checkpoint = true;
}

bool Checkpoint::get_is_victory_checkpoint() {
    return m_is_victory_checkpoint;
}

void Checkpoint::create_body() {
    m_body = Sphere(m_position, 50.0f);
}

Model * Checkpoint::m_model = 0;
unsigned long Checkpoint::m_instance_count = 0lu;