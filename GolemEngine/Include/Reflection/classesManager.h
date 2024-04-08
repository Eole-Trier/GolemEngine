#pragma once

#include "dll.h"

#include <unordered_map>
#include <functional>

#include "displayType.h"

class ClassesManager
{
private:
	struct ClassInfo
	{
		std::function<void*(void)> create;
		std::function<void(void*)> display;
	};

	static inline std::unordered_map<size_t, ClassInfo> m_classes;

public:
	template<typename TypeT>
	static void Add();
	GOLEM_ENGINE_API static void AddAllClasses(); // Should modify this function if a new component class appears
	GOLEM_ENGINE_API static void Display(size_t _hashCode, void* _object);
	GOLEM_ENGINE_API static void* Create(size_t _hashCode);
};

template<typename TypeT>
static void ClassesManager::Add()
{
	// Get class hashcode
	size_t hashCode = typeid(TypeT).hash_code();

	// Associate a DisplayField function to the class represented by hash_code 
	ClassInfo classInfo = {
		.create = []() -> void* { return nullptr; },
		.display = [](void* _class) -> void { DisplayType::DisplayField<TypeT>(static_cast<TypeT*>(_class)); }
	};

	// Check the abstract class case
	if constexpr (!std::is_abstract_v<TypeT>)
		classInfo.create = []() -> void* { return new TypeT; };

	// Store values in std::unordered_map
	m_classes.emplace(hashCode, classInfo);
}

