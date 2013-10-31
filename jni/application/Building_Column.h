//
//  Building_Column.h
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#ifndef __game__Building_Column__
#define __game__Building_Column__

#include <iostream>
#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Building_Column : public Game_Object {
public:
    Building_Column(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
              const Zeni::Vector3f &scale_ = Zeni::Vector3f(150.0f, 150.0f, 150.0f),
              const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Building_Column(const Building_Column &rhs);
    Building_Column & operator=(const Building_Column &rhs);
    ~Building_Column();
    
    void render();
    void step(const float &time_step);
    Collision::Parallelepiped & get_body();
    void set_velocity(const Zeni::Vector3f &velocity_) {m_velocity = velocity_;}
    Point3f get_position() {return m_position;}
    
    void collide();
    
private:
    
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    Collision::Parallelepiped m_my_body;
    Zeni::Sound_Source * m_source;
    
    void create_body();
};

#endif /* defined(__game__Building_Column__) */
