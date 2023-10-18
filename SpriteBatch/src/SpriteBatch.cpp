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
		size_t index = m_Offset * 4;
		if (index < m_VerteArray.size())
		{
			const sf::Transform& t = sprite.getTransform();
			sf::FloatRect rect = sprite.getLocalBounds();

			sf::Vector2f topLeft = t * sf::Vector2f(rect.left, rect.top);
			sf::Vector2f topRight = t * sf::Vector2f(rect.left + rect.width, rect.top);
			sf::Vector2f bottomRight = t * sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
			sf::Vector2f bottomLeft = t * sf::Vector2f(rect.left, rect.top + rect.height);
			
			float tx = (float)sprite.getTextureRect().left;
			float ty = (float)sprite.getTextureRect().top;
			float tw = (float)sprite.getTextureRect().width;
			float th = (float)sprite.getTextureRect().height;

			m_VerteArray[index].position = topLeft;
			m_VerteArray[index].texCoords = sf::Vector2f(tx, ty);
			m_VerteArray[index].color = sprite.getColor();

			m_VerteArray[index + 1].position = topRight;
			m_VerteArray[index + 1].texCoords = sf::Vector2f(tx + tw, ty);
			m_VerteArray[index + 1].color = sprite.getColor();

			m_VerteArray[index + 2].position = bottomRight;
			m_VerteArray[index + 2].texCoords = sf::Vector2f(tx + tw, ty + th);
			m_VerteArray[index + 2].color = sprite.getColor();

			m_VerteArray[index + 3].position = bottomLeft;
			m_VerteArray[index + 3].texCoords = sf::Vector2f(tx, ty + th);
			m_VerteArray[index + 3].color = sprite.getColor();

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