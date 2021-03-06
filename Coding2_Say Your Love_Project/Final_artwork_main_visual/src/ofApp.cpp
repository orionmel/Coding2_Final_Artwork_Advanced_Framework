#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ////////////////////////////ððð syphon ðððððð
    mainOutputSyphonServer.setName("Screen Output");
    individualTextureSyphonServer.setName("Texture Output");

    mClient.setup();
    
    
    mClient.set("","Simple Server");
    
    tex.allocate(200, 100, GL_RGBA);
    
    ofSetFrameRate(60);
    ////////////////////////////ððð syphon ðððððð
    ///
    
    img.load("love_wall_test.jpg");
    
    /////ðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðº
    sampleRate = 48000;
    bufferSize = 512; //256 ,128,64
    
    inputBuffer.resize(bufferSize*1);
    
    cout <<(bufferSize*2/(float)sampleRate)*1000.f << endl;
    ofSoundStreamSetup(2,1,sampleRate,bufferSize,4);
    
    /////ðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðº
    ///
       
       //è®¾ç½®ç½æ ¼ååå§æ¸²æå¼çå®½åº¦åé«åº¦
       width = 100;
       height = 100;

       b_drawWireFrame = true;//åç¹ï¼æèçº¿
    
        // è®¾ç½®è¦ç¨äºæä»¬ç perlinNoise çåå§å¼
           perlinRange =1.0;
           perlinHeight = 5.0;
       
       ofBackground(0); // å°çªå£èæ¯è®¾ç½®ä¸ºé»è²
       ofSetColor(255);
    
       //æåæºçè§åº¦
       mainCam.setPosition(0,0, 100); // ä¸ºæä»¬çeasyCam 3Dæ¥çå¨è®¾ç½®åå§ä½ç½®ï¼ä»åé¢ç
       mainCam.orbit(0,-80, -20);
       
    
//   â ï¸â ï¸â ï¸ â ï¸â ï¸â ï¸å¨è¿éï¼æä»¬å¨ç½æ ¼åå¶ä½ç¹ â ï¸â ï¸â ï¸ â ï¸â ï¸â ï¸
//           å¨å®½åº¦åé«åº¦ä¸åç½æ ¼æ·»å ä¸ä¸ªé¡¶ç¹
//           æä»¬ä½¿ç¨è¿äº x å y å¼æ¥è®¾ç½®ç½æ ¼ç x å y åæ ï¼æ·»å  z å¼ä¸ºé¶ä»¥å®ææ¯ä¸ªé¡¶ç¹ç 3d ä½ç½®
       
       for (int y = 0; y < height; y++){
           for (int x = 0; x<width; x++){
               mainMesh.addVertex( ofPoint(x - width /2 , y - height / 2 ,10)); // mesh index = x + y*width
               mainMesh.addColor(ofFloatColor(255,255,255));//ä¸»è¦çé¢è²
               
           }
       }
       
//    å¨è¿éï¼æä»¬å¾ªç¯éè¿å¹¶å°é¡¶ç¹è¿æ¥å¨ä¸èµ·ä½ä¸ºç´¢å¼ï¼ä»¥å¶ä½ä¸è§å½¢è¡ä»¥å½¢æçº¿æ¡ç½æ ¼
       
       for (int y = 0; y<height-1; y++){
           for (int x=0; x<width-1; x++){
               mainMesh.addIndex(x+y*width);                // 0
               mainMesh.addIndex((x+1)+y*width);            // 1
               mainMesh.addIndex(x+(y+1)*width);            // 10
               
               mainMesh.addIndex((x+1)+y*width);            // 1
               mainMesh.addIndex((x+1)+(y+1)*width);        // 11
               mainMesh.addIndex(x+(y+1)*width);            // 10
           }
       }
    
    /////â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸
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


}

