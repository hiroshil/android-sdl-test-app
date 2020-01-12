#include "Data.h"
#include "FSCUtils.h"
#include <sstream>

using namespace FlameSteelCore;
using namespace FlameSteelCore::Utils;

Data::Data() {

    size = 0;
    data = nullptr;

};

shared_ptr<Data> Data::fromFilePath(shared_ptr<string> filePath) {

    auto data = make_shared<Data>();

    char *buffer = nullptr;
    auto file = fopen (filePath->c_str(), "rb");

    if (file != nullptr) {

        fseek (file, 0, SEEK_END);

        auto length = ftell (file);
        data->size = length;

        fseek (file, 0, SEEK_SET);
        buffer = (char *) malloc (length);

        if (buffer)
        {
            auto readBytes = fread (buffer, 1, length, file);
            if (readBytes != length) {
                string errorString = "FlameSteelCore::Data read from file:";
                stringstream stderrString;
                stderrString << stderr << endl;
                errorString += stderrString.str();
                throwRuntimeException(errorString);
            }
        }

        data->data = buffer;

        fclose (file);
    }

    return data;
};
