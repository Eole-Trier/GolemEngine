#include "Reflection/classesManager.h"
#include "Debug/log.h"
#include "Core/transform.h"
#include "Components/Light/directional.h"
#include "Components/Light/point.h"
#include "Components/Light/spot.h"

void ClassesManager::AddAllClasses()
{
	Add<Component>();
	Add<Transform>();
	Add<Light>();
	Add<DirectionalLight>();
	Add<PointLight>();
	Add<SpotLight>();
}

void ClassesManager::Display(size_t _hashCode, void* _object)
{
	auto it = m_classes.find(_hashCode);

	// return if no classes linked to hash code
	if (it == m_classes.end())
	{
		Log::Print("No hash code");
		return;
	}
	// else store it in display func pointer
	it->second.display(_object);
}
