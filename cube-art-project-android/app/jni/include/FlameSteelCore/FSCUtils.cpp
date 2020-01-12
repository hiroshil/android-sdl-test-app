/*
 * FSCUtils.cpp
 *
 *  Created on: Jul 31, 2016
 *      Author: demensdeum
 */

#include "FSCUtils.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

namespace FlameSteelCore {
namespace Utils {

int RandomInt(int maximalInt) {

    if (maximalInt == 0) {
        return 0;
    }

    int randomInt = rand() % maximalInt;

    return randomInt;
}

bool RandomBool() {
    return RandomInt(2);
}

shared_ptr<string> localizedString(shared_ptr<string> key) {
    return key;
}


}
}