#include "MapEditConfig.h"
#include<Windows.h>
#include<string>

MapEditConfig LoadMaoEditConfig(const std::string& iniPath)
{
	MapEditConfig efg;

	efg.MAPEDIT_WIN_WIDTH = GetPrivateProfileInt("MapEdit", "TILE_SIZE", 255, "./MySetup.ini");
	efg.MAPEDIT_WIN_HEIGHT = GetPrivateProfileInt("MapEdoy", "TILE_X", 255, "./MySetup.ini");
	efg.MAP_IMAGE_SIZE = GetPrivateProfileInt("MapEdit", "TILE_Y", 255, "./MySetup.ini");
	efg.LEFT_MARGIN = GetPrivateProfileInt("MapEdit", "VIEW_X", 255, "./MySetup.ini");
	efg.TOP_MARGIN = GetPrivateProfileInt("MapEdit", "VIEW_Y", 255, "./MySetup.ini");

	return efg;

}

const MapEditConfig&  GetMapEditConfig()
{
	static MapEditConfig config = LoadMaoEditConfig("./MySetup.ini");
	return config;

}