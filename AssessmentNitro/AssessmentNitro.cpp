// AssessmentNitro.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AssessRectangle.h"
#include "AssessDataProvider.h"
//////////////////////////////////////////////////////////////////////////
// JSON code taken from
// https://github.com/DaveGamble/cJSON
// and included in solution under JSON folder
#include "JSON/cJSON.h"
#include "AssessDataProviderJSON.h"
#include "AssessDataProviderFactory.h"
#include "AssessRectsContainer.h"

#include "easyunit\testharness.h"
using namespace easyunit;

//////////////////////////////////////////////////////////////////////////
// intersections info
class twoIntersection
{
public:
	twoIntersection(int f, int s, AssessRectangle r) : first(f), second(s), result(r) {};

	int first, second;
	AssessRectangle result;
};

class threeIntersection : public twoIntersection
{
public:
	threeIntersection(int f, int s, int t, AssessRectangle r) : twoIntersection(f,s,r), third(t) {};

	int third;
};
//////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: AssessmentNitro <JSNOFileName>" << std::endl;
		std::cout << "To run internal tests: AssessmentNitro -test" << std::endl;
		return -1;
	}

	std::string fileName(argv[1]);
	if (fileName == "-test")
	{
		TestRegistry::runAndPrint();
		return 0;
	}

	AssessRectsContainer allRects;

	// Load data from JSON file
	// If it is valid JSON file, we will SKIP rectangles with invalid info, eg. negative width and alike
	std::unique_ptr<AssessDataProvider> inputData = AssessDataProviderFactory::getDataProviderJSON();
	if (!inputData->Init(fileName.c_str()))
	{
		std::cout << "Problem with input file '" << fileName << "'." << std::endl;
		return -1;
	}

	for (int i = 0; i < inputData->Size(); i++)
	{
		AssessRectangle rct = inputData->get(i);
		if (rct.isValid())
		{
			int pos = allRects.add(rct);
		}
		else
		{
			std::cout << "Invalid rectangle no. " << i << " : " << rct.dump() << std::endl;
		}
	}

	// output initial data
	std::cout << std::endl << "Input:" << std::endl;
	for (unsigned int i = 0; i < allRects.Size(); i++)
	{
		std::cout << i + 1 << ": Rectangle at " << allRects.get(i).dump() << std::endl;
	}

	//////////////////////////////////////////////////////////////////////////
	// find overlaps

	// result of any 2 intersections
	AssessRectangle intersection;
	// result of any 3 intersections
	AssessRectangle intersection3;

	// intersections between two rectangles
	std::vector< twoIntersection > twos;

	// intersections between three rectangles
	std::vector< threeIntersection > threes;
	
	// when looking for intersection, we always start looking
	// from NEXT of current rectangle, as previous are already checked
	// same logic apply when searching for third intersection...and forth and so on if needed
	for (unsigned int i = 0; i < allRects.Size() - 1; i++)
	{
		int startFrom = allRects.findIntersectFrom(i + 1, allRects.get(i), intersection);
		while (startFrom != -1)
		{
			twoIntersection ti( i + 1, startFrom + 1, intersection );
			twos.push_back(ti);

			// we will use results intersection from those 2 to see if there is an intersection
			// with some one else as well
			// find third intersection
			int startFrom3 = allRects.findIntersectFrom(startFrom + 1, intersection, intersection3);
			while (startFrom3 != -1)
			{
				threeIntersection ti3(i + 1, startFrom + 1, startFrom3 + 1, intersection3);
				threes.push_back(ti3);
				startFrom3 = allRects.findIntersectFrom(startFrom3 + 1, intersection, intersection3);
			}

			startFrom = allRects.findIntersectFrom(startFrom + 1, allRects.get(i), intersection);
		}
	}

	// dump results
	std::cout << std::endl << "Overlaps" << std::endl;

	// first twos
	for (unsigned int i = 0; i < twos.size(); i++)
	{
		std::cout << "Between rectangle " << twos[i].first << " and " << twos[i].second << " at " << twos[i].result.dump() << std::endl;
	}

	// then threes
	for (unsigned int i = 0; i < threes.size(); i++)
	{
		std::cout << "Between rectangle " << threes[i].first << ", " << threes[i].second << " and " << threes[i].third << " at " << threes[i].result.dump() << std::endl;
	}

	return 0;
}
 
