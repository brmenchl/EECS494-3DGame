//
//  Environment.h
//  game
//
//  Created by Bradley Menchl on 10/28/13.
//
//

#ifndef __game__Environment__
#define __game__Environment__

#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Environment : public Game_Object {
public:
    Environment(const Zeni::Point3f &center_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
          const Zeni::Vector3f &scale_ = Zeni::Vector3f(200.0f, 200.0f, 200.0f),
          const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    ~Environment();
    void groundRender(Point3f player_pos);
    void render(){};
    void collide(){};
    
private:
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    
    Zeni::Sound_Source * m_source;
    
};

#endif /* defined(__game__Environment__) */
