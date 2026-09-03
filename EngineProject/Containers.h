#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>

template<typename T>
using TArray = std::vector<T>;

template<typename K, typename V>
using TMap = std::unordered_map<K, V>;

template<typename T>
using TSet = std::unordered_set<T>;