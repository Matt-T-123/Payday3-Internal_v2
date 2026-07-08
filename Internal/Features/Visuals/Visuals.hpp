#pragma once
#include "pch.h"

class Visuals : public BaseFeature
{
private:
	inline static uint8_t s_iVisualsPageId = ElementBase::AddPage("VISUALS_BUTTON"Hashed, ICON_FA_EYE);

	std::unique_ptr<RadioButtonIcon> m_pMenuButton = std::make_unique<RadioButtonIcon>(
		std::string("VISUALS_BUTTON"),
		"VISUALS_BUTTON"Hashed,
		ElementBase::Style_t({ .vec2Size = ImVec2(-0.1f, 0) }),
		ICON_FA_EYE,
		s_iVisualsPageId);

	std::unique_ptr<Page> m_pMainPage = std::make_unique<Page>(
		"VISUALS_MAIN_PAGE",
		ElementBase::Style_t(),
		s_iVisualsPageId,
		0);

	std::unique_ptr<Page> m_pAdvancedPage = std::make_unique<Page>(
		"VISUALS_ADVANCED_PAGE",
		ElementBase::Style_t(),
		s_iVisualsPageId,
		1);

	std::unique_ptr<Group> m_pMainGroup = std::make_unique<Group>("VISUALS_MAIN_GROUP", ElementBase::Style_t{});
	std::unique_ptr<Group> m_pAdvancedGroup = std::make_unique<Group>("VISUALS_ADVANCED_GROUP", ElementBase::Style_t{});

	std::unique_ptr<GroupChild> m_pMainLeft = std::make_unique<GroupChild>(
		"VISUALS_MAIN_LEFT",
		"VISUALS_MAIN_LEFT"Hashed,
		ElementBase::Style_t(),
		ImGuiChildFlags_Border);

	std::unique_ptr<GroupChild> m_pMainRight = std::make_unique<GroupChild>(
		"VISUALS_MAIN_RIGHT",
		"VISUALS_MAIN_RIGHT"Hashed,
		ElementBase::Style_t{ .eSameLine = ElementBase::ESameLine::Same },
		ImGuiChildFlags_Border);

	std::unique_ptr<GroupChild> m_pAdvancedLeft = std::make_unique<GroupChild>(
		"VISUALS_ADVANCED_LEFT",
		"VISUALS_ADVANCED_LEFT"Hashed,
		ElementBase::Style_t(),
		ImGuiChildFlags_Border);

	std::unique_ptr<GroupChild> m_pAdvancedRight = std::make_unique<GroupChild>(
		"VISUALS_ADVANCED_RIGHT",
		"VISUALS_ADVANCED_RIGHT"Hashed,
		ElementBase::Style_t{ .eSameLine = ElementBase::ESameLine::Same },
		ImGuiChildFlags_Border);

	std::unique_ptr<Checkbox> m_pEnabled = std::make_unique<Checkbox>("VISUALS_ENABLED", "VISUALS_ENABLED"Hashed);
	std::unique_ptr<ColorPicker> m_pAccent = std::make_unique<ColorPicker>("VISUALS_ACCENT", "VISUALS_ACCENT"Hashed, ElementBase::Style_t{ .eSameLine = ElementBase::ESameLine::Same });
	std::unique_ptr<SliderInt> m_pOpacity = std::make_unique<SliderInt>("VISUALS_OPACITY", "VISUALS_OPACITY"Hashed, ElementBase::Style_t{}, 75, 0, 100);
	std::unique_ptr<Button> m_pAction = std::make_unique<Button>(std::string("VISUALS_ACTION"), "VISUALS_ACTION"Hashed);

public:
	bool SetupMenu();
	void HandleMenu();
	void Run();
	RadioButtonIcon* GetMenuButton() const { return m_pMenuButton.get(); }
	std::string GetName() { return "Visuals"; };
};

inline std::unique_ptr<Visuals> pVisuals = std::make_unique<Visuals>();
