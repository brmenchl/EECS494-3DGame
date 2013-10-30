//
//  Arrow.h
//  game
//
//  Created by Bradley Menchl on 10/30/13.
//
//

#ifndef __game__Arrow__
#define __game__Arrow__

#include <zenilib.h>
#include "Game_Object.h"
#include "My_Camera.h"

using namespace Zeni;

class Arrow : public Game_Object {
public:
    Arrow(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
           const Zeni::Vector3f &scale_ = Zeni::Vector3f(0.08f, 0.03f, 0.08f),
           const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    ~Arrow();
    void render(){};
    void arrowRender(My_Camera &m_cam);
    void collide(){};
private:
    static unsigned long m_instance_count;
    static Zeni::Model * m_model;
};
#endif /* defined(__game__Arrow__) */
