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
#include "Checkpoint.h"
#include "Skybox.h"
#include "Arrow.h"

using namespace std;
using namespace Zeni;

class Play_State : public Gamestate_II {
    Play_State(const Play_State &);
    Play_State operator=(const Play_State &);
    
public:
    Play_State();
    void set_actions();
    
    void on_push();
    void on_pop();
    void on_cover();
    
    void render();
    void render_hud();
    void perform_logic();
    void on_event(const Zeni::Zeni_Input_ID &id, const float &confidence, const int &action);
    
    void update_time(float processing_time);
    void check_lose_condition();
    Vector3f get_player_velocity();
    void physics_loop(float processing_time);
    void rotate_player();
    void rotate_player(float time_step);
    void check_collisions();
    void explode_player();
    void invert_if_even(int &x);
    void read_high_scores();
    
private:
    enum GAME_STATE {
        CUT_SCENE,
        PLAY,
        LOSE,
        CRASH,
        WIN
    };
    
    static Vector3f gravity;
    static float look_sensitivity;
    static float roll_sensitivity;
    static float thrust_sensitivity;
    static float yaw_modifier;
    static float base_thrust;
    static float thrust_delta;
    static float thrust_range;
    
    vector<float> high_scores;
    list<Game_Object*> objects;
    list<Checkpoint*> checkpoints;
    list<Game_Object*> debris;
    list<Game_Object*> ground_tiles;
    list<Checkpoint*> next_checkpoints;
    int m_game_state;
    float x, y, w, h, roll;
    Zeni::Point2f vibration;
    float thrust_amount;
    float processing_time;
    float time_remaining;
    float time_of_last_checkpoint;
    float time_value_of_last_checkpoint;
    
    Zeni::Time_HQ time_passed;
    My_Camera m_camera;
    Player m_player;
    Environment m_ground;
    Skybox m_skybox;
    Arrow m_arrow;
    Fog m_fog;
    void add_score();
    static bool score_comp(const float score1, const float score2);
};

#endif /* defined(__game__Play_State__) */
