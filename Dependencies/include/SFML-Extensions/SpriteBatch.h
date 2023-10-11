#pragma once
#pragma warning(disable : 4244)

#include <vector>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sf
{
	class SpriteBatch
	{
	public:

		SpriteBatch();
		~SpriteBatch();

		void Create(const sf::Texture* texture);
		void SetTexture(const sf::Texture* texture);
		void Begin(const size_t& spriteCount);
		void Submit(const sf::Sprite& sprite);
		void Render(sf::RenderTarget& target);

	private:

		sf::RenderStates m_RenderStates;
		std::vector<sf::Vertex> m_VertexVector;

		size_t m_BufferOffset = 0;
		bool m_Create = false;
		bool m_Begin = false;
	};
}
