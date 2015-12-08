#include "ofApp.h"
#include "RESTapi.h"
#include "Base64Codec.h"

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <json/json.h>

using namespace std;

void ofApp::setup(){
    ofBackground(0);
    
    int camWidth = 320;
    int camHeight = 240;
    
    for(int i = 0; i < 50; i ++) {
        biu.push_back(ofPoint(0,0));
    }
    
    ofSetVerticalSync(true);
    
    cam.setDeviceID(0);
    cam.initGrabber(camWidth, camHeight);
    
    happyEmo[0] = "(· ▽ ·)";
    happyEmo[1] = "o(*≧▽≦)ツ";
    
    sadEmo[0] = "_(:3 」∠)_";
    sadEmo[1] = "( ＴAＴ)";
    
    angryEmo[0] = ",,-‸-,,";
    angryEmo[1] = "(＞_＜)";
    
    surprisedEmo[0] = "(*ﾟﾛﾟ)";
    surprisedEmo[1] = "L(・o・)」";
    
    calmEmo[0] = "[´・ω・`]";
    
    confusedEmo[0] = "(‘◇’)?";
    confusedEmo[1] = "(0_0)?";
    
    string cmd = "osascript /Users/zhoulei/Desktop/open.scpt";
    system(cmd.c_str());
}

void ofApp::getInfo() {
    Json::Value response;
    const string api_addr_base = "http://rekognition.com/func/api/?";
    map<string, string> query_config;
    
    query_config["api_key"] = "DhemOTvOt207B6xA";
    query_config["api_secret"] = "gWln6CsS9c39jLNM";
    query_config["jobs"] = "face_emotion";
    query_config["uploaded_file"] = "/Users/zhoulei/Desktop/1.jpg";
    
    std::ifstream t("/Users/zhoulei/Desktop/1.jpg", ios::binary);
    std::string buff_str((std::istreambuf_iterator<char>(t)),
                         std::istreambuf_iterator<char>());
    
    rekognition_api::Base64Codec base64_codec;
    string encoded;
    base64_codec.Encode(buff_str, &encoded);
    query_config["base64"] = encoded;
    
    if (!rekognition_api::APICall(api_addr_base, query_config, &response)) {
        cerr << "API call failure!" << endl;
        return -1;
    }
    
    const Json::Value face_detection = response["face_detection"];
    for (unsigned int i = 0; i < face_detection.size(); ++i) {
        happy = face_detection[i]["emotion"]["happy"].asFloat();
        surprised = face_detection[i]["emotion"]["surprised"].asFloat();
        sad = face_detection[i]["emotion"]["sad"].asFloat();
        angry = face_detection[i]["emotion"]["angry"].asFloat();
        confused = face_detection[i]["emotion"]["confused"].asFloat();
        calm = face_detection[i]["emotion"]["calm"].asFloat();
    }
}

void ofApp::update(){
    x = (float)ofGetWidth() / 790.0f;
    y = (float)ofGetHeight()/600.0f;
    
    cout<<x<<' '<<y<<endl;
    
    cam.update();
    
    img.loadImage("/Users/zhoulei/Desktop/1.jpg");
    
    for(int i = 0; i < biu.size(); i ++) {
        biu[i].x = ofRandom(0, ofGetWidth());
        biu[i].y = ofRandom(0, ofGetHeight());
    }
}

