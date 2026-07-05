#pragma once
#include "../Localization.hpp"

Locale_t localeEnglish{
	.sKey = "English",
	.ullKeyHash = "ENG"Hashed,
	.hMenuFont = &TahomaFont,
	.hFeatureFont = &TahomaFontFeature,
	.umLocalizedStrings = std::unordered_map<size_t, std::string>({
		{ "CHEAT"Hashed, "Cheat"},
		{ "SAVE_CONFIG"Hashed, "Save Config" },
		{ "LOAD_CONFIG"Hashed, "Load Config" },

		{ "SIDEBAR"Hashed, "Sidebar" },
		{ "PLAYER_SEPERATOR"Hashed, "Player" },
		{ "MISC_SEPERATOR"Hashed, "Misc" },
		{ "CONFIG_BUTTON"Hashed, "Config" },
	}),
};
