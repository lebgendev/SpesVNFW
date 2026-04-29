#include "SpesVNFW/SpesVNFW.h"
#include <iostream>
#include <windows.h>




std::string fntLink = "fonts/font.ttf";
Screen screen(1280, 720);
gameState game;
Image *background;
Image *character;
Image *textBox;
Text* author = new Text(fntLink.c_str(), 30);
Text* dialogue = new Text(fntLink.c_str(), 28);


int main(){
    screen.initialize("Emilia Dating Sim");
    return 0;
}


void start(){
    screen.setWindowIcon("images/icon.jpg");
    screen.setColor(255, 255, 255, 255);
    background = screen.imageLoader("images/schoolHallwayBG.jpg", screen.getWidth(), screen.getHeight());
    character = screen.imageLoader("images/man.png", screen.getWidth() * 0.3, screen.getHeight() * 0.8);
    textBox = screen.imageLoader("images/textbox.jpg", screen.getWidth(), screen.getHeight() * 0.3);
    dialogue->setColor(255, 255, 255, 255);
    author->setColor(255, 255, 255, 255);

    game.interpret();
}

void makeButtons(const std::vector<std::string>& t){
    game.dialogueContinue = false;
    float areaHeight = screen.getHeight();
    int numOfObjects = t.size();
    float objH = screen.getHeight() * 0.1;
    float offsetZero = areaHeight / (numOfObjects + 1);
    SDL_RenderClear(screen.getRenderer());
    screen.imageRenderer(
        background,
        255,
        COVER
    );

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
    std::cout << "\n";

    SDL_RenderPresent(screen.getRenderer());
}

void playAudio(std::string t){
    MIX_Audio* h = screen.loadAudio("audio/" + t, false);
    screen.playAudio(h, 0);
    MIX_DestroyAudio(h);
}

void transitionAnimation(std::vector<std::string> t) {
    float screenW = (float)screen.getWidth();
    float screenH = (float)screen.getHeight();
    if(t[0] == "scroll"){
        screen.scrollScreenAnimation(0, 0, 0, 255, background, screenW, screenH, -screenW, 0, 25);
        background->setTexture("images/" + t[1]);
        screen.scrollScreenAnimation(0, 0, 0, 255, background, screenW, screenH, 0, -screenW, -25);
    } else if(t[0] == "fade"){
        screen.fadeScreenAnimation(0, 0, 0, background, screenW, screenH, 0, 255, 5);
        background->setTexture("images/" + t[1]);
        screen.fadeScreenAnimation(0, 0, 0, background, screenW, screenH, 255, 0, -5);
    }

}

void changeBackground(std::string t){
    background->setTexture("images/" + t);
    std::cout <<"IFBQIUFQIUFZUQFI\n";
    displayDialogue(false);
}

void showCharacter(std::string t){
    character->setTexture("images/" + t);
    displayDialogue(false);
}

void displayDialogue(bool overtimeType){

    game.dialogueContinue = false;
    if(!background->texture){
        std::cout << "Background Texture Failed" << "\n";
        std::cout << game.lastDialogue[1] << "\n";
    }
    //character
    character->setDims(screen.getHeight() * 0.7 * character->aspectRatio, screen.getHeight() * 0.7);

    if(!character->texture){
        std::cout << "Character Texture Failed" << "\n";
    }

    character->setCords(screen.getWidth()/2.0 - character->width/2.0, screen.getHeight() - character->height);

    //text box
    textBox->setCords(screen.getWidth()/2 - textBox->width/2.0, screen.getHeight() * 0.85 - textBox->height/2.0);


    //text
    if(game.lastDialogue.size() == 0){
        SDL_RenderPresent(screen.getRenderer());
        return;
    }
    std::string k;
    if(overtimeType){
        for(int i = 0; i < game.lastDialogue[1].length(); i++){
            SDL_RenderClear(screen.getRenderer());
            screen.imageRenderer(
                background,
                255,
                COVER
            );
            screen.imageRenderer(character,
                                255,
                                SCALE
            );
            screen.imageRenderer(textBox,
                                125,
                                SCALE);
            int w, h;
            bool b = TTF_GetStringSize(author->font, game.lastDialogue[0].c_str(), 0, &w, &h);
            screen.textRenderer(author,
                                game.lastDialogue[0],
                                screen.getWidth()/2 - w/2.0,
                                screen.getHeight() * 0.775- h/2.0,
                                w,
                                h);
            k += game.lastDialogue[1].at(i);
            b = TTF_GetStringSize(dialogue->font, k.c_str(), 0, &w, &h);
            screen.textRenderer(dialogue,
                                k,
                                screen.getWidth()/2 - w/2.0,
                                screen.getHeight() * 0.85 - h/2.0,
                                w,
                                h);
            
            SDL_RenderPresent(screen.getRenderer());
            SDL_Delay(30);
        }
    } else {
        SDL_RenderClear(screen.getRenderer());
            screen.imageRenderer(
                background,
                255,
                COVER
            );
            screen.imageRenderer(character,
                                255,
                                SCALE
            );
            screen.imageRenderer(textBox,
                                125,
                                SCALE);
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
    }
    
    game.dialogueContinue = true;
    
    return;
}



// Button* lastHover = nullptr;
void update(){


    //the movement keys are merely for testing controls
    eventHandler eventHandler;
    while (addEventListener(eventHandler)){
        SDL_MouseButtonEvent *mouse = &eventHandler.button;
        switch(eventHandler.type){
            case EVENT_KEY_DOWN:
                switch(eventHandler.key.key){
                    case KEY_ENTER:
                        if(game.dialogueContinue) game.interpret();
                        break;
                }
                break;

            case EVENT_QUIT:
                screen.quit = true;
                MIX_Quit();
                TTF_Quit();
                SDL_Quit();
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (mouse->button == SDL_BUTTON_LEFT){
                    std::string pressedLabel;
                    for(Button* b : game.buttons){
                        Rect rect = {b->x, b->y, b->bgW, b->bgH};
                        if(region_match(rect, eventHandler.button.x, eventHandler.button.y)){
                            pressedLabel = b->label;
                            playAudio("sfx/select.mp3");
                            break;
                        }
                    }
                    if(!pressedLabel.empty()){
                        game.dialogueContinue = true;
                        for(int i = 0; i < game.buttons.size(); i++){
                            delete game.buttons[i];
                        }
                        game.buttons.clear();
                        game.searchForChoice(pressedLabel);
                    }
                }
                break;
            // case SDL_EVENT_MOUSE_MOTION:
            //     if(!game.buttons.empty()){
            //         for(Button* b : game.buttons){
            //             Rect rect = {b->x, b->y, b->bgW, b->bgH};
            //             if(region_match(rect, eventHandler.motion.x, eventHandler.motion.y)){
            //                 if(b == lastHover){
            //                     break;
            //                 }
            //                 playAudio("sfx/select.mp3");
            //                 lastHover = b;
            //                 break;
            //             }
            //         }
            //     }
            //     break;
            
        }
        
    }
    
    
}

