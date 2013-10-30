//
//  Camera.h
//  game
//
//  Created by David Zilli on 10/22/13.
//
//

#ifndef __game__Camera__
#define __game__Camera__

#include <iostream>
#include <Zeni/Camera.h>
#include <Zeni/Collision.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Vector3f.h>
#include "Crate.h"

class My_Camera {
public:
    My_Camera(const Zeni::Camera &camera_,
           const Zeni::Vector3f &end_point_b_,
           const float radius_);
    
    Zeni::Camera & get_camera() {return m_camera;}
    
    void detach_camera();
    bool get_is_attached();
    void track(Game_Object* obj);
    void chase(Game_Object* obj);
    void set_horizon_lock();
    void set_rolling();
    
    // Adjusting position and orientation of camera
    void set_position(const Zeni::Point3f &position);
    void adjust_pitch(const float &phi);
    void turn_left_xy(const float &theta);
    void adjust_roll(const float &rho);
    void increase_follow_distance();
    void decrease_follow_distance();
    
    const Zeni::Vector3f & get_velocity() const {return m_velocity;}
    void set_velocity(const Zeni::Vector3f &velocity_) {m_velocity = velocity_;}
    
    const Zeni::Collision::Capsule & get_body() const {return m_body;}
    
    void step(const float &time_step, Vector3f vel);
    
private:
    enum CAMERA_STATE {
        FREE,
        TRACKING,
        CHASING
    };
    
    enum CHASE_TYPE {
        HORIZON_LOCKED,
        ROLLING
    };
    
    int m_chase_type;
    int m_camera_state;
    Game_Object* m_attached_object;
    Zeni::Camera m_camera;
    float follow_distance;
    Zeni::Vector3f m_end_point_b;
    float m_radius;
    Zeni::Collision::Capsule m_body; // collision
    Zeni::Vector3f m_velocity;
    
    void create_body();
    void chase_attached(Vector3f vel);
    void track_attached();
};

#endif /* defined(__game__Camera__) */
