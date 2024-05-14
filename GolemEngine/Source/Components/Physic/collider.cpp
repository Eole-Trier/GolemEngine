#include "Components/Physic/collider.h"
#include "Physic/physicSystem.h"
#include "Core/gameobject.h"
#include "Wrappers/graphicWrapper.h"

Collider::Collider()
	: m_IsActivated(false), m_MotionType(MotionType::Static), m_model(nullptr), m_modelPath(nullptr)
{
	PhysicSystem::AddCollider(this);
}

Collider::~Collider()
{
	BodyInterface& body_interface = PhysicSystem::physicsSystem.GetBodyInterface();
	// Remove the body from the physics system. Note that the body itself keeps all of its state and can be re-added at any time.
	body_interface.RemoveBody(id);

	// Destroy the body. After this the sphere ID is no longer valid.
	body_interface.DestroyBody(id);
	PhysicSystem::DeleteCollider(this);
}

void Collider::Begin()
{
}

void Collider::PreUpdate()
{
	BodyInterface& bodyInterface = PhysicSystem::physicsSystem.GetBodyInterface();

	switch (m_MotionType)
	{
	case MotionType::Static:
		PhysicSystem::MakeBodyStatic(id);
		break;
	case MotionType::Kinematic:
		break;
	case MotionType::Dynamic:
		PhysicSystem::MakeBodyDynamic(id);
		break;
	default:
		break;
	}
	if (m_IsActivated)
	{
		PhysicSystem::ActivateBody(id);
	}
	else
	{
		PhysicSystem::DeactivateBody(id, owner->transform->localPosition);
	}

	bodyInterface.SetPosition(id, PhysicSystem::ToJph(owner->transform->localPosition), EActivation::DontActivate);
	bodyInterface.SetRotation(id, PhysicSystem::ToJph(Quaternion::EulerToQuaternion(owner->transform->rotation)), EActivation::DontActivate);
}

void Collider::Update()
{
}

void Collider::PostUpdate()
{
	BodyInterface& bodyInterface = PhysicSystem::physicsSystem.GetBodyInterface();
	RVec3 position = bodyInterface.GetPosition(id);
	owner->transform->localPosition = PhysicSystem::ToVector3(position);
}

Model* Collider::GetModel()
{
	return m_model;
}

void Collider::SetModel(Model* _model)
{
	m_model = _model;
	glGenVertexArrays(1, &m_model->VAO);

	glGenBuffers(1, &m_model->VBO);

	glBindVertexArray(m_model->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_model->vertices.size(), m_model->vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const char* Collider::GetModelPath()
{
	return m_modelPath;
}

void Collider::SetModelPath(const char* _path)
{
	m_modelPath = _path;
}