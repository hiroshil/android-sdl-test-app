#include "IOSystem.h"

shared_ptr<IOSystem> IOSystem::initialize() {
    auto ioSystem = make_shared<IOSystem>();
    return ioSystem;
};

shared_ptr<Window> IOSystem::getWindow() {
    return window;
};
