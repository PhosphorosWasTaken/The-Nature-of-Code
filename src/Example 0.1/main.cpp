#include "raylib.h"
#include <vector>
#include <random>


#define WIDTH 1080
#define HEIGHT 720
#define HISTORY 255

struct point{
    int x;
    int y;

    point(int x, int y){
        this->x=x;
        this->y=y;
    }
};

class Walker{
private:
    int x;
    int y;
    int LimitX;
    int LimitY;
    std::random_device rd;
    std::mt19937 gen;

public:
    std::vector<point> PreviousPositions;

    Walker(int LimX, int LimY): gen(rd()){
        x = static_cast<int>(LimX / 2);
        y = static_cast<int>(LimY / 2);
        LimitX = LimX;
        LimitY = LimY;
    }

    void Walk(){
        std::uniform_int_distribution<int> dist(0,3);

        switch(dist(gen)){
            case 0: // X forward 1
            {
                if (x == LimitX){
                    x -= 1;
                    break;
                }
                x += 1;
                break;
            }
            case 1: // X backward 1
            {
                if(x == 0){
                    x += 1;
                    break;
                }
                x -= 1;
                break;
            }
            case 2: // Y forward 1
            {
                if(y == LimitY){
                    y -= 1;
                    break;
                }
                y += 1;
                break;
            }
            case 3: // Y backward 1
            {
                if(y == 0){
                    y += 1;
                    break;
                }
                y -= 1;
                break;
            }
        }
        PreviousPositions.insert(PreviousPositions.end(), point(x, y));

        if(PreviousPositions.size() > HISTORY){
            PreviousPositions.erase(PreviousPositions.begin());
        }
    }
};

int main(){
    Walker example((WIDTH/10)-1,(HEIGHT/10)-1); // Create random walker

    // Create windows and set FPS
    InitWindow(WIDTH, HEIGHT, "Exercise 0.1 - Random Walk");
    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the points
        for(int i = 0; i < example.PreviousPositions.size(); i++){
            Color temp = {static_cast<unsigned char>(i),static_cast<unsigned char>(i),static_cast<unsigned char>(i),static_cast<unsigned char>(i)};

            DrawRectangle(example.PreviousPositions.at(i).x*10, example.PreviousPositions.at(i).y*10, 10, 10, temp);
        }

        // I'm lazy and can't be bothered to do this properly, so imma just draw grid lines on top of the random walker
        for(int i = 0; i <= WIDTH/10; i++){
            DrawLine(i*10, 0, i*10, HEIGHT, GRAY);
        }

        for(int i = 0; i <= HEIGHT/10; i++){
            DrawLine(0, i*10, WIDTH, i*10, GRAY);
        }

        EndDrawing();

        // Update the random walker
        example.Walk();
    }

    return 0;
}