#include "Core/transform.h"
#include "golemEngine.h"
#include "Core/gameobject.h"

Transform::Transform(Vector3 _position, Vector3 _rotation, Vector3 _scaling)
	: position(_position), rotation(_rotation), scaling(_scaling)
{
    m_parent = nullptr;
	m_localModel = Matrix4::TRS(_position, _rotation, _scaling);
}

void Transform::Update()
{
    UpdateSelfAndChilds();
}

void Transform::UpdateSelfAndChilds()
{
    m_localModel = Matrix4::TRS(position, rotation, scaling);

    if (m_parent)
        m_globalModel = m_parent->m_globalModel * m_localModel;
    else
        m_globalModel = m_localModel;

    for (int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->UpdateSelfAndChilds();
    }
}

void Transform::AddChild(Transform* const t)
{
    m_children.push_back(t);
    if (t->m_parent)
        t->m_parent->RemoveChild(t);
    t->m_parent = this;
}

void Transform::AddChildren(std::vector<Transform*> const ts)
{
    for (Transform* t : ts)
        AddChild(t);
}

void Transform::RemoveChild(Transform* const t)
{
    std::erase(m_children, t);
    t->m_parent = GolemEngine::GetInstance()->GetScene()->GetWorld()->transform;
}

void Transform::SetParent(Transform* const t)
{
    if (m_parent)
        m_parent->RemoveChild(this);
    m_parent = t;
    t->AddChild(this);
}

Transform* Transform::GetParent()
{
    return m_parent;
}


Matrix4 Transform::GetGlobalModel()
{
	return m_globalModel;
}

Matrix4 Transform::GetLocalModel()
{
	return m_localModel;
}

const std::vector<Transform*>& Transform::GetChildren() const
{
    return m_children;
}

