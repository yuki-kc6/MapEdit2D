#include "MapChipConfig.h"
#include<Windows.h>
#include<string>

MapChipConfig LoadMapChipConfig(const std::string& iniPath)
{
	MapChipConfig cfg;
	cfg.TILES_PIX_SIZE = GetPrivateProfileInt("MapChip", "TILE_SIZE", 255, "./MySetup.ini");
	cfg.TILES_X =		 GetPrivateProfileInt("MapChip", "TILE_X",    255, "./MySetup.ini");
	cfg.TILES_Y =		 GetPrivateProfileInt("MapChip", "TILE_Y",    255, "./MySetup.ini");
	cfg.MAPCHIP_VIEW_X = GetPrivateProfileInt("MapChip", "VIEW_X",    255, "./MySetup.ini");
	cfg.MAPCHIP_VIEW_Y = GetPrivateProfileInt("MapChip", "VIEW_Y",    255, "./MySetup.ini");
	cfg.MAPCHIP_WIN_WIDTH = cfg.TILES_PIX_SIZE * cfg.MAPCHIP_VIEW_X;
	cfg.MAPCHIP_WIN_HEIGHT = cfg.TILES_PIX_SIZE * cfg.MAPCHIP_VIEW_Y;
	return cfg;
}

const MapChipConfig& GetMapChipConfig() 
{
	static MapChipConfig config = LoadMapChipConfig("./MySetup.ini");
	return config;
}