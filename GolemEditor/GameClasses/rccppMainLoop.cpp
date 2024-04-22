#include "ObjectInterfacePerModule.h"
#include "IObject.h"
#include "rccppMainLoop.h"
#include "systemTable.h"
//#include "player.h"
#include <iostream>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// RCC++ uses interface Id's to distinguish between different classes
// here we have only one, so we don't need a header for this enum and put it in the same
// source code file as the rest of the code
enum InterfaceIDEnumConsoleExample
{
    IID_IRCCPP_MAIN_LOOP = IID_ENDInterfaceID, // IID_ENDInterfaceID from IObject.h InterfaceIDEnum

    IID_ENDInterfaceIDEnumConsoleExample
};

struct RCCppMainLoop : RCCppMainLoopI, TInterface<IID_IRCCPP_MAIN_LOOP, IObject>
{
    RCCppMainLoop()
    {
        PerModuleInterface::g_pSystemTable->pRCCppMainLoopI = this;
    }
    void MainLoop() override
    {
    }
    int GetInt() override
    {
        return 1;
    }
};

REGISTERSINGLETON(RCCppMainLoop, true);