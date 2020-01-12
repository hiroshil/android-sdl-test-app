#ifndef FSEGTSERIALIZEDMODELDEFINED
#define FSEGTSERIALIZEDMODELDEFINED

#include <FlameSteelCore/Object.h>

using namespace FlameSteelCore;

class FSEGTSerializedModel: public Object {

public:
    FSEGTSerializedModel(shared_ptr<string> serializedModel);
	void append(shared_ptr<string> stringToAppend);

    shared_ptr<string> serializedModel;
	int dotsCount = 0;

};

#endif