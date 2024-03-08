#include "UI/Windows/basicActors.h"

#include "Wrappers/interfaceWrapper.h"
#include "golemEngine.h"

BasicActors::BasicActors() {}

BasicActors::~BasicActors() {}

void BasicActors::Update(GolemEngine* _golemEngine, const char* _name)
{
	GOLEM_UI->Begin("Basic_Actors");
	GOLEM_UI->End();
}