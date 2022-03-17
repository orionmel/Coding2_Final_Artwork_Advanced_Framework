#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   
    ///
    
    ///////////////////////////////🧵🧵🧵🧵🧵🧵移动的线🧵🧵🧵🧵🧵🧵///////////////
    ofSetColor(255);
    ofEnableDepthTest();
 
    this->base_radius = 120;
    this->number_of_satellite = 2;
    for (int i = 0; i < 3; i++) {
 
        this->base_noise_seed_list.push_back(glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000)));
 
        auto s_location_list = vector<glm::vec3>();
        auto s_noise_seed_list = vector<glm::vec2>();
 
        for (int k = 0; k < this->number_of_satellite; k++) {
 
            s_location_list.push_back(glm::normalize(glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1))) * this->base_radius * 1.2);
            s_noise_seed_list.push_back(glm::vec2(ofRandom(1000), ofRandom(1000)));
 
        }
 
        this->satellite_location_list.push_back(s_location_list);
        this->satellite_noise_seed_list.push_back(s_noise_seed_list);
    }
 
    this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
    
    ///////////////////////🧵🧵🧵🧵🧵🧵移动的线🧵🧵🧵🧵🧵🧵///////////////
    ///
    ///////////////////////////////❤️❤️❤️❤️❤️///////////////////////////////
    ofSetFrameRate(60);
        ofSetWindowTitle("openFrameworks");
     
        
        ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
        ofNoFill();
     
        this->theta_seed = ofRandom(1000);
        this->scale_seed = ofRandom(1000);
     
        ofColor color;
        vector<int> hex_list = { 0xef476f, 0xffd166, 0x06d6a0, 0x118ab2, 0x073b4c };
        for (auto hex : hex_list) {
     
            color.setHex(hex);
            this->base_color_list.push_back(color);
        }
    ///////////////////////////////❤️❤️❤️❤️❤️///////////////////////////////
}

