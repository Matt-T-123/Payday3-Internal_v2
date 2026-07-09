#include "pch.h"
#include "Visuals.hpp"

bool Visuals::SetupMenu()
{
	Localization::AddToLocale("ENG", std::initializer_list<std::pair<size_t, std::string>>{
		{ "VISUALS_BUTTON"Hashed, "Visuals" },
		{ "VISUALS_MAIN"Hashed, "Main" },
		{ "VISUALS_ADVANCED"Hashed, "Advanced" },
		{ "VISUALS_MAIN_LEFT"Hashed, "Overlay" },
		{ "VISUALS_MAIN_RIGHT"Hashed, "Colors" },
		{ "VISUALS_ADVANCED_LEFT"Hashed, "Layout" },
		{ "VISUALS_ADVANCED_RIGHT"Hashed, "Effects" },
		{ "VISUALS_ENABLED"Hashed, "Enabled" },
		{ "VISUALS_MODE"Hashed, "Mode" },
		{ "VISUALS_ACCENT"Hashed, "Accent" },
		{ "VISUALS_OPACITY"Hashed, "Opacity" },
		{ "VISUALS_ACTION"Hashed, "Apply" }
	});

	return true;
}

void Visuals::HandleMenu()
{
	static std::once_flag onceflag;
	std::call_once(onceflag, [this]() {
		auto pHeaderGroup = static_cast<HeaderGroup*>(Framework::menu->GetChild("HEADER_GROUP"));
		if (pHeaderGroup)
			pHeaderGroup->AddHeaders(Visuals::s_iVisualsPageId, { "VISUALS_MAIN"Hashed, "VISUALS_ADVANCED"Hashed });

		m_pTab1Left->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pTab1Right->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});
		m_pTab2Left->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pTab2Right->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});

		m_pTab1Left->AddElement(m_pEnabled.get());
		m_pTab1Right->AddElement(m_pAccent.get());
		m_pTab1Group->AddElement(m_pTab1Left.get());
		m_pTab1Group->AddElement(m_pTab1Right.get());

		m_pTab2Left->AddElement(m_pOpacity.get());
		m_pTab2Right->AddElement(m_pAction.get());
		m_pTab2Group->AddElement(m_pTab2Left.get());
		m_pTab2Group->AddElement(m_pTab2Right.get());

		m_pTab1Page->AddElement(m_pTab1Group.get());
		m_pTab2Page->AddElement(m_pTab2Group.get());

		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pTab1Page.get());
		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pTab2Page.get());
	});
}

void Visuals::Run()
{
}
