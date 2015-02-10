/*
The MIT License (MIT)

Copyright (c) 2015 Satoshi HORII ( http://satcy.net/ )

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once

#include "ofMain.h"
#include "simple_svg.hpp"

class ofxSvgSaver{
protected:
    ofPtr<svg::Document> doc;
public:
    
    void setup(string const & file_name, int w, int h);
    bool save();
    
    void addPaths(vector<ofPath> & paths);
    
    void addOfPolylines(vector<ofPolyline> const & polys,
                      bool isFilled = true, ofColor const & col = ofColor(0),
                      float stroke_width = -1, ofColor const & stroke_col = ofColor(0));
    
    void addOfPolyline(ofPolyline const & poly,
                     bool isFilled = true, ofColor const & col = ofColor(0),
                     float stroke_width = -1, ofColor const & stroke_col = ofColor(0));
    
    
    void addPolyline(vector<ofPoint> const & points,
                     bool isFilled = true, ofColor const & col = ofColor(0),
                     float stroke_width = -1, ofColor const & stroke_col = ofColor(0));
    void addPolygon(vector<ofPoint> const & points,
                    bool isFilled = true, ofColor const & col = ofColor(0),
                    float stroke_width = -1, ofColor const & stroke_col = ofColor(0));
    
    void addCircle(ofPoint const & center, double diameter,
                   bool isFilled = true, ofColor const & col = ofColor(0),
                   float stroke_width = -1, ofColor const & stroke_col = ofColor(0));
    void addRectangle(ofPoint const & point, double width, double height,
                      bool isFilled = true, ofColor const & col = ofColor(0),
                      float stroke_width = -1, ofColor const & stroke_col = ofColor(0));
    void addElipse(ofPoint const & point, double width, double height,
                   bool isFilled = true, ofColor const & col = ofColor(0),
                   float stroke_width = -1, ofColor const & stroke_col = ofColor(0));
    //void addLine(ofPoint const & start, ofPoint const & end, float stroke_width, ofColor const & stroke_col);
    
    
};



void ofxSvgSaver::setup(string const & file_name, int w, int h){
    svg::Dimensions dimensions(w, h);
    doc = ofPtr<svg::Document>( new svg::Document(ofToDataPath(file_name, true), svg::Layout(dimensions, svg::Layout::TopLeft)) );
}

bool ofxSvgSaver::save(){
    if ( !doc ) return false;
    return doc->save();
}

void ofxSvgSaver::addPaths(vector<ofPath> & paths){
    for ( int i=0; i<paths.size(); i++ ) {
        ofPath path = paths[i];
        addOfPolylines(path.getOutline(), path.isFilled(), path.getFillColor(), path.getStrokeWidth(), path.getStrokeWidth());
    }
}

void ofxSvgSaver::addOfPolylines(vector<ofPolyline> const & polys,
                               bool isFilled, ofColor const & col,
                               float stroke_width, ofColor const & stroke_col){
    for ( int i=0; i<polys.size(); i++ ) {
        addOfPolyline(polys[i], isFilled, col, stroke_width, stroke_col);
    }
}

void ofxSvgSaver::addOfPolyline(ofPolyline const & poly,
                              bool isFilled, ofColor const & col,
                              float stroke_width, ofColor const & stroke_col){
    if ( poly.isClosed() ) {
        addPolygon(poly.getVertices(), isFilled, col, stroke_width, stroke_col);
    } else {
        addPolyline(poly.getVertices(), isFilled, col, stroke_width, stroke_col);
    }
}

void ofxSvgSaver::addPolyline(vector<ofPoint> const & points,
                 bool isFilled, ofColor const & col,
                 float stroke_width, ofColor const & stroke_col){
    if ( !doc ) return;
    
    svg::Polyline poly(svg::Fill( isFilled ? svg::Color(col.r, col.g, col.b) : svg::Color::Transparent ),
                      svg::Stroke(stroke_width, stroke_width > 0 ? svg::Color(stroke_col.r, stroke_col.g, stroke_col.b) : svg::Color::Transparent ));
    for ( int i=0; i<points.size(); i++ ) {
        poly << svg::Point(points[i].x, points[i].y);
    }
    *doc << poly;
}

void ofxSvgSaver::addPolygon(vector<ofPoint> const & points,
                bool isFilled, ofColor const & col,
                float stroke_width, ofColor const & stroke_col){
    if ( !doc ) return;
    
    svg::Polygon poly(svg::Fill( isFilled ? svg::Color(col.r, col.g, col.b) : svg::Color::Transparent ),
                      svg::Stroke(stroke_width, stroke_width > 0 ? svg::Color(stroke_col.r, stroke_col.g, stroke_col.b) : svg::Color::Transparent ));
    for ( int i=0; i<points.size(); i++ ) {
        poly << svg::Point(points[i].x, points[i].y);
    }
    *doc << poly;
}

void ofxSvgSaver::addCircle(ofPoint const & center, double diameter,
               bool isFilled, ofColor const & col,
               float stroke_width, ofColor const & stroke_col){
    if ( !doc ) return;
    
    svg::Circle circle(svg::Point(center.x, center.y), diameter,
                       svg::Fill( isFilled ? svg::Color(col.r, col.g, col.b) : svg::Color::Transparent ),
                       svg::Stroke(stroke_width, stroke_width > 0 ? svg::Color(stroke_col.r, stroke_col.g, stroke_col.b) : svg::Color::Transparent ));
    *doc << circle;
}

void ofxSvgSaver::addRectangle(ofPoint const & point, double width, double height,
                  bool isFilled, ofColor const & col,
                  float stroke_width, ofColor const & stroke_col){
    if ( !doc ) return;
    
    svg::Rectangle rect(svg::Point(point.x, point.y), width, height,
                        svg::Fill( isFilled ? svg::Color(col.r, col.g, col.b) : svg::Color::Transparent ),
                        svg::Stroke(stroke_width, stroke_width > 0 ? svg::Color(stroke_col.r, stroke_col.g, stroke_col.b) : svg::Color::Transparent ));
    *doc << rect;
    
}

void ofxSvgSaver::addElipse(ofPoint const & point, double width, double height,
                               bool isFilled, ofColor const & col,
                               float stroke_width, ofColor const & stroke_col){
    if ( !doc ) return;
    
    svg::Elipse elipse(svg::Point(point.x, point.y), width, height,
                        svg::Fill( isFilled ? svg::Color(col.r, col.g, col.b) : svg::Color::Transparent ),
                        svg::Stroke(stroke_width, stroke_width > 0 ? svg::Color(stroke_col.r, stroke_col.g, stroke_col.b) : svg::Color::Transparent ));
    *doc << elipse;
    
}
/*
void ofxSvgSaver::addLine(ofPoint const & start, ofPoint const & end, float stroke_width, ofColor const & stroke_col){
    if ( !doc ) return;
    
    svg::Line line(svg::Point(start.x, start.y), svg::Point(end.x, end.y),
                   svg::Stroke(stroke_width, svg::Color(stroke_col.r, stroke_col.g, stroke_col.b)));
    
    *doc << line;
}*/
