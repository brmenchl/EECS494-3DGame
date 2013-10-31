//
//  Platform_Building.cpp
//  game
//
//  Created by David Zilli on 10/30/13.
//
//

#include "Platform_Building.h"
#include <zenilib.h>
#include <iostream>
#include "Game_Object.h"
#include "Building_1.h"
#include "Building_Column.h"
#include "Building_Platform.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;

Platform_Building::Platform_Building(const Point3f &corner_,
                       const Vector3f &scale_,
                       const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_)
{
    if(!m_instance_count)
//        m_model = new Model("models/building1center.3ds");
    ++m_instance_count;
    
    Building_1* build_sup = new Building_1(Point3f(corner_.x + 500, corner_.y + 500, corner_.z));
    Building_Platform* bplat =  new Building_Platform(Point3f(corner_.x, corner_.y, corner_.z + 2700));
    Building_Platform* bplat2 = new Building_Platform(Point3f(corner_.x, corner_.y, corner_.z + 5900));
    Building_Column* bcol1 = new Building_Column(Point3f(corner_.x + 100, corner_.y + 100, corner_.z));
    Building_Column* bcol2 = new Building_Column(Point3f(corner_.x + 500, corner_.y + 0, corner_.z));
    Building_Column* bcol3 = new Building_Column(Point3f(corner_.x + 0, corner_.y + 500, corner_.z));
    
    Building_Column* bcol4 = new Building_Column(Point3f(corner_.x + 100, corner_.y + 2800, corner_.z));
    Building_Column* bcol5 = new Building_Column(Point3f(corner_.x + 500, corner_.y + 2800, corner_.z));
    Building_Column* bcol6 = new Building_Column(Point3f(corner_.x + 0, corner_.y + 2300, corner_.z));
    
    Building_Column* bcol7 = new Building_Column(Point3f(corner_.x + 2800, corner_.y + 100, corner_.z));
    Building_Column* bcol8 = new Building_Column(Point3f(corner_.x + 2800, corner_.y + 500, corner_.z));
    Building_Column* bcol9 = new Building_Column(Point3f(corner_.x + 2300, corner_.y + 0, corner_.z));
    
    Building_Column* bcol10 = new Building_Column(Point3f(corner_.x + 2800, corner_.y + 2800, corner_.z));
    Building_Column* bcol11 = new Building_Column(Point3f(corner_.x + 2300, corner_.y + 2800, corner_.z));
    Building_Column* bcol12 = new Building_Column(Point3f(corner_.x + 2800, corner_.y + 2300, corner_.z));

    
    m_bodies.push_back(build_sup);
    m_bodies.push_back(bplat);
    m_bodies.push_back(bplat2);
    m_bodies.push_back(bcol1);
    m_bodies.push_back(bcol2);
    m_bodies.push_back(bcol3);
    m_bodies.push_back(bcol4);
    m_bodies.push_back(bcol5);
    m_bodies.push_back(bcol6);
    m_bodies.push_back(bcol7);
    m_bodies.push_back(bcol8);
    m_bodies.push_back(bcol9);
    m_bodies.push_back(bcol10);
    m_bodies.push_back(bcol11);
    m_bodies.push_back(bcol12);
    
    create_body();
}

Platform_Building::Platform_Building(const Platform_Building &rhs)
: Game_Object(rhs)
{
    ++m_instance_count;
    
    create_body();
}

Platform_Building & Platform_Building::operator=(const Platform_Building &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Platform_Building::~Platform_Building() {

}

void Platform_Building::add_bodies_to_list(std::list<Game_Object *> &list) {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        list.push_back((*it));
    }
}

void Platform_Building::render() {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        (*it)->render();
    }
}

void Platform_Building::step(const float &time_step) {
    m_position += time_step * m_velocity;
    create_body();
}

void Platform_Building::create_body() {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        (*it)->create_body();
    }
}



void Platform_Building::collide() {

}
