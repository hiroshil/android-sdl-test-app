#ifndef FSEGTSCRIPT_H_
#define FSEGTSCRIPT_H_

#include <memory>
#include <string>

using namespace std;

namespace FlameSteelEngine
{
namespace GameToolkit
{

class Script
{

public:
    Script(shared_ptr<string> source);
    shared_ptr<string> source;

};

};
};

#endif