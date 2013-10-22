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
    }
    
private:
    void on_key(const SDL_KeyboardEvent &event) {
        if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
            get_Game().pop_state();
    }
    
    void render() {
        Widget_Gamestate::render();
        
        Zeni::Font &fr = get_Fonts()["title"];
        
        fr.render_text(
#if defined(_WINDOWS)
                       "ALT+F4"
#elif defined(_MACOSX)
                       "Apple+Q"
#else
                       "Ctrl+Q"
#endif
                       " to Quit",
                       Point2f(400.0f, 300.0f - 0.5f * fr.get_text_height()),
                       get_Colors()["title_text"],
                       ZENI_CENTER);
    }
};

#endif /* defined(__game__Instruction_State__) */
