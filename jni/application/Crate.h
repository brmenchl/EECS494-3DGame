#ifndef CRATE_H
#define CRATE_H

#include <zenilib.h>
#include "Game_Object.h"

using namespace Zeni;

class Crate : public Game_Object {
  public:
    Crate(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
          const Zeni::Vector3f &scale_ = Zeni::Vector3f(1.0f, 1.0f, 1.0f),
          const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
    Crate(const Crate &rhs);
    Crate & operator=(const Crate &rhs);
    ~Crate();

    void render();
    void step(const float &time_step);
    void set_velocity(const Zeni::Vector3f &velocity_) {m_velocity = velocity_;}
    Point3f get_position() {return m_position;}

    void collide();

    const Zeni::Collision::Parallelepiped & get_body() const {return m_body;}

  private:

    static Zeni::Model * m_model;
    static unsigned long m_instance_count;

    Zeni::Sound_Source * m_source;
  };

#endif
