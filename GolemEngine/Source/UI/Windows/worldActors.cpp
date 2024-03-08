#include "UI/Windows/worldActors.h"

#include "Wrappers/interfaceWrapper.h"
#include "golemEngine.h"

WorldActors::WorldActors() {}

WorldActors::~WorldActors() {}

void WorldActors::Update(GolemEngine* _golemEngine, const char* _name)
{
	GOLEM_UI->Begin("World_Actors");
	GOLEM_UI->End();
}