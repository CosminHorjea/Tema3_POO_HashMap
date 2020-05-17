#pragma once
#include <functional>

template <class K>
class KeyHash
{
public:
	unsigned long operator()(K key) const
	{
		return std::hash<K>{}(key) % 100;
	}
};