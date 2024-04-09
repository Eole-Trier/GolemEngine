#include "Reflection/classesManager.h"
#include "Debug/log.h"
#include "Components/transform.h"
#include "Components/meshRenderer.h"
#include "Components/Light/directional.h"
#include "Components/Light/point.h"
#include "Components/Light/spot.h"
#include "Components/audio.h"

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
