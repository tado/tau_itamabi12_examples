#include "ofMath.h"
#include "ofLog.h"
#include "ofxSphere.h"

static bool	bPrimitiveGenerateTexCoords	= true;

bool ofGetPrimitiveGenerateTexCoords() {
    return bPrimitiveGenerateTexCoords;
}

void ofEnablePrimitiveGenerateTexCoords() {
    bPrimitiveGenerateTexCoords = true;
}

void ofDisablePrimitiveGenerateTexCoords() {
    bPrimitiveGenerateTexCoords = false;
}

//----------------------------------------------------------
// Sphere

#pragma mark ** Sphere **

ofMesh sphereScratchMesh;
ofxSphereParameters lastGeneratedSphereParams;
ofxSphereParameters currentSphereParams;


//----------------------------------------
void ofxSphere(float x, float y, float z, float radius) {
    ofxSphere(ofPoint(x, y, z), radius);
}

//----------------------------------------
void ofxSphere(float x, float y, float radius) {
    ofxSphere(x, y, 0, radius);
}

//----------------------------------------
void ofxSphere(const ofPoint& position, float radius) {
    ofPushMatrix();
    ofTranslate(position);
    ofxSphere(radius);
    ofPopMatrix();
}

//----------------------------------------
void ofxSphere(float radius) {
    
    if( sphereScratchMesh.getNumVertices() == 0 ||
       !lastGeneratedSphereParams.equals( radius, currentSphereParams.numRings, currentSphereParams.numSegments ) ){
        
        ofGenerateSphereMesh( sphereScratchMesh, radius, currentSphereParams.numRings, currentSphereParams.numSegments );
        
        // Save the parameters of what we just generated
        lastGeneratedSphereParams.radius = radius;
        lastGeneratedSphereParams.numRings = currentSphereParams.numRings;
        lastGeneratedSphereParams.numSegments = currentSphereParams.numSegments;
    }
    
    if(ofGetStyle().bFill) {
        sphereScratchMesh.drawFaces();
    } else {
        sphereScratchMesh.drawWireframe(); // this won't really work, but leave it in for now.		
    }
    
}

void ofSetSphereResolution( int _numRings, int _numSegments ){
    lastGeneratedSphereParams.numRings = _numRings;
    lastGeneratedSphereParams.numSegments = _numSegments;
}

//----------------------------------------
void ofGenerateSphereMesh( ofMesh& _mesh, float _radius, int _numRings, int _numSegments ){
    
    cout << "*** ofGenerateSphereMesh ***" << endl;	
    
    _mesh.clear();	
    
    float uTile = 1.0f; // Texcoord tiling, do we want to support that?
    float vTile = 1.0f;		
    
    float fDeltaRingAngle = (PI / _numRings);
    float fDeltaSegAngle = (TWO_PI / _numSegments);
    
    int offset = 0;	
    
    // Generate the group of rings for the sphere
    for(unsigned int ring = 0; ring <= _numRings; ring++ ) {
        float r0 = _radius * sinf (ring * fDeltaRingAngle);
        float y0 = _radius * cosf (ring * fDeltaRingAngle);
        
        // Generate the group of segments for the current ring
        for(unsigned int seg = 0; seg <= _numSegments; seg++) {
            float x0 = r0 * sinf(seg * fDeltaSegAngle);
            float z0 = r0 * cosf(seg * fDeltaSegAngle);
            
            // Add one vertex to the strip which makes up the sphere
            
            ofVec3f pos(x0, y0, z0);
            
            _mesh.addVertex( pos );
            
            _mesh.addNormal( pos.getNormalized() );
            
            if( ofGetPrimitiveGenerateTexCoords()  ){
                //for (unsigned int tc=0;tc<numTexCoordSet;tc++)				
                _mesh.addTexCoord( ofVec2f( (float) seg / (float)_numSegments * uTile, (float) ring / (float)_numRings * vTile ) );
            }
            
            if (ring != _numRings) {
                // each vertex (except the last) has six indices pointing to it
                
                _mesh.addIndex(offset + _numSegments);
                _mesh.addIndex(offset);
                _mesh.addIndex(offset + _numSegments + 1);
                
                _mesh.addIndex(offset);
                _mesh.addIndex(offset + 1);
                _mesh.addIndex(offset + _numSegments + 1);
                
                offset ++;
            }
        }; // end for seg
    } // end for ring	
}