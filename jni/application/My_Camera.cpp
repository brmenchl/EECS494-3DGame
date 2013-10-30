//
//  Camera.cpp
//  game
//
//  Created by David Zilli on 10/22/13.
//
//

#include "My_Camera.h"

#include <zenilib.h>

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

My_Camera::My_Camera(const Camera &camera_,
               const Vector3f &end_point_b_,
               const float radius_)
: m_camera(camera_),
m_end_point_b(end_point_b_),
m_radius(radius_),
m_camera_state(FREE),
m_chase_type(HORIZON_LOCKED),
follow_distance(0)
{
    m_attached_object = NULL;
    m_focus_object = NULL;
    m_camera.fov_rad = Zeni::Global::pi / 3.0f;
    create_body();
}

void My_Camera::track(Game_Object* obj) {
    m_attached_object = obj;
    m_camera_state = TRACKING;
}

void My_Camera::set_focus_object(Game_Object* obj) {
    m_focus_length = 0;
    m_focus_object = obj;
}

void My_Camera::unset_focus_object() {
    m_focus_object = NULL;
}

void My_Camera::chase(Game_Object* obj) {
    m_attached_object = obj;
    m_camera_state = CHASING;
}

void My_Camera::detach_camera() {
    m_attached_object = NULL;
    m_camera_state = FREE;
}

void My_Camera::set_horizon_lock() {
    m_chase_type = HORIZON_LOCKED;
}

void My_Camera::set_rolling() {
    m_chase_type = ROLLING;
}

bool My_Camera::get_is_attached() {
    return (m_attached_object);
}

void My_Camera::set_position(const Point3f &position) {
    m_camera.position = position;
    create_body();
}

void My_Camera::adjust_pitch(const float &phi) {
    const Quaternion backup = m_camera.orientation;
    const Vector3f backup_up = m_camera.get_up();
    
    m_camera.adjust_pitch(phi);
    
    if(m_camera.get_up().k < 0.0f && backup_up.k >= 0.0f)
        m_camera.orientation = backup;
}

void My_Camera::adjust_roll(const float &rho) {
    m_camera.adjust_roll(rho);
}

void My_Camera::turn_left_xy(const float &theta) {
    m_camera.turn_left_xy(theta);
}

void My_Camera::increase_follow_distance() {
    if (follow_distance < 20) {
        follow_distance += 10;
    }
}

void My_Camera::decrease_follow_distance() {
    if (follow_distance > 10) {
        follow_distance -= 10;
    }
}

void My_Camera::step(const float &time_step, Vector3f vel) {
    
    switch (m_camera_state) {
        case FREE:
            m_camera.position += time_step * m_velocity;
            break;
            
        case TRACKING:
            track_attached();
            break;
            
        case CHASING:
            chase_attached(vel);
            break;
    }

    create_body();
}

void My_Camera::create_body() {
    Sound &sr = get_Sound();
    
    m_body = Capsule(m_camera.position,
                     m_camera.position + m_end_point_b,
                     m_radius);
    
    sr.set_listener_position(m_camera.position);
    sr.set_listener_forward_and_up(m_camera.get_forward(), m_camera.get_up());
    sr.set_listener_velocity(m_velocity);
}

void My_Camera::chase_attached(Vector3f vel) {
    Vector3f move_vec;
    Vector3f look_vec;
    Point3f strict_new_pos, cam_cur_pos, next_pos, focus;
    cam_cur_pos = m_camera.position;
    
    Vector3f pull_back = (m_attached_object->get_rotation() * Vector3f(-follow_distance,0,25));
    
    strict_new_pos = m_attached_object->get_position() + pull_back;
    
    move_vec = Vector3f(strict_new_pos.x - cam_cur_pos.x, strict_new_pos.y - cam_cur_pos.y, strict_new_pos.z - cam_cur_pos.z);
    
    next_pos = cam_cur_pos + move_vec * 0.0028f;
    
    m_camera.position = next_pos;
    
    if (m_focus_object) {
        
        look_vec = Vector3f(m_focus_object->get_position().x - m_attached_object->get_position().x,
                            m_focus_object->get_position().y - m_attached_object->get_position().y,
                            m_focus_object->get_position().z - m_attached_object->get_position().z);

        m_focus_length += 0.00028f;
        focus = m_attached_object->get_position() + look_vec * m_focus_length;
        cout << m_focus_length << endl;
        
        m_camera.look_at(focus);
        
    } else {
        
        
        m_camera.look_at(m_attached_object->get_position() + m_attached_object->get_forward_vec() * vel.magnitude());

        if (m_chase_type == ROLLING) {
            m_camera.orientation = m_attached_object->get_rotation();
        }
    }
    
//    if (m_focus_object) {
//        m_camera.look_at(m_focus_object->get_position());
//    } else {
//        m_camera.look_at(m_attached_object->get_position() + m_attached_object->get_forward_vec() * vel.magnitude());
//    }

}

void My_Camera::track_attached() {

    m_camera.look_at(m_attached_object->get_position());
    
}