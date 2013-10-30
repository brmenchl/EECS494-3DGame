//
//  Checkpoint.h
//  game
//
//  Created by David Zilli on 10/28/13.
//
//

#ifndef __game__Checkpoint__
#define __game__Checkpoint__

#include <iostream>
#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Checkpoint : public Game_Object {
public:
    Checkpoint(float time_value_,
               const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
               const Zeni::Vector3f &scale_ = Zeni::Vector3f(3.0f, 3.0f, 3.0f),
               const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Checkpoint(const Checkpoint &rhs);
    Checkpoint & operator=(const Checkpoint &rhs);
    ~Checkpoint();
    
    void render();
    void step(const float &time_step);
    void set_velocity(const Zeni::Vector3f &velocity_) {m_velocity = velocity_;}
    Point3f get_position() {return m_position;}
    Collision::Sphere & get_checkpoint_body() { return m_body; }
    void collide();
    
    bool get_is_active();
    void set_is_active(bool flag);
    float get_time_value();
    void add_next_checkpoint(Checkpoint* next);
    std::list<Checkpoint*> get_next_checkpoints();
    void activate_next_checkpoints();
    void set_as_victory_checkpoint();
    bool get_is_victory_checkpoint();
    
    float m_keyframe;
private:
    
    std::list<Checkpoint*> next_checkpoints;
    float m_time_value;
    bool m_is_active;
    bool m_is_victory_checkpoint;
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    Collision::Sphere m_body;
    
    Zeni::Sound_Source * m_source;
    void create_body();
};

#endif /* defined(__game__Checkpoint__) */
