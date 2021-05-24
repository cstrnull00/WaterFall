#pragma once

#include "ofMain.h"
#include <vector>
#include <utility>
#include <cmath>
#define EPSILON 5
#define SPEED 5

using namespace std;

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
    
    /* WaterFall-related member variables Regions */

    // flag variables
    int draw_flag;
	int water_draw_flag;
    int load_flag;
	/*****************************/
    
    // Line segment and dot related variables
    int num_of_line, num_of_dot;
    float dot_diameter;

	int route_index;
	
    /* WaterFall-related member functions */
    
    void processOpenFileSelection(ofFileDialogResult openFileResult);

	/******************************/
	typedef struct {
		int x1;
		int y1;
		int selected;
	}Dot;
	Dot *dot_array;
	int selected_num = 0;

	typedef struct {
		int x1;
		int y1;
		int x2;
		int y2;
	}Line;
	Line *line_array;
	/*******************************/

	class Water {
	public:
		vector<pair<float, float>> route;
		int meet_line = 0;
	
		void calculateRoute(int meet_line, pair<float, float> before, float inclination);
		pair<float, int> incline(pair<float, float> curr, int num_of_line, Line *line_array);
		void initializeWaterLines(int Sx, int Sy); // 2nd week portion.
	};

	Water* water;
};