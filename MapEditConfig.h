#pragma once
struct MapEditConfig
{
	int MAPEDIT_WIN_WIDTH;//
	int MAPEDIT_WIN_HEIGHT;//
	int MAP_IMAGE_SIZE;
	int LEFT_MARGIN;
	int TOP_MARGIN;

};

const MapEditConfig& GetMapEditConfig();



