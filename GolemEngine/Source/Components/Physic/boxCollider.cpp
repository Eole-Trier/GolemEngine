#include "Components/Physic/boxCollider.h"

#include <Jolt/Physics/Body/BodyInterface.h>

#include <iostream>

#include "Physic/physicSystem.h"
#include "Physic/layers.h"
#include "Wrappers/graphicWrapper.h"
#include "Resource/resourceManager.h"
#include "MathsLib/utils.h"

BoxCollider::BoxCollider()
	: m_size(Vector3(1.f, 1.f, 1.f))
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	SetModelPath("cubeCollider.obj");
	SetModel(resourceManager->Get<Model>(GetModelPath()));
}

BoxCollider::BoxCollider(Vector3 _size)
	: m_size(_size)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	SetModelPath("cubeCollider.obj");
	SetModel(resourceManager->Get<Model>(GetModelPath()));
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Begin()
{
	id = PhysicSystem::CreateBoxCollider(owner->transform->localPosition, Quaternion::EulerToQuaternion(owner->transform->rotation), m_size);
}

void BoxCollider::PreUpdate()
{
	Collider::PreUpdate();
}

void BoxCollider::Update()
{
	Collider::Update();
	PhysicSystem::SetBoxShape(id, m_size);
}

void BoxCollider::PostUpdate()
{
	Collider::PostUpdate();
}

void BoxCollider::Draw(float _width, float _height, Camera* _camera)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	Shader* shader = resourceManager->Get<Shader>("boxCollider");
	Model* model = GetModel();

	shader->Use();

	Matrix4 view = _camera->GetViewMatrix();
	Matrix4 projection = Matrix4::Projection(DegToRad(_camera->GetZoom()), _width / _height, _camera->GetNear(), _camera->GetFar());
	Matrix4 modelMat = Matrix4::TRS(owner->transform->localPosition, Quaternion::EulerToQuaternion(owner->transform->rotation), Vector3(1));
	shader->SetVec3("size", m_size);
	shader->SetMat4("model", modelMat);
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);

	glBindVertexArray(model->VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, model->vertices.size());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}