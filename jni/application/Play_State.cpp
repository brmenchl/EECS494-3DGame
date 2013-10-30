//
//  Play_State.cpp
//  game
//
//  Created by David Zilli on 10/21/13.
//
//

#include "Play_State.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <String.h>
#include <algorithm>
using namespace std;
using namespace Zeni;

Vector3f Play_State::gravity = Vector3f(0,0,-0.1);
float Play_State::look_sensitivity = 30000.0f;
float Play_State::roll_sensitivity = 11000.0f;
float Play_State::thrust_sensitivity = 30.0f;
float Play_State::yaw_modifier = 5.0f;
float Play_State::base_thrust = 1000.0f;
float Play_State::thrust_delta = 25.0f;
float Play_State::thrust_range = 250.0f;

Play_State::Play_State() : m_crate(Point3f(0.0f, 0.0f, -1.0f),
                                   Vector3f(9000.0f, 9000.0f, 1.0f)),
                            m_player(Point3f(100.0f, 8000.0f, 150.0f),
                                    Vector3f(1.0f, 1.0f, 1.0f)),
                            m_camera(Camera(Point3f(600.0f, 7800.0f, 50.0f),
                                            Quaternion(),
                                            1.0f, 10000.0f),
                                     Vector3f(0.0f, 0.0f, -39.0f),
                                     11.0f),
                            m_ground(),
                            m_skybox(),
                            m_game_state(CUT_SCENE),
        objects(),
        checkpoints(),
        high_scores(),
        debris(),
        x(0),
        y(0),
        w(0),
        h(0),
        roll(0),
        processing_time(0)
    {
        processing_time = 0.0f;
        time_remaining = 30.0f;
        
        /*Checkpoints*/
        Checkpoint* check1 = new Checkpoint(3.0f, Point3f(3500.0f, 3500.0f, 1700.0f));
        Checkpoint* check2 = new Checkpoint(3.0f, Point3f(1200.0f, 1400.0f, 100.0f));
        Checkpoint* check3 = new Checkpoint(3.0f, Point3f(7300.0f, 5300.0f, 500.0f));
        Checkpoint* check4 = new Checkpoint(0.0f, Point3f(8000.0f, 8000.0f, 5500.0f));
        
        check1->add_next_checkpoint(check2);
        check1->set_is_active(true);
        check2->add_next_checkpoint(check3);
        check3->add_next_checkpoint(check4);
        check4->set_as_victory_checkpoint();
        
        checkpoints.push_back(check1);
        checkpoints.push_back(check2);
        checkpoints.push_back(check3);
        checkpoints.push_back(check4);

        
        /*Buildings*/
        Crate* b1 = new Crate(Point3f(100, 500, 500), Vector3f(2000, 2000, 6000));
        Crate* sup1 = new Crate(Point3f(100, 500, 0), Vector3f(100, 100, 500));
        Crate* sup2 = new Crate(Point3f(100, 2400, 0), Vector3f(100, 100, 500));
        Crate* sup3 = new Crate(Point3f(1900, 500, 0), Vector3f(100, 100, 500));
        Crate* sup4 = new Crate(Point3f(1900, 2400, 0), Vector3f(100, 100, 500));
        Crate* b2 = new Crate(Point3f(2500, 500, 0), Vector3f(2000, 2000, 3000));
        Crate* b3 = new Crate(Point3f(4000, 4000, 0), Vector3f(100, 100, 900));
        Crate* b4 = new Crate(Point3f(4000, 4500, 0), Vector3f(100, 100, 1500));
        Crate* b5 = new Crate(Point3f(4000, 5000, 0), Vector3f(100, 100, 900));
        Crate* b8 = new Crate(Point3f(6000, 5000, 0), Vector3f(1000, 1000, 5000), Quaternion::Axis_Angle(Vector3f(0.0f, 1.0f, 0.0f), ::Zeni::Global::pi/12));
        Crate* b9 = new Crate(Point3f(6000, 7800, 0), Vector3f(1000, 1000, 5000));
        Crate* b10 = new Crate(Point3f(7800, 5000, 0), Vector3f(1000, 1000, 5000));
        Crate* b11 = new Crate(Point3f(7800, 7800, 0), Vector3f(1000, 1000, 5000));
        
        objects.push_back(&m_crate);
        objects.push_back(b1);
        objects.push_back(sup1);
        objects.push_back(sup2);
        objects.push_back(sup3);
        objects.push_back(sup4);
        objects.push_back(b2);
        objects.push_back(b3);
        objects.push_back(b4);
        objects.push_back(b5);
        objects.push_back(b8);
        objects.push_back(b9);
        objects.push_back(b10);
        objects.push_back(b11);

        set_pausable(true);
        
        set_actions();

        m_camera.track(&m_player);
        
    }

    void Play_State::on_push() {
        get_Window().set_mouse_state(Window::MOUSE_HIDDEN);
    }

    void Play_State::on_pop() {
        get_Controllers().reset_vibration_all();
    }

    void Play_State::on_cover() {
        get_Controllers().reset_vibration_all();
    }

    void Play_State::render() {
        Video &vr = get_Video();
        vr.set_3d(m_camera.get_camera());
        
//        get_Video().set_lighting(true);
//        get_Video().set_ambient_lighting(Color(1.0f, 0.0f, 0.0f, 0.0f));
//        get_Video().set_Light(0, Zeni::Light::Light(Color(.2, .5, .5, .5), Color(.5, .5, .5, .5), Color(.01, .5, .5, .5), Point3f(5000,5000,20000)));

        m_skybox.boxRender(m_player.get_position());
        
//        Zeni::Light::Light light = Zeni::Light::Light(Color(.2, .5, .5, .5), Color(.5, .7, .2, .5), Color(.01, .5, .5, .5), Point3f(5000,5000,10000), Vector3f(0,0,-1));
//        light.set_light_type(LIGHT_SPOT);
//        light.set_spot_phi(Zeni::Global::pi / 6);
//        light.set_spot_theta(Zeni::Global::pi / 4);
        //get_Video().set_Light(0, light);

        m_crate.render();
        
        std::list<Game_Object*>::iterator it;
        for(it = objects.begin(); it != objects.end(); it++){
            (*it)->render();
        }
        
        std::list<Checkpoint*>::iterator check_it;
        for(check_it = checkpoints.begin(); check_it != checkpoints.end(); check_it++){
            (*check_it)->render();
        }
        
//        vr.set_zwrite(false);
//        
//        m_skybox.boxRender(m_camera.get_camera().position);
//        
//        vr.set_zwrite(true);
        //m_ground.groundRender(m_player.get_position());
        
        if (m_game_state == CRASH) {
            m_player.Game_Object::set_velocity(Vector3f(0,0,0));
            std::list<Game_Object*>::iterator it;
            for(it = debris.begin(); it != debris.end(); it++){
                (*it)->render();
            }
        } else {
            m_player.render();
        }
        
        //vr.set_lighting(false);
        
        vr.set_2d();
        ostringstream stream;
        stream.precision(3);
        stream << "Time left: ";
        stream << time_remaining;
        Zeni::String hud(stream.str());
        get_Fonts()["title"].render_text(hud, Point2f(), Color());
        
        switch (m_game_state) {
            case WIN: {
                Font &score = get_Fonts()["score"];
                get_Fonts()["score"].render_text("Best Times:", Point2f(get_Window().get_width() - 200, 10), Color());

                for (int i = 0; i < high_scores.size() && i < 5; i++) {
                    get_Fonts()["score"].render_text(itoa(i+1) + ". " + ftoa(high_scores[i]), Point2f(get_Window().get_width() - 200, 10 + (i+1) * score.get_text_height() * 1.2), Color());

                }
                
                
                Font &f = get_Fonts()["title"];
                get_Fonts()["title"].render_text("You win!", Point2f(30, get_Window().get_height() -  f.get_text_height() * 2.2), Color());
                get_Fonts()["title"].render_text("Press B to play again", Point2f(30, get_Window().get_height() - f.get_text_height()), Color());
                break;
            }
                
            case LOSE: {
                Font &f = get_Fonts()["title"];
                get_Fonts()["title"].render_text("You ran out of time!", Point2f(30, get_Window().get_height() -  f.get_text_height() * 2.2), Color());
                get_Fonts()["title"].render_text("Press B to play again", Point2f(30, get_Window().get_height() - f.get_text_height()), Color());
                break;
            }
                
            case CRASH: {
                Font &f = get_Fonts()["title"];
                get_Fonts()["title"].render_text("You crashed!", Point2f(30, get_Window().get_height() -  f.get_text_height() * 2.2), Color());
                get_Fonts()["title"].render_text("Press B to play again", Point2f(30, get_Window().get_height() - f.get_text_height()), Color());
                break;
            }
                
            default:
                break;
        }

    }

    void Play_State::perform_logic() {
        //Update clocks
        const Time_HQ current_time = get_Timer_HQ().get_time();
        processing_time = float(current_time.get_seconds_since(time_passed));
        time_passed = current_time;
        
        
        if (m_game_state == CUT_SCENE && time_remaining < 28.0) {
            m_camera.chase(&m_player);
            m_game_state = PLAY;
        }

        
        switch (m_game_state) {
            case CUT_SCENE: {
                update_time(processing_time);
                physics_loop(processing_time);
                break;
            }
                
            case PLAY: {
                update_time(processing_time);
                rotate_player();
                physics_loop(processing_time);
                check_collisions();
                check_lose_condition();
                break;
            }
                
            case WIN: {
                //update_time(processing_time);
                physics_loop(processing_time);
                break;
            }
                
            case LOSE: {
                update_time(processing_time);
                physics_loop(processing_time);
                break;
            }
                
            case CRASH: {
                update_time(processing_time);
                physics_loop(processing_time);
                break;
            }
        }
        
    }

    void Play_State::update_time(float processing_time) {
        if (time_remaining > 0) {
            time_remaining -= processing_time;
        } else if (time_remaining < 0) {
            time_remaining = 0;
        }
    }

    void Play_State::check_lose_condition() {
        if (time_remaining == 0) {
            m_game_state = LOSE;
            m_camera.track(&m_player);
        }
    }

    void Play_State::physics_loop(float processing_time) {
        Vector3f velocity = get_player_velocity();
        
        if (m_game_state == CRASH) {
            velocity = gravity;
        }
        
        
        /** Keep delays under control (if the program hangs for some time, we don't want to lose responsiveness) **/
        if(processing_time > 0.1f) {
            processing_time = 0.1f;
        }
        
        m_player.set_velocity(velocity);
        
        /** Physics processing loop**/
        for(float time_step = 0.0005f; processing_time > 0.0f;) {
            
            if(time_step > processing_time) {
                time_step = processing_time;
            }
            
            /** Move each object which needs to **/
            std::list<Game_Object*>::iterator it;
            for(it = debris.begin(); it != debris.end(); it++){
                (*it)->set_velocity((*it)->get_velocity() + gravity);
                (*it)->step(time_step);
            }
            
            std::list<Checkpoint*>::iterator check_it;
            for(check_it = checkpoints.begin(); check_it != checkpoints.end(); check_it++){
                (*check_it)->step(time_step);
            }
            
            m_player.step(time_step);
            m_camera.step(time_step, velocity.get_k());
            processing_time -= time_step;
        }
    }

    void Play_State::rotate_player() {
        /** Rotate the aircraft **/
        m_player.rotate(Quaternion(-w / (look_sensitivity * yaw_modifier), h / look_sensitivity, roll / roll_sensitivity));
        m_player.adjust_vectors();
    }

    Vector3f Play_State::get_player_velocity() {
        //Get jet thrust
        if (m_game_state == PLAY) {
            /** Calculate current thrust**/
            float desired_thrust = base_thrust + thrust_range * y;
            
            if (thrust_amount > desired_thrust) {
                thrust_amount -= thrust_delta;
            }
            
            if (thrust_amount < desired_thrust) {
                thrust_amount += thrust_delta;
            }
            
            if (thrust_amount == desired_thrust) {
                thrust_amount = desired_thrust;
            }
            
        } else {
            thrust_amount = base_thrust;
        }
        
        /** Get velocity vector */
        return Vector3f((thrust_amount) * m_player.get_forward_vec().get_ij() + (thrust_amount) * m_player.get_forward_vec().get_k());
    }

    void Play_State::check_collisions() {
        if(m_player.is_crashing(objects)){
            m_game_state = CRASH;
            explode_player();
        }
        
        std::list<Checkpoint*>::iterator check_it;
        for(check_it = checkpoints.begin(); check_it != checkpoints.end(); check_it++){
            if (m_player.is_crashing((*check_it)) && (*check_it)->get_is_active()) {
                time_remaining += (*check_it)->get_time_value();
                (*check_it)->set_is_active(false);
                (*check_it)->activate_next_checkpoints();
                cout << "CHECKPOINT" << endl;
                if ((*check_it)->get_is_victory_checkpoint()) {
                    m_game_state = WIN;
                    add_score();
                    read_high_scores();
                }
            }
        }
    }

    /** Generates a bunch of tiny crates that shoot off in random directions */
    void Play_State::explode_player() {
        for (int i = 0; i < 75; i++) {
            int x, y, z;
            x = rand() % 100;
            y = rand() % 100;
            z = rand() % 100;
            invert_if_even(x);
            invert_if_even(y);
            invert_if_even(z);
            
            Crate* c = new Crate(m_player.get_position(), Vector3f(5, 5, 5));
            c->set_velocity(Vector3f(x, y, z));
            debris.push_back(c);
        }
        m_camera.track(debris.front());
    }

    void Play_State::invert_if_even(int &x) {
        if ((x % 2) == 0) {
            x *= -1;
        }
    }

    void Play_State::on_event(const Zeni_Input_ID &id, const float &confidence, const int &action) {
        if(confidence > 0.5f)
            get_Game().write_to_console(ulltoa(id.which) + '.' + ulltoa(id.subid) + ':' + ulltoa(action));
        
        switch(action) {
            case 1:
                if(confidence == 1.0f) {
                    Game &game = get_Game();
                    game.push_state(new Popup_Menu_State);
                }
                break;
                
            case 2: //Left Toggle X
                if (abs(confidence) > 0.25f) {
                    w = confidence * (get_Window().get_height());
                } else {
                    w = 0.0f;
                }
                break;
                
            case 3: //Left Toggle Y

                break;
                
            case 4: //Right Toggle X - Steering
                
                if (abs(confidence) > 0.25f) {
                    roll = (confidence * get_Window().get_width() / 2);
                } else {
                    roll = 0;
                }
                break;
                
            case 5: //Right toggle Y
                if (abs(confidence) > 0.25f) {
                    h = -confidence * (get_Window().get_height());
                } else {
                   h = 0.0f;
                }
                break;
                
            case 6: //D up
                m_camera.set_horizon_lock();
                break;
                
            case 10://D down
                m_camera.set_rolling();
                break;
                
            case 12:
                m_camera.track(&m_player);
                break;
                
            case 7: //Trigger Right - Thrust
                if (abs(confidence) > 0.15f) {
                    y = confidence;
                } else {
                    y = 0;
                }
                break;
                
            case 11: //Trigger Left - Thrust
                if (abs(confidence) > 0.15f) {
                    y = -confidence;
                } else {
                    y = 0;
                }
                break;
                
            case 8: //Left shoulder - Zoom closer to plane
                m_camera.decrease_follow_distance();
                break;
                
            case 9: //Right shoulder - Zoom farther from plane
                m_camera.increase_follow_distance();
                break;
                
            case 13: {//B button
                if (m_game_state != CUT_SCENE && m_game_state != PLAY) {
                    get_Game().pop_state();
                    Play_State* newplay = new Play_State();
                    get_Game().push_state(newplay);
                }
                break;
            }
                
            default:
                break;
        }
    }

