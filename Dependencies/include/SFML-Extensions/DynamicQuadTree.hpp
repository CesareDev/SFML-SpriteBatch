#pragma once
#include <list>
#include <array>
#include <tuple>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sf
{
	struct Rectangle
	{
		sf::Vector2f position;
		sf::Vector2f size;

		Rectangle(const sf::Vector2f& p = { 0.f, 0.f }, const sf::Vector2f& s = { 0.f, 0.f })
			: position(p), size(s)
		{
		}

		Rectangle(float x, float y, float width, float height)
			: position({ x, y }), size({ width, height })
		{
		}

		Rectangle(const sf::FloatRect& rect)
		{
			position.x = rect.left;
			position.y = rect.top;
			size.x = rect.width;
			size.y = rect.height;
		}

		bool contains(const Rectangle& rectangle) const
		{
			return (rectangle.position.x >= position.x) && (rectangle.position.x + rectangle.size.x < position.x + size.x) &&
				(rectangle.position.y >= position.y) && (rectangle.position.y + rectangle.size.y < position.y + size.y);
		}

		bool overlaps(const Rectangle& rectangle) const
		{
			return !(position.x > rectangle.position.x + rectangle.size.x || position.x + size.x < rectangle.position.x || position.y > rectangle.position.y + rectangle.size.y || position.y + size.y < rectangle.position.y);
		}
	};

	template <typename T>
	class DynamicQuadTree
	{
	private:

		//Nested Class and Struct
		//-----------------------------------------------------------------------------

		template <typename OBJ>
		class RealQuadTree
		{
		public:

			size_t size;
			RealQuadTree<OBJ>* parent;

		private:

			unsigned int m_Depth;
			Rectangle m_Area;

			std::array<Rectangle, 4> m_ChildrenAreas;
			std::array<std::unique_ptr<RealQuadTree<OBJ>>, 4> m_Children;
			std::list<std::pair<OBJ, Rectangle>> m_ListOfObjects;

		public:

			inline RealQuadTree(const Rectangle& area = { 0.f, 0.f, 0.f, 0.f }, unsigned int depth = 0)
			{
				m_Depth = depth;
				size = 0;
				parent = nullptr;
				resize(area);
			}

			inline ~RealQuadTree()
			{
			}

			inline void clear()
			{
				m_ListOfObjects.clear();
				for (auto& child : m_Children)
				{
					if (child)
					{
						child->clear();
					}
					child.reset();
				}
			}

			inline void resize(const Rectangle& area)
			{
				m_Area = area;
				sf::Vector2f childSize = { m_Area.size.x / 2.f, m_Area.size.y / 2.f };
				m_ChildrenAreas =
				{
					Rectangle(m_Area.position, childSize),
					Rectangle({ m_Area.position.x + childSize.x, m_Area.position.y }, childSize),
					Rectangle({ m_Area.position.x, m_Area.position.y + childSize.y }, childSize),
					Rectangle(m_Area.position + childSize, childSize)
				};
			}

			inline std::tuple<std::list<std::pair<OBJ, Rectangle>>*, typename std::list<std::pair<OBJ, Rectangle>>::iterator, RealQuadTree<OBJ>*> insert(const OBJ& obj, const Rectangle& objArea, unsigned int maxDepth)
			{
				++size;
				for (int i = 0; i < 4; ++i)
				{
					if (m_ChildrenAreas[i].contains(objArea))
					{
						if (m_Depth + 1 < maxDepth)
						{
							if (!m_Children[i])
							{
								m_Children[i] = std::make_unique<RealQuadTree<OBJ>>(m_ChildrenAreas[i], m_Depth + 1);
								m_Children[i]->parent = this;
							}
							return m_Children[i]->insert(obj, objArea, maxDepth);
						}
					}
				}
				m_ListOfObjects.emplace_back(std::pair<OBJ, Rectangle>(obj, objArea));
				return std::make_tuple(&m_ListOfObjects, std::prev(m_ListOfObjects.end()), this);
			}

			inline void auxSearch(const Rectangle& searchArea, std::list<OBJ>& listToFill) const
			{
				for (const auto& obj : m_ListOfObjects)
				{
					if (searchArea.overlaps(obj.second))
					{
						listToFill.emplace_back(std::move(obj.first));
					}
				}
				for (int i = 0; i < 4; ++i)
				{
					if (searchArea.contains(m_ChildrenAreas[i]))
					{
						if (m_Children[i])
						{
							m_Children[i]->appendAll(listToFill);
						}
					}
					else if (searchArea.overlaps(m_ChildrenAreas[i]))
					{
						if (m_Children[i])
						{
							m_Children[i]->auxSearch(searchArea, listToFill);
						}
					}
				}
			}

			inline void appendAll(std::list<OBJ>& listToFill) const
			{
				for (const auto& obj : m_ListOfObjects)
				{
					listToFill.emplace_back(std::move(obj.first));
				}
				for (const auto& child : m_Children)
				{
					if (child)
					{
						child->appendAll(listToFill);
					}
				}
			}

			inline void update()
			{
				for (auto& child : m_Children)
				{
					if (child)
					{
						if (child->size == 0)
						{
							child.reset();
						}
						else
						{
							child->update();
						}
					}
				}
			}

			inline void updateSize()
			{
				auto x = this;
				while (x->parent != nullptr)
				{
					x->size = x->size - 1;
					x = x->parent;
				}
			}

			inline const Rectangle& getArea()
			{
				return m_Area;
			}
		};

		template <typename OBJ_ITEM>
		struct Item
		{
			OBJ_ITEM* obj;
			std::tuple<
				typename std::list<std::pair<typename std::list<Item<OBJ_ITEM>>::iterator, Rectangle>>*,
				typename std::list<std::pair<typename std::list<Item<OBJ_ITEM>>::iterator, Rectangle>>::iterator,
				RealQuadTree<typename std::list<Item<OBJ_ITEM>>::iterator>*
			> location;
		};

		//Members
		//-----------------------------------------------------------------------------

		unsigned int m_MaxDepth;
		std::list<Item<T>> m_AllObjects;
		RealQuadTree<typename std::list<Item<T>>::iterator> m_Root;

	public:

		inline DynamicQuadTree()
		{
		}

		inline DynamicQuadTree(unsigned int maxDepth, const Rectangle& area = { 0.f, 0.f, 0.f, 0.f })
			: m_MaxDepth(maxDepth), m_Root(area)
		{
		}

		inline ~DynamicQuadTree()
		{
		}

		inline void create(unsigned int maxDepth, const Rectangle& area = { 0.f, 0.f, 0.f, 0.f })
		{
			m_MaxDepth = maxDepth;
			m_Root.resize(area);
		}

		inline size_t size() const
		{
			return m_AllObjects.size();
		}

		inline bool empty() const
		{
			return m_AllObjects.empty();
		}

		inline void clear()
		{
			m_AllObjects.clear();
			m_Root.clear();
		}

		inline typename std::list<Item<T>>::iterator begin()
		{
			return m_AllObjects.begin();
		}

		inline typename std::list<Item<T>>::iterator end()
		{
			return m_AllObjects.end();
		}

		inline typename std::list<Item<T>>::const_iterator cbegin()
		{
			return m_AllObjects.cbegin();
		}

		inline typename std::list<Item<T>>::const_iterator cend()
		{
			return m_AllObjects.cend();
		}

		inline void resize(const Rectangle& area)
		{
			clear();
			m_Root.resize(area);
		}

		inline void insert(T* obj, const Rectangle& objArea)
		{
			if (m_Root.getArea().contains(objArea))
			{
				Item<T> item;
				item.obj = obj;
				m_AllObjects.emplace_back(std::move(item));
				m_AllObjects.back().location = m_Root.insert(std::prev(m_AllObjects.end()), objArea, m_MaxDepth);
			}
		}

		inline void relocate(typename std::list<Item<T>>::iterator& obj_it, const Rectangle& objArea)
		{
			if (m_Root.getArea().contains(objArea))
			{
				std::get<0>(obj_it->location)->erase(std::get<1>(obj_it->location));
				std::get<2>(obj_it->location)->updateSize();
				m_Root.update();
				obj_it->location = m_Root.insert(obj_it, objArea, m_MaxDepth);
			}
		}

		inline typename std::list<Item<T>>::iterator remove(typename std::list<Item<T>>::iterator& obj_it)
		{
			std::get<0>(obj_it->location)->erase(std::get<1>(obj_it->location));
			std::get<2>(obj_it->location)->updateSize();
			m_Root.update();
			return m_AllObjects.erase(obj_it);
		}

		inline std::list<typename std::list<Item<T>>::iterator> search(const Rectangle& searchArea) const
		{
			std::list<typename std::list<Item<T>>::iterator> listToFill;
			m_Root.auxSearch(searchArea, listToFill);
			return listToFill;
		}
	};
}