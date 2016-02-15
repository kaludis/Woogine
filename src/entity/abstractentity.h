#pragma once

#include <string>

class IEntity {
public:
    ~IEntity() {}

    //    virtual void update(float dt) = 0;

    virtual std::string name() const = 0;

    virtual void init() {}
};
