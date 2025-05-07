#include "MapChip.h"
#include "Source\Screen.h"

namespace
{
	//�������O�̕ϐ��͌�ł܂Ƃ߂�
	const int IMAGE_SIZE = { 32 };//�摜�̃T�C�Y

	const int MAP_CHIP_WIDTH = { 16 };//�`�b�v�̉���
	const int MAP_CHIP_HEIGHT = { 12 };//�`�b�v�̏c��

	const int MAP_CHIP_NUM_X = { 8 };//�}�b�v�`�b�v�E�B���h�E�̉����ѐ�
	const int MAP_CHIP_NUM_Y = {24 };//�}�b�v�`�b�v�E�B���h�E��tate���ѐ�


	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_WIDTH / 2 };
	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * 24*8 };
	 
}

MapChip::MapChip()
	:GameObject(),bgHandle_(MAP_CHIP_WIDTH* MAP_CHIP_HEIGHT, -1)
{
	LoadDivGraph("./bg.png", MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT, 
				  IMAGE_SIZE, IMAGE_SIZE, bgHandle_.data());
}

MapChip::~MapChip()
{
	for (int i = 0; i < MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT; i++)
	{
		if (bgHandle_[i] != -1)
		{
			DeleteGraph(bgHandle_[i]);
			bgHandle_[i] = -1;
		}
	}
}

void MapChip::Update()
{

}

void MapChip::Draw()
{
	int TOPLEFT_X = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	int TOPLEFT_Y = 0;
	int RIGHTBOTTOM_X = Screen::WIDTH;
	int RIGHTBOTTOM_Y = MAP_CHIP_WIN_HEIGHT;

	for (int i = 0; i < MAP_CHIP_NUM_X; i++)
	{
		for (int j = 0; j < MAP_CHIP_NUM_Y; j++)
		{
			DrawGraph(TOPLEFT_X+i*IMAGE_SIZE,TOPLEFT_Y+j*IMAGE_SIZE,
				bgHandle_[i+j*MAP_CHIP_NUM_X],true);
		}
	}



	DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(255, 0, 0), false, 3);
}
