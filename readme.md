# C++ LiveCoding TestThingiethingthingieding

This project is a messy testbed for c++ live coding support in openFrameworks. 


### TODO:

- make paths relative
- figure out how to compile OF as dylib (or: compile entire emptyExample as dylib?)
  - not necessary anymore it seems. compiling the app itself with -rdynamic seems neater. 
- let RCCPP know about the dylib
- hope that it works


###  INSTRUCTIONS
based on:
https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus/wiki/Integrating-to-your-own-codebase

---

### 1. create addon

create folder addons/ofxRuntimeCompiledCPlusPlus
put the Aurora folder inside of it so that you have
create folder addons/ofxRuntimeCompiledCPlusPlus/Aurora




### 2. set up empty example

a. make sure it compiles and runs.
b. in xcode create a new group addons/RuntimeCPlusPlus
c. drag Aurora/RuntimeCompiler/RuntimeCompiler.xcodeproj in that group
d. drag Aurora/RuntimeObjectSystem/RuntimeObjectSystem.xcodeproj in that group
e. switch both projects to universal 32/64bit, select them from the scheme editor and build them
f. drag both products (libRuntimeObjectSystem.a and libRuntimeCompiler.a) to the
   "link binary with libraries" stage of the emptyExample target.
g. in emptyExample, set deployment target to 10.7 or newer
h. add ../../../addons/ofxRuntimeCompiledCPlusPlus/Aurora to user header search paths of your project
i. add -rdynamic to your linker flags to export all functions (like ofDrawLine) so they can be used from a shared library. 


see if it still compiles :) 

#### Modify Compiler_PlatformPosix.cpp

Around line 144 change 

		compilerLocation = "clang++ "

to 

		compilerLocation = "clang++ -stdlib=libstdc++ -undefined dynamic_lookup";

`-undefined dynamic_lookup` is needed at the moment because there will be lots of undefined symbols (like ofDrawLine, etc.), that are only resolved once the library is actually loaded.

maybe add `-m32` as well if you use 32 bits. 




---
3. modify your sources

add to ofApp.h
- - - - - - - - - - - - -
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
			char buff[1024];
			va_list args;
			va_start(args, format);
			vsprintf(buff, format, args);
			va_end(args);
			ofLogNotice("RCPP", buff);
		};
		~RCPPLogger() {}
	};
- - - - - - - - - - - - -

change to 

	class ofApp : public ofBaseApp,public IObjectFactoryListener{

and create the variables
		void OnConstructorsAdded(); 
		RuntimeObjectSystem runtimeSystem;
		RCPPLogger logger;
		IUpdateable* 			m_pUpdateable;
		ObjectId	   			m_ObjectId;

then in ofApp.cpp::setup add
	runtimeSystem.Initialise(&logger, NULL);
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
	
and in ofApp.cpp::update add
	runtimeSystem.GetFileChangeNotifier()->Update(1/ofGetFrameRate());


and add the method
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
	


you'll need to create these three files in your project: 

RuntimeObject01.cpp

	#include <RuntimeObjectSystem/ObjectInterfacePerModule.h>
	#include <RuntimeObjectSystem/IObject.h>
	#include "IUpdateable.h"
	#include "InterfaceIds.h"
	#include <iostream>


	class RuntimeObject01 : public TInterface<IID_IUPDATEABLE,IUpdateable>
	{
	public:
		virtual void Update( float deltaTime )
		{
			std::cout << "Runtime Object 01 update called!\n";
		}
	};

	REGISTERCLASS(RuntimeObject01);
	
	
InterfaceIds.h

	#pragma once

	#ifndef INTERFACEIDS_INCLUDED
	#define INTERFACEIDS_INCLUDED

	#include <RuntimeObjectSystem/IObject.h>

	enum InterfaceIDEnumConsoleExample
	{
		IID_IUPDATEABLE = IID_ENDInterfaceID,
	
		IID_ENDInterfaceIDEnumEmptyExample
	};


	#endif //INTERFACEIDS_INCLUDED
	
IUpdateable.h

	#pragma once

	#ifndef IUPDATEABLE_INCLUDED
	#define IUPDATEABLE_INCLUDED		

	#include <RuntimeObjectSystem/IObject.h>

	struct IUpdateable : public IObject
	{
		virtual void Update( float deltaTime ) = 0;
	};

	#endif // IUPDATEABLE_INCLUDED
	
	
	