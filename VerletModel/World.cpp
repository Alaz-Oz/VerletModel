//
//  World.cpp
//  VerletModel
//
//  Created by Afroz Alam on 25/10/23.
//

// While debugging 
#include <iostream>

#pragma once
#include "vector.cpp"
#include "settings.h"
#include "raylib.h"
#include "util/LinkedList.cpp"
using namespace std;
class World{
    struct Object{
        Vector previous_position, current_position, acceleration;
        float rad = 10;
        void updatePosition(float dt){
            // Note this is (velocity*dt)
            const Vector velocity = current_position - previous_position;
            previous_position = current_position;
            
            // Verlet Integration
            current_position = current_position + velocity + acceleration * dt * dt;
            // Reset acceleration
            acceleration = {};
            
        }
        void accelerate(Vector acc){
            acceleration += acc;
        }
        ~Object(){
            cout << "::Object Destroyed::" << endl;
        }
    };
    LinkedList<Object> objects;
    void applyGravity(){
        
        objects.foreach([](Object& object, int i) -> bool {
            object.accelerate({0, GRAVITY});
            return false;
        });
    }
    
    void applyCircularConstraint(){
        const Vector centre(WIDTH/2, HEIGHT/2);
        const float radiusOfBound = RAD_BOUND;
        
        objects.foreach([centre, radiusOfBound](Object& object, int i) -> bool {
            Vector to_obj = object.current_position - centre;
            
            const float x = radiusOfBound - object.rad;
            const float mag = to_obj.mag();
            
            if (mag > x){
                // The ball is out of boundary;
                // Make the ball to be at the bound distance from the centre
                
                to_obj /= mag; // unit vector
                to_obj *= x; // Scale it to make the ball just at boundary
                
                to_obj += centre;
                object.current_position = to_obj;
            }
            return false;
        });
    }
    
    void applyCollision(){
        objects.foreach([this](Object& obj1, int i) -> bool {
            objects.foreach([&obj1, i](Object& obj2, int j) -> bool {
                if (j <= i) return false; // No collisions between same objects, and don't repeat object
                Vector collisionAxis = obj2.current_position - obj1.current_position;
                float mag = collisionAxis.mag();
                if (mag < obj1.rad + obj2.rad){
                    // Colliding
                    collisionAxis /= mag; // Unit vector
                    const float delta = mag - (obj1.rad + obj2.rad);
                    obj1.current_position += collisionAxis * delta * 0.5f;
                    obj2.current_position -= collisionAxis * delta * 0.5f;
                    
                }
                return false;
            });
            return false;
        });
    }
    void updatePosition(float dt){
        
        objects.foreach([dt](Object& o, int i) -> bool {
            o.updatePosition(dt);
            return false;
        });
    }
    int counter=0;
    void insertAtMousePoint(){
        int threshold = 15;
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && counter%threshold == 0) {
            float x = GetMouseX(), y = GetMouseY();
            Object o{{x,y},{x,y}};
            o.rad = GetRandomValue(5, 30);
            objects.pushFront(o);
        }
        counter++;
    }
public:
    // Initializes the World
    World(){
        for (int i = 0; i < COUNT; i++) {
            float x = WIDTH/2 + GetRandomValue(0, 50);
            float y = HEIGHT/2 + GetRandomValue(0, 50);
            Object o{{x,y},{x,y}, {0,0}, (float) GetRandomValue(5, 30)};
            objects.pushFront(o);
        }
    }
    
    // Updates the physical element every frame
    void update(float dt){
        float subdt = dt/SUBSTEPS;
        for(int i = 0; i < SUBSTEPS; i++){
            applyGravity();
            applyCircularConstraint();
            applyCollision();
            updatePosition(subdt);
        }
            insertAtMousePoint();
    }
    
    // Draws all the visual elements
    void draw(){
        DrawCircle(WIDTH/2, HEIGHT/2, RAD_BOUND, WHITE);
        objects.foreach([](Object& o, int i) -> bool{
            DrawCircle(o.current_position.x, o.current_position.y, o.rad, BLACK);
            DrawCircle(o.current_position.x, o.current_position.y, o.rad-1, GRAY);
            return false;
        });
        DrawText(("Items Count: " + to_string(objects.getSize())).c_str(), WIDTH- 150, 50, 15, BLUE);
    }
};
