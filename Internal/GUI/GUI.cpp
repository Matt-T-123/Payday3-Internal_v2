#include "pch.h"
#include "../Features/Player/Player.hpp"
#include "../Features/Visuals/Visuals.hpp"
#include "../Features/Aimbot/Aimbot.hpp"

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
			GuiSidebar->AddElement(GuiMiscSeperator.get());
			GuiSidebar->AddElement(GuiConfig.get());

			if (pPlayer)
				GuiSidebar->InsertElementAfter(pPlayer->GetMenuButton(), "PLAYER_SEPERATOR");
			if (pVisuals)
				GuiSidebar->InsertElementAfter(pVisuals->GetMenuButton(), "PLAYER_BUTTON");
			if (pAimbot)
				GuiSidebar->InsertElementAfter(pAimbot->GetMenuButton(), "VISUALS_BUTTON##VISUALS_FEATURE");

			// Set the default page (optional - defaults to 0 if not set)
			ElementBase::SetDefaultPage(GuiConfig->GetPageId());

			GuiConfigPage->SetPageId(GuiConfig->GetPageId());
			GuiSaveConfig->SetCallback([]() {
				Framework::config->SaveConfig();
			});
			GuiConfigPage->AddElement(GuiSaveConfig.get());
			GuiLoadConfig->SetCallback([]() {
				Framework::config->LoadConfig();
			});
			GuiConfigPage->AddElement(GuiLoadConfig.get());

			GuiHeaderGroup->AddElement(GuiBody.get());
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

			// Load the config
			Framework::config->LoadConfig();
		});
	}
  
	//
	// End Other Render Stuff
	//
}
