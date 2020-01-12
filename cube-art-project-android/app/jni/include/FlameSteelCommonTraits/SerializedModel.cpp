#include "SerializedModel.h"
#include <FlameSteelCore/FSCUtils.h>

using namespace FlameSteelCore::Utils;

FSEGTSerializedModel::FSEGTSerializedModel(shared_ptr<string> serializedModel) {

    this->serializedModel = serializedModel;

}

void FSEGTSerializedModel::append(shared_ptr<string> stringToAppend) {

	if (stringToAppend.get() == nullptr) {
		throwRuntimeException(string("Can't append empty string"));
	}

	*serializedModel += *stringToAppend;

};