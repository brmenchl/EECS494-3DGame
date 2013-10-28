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
using namespace std;
using namespace Zeni;

Play_State::Play_State() : m_crate(Point3f(-200.0f, -200.0f, 0.0f),
                                   Vector3f(9000.0f, 9000.0f, 9000.0f)),
                            m_obstacle(Point3f(3500.0f, 3500.0f, 1700.0f),
                                       Vector3f(300.0f, 300.0f, 300.0f)),
                            m_player(Point3f(150.0f, 150.0f, 150.0f),
                                    Vector3f(1.0f, 1.0f, 1.0f)),
            m_camera(Camera(Point3f(1000.0f, 0.0f, 50.0f),
                    Quaternion(),
                    1.0f, 10000.0f),
             Vector3f(0.0f, 0.0f, -39.0f),
             11.0f),
        base_thrust(15.0f),
        thrust_delta(0.5f),
        thrust_range(10.0f),
        m_game_state(CUT_SCENE),
        objects(),
        x(0),
        y(0),
        w(0),
        h(0),
        roll(0)
    {
    
        look_sensitivity = 25000.0f;
        roll_sensitivity = 8000.0f;
        thrust_sensitivity = 30.0f;
        time_remaining = 30.0f;
                
        objects.push_back(&m_obstacle);
        set_pausable(true);
        
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
        m_crate.render();
        m_obstacle.render();
        m_player.render();
        
        vr.set_2d();
        ostringstream stream;
        stream.precision(3);
        stream << "Time left: ";
        stream << time_remaining;
        Zeni::String hud(stream.str());
        get_Fonts()["title"].render_text(hud, Point2f(), Color());
        
        switch (m_game_state) {
            case WIN:
                get_Fonts()["title"].render_text("You win!", Point2f(30, get_Window().get_height() / 2), Color());
                break;
            
            case LOSE:
                get_Fonts()["title"].render_text("You ran out of time!", Point2f(30, get_Window().get_height() / 2), Color());
                break;
                
            default:
                break;
        }

    }

    void Play_State::perform_logic() {
        
        //Update clocks
        const Time_HQ current_time = get_Timer_HQ().get_time();
        float processing_time = float(current_time.get_seconds_since(time_passed));
        time_passed = current_time;
        Vector3f velocity;
        
        update_time(processing_time);
        velocity = get_player_velocity();
        physics_loop(processing_time, velocity);
        
        switch (m_game_state) {
            case CUT_SCENE: {
                break;
            }
                
            case PLAY: {
                /** Check lose condition */
                check_collisions();
                check_lose_condition();
                rotate_player();
                break;
            }
                
            case WIN: {

                break;
            }
                
            case LOSE: {

                break;
            }
        }
        
        
        /** Just testing playing around with game states here! */
        if (time_remaining < 28.0 && time_remaining > 20.0) {
            m_camera.chase(&m_player);
            m_game_state = PLAY;
        }
        /** End game states tests */
        
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

    void Play_State::physics_loop(float processing_time, Vector3f velocity) {
        /** Keep delays under control (if the program hangs for some time, we don't want to lose responsiveness) **/
        if(processing_time > 0.1f) {
            processing_time = 0.1f;
        }
        
        /** Physics processing loop**/
        for(float time_step = 0.05f; processing_time > 0.0f; processing_time -= time_step) {
            
            if(time_step > processing_time) {
                time_step = processing_time;
            }
            
            /** Try to move on each axis **/
            partial_step(time_step, velocity.get_i());
            partial_step(time_step, velocity.get_j());
            partial_step(time_step, velocity.get_k());
            m_camera.step(time_step);
        }

    }

    void Play_State::rotate_player() {
        /** Rotate the aircraft **/
        m_player.rotate(Quaternion(-w / (look_sensitivity * 7), h / look_sensitivity, roll / roll_sensitivity));
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
        return Vector3f((thrust_amount) * 50.0f * m_player.get_forward_vec().get_ij() + (thrust_amount) * 50.0f * m_player.get_forward_vec().get_k());
    }

    void Play_State::check_collisions() {
        if(m_player.is_crashing(objects)){
            //            m_game_state = LOSE;
            //            Play_State* newplay = new Play_State();
            //            get_Game().push_state(newplay);
            m_game_state = LOSE;
            ofstream myfile;
            myfile.open (get_File_Ops().get_appdata_path().std_str() + "scores.txt", ios::app);
            myfile << time_remaining << "\n";
            myfile.close();
        }
    }

    void Play_State::partial_step(const float &time_step, const Vector3f &velocity) {
        m_player.set_velocity(velocity);
        m_player.step(time_step);
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
                m_camera.chase(&m_player);
                break;
                
            case 10://D down
                m_camera.detach_camera();
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
        
            default:
                break;
        }
    }