#pragma once

#include <memory>

class Entity;
class Input;

class IController {
public:
    ~IController() {}
    
    virtual void process(Entity& entity) = 0;

    virtual void set_dt(float dt) = 0;

    virtual void set_input(Input* input) = 0;
};

using IControllerPtr = std::unique_ptr<IController>;
