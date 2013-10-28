//
//  Player.h
//  game
//
//  Created by David Zilli on 10/21/13.
//
//

#ifndef __game__Player__
#define __game__Player__

#include <iostream>
#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Player : public Game_Object {
public:
    Player(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
          const Zeni::Vector3f &scale_ = Zeni::Vector3f(1.0f, 1.0f, 1.0f),
          const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Player(const Player &rhs);
    Player & operator=(const Player &rhs);
    ~Player();
    
    void render();
    void step(const float &time_step);
    void set_velocity(const Zeni::Vector3f &velocity_) {m_velocity = velocity_;}
    Point3f get_position() {return m_position;}
    
    void collide();
    
    const std::pair<Zeni::Collision::Capsule, Zeni::Collision::Parallelepiped> & get_player_body() const;
    bool is_crashing(std::list<Game_Object*> &objects);
private:
    static Vector3f WING_Z;
    static Vector3f WING_X;
    static Vector3f WING_SPAN;
    //Member variables
    //Vector3f m_velocity;
    void create_body();

    // Level 1
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    
    Zeni::Sound_Source * m_source;
    
    //Together these make the jet bounding box
    //Zeni::Collision::Capsule m_fuselage;
    //Zeni::Collision::Parallelepiped m_wings;
    //FIRST COLLISION IS FUSELAGE, SECOND IS WINGS
    std::pair<Zeni::Collision::Capsule, Zeni::Collision::Parallelepiped> m_body;

    
    Point3f get_front();
    Point3f get_back();
    Point3f get_wing_corner();
    
    // Level 2
    //    Zeni::Point3f m_position;
    //    Zeni::Vector3f m_scale;
    //    Zeni::Quaternion m_rotation;
    
    // Level 3
    //Zeni::Collision::Parallelepiped m_body; // not motion so much as collision
    
    // Level 4
    // A stationary Player has no controls
};

#endif
