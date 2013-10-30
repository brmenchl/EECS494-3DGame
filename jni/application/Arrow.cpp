//
//  Arrow.cpp
//  game
//
//  Created by Bradley Menchl on 10/30/13.
//
//

#include "Arrow.h"
#include "Checkpoint.h"
#include "My_Camera.h"

#include <zenilib.h>

using namespace Zeni;

Arrow::Arrow(const Point3f &corner_,
               const Vector3f &scale_,
               const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_)
{
    std::cout<<"creating"<<std::endl;
        m_model = new Model("models/arrow.3ds");
   // ++m_instance_count;
}

void Arrow::arrowRender(My_Camera &m_cam, Checkpoint* checkpoint) {
    
    Zeni::Camera cam = Camera(m_cam.get_camera().position , Quaternion(),1.0f, 90000.0f);
    
    cam.look_at(checkpoint->get_position());
    
    Vector3f dir = Vector3f(checkpoint->get_position().x - m_position.x,
                            checkpoint->get_position().y - m_position.y,
                            checkpoint->get_position().z - m_position.z)
                            .normalized();
    
    
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    m_model->set_translate(m_cam.get_camera().position + 10 * m_cam.get_camera().get_forward() + 4 * m_cam.get_camera().get_left());
    m_model->set_scale(m_scale);
    //m_model->set_rotate(rotation.second, rotation.first);
    m_model->set_rotate(cam.orientation);
    m_model->render();

}

Arrow::~Arrow() {
    std::cout << "deleting" << std::endl;
    delete m_model;
    m_model = 0l;
}

Model * Arrow::m_model = 0;
unsigned long Arrow::m_instance_count = 0lu;