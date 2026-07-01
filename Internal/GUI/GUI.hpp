#pragma once
#include "pch.h"
#include "Menu/Menu.hpp"

// Colors for ImGui
inline ImU32 Black = ImGui::ColorConvertFloat4ToU32({ 0.f, 0.f, 0.f, 1.f });
inline ImU32 White = ImGui::ColorConvertFloat4ToU32({ 1.f, 1.f, 1.f, 1.f });

inline ImU32 Red = ImGui::ColorConvertFloat4ToU32({ 1.f, 0.f, 0.f, 1.f });
inline ImU32 Green = ImGui::ColorConvertFloat4ToU32({ 0.f, 1.f, 0.f, 1.f });
inline ImU32 Blue = ImGui::ColorConvertFloat4ToU32({ 0.f, 0.f, 1.f, 1.f });

inline ImU32 Cyan = ImGui::ColorConvertFloat4ToU32({ 0.f, 1.f, 1.f, 1.f });
inline ImU32 Gold = ImGui::ColorConvertFloat4ToU32({ 1.f, .84f, 0.f, 1.f });
inline ImU32 Orange = ImGui::ColorConvertFloat4ToU32({ 1.f, .65f, 0.f, 1.f });
inline ImU32 Purple = ImGui::ColorConvertFloat4ToU32({ .5f, 0.f, .5f, 1.f });
inline ImU32 Magenta = ImGui::ColorConvertFloat4ToU32({ 1.f, 0.f, 1.f, 1.f });

inline ImU32 Gray = ImGui::ColorConvertFloat4ToU32({ .8f, .8f, .8f, 1.f });

namespace GUI
{
	inline bool bMenuOpen = true;

	inline float sWIDTH = float(GetSystemMetrics(SM_CXSCREEN));
	inline float sHEIGHT = float(GetSystemMetrics(SM_CYSCREEN));

	inline std::unique_ptr<Child> GuiSidebar = std::make_unique<Child>(std::string("SIDEBAR"), "SIDEBAR"Hashed, ElementBase::Style_t{
		.vec2Size = ImVec2(160.f, 0.f), .iFlags = ImGuiChildFlags_Border }, ImGuiWindowFlags_NoBackground);
	inline std::unique_ptr<SeperatorText> GuiPlayerSeperator = std::make_unique<SeperatorText>(std::string("PLAYER_SEPERATOR"), "PLAYER_SEPERATOR"Hashed);
	inline std::unique_ptr<SeperatorText> GuiMiscSeperator = std::make_unique<SeperatorText>(std::string("MISC_SEPERATOR"), "MISC_SEPERATOR"Hashed);
	inline std::unique_ptr<RadioButtonIcon> GuiPlayer = std::make_unique<RadioButtonIcon>(std::string("PLAYER_BUTTON"), "PLAYER_BUTTON"Hashed, ElementBase::Style_t{
		.vec2Size = ImVec2(-0.1f, 0) }, ICON_FA_CIRCLE, true);
	inline std::unique_ptr<RadioButtonIcon> GuiAimbot = std::make_unique<RadioButtonIcon>(std::string("AIMBOT_BUTTON"), "AIMBOT_BUTTON"Hashed, ElementBase::Style_t{
		.vec2Size = ImVec2(-0.1f, 0) }, ICON_FA_CROSSHAIRS, true);
	inline std::unique_ptr<RadioButtonIcon> GuiVisuals = std::make_unique<RadioButtonIcon>(std::string("VISUALS_BUTTON"), "VISUALS_BUTTON"Hashed, ElementBase::Style_t{
		.vec2Size = ImVec2(-0.1f, 0) }, ICON_FA_EYE, true);
	inline std::unique_ptr<RadioButtonIcon> GuiDeveloper = std::make_unique<RadioButtonIcon>(std::string("DEVELOPER_BUTTON"), "MENU_BUTTON"Hashed, ElementBase::Style_t{
		.vec2Size = ImVec2(-0.1f, 0) }, ICON_FA_TERMINAL, true);
	inline std::unique_ptr<RadioButtonIcon> GuiConfig = std::make_unique<RadioButtonIcon>(std::string("CONFIG_BUTTON"), "CONFIG_BUTTON"Hashed, ElementBase::Style_t{
		.vec2Size = ImVec2(-0.1f, 0) }, ICON_FA_FLOPPY_DISK, true);
	
