#include "Components/Physic/rigidBody.h"

#include <iostream>

RigidBody::RigidBody()
{
	/*m_bodyManager = new JPH::BodyManager();
	JPH::BroadPhaseLayerInterface* layer = new JPH::BroadPhaseLayerInterface();
	
	m_bodyManager->Init(10, 10, *layer);

	m_bodyCreationSettings = new JPH::BodyCreationSettings();
	m_bodyCreationSettings->mPosition = JPH::RVec3(5, 10, 20);

	m_body = m_bodyManager->AllocateBody(*m_bodyCreationSettings);

	m_bodyManager->AddBody(m_body);
	*/
	//JPH::Body* body = &m_bodyManager->GetBody(m_body->GetID());

	//std::cout << m_body->GetPosition() << std::endl;
}

RigidBody::~RigidBody()
{

}