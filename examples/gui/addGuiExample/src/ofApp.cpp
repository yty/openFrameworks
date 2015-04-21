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

	ofxGuiSetFont("simhei",16);
	ofxGuiSetDefaultWidth(300);
	ofxGuiSetDefaultHeight(30);

	gui.setUseTTF(true);
	gui.setup(ofLocaleToUtf8("UI界面"));
	gui.add(testContent0.setup("testContent0",image0));
	gui.add(testDropDownList.setup(ofLocaleToUtf8("测试DropDownList"),sizeArray,0));

	vector<string> temp = ofSplitString(testDropDownList.getItemName(testDropDownList.getCurItemId()),"x");
	camera.setup(ofToInt(temp[0]),ofToInt(temp[1]));

	gui.add(testQuadWarp.setup(ofLocaleToUtf8("image测试QuadWarp"),camera.getTextureReference()));

	testDropDownList.addListener(this,&ofApp::valueChange);//换了位置

	
	gui.loadFromFile("settings.xml");

	string fileName = ofLocaleToUtf8(ofToDataPath("test中文.xml",true));

	//guiEx.setUseTTF(true);
	guiEx.setup(ofLocaleToUtf8("test中文"),fileName,512,10);
	guiEx.add(doShader.setup(ofLocaleToUtf8("使用shader"),false));
	guiEx.add(aperture.setup(ofLocaleToUtf8("光圈"),180.0,0.0,180.0));

	guiEx.add(testChinaToggle.setup(ofLocaleToUtf8("中文"),true));
	testGroup.setup("testGroup");
	testGroup1.setup("testGroup1");
	testGroup1.add(testToggle.setup(ofLocaleToUtf8("test中文"),true));
	testGroup1.add(testFloatSlider.setup(ofLocaleToUtf8("test滑条"),180,0,180));
	testGroup.add(&testGroup1);
	//testGroup.add(testContent1.setup("testContent1",image1));
	guiEx.add(&testGroup);

	guiEx.loadFromFile(fileName);

}

void ofApp::valueChange(int & value){
	vector<string> temp = ofSplitString(testDropDownList.getItemName(value),"x");
	if(camera.isInitialized()){
		camera.close();
	}
	camera.initGrabber(ofToInt(temp[0]),ofToInt(temp[1]));
	testQuadWarp.InitQuadPos(camera.getWidth(),camera.getHeight());
	cout<<"valueChange"<<endl;
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
	guiEx.draw();
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

