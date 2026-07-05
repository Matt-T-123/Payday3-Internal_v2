#include "pch.h"
#include "UI.hpp"

bool UI::SetupMenu()
{
	Localization::AddToLocale("ENG", std::initializer_list<std::pair<size_t, std::string>>{
		{ "UI"Hashed, "UI" },
		{ "UI_BUTTON"Hashed, "UI" },
		{ "UI_MAIN"Hashed, "Main" },
		{ "UI_UNLOAD_BUTTON"Hashed, "Unload" },
		{ "UI_CONSOLE_SHOW"Hashed, "Show Console" },
		{ "UI_CONSOLE_HIDE"Hashed, "Hide Console" },
		{ "UI_LANGUAGE"Hashed, "Language" }
	});

	return true;
}

void UI::HandleMenu()
{
	static std::once_flag onceflag;
	
	std::call_once(onceflag, [this]() {
		Framework::menu->GetChild("SIDEBAR")->InsertElementAfter(m_pMenuButton.get(), "MISC_SEPERATOR");
		auto pHeaderGroup = static_cast<HeaderGroup*>(Framework::menu->GetChild("HEADER_GROUP"));
		if (pHeaderGroup)
			pHeaderGroup->AddHeaders(UI::s_iUIPageId, { "UI_MAIN"Hashed });

		m_pUnloadButton->SetCallback([]() {
			Framework::bShouldRun = false;
		});
		m_pUIPage->AddElement(m_pUnloadButton.get());

		m_pConsoleVisibility->SetCallback([this]() {
			Framework::console->ToggleVisibility();
			m_pConsoleVisibility->SetName(Framework::console->GetVisibility() ? "UI_CONSOLE_HIDE"Hashed : "UI_CONSOLE_SHOW"Hashed);
		});
		m_pUIPage->AddElement(m_pConsoleVisibility.get());

		m_pLocalization->SetCallback([this]() {
			std::vector<Locale_t> vecLocales = Localization::GetLocales();
			for (size_t i = 0; i < vecLocales.size(); ++i)
			{
				bool bSelected = Localization::GetCurrentLocaleIndex() == i;
				Locale_t stLocale = vecLocales.at(i);
				if (ImAdd::Selectable(stLocale.sKey.c_str(), bSelected))
				{
					Localization::SetLocale(stLocale.ullKeyHash);
					m_pLocalization->SetPreviewLabel(stLocale.sKey.c_str());
				}

				if (bSelected)
					ImGui::SetItemDefaultFocus();
			}
		});
		m_pLocalization->SetPreviewLabel(Localization::GetLocales()[Localization::GetCurrentLocaleIndex()].sKey.c_str());
		m_pUIPage->AddElement(m_pLocalization.get());

		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pUIPage.get());
	});
}

void UI::Run()
{

}
