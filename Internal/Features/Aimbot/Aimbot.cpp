#include "pch.h"
#include "Aimbot.hpp"

bool Aimbot::SetupMenu()
{
	Localization::AddToLocale("ENG", std::initializer_list<std::pair<size_t, std::string>>{
		{ "AIMBOT_BUTTON"Hashed, "Aimbot" },
		{ "AIMBOT_TAB1"Hashed, "Main" },
		{ "AIMBOT_TAB1_LEFT"Hashed, "Aimbot" },
		{ "AIMBOT_TAB1_RIGHT"Hashed, "Options" },

		{ "AIMBOT_ENABLED"Hashed, "Aimbot" },
		{ "AIMBOT_FOV_ENABLED"Hashed, "FOV Circle" },
		{ "AIMBOT_TYPE"Hashed, "Aimbot Type" },
		{ "AIMBOT_FOV"Hashed, "FOV" },
		{ "AIMBOT_SMOOTHING"Hashed, "Smoothing" }
	});

	return true;
}

void Aimbot::HandleMenu()
{
	static std::once_flag onceflag;

	std::call_once(onceflag, [this]() {
		auto pHeaderGroup = static_cast<HeaderGroup*>(Framework::menu->GetChild("HEADER_GROUP"));

		if (pHeaderGroup)
			pHeaderGroup->AddHeaders(Aimbot::s_iAimbotPageId, { "AIMBOT_TAB1"Hashed});

		m_pTab1Left->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pTab1Right->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});

		m_pAimbotType->AddOption("Silent");
		m_pAimbotType->AddOption("Snapping");

		m_pTab1Left->AddElement(m_pAimbotEnabled.get());
		m_pTab1Left->AddElement(m_pAimbotFOVEnabled.get());

		m_pTab1Right->AddElement(m_pAimbotType.get());
		m_pTab1Right->AddElement(m_pFOV.get());
		m_pTab1Right->AddElement(m_pSmoothing.get());

		m_pTab1Group->AddElement(m_pTab1Left.get());
		m_pTab1Group->AddElement(m_pTab1Right.get());

		m_pTab1Page->AddElement(m_pTab1Group.get());

		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pTab1Page.get());
	});
}

void Aimbot::Run()
{
}
