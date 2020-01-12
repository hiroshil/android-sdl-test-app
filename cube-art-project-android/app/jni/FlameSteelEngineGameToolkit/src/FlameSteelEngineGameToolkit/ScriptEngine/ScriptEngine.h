#ifndef FSEGTSCRIPTENGINE_H_
#define FSEGTSCRIPTENGINE_H_

#include <memory>
#include <string>
#include <FlameSteelEngineGameToolkit/Data/Action/Script.h>

using namespace FlameSteelEngine::GameToolkit;


class ScriptEngine
{

public:
    void step(shared_ptr<Script> script);

};

#endif