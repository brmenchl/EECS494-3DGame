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

My_Camera::My_Camera(const Camera &camera_,
               const Vector3f &end_point_b_,
               const float radius_)
: m_camera(camera_),
m_end_point_b(end_point_b_),
m_radius(radius_),
m_attached_crate(NULL)
{
    m_camera.fov_rad = Zeni::Global::pi / 3.0f;
    
    create_body();
}

void My_Camera::attach_camera(Crate* crate) {
    m_attached_crate = crate;
}

void My_Camera::detach_camera() {
    m_attached_crate = NULL;
}

bool My_Camera::get_is_attached() {
    return (m_attached_crate);
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

void My_Camera::step(const float &time_step) {
    if (get_is_attached()) {
        //Use the position of the object we are attached to in order to position camera
    } else {
        m_camera.position += time_step * m_velocity;
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