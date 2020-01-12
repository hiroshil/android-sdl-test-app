#ifndef FLAMESTEELCOREDATA
#define FLAMESTEELCOREDATA

#include <string>
#include <memory>

using namespace std;

namespace FlameSteelCore {

class Data {

public:
    Data();
    static shared_ptr<Data> fromFilePath(shared_ptr<string> filePath);

    size_t size;
    char *data;
};

};

#endif