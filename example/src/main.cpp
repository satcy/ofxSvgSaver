#include "ofMain.h"
#include "ofxSvgSaver.h"
#include "ofxSvg.h"

class ofApp : public ofBaseApp{
    ofxSvgSaver svg;
    ofxSVG exported_svg;
public:
    void setup(){
        ofBackground(255);
        svg.setup("export_test.svg", 300, 300);
        svg.addCircle(ofPoint(150,150), 100, true, ofColor::red);
        svg.addRectangle(ofPoint(10,10), 30, 30, false, ofColor(100), 1, ofColor::blue);
        svg.addElipse(ofPoint(30,40), 30, 15, true, ofColor(0,255,0), 2, ofColor::blue);
        vector<ofPoint> line;
        line.push_back(ofPoint(1, 200));
        line.push_back(ofPoint(260, 220));
        svg.addPolyline(line, false, ofColor(0), 10, ofColor::blue);
        
        vector<ofPoint> points;
        for ( int i=0; i<10; i++ ) {
            points.push_back(ofPoint(ofRandom(100)+150, ofRandom(100)));
        }
        svg.addPolygon(points, true, ofColor(0, 255, 255), 1, ofColor(255,0,0));
        
        svg.save();
        
        exported_svg.load("export_test.svg");
        
    }
    
    void draw(){
        exported_svg.draw();
    }
    
    
};

//========================================================================
int main( ){
	ofSetupOpenGL(300,300,OF_WINDOW);
	ofRunApp(new ofApp());
}
