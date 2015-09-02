#include "ofApp.h"

ofVideoGrabber vidGrabber;
ofImage img;
int camWidth, camHeight;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofEnableSmoothing();
    ofSetFrameRate(20);
    //キャプチャする画像のサイズを指定
    camWidth = 1920;
    camHeight = 1080;
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth, camHeight);
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0xFFFFFF);
    vidGrabber.draw(20,20);
    
    unsigned char *pixels = vidGrabber.getPixels();
    //色反転処理
    for(int i = 0; i < camHeight; i++){
        for(int j = 0; j < camWidth; j++){
            pixels[i*camWidth*3 + j*3] = 255-pixels[i*camWidth*3 + j*3];
            pixels[i*camWidth*3 + j*3+1] = 255-pixels[i*camWidth*3 + j*3+1];
            pixels[i*camWidth*3 + j*3+2] = 255-pixels[i*camWidth*3 + j*3+2];
        }
    }
    //処理後の画像の描画
    img.setFromPixels(pixels, camWidth, camHeight, OF_IMAGE_COLOR);
    img.draw(20, 240);
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
