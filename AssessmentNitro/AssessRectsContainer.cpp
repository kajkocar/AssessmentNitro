#include "stdafx.h"
#include "AssessRectangle.h"
#include "AssessRectsContainer.h"

AssessRectsContainer::AssessRectsContainer()
{
}


AssessRectsContainer::~AssessRectsContainer()
{
}

int AssessRectsContainer::add(AssessRectangle& rec)
{
	Rects.push_back(rec);
	return Rects.size() - 1;
}

unsigned int AssessRectsContainer::Size()
{
	return Rects.size();
}

AssessRectangle AssessRectsContainer::get(int ItemNo)
{
	AssessRectangle rct(-1, -1, -1, -1);

	if (ItemNo < Size())
	{
		rct = Rects[ItemNo];
	}

	return rct;
}

int AssessRectsContainer::findIntersectFrom(int start, AssessRectangle& comp, AssessRectangle& res)
{
	for (unsigned int i = start; i < Size(); i++)
	{
		if (comp.intersect(Rects[i], res))
		{
			return i;
		}
	}

	return -1;
}
