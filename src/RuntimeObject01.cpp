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
		// crashes
		ofLine(50,500,400,100);
		return -1;
	}
};

REGISTERCLASS(RuntimeObject01);
