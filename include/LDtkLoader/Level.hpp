// Created by Modar Nasser on 12/11/2020.

#pragma once

#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include "LDtkLoader/containers/FieldsContainer.hpp"
#include "LDtkLoader/thirdparty/json_fwd.hpp"
#include "LDtkLoader/thirdparty/optional.hpp"

#include "LDtkLoader/DataTypes.hpp"
#include "LDtkLoader/Layer.hpp"

namespace ldtk {

    class World;

    class Level : public FieldsContainer
    {
        friend World;

    public:
        struct BgImage
        {
            std::string path;
            IntPoint pos;
            FloatPoint scale;
            IntRect crop;
        };

        ~Level() = default;
        Level(const Level&) = delete;
        Level(Level&&) noexcept = default;
        auto operator=(const Level&) -> Level& = delete;
        auto operator=(Level&&) -> Level& = delete;

        const World* const world;

        const std::string name;
        const IID iid;
        const int uid;
        const IntPoint size;
        const IntPoint position;
        const Color bg_color;
        const int depth;

        auto allLayers() const -> const std::vector<Layer>&;
        auto getLayer(const std::string& layer_name) const -> const Layer&;
        auto getLayer(const IID& iid) const -> const Layer&;

        auto hasBgImage() const -> bool;
        auto getBgImage() const -> const BgImage&;

        auto allNeighbours() const -> const std::vector<ref_wrapper<const Level>>&;
        auto getNeighbours(const Dir& direction) const -> const std::vector<ref_wrapper<const Level>>&;
        auto getNeighbourDirection(const Level& level) const -> Dir;

        explicit Level(const nlohmann::json& j, World* w);

    private:
        std::vector<Layer> m_layers;
        std::experimental::optional<BgImage> m_bg_image;

        std::unordered_set<IID> m_neighbours_iid;
        std::map<Dir, std::unordered_set<IID>> m_neighbours_iid_by_dir;

        std::vector<ref_wrapper<const Level>> m_neighbours;
        std::map<Dir, std::vector<ref_wrapper<const Level>>> m_neighbours_by_dir;
    };

} // namespace ldtk
