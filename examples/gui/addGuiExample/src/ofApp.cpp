#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetDataPathRoot("..\\..\\..\\..\\examples\\graphics\\imageLoaderExample\\bin\\data\\images\\");

	image0.loadImage(ofToDataPath( "bikers.jpg"));
	image1.loadImage(ofToDataPath( "tdf_1972_poster.jpg"));
	image2.loadImage(ofToDataPath( "gears.gif"));

	vector<string> sizeArray;
	sizeArray.push_back("你好");
	sizeArray.push_back("测试");
	sizeArray.push_back("欢迎");

	ofxGuiSetFont("Microsoft YaHei",16);
	ofxGuiSetDefaultWidth(300);
	ofxGuiSetDefaultHeight(30);
	gui.setUseTTF(true);
	gui.setup("UI界面");
	gui.add(testToggle.setup("测试",false));
	gui.add(testDropDownList.setup("测试DropDownList",sizeArray,2));
	gui.add(testContent0.setup("image测试0",image0));
	//gui.add(testContent1.setup("image测试1",image1));
	//gui.add(testContent2.setup("image测试2",image2));
	gui.add(testQuadWarp.setup("image测试QuadWarp",image0,image0.getWidth(),image0.getHeight()));

	testDropDownList.addListener(this,&ofApp::valueChange);
}

void ofApp::exit(){
	testDropDownList.removeListener(this,&ofApp::valueChange);
}
//--------------------------------------------------------------
void ofApp::update(){

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

void ofApp::valueChange(int & value){
	string name = ofUtf8ToLocale(testDropDownList.getItemName(value));
	cout<<name<<endl;
}

