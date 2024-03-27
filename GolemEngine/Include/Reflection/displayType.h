#pragma once

#include <vector>
#include <iostream>

#include "vector3.h"
#include "vector4.h"

#include "imgui.h"
#include "imgui_stdlib.h"

#include "Reflection/refl.hpp"

class DisplayType
{
public:
	template<typename TypeT>
	static void DisplayField(TypeT* _class);

	template<typename TypeT, typename MemberT, typename DescriptorT>
	static void BasicsFields(MemberT* _class);

	template<typename TypeT, typename MemberT, typename DescriptorT>
	static void DisplayStdVector(MemberT* _member);

	GOLEM_ENGINE_API static void DisplayWithHashCode(size_t _hashCode, void* _object);
};

template<typename>
struct is_std_vector : std::false_type {};

template<typename T, typename A>
struct is_std_vector<std::vector<T, A>> : std::true_type {};

template<typename T>
constexpr bool is_std_vector_v = is_std_vector<T>::value;

template<typename TypeT>
void DisplayType::DisplayField(TypeT* _class)
{
	constexpr auto type = refl::reflect<TypeT>();	// Get the reflected class
	for_each(type.members, [&]<typename DescriptorT>(const DescriptorT)	// Loop through each member of the reflected class
	{
		using MemberT = DescriptorT::value_type;
		if constexpr (std::is_array_v<MemberT>) // array case
		{
		}
		else if constexpr (is_std_vector_v<MemberT>) // std::vector case
		{
			DisplayStdVector<TypeT, MemberT, DescriptorT>(&DescriptorT::get(_class));
		}
		else // basic case
		{
			BasicsFields<TypeT, MemberT, DescriptorT>(&DescriptorT::get(_class));
		}
	});
}

template<typename TypeT, typename MemberT, typename DescriptorT>
void DisplayType::BasicsFields(MemberT* _class)
{
	if constexpr (std::is_pointer_v<MemberT>)
	{
		DisplayWithHashCode(typeid(** _class).hash_code(), *_class);
	}
	// Display Imgui with all original types
	else if constexpr (std::is_same_v<std::string, MemberT>) // string
	{
		ImGui::InputText(DescriptorT::name.c_str(), _class);
	}
	else if constexpr (std::is_same_v<std::int8_t, MemberT>) // int_8
	{
		ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_S8, _class);
	}
	else if constexpr (std::is_same_v<std::int16_t, MemberT>) // int_16
	{
		ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_S16, _class);
	}
	else if constexpr (std::is_same_v<std::int32_t, MemberT>) // int_32
	{
		ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_S32, _class);
	}
	else if constexpr (std::is_same_v<std::uint8_t, MemberT>) // uint_8
	{
		ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_U8, _class);
	}
	else if constexpr (std::is_same_v<std::uint16_t, MemberT>) // uint_16
	{
		ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_U16, _class);
	}
	else if constexpr (std::is_same_v<std::uint32_t, MemberT>) // uint_32
	{
		ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_U32, _class);
	}
	else if constexpr (std::is_same_v<float, MemberT>) // float 
	{
		ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_Float, _class);
	}
	else if constexpr (std::is_same_v<double, MemberT>) // double
	{
		ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_Double, _class);
	}
	else if constexpr (std::is_same_v<bool, MemberT>) // bool
	{
		ImGui::Checkbox(DescriptorT::name.c_str(), _class);
	}
	else if constexpr (std::is_same_v<Vector3, MemberT>)
	{
		ImGui::DragFloat3(DescriptorT::name.c_str(), &_class->x, .1f);
	}
	else if constexpr (std::is_same_v<Vector4, MemberT>)
	{
		ImGui::DragFloat4(DescriptorT::name.c_str(), &_class->x, .1f);
	}
}

template<typename TypeT, typename MemberT, typename DescriptorT>
void DisplayType::DisplayStdVector(MemberT* _member)
{
	for (unsigned int i = 0; i < _member->size(); i++)
	{
		BasicsFields<TypeT, MemberT::value_type, DescriptorT>(&(*_member)[i]);
	}
}
