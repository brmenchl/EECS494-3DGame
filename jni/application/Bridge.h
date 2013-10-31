//
//  Bridge.h
//  game
//
//  Created by Bradley Menchl on 10/31/13.
//
//

#ifndef __game__Bridge__
#define __game__Bridge__

#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Bridge : public Game_Object {
public:
    Bridge(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
               const Zeni::Vector3f &scale_ = Zeni::Vector3f(3.0f, 3.0f, 3.0f),
               const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Bridge(const Bridge &rhs);
    Bridge & operator=(const Bridge &rhs);
    ~Bridge();
    
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



#endif /* defined(__game__Bridge__) */
