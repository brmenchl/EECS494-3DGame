//
//  Building_2.h
//  game
//
//  Created by Bradley Menchl on 10/30/13.
//
//

#ifndef __game__Building_2__
#define __game__Building_2__

#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Building_2 : public Game_Object {
public:
    Building_2(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
                      const Zeni::Vector3f &scale_ = Zeni::Vector3f(1500.0f, 1500.0f, 1500.0f),
                      const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Building_2(const Building_2 &rhs);
    Building_2 & operator=(const Building_2 &rhs);
    ~Building_2();
    
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



#endif /* defined(__game__Building_2__) */
