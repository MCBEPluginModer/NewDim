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

class TestDimension : public MoreDimension 
{
public:
    TestDimension(ILevel& ilevel, Scheduler& scheduler,MoreDimensionManager::DimensionInfo& dimensionInfo)
    : MoreDimension(
        ilevel,
        scheduler,
       dimensionInfo
    ) {
        ll::Logger loggg("tests");
    loggg.info("TestDimension::TestDimension");
        dimensionInfo = MoreDimensionManager::DimensionInfo("test",3,12345);
        mDefaultBrightness.sky   = Brightness::MAX;
        mSeaLevel                = 1;
        mHasWeather              = true;
        mDimensionBrightnessRamp = std::make_unique<OverworldBrightnessRamp>();
        mDimensionBrightnessRamp->buildBrightnessRamp();
        std::string name = "test";
       // dimensionInfo.name = name;
        //dimensionInfo.id = 3;
       // dimensionInfo.seed = 34328643;
        //dimensionInfo.generatorType = (enum GeneratorType)0x6;
    }
    void init() final {
        ll::Logger loggg("tests");
        loggg.info("TestDimension::init");
        setSkylight(false);
        Dimension::init();
    }
    std::unique_ptr<WorldGenerator> createGenerator() final {
        ll::Logger loggg("tests");
        loggg.info("TestDimension::createGenerator");
      //  auto& level     = getLevel();
       // auto& levelData = level.getLevelData();
       // level.getBiomeRegistry().lookupByName(levelData.getBiomeOverride());
       // auto& layer = levelData.getFlatWorldGeneratorOptions();

        return std::make_unique<VoidGenerator>(*this);
    }

    void upgradeLevelChunk(ChunkSource& cs, LevelChunk& lc, LevelChunk& generatedChunk) final {
        ll::Logger loggg("tests");
        loggg.info("TestDimension::upgradeLevelChunk");
        BlockSource blockSource = BlockSource(getLevel(), *this, cs, false, true, false);
        VanillaLevelChunkUpgrade::_upgradeLevelChunkViaMetaData(lc, generatedChunk, blockSource);
        VanillaLevelChunkUpgrade::_upgradeLevelChunkLegacy(lc, blockSource);
    }

    void fixWallChunk(ChunkSource& cs, LevelChunk& lc) final {
        ll::Logger loggg("tests");
        loggg.info("TestDimension::fixWallChunk");
        BlockSource blockSource = BlockSource(getLevel(), *this, cs, false, true, false);
        VanillaLevelChunkUpgrade::fixWallChunk(lc, blockSource);
    }

    bool levelChunkNeedsUpgrade(LevelChunk const& lc) const final {
        ll::Logger loggg("tests");
        loggg.info("TestDimension::levelChunkNeedsUpgrade");
        return VanillaLevelChunkUpgrade::levelChunkNeedsUpgrade(lc);
    }
    void _upgradeOldLimboEntity(CompoundTag& tag, ::LimboEntitiesVersion vers) final {
        ll::Logger loggg("tests");
        loggg.info("TestDimension::_upgradeOldLimboEntity");
        auto isTemplate = this->getLevel().getLevelData().isFromWorldTemplate();
        return VanillaLevelChunkUpgrade::upgradeOldLimboEntity(tag, vers, isTemplate);
    }

    /*Vec3 translatePosAcrossDimension(Vec3 const& pos, DimensionType did) const final {
        log.info("TestDimension::translatePosAcrossDimension");
        return (MoreDimen;
    }*/

    std::unique_ptr<ChunkSource>
    _wrapStorageForVersionCompatibility(std::unique_ptr<ChunkSource> cs, ::StorageVersion ver) override {
        ll::Logger loggg("tests");
        loggg.info("TestDimension::_wrapStorageForVersionCompatibility");
        return cs;
    }

    mce::Color getBrightnessDependentFogColor(mce::Color const& color, float brightness) const override {
        ll::Logger loggg("tests");
        loggg.info("TestDimension::getBrightnessDependentFogColor");
        float temp   = (brightness * 0.94f) + 0.06f;
        float temp2  = (brightness * 0.91f) + 0.09f;
        auto  result = color;
        result.r     = color.r * temp;
        result.g     = color.g * temp;
        result.b     = color.b * temp2;
        return result;
    };

    short getCloudHeight() const override { return 192; };

    bool hasPrecipitationFog() const override { return true; };

    static std::unique_ptr<StructureFeatureRegistry>
    makeStructureFeatures(uint a1, bool a2, BaseGameVersion const& a3, Experiments const& a4) {
        ll::Logger loggg("tests");
        loggg.info("TestDimension::makeStructureFeatures");
        return {};
    };
};


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
