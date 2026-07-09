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

		m_pTab1Left->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});
		m_pTab1Right->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});
		m_pTab2Left->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});
		m_pTab2Right->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});

		m_pProfile->AddOption("Default");
		m_pProfile->AddOption("Balanced");
		m_pProfile->AddOption("Custom");

		m_pTab1Left->AddElement(m_pEnabled.get());
		m_pTab1Left->AddElement(m_pMode.get());
		m_pTab1Right->AddElement(m_pStrength.get());
		m_pTab1Group->AddElement(m_pTab1Left.get());
		m_pTab1Group->AddElement(m_pTab1Right.get());

		m_pTab2Left->AddElement(m_pProfile.get());
		m_pTab2Right->AddElement(m_pAction.get());
		m_pTab2Group->AddElement(m_pTab2Left.get());
		m_pTab2Group->AddElement(m_pTab2Right.get());

		m_pTab1Page->AddElement(m_pTab1Group.get());
		m_pTab2Page->AddElement(m_pTab2Group.get());

		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pTab1Page.get());
		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pTab2Page.get());
	});
}

void Aimbot::Run()
{
}
