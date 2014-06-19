#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetDataPathRoot("..\\..\\..\\..\\examples\\graphics\\imageLoaderExample\\bin\\data\\images\\");

	image0.loadImage(ofToDataPath( "bikers.jpg"));
	image1.loadImage(ofToDataPath( "tdf_1972_poster.jpg"));
	image2.loadImage(ofToDataPath( "gears.gif"));

	ofSetDataPathRoot("..\\..\\..\\..\\examples\\gui\\addGuiExample\\bin\\data\\");

	vector<string> sizeArray;
	sizeArray.push_back("320x240");
	sizeArray.push_back("640x480");
	sizeArray.push_back("200x480");

	testDropDownList.addListener(this,&ofApp::valueChange);

	ofxGuiSetFont("Microsoft YaHei",16);
	ofxGuiSetDefaultWidth(300);
	ofxGuiSetDefaultHeight(30);

	gui.setUseTTF(true);
	gui.setup("UI界面");
	gui.add(testContent0.setup("testContent0",image0));
	gui.add(testDropDownList.setup("测试DropDownList",sizeArray,0));
	gui.add(testContent1.setup("testContent1",image1));
	gui.add(testQuadWarp.setup("image测试QuadWarp",camera.getTextureReference()));
	gui.loadFromFile("settings.xml");

}

void ofApp::valueChange(int & value){
	vector<string> temp = ofSplitString(testDropDownList.getItemName(value),"x");
	if(camera.isInitialized()){
		camera.close();
	}
	camera.initGrabber(ofToInt(temp[0]),ofToInt(temp[1]));
	testQuadWarp.InitQuadPos(camera.getWidth(),camera.getHeight());
}

void ofApp::exit(){
	testDropDownList.removeListener(this,&ofApp::valueChange);
}
//--------------------------------------------------------------
void ofApp::update(){
	camera.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
	if (ofxGetCurrentContent()!=NULL){
		ofxGetCurrentContent()->draw(300,100);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == '1'){
		image0 = image1;
	}else if(key == '2'){
		image0 = image2;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