	// Headers are now added dynamically in GUI.cpp
	inline std::vector<ElementBase::Header_t> HeaderGroupHeaders = {};

	inline std::unique_ptr<HeaderGroup> GuiHeaderGroup = std::make_unique<HeaderGroup>(std::string("HEADER_GROUP"), "HEADER_GROUP"Hashed, ElementBase::Style_t{
		.vec2Size = ImVec2(-0.1f, 0), }, HeaderGroupHeaders);

	inline std::unique_ptr<Body> GuiBody = std::make_unique<Body>(std::string("BODY"), ElementBase::Style_t{
		.vec2Size = ImVec2(-0.1f, 0), });

	// Player / Aimbot / Visuals / Menu / Config Page Elements
	inline std::unique_ptr<Page> GuiPlayerPage = std::make_unique<Page>("PLAYER_PAGE", ElementBase::Style_t(), 0, 0);
	inline std::unique_ptr<Page> GuiPlayerSelfPage = std::make_unique<Page>("PLAYER_SELF_PAGE", ElementBase::Style_t(), 0, 0);
	inline std::unique_ptr<Page> GuiPlayerGunmodsPage = std::make_unique<Page>("PLAYER_GUNMODS_PAGE", ElementBase::Style_t(), 0, 1);
	inline std::unique_ptr<Page> GuiAimbotPage = std::make_unique<Page>("AIMBOT_PAGE", ElementBase::Style_t(), 0, 0);
	inline std::unique_ptr<Page> GuiVisualsPage = std::make_unique<Page>("VISUALS_PAGE", ElementBase::Style_t(), 0, 0);
	inline std::unique_ptr<Page> GuiVisualsEspPage = std::make_unique<Page>("VISUALS_ESP_PAGE", ElementBase::Style_t(), 0, 0);
	inline std::unique_ptr<Page> GuiVisualsWorldPage = std::make_unique<Page>("VISUALS_WORLD_PAGE", ElementBase::Style_t(), 0, 1);

	inline std::unique_ptr<Group> GuiPlayerSelfLayout = std::make_unique<Group>("PLAYER_SELF_LAYOUT", ElementBase::Style_t{});
	inline std::unique_ptr<Group> GuiPlayerGunmodsLayout = std::make_unique<Group>("PLAYER_GUNMODS_LAYOUT", ElementBase::Style_t{});
	inline std::unique_ptr<Group> GuiAimbotLayout = std::make_unique<Group>("AIMBOT_LAYOUT", ElementBase::Style_t{});
	inline std::unique_ptr<Group> GuiEspLayout = std::make_unique<Group>("ESP_LAYOUT", ElementBase::Style_t{});
	inline std::unique_ptr<Group> GuiWorldLayout = std::make_unique<Group>("WORLD_LAYOUT", ElementBase::Style_t{});
	inline std::unique_ptr<Group> GuiMenuLayout = std::make_unique<Group>("MENU_LAYOUT", ElementBase::Style_t{});
	inline std::unique_ptr<Group> GuiConfigLayout = std::make_unique<Group>("CONFIG_LAYOUT", ElementBase::Style_t{});

	inline std::unique_ptr<SeperatorText> GuiPlayerHeader = std::make_unique<SeperatorText>("PLAYER_HEADER", "PLAYER"Hashed);
	inline std::unique_ptr<SeperatorText> GuiAimbotHeader = std::make_unique<SeperatorText>("AIMBOT_HEADER", "AIMBOT"Hashed);
	inline std::unique_ptr<SeperatorText> GuiEspHeader = std::make_unique<SeperatorText>("ESP_HEADER", "ESP"Hashed);
	inline std::unique_ptr<SeperatorText> GuiWorldHeader = std::make_unique<SeperatorText>("WORLD_HEADER", "WORLD"Hashed);
	inline std::unique_ptr<SeperatorText> GuiMenuHeader = std::make_unique<SeperatorText>("MENU_HEADER", "MENU"Hashed);
	inline std::unique_ptr<SeperatorText> GuiConfigSectionHeader = std::make_unique<SeperatorText>("CONFIG_SECTION_HEADER", "CONFIG"Hashed);

