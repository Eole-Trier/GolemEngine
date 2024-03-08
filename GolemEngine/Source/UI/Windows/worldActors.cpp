#include "UI/Windows/worldActors.h"

#include "Wrappers/interfaceWrapper0.h"
#include "golemEngine.h"

WorldActors::WorldActors() {}

WorldActors::~WorldActors() {}

void WorldActors::Update(GolemEngine* _golemEngine, const char* _name)
{
	UI_INTERFACE->Begin("World_Actors");
	UI_INTERFACE->End();
}