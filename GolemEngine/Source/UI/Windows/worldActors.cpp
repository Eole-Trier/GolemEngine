#include "UI/Windows/worldActors.h"

#include "Wrappers/interfaceWrapper.h"

WorldActors::WorldActors() {}

WorldActors::~WorldActors() {}

void WorldActors::Update()
{
	InterfaceWrapper::GetInstance()->Begin("World_Actors");
	InterfaceWrapper::GetInstance()->End();
}