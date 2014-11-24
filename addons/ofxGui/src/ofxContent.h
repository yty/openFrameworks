#pragma once

#include "ofxBaseGui.h"
#include "ofParameter.h"
#include "ofxPanel.h"
class ofxContent: public ofxBaseGui {
public:
	ofxContent(){}
	ofxContent(string contentName, ofBaseDraws &content, float width = defaultWidth);
	~ofxContent();

    ofxGuiGroup * setup(string contentName, ofBaseDraws &_content, float _fixwidth= defaultWidth);

    // Abstract methods we must implement, but have no need for!
    virtual bool mouseMoved(ofMouseEventArgs & args){return false;}
    virtual bool mousePressed(ofMouseEventArgs & args);
    virtual bool mouseDragged(ofMouseEventArgs & args){return false;}
    virtual bool mouseReleased(ofMouseEventArgs & args){return false;}
	virtual bool mouseScrolled(ofMouseEventArgs & args){return false;}

	virtual void saveTo(ofBaseSerializer& serializer){};
	virtual void loadFrom(ofBaseSerializer& serializer){};


	template<class ListenerClass, typename ListenerMethod>
	void addListener(ListenerClass * listener, ListenerMethod method){
		value.addListener(listener,method);
	}

	template<class ListenerClass, typename ListenerMethod>
	void removeListener(ListenerClass * listener, ListenerMethod method){
		value.removeListener(listener,method);
	}

    ofAbstractParameter & getParameter();

protected:
	void fixSize();//terry add

	float fixWidth; //terry add

    void render();
    ofParameter<string> label;
	ofPath fg;
    void generateDraw();
    void valueChanged(bool & value);
    bool setValue(float mx, float my, bool bCheckBounds){return false;}
	
	ofBaseDraws * content;
	string name;
	ofxGuiGroup contentGroup;

public:
	static ofBaseDraws * getCurrentContent();
	static ofBaseDraws * contentSelect;
	static string nameSelect;
	ofParameter<bool> value;
};
