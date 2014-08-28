#include "ofxQuadWarp.h"
#include "ofGraphics.h"

ofxQuadWarp::ofxQuadWarp(){
	bGuiActive = false;
	bCircle.push_back(false);
	bCircle.push_back(false);
	bCircle.push_back(false);
	bCircle.push_back(false);

	dstQuadPos = NULL;
	content = NULL;
	srcQuadPos = NULL;
	_dstQuadPos = NULL;
}

ofxQuadWarp::ofxQuadWarp(string quadWarpName, ofBaseDraws &content, float _fixwidth){
	setup(quadWarpName,content,_fixwidth);
}

ofxQuadWarp::~ofxQuadWarp(){
   
}

ofxGuiGroup* ofxQuadWarp::setup(string quadWarpName, ofBaseDraws &_content, float _fixwidth) {

	name = quadWarpName;
	this->content = &_content;
	this->fixWidth = _fixwidth;

	b.x = 0;
	b.y = 0;
	curMoveStep = 1;
	fixSize();

	ofRegisterMouseEvents(this,OF_EVENT_ORDER_BEFORE_APP);

	InitQuadPos(content->getWidth(),content->getHeight());
	
	quadWarpGroup.setup(quadWarpName);
	quadWarpGroup.add(this);
	return &quadWarpGroup;
}

void ofxQuadWarp::fixSize(){
	b.width  = fixWidth;
	b.height = ((b.width * content->getHeight())/content->getWidth());
}

void ofxQuadWarp::render() {



	fixSize();
	ofColor c = ofGetStyle().color;
	this->content->draw(b.x , b.y,b.width,b.height );

	bg.draw();
	circumscribe.clear();
	circumscribe.setStrokeWidth(3);
	circumscribe.setColor(ofColor::darkRed);
	circumscribe.moveTo(dstQuadPos[0]->x * width + b.x,dstQuadPos[0]->y * height + b.y);
	circumscribe.lineTo(dstQuadPos[1]->x * width + b.x,dstQuadPos[1]->y * height + b.y);
	circumscribe.moveTo(dstQuadPos[1]->x * width + b.x,dstQuadPos[1]->y * height + b.y);
	circumscribe.lineTo(dstQuadPos[2]->x * width + b.x,dstQuadPos[2]->y * height + b.y);
	circumscribe.moveTo(dstQuadPos[2]->x * width + b.x,dstQuadPos[2]->y * height + b.y);
	circumscribe.lineTo(dstQuadPos[3]->x * width + b.x,dstQuadPos[3]->y * height + b.y);
	circumscribe.moveTo(dstQuadPos[3]->x * width + b.x,dstQuadPos[3]->y * height + b.y);
	circumscribe.lineTo(dstQuadPos[0]->x * width + b.x,dstQuadPos[0]->y * height + b.y);
	circumscribe.draw();

	for (int i = 0; i < 4; i++){
		if (bCircle[i]){
			circle.clear();
			circle.setFillColor(ofColor(255,0,0));
			circle.setFilled(true);
			circle.circle(0,0,4);
			circle.draw(dstQuadPos[i]->x * width + b.x, dstQuadPos[i]->y * height + b.y);
		}else {
			circle.clear();
			circle.setFillColor(ofColor(0,255,0));
			circle.setFilled(true);
			circle.circle(0,0,3);
			circle.draw(dstQuadPos[i]->x * width + b.x, dstQuadPos[i]->y * height + b.y);
		}
	}

	ofBlendMode blendMode = ofGetStyle().blendingMode;
	if(blendMode!=OF_BLENDMODE_ALPHA){
		ofEnableAlphaBlending();
	}
    ofSetColor(textColor);

    ofSetColor(c);
	if(blendMode!=OF_BLENDMODE_ALPHA){
		ofEnableBlendMode(blendMode);
	}
}

