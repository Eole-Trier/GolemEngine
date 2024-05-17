#include "Physic/bodyActivationManager.h"

#include <iostream>


void BodyActivationManager::OnBodyActivated(const BodyID& inBodyID, uint64 inBodyUserData)
{
	//std::cout << "A body got activated" << std::endl;
}

void BodyActivationManager::OnBodyDeactivated(const BodyID& inBodyID, uint64 inBodyUserData)
{
	//std::cout << "A body went to sleep" << std::endl;
}