#include "Core/transform.h"

Transform::Transform(Vector3 _position, Vector3 _rotation, Vector3 _scaling)
	: position(_position), rotation(_rotation), scaling(_scaling)
{
    m_parent = nullptr;
	m_localModel = Matrix4::TRS(_position, _rotation, _scaling);
    std::cout << m_localModel << std::endl;
}

void Transform::Update()
{
    UpdateSelfAndChilds();
}

void Transform::UpdateSelfAndChilds()
{
    m_localModel = Matrix4::TRS(rotation, position, scaling);

    if (m_parent)
        m_globalModel = m_parent->m_globalModel * m_localModel;
    else
        m_globalModel = m_localModel;

    for (int i = 0; i < m_childs.size(); i++)
    {
        m_childs[i]->UpdateSelfAndChilds();
    }
}

void Transform::AddChild(Transform* const t)
{
    m_childs.push_back(t);
    if (t->m_parent)
        t->m_parent->RemoveChild(t);
    t->m_parent = this;
}

void Transform::AddChilds(std::vector<Transform*> const ts)
{
    for (Transform* t : ts)
        AddChild(t);
}

void Transform::RemoveChild(Transform* const t)
{
    std::erase(m_childs, t);
}

void Transform::SetParent(Transform* const t)
{
    m_parent = t;
}

Matrix4 Transform::GetGlobalModel()
{
	return m_globalModel;
}

Matrix4 Transform::GetLocalModel()
{
	return m_localModel;
}
