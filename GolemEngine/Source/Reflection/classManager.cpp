#include "Reflection/classesManager.h"
#include "Debug/log.h"
#include "Components/transform.h"
#include "Components/meshRenderer.h"
#include "Components/Light/directionalLight.h"
#include "Components/Light/pointLight.h"
#include "Components/Light/spotLight.h"
#include "Components/audio.h"
#include "Components/Physic/sphereCollider.h"
#include "Components/Physic/boxCollider.h"

void ClassesManager::AddAllClasses()
{
	Add<Component>();
	Add<Transform>();
	Add<MeshRenderer>();
	Add<Light>();
	Add<DirectionalLight>();
	Add<PointLight>();
	Add<SpotLight>();
	Add<Audio>();
	Add<SphereCollider>();
	Add<BoxCollider>();
}

void ClassesManager::Display(size_t _hashCode, void* _object)
{
	auto it = m_classes.find(_hashCode);

	// return if no classes linked to hash code
	if (it == m_classes.end())
	{
		Log::Print("No class matches the hash code");
		return;
	}
	// else store it in display func pointer
	it->second.display(_object);
}

void* ClassesManager::Create(size_t _hashCode)
{
	auto it = m_classes.find(_hashCode);

	// return if no classes linked to hash code
	if (it == m_classes.end())
	{
		Log::Print("No class matches the hash code");
		return nullptr;
	}
	// else store it in display func pointer
	return it->second.create();
}
