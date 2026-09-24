#include "raylib.h"
#include <vector>
#include <random>


#define WIDTH 1080
#define HEIGHT 720
#define RECT_WIDTH 30
#define RECT_HEIGHT 360
#define SIZE 512

int main(){
    std::random_device random;
    std::mt19937 generator(random());
    std::normal_distribution<float> dist(static_cast<int>(WIDTH/2), static_cast<int>(WIDTH/4));
    std::vector<int> positions = {};
    // Create windows and set FPS
    
    InitWindow(WIDTH, HEIGHT, "Exercise 0.1 - Random Walk");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        //draw a random point
        positions.insert(positions.end(), static_cast<int>(dist(generator)));
        if(positions.size() > SIZE){
            positions.erase(positions.begin());
        }
        for(int x: positions){
            DrawRectangle(x-(RECT_WIDTH/2), HEIGHT/2 - (RECT_HEIGHT/2), RECT_WIDTH, RECT_HEIGHT, {255,255,255,20} );
        }
        
        EndDrawing();
    }

    return 0;
}