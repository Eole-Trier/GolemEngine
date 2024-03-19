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
}

void Transform::UpdateSelfAndChilds()
{
    m_localModel = Matrix4::TRS(position, rotation, scaling);

    if (m_parent)
    {
        m_globalModel = m_parent->m_globalModel * m_localModel;
    }
    else
        m_globalModel = m_localModel;

    for (int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->UpdateSelfAndChilds();
    }
}

void Transform::AddChild(Transform* const _t)
{
    m_children.push_back(_t);
    if (_t->m_parent)
        _t->m_parent->RemoveChild(_t);
    _t->m_parent = this;
}

void Transform::AddChildren(std::vector<Transform*> const _ts)
{
    for (Transform* t : _ts)
        AddChild(t);
}

void Transform::RemoveChild(Transform* const _t)
{
    std::erase(m_children, _t);
    _t->m_parent = GolemEngine::GetInstance()->GetScene()->GetWorld()->transform;
}

void Transform::SetParent(Transform* const _t)
{
    if (m_parent)
        m_parent->RemoveChild(this);
    m_parent = _t;
    _t->AddChild(this);
}

bool Transform::IsChildOf(Transform* const _parent)
{
    return (m_parent == _parent);
}

bool Transform::IsAParentOf(Transform* const _t)
{
    if (m_children.size() != 0)
    {
        for (Transform* child : m_children)
        {
            if (child == _t)
                return true;
            child->IsAParentOf(_t);
        }
    }
    else
        return false;
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

