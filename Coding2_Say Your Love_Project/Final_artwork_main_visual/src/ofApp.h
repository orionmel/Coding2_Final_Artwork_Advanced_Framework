#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ////////////////////////////😊😊😊 syphon 😊😊😊😊😊😊
    ofTexture tex;
    
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonServer individualTextureSyphonServer;
    
    ofxSyphonClient mClient;
    ////////////////////////////😊😊😊 syphon 😊😊😊😊😊😊
    
    
        // 创建新的mesh物体
        ofMesh mainMesh;
        ofEasyCam mainCam;

        int width, height;
        bool b_messyMesh, b_perlinMesh, b_drawWireFrame, b_marchMesh;
        float perlinRange, perlinHeight;
    
    
      /////❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️
    glm::vec2 make_point(float theta);
 
    vector<ofColor> base_color_list;
    float theta_seed, scale_seed;
    vector<pair<float, float>> param_list;
    vector<vector<glm::vec2>> log_list;
    vector<ofColor> color_list;
    vector<float> life_list;
    
    /////🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺
    void exit();
    
    void audioIn(float*input,int bufferSize,int nChannels);
    void audioOut(float*buffer,int bufferSize,int nChannels);
    
    int sampleRate;
    int bufferSize;

    vector<float>inputBuffer;
    
    /////🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺🎺
    
    ofImage img;
		
    //////////⚠️⚠️⚠️⚠️
    glm::vec2 make_number(float love);
};
