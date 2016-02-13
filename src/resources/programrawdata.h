#pragma once

#include <string>
#include <memory>

struct ProgramRawData {
    std::string vs_source;
    std::string fs_source;
};

using ProgramRawDataPtr = std::unique_ptr<ProgramRawData>;
