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
#include "Environment.h"
#include "My_Camera.h"

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
    
    void update_time(float processing_time);
    void check_lose_condition();
    Vector3f get_player_velocity();
    void physics_loop(float processing_time);
    void rotate_player();
    void check_collisions();
    
private:
    enum GAME_STATE {
        CUT_SCENE,
        PLAY,
        LOSE,
        WIN
    };
    
    static float look_sensitivity;
    static float roll_sensitivity;
    static float thrust_sensitivity;
    static float yaw_modifier;
    static float base_thrust;
    static float thrust_delta;
    static float thrust_range;
    
    list<Game_Object*> objects;
    int m_game_state;
    float x, y, w, h, roll;
    Zeni::Point2f vibration;
    float thrust_amount;
    float time_remaining;
    
    Zeni::Time_HQ time_passed;
    My_Camera m_camera;
    Crate m_crate;
    Crate m_obstacle;
    Player m_player;
    Environment m_ground;
    
    void partial_step(const float &time_step, const Vector3f &velocity);
    

};

#endif /* defined(__game__Play_State__) */
