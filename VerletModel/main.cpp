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

