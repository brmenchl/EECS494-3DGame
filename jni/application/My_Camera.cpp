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
m_camera_state(FREE)
{
    follow_distance = -300;
    m_attached_object = NULL;
    m_camera.fov_rad = Zeni::Global::pi / 3.0f;
    create_body();
}

void My_Camera::track(Game_Object* obj) {
    m_attached_object = obj;
    m_camera_state = TRACKING;
}

void My_Camera::chase(Game_Object* obj) {
    m_attached_object = obj;
    m_camera_state = CHASING;
}

void My_Camera::detach_camera() {
    m_attached_object = NULL;
    m_camera_state = FREE;
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
    if (follow_distance > -400) {
        follow_distance -= 100;
    }
}

void My_Camera::decrease_follow_distance() {
    if (follow_distance < 300) {
        follow_distance += 100;
    }
}

void My_Camera::step(const float &time_step) {
    
    switch (m_camera_state) {
        case FREE:
            m_camera.position += time_step * m_velocity;
            break;
            
        case TRACKING:
            track_attached();
            break;
            
        case CHASING:
            chase_attached();
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

void My_Camera::chase_attached() {
    Vector3f move_vec;
    Point3f strict_new_pos, cam_cur_pos, next_pos;
    cam_cur_pos = m_camera.position;
    
    Vector3f pull_back = (m_attached_object->get_rotation() * Vector3f(follow_distance,0,25));
    strict_new_pos = m_attached_object->get_position() + pull_back;
    
    move_vec = Vector3f(strict_new_pos.x - cam_cur_pos.x, strict_new_pos.y - cam_cur_pos.y, strict_new_pos.z - cam_cur_pos.z);
    
    next_pos = cam_cur_pos + move_vec * 0.02f;
    
    m_camera.position = next_pos;
    m_camera.look_at(m_attached_object->get_position());
}

void My_Camera::track_attached() {

    m_camera.look_at(m_attached_object->get_position());
    
}