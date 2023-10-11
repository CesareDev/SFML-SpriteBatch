#pragma once
#include <vector>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sfex
{
	class SpriteBatch
	{
	public:

		/// <summary>
		/// Default Constructor, this constructor doesn't do anything
		/// </summary>
		SpriteBatch();

		/// <summary>
		/// Destructor
		/// </summary>
		~SpriteBatch();


		/// <summary>
		/// This function assign a texture to the batch, make sure the texture doesn't get destroyed befor the batch itself is destroyed
		/// </summary>
		/// <param name="texture: ">reference to an existing texture</param>
		void Init(const sf::Texture& texture);

		/// <summary>
		/// This function resize the vertex array with the appropriate number of vertex based on how many sprite should be drawned
		/// </summary>
		/// <param name="count: ">Sprites count</param>
		void Begin(size_t count);

		/// <summary>
		/// This function submit the sprite to the batch updating the corresponding vertices position and texture coordinates
		/// </summary>
		/// <param name="sprite: ">sprite to submit</param>
		void Submit(const sf::Sprite& sprite);


		/// <summary>
		/// This function draw the entire vertex array in the render target with a single draw call
		/// </summary>
		/// <param name="target: ">target to draw on</param>
		void Render(sf::RenderTarget& target);

	private:
		
		/// <summary>
		/// Render States used to store the texture pointer
		/// </summary>
		sf::RenderStates m_States;

		/// <summary>
		/// The vertices of all the sprite submitted to the batch
		/// </summary>
		std::vector<sf::Vertex> m_VerteArray;

		/// <summary>
		/// Offset used to get every sprite vertex from the vertexarray
		/// </summary>
		size_t m_Offset = 0;
	};
}