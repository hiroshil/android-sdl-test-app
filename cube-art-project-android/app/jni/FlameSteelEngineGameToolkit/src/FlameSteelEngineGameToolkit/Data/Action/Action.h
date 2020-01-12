#ifndef FSEGTACTION_H_
#define FSEGTACTION_H_

#include "Script.h"
#include <FlameSteelEngineGameToolkit/ScriptEngine/ScriptEngine.h>
#include <FlameSteelCore/Object.h>
#include <memory>
#include <string>

using namespace FlameSteelCore;
using namespace std;

namespace FlameSteelEngine
{
namespace GameToolkit
{

class Action: Object
{

public:
    Action(shared_ptr<string> instanceIdentifier, shared_ptr<Script> script, weak_ptr<ScriptEngine> scriptEngine);
    virtual void step();

private:
    shared_ptr<Script> script;
    weak_ptr<ScriptEngine> scriptEngine;

};
};
};

#endif