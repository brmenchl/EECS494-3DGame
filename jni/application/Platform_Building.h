//
//  Platform_Building.h
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#ifndef __game__Platform_Building__
#define __game__Platform_Building__

#include <iostream>

#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Platform_Building : public Game_Object {
public:
    Platform_Building(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
               const Zeni::Vector3f &scale_ = Zeni::Vector3f(150.0f, 150.0f, 150.0f),
               const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Platform_Building(const Platform_Building &rhs);
    Platform_Building & operator=(const Platform_Building &rhs);
    ~Platform_Building();
    
    void render();
    void step(const float &time_step);
    Collision::Parallelepiped & get_body() { return m_body; };
    void add_bodies_to_list(std::list<Game_Object*> &list);
    void set_velocity(const Zeni::Vector3f &velocity_) {m_velocity = velocity_;}
    Point3f get_position() {return m_position;}
    
    void collide();
    void create_body();
    
private:
    
    std::list<Game_Object*> m_bodies;
};


#endif /* defined(__game__Platform_Building__) */
