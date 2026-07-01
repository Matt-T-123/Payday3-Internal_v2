#pragma once
#include "Features/Feature.hpp"

class PlayerFeature : public BaseFeature
{
public:
    bool SetupMenu() override;
    void HandleMenu() override;
    void HandleInput() override;
    void Render() override;
    std::string GetName() override { return "Player"; }

private:
    bool m_bEnabled = false;
    int m_iFov = 90;
    float m_fSmooth = 0.25f;
    bool m_bVisibleOnly = false;
};

inline std::unique_ptr<PlayerFeature> pPlayerFeature = std::make_unique<PlayerFeature>();
