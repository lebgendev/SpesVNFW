#include <SDL3/SDL.h>
#include <SDL3_Image/SDL_image.h>
#include <iostream>


//define buttons from SDL

#define KEY_A SDLK_a
#define KEY_B SDLK_b
#define KEY_C SDLK_c
#define KEY_D SDLK_d
#define KEY_E SDLK_e
#define KEY_F SDLK_f
#define KEY_G SDLK_g
#define KEY_H SDLK_h
#define KEY_I SDLK_i
#define KEY_J SDLK_j
#define KEY_K SDLK_k
#define KEY_L SDLK_l
#define KEY_M SDLK_m
#define KEY_N SDLK_n
#define KEY_O SDLK_o
#define KEY_P SDLK_p
#define KEY_Q SDLK_q
#define KEY_R SDLK_r
#define KEY_S SDLK_s
#define KEY_T SDLK_t
#define KEY_U SDLK_u
#define KEY_V SDLK_v
#define KEY_W SDLK_w
#define KEY_X SDLK_x
#define KEY_Y SDLK_y
#define KEY_Z SDLK_z

// Numbers (top row)
#define KEY_0 SDLK_0
#define KEY_1 SDLK_1
#define KEY_2 SDLK_2
#define KEY_3 SDLK_3
#define KEY_4 SDLK_4
#define KEY_5 SDLK_5
#define KEY_6 SDLK_6
#define KEY_7 SDLK_7
#define KEY_8 SDLK_8
#define KEY_9 SDLK_9

// Control keys
#define KEY_ENTER      SDLK_RETURN
#define KEY_ESCAPE     SDLK_ESCAPE
#define KEY_BACKSPACE  SDLK_BACKSPACE
#define KEY_TAB        SDLK_TAB
#define KEY_SPACE      SDLK_SPACE

// Modifiers
#define KEY_LSHIFT SDLK_LSHIFT
#define KEY_RSHIFT SDLK_RSHIFT
#define KEY_LCTRL  SDLK_LCTRL
#define KEY_RCTRL  SDLK_RCTRL
#define KEY_LALT   SDLK_LALT
#define KEY_RALT   SDLK_RALT

// Arrow keys
#define KEY_UP    SDLK_UP
#define KEY_DOWN  SDLK_DOWN
#define KEY_LEFT  SDLK_LEFT
#define KEY_RIGHT SDLK_RIGHT

// Function keys
#define KEY_F1  SDLK_F1
#define KEY_F2  SDLK_F2
#define KEY_F3  SDLK_F3
#define KEY_F4  SDLK_F4
#define KEY_F5  SDLK_F5
#define KEY_F6  SDLK_F6
#define KEY_F7  SDLK_F7
#define KEY_F8  SDLK_F8
#define KEY_F9  SDLK_F9
#define KEY_F10 SDLK_F10
#define KEY_F11 SDLK_F11
#define KEY_F12 SDLK_F12

// Symbols
#define KEY_MINUS        SDLK_MINUS        // -
#define KEY_EQUALS       SDLK_EQUALS       // =
#define KEY_LEFTBRACKET  SDLK_LEFTBRACKET  // [
#define KEY_RIGHTBRACKET SDLK_RIGHTBRACKET // ]
#define KEY_BACKSLASH    SDLK_BACKSLASH    // 
#define KEY_SEMICOLON    SDLK_SEMICOLON    // ;
#define KEY_APOSTROPHE   SDLK_APOSTROPHE   // '
#define KEY_COMMA        SDLK_COMMA        // ,
#define KEY_PERIOD       SDLK_PERIOD       // .
#define KEY_SLASH        SDLK_SLASH        // /

// Lock keys
#define KEY_CAPSLOCK SDLK_CAPSLOCK

//sdl event key down
#define EVENT_KEY_DOWN SDL_EVENT_KEY_DOWN
#define EVENT_QUIT SDL_EVENT_QUIT


typedef SDL_Event eventHandler;
bool addEventListener(eventHandler& e){
    return SDL_PollEvent(&e);
}


void start();
void update();







