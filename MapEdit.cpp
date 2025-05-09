#include "MapEdit.h"

MapEdit::MapEdit()
	:GameObject(),myMap_(MAP_WIDTH*MAP_HEIGHT,-1)//�����l���|1��20��20��
{

}

MapEdit::~MapEdit()
{

}

void MapEdit::Update()
{

}

void MapEdit::Draw()
{
	DrawBox(LEFT_MARGIN, TOP_MARGIN, MAP_WIDTH * MAP_IMAGE_SIZE, MAP_HEIGHT * MAP_IMAGE_SIZE, GetColor(255, 255, 0), false, 3);
	
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		DrawLine(i*MAP_IMAGE_SIZE, 0, i* MAP_IMAGE_SIZE, MAP_HEIGHT * MAP_IMAGE_SIZE, GetColor(255, 255, 255), 0);
	}

	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		DrawLine(0, j* MAP_IMAGE_SIZE, MAP_WIDTH * MAP_IMAGE_SIZE, j* MAP_IMAGE_SIZE, GetColor(255, 255, 255), 0);
	}

}
