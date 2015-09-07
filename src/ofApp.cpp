#include "ofApp.h"

ofVideoGrabber vidGrabber;
ofImage img;
int camWidth, camHeight;
unsigned char *late_imgs;
unsigned char *crr_pixels;
unsigned char *tmp_pixels;
unsigned char *back_pixels;
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
    back_pixels = (unsigned char*)malloc(3 * vidGrabber.height * vidGrabber.width);
    img_id = 0;
    play_img_id = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < late_img_size; i ++) {
        tmp_pixels[i] = crr_pixels[i];
    }
//    play_img_id = (++play_img_id) % set_size;
//    if (img_id > play_img_id) {
//        for (int i = 0; i < late_img_size; i++) {
//            crr_pixels[i] = late_imgs[late_img_size * play_img_id + i];
//        }
//    }
    int diff;
    int diff_thre = 20;
    for (int i = 0; i < late_img_size; i+=3) {
        diff = 0;
        for(int c = 0; c < 3; c++) {
            diff += abs(tmp_pixels[i + c] - back_pixels[i + c]);
        }
        for(int c = 0; c < 3; c++) {
            if (diff < diff_thre) {
                crr_pixels[i + c] = 0;
            } else {
                crr_pixels[i + c] = tmp_pixels[i + c];
            }
        }
    }
    img.setFromPixels(crr_pixels, camWidth, camHeight, OF_IMAGE_COLOR);
    img.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (img_id > set_size) {
        return;
    }
    int diff_thre = 10;
    int diff = 0;
    for(int i = 0; i < late_img_size; i += 3) {
        diff = 0;
        for(int c = 0; c < 3; c++) {
            diff += tmp_pixels[i + c] - back_pixels[i + c];
        }
        for(int c = 0; c < 3; c++) {
            if (diff < diff_thre) {
                late_imgs[late_img_size * img_id + i + c] = tmp_pixels[i + c];
            } else {
                late_imgs[late_img_size * img_id + i + c] = 0;
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
    for(int i = 0; i < late_img_size; i ++) {
        back_pixels[i] = tmp_pixels[i];
    }
    std::cout << "back";
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
