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
#include "Debris.h"
#include "Residence.h"
#include "Building_1.h"
#include "Building_2.h"
#include "Building_2_piece.h"
#include "Building_Column.h"
#include "Building_Platform.h"
#include "Platform_Building.h"
#include "Grass.h"
#include "Building_2.h"
#include "Road_Straight.h"
#include "Road_Intersection.h"
#include "Challenge_Checkpoint.h"
#include "Reg_Checkpoint.h"
#include "Bridge.h"

using namespace std;
using namespace Zeni;

Vector3f Play_State::gravity = Vector3f(0,0,-0.1);
float Play_State::look_sensitivity = 30000.0f;
float Play_State::roll_sensitivity = 11000.0f;
float Play_State::thrust_sensitivity = 30.0f;
float Play_State::yaw_modifier = 5.0f;
float Play_State::base_thrust = 1250.0f;
float Play_State::thrust_delta = 10.0f;
float Play_State::thrust_range = 150.0f;

Play_State::Play_State() : m_player(Point3f(0.0f, 8000.0f, 150.0f),
                                    Vector3f(1.0f, 1.0f, 1.0f)),
                            m_camera(Camera(Point3f(1200.0f, 7800.0f, 50.0f),
                                            Quaternion(),
                                            1.0f, 90000.0f),
                                     Vector3f(0.0f, 0.0f, -39.0f),
                                     11.0f),
                            m_arrow(),
                            m_skybox(),
                            m_game_state(CUT_SCENE),
        objects(),
        checkpoints(),
        animated_objects(),
        high_scores(),
        debris(),
        next_checkpoints(),
        ground_tiles(),
        x(0),
        y(0),
        w(0),
        h(0),
        roll(0),
        processing_time(0),
        time_of_last_checkpoint(100000),
        time_value_of_last_checkpoint(0)
    {
        processing_time = 0.0f;
        time_remaining = 60.0f;
        
        /*Checkpoints*/
        Reg_Checkpoint* check1 = new Reg_Checkpoint(3.0f, Point3f(5000.0f, 9000.0f, 700.0f));
        Reg_Checkpoint* check2 = new Reg_Checkpoint(3.0f, Point3f(8800.0f, 9400.0f, 2900.0f));
        Reg_Checkpoint* check3 = new Reg_Checkpoint(5.0f, Point3f(11928.0f, 10765.0f, 3000.0f));
        Challenge_Checkpoint* check3_c = new Challenge_Checkpoint(10.0f, Point3f(10700.0f, 7660.0f, 4000.0f));
        Reg_Checkpoint* check4 = new Reg_Checkpoint(2.0f, Point3f(14400, 16000, 615));
        Challenge_Checkpoint* check4_c = new Challenge_Checkpoint(10.0f, Point3f(10701, 4880.62, 1060.12));
        Reg_Checkpoint* check5 = new Reg_Checkpoint(4.0f, Point3f(14600, 19800, 400));
        Challenge_Checkpoint* check5_c = new Challenge_Checkpoint(10.0f, Point3f(13710.3, 16028.6, 170.135));
        Reg_Checkpoint* check6 = new Reg_Checkpoint(5.0f, Point3f(7850, 20560, 350));
        Challenge_Checkpoint* check6_c = new Challenge_Checkpoint(10.0f, Point3f(8198.48, 19540.9, 338.112));
        Reg_Checkpoint* check7 = new Reg_Checkpoint(3.0f, Point3f(5400, 11700, 730));
        Challenge_Checkpoint* check7_c = new Challenge_Checkpoint(10.0f, Point3f(4500, 11710, 310));
        Reg_Checkpoint* check8 = new Reg_Checkpoint(3.0f, Point3f(7080, 7500, 2550));
        Reg_Checkpoint* check9 = new Reg_Checkpoint(3.0f, Point3f(8350, 5760, 7520));
        //Reg_Checkpoint* check10 = new Reg_Checkpoint(1.0f, Point3f(12260, 11075, 2880));
        Reg_Checkpoint* check11 = new Reg_Checkpoint(2.0f, Point3f(10800, 5683, 7766));
        Reg_Checkpoint* check12 = new Reg_Checkpoint(2.0f, Point3f(15360, 7284, 7011));
        Challenge_Checkpoint* check12_c = new Challenge_Checkpoint(12.0f, Point3f(16114.1, 7418.5, 5442.87));
        Reg_Checkpoint* check13 = new Reg_Checkpoint(2.0f, Point3f(18100, 7537, 6760));
        Challenge_Checkpoint* check13_c = new Challenge_Checkpoint(13.0f, Point3f(18874.9, 6711.48, 3431.7));
        Reg_Checkpoint* check14 = new Reg_Checkpoint(2.0f, Point3f(19343, 5789.07, 6708.82));
        Challenge_Checkpoint* check14_c = new Challenge_Checkpoint(14.0f, Point3f(21696.6, 5207.04, 484.542));
        Reg_Checkpoint* check15 = new Reg_Checkpoint(2.0f, Point3f(21131.2, 4837.54, 6672.9));
        Reg_Checkpoint* check16 = new Reg_Checkpoint(2.0f, Point3f(23245.3, 6989.2, 6714.61));
        Reg_Checkpoint* check17 = new Reg_Checkpoint(3.0f, Point3f(24098.2, 11099.2, 1208.9));
        Challenge_Checkpoint* check17_c = new Challenge_Checkpoint(14.0f, Point3f(23661.4, 11510.9, 5421.14));
        Reg_Checkpoint* check18 = new Reg_Checkpoint(4.0f, Point3f(21532.8, 15227, 310.453));
        Reg_Checkpoint* check19 = new Reg_Checkpoint(4.0f, Point3f(14425.4, 12395.5, 255.657));
        Reg_Checkpoint* check20 = new Reg_Checkpoint(4.0f, Point3f(8478.66, 12209, 550.4));
        Challenge_Checkpoint* check20_c = new Challenge_Checkpoint(8.0f, Point3f(8750.49, 12202.2, 154.98));




        
        check1->add_next_checkpoint(check2);
        
        check2->add_next_checkpoint(check3);
        check2->add_next_checkpoint(check3_c);
        
        check3_c->add_next_checkpoint(check4_c);
        check3->add_next_checkpoint(check4);
        check3->add_next_checkpoint(check4_c);
        
        check4->add_next_checkpoint(check5);
        check4->add_next_checkpoint(check5_c);
        check4_c->add_next_checkpoint(check4);
        check4_c->add_next_checkpoint(check5_c);
        
        check5->add_next_checkpoint(check6);
        check5->add_next_checkpoint(check6_c);
        check5_c->add_next_checkpoint(check5);
        
        check6->add_next_checkpoint(check7);
        check6->add_next_checkpoint(check7_c);
        check6_c->add_next_checkpoint(check7_c);
        check6_c->add_next_checkpoint(check7);
        
        check7->add_next_checkpoint(check8);
        check7_c->add_next_checkpoint(check8);
        
        check8->add_next_checkpoint(check9);
        
        check9->add_next_checkpoint(check11);
        //check10->add_next_checkpoint(check11);
        check11->add_next_checkpoint(check12);
        check11->add_next_checkpoint(check12_c);
        
        check12->add_next_checkpoint(check13);
        check12->add_next_checkpoint(check13_c);
        check12_c->add_next_checkpoint(check13);
        check12_c->add_next_checkpoint(check13_c);
        
        check13->add_next_checkpoint(check14);
        check13->add_next_checkpoint(check14_c);
        check13_c->add_next_checkpoint(check14);
        check13_c->add_next_checkpoint(check14_c);
        
        check14->add_next_checkpoint(check15);
        check14_c->add_next_checkpoint(check18);
        check14_c->add_next_checkpoint(check17_c);
        
        check15->add_next_checkpoint(check16);
        
        check16->add_next_checkpoint(check17);
        check16->add_next_checkpoint(check17_c);
        
        check17->add_next_checkpoint(check18);
        check17_c->add_next_checkpoint(check18);
        
        check18->add_next_checkpoint(check19);
        
        check19->add_next_checkpoint(check20);
        check19->add_next_checkpoint(check20_c);
        
        check20_c->set_as_victory_checkpoint();
        check20->set_as_victory_checkpoint();

        checkpoints.push_back(check1);
        checkpoints.push_back(check2);
        checkpoints.push_back(check3);
        checkpoints.push_back(check3_c);
        checkpoints.push_back(check4);
        checkpoints.push_back(check4_c);
        checkpoints.push_back(check5);
        checkpoints.push_back(check5_c);
        checkpoints.push_back(check6);
        checkpoints.push_back(check6_c);
        checkpoints.push_back(check7);
        checkpoints.push_back(check7_c);
        checkpoints.push_back(check8);
        checkpoints.push_back(check9);
        //checkpoints.push_back(check10);
        checkpoints.push_back(check11);
        checkpoints.push_back(check12);
        checkpoints.push_back(check12_c);
        checkpoints.push_back(check13);
        checkpoints.push_back(check13_c);
        checkpoints.push_back(check14);
        checkpoints.push_back(check14_c);
        checkpoints.push_back(check15);
        checkpoints.push_back(check16);
        checkpoints.push_back(check17);
        checkpoints.push_back(check17_c);
        checkpoints.push_back(check18);
        checkpoints.push_back(check19);
        checkpoints.push_back(check20);
        checkpoints.push_back(check20_c);


        //Set the initial checkpoint
        check1->set_is_active(true);
        next_checkpoints.push_back(check1);
        /* Done with checkpoints */
        
        /*Ground*/
        for (int i = -15; i < 15; i++) {
            for (int j = -15; j < 15; j++) {
                
                Grass* c = new Grass(Point3f(i * 8000, j * 8000, 0), Vector3f(100, 100, 1));
                ground_tiles.push_back(c);
            }
        }
        
        for (int i = 0; i < 35; i++) {
            for (int j = 0; j < 35; j++) {
                bool w, h;
                w = j % 5 == 0 && j > 0;
                h = (i + 1) % 10 == 0 && i > 0;
                if (w) {
                    Road_Straight* c = new Road_Straight(Point3f(i * 800, j * 800, 3), Vector3f(10, 10, 1));
                    ground_tiles.push_back(c);
                }
                
                if (h) {
                    Road_Straight* c = new Road_Straight(Point3f(i * 800, j * 800, 3), Vector3f(10, 10, 1), Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), Global::pi / 2));
                    ground_tiles.push_back(c);
                }
                
                if (h && w) {
                    Road_Intersection* c = new Road_Intersection(Point3f((i - 1) * 800, j * 800, 4), Vector3f(10, 10, 1));
                    ground_tiles.push_back(c);
                }
            }
        }

        //Grass* c  = new Grass(Point3f(0, 0, -1), Vector3f(800 * 30, 800 * 30, 1));
        /* Done with ground */
        
        /*Buildings*/
        objects.push_back(new Crate(Point3f(0,0,0), Vector3f(30 * 800, 30 * 800, 1)));
        objects.push_back(new Residence(Point3f(4500, 9000, 0)));
        objects.push_back(new Residence(Point3f(3000, 9000, 0)));
        objects.push_back(new Residence(Point3f(1500, 9000, 0)));
        objects.push_back(new Residence(Point3f(0, 9000, 0)));
        objects.push_back(new Residence(Point3f(6000, 11700, 0), Vector3f(15.0f, 15.0f, 15.0f), Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), Global::pi)));
        objects.push_back(new Residence(Point3f(4500, 11700, 0), Vector3f(15.0f, 15.0f, 15.0f),  Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), Global::pi)));
        objects.push_back(new Residence(Point3f(3000, 11700, 0), Vector3f(15.0f, 15.0f, 15.0f),  Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), Global::pi)));
        objects.push_back(new Residence(Point3f(1500, 11700, 0), Vector3f(15.0f, 15.0f, 15.0f),  Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), Global::pi)));
        objects.push_back(new Residence(Point3f(6000, 9600, 0), Vector3f(15.0f, 15.0f, 15.0f),  Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), Global::pi / 2)));
        objects.push_back(new Residence(Point3f(12500, 21000, 0)));
        objects.push_back(new Residence(Point3f(11000, 21000, 0)));
        objects.push_back(new Residence(Point3f(9500, 21000, 0)));
        objects.push_back(new Residence(Point3f(8000, 21000, 0)));
        objects.push_back( new Residence(Point3f(20500, 21000, 0)));
        objects.push_back(new Residence(Point3f(19000, 21000, 0)));
        objects.push_back(new Residence(Point3f(17500, 21000, 0)));
        objects.push_back(new Residence(Point3f(16000, 21000, 0)));
        objects.push_back(new Residence(Point3f(16000, 9000, 0)));
        objects.push_back(new Residence(Point3f(19000, 9000, 0)));
        objects.push_back(new Residence(Point3f(14000, 12000, 0), Vector3f(15.0f, 15.0f, 15.0f), Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), Global::pi)));
        objects.push_back(new Residence(Point3f(20000, 11400, 0)));
        objects.push_back(new Residence(Point3f(18000, 11400, 0)));
        objects.push_back(new Residence(Point3f(13000, 15000, 0)));
        objects.push_back(new Residence(Point3f(11261.4, 15058.1, 0)));
        objects.push_back(new Residence(Point3f(7631.52, 15176.8, 0)));
        objects.push_back(new Residence(Point3f(17439.7, 14071, 0)));
        objects.push_back(new Residence(Point3f(23307.9, 13842.3, 0)));
        objects.push_back(new Residence(Point3f(7235.03, 13000, 0)));
        objects.push_back(new Building_2_piece("models/building2l1.3DS", Point3f(8000.71, 10600.1, 0)));

        
        Platform_Building* platform_1 = new Platform_Building(Point3f(8000, 4900, 0));
        Platform_Building* platform_2 = new Platform_Building(Point3f(7500, 17000, 0));
        Platform_Building* platform_3 = new Platform_Building(Point3f(11000, 17000, 0));
        Platform_Building* platform_4 = new Platform_Building(Point3f(16000, 17000, 0));
        Platform_Building* platform_5 = new Platform_Building(Point3f(19500, 17000, 0));
        Platform_Building* platform_6 = new Platform_Building(Point3f(24000, 17000, 0));
        Platform_Building* platform_7 = new Platform_Building(Point3f(27500, 17000, 0));
        
        Platform_Building* platform_8 = new Platform_Building(Point3f(11000, 4900, 0));
        Platform_Building* platform_9 = new Platform_Building(Point3f(16000, 4900, 0));
        Platform_Building* platform_10 = new Platform_Building(Point3f(19500, 4900, 0));
        Platform_Building* platform_11 = new Platform_Building(Point3f(24000, 4900, 0));
        Platform_Building* platform_12 = new Platform_Building(Point3f(27500, 4900, 0));

        Building_2* building2_1 = new Building_2(Point3f(10, 4000, 0));
        Building_2* building2_2 = new Building_2(Point3f(8500, 9000, 0));
        Building_2* building2_3 = new Building_2(Point3f(15400.4, 13200.9, 0));
    
        Bridge* bridge1 = new Bridge(Point3f(8500, 11480, 0));

        Turbine* turbine = new Turbine(Point3f(300,5300,0));
        Turbine* turbine2 = new Turbine(Point3f(22000,15000,0));
        Turbine* turbine3 = new Turbine(Point3f(20000,15000,0));
        Turbine* turbine4 = new Turbine(Point3f(1500,13000,0));
        Turbine* turbine5 = new Turbine(Point3f(4000,14000,0));
        Turbine* turbine6 = new Turbine(Point3f(23225.4, 11376.5, 0));
        Turbine* turbine7 = new Turbine(Point3f(25412, 11542.6, 0));



        animated_objects.push_back(turbine);
        animated_objects.push_back(turbine2);
        animated_objects.push_back(turbine3);
        animated_objects.push_back(turbine4);
        animated_objects.push_back(turbine5);
        animated_objects.push_back(turbine6);
        animated_objects.push_back(turbine7);

        platform_1->add_bodies_to_list(objects);
        platform_2->add_bodies_to_list(objects);
        platform_3->add_bodies_to_list(objects);
        platform_4->add_bodies_to_list(objects);
        platform_5->add_bodies_to_list(objects);
        platform_6->add_bodies_to_list(objects);
        platform_7->add_bodies_to_list(objects);
        platform_8->add_bodies_to_list(objects);
        platform_9->add_bodies_to_list(objects);
        platform_10->add_bodies_to_list(objects);
        platform_11->add_bodies_to_list(objects);
        platform_12->add_bodies_to_list(objects);

        building2_1->add_bodies_to_list(objects);
        building2_2->add_bodies_to_list(objects);
        building2_3->add_bodies_to_list(objects);
        
        bridge1->add_bodies_to_list(objects);

        turbine->add_bodies_to_list(objects);
        turbine2->add_bodies_to_list(objects);
        turbine3->add_bodies_to_list(objects);
        turbine4->add_bodies_to_list(objects);
        turbine5->add_bodies_to_list(objects);
        turbine6->add_bodies_to_list(objects);
        turbine7->add_bodies_to_list(objects);

        set_pausable(true);
        
        set_actions();

        m_camera.track(&m_player);
        
    }

    void Play_State::on_push() {
        get_Window().set_mouse_state(Window::MOUSE_HIDDEN);
    }

    void Play_State::on_pop() {
        std::list<Game_Object*>::iterator it;
         for(it = debris.begin(); it != debris.end(); it++){
             delete (*it);
         }
        
        for(it = objects.begin(); it != objects.end(); it++){
            delete (*it);
        }
        
        for(it = ground_tiles.begin(); it != ground_tiles.end(); it++){
            delete (*it);
        }
        
        std::list<Checkpoint*>::iterator check_it;
        for(check_it = checkpoints.begin(); check_it != checkpoints.end(); check_it++){
            delete (*check_it);
        }
        
        get_Controllers().reset_vibration_all();
        
    }

    void Play_State::on_cover() {
        get_Controllers().reset_vibration_all();
        processing_time = 0;
    }

    void Play_State::render() {
        Video &vr = get_Video();
        vr.set_3d(m_camera.get_camera());
        
//        
//        vr.set_Fog(Fog(Color(.2,.2,.2,.2),1.0f, FOG_LINEAR, 17000.0f, 19000.0f));
        vr.set_zwrite(false);
        m_skybox.boxRender(m_camera.get_camera().position);
        vr.set_zwrite(true);
        
        std::list<Game_Object*>::iterator it;
        for(it = ground_tiles.begin(); it != ground_tiles.end(); it++){
            (*it)->render();
        }

        for(it = objects.begin(); it != objects.end(); it++){
            Vector3f distance = Vector3f(m_camera.get_camera().position.x - (*it)->get_position().x,
                                         m_camera.get_camera().position.y - (*it)->get_position().y,
                                         m_camera.get_camera().position.z - (*it)->get_position().z);
            if (distance.magnitude() < 20000) {
                (*it)->render();
            }
        }
        
        
        get_Video().set_lighting(true);
        get_Video().set_ambient_lighting(Color(1.0f, 0.0f, 0.0f, 0.0f));
        get_Video().set_Light(0, Zeni::Light::Light(Color(.2, .7, .7, .7), Color(.5, .5, .5, .5), Color(.01, .5, .5, .5), Point3f(9000,12000,30000)));
        
        std::list<Checkpoint*>::iterator check_it;
        for(check_it = checkpoints.begin(); check_it != checkpoints.end(); check_it++){
            if ((*check_it)->get_is_active() || m_game_state == CUT_SCENE) {
                (*check_it)->render();
            }
        }
        
        if (m_game_state == CRASH) {
            m_player.Game_Object::set_velocity(Vector3f(0,0,0));
            std::list<Game_Object*>::iterator it;
            for(it = debris.begin(); it != debris.end(); it++){
                (*it)->render();
            }
        } else {
            m_player.render();
        }
        
        vr.set_lighting(false);
        
        vr.set_2d();
        
        render_hud();
    }

    void Play_State::render_hud() {
        
        
        
        if (time_of_last_checkpoint - time_remaining < 0 && m_game_state == PLAY) {
            get_Fonts()["hud"].render_text("Checkpoint! +" + itoa(time_value_of_last_checkpoint) + " seconds!", Point2f(0, get_Window().get_height() - 200), Color());
        }
        
        switch (m_game_state) {
                
            case PLAY: {
                ostringstream stream;
                stream.precision(2);
                stream << "time left: ";
                stream << time_remaining;
                Zeni::String hud(stream.str());
                get_Fonts()["hud"].render_text(hud, Point2f(), Color());
                break;
            }
                
            case WIN: {
                Font &score = get_Fonts()["score"];
                get_Fonts()["score"].render_text("Best Times:", Point2f(get_Window().get_width() - 200, 10), Color());
                
                for (int i = 0; i < high_scores.size() && i < 5; i++) {
                    get_Fonts()["score"].render_text(itoa(i+1) + ". " + ftoa(high_scores[i]), Point2f(get_Window().get_width() - 200, 10 + (i+1) * score.get_text_height() * 1.2), Color());
                    
                }
                
                
                Font &f = get_Fonts()["hud"];
                get_Fonts()["hud"].render_text("Course complete!", Point2f(30, get_Window().get_height() -  f.get_text_height() * 2.2), Color());
                get_Fonts()["hud"].render_text("Press B to play again", Point2f(30, get_Window().get_height() - f.get_text_height()), Color());
                break;
            }
                
            case LOSE: {
                Font &f = get_Fonts()["hud"];
                get_Fonts()["hud"].render_text("You ran out of time!", Point2f(30, get_Window().get_height() -  f.get_text_height() * 2.2), Color());
                get_Fonts()["hud"].render_text("Press B to play again", Point2f(30, get_Window().get_height() - f.get_text_height()), Color());
                break;
            }
                
            case CRASH: {
                Font &f = get_Fonts()["hud"];
                get_Fonts()["hud"].render_text("You crashed!", Point2f(30, get_Window().get_height() -  f.get_text_height() * 2.2), Color());
                get_Fonts()["hud"].render_text("Press B to play again", Point2f(30, get_Window().get_height() - f.get_text_height()), Color());
                break;
            }
                
            case CUT_SCENE: {
                Zeni::String text, skip_text;
                skip_text = "Press B to skip";
                if (time_remaining > 53) {
                    text = "Hello Ace! Today you'll be flying\n the course around Wind City.";
                } else if (time_remaining > 45) {
                    text = "You'll need to fly through a series of checkpoints,\n each one adding a few seconds to your remaining time.";
                } else if (time_remaining > 38) {
                    text = "Each time you pass through a checkpoint, the next will appear.\n Use LB to look in its direction if you don't see it.";
                } else if (time_remaining > 33) {
                    text =  "Red checkpoints are challenge checkpoints and award\n more time, but are harder to find and much harder to reach.";
                } else if (time_remaining > 30) {
                    text = "If you run out of time, you fail the assessment!\n Good luck, and watch out for Skyrates!";
                }
                get_Fonts()["cutscene"].render_text(text, Point2f(30, get_Window().get_height() / 2 + 100), Color());
                get_Fonts()["cutscene"].render_text(skip_text, Point2f(get_Window().get_width() - 200, 10), Color());

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
                if (time_remaining > 53) {
                    //Hello Ace! Today you'll be flying the course around city.
                    m_camera = My_Camera(Camera(Point3f(1000, 500, 5000), Quaternion(), 1.0f, 90000.0f), Vector3f(0.0f, 0.0f, -39.0f), 11.0f);
                    m_camera.track(&m_player);
                } else if (time_remaining > 45) {
                    //You'll fly through a series of checkpoints, each one adding a few seconds to your remaining time.
                    m_camera = My_Camera(Camera(Point3f(4500.0f, 15000.0f, 900.0f), Quaternion(), 1.0f, 90000.0f), Vector3f(0.0f, 0.0f, -39.0f), 11.0f);
                    m_camera.track(&m_player);
                } else if (time_remaining > 38) {
                    //Each time you pass through a checkpoint, the next will appear. Use LB to look in its direction if you don't see it.
                    m_camera = My_Camera(Camera(Point3f(8600, 11980, 400), Quaternion(), 1.0f, 90000.0f), Vector3f(0.0f, 0.0f, -39.0f), 11.0f);
                    m_camera.track(&m_player);
                } else if (time_remaining > 33) {
                    // Red checkpoints are challenge checkpoints and award more time, but are harder to find and much harder to reach.
                    m_camera.get_camera() = Camera(Point3f(13710.3, 16238.6, 170.135), Quaternion(), 1.0f, 90000.0f);
                    m_camera.track(&m_player);
                } else if (time_remaining > 30) {
                    //If you run out of time, you fail the assessment! Good luck!
                    m_camera = My_Camera(Camera(Point3f(1200.0f, 7800.0f, 50.0f), Quaternion(), 1.0f, 90000.0f), Vector3f(0.0f, 0.0f, -39.0f), 11.0f);
                    m_player = Player(Point3f(0.0f, 8000.0f, 150.0f),
                                      Vector3f(1.0f, 1.0f, 1.0f));
                    m_camera.track(&m_player);
                }
                
                
                update_time(processing_time);
                physics_loop(processing_time);
                break;
            }
                
            case PLAY: {
                update_time(processing_time);
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
        /** Keep delays under control (if the program hangs for some time, we don't want to lose responsiveness) **/
        if(processing_time > 0.1f) {
            processing_time = 0.1f;
        }
        
        /** Physics processing loop**/
        for(float time_step = 0.0005f; processing_time > 0.0f;) {
            
            Vector3f velocity = get_player_velocity(time_step * 90);
            
            if (m_game_state == CRASH) {
                velocity = gravity;
            }
            
            m_player.set_velocity(velocity);
            
            if(time_step > processing_time) {
                time_step = processing_time;
            }
            
            if (m_game_state == PLAY) {
                rotate_player(time_step * 70);
            }
            
            /** Move each object which needs to **/
            std::list<Game_Object*>::iterator it;
            for(it = debris.begin(); it != debris.end(); it++){
                (*it)->set_velocity((*it)->get_velocity() + gravity);
                (*it)->step(time_step);
            }
            
            std::list<Game_Object*>::iterator anIt;
            for(anIt=animated_objects.begin(); anIt != animated_objects.end(); anIt++){
                (*anIt)->step(time_step);
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

    void Play_State::rotate_player(float time_step) {
        /** Rotate the aircraft **/
        float pull_up_modifier;
        if (m_player.get_up_vec().get_jk().k > 0 && m_player.get_forward_vec().get_jk().k < -0.6) {
            pull_up_modifier = 1.4 + m_player.get_forward_vec().get_jk().k;
        } else {
            pull_up_modifier = 1.0;
        }
        m_player.rotate(Quaternion((-w * time_step / (look_sensitivity * yaw_modifier)),
                                   (h * time_step / (look_sensitivity) * pull_up_modifier),
                                   (roll * time_step / roll_sensitivity)));
        m_player.adjust_vectors();
    }

    Vector3f Play_State::get_player_velocity(float time_step) {
        //Get jet thrust
        if (m_game_state == PLAY) {
            /** Calculate current thrust**/
            float desired_thrust = max((base_thrust + thrust_range * y), 1100.0f);
            
            if (thrust_amount > desired_thrust) {
                thrust_amount -= thrust_delta * time_step;
            }
            
            if (thrust_amount < desired_thrust) {
                thrust_amount += thrust_delta * time_step;
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
            if (m_player.is_crossing_checkpoint((*check_it)) && (*check_it)->get_is_active()) {
                time_value_of_last_checkpoint = (*check_it)->get_time_value();
                time_of_last_checkpoint = time_remaining;
                time_remaining += (*check_it)->get_time_value();
                (*check_it)->set_is_active(false);
                (*check_it)->activate_next_checkpoints();
                std::list<Checkpoint*>::iterator next_check_it;
                for (next_check_it = next_checkpoints.begin(); next_check_it != next_checkpoints.end(); next_check_it++) {
                    (*next_check_it)->set_is_active(false);
                }
                next_checkpoints = (*check_it)->get_next_checkpoints();
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
            
            Debris* c = new Debris(m_player.get_position(), Vector3f(1, 1, 1));
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
                    w = confidence * 600;
                } else {
                    w = 0.0f;
                }
                break;
                
            case 3: //Left Toggle Y

                break;
                
            case 4: //Right Toggle X - Steering
                
                if (abs(confidence) > 0.25f) {
                    roll = (confidence * 400);
                } else {
                    roll = 0;
                }
                break;
                
            case 5: //Right toggle Y
                if (abs(confidence) > 0.25f) {
                    h = -confidence * (600);
                } else {
                   h = 0.0f;
                }
                break;
                
            case 10: //D down
                m_camera.set_horizon_lock();
                break;
                
            case 6://D up
                m_camera.set_rolling();
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
                
            case 8: { //Left shoulder - Zoom closer to plane
//                m_camera.decrease_follow_distance();
                if (confidence) {
                    m_camera.set_focus_object(next_checkpoints.front());
                } else {
                    m_camera.unset_focus_object();
                }
                break;
            }
                
            case 9: { //Right shoulder - Zoom farther from plane
                //m_camera.increase_follow_distance();
                cout << m_player.get_position().x << ", " << m_player.get_position().y << ", " << m_player.get_position().z << endl;
                break;
            }
                
            case 13: {//B button
                if (m_game_state != CUT_SCENE && m_game_state != PLAY) {
                    get_Game().pop_state();
                    Play_State* newplay = new Play_State();
                    get_Game().push_state(newplay);
                } else if (m_game_state == CUT_SCENE) {
                    time_remaining = 30.1;
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
    }
}

bool Play_State::score_comp(const float score1, const float score2) {
    return score1 > score2;
}