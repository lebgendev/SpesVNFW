#include "SpesVNFW/SpesVNFW.h"
#include <iostream>
#include <windows.h>




std::string fntLink = "fonts/font.ttf";
Screen screen(1080, 720);
gameState game;
Image *background;
Image *character;
Image *textBox;
Text* author = new Text(fntLink.c_str(), 30);
Text* dialogue = new Text(fntLink.c_str(), 28);
int a = 0;


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
    author->setColor(255, 255, 255, 255);

    game.interpret();
}

void makeButtons(const std::vector<std::string>& t){
    float areaHeight = screen.getHeight() - textBox->height;
    int numOfObjects = t.size();
    float objH = screen.getHeight() * 0.1;
    float offsetZero = areaHeight / (numOfObjects + 1);

    for(int i = 0; i < numOfObjects; i++){
        float offset = offsetZero * (i + 1);
        Button* btn = new Button(fntLink.c_str(), 25, t[i]);

        btn->setColor(255, 255, 255, 255);
        btn->setBackgroundDims(screen.getWidth() * 0.4, objH);
        btn->autoScaleDims();
        btn->setCords(screen.getWidth()/2.0 - btn->textW/2.0, offset - btn->textH/2.0);

        game.buttons.push_back(btn);
        screen.buttonRenderer(btn);
    }

    SDL_RenderPresent(screen.getRenderer());
}

void transitionAnimation(std::vector<std::string> t) {
    float screenW = (float)screen.getWidth();
    float screenH = (float)screen.getHeight();
    screen.scrollScreenAnimation(0, 0, 0, 255, background, screenW, screenH, -screenW, 0, 25);
    background->setTexture("images/" + t[1]);
    screen.scrollScreenAnimation(0, 0, 0, 255, background, screenW, screenH, 0, -screenW, -25);
}

void changeBackground(std::string t){
    background->setTexture("images/" + t);
    std::cout <<"IFBQIUFQIUFZUQFI\n";
    displayDialogue();
}

void showCharacter(std::string t){
    character->setTexture("images/" + t);
    displayDialogue();
}

void displayDialogue(){
    SDL_RenderClear(screen.getRenderer());

    if(!background->texture){
        std::cout << "Background Texture Failed" << "\n";
        std::cout << game.lastDialogue[1] << "\n";
    }
    background->setDims(background->height * background->aspectRatio, background->height);
    screen.imageRenderer(
        background,
        255,
        COVER
    );


    //character
    character->setDims(screen.getHeight() * 0.7 * character->aspectRatio, screen.getHeight() * 0.7);

    if(!character->texture){
        std::cout << "Character Texture Failed" << "\n";
    }

    character->setCords(screen.getWidth()/2.0 - character->width/2.0, screen.getHeight() - character->height);
    screen.imageRenderer(character,
                        255,
                        SCALE
    );



    //text box
    textBox->setCords(screen.getWidth()/2 - textBox->width/2.0, screen.getHeight() * 0.85 - textBox->height/2.0);
    screen.imageRenderer(textBox,
                        125,
                        SCALE);


    //text
    if(game.lastDialogue.size() == 0){
        SDL_RenderPresent(screen.getRenderer());
        return;
    }
    int w, h;
    bool b = TTF_GetStringSize(author->font, game.lastDialogue[0].c_str(), 0, &w, &h);
    screen.textRenderer(author,
                        game.lastDialogue[0],
                        screen.getWidth()/2 - w/2.0,
                        screen.getHeight() * 0.775- h/2.0,
                        w,
                        h);
    b = TTF_GetStringSize(dialogue->font, game.lastDialogue[1].c_str(), 0, &w, &h);
    screen.textRenderer(dialogue,
                        game.lastDialogue[1],
                        screen.getWidth()/2 - w/2.0,
                        screen.getHeight() * 0.85 - h/2.0,
                        w,
                        h);
    
    SDL_RenderPresent(screen.getRenderer());
    return;
}

void update(){


    //the movement keys are merely for testing controls
    eventHandler eventHandler;
    while (addEventListener(eventHandler)){
        if(eventHandler.type == EVENT_KEY_DOWN){
            switch(eventHandler.key.key){
                case KEY_ENTER:
                    game.interpret();
                    break;
                case KEY_SPACE:
                    game.currentRow = 0;
                    game.interpret();
                    break;
            }

        }
        if(eventHandler.type == EVENT_QUIT){
            screen.quit = true;
        }
    }
    
    
}

