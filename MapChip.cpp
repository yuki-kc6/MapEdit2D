#define NOMINMAX
#include "MapChip.h"+
#include "Source\Screen.h"
#include "Input.h"
#include <algorithm>

namespace
{
   //	//同じ名前の変数は後でまとめる
//	const int IMAGE_SIZE = { 32 };//画像のサイズ
//
//	const int MAP_CHIP_WIDTH = { 16 };//チップの横数
//	const int MAP_CHIP_HEIGHT = { 12 };//チップの縦数
//
//	const int MAP_CHIP_NUM_X = { 8 };//マップチップウィンドウの横並び数
//	const int MAP_CHIP_NUM_Y = { 24 };//マップチップウィンドウのtate並び数
//
//
//	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X };
//	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y };
//	 
//	const int DRAG_THRESHOLD = 5;
}

MapChip::MapChip()
	:GameObject(),cfg_(GetMapChipConfig()),isUpdate_(),bgHandle(cfg_.TILES_X*cfg_.TILES_Y, -1),
	isInMapChipArea_(false),selectedIndex_(-1), selected_({ 0,0 }),isHold_(false),ScrollOffset_({0,0})
{

	LoadDivGraph("./bg.png", cfg_.TILES_X* cfg_.TILES_Y,
		cfg_.TILES_X, cfg_.TILES_Y,
		 cfg_.TILES_PIX_SIZE, cfg_.TILES_PIX_SIZE, bgHandle.data());
	
	for (int i = 0; i < bgHandle.size(); i++)
	{
		HandleToIndex[bgHandle[i]] = i;
	}

}

MapChip::~MapChip()
{
	for (int i = 0; i < cfg_.TILES_X * cfg_.TILES_Y; i++)
	{
		if (bgHandle[i] != -1)
		{
			DeleteGraph(bgHandle[i]);
			bgHandle[i] = -1;
		}
	}
}

Point MapChip::GetViewOrigin()const {
	return { Screen::WIDTH - cfg_.MAPCHIP_WIN_WIDTH,0  };
};

bool MapChip::IsInMapChipArea(const Point& mouse)const
{
	return(mouse.x > GetViewOrigin().x && mouse.x<Screen::WIDTH 
		&& mouse.y>GetViewOrigin().y && mouse.y < Screen::HEIGHT);
}


Point MapChip::ScreenToChipIndex(const Point& mouse)const 
{
	int localX = (mouse.x - GetViewOrigin().x) / cfg_.TILES_PIX_SIZE;
	int localY = mouse.y / cfg_.TILES_PIX_SIZE;
	return { localX,localY };

}

void MapChip::Update()
{

	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1) {
		return;
	}

	isInMapChipArea_ = IsInMapChipArea(mousePos);

	if (isInMapChipArea_)
	{
		if (Input::IsKeyDown(KEY_INPUT_LEFT))
			ScrollOffset_.x = std::max(0, ScrollOffset_.x - 1);
			//ScrollOffset_.x = ScrollOffset_.x - 1;
		if (Input::IsKeyDown(KEY_INPUT_RIGHT))
			ScrollOffset_.x = std::min(std::max(0, cfg_.TILES_X-cfg_.MAPCHIP_VIEW_X ), ScrollOffset_.x + 1);
			//ScrollOffset_.x = ScrollOffset_.x + 1;
		
		if (Input::IsKeyDown(KEY_INPUT_UP))
			ScrollOffset_.y = std::max(0, ScrollOffset_.y - 1);
		if (Input::IsKeyDown(KEY_INPUT_DOWN))
			ScrollOffset_.y = std::min(std::max(0, cfg_.TILES_Y - cfg_.MAPCHIP_VIEW_Y), ScrollOffset_.y + 1);

		selected_ = ScreenToChipIndex(mousePos);
		int index = selected_.y * cfg_.TILES_X + selected_.x;
		
		if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
		{
			isHold_ = true;
			selectedIndex_ = bgHandle[index];
		}
	}
	else
	{
		isInMapChipArea_ = false;
	}
}

void MapChip::Draw()
{
	for (int i = 0; i < cfg_.TILES_X; i++) {
		for (int j = 0; j < cfg_.TILES_Y/2; j++) {
			int index = (i + ScrollOffset_.x + j * cfg_.TILES_X)+cfg_.TILES_X*ScrollOffset_.y;
			if (index < 0 || index >= bgHandle.size())
				continue;
			DrawGraph(GetViewOrigin().x + i * cfg_.TILES_PIX_SIZE,
					  GetViewOrigin().y + j * cfg_.TILES_PIX_SIZE,
				      bgHandle[index], TRUE);
		}
	}

	//マップチップの選択範囲をハイライト表示
	if (isInMapChipArea_)
	{

		int px = GetViewOrigin().x + selected_.x * cfg_.TILES_PIX_SIZE;
		int py = selected_.y * cfg_.TILES_PIX_SIZE;
		
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(px, py ,
			px+cfg_.TILES_PIX_SIZE , py+ cfg_.TILES_PIX_SIZE ,
			GetColor(255, 255, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawBox(px, py,px+cfg_.TILES_PIX_SIZE,py+cfg_.TILES_PIX_SIZE,
			GetColor(255, 0, 0), FALSE, 2);
	}

		if (isHold_)
		{
			Point mousePos;
			if (GetMousePoint(&mousePos.x, &mousePos.y) != 1)
			{
				DrawExtendGraph(mousePos.x, mousePos.y, mousePos.x + cfg_.TILES_PIX_SIZE, mousePos.y + cfg_.TILES_PIX_SIZE, selectedIndex_, TRUE);
				
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
