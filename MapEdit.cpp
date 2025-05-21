#include "MapEdit.h"

MapEdit::MapEdit()
	:GameObject(),myMap_(MAP_WIDTH*MAP_HEIGHT,-1)//èâä˙ílÇÅ|1Ç≈20Åñ20ÇÃ
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
	DrawBox(LEFT_MARGIN, TOP_MARGIN, MAP_WIDTH * MAP_IMAGE_SIZE + LEFT_MARGIN, MAP_HEIGHT * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(255, 255, 0), false, 3);
	
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			DrawLine(i * MAP_IMAGE_SIZE + LEFT_MARGIN, TOP_MARGIN + j * MAP_IMAGE_SIZE, (i + 1) * MAP_IMAGE_SIZE + LEFT_MARGIN, TOP_MARGIN + j * MAP_IMAGE_SIZE, GetColor(255, 255, 255), 0);


			DrawLine(LEFT_MARGIN + i * MAP_IMAGE_SIZE, j * MAP_IMAGE_SIZE + TOP_MARGIN, i * MAP_IMAGE_SIZE + LEFT_MARGIN, (j + 1) * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(255, 255, 255), 0);
		}
	}


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


