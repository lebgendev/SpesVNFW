#pragma once

#include <SDL3/SDL.h>
#include <SDL3_Image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>

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


enum imageSize {
  SCALE,
  COVER
};


typedef SDL_Event eventHandler;
typedef SDL_FRect Rect;
bool addEventListener(eventHandler& e);
 

void start();
void update();




class Text{
    public: 
        TTF_Font* font = nullptr;
        SDL_Color color = {0,0,0, 255};
        SDL_Surface* surface = nullptr;
        SDL_Texture* texture = nullptr;
        Text(const char* link, int size);
        virtual ~Text();
        void setColor(int r, int g, int b, int a);

};


class Image{
    public:
        std::string url;
        SDL_Texture* texture = nullptr;
        SDL_Renderer** renderer = nullptr;
        float aspectRatio = 1;
        float width;
        float height;
        float texWidth;
        float texHeight;
        float x = 0;
        float y = 0;
        Image(SDL_Renderer** renderer, const std::string &url, float w, float h);
        ~Image();
        void setCords(float x, float y);
        void setDims(float w, float h);
        void setTexture(std::string url);

};



class Button : public Text{
    public:
        std::string label;
        float x, y, bgW, bgH, textW, textH;
        Image *bg;
        Button(const char* link, int size,const std::string& label);
        ~Button();
        void setBackgroundDims(float w, float h);
        void setCords(float x, float y);
        void autoScaleDims();
        void setTextDims(float w, float h);
};


class Screen{
    private:
        int width = 300;
        int height = 300;
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
    public:
        bool quit = false;

        Screen(int width, int height);

        int getWidth();

        int getHeight();


        SDL_Window* getWindow();

        SDL_Renderer* getRenderer();

        void initialize();

        void updateRenderer();

        void setColor(int r, int g, int b, int a);

        void drawRectangle(int r, int g, int b, int a, float x, float y, float w, float h);

        Image *imageLoader(const std::string url, float w, float h);

        void imageRenderer(Image *img, int alpha, enum imageSize t);

        void imageRenderer(Image *img, Rect src, int alpha, enum imageSize t);

        void textRenderer(Text *txt, std::string text, float x, float y, float w, float h);

        void scrollScreenAnimation(int r, int g, int b, int a, Image* &background, float w, float h, float start, float finish, float rate);

        void buttonRenderer(Button *btn);

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


