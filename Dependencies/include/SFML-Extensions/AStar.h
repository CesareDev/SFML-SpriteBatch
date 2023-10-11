#pragma once
#include "TileMap.h"

namespace sf
{

	struct Node
	{
		sf::Vector2i position;
		bool isWall = false;
		bool isVisited = false;
		float globalGoal;
		float localGoal;
		Node* neighbors[4];
		Node* parent;
	};

	class AStar
	{
	public:

		AStar();
		~AStar();

		void init(const sf::TileMap& tilemap);
		const std::list<Node*>& calcolatePath(const sf::Vector2i& start, const sf::Vector2i& end);

	private:

		float heuristic(Node* a, Node* b);

	private:

		Node* m_StartNode;
		Node* m_EndNode;

		sf::Vector2u m_MapSize;
		sf::Vector2u m_TileSize;
		std::vector<Node> m_Nodes;
		std::list<Node*> m_Path;
	};
}

