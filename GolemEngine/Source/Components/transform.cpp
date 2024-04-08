#include "Components/transform.h"
#include "golemEngine.h"
#include "Core/gameobject.h"
#include "Resource/sceneManager.h"

Transform::Transform()
{
    m_parent = SceneManager::GetCurrentScene()->GetWorld()->transform;
    m_localModel = Matrix4::TRS(Vector3(0, 0, 0), Quaternion::EulerToQuaternion(Vector3(0, 0, 0)), Vector3(1, 1, 1));
    if (m_parent)
        m_parent->AddChild(this);
}

Transform::Transform(Transform* _parent)
    : m_parent(_parent)
{
    m_localModel = Matrix4::TRS(Vector3(0, 0, 0), Quaternion::EulerToQuaternion(Vector3(0, 0, 0)), Vector3(1, 1, 1));
    if (m_parent)
        m_parent->AddChild(this);
}


Transform::Transform(Vector3 _position, Vector3 _rotation, Vector3 _scaling, Transform* _parent)
	: localPosition(_position), rotation(_rotation), scaling(_scaling), m_parent(_parent)
{
	m_localModel = Matrix4::TRS(_position, Quaternion::EulerToQuaternion(_rotation), _scaling);
    if (m_parent)
      m_parent->AddChild(this);
    
}

Transform::~Transform()
{
    owner->DeleteTransform(this);
}


void Transform::Update()
{}

void Transform::UpdateSelfAndChilds()
{
    m_localModel = Matrix4::TRS(localPosition, Quaternion::EulerToQuaternion(rotation), scaling);

    if (m_parent)
    {
        m_globalModel = m_parent->m_globalModel * m_localModel;
    }
    else
    {
        m_globalModel = m_localModel;
    }

    for (int i = 0; i < m_children.size(); i++)
    {
        m_children[i]->UpdateSelfAndChilds();
    }
    globalPosition = m_globalModel.TrsToPosition();
}

void Transform::AddChild(Transform* const _t)
{
    m_children.push_back(_t);
    if (_t->m_parent && _t->m_parent != this)
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
    _t->m_parent = SceneManager::GetCurrentScene()->GetWorld()->transform;
}

void Transform::SetParent(Transform* const _t)
{
    if (m_parent)
        m_parent->RemoveChild(this);
    m_parent = _t;
    _t->m_children.push_back(this);

    m_globalModel = _t->m_globalModel.Inverse() * m_globalModel;

    localPosition = m_globalModel.TrsToPosition();
    rotation = Vector3::QuaternionToEuler(m_globalModel.TrsToRotation());
    scaling = m_globalModel.TrsToScaling();
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
        }
        for (Transform* child : m_children)
        {
            return child->IsAParentOf(_t);
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

