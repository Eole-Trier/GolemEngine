#pragma once

#include "dll.h"

#include <unordered_map>
#include <functional>

#include "displayType.h"
#include "Resource/sceneManager.h"

class ClassesManager
{
private:
	struct ClassInfo
	{
		std::function<void*(void)> create;
		std::function<void(void*)> display;
		std::function<bool()> createCondition;

		std::string name;
	};

	template <typename T>
	struct CreateCondition
	{
		_NODISCARD static bool CanCreate() { return true; }
	};

	template <>
	struct CreateCondition<Transform>
	{
		_NODISCARD static bool CanCreate() { return false; }
	};

	template <>
	struct CreateCondition<DirectionalLight>
	{
		_NODISCARD static bool CanCreate() { return SceneManager::GetCurrentScene()->GetDirectionalLights().size() < SceneManager::GetCurrentScene()->GetMaxDirectionalLights(); }
	};

	template <>
	struct CreateCondition<PointLight>
	{
		_NODISCARD static bool CanCreate() { return SceneManager::GetCurrentScene()->GetPointLights().size() < SceneManager::GetCurrentScene()->GetMaxPointLights(); }
	};

	template <>
	struct CreateCondition<SpotLight>
	{
		_NODISCARD static bool CanCreate() { return SceneManager::GetCurrentScene()->GetSpotLights().size() < SceneManager::GetCurrentScene()->GetMaxSpotLights(); }
	};

	static inline std::unordered_map<size_t, ClassInfo> m_classes;
	static inline std::unordered_map<std::string, ClassInfo> m_classesByName;

public:
	template<typename TypeT>
	static void Add();
	GOLEM_ENGINE_API static void AddAllClasses(); // Should modify this function if a new component class appears
	GOLEM_ENGINE_API static void Display(size_t _hashCode, void* _object);
	GOLEM_ENGINE_API static void* Create(size_t _hashCode);
	GOLEM_ENGINE_API static void* Create(const std::string& _name);
	GOLEM_ENGINE_API static std::vector<std::string> GetComponents();
};

template<typename TypeT>
static void ClassesManager::Add()
{
	// Get class hashcode
	size_t hashCode = typeid(TypeT).hash_code();

	// Associate a DisplayField function to the class represented by hash_code 
	ClassInfo classInfo = {
		.create = []() -> void* { return nullptr; },
		.display = [](void* _class) -> void { DisplayType::DisplayField<TypeT>(static_cast<TypeT*>(_class)); },
		.createCondition = CreateCondition<TypeT>::CanCreate,
		.name = typeid(TypeT).name()
	};

	// Check the abstract class case
	if constexpr (!std::is_abstract_v<TypeT>)
		classInfo.create = []() -> void* { return new TypeT; };

	// Store values in std::unordered_map
	m_classes.emplace(hashCode, classInfo);
	m_classesByName.emplace(classInfo.name, classInfo);

}

