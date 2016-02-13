#pragma once

#include "windowsize.h"

#include <memory>

class IWindow {
public:
    ~IWindow() {}

    virtual void swap_window() = 0;

    virtual void resize(int width, int height) = 0;

    WindowSize virtual size() const = 0;
};

using IWindowPtr = std::unique_ptr<IWindow>;
