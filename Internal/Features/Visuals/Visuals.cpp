#include "pch.h"
#include "Visuals.hpp"

bool Visuals::SetupMenu()
{
	Localization::AddToLocale("ENG", std::initializer_list<std::pair<size_t, std::string>>{
		{ "VISUALS_BUTTON##VISUALS_FEATURE"Hashed, "Visuals" },
		{ "VISUALS_MAIN"Hashed, "Main" },
		{ "VISUALS_ADVANCED"Hashed, "Advanced" },
		{ "VISUALS_MAIN_LEFT##VISUALS_FEATURE"Hashed, "Overlay" },
		{ "VISUALS_MAIN_RIGHT##VISUALS_FEATURE"Hashed, "Colors" },
		{ "VISUALS_ADVANCED_LEFT##VISUALS_FEATURE"Hashed, "Layout" },
		{ "VISUALS_ADVANCED_RIGHT##VISUALS_FEATURE"Hashed, "Effects" },
		{ "VISUALS_ENABLED##VISUALS_FEATURE"Hashed, "Enabled" },
		{ "VISUALS_MODE##VISUALS_FEATURE"Hashed, "Mode" },
		{ "VISUALS_ACCENT##VISUALS_FEATURE"Hashed, "Accent" },
		{ "VISUALS_OPACITY##VISUALS_FEATURE"Hashed, "Opacity" },
		{ "VISUALS_ACTION##VISUALS_FEATURE"Hashed, "Apply" }
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
			return ImVec2(ImGui::GetWindowWidth() * 0.48f, 128.f);
		});
		m_pMainRight->SetCallback([]() {
			return ImVec2(ImGui::GetWindowWidth() * 0.48f, 128.f);
		});
		m_pAdvancedLeft->SetCallback([]() {
			return ImVec2(ImGui::GetWindowWidth() * 0.48f, 96.f);
		});
		m_pAdvancedRight->SetCallback([]() {
			return ImVec2(ImGui::GetWindowWidth() * 0.48f, 96.f);
		});

		m_pMode->AddOption("Compact");
		m_pMode->AddOption("Balanced");
		m_pMode->AddOption("Detailed");

		m_pMainLeft->AddElement(m_pEnabled.get());
		m_pMainLeft->AddElement(m_pMode.get());
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
