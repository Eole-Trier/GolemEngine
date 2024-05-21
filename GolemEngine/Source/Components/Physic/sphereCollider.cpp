#include "Components/Physic/sphereCollider.h"

#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>

#include <iostream>

#include "Physic/physicSystem.h"
#include "Physic/layers.h"
#include "MathsLib/utils.h"
#include "Wrappers/graphicWrapper.h"
#include "Resource/resourceManager.h"
#include "Wrappers/windowWrapper.h"

using namespace JPH;
using namespace JPH::literals;

SphereCollider::SphereCollider()
	: m_radius(1.f)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	SetModelPath("sphereCollider.obj");
	SetModel(resourceManager->Get<Model>(GetModelPath()));
}

SphereCollider::SphereCollider(float _radius)
	: m_radius(_radius)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	SetModelPath("sphereCollider.obj");
	SetModel(resourceManager->Get<Model>(GetModelPath()));
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Begin()
{
	id = PhysicSystem::CreateSphereCollider(owner->transform->localPosition, Quaternion::EulerToQuaternion(owner->transform->rotation), m_radius);
}

void SphereCollider::PreUpdate()
{
	Collider::PreUpdate();
}

void SphereCollider::Update()
{
	Collider::Update();
	PhysicSystem::SetSphereShape(id, m_radius);
}

void SphereCollider::PostUpdate()
{
	Collider::PostUpdate();
}

void SphereCollider::Draw(Camera* _camera)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	Shader* shader = resourceManager->Get<Shader>(resourceManager->GetSphereColliderShader());
	Model* model = GetModel();

	shader->Use();

	Matrix4 view = _camera->GetViewMatrix();
	Matrix4 projection = Matrix4::Projection(DegToRad(_camera->GetZoom()), WindowWrapper::GetScreenSize().x / WindowWrapper::GetScreenSize().y, _camera->GetNear(), _camera->GetFar());
	Matrix4 modelMat = Matrix4::TRS(owner->transform->localPosition, Quaternion::EulerToQuaternion(owner->transform->rotation), Vector3(1));
	shader->GetVertexShader()->SetFloat("radius", m_radius);
	shader->GetVertexShader()->SetMat4("model", modelMat);
	shader->GetVertexShader()->SetMat4("view", view);
	shader->GetVertexShader()->SetMat4("projection", projection);

	glBindVertexArray(model->VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, model->vertices.size());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}
