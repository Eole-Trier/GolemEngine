#include "Physic/contactManager.h"

#include <iostream>

ValidateResult ContactManager::OnContactValidate(const Body& inBody1, const Body& inBody2, RVec3Arg inBaseOffset, const CollideShapeResult& inCollisionResult)
{
	std::cout << "Contact validate callback" << std::endl;

	// Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
	return ValidateResult::AcceptAllContactsForThisBodyPair;
}

void ContactManager::OnContactAdded(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings)
{
	std::cout << "A contact was added" << std::endl;
}

void ContactManager::OnContactPersisted(const Body& inBody1, const Body& inBody2, const ContactManifold& inManifold, ContactSettings& ioSettings)
{
	std::cout << "A contact was persisted" << std::endl;
}

void ContactManager::OnContactRemoved(const SubShapeIDPair& inSubShapePair)
{
	std::cout << "A contact was removed" << std::endl;
}