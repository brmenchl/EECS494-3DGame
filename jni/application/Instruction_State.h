//
//  Instruction_State.h
//  game
//
//  Created by David Zilli on 10/21/13.
//
//

#ifndef __game__Instruction_State__
#define __game__Instruction_State__

#include <iostream>
#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Instructions_State : public Widget_Gamestate {
    Instructions_State(const Instructions_State &);
    Instructions_State operator=(const Instructions_State &);
    
public:
    Instructions_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
    {
        Vertex2f_Texture ul(Point2f(0,0), Point2f(0.0f, 0.0f));
        Vertex2f_Texture ll(Point2f(0,600), Point2f(0.0f, 1.0f));
        Vertex2f_Texture lr(Point2f(800,600), Point2f(1.0f, 1.0f));
        Vertex2f_Texture ur(Point2f(800,0), Point2f(1.0f, 0.0f));
        Material material("instructions");
        
        Quadrilateral<Vertex2f_Texture> quad(ul, ll, lr, ur);
        quad.lend_Material(&material);
        
    }
    
private:
    Quadrilateral<Vertex2f_Texture> quad;
    void on_key(const SDL_KeyboardEvent &event) {
        if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
            get_Game().pop_state();
    }
    
    void render() {
        Widget_Gamestate::render();
        get_Video().render(quad);
        Zeni::render_image (String("instructions"), Point2f(0,0), Point2f(800,600), false, Color());
    }
};

#endif /* defined(__game__Instruction_State__) */
