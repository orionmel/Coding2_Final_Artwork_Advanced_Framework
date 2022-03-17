#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ////////////////////////////😊😊😊 syphon 😊😊😊😊😊😊
    mainOutputSyphonServer.setName("Screen Output");
    individualTextureSyphonServer.setName("Texture Output");

    mClient.setup();
    
    
    mClient.set("","Simple Server");
    
    tex.allocate(200, 100, GL_RGBA);
    
    ofSetFrameRate(60);
    ////////////////////////////😊😊😊 syphon 😊😊😊😊😊😊
    ///
    
    img.load("love_wall_test.jpg");
    
    /////🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺
    sampleRate = 48000;
    bufferSize = 512; //256 ,128,64
    
    inputBuffer.resize(bufferSize*1);
    
    cout <<(bufferSize*2/(float)sampleRate)*1000.f << endl;
    ofSoundStreamSetup(2,1,sampleRate,bufferSize,4);
    
    /////🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺
    ///
       
       //设置网格和初始渲染值的宽度和高度
       width = 100;
       height = 100;

       b_drawWireFrame = true;//圆点，或者线
    
        // 设置要用于我们的 perlinNoise 的初始值
           perlinRange =1.0;
           perlinHeight = 5.0;
       
       ofBackground(0); // 将窗口背景设置为黑色
       ofSetColor(255);
    
       //摄像机的角度
       mainCam.setPosition(0,0, 100); // 为我们的easyCam 3D查看器设置初始位置，从后面看
       mainCam.orbit(0,-80, -20);
       
    
//   ⚠️⚠️⚠️ ⚠️⚠️⚠️在这里，我们在网格内制作点 ⚠️⚠️⚠️ ⚠️⚠️⚠️
//           在宽度和高度上向网格添加一个顶点
//           我们使用这些 x 和 y 值来设置网格的 x 和 y 坐标，添加 z 值为零以完成每个顶点的 3d 位置
       
       for (int y = 0; y < height; y++){
           for (int x = 0; x<width; x++){
               mainMesh.addVertex( ofPoint(x - width /2 , y - height / 2 ,10)); // mesh index = x + y*width
               mainMesh.addColor(ofFloatColor(255,255,255));//主要的颜色
               
           }
       }
       
//    在这里，我们循环通过并将顶点连接在一起作为索引，以制作三角形行以形成线框网格
       
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
    
    /////❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️
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
    

    
    //////////////⚠️⚠️⚠️⚠️向前移动⚠️⚠️⚠️⚠️///////////////////////////////
     for (int y = height; y>0; y--){
         for (int  x= width; x>0; x--){
        oldPosition = mainMesh.getVertex( x + ( y  * width));
        newPosition = mainMesh.getVertex(x + ( (y - 1) * width) );
        oldPosition.z = newPosition.z;
        mainMesh.setVertex( x + ( y * width ), oldPosition); //更新顶点的位置
        newColor.setHsb(150 ,  255 - ofMap( newPosition.z, 0,  perlinHeight, 0 ,  255), 255);
        mainMesh.setColor(x + ( y * width ), newColor);

          }
     }
     for (int x=0; x<width; x++){
     newPosition = mainMesh.getVertex(x); // 获取此顶点的当前 x，y，z 位置
     newPosition.z = ofRandom(-1, 1); // 将其的 z 值设置为新的随机数
     mainMesh.setVertex(x, newPosition); // 使用新坐标更新顶点的位置
      }
                            
     
 

    /////❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️
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
    
    /////////////////8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️
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
    
    /////////////////8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️8⃣️❤️
    
    //////////⚠️⚠️⚠️⚠️
    
    ////////////🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕
    img.draw(0,0);
    ////////////🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕🆕
    
    /////🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺
    ofSetColor(255);
    for(int i = 0 ; i<bufferSize;i++){
        ofCircle(ofGetWidth()/2, ofGetHeight()/2,-(inputBuffer[i]*500) );
    }
    
    /////🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺
    ///
    
    ////////////////////////////😊😊😊 syphon 😊😊😊😊😊😊
    
    mClient.draw(50, 50);
    
    mainOutputSyphonServer.publishScreen();
    
    individualTextureSyphonServer.publishTexture(&tex);
    ////////////////////////////😊😊😊 syphon 😊😊😊😊😊😊
    
    /////❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️
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
    
    /////❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️
    
    ///////⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️
    glPointSize(3);
        mainCam.begin();

        if (b_drawWireFrame){
            //选择将网格绘制为线框
            mainMesh.drawWireframe();
        } else {
            //选择将网格绘制为点云
            mainMesh.drawVertices();
        }
        
        mainCam.end();
    
    ///////⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️
        

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