void Play_State::set_actions() {
    set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE), 1);
    set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_BACK), 1);
    set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTX /* x-axis */), 2);
    set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTY /* y-axis */), 3);
    set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTX /* x-rotation */), 4);
    set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTY /* y-rotation */), 5);
    set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_DPAD_UP /* z-axis */), 6);
    set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_DPAD_DOWN /* z-axis */), 10);
    set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_DPAD_LEFT /* z-axis */), 12);
    set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERRIGHT /* z-axis */), 7);
    set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERLEFT /* z-axis */), 11);
    set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_LEFTSHOULDER /* roll */), 8);
    set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER /* roll */), 9);
    set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_B), 13);
}

void Play_State::add_score() {
    ofstream myfile;
    myfile.open (get_File_Ops().get_appdata_path().std_str() + "scores.txt", ios::app);
    myfile << time_remaining << "\n";
    myfile.close();
}

void Play_State::read_high_scores() {
    //Open file
    std::ifstream inFile;
    inFile.open(get_File_Ops().get_appdata_path().std_str() + "scores.txt");
    float input;
    
    while(inFile >> input)
    {
        high_scores.push_back(input);
    }
    
    //Close file
    inFile.close();
    std::sort(high_scores.begin(), high_scores.end(), Play_State::score_comp);
    for (int i = 0; i < high_scores.size(); i++) {
        cout << high_scores[i] << endl;
    }
}

bool Play_State::score_comp(const float score1, const float score2) {
    return score1 > score2;
}