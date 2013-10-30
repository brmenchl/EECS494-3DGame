//
//  Skybox.cpp
//  game
//
//  Created by Bradley Menchl on 10/29/13.
//
//

#include "Skybox.h"
#include <zenilib.h>

using namespace Zeni;

Skybox::Skybox(const Point3f &corner_,
               const Vector3f &scale_,
               const Quaternion &rotation_)
                : Game_Object(corner_, scale_, rotation_)
{
    
    if(!m_instance_count){
        m_modelS1 = new Model("models/side1Sky.3ds");
        skybox.push_back(m_modelS1);
        m_modelS2 = new Model("models/side2Sky.3ds");
        skybox.push_back(m_modelS2);
        m_modelS3 = new Model("models/side3Sky.3ds");
        skybox.push_back(m_modelS3);
        m_modelS4 = new Model("models/side4Sky.3ds");
        skybox.push_back(m_modelS4);
        m_modelTop = new Model("models/topSky.3ds");
        skybox.push_back(m_modelTop);
        ++m_instance_count;
    }
}

void Skybox::boxRender(Point3f player_pos) {
    const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
    for(Model *m : skybox){
        m->set_translate(Point3f(player_pos.x, player_pos.y, 0.0f));
        m->set_scale(m_scale);
        m->set_rotate(rotation.second, rotation.first);
        m->render();
    }
}

Skybox::~Skybox() {
    
    if(!--m_instance_count) {
        for(Model *m : skybox){
            delete m;
            m = 0l;
        }
    }
}

Model * Skybox::m_modelS1 = 0;
Model * Skybox::m_modelS2 = 0;
Model * Skybox::m_modelS3 = 0;
Model * Skybox::m_modelS4 = 0;
Model * Skybox::m_modelTop = 0;
unsigned long Skybox::m_instance_count = 0lu;