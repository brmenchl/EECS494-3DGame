//
//  Turbine.cpp
//  game
//
//  Created by Bradley Menchl on 10/31/13.
//
//

#include "Turbine.h"
#include <zenilib.h>
#include "Game_Object.h"
#include "Turbine_piece.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;


Turbine::Turbine(const Point3f &corner_,
               const Vector3f &scale_,
               const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_)
{
    if(!m_instance_count)
        //        m_model = new Model("models/building1center.3ds");
        ++m_instance_count;
    
    Turbine_piece* wing1 = new Turbine_piece(String("models/turbinewings.3ds"),Point3f(corner_.x+100, corner_.y-150, corner_.z+4900),
                                             Vector3f(18,18,18),
                                             Quaternion::Axis_Angle(Vector3f(0.0f, 1.0f, 0.0f), 0.0f));
    Turbine_piece* wing2 = new Turbine_piece(String("models/turbinewings.3ds"),Point3f(corner_.x+100, corner_.y-150, corner_.z+4900),
                                             Vector3f(18,18,18),
                                             Quaternion::Axis_Angle(Vector3f(0.0f, 1.0f, 0.0f), 2*Global::pi/3));
    Turbine_piece* wing3 = new Turbine_piece(String("models/turbinewings.3ds"),Point3f(corner_.x+100, corner_.y-150, corner_.z+4900),
                                             Vector3f(18,18,18),
                                             Quaternion::Axis_Angle(Vector3f(0.0f, 1.0f, 0.0f),4*Global::pi/3));
    Turbine_piece* base = new Turbine_piece(String("models/turbinebase.3ds"),Point3f(corner_.x, corner_.y, corner_.z));
    
    
    m_bodies.push_back(wing1);
    m_bodies.push_back(wing2);
    m_bodies.push_back(wing3);
    m_bodies.push_back(base);
    
    create_body();
}

Turbine::Turbine(const Turbine &rhs)
: Game_Object(rhs)
{
    ++m_instance_count;
    
    create_body();
}

Turbine & Turbine::operator=(const Turbine &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Turbine::~Turbine() {
    
}

void Turbine::add_bodies_to_list(std::list<Game_Object *> &list) {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        list.push_back((*it));
    }
}

void Turbine::render() {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        (*it)->render();
    }
}

void Turbine::step(const float &time_step) {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != std::prev(m_bodies.end()); ++it){
        (*it)->step(time_step);
        (*it)->adjust_vectors();
    }
    create_body();
}

void Turbine::create_body() {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        (*it)->create_body();
    }
}



void Turbine::collide() {
    
}