//
//  Bridge_piece.h
//  game
//
//  Created by Bradley Menchl on 10/31/13.
//
//

#ifndef __game__Bridge_piece__
#define __game__Bridge_piece__


#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Bridge_piece : public Game_Object {
public:
    Bridge_piece(const String &texture, const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
                     const Zeni::Vector3f &scale_ = Zeni::Vector3f(3.0f, 3.0f, 3.0f),
                     const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Bridge_piece(const Bridge_piece &rhs);
    Bridge_piece & operator=(const Bridge_piece &rhs);
    ~Bridge_piece();
    
    void render();
    void step(const float &time_step);
    Collision::Parallelepiped & get_body();
    void set_velocity(const Zeni::Vector3f &velocity_) {m_velocity = velocity_;}
    Point3f get_position() {return m_position;}
    
    void collide();
    void create_body();
    
private:
    
    Zeni::Model * m_model;
    static unsigned long m_instance_count;
    Collision::Parallelepiped m_my_body;
    Zeni::Sound_Source * m_source;
    bool leg;
    
};


#endif /* defined(__game__Bridge_piece__) */