void ofApp::draw(){
    ofSetColor(254, 67, 101, 150);
    for(int i = 0; i< biu.size(); i++) {
        ofCircle(biu[i].x, biu[i].y, 3);
    }
    
    ofSetColor(252,157, 154, 200);
    
    cam.draw(50 * x, 100 * y, 320 * x, 240 * y);
    
    ofSetColor(254, 67, 101, 200);
    img.draw(420 * x, 100 * y, 320 * x, 240 * y);
    
    ofSetColor(254, 67, 101);
    font.loadFont("1.ttc", 30 * y);
    font.drawString("Emoooo(表情输入法)", ofGetWidth()/2 - font.stringWidth("Emoooo(表情输入法)")/2, 60 * y);
    font.loadFont("1.ttc", 15 * y);
    font.drawString("快乐(Happy) : " + ofToString(happy), 210 * x - font.stringWidth("快乐(Happy) : " + ofToString(happy))/2, 400 * y);
    font.drawString("悲伤(Sad) : " + ofToString(sad), 210 * x - font.stringWidth("悲伤(Sad) : " + ofToString(sad))/2, 430 * y);
    font.drawString("平静(Calm) : " + ofToString(calm), 210 * x - font.stringWidth("平静(Calm) : " + ofToString(calm))/2, 460 * y);
    font.drawString("困惑(Confused) : " + ofToString(confused), 210 * x - font.stringWidth("困惑(Confused) : " + ofToString(confused))/2, 490 * y);
    font.drawString("愤怒(Angry) : " + ofToString(angry), 210 * x - font.stringWidth("愤怒(Angry) : " + ofToString(angry))/2, 520 * y);
    font.drawString("惊讶(Surprised) : " + ofToString(surprised), 210 * x - font.stringWidth("惊讶(Surprised) : " + ofToString(surprised))/2, 550 * y);
    
    
    font.loadFont("1.ttc", 50 * y);
    if(happy > 0.7) {
        font.drawString(happyEmo[1], 580 * x - font.stringWidth(happyEmo[1])/2, 490 * y);
        
    } else if (happy > 0.3) {
        font.drawString(happyEmo[0], 580 * x - font.stringWidth(happyEmo[0])/2, 490 * y);
    }
    
    if(sad > 0.7) {
        font.drawString(sadEmo[1], 580 * x - font.stringWidth(sadEmo[1])/2, 490 * y);
    } else if (sad > 0.3) {
        font.drawString(sadEmo[0], 580 * x - font.stringWidth(sadEmo[0])/2, 490 * y);
    }
    
    if(surprised > 0.7) {
        font.drawString(surprisedEmo[1], 580 * x - font.stringWidth(surprisedEmo[1])/2, 490 * y);
    } else if (surprised > 0.3) {
        font.drawString(surprisedEmo[0], 580 * x - font.stringWidth(surprisedEmo[0])/2, 490 * y);
    }
    
    if(calm > 0.3) {
        font.drawString(calmEmo[0], 580 * x - font.stringWidth(calmEmo[0])/2, 490 * y);
    }
    
    if(confused > 0.7) {
        font.drawString(confusedEmo[1], 580 * x - font.stringWidth(confusedEmo[1])/2, 490 * y);
    } else if (confused > 0.3) {
        font.drawString(confusedEmo[0], 580 * x - font.stringWidth(confusedEmo[0])/2, 490 * y);
    }
    
    if(angry > 0.7) {
        font.drawString(angryEmo[1], 580 * x - font.stringWidth(angryEmo[1])/2, 490 * y);
    } else if (angry > 0.3) {
        font.drawString(angryEmo[0], 580 * x - font.stringWidth(angryEmo[0])/2, 490 * y);
    }
}

void ofApp::keyPressed(int key){
    if(key == ' ') {
        ofImage now;
        now.setFromPixels(cam.getPixelsRef());
        now.resize(160, 120);
        now.saveImage("/Users/zhoulei/Desktop/1.jpg");
        
        getInfo();
        if(happy > 0.7) {
            string cmd = "osascript /Users/zhoulei/Desktop/happy0.scpt";
            system(cmd.c_str());
        } else {
            if (happy > 0.3) {
                string cmd = "osascript /Users/zhoulei/Desktop/happy1.scpt";
                system(cmd.c_str());
            }
        }
        
        if(surprised > 0.7) {
            string cmd = "osascript /Users/zhoulei/Desktop/surprised0.scpt";
            system(cmd.c_str());
        } else {
            if (surprised > 0.3) {
                string cmd = "osascript /Users/zhoulei/Desktop/surprised1.scpt";
                system(cmd.c_str());
            }
        }
    }
}