class Image{
    public:
        std::string url;
        SDL_Texture* texture = nullptr;
        float width;
        float height;
        float x = 0;
        float y = 0;
        Image(SDL_Renderer* renderer, std::string &url, float w, float h){
            this->url = url;
            this->texture = IMG_LoadTexture(renderer, url.c_str());
            setDims(w, h);
            std::cout << this->width << this->height;
        }
        ~Image(){
            if (texture) {
                SDL_DestroyTexture(texture);
            }
        }
        void setCords(float x, float y){
            this->x = x;
            this->y = y;
        }
        void setDims(float w, float h){
            this->width = w;
            this->height = h;
        }

};



class Screen{
    private:
        int width = 300;
        int height = 300;
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
    public:
        bool quit = false;
        Screen(int width, int height){
            this->width = width;
            this->height = height;
        }

        int getWidth(){
            return width;
        }

        int getHeight(){
            return height;
        }


        SDL_Window* getWindow(){
            return this->window;
        }

        SDL_Renderer* getRenderer(){
            return this->renderer;
        }

        void initialize(){
            if(!SDL_Init(SDL_INIT_VIDEO)){
                printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            } else {
                window = SDL_CreateWindow( "SDL Tutorial", width, height, 0 );
                if( window == NULL )
                {
                    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
                } else {
                    
                    renderer = SDL_CreateRenderer(window, NULL);
                    start();
                    while (!quit) {
                        update();
                    }
                }

            }
        }

        void updateRenderer(){
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }

        void setColor(int r, int g, int b, int a){
            SDL_SetRenderDrawColor(renderer, r, g, b, a);
            updateRenderer();
        }

        Image *imageLoader(std::string url, float w, float h){
            return new Image(this->renderer, url, w, h);
        }

        void imageRenderer(Image *img, float x, float y){
            SDL_RenderClear(renderer);
            SDL_FRect cords;
            cords.x = x;
            cords.y = y;
            cords.w = img->width;
            cords.h = img->height;
            img->setCords(x, y);
            SDL_RenderTexture(renderer, img->texture, nullptr, &cords);
            SDL_RenderPresent(renderer);
        }


        // Experimental Rotate Transformation, TODO, edit later.
        // void imageRendererTransform(Image *img, float x, float y, float angle, float oX, float oY){
        //     SDL_RenderClear(renderer);
        //     SDL_FRect cords;
        //     cords.x = x;
        //     cords.y = y;
        //     cords.w = img->width;
        //     cords.h = img->height;
        //     SDL_FPoint origin = {oX, oY};


        //     img->setCords(x, y);
        //     SDL_RenderTextureRotated(renderer, img->texture, nullptr, &cords, angle, &origin, SDL_FLIP_NONE);
        //     SDL_RenderPresent(renderer);
        // }
};



//using the code itself.


Screen screen(600, 400);
Image *background; 



int main(){
    screen.initialize();
    return 0;
}

void start(){
    screen.setColor(255, 255, 255, 255);
    background = screen.imageLoader("images/sdl.png", screen.getWidth()/2.0, screen.getHeight()/2.0);
    screen.imageRenderer(background, screen.getWidth()/2 - background->width/2.0, screen.getHeight()/2 - background->height/2.0);
    std::cout << "\n" << background->x ;
}

void update(){

    //the movement keys are merely for testing controls
    eventHandler eventHandler;
    while (addEventListener(eventHandler)){
        if(eventHandler.type == EVENT_KEY_DOWN){
            if(eventHandler.key.key == KEY_ENTER){
                screen.setColor(255, 0, 0, 255);
            }
            if(eventHandler.key.key == KEY_SPACE){
                screen.setColor(0, 0, 0, 255);
            }
            if(eventHandler.key.key == SDLK_D){
                background->x += 5.0;
                screen.imageRenderer(background, background->x, background->y);
            }
            if(eventHandler.key.key == SDLK_Q){
                background->x -= 5.0;
                screen.imageRenderer(background, background->x, background->y);
            }
            if(eventHandler.key.key == SDLK_Z){
                background->y -= 5.0;
                screen.imageRenderer(background, background->x, background->y);
            }
            if(eventHandler.key.key == SDLK_S){
                background->y += 5.0;
                screen.imageRenderer(background, background->x, background->y);
            }

        }
        if(eventHandler.type == EVENT_QUIT){
            screen.quit = true;
        }
    }
    
}
