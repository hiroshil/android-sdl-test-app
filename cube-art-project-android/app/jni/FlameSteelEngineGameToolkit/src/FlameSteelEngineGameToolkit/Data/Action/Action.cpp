#include "Action.h"

using namespace FlameSteelEngine::GameToolkit;

Action::Action(shared_ptr<string> instanceIdentifier, shared_ptr<Script> script, weak_ptr<ScriptEngine> scriptEngine)
{

    setInstanceIdentifier(instanceIdentifier);

    if (script.get() == nullptr)
    {
        throw logic_error("Can't set script in action constructor - script is null");
    }

    this->script = script;
    this->scriptEngine = scriptEngine;
}

void Action::step()
{

    auto lockedScriptEngine = scriptEngine.lock();

    if (lockedScriptEngine.get() == nullptr)
    {
        throw logic_error("Trying to call freed script engine");
    }

    lockedScriptEngine->step(script);
}