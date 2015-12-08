#pragma once

#include "ofMain.h"
#include <RuntimeObjectSystem/RuntimeObjectSystem.h>
#include <RuntimeCompiler/ICompilerLogger.h>
#include <RuntimeObjectSystem/IObjectFactorySystem.h>
#include <RuntimeObjectSystem/ObjectInterface.h>
#include <RuntimeCompiler/AUArray.h>
#include "IUpdateable.h"

struct RCPPLogger : ICompilerLogger
{
	void LogError(const char * format, ...){
		char buff[1024];
		va_list args;
		va_start(args, format);
		vsprintf(buff, format, args);
		va_end(args);
		ofLogError("RCPP", buff);
	};
	void LogWarning(const char * format, ...) {
		char buff[1024];
		va_list args;
		va_start(args, format);
		vsprintf(buff, format, args);
		va_end(args);
		ofLogWarning("RCPP", buff);
	};
	void LogInfo(const char * format, ...){
		char buff[1024*4];
		va_list args;
		va_start(args, format);
		vsprintf(buff, format, args);
		va_end(args);
		ofLogNotice("RCPP", buff);
	};
	~RCPPLogger() {}
};


class ofApp : public ofBaseApp,public IObjectFactoryListener{
	public:
		void setup();
		void update();
		void draw();
	
		void OnConstructorsAdded();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		RuntimeObjectSystem runtimeSystem;
		RCPPLogger logger;
		IUpdateable* 			m_pUpdateable;
		ObjectId	   			m_ObjectId;
};
