//
//  main.cpp
//  VerletModel
//
//  Created by Afroz Alam on 28/07/23.
//

#include <iostream>
#include "raylib.h"
#include "vector.cpp"
#include "settings.h"
#include "World.cpp"

using namespace std;

int main(){
    InitWindow(WIDTH, HEIGHT, "Verlet Physics Simulation");
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    World w;
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        w.update(GetFrameTime());
        if (IsKeyReleased(KEY_R)) {
            w = World();
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Made by AlazOz: asteroidalaz@gmail.com", 10, HEIGHT-50, 20, RAYWHITE);
        w.draw();
        DrawFPS(10, 50);
        EndDrawing();
    }
}


























/*
#include <iostream>

#include "raylib.h"
#include "vector.cpp"

#define WIDTH   800
#define HEIGHT  800
#define GRAVITY 1.9
#define FPS 60
#define rad 20
#define size 1
#define bound 200

using namespace std;

class Particle{
    Vector pos, prev, vel;
    
    void applyGravity(){
        vel.y += GRAVITY;
    }
    
    void checkColl(){
        
    }
    
    void containerBound(){
        
        // if the distance of the ball is greater than the bound, then, make 
        // it equal to bound
        
        
        Vector x(pos);
        Vector centre(WIDTH/2, HEIGHT/2);
        
        x -= centre; // pos - centre
        
        double mag = x.mag();
        
        if (mag > bound - rad){
            // The ball is out of boundary;
            // Make the ball to be at the bound distance from the centre
            
            x /= mag; // unit vector
            x *= bound - rad; // Scale it to make the ball just at boundary
            
            x += centre;
            pos = x;
        }
    }
    
public:
    Particle(){
        int ra = GetRandomValue(-100, 100);
        pos.x = WIDTH/2 + ra;
        ra = GetRandomValue(-100, 100);
        pos.y = HEIGHT/2 + ra;
        prev = pos;
    }
    void update(){
        // Storing the prev
        prev.x = pos.x;
        prev.y = pos.y;
        
        applyGravity();
        // Check Collision
        checkColl();
        // Contain in the cell
        containerBound();
        // Updating the pos
//        pos.x += vel.x * GetFrameTime();
        pos.x += vel.x;
//        pos.y += vel.y * GetFrameTime();
        pos.y += vel.y;
        
    }
    void draw(){
        DrawCircle(pos.x, pos.y, rad, WHITE);
    }
};
//    Note: The top left is (0,0) and y is +ve while moving downward
int main()
{
    Particle x[size];
    
    InitWindow(WIDTH, HEIGHT, "X3");
    SetTargetFPS(FPS);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircle(WIDTH/2, HEIGHT/2, bound, GRAY);
        for(int i = 0; i < size; i++){
            x[i].update();
            x[i].draw();
        }
        DrawFPS(10, 50);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
*/
