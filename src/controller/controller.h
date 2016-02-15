#pragma once

#include "abstractcontroller.h"

class Entity;
class Input;

class Controller : public IController {
public:
    void process(Entity& entity) override;

    void set_dt(float dt) override;

    void set_input(Input* input) override;    

private:
    Input* _pinput;
    float _dt;
};

inline
void Controller::set_input(Input* input)
{
    _pinput = input;
}

inline
void Controller::set_dt(float dt)
{
    _dt = dt;
}
