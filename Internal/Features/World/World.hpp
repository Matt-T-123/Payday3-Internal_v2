#pragma once
#include "Features/Feature.hpp"

class WorldFeature : public BaseFeature
{
public:
    bool SetupMenu() override;
    void HandleMenu() override;
    void HandleInput() override;
    void Render() override;
    std::string GetName() override { return "World"; }

private:
    bool m_bLootGlow = false;
    bool m_bVehicleNames = false;
    int m_iMaxDistance = 300;
};

inline std::unique_ptr<WorldFeature> pWorldFeature = std::make_unique<WorldFeature>();
