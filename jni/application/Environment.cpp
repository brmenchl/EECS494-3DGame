//
//  Environment.cpp
//  game
//
//  Created by Bradley Menchl on 10/28/13.
//
//

#include "Environment.h"
#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Environment::Environment(const Point3f &center_,
             const Vector3f &scale_,
             const Quaternion &rotation_)
                : Game_Object(center_, scale_, rotation_),
                    m_source(new Sound_Source(get_Sounds()["collide"]))
{
    if(!m_instance_count)
        m_model = new Model("models/ground.3ds");
    ++m_instance_count;
    
    create_body();
}


Environment::~Environment() {
    delete m_source;
    if(!--m_instance_count) {
        delete m_model;
        m_model = 0lu;
    }
}

void Environment::groundRender(Point3f player_pos) {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    m_model->set_translate(Point3f(player_pos.x, player_pos.y, 0.0f));
    m_model->set_scale(m_scale);
    m_model->set_rotate(rotation.second, rotation.first);
    m_model->render();
}

void Environment::create_body() {
    m_body = Parallelepiped(m_position,
                            m_rotation * m_scale.get_i(),
                            m_rotation * m_scale.get_j(),
                            m_rotation * m_scale.get_k());
}

Model * Environment::m_model = 0;
unsigned long Environment::m_instance_count = 0lu;