#pragma once
#pragma warning(disable : 4244)

#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

namespace sf {

	class TileMap
	{
	public:

		TileMap();
		~TileMap();

		bool load(const std::string& tmxFilePath);
		bool load(const std::string& tmxFilePath, const sf::Texture* tileset);

		void update(float dt);
		void drawLayer(sf::RenderTarget& target, uint32_t layerIndex);
		void draw(sf::RenderTarget& target);
		void clean();
		void setWall(const sf::Vector2i& posInUnit, bool isWall);
		void setColor(const sf::Color& color);

		const sf::Color& getColor() const;
		uint32_t getLayerCount() const;
		const sf::Vector2u& getMapSize() const;
		const sf::Vector2u& getTileSize() const;
		bool isCellWall(const sf::Vector2i& posInUnit) const;
		bool isCellTile(const sf::Vector2i& posInUnit) const;

	private:

		struct AnimationState
		{
			uint32_t layer;
			sf::Vector2u position;
			tmx::Tileset::Tile tile;

			uint32_t frameIndex = 0;
			float elapsed = 0.f;

			AnimationState(uint32_t _layer, const sf::Vector2u& pos, const tmx::Tileset::Tile& _tile)
				: layer(_layer), position(pos), tile(_tile)
			{}
		};

		uint32_t m_LayerCount;
		uint32_t m_TileSetWidthInTile;

		sf::Vector2u m_MapSize;
		sf::Vector2u m_MapSizeInTile;
		sf::Vector2u m_TileSize;

		std::vector<std::vector<sf::Vertex>> m_TileMap;
		std::vector<AnimationState> m_AnimatedTiles;
		std::vector<bool> m_Walls;
		std::vector<bool> m_VectorForMiniMap;

		sf::Texture* m_TileSet;
		sf::RenderStates m_States;
		sf::RenderTexture m_MapDrawBuffer;
		sf::Sprite m_RenderTextureSprite;
	};
}

