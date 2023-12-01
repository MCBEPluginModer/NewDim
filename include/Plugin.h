#pragma once
#include <ll/api/dimension/MoreDimension.h>
#include <ll/api/dimension/MoreDimensionManager.h>
#include <string_view>

#include <ll/api/Logger.h>
#include <ll/api/plugin/Plugin.h>
#include <ll/api/memory/Hook.h>
#include <mc/common/wrapper/OwnerPtrFactory.h>
#include <mc/deps/core/mce/Color.h>
#include <mc/deps/json/Value.h>
#include <mc/math/Vec3.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/DimensionConversionData.h>
#include <mc/world/level/Level.h>
#include <mc/world/level/biome/registry/BiomeRegistry.h>
#include <mc/world/level/chunk/LevelChunk.h>
#include <mc/world/level/chunk/ChunkSource.h>
#include <mc/world/level/chunk/VanillaLevelChunkUpgrade.h>
#include <mc/world/level/dimension/Dimension.h>
#include <mc/world/level/dimension/OverworldBrightnessRamp.h>
#include <mc/world/level/dimension/OverworldDimension.h>
#include <mc/world/level/dimension/VanillaDimensionFactory.h>
#include <mc/world/level/dimension/VanillaDimensions.h>
#include <mc/world/level/levelgen/flat/FlatWorldGenerator.h>
#include <mc/world/level/levelgen/structure/StructureFeatureRegistry.h>
#include <mc/world/level/storage/LevelData.h>

namespace plugins {

class Plugin {
public:
    MoreDimensionManager* manager;
    Plugin() = default;

    ~Plugin() = default;

    /// @brief Loads the plugin.
    /// @param self The plugin handle.
    /// @return True if the plugin was loaded successfully.
    bool load(ll::plugin::Plugin& self);

    /// @brief Unloads the plugin.
    /// @param self The plugin handle.
    /// @return True if the plugin was unloaded successfully.
    bool unload(ll::plugin::Plugin& self);

    /// @brief Enables the plugin.
    /// @param self The plugin handle.
    /// @return True if the plugin was enabled successfully.
    bool enable(ll::plugin::Plugin& self);

    /// @brief Disables the plugin.
    /// @param self The plugin handle.
    /// @return True if the plugin was disabled successfully.
    bool disable(ll::plugin::Plugin& self);

    /// @brief Gets the logger.
    /// @return The logger.
    ll::Logger const& getLogger() const;

    /// @brief Gets the plugin name.
    /// @return The plugin name.
    std::string_view getName() const;

    /// @brief Gets the LeviLamina plugin instance.
    /// @return The LeviLamina plugin instance.
    ll::plugin::Plugin& getSelf() const;

    /// @brief Checks if the plugin is enabled.
    /// @return True if the plugin is enabled.
    bool isEnabled() const;

    // More plugin methods here...

private:
    bool mIsEnabled = false;
    ll::plugin::Plugin* mSelf = nullptr;
};

} // namespace plugins