ofAbstractParameter & ofxQuadWarp::getParameter(){
	dstQuadPosGroup.setName(name);
	dstQuadPosGroup.add(dstQuadPos[0]);
	dstQuadPosGroup.add(dstQuadPos[1]);
	dstQuadPosGroup.add(dstQuadPos[2]);
	dstQuadPosGroup.add(dstQuadPos[3]);
	return dstQuadPosGroup;
}

void ofxQuadWarp::valueChanged(string & value){
	generateDraw();
}

bool ofxQuadWarp::mouseMoved(ofMouseEventArgs & args){
	return false;
}

bool ofxQuadWarp::mousePressed(ofMouseEventArgs & args){
	if(setValue(args.x, args.y, true)){
		return true;
	}else{
		return false;
	}
}

bool ofxQuadWarp::mouseDragged(ofMouseEventArgs & args){
	for (int i = 0; i < 4; i++){
		if (bCircle[i]){
			ofRectangle check = ofRectangle(b.x,b.y,b.width,b.height);
			if (check.inside(args.x,args.y)){
				dstQuadPos[i]= ofVec3f((args.x - b.x)/width, (args.y - b.y)/height);
			}
		}
	}
	return false;
}

bool ofxQuadWarp::mouseReleased(ofMouseEventArgs & args){
	for (int i = 0; i < 4; i++){
		if (ofDistSquared(args.x, args.y,dstQuadPos[i]->x * width +b.x,dstQuadPos[i]->y * height + b.y)<MOUSE_DISTANCE * MOUSE_DISTANCE && (ofGetElapsedTimef() -lastMousePressTime)<1.0f ){
				switch (i){
				case 0:  dstQuadPos[0] = ofVec3f(0,0);                                        break;
				case 1:  dstQuadPos[1] = ofVec3f(content->getWidth(),0);                      break;
				case 2:  dstQuadPos[2] = ofVec3f(content->getWidth(),content->getHeight());   break;
				case 3:  dstQuadPos[3] = ofVec3f(0,content->getHeight());                     break;
				}
		}
	}
	lastMousePressTime = ofGetElapsedTimef();
	bGuiActive = false; //terry add
	return false;
}

void ofxQuadWarp::keyPressed(int key){
	
	switch (key)
	{
		case '7':
			bGuiActive = true;
			setValue(dstQuadPos[0]->x * width + b.x,dstQuadPos[0]->y * height + b.y,true);
			break;
		case '9':
			bGuiActive = true;
			setValue(dstQuadPos[1]->x * width + b.x,dstQuadPos[1]->y * height + b.y,true);
			break;
		case '1':
			bGuiActive = true;
			setValue(dstQuadPos[3]->x * width + b.x,dstQuadPos[3]->y * height + b.y,true);
			break;
		case '3':
			bGuiActive = true;
			setValue(dstQuadPos[2]->x * width + b.x,dstQuadPos[2]->y * height + b.y,true);
			break;
	}


	ofVec2f v2f;



	for (int i = 0; i < 4; i++){

		if (bCircle[i]){

			switch (key)
			{
				case '8':

					v2f.set(0,curMoveStep);
					dstQuadPos[i] -= v2f;
					bGuiActive = true;
					break;
				case '2':
					v2f.set(0,curMoveStep);
					dstQuadPos[i] += v2f;
					bGuiActive = true;
					break;
				case '4':

					v2f.set(curMoveStep,0);
					dstQuadPos[i] -= v2f;
					bGuiActive = true;
					break;
				case '6':
					v2f.set(curMoveStep,0);
					dstQuadPos[i] += v2f;
					bGuiActive = true;
					break;
			}
		}
	}


}

void ofxQuadWarp::keyReleased(int key){

}

