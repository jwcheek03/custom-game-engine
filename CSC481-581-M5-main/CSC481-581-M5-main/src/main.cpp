#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cmath>
#include <string>
#include <iostream>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const double MAX_SPEED = 8.0;
const double MIN_SPEED = 0.5;

struct Timeline {
    double timeScale = 1.0; 
    Uint64 lastTicks = 0;
    double accumulated = 0.0; // Time units accumulated since initialization
    
    void init() {
        // Initialize lastTicks with current SDL ticks
        // Your Code here
    }
    
    double update() {
        /** 
        * Update accumulated variable with how many ticks past since lastTicks
        * Utilize timeScale to determine how quickly or slowly accumulated grows
        * Also update last ticks for next update cycle
        * Return the accumulated variable
         */
        // Your Code Here
        return 0.0; // Returning 0 so clock will appear stopped
    }
    
    void setScale(double s) { 
        timeScale = std::max(MIN_SPEED, std::min(MAX_SPEED, s)); 
    }
    
    double getScale() const { return timeScale; }
};

SDL_Texture* renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
    if (!surface) return nullptr;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    return texture;
}

void drawClock(SDL_Renderer* renderer, TTF_Font* font, TTF_Font* numberFont, const Timeline& timeline, double currentTime) {
    // Clock center and radius
    int cx = WINDOW_WIDTH / 2;
    int cy = WINDOW_HEIGHT / 2;
    int radius = 200;
    
    // Draw clock face (12 markers)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < 12; i++) {
        double angle = i * M_PI / 6;
        int x1 = cx + (int)(radius * cos(angle));
        int y1 = cy + (int)(radius * sin(angle));
        int x2 = cx + (int)((radius - 20) * cos(angle));
        int y2 = cy + (int)((radius - 20) * sin(angle));
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }
    
    // Draw numbers 1-12
    SDL_Color black = {0, 0, 0, 255};
    for (int i = 1; i <= 12; i++) {
        // Calculate angle - 12 is at top (angle 0), so we start from there
        double angle = (i - 3) * M_PI / 6; // -3 to rotate so 12 is at top
        
        // Position numbers outside the markers
        int numberRadius = radius + 30;
        int x = cx + (int)(numberRadius * cos(angle));
        int y = cy + (int)(numberRadius * sin(angle));
        
        std::string numberText = std::to_string(i);
        SDL_Texture* numberTex = renderText(renderer, numberFont, numberText, black);
        
        if (numberTex) {
            float tw, th;
            SDL_GetTextureSize(numberTex, &tw, &th);
            
            // Center the text on the calculated position
            SDL_FRect dst = { 
                (float)(x - tw/2), 
                (float)(y - th/2), 
                (float)tw, 
                (float)th 
            };
            
            SDL_RenderTexture(renderer, numberTex, NULL, &dst);
            SDL_DestroyTexture(numberTex);
        }
    }
    
    // Draw second hand
    double seconds = fmod(currentTime, 60.0);
    double angle = (seconds / 60.0) * 2 * M_PI - M_PI/2;
    int handLength = radius - 40;
    int xEnd = cx + (int)(handLength * cos(angle));
    int yEnd = cy + (int)(handLength * sin(angle));
    SDL_RenderLine(renderer, cx, cy, xEnd, yEnd);
    
    // Draw speed multiplier text
    std::string speedText = "Speed: x" + std::to_string(timeline.getScale());
    SDL_Texture* textTex = renderText(renderer, font, speedText, black);
    if (textTex) {
        float tw, th;
        SDL_GetTextureSize(textTex, &tw, &th);
        SDL_FRect dst = { (float)(WINDOW_WIDTH - tw - 10), 10.0f, (float)tw, (float)th };
        SDL_RenderTexture(renderer, textTex, NULL, &dst);
        SDL_DestroyTexture(textTex);
    }
    
    // Draw instructions
    std::string instructions = "UP/DOWN arrows to change speed";
    SDL_Texture* instructTex = renderText(renderer, font, instructions, black);
    if (instructTex) {
        float tw, th;
        SDL_GetTextureSize(instructTex, &tw, &th);
        SDL_FRect dst = { 10.0f, 10.0f, (float)tw, (float)th };
        SDL_RenderTexture(renderer, instructTex, NULL, &dst);
        SDL_DestroyTexture(instructTex);
    }
}

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }
    
    if (TTF_Init() < 0) {
        SDL_Log("TTF_Init Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Timeline Clock", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    TTF_Font* font = TTF_OpenFont("./../fonts/DejaVuSans.ttf", 18);
    TTF_Font* numberFont = TTF_OpenFont("./../fonts/DejaVuSans-Bold.ttf", 24);
    
    if (!font) {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    
    if (!numberFont) {
        numberFont = font;
    }
    
    Timeline timeline;
    timeline.init();
    
    bool running = true;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_UP) {
                    timeline.setScale(timeline.getScale() * 2.0);
                } else if (event.key.key == SDLK_DOWN) {
                    timeline.setScale(timeline.getScale() * 0.5);
                }
            }
        }
        
        double currentTime = timeline.update();
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        // Draw (clock + text)
        drawClock(renderer, font, numberFont, timeline, currentTime);
        
        SDL_RenderPresent(renderer);
    }
    
    if (numberFont != font) {
        TTF_CloseFont(numberFont);
    }
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
