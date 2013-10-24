//
//  Play_State.cpp
//  game
//
//  Created by David Zilli on 10/21/13.
//
//

#include "Play_State.h"
using namespace std;
using namespace Zeni;

Play_State::Play_State() : m_crate(Point3f(-200.0f, -200.0f, 0.0f),
                                   Vector3f(3000.0f, 3000.0f, 3000.0f)),
                            m_player_crate(Point3f(150.0f, 0.0f, 50.0f),
                                    Vector3f(30.0f, 30.0f, 30.0f)),
            m_camera(Camera(Point3f(0.0f, 0.0f, 50.0f),
                    Quaternion(),
                    1.0f, 10000.0f),
             Vector3f(0.0f, 0.0f, -39.0f),
             11.0f) {
    
        look_sensitivity = 15000.0f;
        roll_sensitivity = 6500.0f;
        thrust_sensitivity = 30.0f;
        set_pausable(true);
        
        set_action(Zeni_Input_ID(SDL_KEYDOWN, SDLK_ESCAPE), 1);
        set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_BACK), 1);
        set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTX /* x-axis */), 2);
        set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_LEFTY /* y-axis */), 3);
        set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTX /* x-rotation */), 4);
        set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_RIGHTY /* y-rotation */), 5);
        set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_DPAD_UP /* z-axis */), 6);
        set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_DPAD_DOWN /* z-axis */), 10);
        set_action(Zeni_Input_ID(SDL_CONTROLLERAXISMOTION, SDL_CONTROLLER_AXIS_TRIGGERRIGHT /* z-axis */), 7);
        set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_LEFTSHOULDER /* roll */), 8);
        set_action(Zeni_Input_ID(SDL_CONTROLLERBUTTONDOWN, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER /* roll */), 9);


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
        m_player_crate.render();
    }

    void Play_State::perform_logic() {
        const Time_HQ current_time = get_Timer_HQ().get_time();
        float processing_time = float(current_time.get_seconds_since(time_passed));
        time_passed = current_time;
        
        /** Get current rotation from the player **/
        Quaternion rotation = m_player_crate.get_rotation();
        
        const Vector3f forward = rotation * Vector3f(1,0,0).normalized();
//        const Vector3f left = rotation * Vector3f(0,1,0).get_ij().normalized();
//        const Vector3f up = rotation * Vector3f(0,0,1).get_jk().normalized();
        
        /** Get velocity vector split into a number of axes **/
        const Vector3f velocity = (-y) * 50.0f * forward.get_ij() + (-y) * 50.0f * forward.get_k();
        const Vector3f y_vel = velocity.get_i();
        const Vector3f x_vel = velocity.get_j();
        const Vector3f z_vel = velocity.get_k();
        
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
            partial_step(time_step, x_vel);
            partial_step(time_step, y_vel);
            partial_step(time_step, z_vel);
            
            /** Look around **/
//            m_camera.adjust_pitch(h / look_sensitivity);
//            m_camera.turn_left_xy(-w / look_sensitivity);
//            m_camera.adjust_roll(roll / 100);
            m_player_crate.rotate(Quaternion(-w / look_sensitivity, h / look_sensitivity, roll / roll_sensitivity));
            
            /** keep player above the ground **/
            const Point3f &position = m_camera.get_camera().position;
            if(position.z < 50.0f) {
                m_camera.set_position(Point3f(position.x, position.y, 50.0f));
            }
        }
    }

    void Play_State::partial_step(const float &time_step, const Vector3f &velocity) {
        //m_camera.set_velocity(velocity);
        m_player_crate.set_velocity(velocity);
        //const Point3f backup_position = m_camera.get_camera().position;
        m_camera.step(time_step);
        m_player_crate.step(time_step);
        
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
                m_camera.attach_camera(&m_player_crate);
                break;
                
            case 10://D down
                m_camera.detach_camera();
                break;
                
            case 7: //Trigger Right - Thrust
                if (abs(confidence) > 0.15f) {
                    y = -(confidence * get_Window().get_height() / 2) / thrust_sensitivity;
                } else {
                    y = 0;
                }
                break;
                
            case 8: //Left shoulder
                break;
                
            case 9: //Right shoulder
                break;
        
            default:
                break;
        }
    }