#include "MapEditConfig.h"
#include<Windows.h>
#include<string>

MapEditConfig LoadMaoEditConfig(const std::string& iniPath)
{
	MapEditConfig efg;
	efg.MAPEDIT_WIN_WIDTH = GetPrivateProfileInt("MapEdit", "MAP_W",        255, "./MySetup.ini");
	efg.MAPEDIT_WIN_HEIGHT = GetPrivateProfileInt("MapEdit", "MAP_H", 255, "./MySetup.ini");
	efg.MAP_IMAGE_SIZE = GetPrivateProfileInt("MapEdit", "TILE_SIZE", 255, "./MySetup.ini");
	efg.LEFT_MARGIN = GetPrivateProfileInt("MapEdit", "LEFT_MARGIN", 255, "./MySetup.ini");
	efg.TOP_MARGIN = GetPrivateProfileInt("MapEdit", "TOP_MARGIN", 255, "./MySetup.ini");

	return efg;

}

const MapEditConfig& GetMapEditConfig()
{
	static MapEditConfig config = LoadMaoEditConfig("MapEdit.ini");
	return config;
}
