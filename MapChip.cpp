#include "MapChip.h"
#include "Source\Screen.h"
#include "Input.h"

namespace
{
	//�������O�̕ϐ��͌�ł܂Ƃ߂�
	const int IMAGE_SIZE = { 32 };//�摜�̃T�C�Y

	const int MAP_CHIP_WIDTH = { 16 };//�`�b�v�̉���
	const int MAP_CHIP_HEIGHT = { 12 };//�`�b�v�̏c��

	const int MAP_CHIP_NUM_X = { 8 };//�}�b�v�`�b�v�E�B���h�E�̉����ѐ�
	const int MAP_CHIP_NUM_Y = { 24 };//�}�b�v�`�b�v�E�B���h�E��tate���ѐ�


	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X };
	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y };
	 
	const int DRAG_THRESHOLD = 5;
}

MapChip::MapChip()
	:GameObject(),isUpdate_(),bgHandle(MAP_CHIP_WIDTH* MAP_CHIP_HEIGHT, -1),
	isInMapChipArea_(false),selectedIndex_(-1), selected_({ 0,0 }),isHold_(false)
{
	LoadDivGraph("./bg.png", MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT, 
				  IMAGE_SIZE, IMAGE_SIZE, bgHandle.data());
	for (int i = 0; i < MAP_CHIP_NUM_X; i++) {
		for (int j = 0; j < MAP_CHIP_NUM_Y; j++) {
			Rect tmp{
			i * IMAGE_SIZE, j * IMAGE_SIZE,
			IMAGE_SIZE, IMAGE_SIZE
			};
			bgRects_.push_back(tmp);
		}
	}
	for (int i = 0; i < bgHandle.size(); i++)
	{
		HandleToIndex[bgHandle[i]] = i;
	}

}

MapChip::~MapChip()
{
	for (int i = 0; i < MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT; i++)
	{
		if (bgHandle[i] != -1)
		{
			DeleteGraph(bgHandle[i]);
			bgHandle[i] = -1;
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
		selected_.x = (mousePos.x - (Screen::WIDTH - MAP_CHIP_WIN_WIDTH)) / IMAGE_SIZE;
		selected_.y = mousePos.y / IMAGE_SIZE;
		if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
		{
			isHold_ = true;
			selectedIndex_ = bgHandle[selected_.y * MAP_CHIP_NUM_X + selected_.x];
		}
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
			DrawGraph(TOPLEFT_X + i * IMAGE_SIZE, TOPLEFT_Y + j * IMAGE_SIZE,
				bgHandle[i + j * MAP_CHIP_NUM_X], true);
		}
	}

	if (isInMapChipArea_)
	{
		//int xM = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
		//DrawBox(xM + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE,
		//	xM + (selected_.x + 1) * IMAGE_SIZE, (selected_.y + 1) * IMAGE_SIZE,
		//	GetColor(255, 0, 0), false, 2);
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		//DrawBox(xM + selected_.x * IMAGE_SIZE + 1, selected_.y * IMAGE_SIZE - 1,
		//	xM + (selected_.x + 1) * IMAGE_SIZE - 1, (selected_.y + 1) * IMAGE_SIZE+1,
		//	GetColor(255, 255, 0), true);
		//SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 0);

		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		//DrawBox(TOPLEFT_X + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE,
		//	TOPLEFT_X + selected_.x * IMAGE_SIZE + IMAGE_SIZE, selected_.y * IMAGE_SIZE + IMAGE_SIZE,
		//	GetColor(132, 255, 193), TRUE);
		////DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(132, 255, 193), true);
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//DrawBox(TOPLEFT_X + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE,
		//	TOPLEFT_X + selected_.x * IMAGE_SIZE + IMAGE_SIZE, selected_.y * IMAGE_SIZE + IMAGE_SIZE,
		//	GetColor(255, 0, 0), TRUE);


		int xM = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(xM + selected_.x * IMAGE_SIZE + 1, selected_.y * IMAGE_SIZE - 1,
			xM + (selected_.x + 1) * IMAGE_SIZE - 1, (selected_.y + 1) * IMAGE_SIZE + 1,
			GetColor(255, 255, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawBox(xM + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE,
			xM + (selected_.x + 1) * IMAGE_SIZE, (selected_.y + 1) * IMAGE_SIZE,
			GetColor(255, 0, 0), FALSE, 2);
	}

		if (isHold_)
		{
			Point mousePos;
			if (GetMousePoint(&mousePos.x, &mousePos.y) != 1)
			{
				DrawExtendGraph(mousePos.x, mousePos.y, mousePos.x + IMAGE_SIZE, mousePos.y + IMAGE_SIZE, selectedIndex_, TRUE);
				
			}
			if(Input::IsButtonUP(MOUSE_INPUT_RIGHT))
			{
				isHold_ = false;
				selectedIndex_ = -1;
			}
		}



}

bool MapChip::IsHold()
{
	return isHold_;
}

int MapChip::GetHoldImage()
{
	if (isHold_)
	{
		return selectedIndex_;
	}
	else
	{
		return -1;
	}
}

int MapChip::GetChipIndex(int handle)
{
	/*for (int i = 0; i < bgHandle.size(); i++)
	{
		if (handle == bgHandle[i])
			return i;
	}*/
	return HandleToIndex[handle];
}



	/*if (mx > Screen::WIDTH - 32 * 16 / 2)
	{
		DrawBox(TOPLEFT_X + mx / MAP_CHIP_WIDTH , TOPLEFT_Y + my / MAP_CHIP_HEIGHT , TOPLEFT_X + mx / MAP_CHIP_WIDTH * IMAGE_SIZE + 32, TOPLEFT_Y + my / MAP_CHIP_HEIGHT + 32, GetColor(255, 0, 0), false);
	}


	DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(255, 0, 0), false, 3);*/
