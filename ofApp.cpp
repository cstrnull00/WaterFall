#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second
    
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255,255,255);
    ofSetLineWidth(4);
    
    draw_flag = 0;
    load_flag = 0;
    water_draw_flag = 0;
    dot_diameter = 20.0f;

    route_index = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

    if (water_draw_flag) {
        water->calculateRoute(water->incline(water->route[route_index], num_of_line, line_array).second, water->route[route_index], water->incline(water->route[route_index], num_of_line, line_array).first);
        route_index++;
    }
    if (route_index > 0 && water->route[route_index].second > 728)
        water_draw_flag = 0;
}

//--------------------------------------------------------------
void ofApp::draw(){
	int i, j;
	ofColor myRed = ofColor::red;
	ofColor myBlack = ofColor::black;
    ofColor myBlue = ofColor::blue;
    ofSetColor(127,23,31);  // Set the drawing color to brown
    
    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (0, 0), 1024 wide x 40 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (0, 728), 1024 wide x 40 high
    ofSetLineWidth(5);
    
    
    ofSetLineWidth(5);
    if( draw_flag ){
        
        /* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
         Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
         */

		/*******************/
		for (i = 0; i < num_of_line; i++) {
			ofSetLineWidth(5);
			ofDrawLine(line_array[i].x1, line_array[i].y1, line_array[i].x2, line_array[i].y2);
		}

		for (j = 0; j < num_of_dot; j++) {
			if (dot_array[j].selected == 1) {
				ofSetColor(myRed);
				ofDrawCircle(dot_array[j].x1, dot_array[j].y1, 10);
			}
			else {
				ofSetColor(myBlack);
				ofDrawCircle(dot_array[j].x1, dot_array[j].y1, 10);
			}
		}
		/*******************/
        ofSetBackgroundAuto(false);
        ofSetLineWidth(2);
        ofSetColor(myBlue);
        // 2nd week portion.
        if (water_draw_flag && route_index > 0) 
            ofDrawLine(water->route[route_index - 1].first, water->route[route_index - 1].second, water->route[route_index].first, water->route[route_index].second);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 'q' || key == 'Q'){
        // Reset flags
        draw_flag = 0;
        if(water_draw_flag) water_draw_flag = 0;
        
        // Free the dynamically allocated memory exits.
		/*******************/
		delete[] line_array;
		delete[] dot_array;
		/*******************/
        
		cout << "Memory for line segement has been freed." << endl;
        cout << "Memory for dot has been freed." << endl;
        
        _Exit(0);
    }
    if (key == 'd' || key == 'D'){
        if( !load_flag) return;
		draw_flag = 1;
    }
    if (key == 's'){
        water = new Water();
        
        water->initializeWaterLines(dot_array[selected_num].x1, dot_array[selected_num].y1);
        water_draw_flag = 1;
        // 2nd week portion.
    }
    if (key == 'e'){
        water_draw_flag = 0;
        route_index = 0;

        ofSetBackgroundAuto(true);

        delete water;
        // 2nd week portion.
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if( key == 'l' || key == 'L'){
        // Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a only txt for Waterfall");
        
        // Check whether the user opened a file
        if( openFileResult.bSuccess){
            ofLogVerbose("User selected a file");
            
            // We have a file, so let's check it and process it
            processOpenFileSelection(openFileResult);
            load_flag = 1;
        }
    }
    
    /* COMSIL1-TODO 4: This is selection dot control part.
     You can select dot in which water starts to flow by left, right direction key (<- , ->).
     */
    
    if (key == OF_KEY_RIGHT){
		/**************************************/
		dot_array[selected_num++].selected = 0;
		selected_num %= num_of_dot;
		dot_array[selected_num].selected = 1;
        cout << "Selcted Dot Coordinate is (" << dot_array[selected_num].x1 <<", "<< dot_array[selected_num].y1 << ")" << endl;
		/**************************************/
    }
    if (key == OF_KEY_LEFT){
		/**************************************/
		dot_array[selected_num].selected = 0;
		if (selected_num == 0)
		{
			selected_num = num_of_dot - 1;
		}
		else {
			selected_num--;
		}
		dot_array[selected_num].selected = 1;
		cout << "Selcted Dot Coordinate is (" << dot_array[selected_num].x1 << ", " << dot_array[selected_num].y1 << ")" << endl;
		/**************************************/
    }
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

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) { 
    //Path to the comma delimited file
    //string fileName = "input.txt";
    
    string fileName = openFileResult.getName();
    ofFile file(fileName);
    
    if( !file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;
    
    ofBuffer buffer(file);
    
    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0;
    
    
    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */

	/********************/
	int i = 0, j = 0, k = 0;
	/********************/

    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        // Split line into strings
        vector<string> words = ofSplitString(line, " ");
        
        if( words.size() == 1){
            if( input_type == 0){ // Input for the number of lines.
                num_of_line = atoi(words[0].c_str());
                cout << "The number of line is: " << num_of_line << endl;
				/********************/
				if (num_of_line == 0) {
					input_type == 1;
					line_array = NULL;
					continue;
				}
				else {
					line_array = new Line[num_of_line];
				}
				/********************/
            }
            else{ // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str());
                cout << "The number of dot is: " << num_of_dot << endl;

				/********************/
				dot_array = new Dot[num_of_dot];
				/********************/
            }
        }
        else if (words.size() >= 2){
            int x1,y1,x2,y2;
            if( input_type == 0){ // Input for actual information of lines
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                x2 = atoi(words[2].c_str());
                y2 = atoi(words[3].c_str());

				/********************/
				if (x1 < 0 || x1 > 1024) {
					_Exit(0);
				}
				if (y1 < 40 || y1 >= 728) {
					_Exit(0);
				}
				if (x2 < 0 || x2 > 1024) {
					_Exit(0);
				}
				if (y2 < 40 || y2 >= 728) {
					_Exit(0);
				}
				line_array[i].x1 = x1;
				line_array[i].y1 = y1;
				line_array[i].x2 = x2;
				line_array[i].y2 = y2;
				i++;

				if (i == num_of_line) {
					input_type = 1;
				}
				/********************/
            }
            else{ // Input for actual information of dots.
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());

				/********************/
				if (x1 < 0 || x1 > 1024) {
					_Exit(0);
				}
				if (y1 < 40 || y1 > 728) {
					_Exit(0);
				}
				dot_array[j].x1 = x1;
				dot_array[j].y1 = y1;
				if (j == 0) {
					dot_array[j].selected = 1;
				}
				else {
					dot_array[j].selected = 0;
				}
				j++;
				/********************/
            }
        } // End of else if.
    } // End of for-loop (Read file line by line).
}

