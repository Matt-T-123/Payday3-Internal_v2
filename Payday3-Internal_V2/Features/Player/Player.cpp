#include "pch.h"
#include "Player.hpp"

bool Player::SetupMenu()
{
	Localization::AddToLocale("ENG", std::initializer_list<std::pair<size_t, std::string>>{
		{ "PLAYER_BUTTON"Hashed, "Player" },
		{ "PLAYER_TAB1"Hashed, "Local Player" },
		{ "PLAYER_TAB2"Hashed, "Players" },
		{ "PLAYER_TAB3"Hashed, "Weapon Mods" },

		{ "PLAYER_TAB1_LEFT"Hashed, "General" },
		{ "PLAYER_TAB1_RIGHT"Hashed, "Options" },

		{ "PLAYER_TAB2_LEFT"Hashed, "Details" },

		{ "PLAYER_TAB3_LEFT"Hashed, "Mods" },
		{ "PLAYER_TAB3_RIGHT"Hashed, "Options" },

		//Tab 1
		{ "PLAYER_GODMODE_TYPE"Hashed, "Godmode Type" },
		{ "PLAYER_GODMODE"Hashed, "Godmode" },
		{ "PLAYER_INF_STAMINA"Hashed, "Infinite Stamina" },
		{ "PLAYER_INSTA_MELEE"Hashed, "Instant Melee" },
		{ "PLAYER_NO_SCREENSHAKE"Hashed, "No Screenshake" },
		{ "PLAYER_NO_FALLDAMAGE"Hashed, "No Fall Damage" },
		{ "PLAYER_NO_DETECTION"Hashed, "No Detection" },

		//Tab2
		{ "PLAYER_TABLE"Hashed, "Players" },
		{ "PLAYER_TABLE_ROW1"Hashed, "Row 1" },

		//Tab3
		{ "PLAYER_INSTA_RELOAD"Hashed, "Instant Reload" },
		{ "PLAYER_INF_AMMO"Hashed, "Infinite Ammo" },
		{ "PLAYER_NO_RECOIL"Hashed, "No Recoil" },
		{ "PLAYER_NO_SPREAD"Hashed, "No Spread" },
		{ "PLAYER_FIRE_RATE_SLIDER"Hashed, "Fire Rate" },
		{ "PLAYER_FIRE_RATE"Hashed, "Fire Rate" }
	});

	return true;
}

void Player::HandleMenu()
{
	static std::once_flag onceflag;

	std::call_once(onceflag, [this]() {
		auto pHeaderGroup = static_cast<HeaderGroup*>(Framework::menu->GetChild("HEADER_GROUP"));
		if (pHeaderGroup)
			pHeaderGroup->AddHeaders(Player::s_iPlayerPageId, { "PLAYER_TAB1"Hashed, "PLAYER_TAB2"Hashed, "PLAYER_TAB3"Hashed });

		m_pTab1Left->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pTab1Right->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pTab2Left->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 20.0f), (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pTab3Left->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});
		m_pTab3Right->SetCallback([]() {
			return ImVec2((ImGui::GetWindowWidth() - 10.0f - 10.0f * 2) / 2, (ImGui::GetWindowHeight() - 20.0f));
		});

		/////////////////Tab 1////////////////////

		// Godmode Toggle
		m_pTab1Left->AddElement(m_pGodMode.get());

		// Infinite Stamina Toggle
		m_pTab1Left->AddElement(m_pInfStamina.get());

		// Instant Melee Toggle
		m_pTab1Left->AddElement(m_pInstaMelee.get());
		m_pInstaMelee->SetOnValueChangedCallback([this](const bool, const bool bNewValue) {
			InstantMelee(bNewValue);
		});

		// No Screenshake Toggle
		m_pTab1Left->AddElement(m_pNoScreenshake.get());

		// No Fall Damage Toggle
		m_pTab1Left->AddElement(m_pNoFallDamage.get());

		// No Detection Toggle
		m_pTab1Left->AddElement(m_pNoDetection.get());

		// Godmode Type
		m_pGodModeType->AddOption("Set");
		m_pGodModeType->AddOption("Block");
		m_pTab1Right->AddElement(m_pGodModeType.get());

		m_pTab1Group->AddElement(m_pTab1Left.get());
		m_pTab1Group->AddElement(m_pTab1Right.get());

		////////////////Tab 2///////////////////

		//Add a ?x? table then populate it with player(s) info
		//Need to figure out then best way to interact with the players in the table, maybe a left click player color highlight and then select an action from below the table ?
		//Edit: Implemented tables, just need to do the populate it with player info and then work on interacting with table rows and selecting actions for the selected player(s).
		//Edit2: I'll have to make the tables look better first befoore populating cus they look a lil ugly rn
		m_pPlayerRow1->AddElement(m_pPlayerName.get());
		m_pPlayerRow1->AddElement(m_pPlayerHealth.get());
		m_pPlayerTable->AddElement(m_pPlayerRow1.get());
		
		m_pTab2Left->AddElement(m_pPlayerTable.get());

		m_pTab2Group->AddElement(m_pTab2Left.get());

		////////////////Tab 3///////////////////

		m_pTab3Left->AddElement(m_pInstaReload.get());
		m_pTab3Left->AddElement(m_pInfAmmo.get());
		m_pTab3Left->AddElement(m_pNoRecoil.get());
		m_pTab3Left->AddElement(m_pNoSpread.get());
		m_pTab3Left->AddElement(m_pFireRate.get());
		m_pTab3Right->AddElement(m_pFireRateSlider.get());

		m_pTab3Group->AddElement(m_pTab3Left.get());
		m_pTab3Group->AddElement(m_pTab3Right.get());

		m_pTab1Page->AddElement(m_pTab1Group.get());
		m_pTab2Page->AddElement(m_pTab2Group.get());
		m_pTab3Page->AddElement(m_pTab3Group.get());

		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pTab1Page.get());
		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pTab2Page.get());
		Framework::menu->GetChild("HEADER_GROUP")->GetChild("BODY")->AddElement(m_pTab3Page.get());
	});
}

