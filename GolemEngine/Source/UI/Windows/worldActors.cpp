#include "UI/Windows/worldActors.h"

#include "Wrappers/interfaceWrapper.h"
#include "golemEngine.h"

WorldActors::WorldActors() {}

WorldActors::~WorldActors() {}

void WorldActors::Update(GolemEngine* _golemEngine, const char* _name)
{
	InterfaceWrapper::GetInstance()->Begin("World_Actors");
	InterfaceWrapper::GetInstance()->End();
}