void ofApp::Water::initializeWaterLines(int Sx, int Sy) {
    route.push_back(make_pair(Sx, Sy));
}

void ofApp::Water::calculateRoute(int meet_line, pair<float, float> before, float inclination) {
    pair<float, float> coordi;

    if (meet_line) {
        if (sin(inclination) > 0) {
            coordi.first = before.first + SPEED * cos(inclination);
            coordi.second = before.second + SPEED * sin(inclination);
        }
        else if (sin(inclination) < 0) {
            coordi.first = before.first - SPEED * cos(inclination);
            coordi.second = before.second - SPEED * sin(inclination);
        }
    }
    else {
        coordi.first = before.first;
        coordi.second = before.second + SPEED;
    }

    route.push_back(coordi);
}

pair<float, int> ofApp::Water::incline(pair<float, float> curr, int num_of_line, Line *line_array) {
    int meet_line = 0;
    int index = 0;
    int i;
    float meet_point;
    float inclination;

    for (i = 0; i < num_of_line; i++) {
        if (curr.first > line_array[i].x1 && line_array[i].x2 > curr.first || curr.first < line_array[i].x1 && line_array[i].x2 < curr.first) {
            if (curr.second > line_array[i].y1 && line_array[i].y2 > curr.second || curr.second < line_array[i].y1 && line_array[i].y2 < curr.second) {
                inclination = (float)atan((float)(line_array[i].y2 - line_array[i].y1) / (float)(line_array[i].x2 - line_array[i].x1));
                meet_point = tan(inclination) * (curr.first - line_array[i].x1) + line_array[i].y1;
                if (abs(meet_point - curr.second) < EPSILON)
                    meet_line = 1;
            }
        }
    }

    return make_pair(inclination, meet_line);
}