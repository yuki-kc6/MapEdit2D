#include <Windows.h>
#include "MapEdit.h"
#include <cassert>
#include "Input.h"
#include "DxLib.h"
#include "MapChip.h"
#include<fstream>
#include <sstream>
#include <iostream>


MapEdit::MapEdit()
	:GameObject(),efg_(GetMapEditConfig()), myMap_(efg_.MAPEDIT_WIN_WIDTH * efg_.MAPEDIT_WIN_HEIGHT, -1), //初期値を-1で20＊20の配列を配置
	isInMapEditArea_(false)
{
	mapEditRect_ = { efg_.LEFT_MARGIN,efg_.TOP_MARGIN,
		efg_.MAPEDIT_WIN_WIDTH * efg_.MAP_IMAGE_SIZE,efg_.MAPEDIT_WIN_HEIGHT * efg_.MAP_IMAGE_SIZE };
	
}

MapEdit::~MapEdit()
{

}

void MapEdit::SetMap(Point p, int value)
{

	assert(p.x >= 0 && p.x < efg_.MAPEDIT_WIN_WIDTH);
	assert(p.y >= 0 && p.x < efg_.MAPEDIT_WIN_HEIGHT);
	myMap_[p.y * efg_.MAPEDIT_WIN_WIDTH + p.x] = value;

}

int MapEdit::GetMap(Point p) const
{
	assert(p.x >= 0 && p.x < efg_.MAPEDIT_WIN_WIDTH);
	assert(p.y >= 0 && p.x < efg_.MAPEDIT_WIN_HEIGHT);
	return myMap_[p.y * efg_.MAPEDIT_WIN_WIDTH + p.x];
}

void MapEdit::Update()
{
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1) {
		return;
	}
	//マウスの座標がマップエディタ領域内にいるかどうかを判定する
	isInMapEditArea_ = mousePos.x >= mapEditRect_.x && mousePos.x <= mapEditRect_.w + mapEditRect_.x && 
		mousePos.y >= mapEditRect_.y && mousePos.y <= mapEditRect_.h + mapEditRect_.y;
	
	if (!isInMapEditArea_)
	{
		return;
	}


	int gridX = (mousePos.x - efg_.LEFT_MARGIN) / efg_.MAP_IMAGE_SIZE;
	int gridY = (mousePos.y - efg_.TOP_MARGIN) / efg_.MAP_IMAGE_SIZE;
	
	drawAreaRect_ = { efg_.LEFT_MARGIN + gridX * efg_.MAP_IMAGE_SIZE,
		efg_.TOP_MARGIN + gridY * efg_.MAP_IMAGE_SIZE,
		efg_.MAP_IMAGE_SIZE,efg_.MAP_IMAGE_SIZE };

	if (Input::IsButtonKeep(MOUSE_INPUT_LEFT))
	{
		MapChip* mapChip = FindGameObject<MapChip>();

		if (Input::IsKeepKeyDown(KEY_INPUT_LSHIFT))
		{
			SetMap({ gridX,gridY }, -1);//マップに値をセット
		}


		else if (mapChip && mapChip->IsHold())
		{
			SetMap({ gridX,gridY }, mapChip->GetHoldImage());//マップに値をセット

		}

	}
	if (Input::IsKeyDown(KEY_INPUT_S))
	{
		SaveMapData();
	}
	if (Input::IsKeyDown(KEY_INPUT_L))
	{
		LoadMapData();
	}

}

