#include "stdafx.h"
#include "AssessRectangle.h"
#include "AssessDataProvider.h"
//////////////////////////////////////////////////////////////////////////
// JSON code taken from
// https://github.com/DaveGamble/cJSON
// and included in solution under JSON folder
#include "JSON/cJSON.h"
#include "AssessDataProviderJSON.h"


AssessDataProviderJSON::~AssessDataProviderJSON()
{
	if (root)
		cJSON_Delete(root);
};

// in case of JSON data provider, init data is file name 
// (with full path if not in executable folder)
bool AssessDataProviderJSON::Init(std::string initData)
{
	std::ifstream t(initData);
	std::stringstream my_json_string;
	my_json_string << t.rdbuf();
	if (my_json_string.str().empty())
		return false;

	root = cJSON_Parse(my_json_string.str().c_str());
	if (!root)
		return false;

	rects = cJSON_GetObjectItem(root, "rects");
	if (!rects)
		return false;

	return true;
}

int AssessDataProviderJSON::Size()
{
	if (rects)
		return cJSON_GetArraySize(rects);

	return -1;
}

AssessRectangle AssessDataProviderJSON::get(int ItemNo)
{
	AssessRectangle rct(-1, -1, -1, -1);

	if (ItemNo < cJSON_GetArraySize(rects))
	{
		cJSON * subitem = cJSON_GetArrayItem(rects, ItemNo);
		rct.setX(cJSON_GetObjectItem(subitem, "x")->valueint);
		rct.setY(cJSON_GetObjectItem(subitem, "y")->valueint);
		rct.setWidth(cJSON_GetObjectItem(subitem, "w")->valueint);
		rct.setHeight(cJSON_GetObjectItem(subitem, "h")->valueint);
	}

	return rct;
}
