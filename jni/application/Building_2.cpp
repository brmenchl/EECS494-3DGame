//
//  Building_2.cpp
//  game
//
//  Created by Bradley Menchl on 10/30/13.
//
//

#include "Building_2.h"

//
//  Building_2.cpp
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#include "Building_2.h"
#include <zenilib.h>
#include <iostream>
#include "Game_Object.h"
#include "Building_2_piece.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Building_2::Building_2(const Point3f &corner_,
                                     const Vector3f &scale_,
                                     const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_)
{
    if(!m_instance_count)
        //        m_model = new Model("models/building1center.3ds");
        ++m_instance_count;
    
    Building_2_piece* l1 = new Building_2_piece(String("models/building2l1.3ds"),Point3f(corner_.x, corner_.y, corner_.z));
    Building_2_piece* l2 = new Building_2_piece(String("models/building2l2.3ds"),Point3f(corner_.x+150, corner_.y+95, corner_.z+865));
    Building_2_piece* l3 = new Building_2_piece(String("models/building2l3.3ds"),Point3f(corner_.x+229, corner_.y+190, corner_.z + 1738));
    Building_2_piece* l4 = new Building_2_piece(String("models/building2l4.3ds"),Point3f(corner_.x+292, corner_.y+240, corner_.z+2250));
    
    
    
    m_bodies.push_back(l1);
    m_bodies.push_back(l2);
    m_bodies.push_back(l3);
    m_bodies.push_back(l4);
    
    create_body();
}

Building_2::Building_2(const Building_2 &rhs)
: Game_Object(rhs)
{
    ++m_instance_count;
    
    create_body();
}

Building_2 & Building_2::operator=(const Building_2 &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Building_2::~Building_2() {
    
}

void Building_2::add_bodies_to_list(std::list<Game_Object *> &list) {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        list.push_back((*it));
    }
}

void Building_2::render() {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        (*it)->render();
    }
}

void Building_2::step(const float &time_step) {
    create_body();
}

void Building_2::create_body() {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        (*it)->create_body();
    }
}



void Building_2::collide() {
    
}
