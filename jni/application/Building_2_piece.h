//
//  Building_2_piece.h
//  game
//
//  Created by Bradley Menchl on 10/30/13.
//
//

#ifndef __game__Building_2_piece__
#define __game__Building_2_piece__


#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Building_2_piece : public Game_Object {
public:
    Building_2_piece(const String &texture, const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
                    const Zeni::Vector3f &scale_ = Zeni::Vector3f(40.0f, 40.0f, 40.0f),
                    const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Building_2_piece(const Building_2_piece &rhs);
    Building_2_piece & operator=(const Building_2_piece &rhs);
    ~Building_2_piece();
    
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
    int level;
    
};

#endif /* defined(__game__Building_2_piece__) */
