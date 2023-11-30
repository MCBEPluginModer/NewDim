#pragma once

#include <string_view>

#include <ll/api/Logger.h>
#include <ll/api/plugin/Plugin.h>
#include <ll/api/dimension/MoreDimension.h>
#include <ll/api/dimension/MoreDimensionManager.h>
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

class ILevel;
class Scheduler;
class Dimension;
class CompoundTag;
class StructureFeatureRegistry;
using namespace ll::memory;

class TestDimension : public MoreDimension 
{
public:
    TestDimension(ILevel& ilevel, Scheduler& scheduler,MoreDimensionManager::DimensionInfo& dimensionInfo)
    : MoreDimension(
        ilevel,
        scheduler,
        dimensionInfo
    ) {
        logger.info("TestDimension::TestDimension");
    }
    void init() final {
        logger.info("TestDimension::init");
        ((MoreDimension*)this)->init();
    }
    std::unique_ptr<WorldGenerator> createGenerator() final {
        logger.info("TestDimension::createGenerator");
        return ((MoreDimension*)this)->createGenerator();
    }

    void upgradeLevelChunk(ChunkSource& cs, LevelChunk& lc, LevelChunk& generatedChunk) final {
        logger.info("TestDimension::upgradeLevelChunk");
        ((MoreDimension*)this)->upgradeLevelChunk(cs, lc, generatedChunk);
    }

    void fixWallChunk(ChunkSource& cs, LevelChunk& lc) final {
        logger.info("TestDimension::fixWallChunk");
        ((MoreDimension*)this)->fixWallChunk(cs, lc);
    }

    bool levelChunkNeedsUpgrade(LevelChunk const& lc) const final {
        logger.info("TestDimension::levelChunkNeedsUpgrade");
        return ((MoreDimension*)this)->levelChunkNeedsUpgrade(lc);
    }
    void _upgradeOldLimboEntity(CompoundTag& tag, ::LimboEntitiesVersion vers) final {
        logger.info("TestDimension::_upgradeOldLimboEntity");
        return ((MoreDimension*)this)->_upgradeOldLimboEntity(tag, vers);
    }

    Vec3 translatePosAcrossDimension(Vec3 const& pos, DimensionType did) const final {
        logger.info("TestDimension::translatePosAcrossDimension");
        return ((MoreDimension*)this)->translatePosAcrossDimension(pos, did);
    }

    std::unique_ptr<ChunkSource>
    _wrapStorageForVersionCompatibility(std::unique_ptr<ChunkSource> cs, ::StorageVersion ver) override {
        logger.info("TestDimension::_wrapStorageForVersionCompatibility");
        return cs;
    }

    mce::Color getBrightnessDependentFogColor(mce::Color const& color, float brightness) const override {
        logger.info("TestDimension::getBrightnessDependentFogColor");
        return ((MoreDimension*)this)->getBrightnessDependentFogColor(color, brightness);
    };

    short getCloudHeight() const override { return 192; };

    bool hasPrecipitationFog() const override { return true; };

    static std::unique_ptr<StructureFeatureRegistry>
    makeStructureFeatures(uint a1, bool a2, BaseGameVersion const& a3, Experiments const& a4) {
        logger.info("TestDimension::makeStructureFeatures");
        return MoreDimension::makeStructureFeatures(a1, a2, a3, a4);
    };
};


namespace plugins {

class Plugin {
public:
    MoreDimensionManager manager;
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
