#pragma once
#include "Features/Feature.hpp"

class EspFeature : public BaseFeature
{
public:
    bool SetupMenu() override;
    void HandleMenu() override;
    void HandleInput() override;
    void Render() override;
    std::string GetName() override { return "ESP"; }

private:
    bool m_bEnabled = false;
    ImVec4 m_Color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    int m_iDistance = 120;
    bool m_bSkeleton = false;
};

inline std::unique_ptr<EspFeature> pEspFeature = std::make_unique<EspFeature>();
