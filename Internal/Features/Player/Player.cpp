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
		m_pInstaMelee->SetOnValueChangedCallback([this](const bool, const bool bNewValue) {
			InstantMelee(bNewValue);
		});

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

void Player::InstantMelee(bool bEnabled)
{
    auto* localChar = Unreal::GetLocalCharacter();
    if (!localChar)
        return;

    auto* montage = localChar->CurrentMeleeMontage;
    if (!montage)
    {
        m_pLastMeleeMontage = nullptr;
        m_bInstantMeleeApplied = false;
        return;
    }

    if (bEnabled)
    {
        if (montage != m_pLastMeleeMontage)
        {
            m_pLastMeleeMontage = montage;
            m_flOriginalMeleeRate = montage->RateScale;
            m_bInstantMeleeApplied = false;
        }

        // Keep trying until ratescale is applied
        if (!m_bInstantMeleeApplied || montage->RateScale != 10000.0f)
        {
            montage->RateScale = 10000.0f;

            if (montage->RateScale == 10000.0f)
                m_bInstantMeleeApplied = true;
        }
    }
    else
    {
        if (m_bInstantMeleeApplied)
        {
            montage->RateScale = m_flOriginalMeleeRate;

            m_bInstantMeleeApplied = false;
            m_pLastMeleeMontage = nullptr;
        }
    }
}

void Player::InstantReload(bool bEnabled)
{
	auto* localChar = Unreal::GetLocalCharacter();
	if (!localChar)
		return;

	auto* montage = localChar->LastLocalReloadMontage;
	if (!montage)
	{
		m_pLastReloadMontage = nullptr;
		m_bInstantReloadApplied = false;
		return;
	}

	if (bEnabled)
	{
		if (montage != m_pLastReloadMontage)
		{
			m_pLastReloadMontage = montage;
			m_flOriginalReloadRate = montage->RateScale;
			m_bInstantReloadApplied = false;
		}

		// Keep trying until ratescale is applied
		if (!m_bInstantReloadApplied || montage->RateScale != 10000.0f)
		{
			montage->RateScale = 10000.0f;

			if (montage->RateScale == 10000.0f)
				m_bInstantReloadApplied = true;
		}
	}
	else
	{
		if (m_bInstantReloadApplied)
		{
			montage->RateScale = m_flOriginalReloadRate;

			m_bInstantReloadApplied = false;
			m_pLastReloadMontage = nullptr;
		}
	}
}

void Player::Run()
{
	//Godmode
	if(m_pGodMode->GetValue())
	{
		auto* localChar = Unreal::GetLocalCharacter();
		if (!localChar) return;

		if (m_pGodModeType->GetSelectedIndex() == 0){
			auto* PlayerAttributeSet = localChar->PlayerAttributeSet;
			//PlayerAttributeSet->Health.CurrentValue = PlayerAttributeSet->HealthMax.CurrentValue;
			PlayerAttributeSet->Health.CurrentValue = 200.0f;
		}
		else{
			//Figure out how to block damage. Too lazy to do this rn
			Utils::LogDebug("Block");
		}
	};

	//Infinite Stamina
	if (m_pInfStamina->GetValue())
	{
		auto* localChar = Unreal::GetLocalCharacter();
		if (!localChar) return;

		auto* PlayerAttributeSet = localChar->PlayerAttributeSet;
		PlayerAttributeSet->Stamina.CurrentValue = 100.0f;
	}

	//Instant Melee
	if (m_pInstaMelee->GetValue())
	{
		InstantMelee(m_pInstaMelee->GetValue());
	}

	//Instant Reload
	if (m_pInstaReload->GetValue())
	{
		InstantReload(m_pInstaReload->GetValue());
	}

	//No Screen Shake
	if (m_pNoScreenshake->GetValue())
	{
		auto* camManager = Unreal::GetPlayerCameraManager();
		if (!camManager)
			return;

		camManager->StopAllCameraShakes(m_pNoScreenshake->GetValue());
	}

	//No Fall Damage
	if (m_pNoFallDamage->GetValue())
	{
		auto* localChar = Unreal::GetLocalCharacter();
		if (!localChar)
			return;

		localChar->FallingStartHeight = localChar->K2_GetActorLocation().Z;
	}

	//No Detection
	if (m_pNoDetection->GetValue())
	{
		auto* localChar = Unreal::GetLocalCharacter();
		if (!localChar)
			return;

		for (UC::int32 i=0; i<localChar->VisualDetectors.Num(); ++i) {
        	auto* det = localChar->VisualDetectors[i];
			if (!det) continue;

			for (UC::int32 e=0; e<det->EnemyDetectionValue.Num(); ++e) {
				auto& d = det->EnemyDetectionValue[e];
				d.Target = nullptr;
        	}
			det->bMarkAsCriminalOnSearch = false;
			det->bShouldDisplayDetectionBuildup = false;
    	}
	}
}
