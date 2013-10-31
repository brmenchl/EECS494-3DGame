//
//  Road_Straight.h
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#ifndef __game__Road_Straight__
#define __game__Road_Straight__

#include <iostream>
#include <iostream>
#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Road_Straight : public Game_Object {
public:
    Road_Straight(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
          const Zeni::Vector3f &scale_ = Zeni::Vector3f(1.0f, 1.0f, 1.0f),
          const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Road_Straight(const Road_Straight &rhs);
    Road_Straight & operator=(const Road_Straight &rhs);
    ~Road_Straight();
    
    void render();
    void step(const float &time_step);
    void set_velocity(const Zeni::Vector3f &velocity_) {m_velocity = velocity_;}
    Point3f get_position() {return m_position;}
    Collision::Parallelepiped & get_body() {return m_body;}
    void collide();
    
private:
    
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    Collision::Parallelepiped m_body;
    Zeni::Sound_Source * m_source;
    
    void create_body();
};

#endif /* defined(__game__Road_Straight__) */
