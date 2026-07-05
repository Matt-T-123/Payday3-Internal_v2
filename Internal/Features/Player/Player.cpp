#include "pch.h"
#include "Player.hpp"

bool Player::SetupMenu()
{
	Localization::AddToLocale("ENG", std::initializer_list<std::pair<size_t, std::string>>{
		{ "PLAYER_BUTTON"Hashed, "Player" },
		{ "PLAYER_TAB1"Hashed, "Player" },
		{ "PLAYER_TAB2"Hashed, "Advanced" },

		{ "PLAYER_TAB1_LEFT"Hashed, "General" },
		{ "PLAYER_TAB1_RIGHT"Hashed, "Options" },

		{ "PLAYER_TAB2_LEFT"Hashed, "Details" },
		{ "PLAYER_TAB2_RIGHT"Hashed, "Actions" },

		{ "PLAYER_GODMODE_TYPE"Hashed, "Godmode Type" },
		{ "PLAYER_GODMODE"Hashed, "Godmode" },
		{ "PLAYER_INF_STAMINA"Hashed, "Infinite Stamina" },
		{ "PLAYER_INSTA_MELEE"Hashed, "Instant Melee" },
		{ "PLAYER_INSTA_RELOAD"Hashed, "Instant Reload" },
		{ "PLAYER_NO_SCREENSHAKE"Hashed, "No Screenshake" },
		{ "PLAYER_NO_FALLDAMAGE"Hashed, "No Fall Damage" },
		{ "PLAYER_NO_DETECTION"Hashed, "No Detection" },

		{ "PLAYER_SCALE"Hashed, "Scale" },
		{ "PLAYER_PRESET"Hashed, "Preset" },
		{ "PLAYER_ACTION"Hashed, "Apply" }
	});

	return true;
}

void Player::HandleMenu()
{
	static std::once_flag onceflag;

	std::call_once(onceflag, [this]() {
		auto pHeaderGroup = static_cast<HeaderGroup*>(Framework::menu->GetChild("HEADER_GROUP"));
		if (pHeaderGroup)
			pHeaderGroup->AddHeaders(Player::s_iPlayerPageId, { "PLAYER_TAB1"Hashed, "PLAYER_TAB2"Hashed });

		m_pMainLeft->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pMainRight->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});
		m_pAdvancedLeft->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});
		m_pAdvancedRight->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 10.0f - 10.0f * 2) / 2);
		});

		m_pPreset->AddOption("Default");
		m_pPreset->AddOption("Compact");
		m_pPreset->AddOption("Expanded");

		// Godmode Toggle
		m_pMainLeft->AddElement(m_pGodMode.get());

		// Infinite Stamina Toggle
		m_pMainLeft->AddElement(m_pInfStamina.get());

		// Instant Melee Toggle
		m_pMainLeft->AddElement(m_pInstaMelee.get());

		// Instant Reload Toggle
		m_pMainLeft->AddElement(m_pInstaReload.get());

		// No Screenshake Toggle
		m_pMainLeft->AddElement(m_pNoScreenshake.get());

		// No Fall Damage Toggle
		m_pMainLeft->AddElement(m_pNoFallDamage.get());

		// No Detection Toggle
		m_pMainLeft->AddElement(m_pNoDetection.get());

		// Godmode Type
		m_pGodModeType->AddOption("Set");
		m_pGodModeType->AddOption("Block");
		m_pMainRight->AddElement(m_pGodModeType.get());

		m_pMainRight->AddElement(m_pScale.get());
		m_pMainGroup->AddElement(m_pMainLeft.get());
		m_pMainGroup->AddElement(m_pMainRight.get());

		m_pAdvancedLeft->AddElement(m_pPreset.get());
		m_pAdvancedRight->AddElement(m_pAction.get());
		m_pAdvancedGroup->AddElement(m_pAdvancedLeft.get());
		m_pAdvancedGroup->AddElement(m_pAdvancedRight.get());

		m_pMainPage->AddElement(m_pMainGroup.get());
		m_pAdvancedPage->AddElement(m_pAdvancedGroup.get());

		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pMainPage.get());
		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pAdvancedPage.get());
	});
}

static inline SDK::ASBZPlayerCharacter* GetLocalChar(SDK::APlayerController* pc) {
    if (!pc || !pc->Pawn || !pc->Pawn->IsA(SDK::ASBZPlayerCharacter::StaticClass())) return nullptr;
    return static_cast<SDK::ASBZPlayerCharacter*>(pc->Pawn);
}

void Player::Run()
{
	//Godmode
	if(m_pGodMode->GetValue())
	{
		SDK::UWorld* world = SDK::UWorld::GetWorld();
		if (!world) return;
		SDK::APlayerController* localPC = SDK::USBZPlayerLibrary::GetLocalPlayerController(world);
		if (!localPC) return;
		auto* localChar = GetLocalChar(localPC);
		if (!localChar) return;

		if (m_pGodModeType->GetSelectedIndex() == 0){
			auto* PlayerAttributeSet = localChar->PlayerAttributeSet;
			//PlayerAttributeSet->Health.CurrentValue = PlayerAttributeSet->HealthMax.CurrentValue;
			PlayerAttributeSet->Health.CurrentValue = 500.0f;
			Utils::LogDebug("Set");
		}
		else{
			//Figure out how to block damage. Too lazy to do this rn
			Utils::LogDebug("Block");
		}
	};
}
