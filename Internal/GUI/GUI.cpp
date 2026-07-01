#include "pch.h"

void GUI::Render()
{
	if (!Framework::bInitalized)
		return;

	if (ImGui::IsKeyPressed(Framework::keyMenuKey) || ImGui::IsKeyPressed(ImGuiKey_GamepadStart))
	{
		bMenuOpen = !bMenuOpen;
		ImGui::GetIO().MouseDrawCursor = GUI::bMenuOpen;

		if (ImGui::GetIO().MouseDrawCursor)
			SetCursor(NULL);
	}

	if (ImGui::IsKeyPressed(Framework::keyConsoleKey))
		Framework::console->ToggleVisibility();

	if (ImGui::IsKeyPressed(Framework::keyUnloadKey1) || ImGui::IsKeyPressed(Framework::keyUnloadKey2))
		Framework::bShouldRun = false;

	for (auto& pFeature : Framework::g_vecFeatures)
		pFeature->HandleInput();

	if (bMenuOpen)
	{
		static std::once_flag onceflag;
		std::call_once(onceflag, []() {
			GuiSidebar->SetPushVarsCallback([]() {
				ImGuiStyle& imStyle = ImGui::GetStyle();
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, imStyle.ChildRounding);
				ImGui::PushStyleColor(ImGuiCol_FrameBg, imStyle.Colors[ImGuiCol_Header]);
			});

			GuiSidebar->SetPopVarsCallback([]() {
				ImGui::PopStyleColor();
				ImGui::PopStyleVar();
			});

			GuiSidebar->AddElement(GuiPlayerSeperator.get());
			GuiSidebar->AddElement(GuiPlayer.get());
			GuiSidebar->AddElement(GuiAimbot.get());
			GuiSidebar->AddElement(GuiVisuals.get());
			GuiSidebar->AddElement(GuiMiscSeperator.get());
			GuiSidebar->AddElement(GuiDeveloper.get());
			GuiSidebar->AddElement(GuiConfig.get());

			// Set the default page (optional - defaults to 0 if not set)
			ElementBase::SetDefaultPage(GuiPlayer->GetPageId());

			auto pHeaderGroup = static_cast<HeaderGroup*>(GuiHeaderGroup.get());
			if (pHeaderGroup)
			{
				pHeaderGroup->AddHeaders(GuiPlayer->GetPageId(), { "PLAYER_MAIN"Hashed, "PLAYER_GUNMODS"Hashed });
				pHeaderGroup->AddHeaders(GuiAimbot->GetPageId(), { "AIMBOT_MAIN"Hashed });
				pHeaderGroup->AddHeaders(GuiVisuals->GetPageId(), { "VISUALS_MAIN"Hashed });
				pHeaderGroup->AddHeaders(GuiDeveloper->GetPageId(), { "MENU_MAIN"Hashed });
				pHeaderGroup->AddHeaders(GuiConfig->GetPageId(), { "CONFIG_MAIN"Hashed });
			}

			GuiPlayerSelfPage->SetPageId(GuiPlayer->GetPageId());
			GuiPlayerSelfPage->SetSubPageId(0);
			GuiPlayerSelfPage->AddElement(GuiPlayerSelfLayout.get());
			GuiPlayerSelfLayout->AddElement(GuiPlayerHeader.get());
			GuiPlayerSelfLayout->AddElement(GuiPlayerGodmode.get());
			GuiPlayerSelfLayout->AddElement(GuiPlayerReload.get());
			GuiPlayerSelfLayout->AddElement(GuiPlayerMelee.get());

			GuiPlayerGunmodsPage->SetPageId(GuiPlayer->GetPageId());
			GuiPlayerGunmodsPage->SetSubPageId(1);
			GuiPlayerGunmodsPage->AddElement(GuiPlayerGunmodsLayout.get());
			GuiPlayerGunmodsLayout->AddElement(GuiPlayerHeader.get());
			GuiPlayerGunmodsLayout->AddElement(GuiPlayerNoRecoil.get());
			GuiPlayerGunmodsLayout->AddElement(GuiPlayerNoSpread.get());

			GuiAimbotPage->SetPageId(GuiAimbot->GetPageId());
			GuiAimbotPage->AddElement(GuiAimbotLayout.get());
			GuiAimbotLayout->AddElement(GuiAimbotHeader.get());
			GuiAimbotLayout->AddElement(GuiAimbotSilent.get());
			GuiAimbotLayout->AddElement(GuiAimbotTrigger.get());

			GuiVisualsPage->SetPageId(GuiVisuals->GetPageId());
			GuiVisualsPage->AddElement(GuiEspLayout.get());
			GuiEspLayout->AddElement(GuiEspHeader.get());
			GuiEspLayout->AddElement(GuiEspEnabled.get());
			GuiVisualsPage->AddElement(GuiWorldLayout.get());
			GuiWorldLayout->AddElement(GuiWorldHeader.get());
			GuiWorldLayout->AddElement(GuiWorldEnabled.get());

			GuiDeveloperPage->SetPageId(GuiDeveloper->GetPageId());
			GuiDeveloperPage->AddElement(GuiMenuLayout.get());
			GuiMenuLayout->AddElement(GuiMenuHeader.get());
			GuiMenuLayout->AddElement(GuiMenuAnimated.get());
			GuiMenuLayout->AddElement(GuiMenuTheme.get());
			GuiMenuTheme->AddOption("Dark");
			GuiMenuTheme->AddOption("Neon");
			GuiMenuTheme->AddOption("Classic");
			GuiMenuLayout->AddElement(GuiMenuOpacity.get());

			GuiConfigPage->SetPageId(GuiConfig->GetPageId());
			GuiConfigPage->AddElement(GuiConfigLayout.get());
			GuiConfigLayout->AddElement(GuiConfigSectionHeader.get());
			GuiConfigLayout->AddElement(GuiConfigSave.get());
			GuiConfigLayout->AddElement(GuiConfigLoad.get());
			GuiConfigLayout->AddElement(GuiConfigAutoSave.get());

			GuiUnloadButton->SetCallback([]() {
				Framework::bShouldRun = false;
			});
			GuiDeveloperPage->AddElement(GuiUnloadButton.get());
			GuiConsoleVisibility->SetCallback([]() {
				Framework::console->ToggleVisibility();
				GuiConsoleVisibility->SetName(Framework::console->GetVisibility() ? "CONSOLE_HIDE"Hashed : "CONSOLE_SHOW"Hashed);
			});
			GuiDeveloperPage->AddElement(GuiConsoleVisibility.get());
			GuiLocalization->SetCallback([]() {
				std::vector<Locale_t> vecLocales = Localization::GetLocales();
				for (size_t i = 0; i < vecLocales.size(); ++i)
				{
					bool bSelected = Localization::GetCurrentLocaleIndex() == i;
					Locale_t stLocale = vecLocales.at(i);
					if (ImAdd::Selectable(stLocale.sKey.c_str(), bSelected))
					{
						Localization::SetLocale(stLocale.ullKeyHash);
						GuiLocalization->SetPreviewLabel(stLocale.sKey.c_str());
					}

					if (bSelected)
						ImGui::SetItemDefaultFocus();
				}
			});
			GuiDeveloperPage->AddElement(GuiLocalization.get());

			GuiConfigPage->SetPageId(GuiConfig->GetPageId());
			GuiConfigSave->SetCallback([]() {
				Framework::config->SaveConfig();
			});
			GuiConfigPage->AddElement(GuiConfigSave.get());
			GuiConfigLoad->SetCallback([]() {
				Framework::config->LoadConfig();
			});
			GuiConfigPage->AddElement(GuiConfigLoad.get());

			GuiHeaderGroup->AddElement(GuiBody.get());
			GuiBody->AddElement(GuiPlayerSelfPage.get());
			GuiBody->AddElement(GuiPlayerGunmodsPage.get());
			GuiBody->AddElement(GuiAimbotPage.get());
			GuiBody->AddElement(GuiVisualsPage.get());
			GuiBody->AddElement(GuiDeveloperPage.get());
			GuiBody->AddElement(GuiConfigPage.get());
		});

		if (!GuiSidebar->HasParent()) {
			Framework::menu->AddElement(GuiSidebar.get());
			Framework::menu->AddElement(GuiHeaderGroup.get());
		}

		for (auto& pFeature : Framework::g_vecFeatures)
			pFeature->HandleMenu();

		Framework::menu->Render();
	}

	//
	//	Other Render Stuff
	//

	for (auto& pFeature : Framework::g_vecFeatures)
		pFeature->Render();

	// Gui init shit 
	if (Framework::menu->HasChildren()) // We have to wait till the menu has children to do the init
	{
		std::call_once(LoadFlag, []() {
			// The menu is opened on load so spawn the mouse
			ImGui::GetIO().MouseDrawCursor = GUI::bMenuOpen;
			if (ImGui::GetIO().MouseDrawCursor)
				SetCursor(NULL);

			GuiLocalization->SetPreviewLabel((Localization::GetInstance())->GetLocales()[(Localization::GetInstance())->GetCurrentLocaleIndex()].sKey.c_str());

			// Load the config
			Framework::config->LoadConfig();
		});
	}
  
	//
	// End Other Render Stuff
	//
}