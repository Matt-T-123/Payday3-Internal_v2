#pragma once
#include "pch.h"

class Player : public BaseFeature
{
private:
	inline static uint8_t s_iPlayerPageId = ElementBase::AddPage("PLAYER_BUTTON"Hashed, ICON_FA_USER);

	std::unique_ptr<RadioButtonIcon> m_pMenuButton = std::make_unique<RadioButtonIcon>(
		std::string("PLAYER_BUTTON"),
		"PLAYER_BUTTON"Hashed,
		ElementBase::Style_t({ .vec2Size = ImVec2(-0.1f, 0) }),
		ICON_FA_USER,
		s_iPlayerPageId);

	std::unique_ptr<Page> m_pMainPage = std::make_unique<Page>(
		"PLAYER_TAB1_PAGE",
		ElementBase::Style_t(),
		s_iPlayerPageId,
		0);

	std::unique_ptr<Page> m_pAdvancedPage = std::make_unique<Page>(
		"PLAYER_TAB2_PAGE",
		ElementBase::Style_t(),
		s_iPlayerPageId,
		1);

	std::unique_ptr<Page> m_pWeaponModsPage = std::make_unique<Page>(
		"PLAYER_TAB3_PAGE",
		ElementBase::Style_t(),
		s_iPlayerPageId,
		2);

	std::unique_ptr<Group> m_pMainGroup = std::make_unique<Group>("PLAYER_TAB1_GROUP", ElementBase::Style_t{});
	std::unique_ptr<Group> m_pAdvancedGroup = std::make_unique<Group>("PLAYER_TAB2_GROUP", ElementBase::Style_t{});
	std::unique_ptr<Group> m_pWeaponModsGroup = std::make_unique<Group>("PLAYER_TAB3_GROUP", ElementBase::Style_t{});

	std::unique_ptr<GroupChild> m_pMainLeft = std::make_unique<GroupChild>(
		"PLAYER_TAB1_LEFT",
		"PLAYER_TAB1_LEFT"Hashed,
		ElementBase::Style_t(),
		ImGuiChildFlags_Border);

	std::unique_ptr<GroupChild> m_pMainRight = std::make_unique<GroupChild>(
		"PLAYER_TAB1_RIGHT",
		"PLAYER_TAB1_RIGHT"Hashed,
		ElementBase::Style_t{ .eSameLine = ElementBase::ESameLine::Same },
		ImGuiChildFlags_Border);

	std::unique_ptr<GroupChild> m_pAdvancedLeft = std::make_unique<GroupChild>(
		"PLAYER_TAB2_LEFT",
		"PLAYER_TAB2_LEFT"Hashed,
		ElementBase::Style_t(),
		ImGuiChildFlags_Border);

	std::unique_ptr<GroupChild> m_pAdvancedRight = std::make_unique<GroupChild>(
		"PLAYER_TAB2_RIGHT",
		"PLAYER_TAB2_RIGHT"Hashed,
		ElementBase::Style_t{ .eSameLine = ElementBase::ESameLine::Same },
		ImGuiChildFlags_Border);

	std::unique_ptr<Combo> m_pGodModeType = std::make_unique<Combo>("PLAYER_GODMODE_TYPE", "PLAYER_GODMODE_TYPE"Hashed, ElementBase::Style_t{ .iFlags = ImGuiComboFlags_WidthFitPreview });
	std::unique_ptr<Checkbox> m_pGodMode = std::make_unique<Checkbox>("PLAYER_GODMODE", "PLAYER_GODMODE"Hashed);
	std::unique_ptr<Checkbox> m_pInfStamina = std::make_unique<Checkbox>("PLAYER_INF_STAMINA", "PLAYER_INF_STAMINA"Hashed);
	std::unique_ptr<Checkbox> m_pInstaMelee = std::make_unique<Checkbox>("PLAYER_INSTA_MELEE", "PLAYER_INSTA_MELEE"Hashed);
	std::unique_ptr<Checkbox> m_pInstaReload = std::make_unique<Checkbox>("PLAYER_INSTA_RELOAD", "PLAYER_INSTA_RELOAD"Hashed);
	std::unique_ptr<Checkbox> m_pNoScreenshake = std::make_unique<Checkbox>("PLAYER_NO_SCREENSHAKE", "PLAYER_NO_SCREENSHAKE"Hashed);
	std::unique_ptr<Checkbox> m_pNoFallDamage = std::make_unique<Checkbox>("PLAYER_NO_FALLDAMAGE", "PLAYER_NO_FALLDAMAGE"Hashed);
	std::unique_ptr<Checkbox> m_pNoDetection = std::make_unique<Checkbox>("PLAYER_NO_DETECTION", "PLAYER_NO_DETECTION"Hashed);

	std::unique_ptr<Combo> m_pPreset = std::make_unique<Combo>("PLAYER_PRESET", "PLAYER_PRESET"Hashed, ElementBase::Style_t{ .iFlags = ImGuiComboFlags_WidthFitPreview });
	std::unique_ptr<Button> m_pAction = std::make_unique<Button>(std::string("PLAYER_ACTION"), "PLAYER_ACTION"Hashed);

	void blockDamage(bool bEnabled);
	bool m_bBlockDamageApplied = false;
	bool m_bOriginalCanBeDamaged = true;

	bool m_bInstantMeleeApplied = false;
    float m_flOriginalMeleeRate = 1.0f;
	SDK::UAnimMontage* m_pLastMeleeMontage = nullptr;
	void InstantMelee(bool bEnabled);

	bool m_bInstantReloadApplied = false;
    float m_flOriginalReloadRate = 1.0f;
	SDK::UAnimMontage* m_pLastReloadMontage = nullptr;
	void InstantReload(bool bEnabled);

public:
	bool SetupMenu();
	void HandleMenu();
	void Run();
	RadioButtonIcon* GetMenuButton() const { return m_pMenuButton.get(); }
	std::string GetName() { return "Player"; };
};

inline std::unique_ptr<Player> pPlayer = std::make_unique<Player>();
