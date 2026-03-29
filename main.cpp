#include "SpesVNFW/SpesVNFW.h"
#include <iostream>




std::string fntLink = "fonts/font.ttf";
Screen screen(1080, 720);
gameState game;
Image *background;
Image *character;
Image *textBox;
Text* author = new Text(fntLink.c_str(), 24);
Text* dialogue = new Text(fntLink.c_str(), 24);



int main(){
    screen.initialize();
    return 0;
}


void start(){
    screen.setColor(255, 255, 255, 255);
    background = screen.imageLoader("images/schoolHallwayBG.jpg", screen.getWidth(), screen.getHeight());
    character = screen.imageLoader("images/man.png", screen.getWidth() * 0.3, screen.getHeight() * 0.8);
    textBox = screen.imageLoader("images/textbox.jpg", screen.getWidth(), screen.getHeight() * 0.3);
    dialogue->setColor(255, 255, 255, 255);
    
    

    game.interpret(screen);
}

void displayDialogue(Screen &sc, std::vector<std::string> t){
    SDL_RenderClear(sc.getRenderer());

    //background
    screen.imageRenderer(background,
                        screen.getWidth()/2.0 - background->width/2.0,
                        screen.getHeight()/2.0 - background->height/2.0,
                        255,
                        COVER);
    if(t.size() == 4 && !t[3].empty()){
        background->setTexture(t[3]);
    } else {
        background->setTexture(background->url);
    }
    if(!background->texture){
        std::cout << "Background Texture Failed" << "\n";
    }
    background->setDims(background->height * background->aspectRatio, background->height);
    screen.imageRenderer(background,
                        screen.getWidth()/2.0 - background->width/2.0,
                        screen.getHeight()/2.0 - background->height/2.0,
                        255,
                        COVER);


    //character
    

    if(t.size() > 2 && !t[2].empty()){
        std::string l = t[2] + ".png";
        character->setTexture(l);
    } else {
        std::cout << "hiiii";
        character->setTexture(character->url);
    }
    character->setDims(screen.getHeight() * 0.7 * character->aspectRatio, screen.getHeight() * 0.7);

    if(!character->texture){
        std::cout << "Character Texture Failed" << "\n";
    }

    screen.imageRenderer(character,
                        screen.getWidth()/2.0 - character->width/2.0,
                        screen.getHeight() - character->height,
                        255,
                        SCALE
    );



    //text box
    textBox->setTexture("images/textbox.jpg");
    screen.imageRenderer(textBox,
                        screen.getWidth()/2 - textBox->width/2.0,
                        screen.getHeight() * 0.85 - textBox->height/2.0,
                        125,
                        SCALE);


    //text
    float w = textBox->width * 0.6;
    float h = textBox->height * 0.3;
    screen.textRenderer(dialogue,
                        t[1],
                        screen.getWidth()/2 - w/2.0,
                        screen.getHeight() * 0.85 - h/2.0,
                        w,
                        h);
    
    SDL_RenderPresent(sc.getRenderer());
    return;
}

void update(){

    //the movement keys are merely for testing controls
    eventHandler eventHandler;
    while (addEventListener(eventHandler)){
        if(eventHandler.type == EVENT_KEY_DOWN){
            switch(eventHandler.key.key){
                case KEY_ENTER:
                    game.interpret(screen);
                    break;
            }

        }
        if(eventHandler.type == EVENT_QUIT){
            screen.quit = true;
        }
    }
    
}

