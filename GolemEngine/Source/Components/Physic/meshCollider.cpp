#include "Components/Physic/meshCollider.h"

#include <Jolt/Physics/Body/BodyInterface.h>

#include <iostream>

#include "Physic/physicSystem.h"
#include "Physic/layers.h"
#include "Wrappers/graphicWrapper.h"
#include "Resource/resourceManager.h"
#include "Components/meshRenderer.h"
#include "MathsLib/utils.h"

MeshCollider::MeshCollider()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
}

MeshCollider::~MeshCollider()
{
}

void MeshCollider::Begin()
{
	SetModel(owner->GetComponent<MeshRenderer>()->GetMesh()->GetModel());
	id = PhysicSystem::CreateMeshCollider(GetModel()->vertices, owner->transform->localPosition, Quaternion::EulerToQuaternion(owner->transform->rotation));
}

void MeshCollider::PreUpdate()
{
	Collider::PreUpdate();
}

void MeshCollider::Update()
{
	Collider::Update();
	//PhysicSystem::SetBoxShape(id, m_size);
}

void MeshCollider::PostUpdate()
{
	Collider::PostUpdate();
}

void MeshCollider::Draw(float _width, float _height, Camera* _camera)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	Shader* shader = resourceManager->Get<Shader>("meshCollider");

	Model* model = GetModel();

	shader->Use();

	Matrix4 view = _camera->GetViewMatrix();
	Matrix4 projection = Matrix4::Projection(DegToRad(_camera->GetZoom()), _width / _height, _camera->GetNear(), _camera->GetFar());
	Matrix4 modelMat = Matrix4::TRS(owner->transform->localPosition, Quaternion::EulerToQuaternion(owner->transform->rotation), Vector3(1));
	shader->SetMat4("model", modelMat);
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);

	glBindVertexArray(model->VAO);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, model->vertices.size());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(0);
}