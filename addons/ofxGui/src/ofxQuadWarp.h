#pragma once

#include "ofxBaseGui.h"
#include "ofParameter.h"
#include "ofParameterGroup.h"
#include "ofxGuiGroup.h"

#define MOUSE_DISTANCE 5

class ofxQuadWarp: public ofxBaseGui {
public:
    ofxQuadWarp();
    ofxQuadWarp(string quadWarpName, ofBaseDraws &content,float _fixwidth= defaultWidth);
    virtual ~ofxQuadWarp();

	ofxGuiGroup * setup(string quadWarpName, ofBaseDraws &content,float _fixwidth= defaultWidth);

    // Abstract methods we must implement, but have no need for!
    virtual bool mouseMoved(ofMouseEventArgs & args);
    virtual bool mousePressed(ofMouseEventArgs & args);
    virtual bool mouseDragged(ofMouseEventArgs & args);
    virtual bool mouseReleased(ofMouseEventArgs & args);
	virtual bool mouseScrolled(ofMouseEventArgs & args){return false;}

	void keyPressed(int key);
	void keyReleased(int key);

	template<class ListenerClass, typename ListenerMethod>
	void addListener(ListenerClass * listener, ListenerMethod method){
		label.addListener(listener,method);
	}

	template<class ListenerClass, typename ListenerMethod>
	void removeListener(ListenerClass * listener, ListenerMethod method){
		label.removeListener(listener,method);
	}

    ofAbstractParameter & getParameter();
	void InitQuadPos(float w,float h);
	void InitQuadPos(float w,float h,ofPoint &p1,ofPoint &p2,ofPoint &p3,ofPoint &p4);

	ofVec3f * getDstQuadPos();
	ofVec3f * getSrcQuadPos();

	void minimize();
    void maximize();
    void minimizeAll();
    void maximizeAll();

	int curMoveStep;
	bool bGuiActive;
	void fixSize(); //terry add

protected:
	float fixWidth; //terry add

    void render();
    void valueChanged(string & value);
    bool setValue(float mx, float my, bool bCheckBounds);
    ofPath bg;
    ofVboMesh textMesh;
	string name;

	
	vector<bool> bCircle;
	ofRectangle rectCircumscribe;
	float lastMousePressTime;
	ofPoint * _dstQuadPos;
	ofPoint * srcQuadPos;

	ofPath circumscribe;
	ofPath circle;
	ofBaseDraws * content;
    ofParameter<ofVec3f> * dstQuadPos;
	ofParameterGroup dstQuadPosGroup;
	
	ofxGuiGroup quadWarpGroup;

	float width;
	float height;
};