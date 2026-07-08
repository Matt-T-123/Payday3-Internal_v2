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

		m_pMainLeft->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pMainRight->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});
		m_pAdvancedLeft->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pAdvancedRight->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});

		m_pMainLeft->AddElement(m_pEnabled.get());
		m_pMainRight->AddElement(m_pAccent.get());
		m_pMainGroup->AddElement(m_pMainLeft.get());
		m_pMainGroup->AddElement(m_pMainRight.get());

		m_pAdvancedLeft->AddElement(m_pOpacity.get());
		m_pAdvancedRight->AddElement(m_pAction.get());
		m_pAdvancedGroup->AddElement(m_pAdvancedLeft.get());
		m_pAdvancedGroup->AddElement(m_pAdvancedRight.get());

		m_pMainPage->AddElement(m_pMainGroup.get());
		m_pAdvancedPage->AddElement(m_pAdvancedGroup.get());

		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pMainPage.get());
		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pAdvancedPage.get());
	});
}

void Visuals::Run()
{
}