bool ofxQuadWarp::setValue(float mx, float my, bool bCheck){
	if( !isGuiDrawing() ){
		bGuiActive = false;
		return false;
	}
	for (int i = 0; i < 4; i++){
		bCircle[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		if( bCheck ){
			//cout<<mx<<","<<dstQuadPos[i]->x * width + b.x<<endl;
			//cout<<my<<","<<dstQuadPos[i]->y * height + b.y<<endl;
			if(ofDistSquared(mx,my,dstQuadPos[i]->x * width + b.x,dstQuadPos[i]->y * height + b.y)<MOUSE_DISTANCE * MOUSE_DISTANCE){
				bGuiActive = true;
			}else{
				bGuiActive = false;
			}
		}
		if( bGuiActive ){
			bCircle[i] = !bCircle[i];
			return true;
		}
	}
	return false;
}

void ofxQuadWarp::InitQuadPos(float w,float h){
	b.width  = fixWidth;
	b.height = fixWidth * (h/w);// * ( content->getWidth()/initWidth) ;
	
	this->width = b.width/w;
	this->height = b.height/h;
	
	if(dstQuadPos == NULL){
		dstQuadPos = new ofParameter<ofVec3f>[4];
	}
	dstQuadPos[0].set("dstQuadPos0",ofVec3f(0,0));
	dstQuadPos[1].set("dstQuadPos1",ofVec3f(w,0));
	dstQuadPos[2].set("dstQuadPos2",ofVec3f(w,h));
	dstQuadPos[3].set("dstQuadPos3",ofVec3f(0,h));
	
	if(srcQuadPos == NULL){
		srcQuadPos = new ofPoint[4];
	}
	srcQuadPos[0] = ofVec3f(0,0);
	srcQuadPos[1] = ofVec3f(w,0);
	srcQuadPos[2] = ofVec3f(w,h);
	srcQuadPos[3] = ofVec3f(0,h);

	ofLogNotice("ofxQuadWarp")<<"InitQuadPos()=>"<<w<<","<<h;
}

void ofxQuadWarp::InitQuadPos(float w,float h,ofPoint &p1,ofPoint &p2,ofPoint &p3,ofPoint &p4){
	b.width  = fixWidth;
	b.height = fixWidth * (h/w);// * ( content->getWidth()/initWidth) ;
	
	this->width = b.width/w;
	this->height = b.height/h;
	
	if(dstQuadPos == NULL){
		dstQuadPos = new ofParameter<ofVec3f>[4];
	}
	dstQuadPos[0].set("dstQuadPos0",p1);
	dstQuadPos[1].set("dstQuadPos1",p2);
	dstQuadPos[2].set("dstQuadPos2",p3);
	dstQuadPos[3].set("dstQuadPos3",p4);
	
	if(srcQuadPos == NULL){
		srcQuadPos = new ofPoint[4];
	}
	srcQuadPos[0] = ofVec3f(0,0);
	srcQuadPos[1] = ofVec3f(w,0);
	srcQuadPos[2] = ofVec3f(w,h);
	srcQuadPos[3] = ofVec3f(0,h);

	ofLogNotice("ofxQuadWarp")<<"InitQuadPos()=>"<<w<<","<<h;
}

ofVec3f * ofxQuadWarp::getDstQuadPos(){
	if(_dstQuadPos == NULL){
		_dstQuadPos = new ofVec3f[4];
	}
	_dstQuadPos[0] = dstQuadPos[0];
	_dstQuadPos[1] = dstQuadPos[1];
	_dstQuadPos[2] = dstQuadPos[2];
	_dstQuadPos[3] = dstQuadPos[3];
	return _dstQuadPos; 
}

ofVec3f * ofxQuadWarp::getSrcQuadPos(){
	return srcQuadPos; 
}

void ofxQuadWarp::minimize(){
	quadWarpGroup.minimize();
}
void ofxQuadWarp::maximize(){
	quadWarpGroup.maximize();
}

void ofxQuadWarp::minimizeAll(){
	quadWarpGroup.minimizeAll();
}
void ofxQuadWarp::maximizeAll(){
	quadWarpGroup.maximizeAll();
}