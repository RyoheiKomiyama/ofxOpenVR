#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(false);

	openVR.setup(std::bind(&ofApp::render, this, std::placeholders::_1));
	openVR.setDrawControllers(true);

	ofAddListener(openVR.ofxOpenVRControllerEvent, this, &ofApp::controllerEvent);

	img.load("of.png");
	img.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);

	box.set(1);
	box.enableColors();
	box.mapTexCoordsFromTexture(img.getTexture());

	// Create a translation matrix to place the box in the space
	translateMatrix.translate(ofVec3f(0.0, .0, -2.0));

	shader.load("shader/shader");
	controllersShader.load("shader/controllers");
}

//--------------------------------------------------------------
void ofApp::exit() {
	ofRemoveListener(openVR.ofxOpenVRControllerEvent, this, &ofApp::controllerEvent);
	openVR.exit();
}

//--------------------------------------------------------------
void ofApp::update() {
	openVR.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	openVR.render();
	openVR.renderDistortion();
	openVR.drawDebugInfo();
}

//--------------------------------------------------------------
void ofApp::render(vr::Hmd_Eye nEye) {

	// oF textured cube
	glm::mat4x4 cvpm = openVR.getCurrentViewProjectionMatrix(nEye);
	ofMatrix4x4 currentViewProjectionMatrix(cvpm[0][0], cvpm[0][1], cvpm[0][2], cvpm[0][3],
		cvpm[1][0], cvpm[1][1], cvpm[1][2], cvpm[1][3],
		cvpm[2][0], cvpm[2][1], cvpm[2][2], cvpm[2][3],
		cvpm[3][0], cvpm[3][1], cvpm[3][2], cvpm[3][3]);
	ofMatrix4x4 hdmPoseMat = translateMatrix * currentViewProjectionMatrix;

	shader.begin();
	shader.setUniformMatrix4f("matrix", hdmPoseMat, 1);
	shader.setUniformTexture("baseTex", img.getTexture(), 0);
	box.draw();
	shader.end();

	// Left controller
	if (openVR.isControllerConnected(vr::TrackedControllerRole_LeftHand)) {
		glm::mat4x4 cpl = openVR.getControllerPose(vr::TrackedControllerRole_LeftHand);
		ofMatrix4x4 controllerPoseLeft(cpl[0][0], cpl[0][1], cpl[0][2], cpl[0][3],
			cpl[1][0], cpl[1][1], cpl[1][2], cpl[1][3],
			cpl[2][0], cpl[2][1], cpl[2][2], cpl[2][3],
			cpl[3][0], cpl[3][1], cpl[3][2], cpl[3][3]);
		ofMatrix4x4 leftControllerPoseMat = currentViewProjectionMatrix * controllerPoseLeft;

		controllersShader.begin();
		controllersShader.setUniformMatrix4f("matrix", leftControllerPoseMat, 1);
		controllerBox.drawWireframe();
		controllersShader.end();
	}

	// Right controller
	if (openVR.isControllerConnected(vr::TrackedControllerRole_RightHand)) {
		glm::mat4x4 cpr = openVR.getControllerPose(vr::TrackedControllerRole_RightHand);
		ofMatrix4x4 controllerPoseRight(cpr[0][0], cpr[0][1], cpr[0][2], cpr[0][3],
			cpr[1][0], cpr[1][1], cpr[1][2], cpr[1][3],
			cpr[2][0], cpr[2][1], cpr[2][2], cpr[2][3],
			cpr[3][0], cpr[3][1], cpr[3][2], cpr[3][3]);
		ofMatrix4x4 rightControllerPoseMat = currentViewProjectionMatrix * controllerPoseRight;

		controllersShader.begin();
		controllersShader.setUniformMatrix4f("matrix", rightControllerPoseMat, 1);
		controllerBox.drawWireframe();
		controllersShader.end();
	}
}

//--------------------------------------------------------------
void ofApp::controllerEvent(ofxOpenVRControllerEventArgs& args)
{
	cout << "ofApp::controllerEvent > role: " << (int)args.controllerRole << " - event type: " << (int)args.eventType << " - button type: " << (int)args.buttonType << " - x: " << args.analogInput_xAxis << " - y: " << args.analogInput_yAxis << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	openVR.toggleGrid();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
