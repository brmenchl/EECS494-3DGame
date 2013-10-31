//
//  Bridge.cpp
//  game
//
//  Created by Bradley Menchl on 10/31/13.
//
//

#include "Bridge.h"
#include <zenilib.h>
#include "Game_Object.h"
#include "Bridge_piece.h"

using namespace Zeni;
using namespace Zeni::Collision;
using namespace std;


Bridge::Bridge(const Point3f &corner_,
                       const Vector3f &scale_,
                       const Quaternion &rotation_)
: Game_Object(corner_, scale_, rotation_)
{
    if(!m_instance_count)
        //        m_model = new Model("models/building1center.3ds");
        ++m_instance_count;
    
    Bridge_piece* leg1 = new Bridge_piece(String("models/bridgeleg.3ds"),Point3f(corner_.x, corner_.y+15, corner_.z));
    Bridge_piece* leg2 = new Bridge_piece(String("models/bridgeleg.3ds"),Point3f(corner_.x, corner_.y+490, corner_.z));
    Bridge_piece* leg3 = new Bridge_piece(String("models/bridgeleg.3ds"),Point3f(corner_.x, corner_.y+975, corner_.z));
    Bridge_piece* leg4 = new Bridge_piece(String("models/bridgeleg.3ds"),Point3f(corner_.x, corner_.y+1453, corner_.z));
    Bridge_piece* leg5 = new Bridge_piece(String("models/bridgeleg.3ds"),Point3f(corner_.x, corner_.y+1930, corner_.z));
    Bridge_piece* top = new Bridge_piece(String("models/bridge.3ds"),Point3f(corner_.x, corner_.y, corner_.z+174));
    
    
    
    m_bodies.push_back(leg1);
    m_bodies.push_back(leg2);
    m_bodies.push_back(leg3);
    m_bodies.push_back(leg4);
    m_bodies.push_back(leg5);
    m_bodies.push_back(top);
    
    create_body();
}

Bridge::Bridge(const Bridge &rhs)
: Game_Object(rhs)
{
    ++m_instance_count;
    
    create_body();
}

Bridge & Bridge::operator=(const Bridge &rhs) {
    m_position = rhs.m_position;
    m_scale = rhs.m_scale;
    m_rotation = rhs.m_rotation;
    
    create_body();
    
    return *this;
}

Bridge::~Bridge() {
    
}

void Bridge::add_bodies_to_list(std::list<Game_Object *> &list) {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        list.push_back((*it));
    }
}

void Bridge::render() {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        (*it)->render();
    }
}

void Bridge::step(const float &time_step) {
    create_body();
}

void Bridge::create_body() {
    std::list<Game_Object*>::iterator it;
    for(it = m_bodies.begin(); it != m_bodies.end(); it++){
        (*it)->create_body();
    }
}



void Bridge::collide() {
    
}