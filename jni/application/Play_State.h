//
//  Play_State.h
//  game
//
//  Created by David Zilli on 10/21/13.
//
//

#ifndef __game__Play_State__
#define __game__Play_State__

#include <iostream>
#include <zenilib.h>
#include "Player.h"
#include "Crate.h"

using namespace std;
using namespace Zeni;

class Play_State : public Gamestate_II {
    Play_State(const Play_State &);
    Play_State operator=(const Play_State &);
    
public:
    Play_State();
    
    void on_push();
    void on_pop();
    void on_cover();
    
    void render();
    void perform_logic();
    void on_event(const Zeni::Zeni_Input_ID &id, const float &confidence, const int &action);
    void on_mouse_motion(const SDL_MouseMotionEvent &event);
    
private:
    float x, y, w, h, roll;
    Zeni::Point2f vibration;
    float look_sensitivity;
    Zeni::Time_HQ time_passed;
    Player m_player;
    Crate m_crate;
    
    void partial_step(const float &time_step, const Vector3f &velocity);

};

#endif /* defined(__game__Play_State__) */
