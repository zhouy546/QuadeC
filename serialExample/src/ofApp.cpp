#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	a=0;
	 gravity.set(0, 0);
	ofSetVerticalSync(true);
	
	bSendSerialMessage = false;
	ofBackground(255);	
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	font.loadFont("DIN.otf", 64);
	
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 9600;
	//serial.setup(0, baud); //open the first device
	serial.setup("COM8", baud); // windows example
	//serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 3);
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < 1; i++) {
		//intensity input~~~~~~~~~~~~~~~~~`
        Particle particle(10);
        particleList.push_back(particle);
        
    }
    
    for (int i = 0; i < particleList.size(); i++) {
        particleList[i].resetForces();
        particleList[i].applyForce(gravity);
        particleList[i].update();
    }
    
    while (particleList.size() > 1000) {
        particleList.erase(particleList.begin());
    }
	if (bSendSerialMessage){
		
		// (1) write the letter "a" to serial:
		serial.writeByte('a');
		
		// (2) read
		// now we try to read 3 bytes
		// since we might not get them all the time 3 - but sometimes 0, 6, or something else,
		// we will try to read three bytes, as much as we can
		// otherwise, we may have a "lag" if we don't read fast enough
		// or just read three every time. now, we will be sure to 
		// read as much as we can in groups of three...
		
		nTimesRead = 0;
		nBytesRead = 0;
		int nRead  = 0;  // a temp variable to keep count per read
		
		unsigned char bytesReturned[3];
		
		memset(bytesReadString, 0, 4);
		memset(bytesReturned, 0, 3);
		
		while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
			nTimesRead++;	
			nBytesRead = nRead;
		};
		
		memcpy(bytesReadString, bytesReturned, 3);
		
		bSendSerialMessage = false;
		readTime = ofGetElapsedTimef();
	}
	a++;
	if(a>20){
	bSendSerialMessage=true;
	a=0;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	

	if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
		ofSetColor(0);
	} else {
		ofSetColor(220);
	}
	string msg;
	//msg += "click to test serial:\n";
	//msg += "nBytes read " + ofToString(nBytesRead) + "\n";
	//msg += "nTimes read " + ofToString(nTimesRead) + "\n";
	msg +=  ofToString(bytesReadString);
	//msg += "(at time " + ofToString(readTime, 3) + ")";
	font.drawString(msg, 50, 100);
	float size= ofToFloat(msg);
	ofSetColor(255,0,0);
	if(size<35){
	size =35;
	}
	float Psize=ofMap(size,35,100,5,100);
	for (int i = 0; i < particleList.size(); i++) {
        particleList[i].draw(Psize);
    }

	//ofCircle(ofGetWidth()/2,ofGetHeight()/2,size);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	bSendSerialMessage = true;
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
