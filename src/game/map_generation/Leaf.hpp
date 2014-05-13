#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

template<class T>
class Leaf
{
public:
	Leaf(T x, T y, T width, T height)
		: m_x(x)
		, m_y(y)
		, m_width(width)
		, m_height(height)
		, m_leftChild(nullptr)
		, m_rightChild(nullptr)
		, m_room()
		, m_halls()
	{
	}

	virtual ~Leaf() {};

public:
	bool Split()
	{
		// Begin splitting the leaf into two children
		if (m_leftChild != nullptr || m_rightChild != nullptr)
		{
			return false;
		}

		// Determine direction of split
		// If the width is 25% larger than height, we split vertically
		// If the height is 25% larger than the width, we split horizontally
		// Otherwise split randomly

		bool splitH = (std::rand() % 100) > 25 ? true : false;
		if (m_width > m_height && m_height / m_width >= (T)0.05)
		{
			splitH = false;
		}
		else if (m_height > m_width && m_width / m_height >= (T)0.05)
		{
			splitH = true;
		}

		// Determine the maximum width or height
		T max = (splitH ? m_height : m_width) - MIN_LEAF_SIZE;
		if (max <= MIN_LEAF_SIZE)
		{
			// Area is too small to split anymore
			return false;
		}

		// Determine where we're going to split
		T split = (T)std::rand(MIN_LEAF_SIZE, max);

		// Create our left and right children based on the direction of the split
		if (splitH)
		{
			m_leftChild = std::make_shared<Leaf>(m_x, m_y, m_width, split);
			m_rightChild = std::make_shared<Leaf>(m_x, m_y + split, m_width, m_height - split);
		}
		else
		{
			m_leftChild = std::make_shared<Leaf>(m_x, m_y, split, m_height);
			m_rightChild = std::make_shared<Leaf>(m_x + split, m_y, m_width - split, m_height);
		}

		// Split successful
		return true;
	};

	void CreateRooms();

	sf::Rect<T> GetRoom();
	void CreateHall(sf::Rect<T> left, sf::Rect<T> right);

private:
	static const unsigned int MIN_LEAF_SIZE = 20;

private:
	const T m_x;
	const T m_y;
	
	const T m_width;
	const T m_height;

	Leaf<T> m_leftChild;
	Leaf<T> m_rightChild;

	sf::Rect<T> m_room;
	sf::Vector2<T> m_halls;
};

template <class T>
using LeafPtr = std::shared_ptr<Leaf<T>>;

