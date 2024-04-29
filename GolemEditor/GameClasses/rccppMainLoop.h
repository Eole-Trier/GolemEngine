#pragma once

#include "RuntimeInclude.h"
RUNTIME_MODIFIABLE_INCLUDE; //recompile runtime files when this changes
// abstract interface to our RCCppMainLoop class, using I at end to denote Interface

struct RCCppMainLoopI
{
    virtual void MainLoop() = 0;
    virtual int GetInt() = 0;
    virtual float GetFloat() = 0;
    virtual bool GetBool() = 0;
};