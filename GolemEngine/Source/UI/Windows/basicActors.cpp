#include "UI/Windows/basicActors.h"

#include "Wrappers/interfaceWrapper0.h"
#include "golemEngine.h"

BasicActors::BasicActors() {}

BasicActors::~BasicActors() {}

void BasicActors::Update(GolemEngine* _golemEngine, const char* _name)
{
	UI_INTERFACE->Begin("Basic_Actors");
	UI_INTERFACE->End();
}