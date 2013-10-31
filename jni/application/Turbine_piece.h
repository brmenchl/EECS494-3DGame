//
//  Turbine_piece.h
//  game
//
//  Created by Bradley Menchl on 10/31/13.
//
//


#ifndef __game__Turbine_piece__
#define __game__Turbine_piece__


#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Turbine_piece : public Game_Object {
public:
    Turbine_piece(const String &texture, const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
                 const Zeni::Vector3f &scale_ = Zeni::Vector3f(18.0f, 18.0f, 18.0f),
                 const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(1.0f, 0.0f, -1.0f), 0.0f));
    Turbine_piece(const Turbine_piece &rhs);
    Turbine_piece & operator=(const Turbine_piece &rhs);
    ~Turbine_piece();
    
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
    bool wing;
};


#endif /* defined(__game__Turbine_piece__) */
