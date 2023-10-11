#include "SpriteBatch.h"
#include <SFML/Graphics/PrimitiveType.hpp>

namespace sfex
{
	SpriteBatch::SpriteBatch()
	{
	}

	SpriteBatch::~SpriteBatch()
	{

	}

	void SpriteBatch::Init(const sf::Texture& texture)
	{
		m_Texture = &texture;
	}

	void SpriteBatch::Begin(size_t count)
	{
		m_VerteArray.resize(count * 4);
		m_Offset = 0;
	}

	void SpriteBatch::Submit(const sf::Sprite& sprite)
	{
		if (m_Offset * 4 < m_VerteArray.size())
		{

			const sf::Transform& t = sprite.getTransform();
			sf::FloatRect rect = sprite.getLocalBounds();

			sf::Vector2f topLeft(rect.left, rect.top);
			sf::Vector2f topRight(rect.left + rect.width, rect.top);
			sf::Vector2f bottomRight(rect.left + rect.width, rect.top + rect.height);
			sf::Vector2f bottomLeft(rect.left, rect.top + rect.height);

			topLeft = t * topLeft;
			topRight = t * topRight;
			bottomRight = t * bottomRight;
			bottomLeft = t * bottomLeft;
			
			float tx = (float)sprite.getTextureRect().left;
			float ty = (float)sprite.getTextureRect().top;
			float tw = (float)sprite.getTextureRect().width;
			float th = (float)sprite.getTextureRect().height;

			sf::Vertex* vertices = &m_VerteArray[m_Offset * 4];

			vertices[0].position = topLeft;
			vertices[0].texCoords = sf::Vector2f(tx, ty);
			vertices[0].color = sprite.getColor();

			vertices[1].position = topRight;
			vertices[1].texCoords = sf::Vector2f(tx + tw, ty);
			vertices[1].color = sprite.getColor();

			vertices[2].position = bottomRight;
			vertices[2].texCoords = sf::Vector2f(tx + tw, ty + th);
			vertices[2].color = sprite.getColor();

			vertices[3].position = bottomLeft;
			vertices[3].texCoords = sf::Vector2f(tx, ty + th);
			vertices[3].color = sprite.getColor();

			++m_Offset;
		}
	}

	void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_Texture)
			states.texture = m_Texture;
		target.draw(m_VerteArray.data(), m_VerteArray.size(), sf::Quads, states);
	}
}