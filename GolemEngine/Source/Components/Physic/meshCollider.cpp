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
}

MeshCollider::~MeshCollider()
{
}

void MeshCollider::Begin()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	Model* model = owner->GetComponent<MeshRenderer>()->GetMesh()->GetModel();
	Model* newModel = resourceManager->Create<Model>(owner->name + "Collider", model->path);
	newModel->Load(newModel->path.c_str());

	SetModel(newModel);
	id = PhysicSystem::CreateMeshCollider(GetModel()->vertices, owner->transform->localPosition, Quaternion::EulerToQuaternion(owner->transform->rotation));
}

void MeshCollider::PreUpdate()
{
	Collider::PreUpdate();
}

void MeshCollider::Update()
{
	Collider::Update();
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