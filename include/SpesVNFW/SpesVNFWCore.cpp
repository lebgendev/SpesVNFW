#include "SpesVNFWCore.h"
#include <iostream>

typedef SDL_Event eventHandler;
bool addEventListener(eventHandler& e){
    return SDL_PollEvent(&e);
}







        Text::Text(const char* link, int size){
            this->font = TTF_OpenFont(link, size);
            if (!this->font) {
                std::cout << "TTF_OpenFont error: " << SDL_GetError() << std::endl;
            }
        }

        Text::~Text(){
            SDL_DestroySurface(surface);
            SDL_DestroyTexture(texture);
            TTF_CloseFont(font);
            surface = nullptr;
            texture = nullptr;
            font = nullptr;
        }

        void Text::setColor(int r, int g, int b, int a){
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }


        Image::Image(SDL_Renderer** renderer, const std::string &url, float w, float h){
            this->renderer = renderer;
            setTexture(url);
            setDims(w, h);
        }
        Image::~Image(){
            if (texture) {
                SDL_DestroyTexture(texture);
            }
        }
        void Image::setCords(float x, float y){
            this->x = x;
            this->y = y;
        }
        void Image::setDims(float w, float h){
            this->width = w;
            this->height = h;
        }
        void Image::setTexture(std::string url){
            
            SDL_DestroyTexture(this->texture);
            texture = nullptr;

            this->url = url;
            this->texture = IMG_LoadTexture(*(renderer), url.c_str());
            float i, j;
            SDL_GetTextureSize(this->texture, &i, &j);
            this->texWidth = i;
            this->texHeight = j;
            this->aspectRatio = static_cast<float>(i) / j;
            SDL_SetTextureBlendMode(this->texture, SDL_BLENDMODE_BLEND);
            std::cout << "Retextering " << url << "\n";
        }



        // This section is dedicated to define the class Button, a child of the Text Class.
        // Designed to make input, or rather "choices," possible in this framework.


        Button::Button(const char* link, int size, const std::string& label) : Text(link, size), label(label){}

        Button::~Button(){
            SDL_DestroySurface(surface);
            SDL_DestroyTexture(texture);
            TTF_CloseFont(font);
            surface = nullptr;
            texture = nullptr;
            font = nullptr;
        }

        void Button::setCords(float x, float y){
            this->x = x;
            this->y = y;
        }

        void Button::setBackgroundDims(float w, float h){
            this->bgW = w;
            this->bgH = h;
        }

        void Button::autoScaleDims(){
            int w, h;
            bool b = TTF_GetStringSize(this->font, this->label.c_str(), 0, &w, &h);
            setTextDims((float)w, (float)h);
        }

        void Button::setTextDims(float w, float h){
            this->textW = w;
            this->textH = h;
        }


        //This section is for the Screen itself, the core class of this framework, where everything begins.
        //All it takes is initializing this object with a width and height, then calling the Screen::initialize function in the main() function
        //of the program.

        //After calling the latter, a start() and update() should be defined, for they are already declared AND called within the Screen Intiliazation Function.

        Screen::Screen(int width, int height){
            this->width = width;
            this->height = height;
            TTF_Init();
        }

        int Screen::getWidth(){
            return width;
        }

        int Screen::getHeight(){
            return height;
        }


        SDL_Window* Screen::getWindow(){
            return this->window;
        }

        SDL_Renderer* Screen::getRenderer(){
            return this->renderer;
        }

        void Screen::initialize(){
            TTF_Init();
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

        void Screen::updateRenderer(){
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }

        void Screen::setColor(int r, int g, int b, int a){
            SDL_SetRenderDrawColor(renderer, r, g, b, a);
            updateRenderer();
        }

        void Screen::drawRectangle(int r, int g, int b, int a, float x, float y, float w, float h){
            SDL_SetRenderDrawColor(renderer, r, g, b, a);

            SDL_FRect rect = {x, y, w, h};  


            SDL_RenderFillRect(renderer, &rect);
        }

        Image* Screen::imageLoader(const std::string url, float w, float h){
            return new Image(&(this->renderer), url, w, h);
        }

        void Screen::imageRenderer(Image *img, int alpha, enum imageSize t){
            SDL_SetTextureAlphaMod(img->texture, alpha);
            SDL_FRect cords;
            cords.x = img->x;
            cords.y = img->y;
            cords.w = img->width;
            cords.h = img->height;
            SDL_RenderTexture(renderer, img->texture, nullptr, &cords);
        }

        void Screen::imageRenderer(Image *img, Rect src, int alpha, enum imageSize t){
            SDL_SetTextureAlphaMod(img->texture, alpha);
            SDL_FRect cords;
            cords.x = img->x;
            cords.y = img->y;
            cords.w = img->width;
            cords.h = img->height;
            SDL_RenderTexture(renderer, img->texture, &src, &cords);
        }

        void Screen::textRenderer(Text *txt, std::string text, float x, float y, float w, float h){
            std::cout << "\n" << txt->font;
            txt->surface = TTF_RenderText_Blended_Wrapped(
                txt->font,
                text.c_str(),
                text.length(),          
                txt->color,
                w
            );
            if (!txt->surface) {
                std::cout << "Text Surface Failed. \n" << std::endl;
                return;
            }
            txt->texture = SDL_CreateTextureFromSurface(renderer, txt->surface);
            SDL_DestroySurface(txt->surface);
            txt->surface = nullptr;
            SDL_FRect dst;
            dst.x = x;
            dst.y = y;
            dst.w = w;  
            dst.h = h;

            SDL_RenderTexture(renderer, txt->texture, NULL, &dst);
            SDL_DestroyTexture(txt->texture);
            txt->texture = nullptr;
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

        void Screen::scrollScreenAnimation(int r, int g, int b, int a, Image* &background, float w, float h, float start, float finish, float rate){
            float k = start;
            while (true) {

                SDL_RenderClear(renderer);
                imageRenderer(
                    background,
                    255,
                    COVER
                );

                
                drawRectangle(r, g, b, a,
                    k,          
                    0,           
                    w,     
                    h      
                );

                k += rate;

                SDL_RenderPresent(renderer);
                if (k >= finish && finish >= 0) break;
                if (k <= finish && finish < 0) break;
                SDL_Delay(16); 
            }
        }

        void Screen::buttonRenderer(Button *btn){
            
            drawRectangle(0, 0, 0, 255, btn->x + btn->textW/2.0 - btn->bgW/2.0, btn->y + btn->textH/2.0 - btn->bgH/2.0, btn->bgW, btn->bgH);
            btn->surface = TTF_RenderText_Blended_Wrapped(
                btn->font,
                btn->label.c_str(),
                btn->label.length(),          
                btn->color,
                btn->textW
            );
            if (!btn->surface) {
                std::cout << "Button Surface Failed. \n" << std::endl;
                return;
            }
            btn->texture = SDL_CreateTextureFromSurface(renderer, btn->surface);
            SDL_DestroySurface(btn->surface);
            btn->surface = nullptr;
            SDL_FRect dst;
            dst.x = btn->x;
            dst.y = btn->y;
            dst.w = btn->textW;  
            dst.h = btn->textH;

            SDL_RenderTexture(renderer, btn->texture, NULL, &dst);
            SDL_DestroyTexture(btn->texture);
            btn->texture = nullptr;
            
        }