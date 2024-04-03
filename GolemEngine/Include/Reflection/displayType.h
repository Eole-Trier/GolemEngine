#pragma once

#include <vector>
#include <iostream>

#include "vector3.h"
#include "vector4.h"

#include "imgui.h"
#include "imgui_stdlib.h"

#include "Reflection/attributes.h"
#include "Refl/refl.hpp"
#include "Core/gameObject.h"

class DisplayType
{
public:
	template<typename TypeT>
	static void DisplayField(TypeT* _class);

	template<typename TypeT, typename MemberT, typename DescriptorT>
	static void BasicsFields(MemberT* _class);

	template<typename TypeT, typename MemberT, typename DescriptorT>
	static void DisplayStdVector(MemberT* _member);

	template<typename TypeT, typename MemberT, typename DescriptorT>
	static void DisplayIntOrFloat(MemberT* _member);

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
	if (dynamic_cast<Component*>(_class) && !dynamic_cast<Transform*>(_class))  // If class is component replace the name by a button that can delete (can't delete transform)
	{
		Component* c = dynamic_cast<Component*>(_class);
		const char* removeComponentPopupId = "Remove Component";
		if (ImGui::Button(type.name.c_str()))
			ImGui::OpenPopup(removeComponentPopupId);

		if (ImGui::BeginPopupContextItem(removeComponentPopupId))
		{
			if (ImGui::MenuItem("Remove Component"))
			{
				c->owner->RemoveComponent(c);
			}
			ImGui::EndPopup();
		}
	}
	else
	{
		ImGui::Text("%s", type.name.c_str());
	}
	for_each(type.members, [&]<typename DescriptorT>(const DescriptorT)	// Loop through each member of the reflected class
	{
		using MemberT = DescriptorT::value_type;

		if constexpr (!refl::descriptor::has_attribute<HideInInspector>(DescriptorT{}))
		{
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
	else if constexpr (std::is_same_v<bool, MemberT>) // bool
	{
		ImGui::Checkbox(DescriptorT::name.c_str(), _class);
	}
	else if (std::is_integral_v<MemberT> || std::is_floating_point_v<MemberT>)
	{
		DisplayIntOrFloat<TypeT, MemberT, DescriptorT>(_class);
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

template<typename TypeT, typename MemberT, typename DescriptorT>
void DisplayType::DisplayIntOrFloat(MemberT* _member)
{
	int type = ImGuiDataType_S8;
	if constexpr (std::is_same_v<std::int8_t, MemberT>) // int_8
	{
		type = ImGuiDataType_S8;
	}
	else if constexpr (std::is_same_v<std::int16_t, MemberT>) // int_16
	{
		type = ImGuiDataType_S16;
	}
	else if constexpr (std::is_same_v<std::int32_t, MemberT>) // int_32
	{
		type = ImGuiDataType_S32;
	}
	else if constexpr (std::is_same_v<std::uint8_t, MemberT>) // uint_8
	{
		type = ImGuiDataType_U8;
	}
	else if constexpr (std::is_same_v<std::uint16_t, MemberT>) // uint_16
	{
		type = ImGuiDataType_U16;
	}
	else if constexpr (std::is_same_v<std::uint32_t, MemberT>) // uint_32
	{
		type = ImGuiDataType_U32;
	}
	else if constexpr (std::is_same_v<float, MemberT>) // float 
	{
		type = ImGuiDataType_Float;
	}
	else if constexpr (std::is_same_v<double, MemberT>) // double
	{
		type = ImGuiDataType_Double;
	}

	if constexpr (refl::descriptor::has_attribute<Range>(DescriptorT{}))
		ImGui::SliderScalar(DescriptorT::name.c_str(), type, _member, &refl::descriptor::get_attribute<Range>(DescriptorT{}).min, &refl::descriptor::get_attribute<Range>(DescriptorT{}).max);
	else
		ImGui::DragScalar(DescriptorT::name.c_str(), type, _member);
}
