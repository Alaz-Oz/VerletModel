//
//  vector.cpp
//  abck
//
//  Created by Afroz Alam on 10/05/23.
//
#pragma once
#include <math.h>
using namespace std;
struct Vector{
public:
    float x, y;
    
    Vector(){
        x = 0;
        y = 0;
    }
    
    Vector(const Vector& o){
        x = o.x;
        y = o.y;
    }
    Vector(float x, float y){
        set(x, y);
    }
    void set(float x, float y){
        this->x = x;
        this->y = y;
    }
    Vector operator+(Vector o) const{
        Vector vec;
        vec.x = this->x + o.x;
        vec.y = this->y + o.y;
        return vec;
    }
    Vector operator-(Vector o) const{
        Vector vec;
        vec.x = this->x - o.x;
        vec.y = this->y - o.y;
        return vec;
    }
    Vector operator*(float o) const{
        Vector vec;
        vec.x = this->x * o;
        vec.y = this->y * o;
        return vec;
    }
    void operator=(const Vector o){
        x = o.x;
        y = o.y;
    }
    void operator+=(const Vector o){
        x += o.x;
        y += o.y;
    }
    void operator-=(const Vector o){
        x -= o.x;
        y -= o.y;
    }
    void operator*=(const float x){
        this->x *= x;
        this->y *= x;
    }
    void operator/=(const float x){
        this->x /= x;
        this->y /= x;
    }
    float mag2() const{
        return x*x + y*y;
    }
    float mag() const{
        return sqrt(mag2());
    }
};
