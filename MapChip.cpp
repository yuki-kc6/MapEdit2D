#include "MapChip.h"
#include "Source\Screen.h"
#include "Input.h"

namespace
{
	//同じ名前の変数は後でまとめる
	const int IMAGE_SIZE = { 32 };//画像のサイズ

	const int MAP_CHIP_WIDTH = { 16 };//チップの横数
	const int MAP_CHIP_HEIGHT = { 12 };//チップの縦数

	const int MAP_CHIP_NUM_X = { 8 };//マップチップウィンドウの横並び数
	const int MAP_CHIP_NUM_Y = {24 };//マップチップウィンドウのtate並び数


	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_WIDTH / 2 };
	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * 24*8 };
	 
}

MapChip::MapChip()
	:GameObject(),bgHandle_(MAP_CHIP_WIDTH* MAP_CHIP_HEIGHT, -1),isInMapChipArea_(true),selectedIndex_(-1), selected_({ 0,0 }),isUpdate_(false)
{
	LoadDivGraph("./bg.png", MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT, 
				  IMAGE_SIZE, IMAGE_SIZE, bgHandle_.data());
	for (int i = 0; i < MAP_CHIP_NUM_X; i++) {
		for (int j = 0; j < MAP_CHIP_NUM_Y; j++) {
			Rect tmp{
				i * IMAGE_SIZE, j * IMAGE_SIZE,
				IMAGE_SIZE, IMAGE_SIZE
			};
			bgRects_.push_back(tmp);
		}
	}

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

	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1) {
		return;
	}

	isInMapChipArea_ = (mousePos.x > Screen::WIDTH - MAP_CHIP_WIN_WIDTH && mousePos.x < Screen::WIDTH &&
		mousePos.y>0 && mousePos.y < MAP_CHIP_WIN_HEIGHT);

	if (isInMapChipArea_)
	{
		selected_.x = (mousePos.x - (Screen::WIDTH - MAP_CHIP_WIN_WIDTH))/IMAGE_SIZE;
		selected_.y = mousePos.y / IMAGE_SIZE;
		/*if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
		{
			selectedIndex_ = selected_.y + MAP_CHIP_NUM_X + selected_.y;
		}*/
	}
	else
	{
		isInMapChipArea_ = false;
	}
	

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

	if (isInMapChipArea_)
	{
		/*int xM = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
		DrawBox(xM + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE,
			xM + (selected_.x + 1) * IMAGE_SIZE, (selected_.y + 1) * IMAGE_SIZE,
			GetColor(255, 0, 0), false, 2);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(xM + selected_.x * IMAGE_SIZE + 1, selected_.y * IMAGE_SIZE - 1,
			xM + (selected_.x + 1) * IMAGE_SIZE - 1, (selected_.y + 1) * IMAGE_SIZE+1,
			GetColor(255, 255, 0), true);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 0);*/

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100); 
		DrawBox(TOPLEFT_X + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE, 
			TOPLEFT_X + selected_.x * IMAGE_SIZE + IMAGE_SIZE, selected_.y * IMAGE_SIZE + IMAGE_SIZE, 
			GetColor(132, 255, 193), TRUE);
		//DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(132, 255, 193), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		DrawBox(TOPLEFT_X + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE, 
			TOPLEFT_X + selected_.x * IMAGE_SIZE + IMAGE_SIZE, selected_.y * IMAGE_SIZE + IMAGE_SIZE, 
			GetColor(255, 0, 0), TRUE);
	
		



	}



	/*if (mx > Screen::WIDTH - 32 * 16 / 2)
	{
		DrawBox(TOPLEFT_X + mx / MAP_CHIP_WIDTH , TOPLEFT_Y + my / MAP_CHIP_HEIGHT , TOPLEFT_X + mx / MAP_CHIP_WIDTH * IMAGE_SIZE + 32, TOPLEFT_Y + my / MAP_CHIP_HEIGHT + 32, GetColor(255, 0, 0), false);
	}


	DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(255, 0, 0), false, 3);*/
}
