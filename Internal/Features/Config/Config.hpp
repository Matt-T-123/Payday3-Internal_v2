#pragma once
#include "Features/Feature.hpp"

class ConfigFeature : public BaseFeature
{
public:
    bool SetupMenu() override;
    void HandleMenu() override;
    void HandleInput() override;
    void Render() override;
    std::string GetName() override { return "Config"; }

private:
    bool m_bAutoSave = true;
};

inline std::unique_ptr<ConfigFeature> pConfigFeature = std::make_unique<ConfigFeature>();
