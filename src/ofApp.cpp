#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	runtimeSystem.Initialise(&logger, NULL);
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/3d");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/app");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/communication");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/events");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/gl");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/graphics");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/math");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/ofMain.h");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/sound");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/types");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/utils");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworks/video");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/cairo/include");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/cairo/include/cairo/");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/fmodex/include");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/FreeImage/include");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/freetype/include");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/glew/include");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/glfw/include");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/glut/include");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openssl/include");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/poco/include");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/rtAudio/include");
	runtimeSystem.AddIncludeDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/tess2/include");
	runtimeSystem.AddLibraryDir("/Users/hansi/Documents/OF/of_v0084_osx_release/libs/openFrameworksCompiled/lib/osx");
	runtimeSystem.GetObjectFactorySystem()->AddListener(this);

	// construct first object
	IObjectConstructor* pCtor = runtimeSystem.GetObjectFactorySystem()->GetConstructor( "RuntimeObject01" );
	if( pCtor )
	{
		IObject* pObj = pCtor->Construct();
		pObj->GetInterface( &m_pUpdateable );
		if( 0 == m_pUpdateable )
		{
			delete pObj;
			logger.LogError("Error - no updateable interface found\n");
			return false;
		}
		m_ObjectId = pObj->GetObjectId();
	}
	
	runtimeSystem.CompileAll(false);
}

void ofApp::OnConstructorsAdded()
{
	// This could have resulted in a change of object pointer, so release old and get new one.
	if( m_pUpdateable )
	{
		IObject* pObj = runtimeSystem.GetObjectFactorySystem()->GetObject( m_ObjectId );
		pObj->GetInterface( &m_pUpdateable );
		if( 0 == m_pUpdateable )
		{
			delete pObj;
			logger.LogError( "Error - no updateable interface found\n");
		}
	}
}


//--------------------------------------------------------------
void ofApp::update(){
	runtimeSystem.GetFileChangeNotifier()->Update(1/ofGetFrameRate());
	if( runtimeSystem.GetIsCompiledComplete() ){
		runtimeSystem.LoadCompiledModule();
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0, 0, 0);
	ofSetColor(255);
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	ofCircle(0,50*cos(ofGetElapsedTimef()),50);
	
	// 2 lzy 2 rename
	m_pUpdateable->Get();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}