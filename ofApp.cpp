
#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	//ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofNoFill();

	for(float radius = 50; radius <= 200; radius += 50){
		for (float deg = 0; deg < 360; deg += 1) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			this->base_location_list.push_back(location);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->log_list.clear();

	for (int i = 0; i < this->base_location_list.size(); i++) {

		vector<glm::vec3> log;
		log.push_back(glm::vec3(this->base_location_list[i], 0));
		this->log_list.push_back(log);
	}

	int step = 2;
	for (int i = 0; i < this->log_list.size(); i++) {

		while (this->log_list[i].size() < 50) {

			auto deg = ofMap(ofNoise(glm::vec4(this->log_list[i].back() * 0.015, (ofGetFrameNum() + this->log_list[i].size()) * 0.002)), 0, 1, -360, 360);
			auto next = this->log_list[i].back() + glm::vec2(step * cos(deg * DEG_TO_RAD), step * sin(deg * DEG_TO_RAD));
			this->log_list[i].push_back(next);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofSetColor(39);
	for (int i = 0; i < this->log_list.size(); i++) {

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}