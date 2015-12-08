#include "/Users/hansi/Documents/OF/of_v0084_osx_release/addons/ofxRuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem/ObjectInterfacePerModule.h"
#include "/Users/hansi/Documents/OF/of_v0084_osx_release/addons/ofxRuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem/IObject.h"
#include "IUpdateable.h"
#include "InterfaceIds.h"
#include <iostream>
#include "ofMain.h"

class RuntimeObject01 : public TInterface<IID_IUPDATEABLE,IUpdateable>
{
public:
	virtual int Get()
	{
		// outputs pt=0
		// cout << "pt= " << ofGetAppPtr() << endl;
		// just doing some dumb shit with matrices to make sure they work.
		ofMatrix4x4 mat;
		ofVec3f v(1,0,0);
		ofLine(200,500,0,ofGetMouseY()-400 + (mat*v).x);
		return -1;
	}
};

REGISTERCLASS(RuntimeObject01);