//--------------------------------------------------------------
void ofApp::update(){
    //////////////////////////////////🧵🧵🧵🧵🧵🧵移动的线🧵🧵🧵🧵🧵🧵///////////////
    for (int i = 0; i < this->base_noise_seed_list.size(); i++) {
     
            auto base_location = glm::vec3(
                ofMap(ofNoise(this->base_noise_seed_list[i].x, (ofGetFrameNum() + 0) * 0.005), 0, 1, -300, 300),
                ofMap(ofNoise(this->base_noise_seed_list[i].y, (ofGetFrameNum() + 0) * 0.005), 0, 1, -300, 300),
                ofMap(ofNoise(this->base_noise_seed_list[i].z, (ofGetFrameNum() + 0) * 0.005), 0, 1, -300, 300)
            );
     
            for (int k = 0; k < this->number_of_satellite; k++) {
     
                auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(this->satellite_noise_seed_list[i][k].x, (ofGetFrameNum() + 0) * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
                auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(this->satellite_noise_seed_list[i][k].y, (ofGetFrameNum() + 0) * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
                auto satellite_location = glm::vec4(this->satellite_location_list[i][k], 0) * rotation_y * rotation_x;
     
                auto next_base_location = glm::vec3(
                    ofMap(ofNoise(this->base_noise_seed_list[i].x, (ofGetFrameNum() + 1) * 0.005), 0, 1, -300, 300),
                    ofMap(ofNoise(this->base_noise_seed_list[i].y, (ofGetFrameNum() + 1) * 0.005), 0, 1, -300, 300),
                    ofMap(ofNoise(this->base_noise_seed_list[i].z, (ofGetFrameNum() + 1) * 0.005), 0, 1, -300, 300)
                );
     
                auto next_rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(this->satellite_noise_seed_list[i][k].x, (ofGetFrameNum() + 1) * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
                auto next_rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(this->satellite_noise_seed_list[i][k].y, (ofGetFrameNum() + 1) * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
                auto next_satellite_location = glm::vec4(this->satellite_location_list[i][k], 0) * rotation_y * rotation_x;
     
                auto location = base_location + satellite_location;
                auto next_location = next_base_location + next_satellite_location;
                auto distance = location - next_location;
     
                auto future = glm::vec3(satellite_location) + distance * 80;
                auto random_deg_1 = ofRandom(360);
                auto random_deg_2 = ofRandom(360);
                future += glm::vec3(
                    30 * cos(random_deg_1 * DEG_TO_RAD) * sin(random_deg_2 * DEG_TO_RAD),
                    30 * sin(random_deg_1 * DEG_TO_RAD) * sin(random_deg_2 * DEG_TO_RAD),
                    30 * cos(random_deg_2 * DEG_TO_RAD)
                );
                auto future_distance = future - satellite_location;
     
                this->frame.addVertex(location);
                this->face.addVertex(location);
     
                this->frame.addColor(ofColor(255));
                this->face.addColor(ofColor(255, 64));
     
                this->velocity_list.push_back(glm::normalize(future_distance) * glm::length(distance));
            }
        }
     
        for (int i = 0; i < this->frame.getNumVertices(); i++) {
     
            this->frame.setVertex(i, this->frame.getVertex(i) + this->velocity_list[i]);
            this->face.setVertex(i, this->face.getVertex(i) + this->velocity_list[i]);
        }
     
        for (int i = this->velocity_list.size() - 1; i >= 0; i--) {
     
            if (glm::length(this->frame.getVertex(i)) > 720) {
     
                this->velocity_list.erase(this->velocity_list.begin() + i);
                this->frame.removeVertex(i);
                this->face.removeVertex(i);
            }
        }
     
        this->frame.clearIndices();
        this->face.clearIndices();
        for (int i = 0; i < this->frame.getNumVertices(); i++) {
     
            vector<int> near_index_list;
            for (int k = i + 1; k < this->frame.getNumVertices(); k++) {
     
                auto distance = glm::distance(this->frame.getVertex(i), this->frame.getVertex(k));
                if (distance < 50) {
     
                    this->frame.addIndex(i); this->frame.addIndex(k);
                }
     
                if (distance < 80) {
     
                    near_index_list.push_back(k);
                }
            }
     
            if (near_index_list.size() > 3) {
            
                for (int k = 0; k < near_index_list.size() - 2; k++) {
     
                    this->face.addIndex(i);
                    this->face.addIndex(near_index_list[k]);
                    this->face.addIndex(near_index_list[k + 1]);
                }
            }
        }

    ///////////////////////🧵🧵🧵🧵🧵🧵移动的线🧵🧵🧵🧵🧵🧵///////////////
    ///
    ///////////////////////////////❤️❤️❤️❤️❤️///////////////////////////////////
    ofBackground(150,0,ofRandom(10,30));
    while (this->param_list.size() < 100) {
     
            auto deg_pair = make_pair(ofRandom(360), ofRandom(3, 20));
            this->param_list.push_back(deg_pair);
            vector<glm::vec2> log;
            this->log_list.push_back(log);
            this->color_list.push_back(this->base_color_list[(int)ofRandom(this->base_color_list.size())]);
            this->life_list.push_back(ofRandom(60, 180));
        }
     
        for (int i = this->param_list.size() - 1; i >= 0; i--) {
     
            this->life_list[i] -= 1;
            if (this->life_list[i] < 0) {
     
                this->param_list.erase(this->param_list.begin() + i);
                this->log_list.erase(this->log_list.begin() + i);
                this->color_list.erase(this->color_list.begin() + i);
                this->life_list.erase(this->life_list.begin() + i);
     
                continue;
            }
     
            auto noise_location = this->make_point(this->param_list[i].first);
            auto u_param = ofMap(ofNoise(glm::vec4(noise_location * 0.003, this->param_list[i].second * 0.03, this->theta_seed + ofGetFrameNum() * 0.003)), 0, 1, -0.5, 0.5);
            auto v_param = ofMap(ofNoise(glm::vec4(noise_location * 0.003, this->param_list[i].second * 0.03, this->scale_seed + ofGetFrameNum() * 0.008)), 0, 1, 3, 20);
     
            this->param_list[i].first += u_param;
            this->param_list[i].second = v_param;
     
            this->log_list[i].push_back(this->make_point(this->param_list[i].first) * this->param_list[i].second);
            while (this->log_list[i].size() > 100) {
     
                this->log_list[i].erase(this->log_list[i].begin());
            }
        }
    ///////////////////////////////❤️❤️❤️❤️❤️///////////////////////////////
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //////////////🧵🧵///////////////////////🧵🧵🧵🧵🧵🧵移动的线🧵🧵🧵🧵🧵🧵///////////////
    
    this->cam.begin();
     
        for (int i = 0; i < this->frame.getNumVertices(); i++) {
     
            ofDrawSphere(this->frame.getVertex(i), 2);
        }
     
        this->frame.drawWireframe();
        this->face.draw();
     
        this->cam.end();
    
    //////////////🧵🧵///////////////////////🧵🧵🧵🧵🧵🧵移动的线🧵🧵🧵🧵🧵🧵///////////////
    ///
   
    ///
    ///////////////////////////////❤️❤️❤️❤️❤️///////////////////////////////

    ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
     
        for (int i = 0; i < this->param_list.size(); i++) {
     
            ofSetColor(this->color_list[i]);
            
     
            if (this->life_list[i] > 60) {
     
                ofSetLineWidth(1.5);
            }
            else {
     
                ofSetLineWidth(ofMap(this->life_list[i], 0, 60, 0, 1.5));
            }
     
            ofBeginShape();
            ofVertices(this->log_list[i]);
            ofEndShape();
        }
    ///////////////////////////////❤️❤️❤️❤️❤️///////////////////////////////
    ///
    
}

//--------------------------------------------------------------
///////////////////////////////❤️❤️❤️❤️❤️///////////////////////////////
// Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {
 
    float x = 16 * (pow(sin(theta), 3));
    float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
    return glm::vec2(x, -y);
}
///////////////////////////////❤️❤️❤️❤️❤️///////////////////////////////

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
