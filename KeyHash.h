#pragma once
#include <functional>

template <class K>
class KeyHash
{
public:
	unsigned long operator()(K key)
	{
		return std::hash<K>{}(key) % 100;
	}
};