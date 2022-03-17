#pragma once

#include "ofMain.h"

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
    
    glm::vec2 make_point(float theta);
     
        vector<ofColor> base_color_list;
        float theta_seed, scale_seed;
        vector<pair<float, float>> param_list;
        vector<vector<glm::vec2>> log_list;
        vector<ofColor> color_list;
        vector<float> life_list;
		
    
    ///////////////////////🧵🧵🧵🧵🧵🧵移动的线🧵🧵🧵🧵🧵🧵///////////////
    ofEasyCam cam;
 
    int base_radius;
    int number_of_satellite;
 
    vector<glm::vec3> base_noise_seed_list;
    vector<vector<glm::vec3>> satellite_location_list;
    vector<vector<glm::vec2>> satellite_noise_seed_list;
    vector<glm::vec3> location_list;
    vector<glm::vec3> velocity_list;
 
    ofMesh face, frame;
    ///////////////////////🧵🧵🧵🧵🧵🧵移动的线🧵🧵🧵🧵🧵🧵///////////////
    
 
};
