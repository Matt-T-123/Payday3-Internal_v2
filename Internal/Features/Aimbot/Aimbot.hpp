#pragma once
#include "Features/Feature.hpp"

class AimbotFeature : public BaseFeature
{
public:
    bool SetupMenu() override;
    void HandleMenu() override;
    void HandleInput() override;
    void Render() override;
    std::string GetName() override { return "Aimbot"; }

private:
    bool m_bEnabled = false;
    int m_iHitbox = 0;
    int m_iDelay = 80;
    float m_fRecoilCompensation = 0.4f;
};

inline std::unique_ptr<AimbotFeature> pAimbotFeature = std::make_unique<AimbotFeature>();
