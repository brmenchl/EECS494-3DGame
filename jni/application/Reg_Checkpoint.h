//
//  Reg_Checkpoint.h
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#ifndef __game__Reg_Checkpoint__
#define __game__Reg_Checkpoint__

#include <iostream>
#include <iostream>
#include <zenilib.h>
#include "Game_Object.h"
#include "Checkpoint.h"

using namespace Zeni;

class Reg_Checkpoint : public Checkpoint {
public:
    Reg_Checkpoint(float time_value_,
                         const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
                         const Zeni::Vector3f &scale_ = Zeni::Vector3f(3.0f, 3.0f, 3.0f),
                         const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    ~Reg_Checkpoint();
    
    void render();
    
private:
    
    static Zeni::Model * m_model;
    static unsigned long m_instance_count;
    void load_model();
    
};



#endif /* defined(__game__Reg_Checkpoint__) */
