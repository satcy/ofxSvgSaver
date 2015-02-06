#include "ofMain.h"
#include "ofxSvgSaver.h"

class ofApp : public ofBaseApp{
    ofxSvgSaver svg;
public:
    void setup(){
        
        svg.setup("export_test.svg", 300, 300);
        svg.addCircle(ofPoint(150,150), 100, true, ofColor::red);
        svg.addRectangle(ofPoint(10,10), 30, 30, false, ofColor(0), 1, ofColor::blue);
        svg.addElipse(ofPoint(10,40), 30, 20, true, ofColor(0,255,0), 2, ofColor::blue);
        svg.addLine(ofPoint(0,200), ofPoint(260, 220), 10, ofColor::green);
        
        vector<ofPoint> points;
        for ( int i=0; i<10; i++ ) {
            points.push_back(ofPoint(ofRandom(100)+150, ofRandom(100)));
        }
        svg.addFilledPoly(points, ofColor(0, 255, 255));
        svg.addStrokedPoly(points, 3, ofColor(0, 0, 0));
        
        svg.save();
    }
    
    
};

//========================================================================
int main( ){
	ofSetupOpenGL(300,300,OF_WINDOW);
	ofRunApp(new ofApp());
}
