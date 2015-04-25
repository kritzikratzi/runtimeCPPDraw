#pragma once

#ifndef IUPDATEABLE_INCLUDED
#define IUPDATEABLE_INCLUDED

#include "/Users/hansi/Documents/OF/of_v0084_osx_release/addons/ofxRuntimeCompiledCPlusPlus/Aurora/RuntimeObjectSystem/IObject.h"

struct IUpdateable : public IObject
{
	virtual int Get() = 0;
};

#endif // IUPDATEABLE_INCLUDED