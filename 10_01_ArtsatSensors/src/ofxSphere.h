#pragma once

#include "ofGraphics.h"
#include "ofVectorMath.h"

bool ofGetPrimitiveGenerateTexCoords();
void ofEnablePrimitiveGenerateTexCoords();
void ofDisablePrimitiveGenerateTexCoords();

//----------------------------------------------------------
// Sphere

void ofxSphere(float x, float y, float z, float radius);
void ofxSphere(float x, float y, float radius);
void ofxSphere(const ofPoint& position, float radius);
void ofxSphere(float radius);

void ofSetSphereResolution( int _numRings, int _numSegments );
void ofGenerateSphereMesh( ofMesh& _mesh, float _radius, int _numRings = 64, int _numSegments = 64 );

// Small helper classes to keep track of with what settings we've generated meshes with
//----------------------------------------------------------
class ofxSphereParameters{
public:	
    
    ofxSphereParameters() { 
        radius = -1.0f; numRings = 64; numSegments = 64; // set defaults, apart from radius
    }
    
    bool equals( float _radius, int _numRings, int _numSegments ){
        if( radius == _radius && numRings == _numRings && numSegments == _numSegments ){
            return true;
        } else {
            return false;			
        }
    }
    
    float radius;
    int numRings;
    int numSegments;
};