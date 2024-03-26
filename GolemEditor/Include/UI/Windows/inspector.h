#pragma once

#include "UI/Windows/window.h"
#include "Core/gameobject.h"
#include "Core/transform.h"
#include "Reflection/refl.hpp"
#include <iostream>
#include "imgui.h"
#include "imgui_stdlib.h"

class GolemEngine;

class Inspector : public Window
{
public:
	Inspector(std::string _name);
	~Inspector();

	void Update(GolemEngine* _golemEngine) override;

	template<typename TypeT>
	void DisplayField(TypeT* _class);
};



template<typename TypeT>
void Inspector::DisplayField(TypeT* _class)
{
	constexpr auto type = refl::reflect<TypeT>();
	for_each(type.members, [&]<typename DescriptorT>(const DescriptorT)
	{
		using MemberT = DescriptorT::value_type;

		if constexpr (std::is_pointer_v<MemberT>)
		{
			DisplayField(DescriptorT::get(_class));
		}
		// Display Imgui with all original types
		else if constexpr (std::is_same_v<std::string, MemberT>) // string
		{
			ImGui::InputText(DescriptorT::name.c_str(), &DescriptorT::get(_class));
		}
		else if constexpr (std::is_same_v<std::int8_t, MemberT>) // int_8
		{
			ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_S8, &DescriptorT::get(_class));
		}
		else if constexpr (std::is_same_v<std::int16_t, MemberT>) // int_16
		{
			ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_S16, &DescriptorT::get(_class));
		}
		else if constexpr (std::is_same_v<std::int32_t, MemberT>) // int_32
		{
			ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_S32, &DescriptorT::get(_class));
		}
		else if constexpr (std::is_same_v<std::uint8_t, MemberT>) // uint_8
		{
			ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_U8, &DescriptorT::get(_class));
		}
		else if constexpr (std::is_same_v<std::uint16_t, MemberT>) // uint_16
		{
			ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_U16, &DescriptorT::get(_class));
		}
		else if constexpr (std::is_same_v<std::uint32_t, MemberT>) // uint_32
		{
			ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_U32, &DescriptorT::get(_class));
		}
		else if constexpr (std::is_same_v<float, MemberT>) // float 
		{
			ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_Float, &DescriptorT::get(_class));
		}
		else if constexpr (std::is_same_v<double, MemberT>) // double
		{
			ImGui::DragScalar(DescriptorT::name.c_str(), ImGuiDataType_Double, &DescriptorT::get(_class));
		}
		else if constexpr (std::is_same_v<bool, MemberT>) // bool
		{
			ImGui::Checkbox(DescriptorT::name.c_str(), &DescriptorT::get(_class));
		}
		else if constexpr (std::is_same_v<Vector3, MemberT>)
		{
			ImGui::DragFloat3(DescriptorT::name.c_str(), &DescriptorT::get(_class).x, .1f);
		}
	});
}