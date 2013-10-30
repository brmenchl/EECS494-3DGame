//
//  Debris.h
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#ifndef __game__Debris__
#define __game__Debris__

#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Debris : public Game_Object {
public:
    Debris(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
          const Zeni::Vector3f &scale_ = Zeni::Vector3f(1.0f, 1.0f, 1.0f),
          const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Debris(const Debris &rhs);
    Debris & operator=(const Debris &rhs);
    ~Debris();
    
    void render();
    void step(const float &time_step);
    void set_velocity(const Zeni::Vector3f &velocity_) {m_velocity = velocity_;}
    Point3f get_position() {return m_position;}
    
    void collide();
    
private:
    
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    
    Zeni::Sound_Source * m_source;
};


#endif /* defined(__game__Debris__) */
