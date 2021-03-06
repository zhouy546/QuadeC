//
//  Particle.cpp
//  01_oneParticle
//
//  Created by Bernardo Schorr on 3/2/15.
//
//

#include "Particle.h"

Particle::Particle(float _instensity) {
    pos.set(ofGetWindowSize()/2);
    vel.x = ofRandom(-1*_instensity, 1*_instensity);
    vel.y = ofRandom(-1*_instensity, 1*_instensity);
    lifespan = 255;
}

void Particle::setup() {
    
}

void Particle::resetForces() {
    acc *= 0;
}

void Particle::applyForce(ofVec2f force) {
    acc += force;
}

void Particle::update() {
    vel += acc;
    pos += vel;
    
    if (lifespan > 0) lifespan -= 3.0;
    
}

void Particle::draw(float size) {
    ofSetColor(lifespan);
    ofCircle(pos, size);
}




