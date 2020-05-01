#pragma once
#include "SLL.h"
#include "SortedMultiMap.h"
#include <utility>

class SortedMultiMap;
class SMMIterator
{
	friend class SortedMultiMap;
private:
	const SortedMultiMap& smm;
	SLLother* currentn;

	SMMIterator(const SortedMultiMap& othersmm);
public:
	void first();
	bool valid();
	void next();
	Telem getCurrent();
	~SMMIterator();
};