//--------------------------------------------------------------
void ofApp::update(){
    ofColor newColor;
    ofVec3f newPosition, oldPosition;
    

    
    //////////////â ï¸â ï¸â ï¸â ï¸ååç§»å¨â ï¸â ï¸â ï¸â ï¸///////////////////////////////
     for (int y = height; y>0; y--){
         for (int  x= width; x>0; x--){
        oldPosition = mainMesh.getVertex( x + ( y  * width));
        newPosition = mainMesh.getVertex(x + ( (y - 1) * width) );
        oldPosition.z = newPosition.z;
        mainMesh.setVertex( x + ( y * width ), oldPosition); //æ´æ°é¡¶ç¹çä½ç½®
        newColor.setHsb(150 ,  255 - ofMap( newPosition.z, 0,  perlinHeight, 0 ,  255), 255);
        mainMesh.setColor(x + ( y * width ), newColor);

          }
     }
     for (int x=0; x<width; x++){
     newPosition = mainMesh.getVertex(x); // è·åæ­¤é¡¶ç¹çå½å xï¼yï¼z ä½ç½®
     newPosition.z = ofRandom(-1, 1); // å°å¶ç z å¼è®¾ç½®ä¸ºæ°çéæºæ°
     mainMesh.setVertex(x, newPosition); // ä½¿ç¨æ°åæ æ´æ°é¡¶ç¹çä½ç½®
      }
                            
     
 

    /////â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸
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
                
          this->param_list[i].second = v_param ;
            
            
     
            this->log_list[i].push_back(this->make_point(this->param_list[i].first) * this->param_list[i].second);
            while (this->log_list[i].size() > 100) {
     
                this->log_list[i].erase(this->log_list[i].begin());
            }
        }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /////////////////8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸
    for (int i = 0; i < 50; i++) {
     
            auto location = glm::vec2(ofRandom(ofGetWidth()), ((int)ofRandom(ofGetHeight() + ofGetFrameNum()) % (ofGetHeight() + 100) - 50));
            auto scale = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 1, 3);
     
            ofPushMatrix();
            ofTranslate(location);
            ofRotate(ofRandom(360));
        ofSetColor(255,ofRandom(100,200),ofRandom(100,150));
     
            ofBeginShape();
            for (auto deg = 0; deg < 360; deg += 1) {
     
                ofVertex(this->make_number(deg * DEG_TO_RAD) * scale);
            }
            ofEndShape(true);
     
            ofPopMatrix();
        }
    
    /////////////////8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸8â£ï¸â¤ï¸
    
    //////////â ï¸â ï¸â ï¸â ï¸
    
    ////////////ððððððððððððððððððððð
    img.draw(0,0);
    ////////////ððððððððððððððððððððð
    
    /////ðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðº
    ofSetColor(255);
    for(int i = 0 ; i<bufferSize;i++){
        ofCircle(ofGetWidth()/2, ofGetHeight()/2,-(inputBuffer[i]*500) );
    }
    
    /////ðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðºðº
    ///
    
    ////////////////////////////ððð syphon ðððððð
    
    mClient.draw(50, 50);
    
    mainOutputSyphonServer.publishScreen();
    
    individualTextureSyphonServer.publishTexture(&tex);
    ////////////////////////////ððð syphon ðððððð
    
    /////â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸
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
    
    /////â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸â¤ï¸
    
    ///////â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸
    glPointSize(3);
        mainCam.begin();

        if (b_drawWireFrame){
            //éæ©å°ç½æ ¼ç»å¶ä¸ºçº¿æ¡
            mainMesh.drawWireframe();
        } else {
            //éæ©å°ç½æ ¼ç»å¶ä¸ºç¹äº
            mainMesh.drawVertices();
        }
        
        mainCam.end();
    
    ///////â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸â ï¸
        

}

glm::vec2 ofApp::make_point(float theta) {
 
    float x = 16 * (pow(sin(theta), 3));
    float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
    return glm::vec2(x, -y);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){


}
void ofApp::audioIn(float*input,int bufferSize,int nChannels){
    for(int i = 0;i<bufferSize;i++){
        inputBuffer[i*nChannels+0]=input[i];
    }
    
}
void ofApp::audioOut(float*buffer,int bufferSize,int nChannels){
    for(int i = 0;i<bufferSize;i++){
        float inputSample;
        float currentSample;
        
        inputSample = inputBuffer[i];
        
        currentSample = inputSample;
        
        buffer[i*nChannels + 0]= currentSample;
        buffer[i*nChannels + 1] = currentSample;
    }
}


glm::vec2 ofApp::make_number(float love) {
 
    float x = 16 * (pow(sin(love), 3));
    float y = 13 * cos(love) - 5 * cos(2 * love) - 2 * cos(3 * love) - cos(4 * love);
    return glm::vec2(x, -y);
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
void ofApp:: exit(){
    ofSoundStreamClose();
}
