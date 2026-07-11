#include "pch.h"
#include "Visuals.hpp"

bool Visuals::SetupMenu()
{
	Localization::AddToLocale("ENG", std::initializer_list<std::pair<size_t, std::string>>{
		{ "VISUALS_BUTTON"Hashed, "Visuals" },
		{ "VISUALS_TAB1"Hashed, "ESP" },
		{ "VISUALS_TAB1_LEFT"Hashed, "ESP" },
		{ "VISUALS_TAB1_RIGHT"Hashed, "Colors" },

		{ "VISUALS_BOUNDING_BOX"Hashed, "Bounding Box" },
		{ "VISUALS_BOUNDING_BOX_COLOR"Hashed, "Bounding Box Color" },
		{ "VISUALS_HEALTH_BAR"Hashed, "Health Bar" },
		{ "VISUALS_HEALTH_BAR_COLOR"Hashed, "Health Bar Color" },
		{ "VISUALS_ARMOR_BAR"Hashed, "Armor Bar" },
		{ "VISUALS_ARMOR_BAR_COLOR"Hashed, "Armor Bar Color" },
		{ "VISUALS_SKELETON"Hashed, "Skeleton" },
		{ "VISUALS_SKELETON_COLOR"Hashed, "Skeleton Color" },
		{ "VISUALS_HIGHLIGHT"Hashed, "Highlight" },
		{ "VISUALS_HIGHLIGHT_COLOR"Hashed, "Highlight Color" },
		{ "VISUALS_KEY_ITEM"Hashed, "Key Items" },
		{ "VISUALS_KEY_ITEM_COLOR"Hashed, "Key Items Color" }
	});

	return true;
}

void Visuals::HandleMenu()
{
	static std::once_flag onceflag;
	std::call_once(onceflag, [this]() {
		auto pHeaderGroup = static_cast<HeaderGroup*>(Framework::menu->GetChild("HEADER_GROUP"));
		if (pHeaderGroup)
			pHeaderGroup->AddHeaders(Visuals::s_iVisualsPageId, { "VISUALS_TAB1"Hashed});

		m_pTab1Left->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pTab1Right->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});

		m_pTab1Left->AddElement(m_pBoundingBox.get());
		m_pTab1Right->AddElement(m_pBoundingBoxColor.get());
		m_pTab1Left->AddElement(m_pHealthBar.get());
		m_pTab1Right->AddElement(m_pHealthBarColor.get());
		m_pTab1Left->AddElement(m_pArmorBar.get());
		m_pTab1Right->AddElement(m_pArmorBarColor.get());
		m_pTab1Left->AddElement(m_pSkeleton.get());
		m_pTab1Right->AddElement(m_pSkeletonColor.get());
		m_pTab1Left->AddElement(m_pHighlight.get());
		m_pTab1Right->AddElement(m_pHighlightColor.get());
		m_pTab1Left->AddElement(m_pKeyItem.get());
		m_pTab1Right->AddElement(m_pKeyItemColor.get());
		m_pTab1Group->AddElement(m_pTab1Left.get());
		m_pTab1Group->AddElement(m_pTab1Right.get());

		m_pTab1Page->AddElement(m_pTab1Group.get());

		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pTab1Page.get());
	});
}

void Visuals::Run()
{
}