void Player::blockDamage(bool bEnabled)
{
	auto* localChar = Unreal::GetLocalCharacter();
	if (!localChar)
	{
		m_bBlockDamageApplied = false;
		return;
	}

	if (bEnabled) //I'm not kidding I had to design the method this way because bCanBeDamaged wasn't disabling for some reason. Digusting but it works.
	{
		if (!m_bBlockDamageApplied)
		{
			m_bOriginalCanBeDamaged = localChar->bCanBeDamaged;
			m_bBlockDamageApplied = false;
		}

		localChar->bCanBeDamaged = false;
		m_bBlockDamageApplied = true;
	}
	else if (m_bBlockDamageApplied)
	{
		localChar->bCanBeDamaged = m_bOriginalCanBeDamaged;
		m_bBlockDamageApplied = false;
	}
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
	/////////////////Tab 1///////////////////

	//Godmode
	if(m_pGodMode->GetValue())
	{
		auto* localChar = Unreal::GetLocalCharacter();
		if (!localChar) return;

		if (m_pGodModeType->GetSelectedIndex() == 0){
			auto* PlayerAttributeSet = localChar->PlayerAttributeSet;
			// Need to change back on disable, too lazy to do rn
			PlayerAttributeSet->Health.CurrentValue = 200.0f;
		}
		else
		{
			blockDamage(true);
		}
	}
	else
	{
		blockDamage(false);
	}

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

	/////////////////Tab 2///////////////////

	//Populate the player table with player(s) info here

	/////////////////Tab 3///////////////////

	//Instant Reload
	if (m_pInstaReload->GetValue())
	{
		InstantReload(m_pInstaReload->GetValue());
	}

	//Infinite Ammo
	if (m_pInfAmmo->GetValue()) //Needs rework to return ammo back to normal on disable
	{
		auto* localChar = Unreal::GetLocalCharacter();
		if (!localChar) return;

		auto* Att = localChar->PlayerAttributeSet;

		Att->PrimaryEquippableAmmoInventory.CurrentValue = 999;
		Att->SecondaryEquippableAmmoInventory.CurrentValue = 999;
		Att->TertiaryEquippableAmmoInventory.CurrentValue = 999;

		Att->PrimaryThrowableAmmoInventory.CurrentValue = 999;
		Att->SecondaryThrowableAmmoInventory.CurrentValue = 999;
		Att->TertiaryThrowableAmmoInventory.CurrentValue = 999;

		Att->PrimaryToolAmmoInventory.CurrentValue = 999;
		Att->SecondaryToolAmmoInventory.CurrentValue = 999;
		Att->TertiaryToolAmmoInventory.CurrentValue = 999;
	}
	
	//No Recoil
	if (m_pNoRecoil->GetValue()) //Needs rework to return recoil back to normal on disable
	{
		auto* localChar = Unreal::GetLocalCharacter();
		if (!localChar) return;

		auto* weaponData = reinterpret_cast<SDK::USBZRangedWeaponData*>(localChar->FPCameraAttachment->EquippedWeaponData);
		if (weaponData)
		{
			weaponData->RecoilData->ViewKick.SpeedDeflect = 0.f;
			weaponData->RecoilData->GunKickBack.SpeedDeflect = 0.f;
			weaponData->RecoilData->GunKickXY.SpeedDeflect = 0.f;
		}
	}

	//No Spread
	if (m_pNoSpread->GetValue()) //Needs rework to return spread back to normal on disable
	{
		auto* localChar = Unreal::GetLocalCharacter();
		if (!localChar) return;

		auto* SpreadData = reinterpret_cast<SDK::USBZRangedWeaponData*>(localChar->FPCameraAttachment->EquippedWeaponData)->SpreadData;
		if (SpreadData)
		{
			SpreadData->InnerClusterSpreadMultiplier = SpreadData->FireSpreadStart = SpreadData->FireSpreadMinCap = SpreadData->FireSpreadCap = SpreadData->FireSpreadIncrease = 0.f;
		}
	}

	//Fire Rate
	if (m_pFireRate->GetValue()) //Needs rework to return fire rate back to normal on disable
	{
		auto* localChar = Unreal::GetLocalCharacter();
		if (!localChar) return;

		auto* FireData = reinterpret_cast<SDK::USBZRangedWeaponData*>(localChar->FPCameraAttachment->EquippedWeaponData)->FireData;
		if (FireData)
		{
			FireData->ProjectilesPerFiredRound = m_pFireRateSlider->GetValue();
			FireData->FireMode = SDK::ESBZFireMode::Auto;
		}
	}
}
