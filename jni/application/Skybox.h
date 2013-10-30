//
//  Skybox.h
//  game
//
//  Created by Bradley Menchl on 10/29/13.
//
//

#ifndef __game__Skybox__
#define __game__Skybox__

#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Skybox : public Game_Object {
public:
    Skybox(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
           const Zeni::Vector3f &scale_ = Zeni::Vector3f(80.0f, 80.0f, 80.0f),
           const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    ~Skybox();
    void render(){};
    void boxRender(Point3f player_pos);
    void collide(){};
private:
    static unsigned long m_instance_count;
    static Zeni::Model * m_model;
};

#endif /* defined(__game__Skybox__) */

