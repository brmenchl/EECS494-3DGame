//
//  Game_Object.h
//  game
//
//  Created by David Zilli on 10/22/13.
//
//

#ifndef __game__Game_Object__
#define __game__Game_Object__

#include <iostream>
#include <zenilib.h>

using namespace Zeni;

class Game_Object {
public:
    Game_Object(const Point3f &corner_ = Point3f(0.0f, 0.0f, 0.0f),
          const Vector3f &scale_ = Vector3f(1.0f, 1.0f, 1.0f),
          const Quaternion &rotation_ = Quaternion::Axis_Angle(Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Game_Object(const Game_Object &rhs);
    Game_Object & operator=(const Game_Object &rhs);
    ~Game_Object();
    
    virtual void render() = 0;
    virtual void collide() = 0;
    void step(const float &time_step);
    void set_velocity(const Vector3f &velocity_) {m_velocity = velocity_;}
    Vector3f get_velocity() { return m_velocity; }
    Point3f get_position() {return m_position;}
    Vector3f get_scale() {return m_scale;}
    Quaternion get_rotation() {return m_rotation;}
    void rotate(const Quaternion &rot_) { m_rotation *= rot_; }
    virtual Collision::Parallelepiped & get_body() {return m_body;}
    Vector3f get_forward_vec();
    Vector3f get_up_vec();
    Vector3f get_left_vec();
    void adjust_vectors();
    
    virtual void create_body() = 0;
protected:
    //Member variables
    Vector3f m_velocity;
    Point3f m_position;
    Vector3f m_scale;
    Quaternion m_rotation;
    Collision::Parallelepiped m_body;
    Vector3f m_forward_vec;
    Vector3f m_up_vec;
    Vector3f m_left_vec;
    //static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    

};
 

#endif /* defined(__game__Game_Object__) */
