// Created by Modar Nasser on 12/11/2020.

#pragma once

#include <string>

#include "LDtkLoader/thirdparty/json.hpp"
#include "LDtkLoader/DataTypes.hpp"
#include "LDtkLoader/LayerDef.hpp"
#include "LDtkLoader/Tileset.hpp"
#include "LDtkLoader/Entity.hpp"

namespace ldtk {

    class World;
    class Level;

    class Layer {
        friend Level;
    public:
        Layer(Layer&& other) noexcept;

        const LayerType type;
        const std::string name;
        const UIntPoint grid_size;
        const unsigned int cell_size;

        auto getOffset() const -> const IntPoint&;
        void setOffset(const IntPoint& offset);

        auto getOpacity() const -> float;
        void setOpacity(float opacity);

        auto hasTileset() const -> bool;
        auto getTileset() const -> const Tileset&;

        auto allTiles() const -> const std::vector<Tile>&;
        auto getTile(unsigned int grid_x, unsigned int grid_y) const -> const Tile&;

        auto hasEntity(const std::string& entity_name) const -> bool;
        auto getEntities(const std::string& entity_name) const -> const std::vector<Entity>&;

    private:
        explicit Layer(const nlohmann::json& j, const World* w);
        void updateTileVertices(Tile& tile) const;

        const LayerDef* m_definition = nullptr;

        IntPoint m_total_offset;
        float m_opacity;

        std::vector<Tile> m_tiles;
        std::unordered_map<std::string, std::vector<Entity>> m_entities;
        std::map<unsigned int, Tile*> m_tiles_map;
    };

}
