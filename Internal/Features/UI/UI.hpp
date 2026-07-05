#pragma once
#include "pch.h"

class UI : public BaseFeature
{
private:
    inline static uint8_t s_iUIPageId = ElementBase::AddPage("UI_BUTTON"Hashed, ICON_FA_STAR);

    std::unique_ptr<RadioButtonIcon> m_pMenuButton = std::make_unique<RadioButtonIcon>(
        std::string("UI_BUTTON"),
        "UI_BUTTON"Hashed,
        ElementBase::Style_t({ .vec2Size = ImVec2(-0.1f, 0) }),
        ICON_FA_STAR,
        s_iUIPageId);

    std::unique_ptr<Page> m_pUIPage = std::make_unique<Page>(
        "UI_MAIN",
        ElementBase::Style_t(),
        s_iUIPageId,
        0);
    std::unique_ptr<Button> m_pUnloadButton = std::make_unique<Button>(
        std::string("UI_UNLOAD_BUTTON"),
        "UI_UNLOAD_BUTTON"Hashed);

    std::unique_ptr<Button> m_pConsoleVisibility = std::make_unique<Button>(
        std::string("UI_CONSOLE_VISIBILITY"),
        "UI_CONSOLE_HIDE"Hashed,
        ElementBase::Style_t{ .eSameLine = ElementBase::ESameLine::Same });

    std::unique_ptr<Combo> m_pLocalization = std::make_unique<Combo>(
        std::string("UI_LANGUAGE"),
        "UI_LANGUAGE"Hashed,
        ElementBase::Style_t{ .iFlags = ImGuiComboFlags_WidthFitPreview });

public:
    bool SetupMenu();
    void HandleMenu();
    void Run();
    std::string GetName() { return "UI"; };
};

std::unique_ptr<UI> pUI = std::make_unique<UI>();
