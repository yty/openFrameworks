#include "ofxContent.h"
#include "ofGraphics.h"

ofBaseDraws * ofxContent::contentSelect = NULL;
string ofxContent::nameSelect = "";
ofBaseDraws* ofxGetCurrentContent(){
	return ofxContent::getCurrentContent();
}

ofxContent::ofxContent(string contentName, ofBaseDraws &_content, float fixwidth){
	setup(contentName,_content,fixwidth);
}

ofxContent::~ofxContent(){
    value.removeListener(this,&ofxContent::valueChanged);
}

ofxContent* ofxContent::setup(string contentName, ofBaseDraws &_content, float _fixwidth) {
	this->name = contentName;
	this->content = &_content;
	this->fixWidth = _fixwidth;
	this->initWidth = content->getWidth();
	this->initHeight = content->getHeight();

	fixSize();

	ofRegisterMouseEvents(this,OF_EVENT_ORDER_BEFORE_APP);
	value.set(contentName,false);
	value.addListener(this,&ofxContent::valueChanged);
	generateDraw();
    return this;
}

void ofxContent::fixSize(){

	b.width  = fixWidth;
	b.height = fixWidth * (content->getHeight()/content->getWidth()) * ( content->getWidth()/initWidth) + defaultHeight;

}

void ofxContent::generateDraw(){
	bg.clear();
	bg.setFillColor(thisBackgroundColor);
	bg.setFilled(true);
	bg.rectangle(ofRectangle(b.x,b.y+b.height-defaultHeight,b.width,defaultHeight));

	fg.clear();
	if(value){
		fg.setFilled(true);
		fg.setFillColor(thisFillColor);
	}else{
		fg.setFilled(false);
		fg.setStrokeWidth(1);
		fg.setStrokeColor(thisFillColor);
	}
	fg.rectangle(ofRectangle(b.x,b.y+b.height-defaultHeight,b.width,defaultHeight));

	textMesh = getTextMesh(name, b.x + textPadding,b.y + defaultHeight/2 + 4 + b.height-defaultHeight);
}

void ofxContent::render() {
	fixSize();
	value = (nameSelect == this->name);
	ofColor c = ofGetStyle().color;
	this->content->draw(b.x , b.y,b.width*(content->getWidth()/initWidth),b.height - defaultHeight);
	bg.draw();
	fg.draw();
	ofBlendMode blendMode = ofGetStyle().blendingMode;
	if(blendMode!=OF_BLENDMODE_ALPHA){
		ofEnableAlphaBlending();
	}
    ofSetColor(textColor);
    bindFontTexture();
#ifdef SONOVO_FONTSTASH
	unicodeFont.draw(name,fontSize, b.x + textPadding,b.y + defaultHeight/2 + fontSize/2 - (2 * (fontSize/12)) + b.height-defaultHeight);
#else
	textMesh.draw();
#endif
    unbindFontTexture();
    ofSetColor(c);
	if(blendMode!=OF_BLENDMODE_ALPHA){
		ofEnableBlendMode(blendMode);
	}
}

ofAbstractParameter & ofxContent::getParameter(){
	label.set("Content",name);
	return label;
}

void ofxContent::valueChanged(bool & value){
	
	generateDraw();
}

bool ofxContent::mousePressed(ofMouseEventArgs & args){
	if (isGuiDrawing()&&b.inside(args.x,args.y)){
		if (args.button == 0){
			contentSelect = this->content;
			nameSelect = name;
		}

	    if (args.button == 2){
			if (contentSelect == this->content){
				contentSelect = NULL;
				nameSelect = "";
			}
		}
	}
	return false;
}

ofBaseDraws* ofxContent::getCurrentContent(){
	return contentSelect;
}