	inline std::unique_ptr<Checkbox> GuiPlayerGodmode = std::make_unique<Checkbox>("PLAYER_GODMODE", "GODMODE"Hashed);
	inline std::unique_ptr<Checkbox> GuiPlayerReload = std::make_unique<Checkbox>("PLAYER_INSTANT_RELOAD", "INSTANT_RELOAD"Hashed);
	inline std::unique_ptr<Checkbox> GuiPlayerMelee = std::make_unique<Checkbox>("PLAYER_INSTANT_MELEE", "INSTANT_MELEE"Hashed);
	inline std::unique_ptr<Checkbox> GuiPlayerNoRecoil = std::make_unique<Checkbox>("PLAYER_NO_RECOIL", "NO_RECOIL"Hashed);
	inline std::unique_ptr<Checkbox> GuiPlayerNoSpread = std::make_unique<Checkbox>("PLAYER_NO_SPREAD", "NO_SPREAD"Hashed);

	inline std::unique_ptr<Toggle> GuiAimbotSilent = std::make_unique<Toggle>("AIMBOT_SILENT", "SILENT_AIMBOT"Hashed);
	inline std::unique_ptr<Toggle> GuiAimbotTrigger = std::make_unique<Toggle>("AIMBOT_TRIGGER", "TRIGGER_AIMBOT"Hashed);

	inline std::unique_ptr<Checkbox> GuiEspEnabled = std::make_unique<Checkbox>("ESP_ENABLED", "ESP"Hashed);
	inline std::unique_ptr<Checkbox> GuiWorldEnabled = std::make_unique<Checkbox>("WORLD_ENABLED", "WORLD"Hashed);

	inline std::unique_ptr<Checkbox> GuiMenuAnimated = std::make_unique<Checkbox>("MENU_ANIMATED", "ANIMATED"Hashed);
	inline std::unique_ptr<Combo> GuiMenuTheme = std::make_unique<Combo>("MENU_THEME", "THEME"Hashed);
	inline std::unique_ptr<SliderInt> GuiMenuOpacity = std::make_unique<SliderInt>("MENU_OPACITY", "OPACITY"Hashed, ElementBase::Style_t{}, 100, 50, 100);

	inline std::unique_ptr<Button> GuiConfigSave = std::make_unique<Button>(std::string("SAVE_CONFIG"), "SAVE_CONFIG"Hashed);
	inline std::unique_ptr<Button> GuiConfigLoad = std::make_unique<Button>(std::string("LOAD_CONFIG"), "LOAD_CONFIG"Hashed, ElementBase::Style_t{
		.eSameLine = ElementBase::ESameLine::Same });
	inline std::unique_ptr<Checkbox> GuiConfigAutoSave = std::make_unique<Checkbox>("CONFIG_AUTO_SAVE", "AUTO_SAVE"Hashed);

	// Developer Page Elements
	inline std::unique_ptr<Page> GuiDeveloperPage = std::make_unique<Page>("DEVELOPER_PAGE", ElementBase::Style_t(), 0, 0);
	inline std::unique_ptr<Button> GuiUnloadButton = std::make_unique<Button>(std::string("UNLOAD_BTN"), "UNLOAD_BTN"Hashed);
	inline std::unique_ptr<Button> GuiConsoleVisibility = std::make_unique<Button>(std::string("CONSOLE_VISIBILITY"), "CONSOLE_HIDE"Hashed, ElementBase::Style_t{
		.eSameLine = ElementBase::ESameLine::Same });
	inline std::unique_ptr<Combo> GuiLocalization = std::make_unique<Combo>(std::string("LANGUAGE"), "LANGUAGE"Hashed, ElementBase::Style_t{
		.iFlags = ImGuiComboFlags_WidthFitPreview });

	// Config Page Elements
	inline std::unique_ptr<Page> GuiConfigPage = std::make_unique<Page>("CONFIG_PAGE", ElementBase::Style_t(), 0, 0);

	void Render();

	inline std::once_flag LoadFlag;
}