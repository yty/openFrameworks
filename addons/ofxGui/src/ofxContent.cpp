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

ofxGuiGroup* ofxContent::setup(string contentName, ofBaseDraws &_content, float _fixwidth) {
	this->name = contentName;
	this->content = &_content;
	this->fixWidth = _fixwidth;

	fixSize();

	ofRegisterMouseEvents(this,OF_EVENT_ORDER_BEFORE_APP);

	value.set(contentName,false);

	value.addListener(this,&ofxContent::valueChanged);

	generateDraw();

	contentGroup.setup(this->name);
	contentGroup.add(this);
	return &contentGroup;
}

void ofxContent::fixSize(){

	b.width  = fixWidth;
	b.height = ((b.width * content->getHeight())/content->getWidth());
}

void ofxContent::generateDraw(){
	
	fg.clear();
	fg.setFilled(false);
	if(value){
		fg.setStrokeWidth(2);
		fg.setFillColor(thisFillColor);
	}else{
		fg.setStrokeWidth(0);
		fg.setStrokeColor(thisFillColor);
	}
	fg.rectangle(ofRectangle(b.x,b.y,b.width,b.height));
}

void ofxContent::render() {
	fixSize();
	value = (nameSelect == this->name);
	//ofColor c = ofGetStyle().color;
	this->content->draw(b.x,b.y,b.width,((b.width * content->getHeight())/content->getWidth()));
	fg.draw();
}

ofAbstractParameter & ofxContent::getParameter(){
	label.set("Content",name);
	return value;//ofAbstractParameter(); terry edit 2014.10.8
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