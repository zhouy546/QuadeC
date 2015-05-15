//
//  Particle.h
//  01_oneParticle
//
//  Created by Bernardo Schorr on 3/2/15.
//
//

#pragma once

#include "ofMain.h"

class Particle {
public:
    
    Particle(float _instensity);
    
    void setup();
    
    void resetForces();
    void applyForce(ofVec2f force);
    
    void update();
    void draw(float size);
    
    ofVec2f pos, vel, acc;
    float lifespan;
    
};


