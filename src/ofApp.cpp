#include "ofApp.h"

ofVideoGrabber vidGrabber;
ofImage img;
int camWidth, camHeight;
unsigned char *late_imgs;
unsigned char *crr_pixels;
unsigned char *tmp_pixels;
int late_img_size, img_id, set_size, play_img_id;
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofEnableSmoothing();
    ofSetFrameRate(30);
    camWidth = 1920;
    camHeight = 1080;
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(camWidth, camHeight);
    set_size = 5;
    late_imgs = (unsigned char*)malloc(3 * vidGrabber.height * vidGrabber.width * set_size);
    crr_pixels = vidGrabber.getPixels();
    tmp_pixels = vidGrabber.getPixels();
    late_img_size = 3 * vidGrabber.height * vidGrabber.width;
    img_id = 0;
    play_img_id = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int h = 0; h < camHeight; h++) {
        for(int w = 0; w < camWidth; w++) {
            for (int c = 0; c < 3; c++) {
                tmp_pixels[h * camWidth * 3 + w * 3 + c] = crr_pixels[h * camWidth * 3 + w * 3 + c];
            }
        }
    }
    play_img_id = (++play_img_id) % set_size;
    
    if (img_id > play_img_id) {
        for(int h = 0; h < camHeight; h++) {
            for(int w = 0; w < camWidth; w++) {
                for (int c = 0; c < 3; c++) {
                    crr_pixels[h * camWidth * 3 + w * 3 + c] = (crr_pixels[h * camWidth * 3 + w * 3 + c] + late_imgs[ late_img_size * play_img_id + h * camWidth * 3 + w * 3 + c] ) / 2;
                }
            }
        }
    }
    
    img.setFromPixels(tmp_pixels, camWidth, camHeight, OF_IMAGE_COLOR);
    img.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (img_id > set_size) {
        return;
    }
    for(int h = 0; h < camHeight; h++) {
        for(int w = 0; w < camWidth; w++) {
            for (int c = 0; c < 3; c++) {
                late_imgs[ late_img_size * img_id + h * camWidth * 3 + w * 3 + c] = tmp_pixels[h * camWidth * 3 + w * 3 + c];
            }
        }
    }
    img_id++;
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
