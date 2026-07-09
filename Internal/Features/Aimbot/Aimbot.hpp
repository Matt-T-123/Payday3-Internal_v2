#pragma once
#include "pch.h"

class Aimbot : public BaseFeature
{
private:
	inline static uint8_t s_iAimbotPageId = ElementBase::AddPage("AIMBOT_BUTTON"Hashed, ICON_FA_CROSSHAIRS);

	std::unique_ptr<RadioButtonIcon> m_pMenuButton = std::make_unique<RadioButtonIcon>(
		std::string("AIMBOT_BUTTON"),
		"AIMBOT_BUTTON"Hashed,
		ElementBase::Style_t({ .vec2Size = ImVec2(-0.1f, 0) }),
		ICON_FA_CROSSHAIRS,
		s_iAimbotPageId);

	std::unique_ptr<Page> m_pTab1Page = std::make_unique<Page>(
		"AIMBOT_MAIN_PAGE##AIMBOT_FEATURE",
		ElementBase::Style_t(),
		s_iAimbotPageId,
		0);

	std::unique_ptr<Page> m_pTab2Page = std::make_unique<Page>(
		"AIMBOT_ADVANCED_PAGE##AIMBOT_FEATURE",
		ElementBase::Style_t(),
		s_iAimbotPageId,
		1);

	std::unique_ptr<Group> m_pTab1Group = std::make_unique<Group>("AIMBOT_MAIN_GROUP##AIMBOT_FEATURE", ElementBase::Style_t{});
	std::unique_ptr<Group> m_pTab2Group = std::make_unique<Group>("AIMBOT_ADVANCED_GROUP##AIMBOT_FEATURE", ElementBase::Style_t{});

	std::unique_ptr<GroupChild> m_pTab1Left = std::make_unique<GroupChild>(
		"AIMBOT_MAIN_LEFT",
		"AIMBOT_MAIN_LEFT"Hashed,
		ElementBase::Style_t(),
		ImGuiChildFlags_Border);

	std::unique_ptr<GroupChild> m_pTab1Right = std::make_unique<GroupChild>(
		"AIMBOT_MAIN_RIGHT",
		"AIMBOT_MAIN_RIGHT"Hashed,
		ElementBase::Style_t{ .eSameLine = ElementBase::ESameLine::Same },
		ImGuiChildFlags_Border);

	std::unique_ptr<GroupChild> m_pTab2Left = std::make_unique<GroupChild>(
		"AIMBOT_ADVANCED_LEFT",
		"AIMBOT_ADVANCED_LEFT"Hashed,
		ElementBase::Style_t(),
		ImGuiChildFlags_Border);

	std::unique_ptr<GroupChild> m_pTab2Right = std::make_unique<GroupChild>(
		"AIMBOT_ADVANCED_RIGHT",
		"AIMBOT_ADVANCED_RIGHT"Hashed,
		ElementBase::Style_t{ .eSameLine = ElementBase::ESameLine::Same },
		ImGuiChildFlags_Border);

	std::unique_ptr<Checkbox> m_pEnabled = std::make_unique<Checkbox>("AIMBOT_ENABLED", "AIMBOT_ENABLED"Hashed);
	std::unique_ptr<Toggle> m_pMode = std::make_unique<Toggle>("AIMBOT_MODE", "AIMBOT_MODE"Hashed);
	std::unique_ptr<SliderInt> m_pStrength = std::make_unique<SliderInt>("AIMBOT_STRENGTH", "AIMBOT_STRENGTH"Hashed, ElementBase::Style_t{}, 50, 0, 100);
	std::unique_ptr<Combo> m_pProfile = std::make_unique<Combo>("AIMBOT_PROFILE", "AIMBOT_PROFILE"Hashed, ElementBase::Style_t{ .iFlags = ImGuiComboFlags_WidthFitPreview });
	std::unique_ptr<Button> m_pAction = std::make_unique<Button>(std::string("AIMBOT_ACTION"), "AIMBOT_ACTION"Hashed);

public:
	bool SetupMenu();
	void HandleMenu();
	void Run();
	RadioButtonIcon* GetMenuButton() const { return m_pMenuButton.get(); }
	std::string GetName() { return "Aimbot"; };
};

inline std::unique_ptr<Aimbot> pAimbot = std::make_unique<Aimbot>();
