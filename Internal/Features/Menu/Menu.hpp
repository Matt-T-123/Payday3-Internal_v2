#pragma once
#include "Features/Feature.hpp"

class MenuFeature : public BaseFeature
{
public:
    bool SetupMenu() override;
    void HandleMenu() override;
    void HandleInput() override;
    void Render() override;
    std::string GetName() override { return "Menu"; }

private:
    bool m_bAnimated = true;
    int m_iTheme = 0;
    int m_iOpacity = 100;
};

inline std::unique_ptr<MenuFeature> pMenuFeature = std::make_unique<MenuFeature>();