void MapEdit::Draw()
{
	for (int j = 0; j < efg_.MAPEDIT_WIN_HEIGHT; j++)
	{
		for (int i = 0; i < efg_.MAPEDIT_WIN_WIDTH; i++)
		{
			int value = GetMap({ i,j });
			if (value != 1)
			{
				DrawGraph(efg_.LEFT_MARGIN + i * efg_.MAP_IMAGE_SIZE, 
					efg_.TOP_MARGIN + j * efg_.MAP_IMAGE_SIZE,value, true);
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(efg_.LEFT_MARGIN, efg_.TOP_MARGIN, 
		efg_.MAPEDIT_WIN_WIDTH * efg_.MAP_IMAGE_SIZE + efg_.LEFT_MARGIN, 
		efg_.MAPEDIT_WIN_HEIGHT * efg_.MAP_IMAGE_SIZE + efg_.TOP_MARGIN, 
		GetColor(255, 255, 0), false, 3);
	
	for (int i = 0; i < efg_.MAPEDIT_WIN_WIDTH; i++) {
		for (int j = 0; j < efg_.MAPEDIT_WIN_HEIGHT; j++)
		{
			DrawLine(i * efg_.MAP_IMAGE_SIZE + efg_.LEFT_MARGIN, 
				efg_.TOP_MARGIN + j * efg_.MAP_IMAGE_SIZE, 
				(i + 1) * efg_.MAP_IMAGE_SIZE + efg_.LEFT_MARGIN, 
				efg_.TOP_MARGIN + j * efg_.MAP_IMAGE_SIZE, GetColor(255, 255, 255), 0);


			DrawLine(efg_.LEFT_MARGIN + i * efg_.MAP_IMAGE_SIZE, 
				j * efg_.MAP_IMAGE_SIZE + efg_.TOP_MARGIN, i * efg_.MAP_IMAGE_SIZE + efg_.LEFT_MARGIN, (j + 1) * efg_.MAP_IMAGE_SIZE + efg_.TOP_MARGIN, GetColor(255, 255, 255), 0);
		}
	}
	if (isInMapEditArea_)
	{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(drawAreaRect_.x, drawAreaRect_.y, drawAreaRect_.x + drawAreaRect_.w, drawAreaRect_.y + drawAreaRect_.h, GetColor(255, 255, 0), true, 3);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void MapEdit::SaveMapData()
{
	//頑張ってファイル選択ダイアログを出す回
	TCHAR filename[255] = "";
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(ofn);
	//ウィンドウのオーナー＝親ウィンドウのハンドル
	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_OVERWRITEPROMPT;


	if (GetSaveFileName(&ofn))
	{
		printfDx("ファイルが選択された\n");
		//ファイルを開いて、セーブ
		//std::filesystem ファイル名だけ取り出す
		//ofstreamを開く
		std::ofstream openfile(filename);
		openfile << "#TinyMapData\n";

		MapChip* mc = FindGameObject<MapChip>();

		for (int j = 0; j < efg_.MAPEDIT_WIN_HEIGHT; j++) {
			for (int i = 0; i < efg_.MAPEDIT_WIN_WIDTH; i++) {

				int index;
				if (myMap_[j * efg_.MAPEDIT_WIN_WIDTH + i] != -1)
					index = mc->GetChipIndex(myMap_[j * efg_.MAPEDIT_WIN_WIDTH + i]);
				else
					index = -1;

				if (i == efg_.MAPEDIT_WIN_WIDTH - 1)
				{
					openfile << index;
				}
				else
				{
					openfile << index << ",";
				}

				
			}
			openfile << std::endl;
		}

		openfile.close();
		printfDx("File Saved!!!\n");
	}
}

void MapEdit::LoadMapData()
{
	//頑張ってファイル選択ダイアログを出す回
	TCHAR filename[255] = "";
	OPENFILENAME ifn = { 0 };

	ifn.lStructSize = sizeof(ifn);
	//ウィンドウのオーナー＝親ウィンドウのハンドル
	ifn.hwndOwner = GetMainWindowHandle();
	ifn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	ifn.lpstrFile = filename;
	ifn.nMaxFile = 255;
	//ifn.Flags = OFN_OVERWRITEPROMPT;

	//GetOpenFileName()

	if (GetOpenFileName(&ifn))
	{
		printfDx("ファイルが選択された→%s\n", filename);
		//ファイルを開いて、セーブ
		//std::filesystem ファイル名だけ取り出す
		//ifstreamを開く input file stream
		std::ifstream inputfile(filename);
		//ファイルがオープンしたかどうかはチェックが必要
		std::string line;

		//マップチップの情報を取りたい
		MapChip* mc = FindGameObject<MapChip>();
		myMap_.clear();//マップを空に
		while (std::getline(inputfile, line))
		{
			// 空行はスキップ
			if (line.empty()) continue;
			//printfDx("%s\n", line.c_str());
			//ここに読み込みの処理を書く
			if (line[0] != '#')
			{
				std::istringstream iss(line);
				std::string tmp;//これに一個ずつ読み込んでいく
				while (getline(iss, tmp, ',')) {
					/*if (tmp == -1)
						myMap_.push_back(-1);
					else
						myMap_.push_back(mc->GetHandle(tmp));*/
					printfDx("%s", tmp.c_str());
					if (tmp == "-1")
					{
						myMap_.push_back(-1);
					}
					else
					{
						int index = std::stoi(tmp);
						int handle = mc->GetHandle(index);
						myMap_.push_back(handle);//マップにハンドルをセット
					}
				}
			}
		}
	}

	
	
}


