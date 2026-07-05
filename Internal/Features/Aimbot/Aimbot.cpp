#include "pch.h"
#include "Aimbot.hpp"

bool Aimbot::SetupMenu()
{
	Localization::AddToLocale("ENG", std::initializer_list<std::pair<size_t, std::string>>{
		{ "AIMBOT_BUTTON"Hashed, "Aimbot" },
		{ "AIMBOT_MAIN"Hashed, "Main" },
		{ "AIMBOT_ADVANCED"Hashed, "Advanced" },
		{ "AIMBOT_MAIN_LEFT"Hashed, "Control" },
		{ "AIMBOT_MAIN_RIGHT"Hashed, "Options" },
		{ "AIMBOT_ADVANCED_LEFT"Hashed, "Tuning" },
		{ "AIMBOT_ADVANCED_RIGHT"Hashed, "Actions" },
		{ "AIMBOT_ENABLED"Hashed, "Enabled" },
		{ "AIMBOT_MODE"Hashed, "Mode" },
		{ "AIMBOT_STRENGTH"Hashed, "Strength" },
		{ "AIMBOT_PROFILE"Hashed, "Profile" },
		{ "AIMBOT_ACTION"Hashed, "Apply" }
	});

	return true;
}

void Aimbot::HandleMenu()
{
	static std::once_flag onceflag;

	std::call_once(onceflag, [this]() {
		auto pHeaderGroup = static_cast<HeaderGroup*>(Framework::menu->GetChild("HEADER_GROUP"));

		if (pHeaderGroup)
			pHeaderGroup->AddHeaders(Aimbot::s_iAimbotPageId, { "AIMBOT_MAIN"Hashed, "AIMBOT_ADVANCED"Hashed });

		m_pMainLeft->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});
		m_pMainRight->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});
		m_pAdvancedLeft->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});
		m_pAdvancedRight->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});

		m_pProfile->AddOption("Default");
		m_pProfile->AddOption("Balanced");
		m_pProfile->AddOption("Custom");

		m_pMainLeft->AddElement(m_pEnabled.get());
		m_pMainLeft->AddElement(m_pMode.get());
		m_pMainRight->AddElement(m_pStrength.get());
		m_pMainGroup->AddElement(m_pMainLeft.get());
		m_pMainGroup->AddElement(m_pMainRight.get());

		m_pAdvancedLeft->AddElement(m_pProfile.get());
		m_pAdvancedRight->AddElement(m_pAction.get());
		m_pAdvancedGroup->AddElement(m_pAdvancedLeft.get());
		m_pAdvancedGroup->AddElement(m_pAdvancedRight.get());

		m_pMainPage->AddElement(m_pMainGroup.get());
		m_pAdvancedPage->AddElement(m_pAdvancedGroup.get());

		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pMainPage.get());
		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pAdvancedPage.get());
	});
}

void Aimbot::Run()
{
}
