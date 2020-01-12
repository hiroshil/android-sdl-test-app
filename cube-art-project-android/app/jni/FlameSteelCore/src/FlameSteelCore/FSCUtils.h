/*
 * FSCUtils.h
 *
 *  Created on: Jul 31, 2016
 *      Author: demensdeum
 */

#ifndef FSCUTILS_H_
#define FSCUTILS_H_

#include <string>
#include <memory>

using namespace std;

namespace FlameSteelCore {
namespace Utils {

int RandomInt(int maximalInt);
bool RandomBool();
shared_ptr<string> localizedString(shared_ptr<string> key);

template <typename T>
void throwRuntimeException(T errorText) {
    throw runtime_error(errorText);
};

};
};

#endif /* FSCUTILS_H_ */
