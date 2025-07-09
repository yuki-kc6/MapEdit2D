#include <Windows.h>
#include "MapEdit.h"
#include <cassert>
#include "Input.h"
#include "DxLib.h"
#include "MapChip.h"
#include<fstream>
#include <sstream>



MapEdit::MapEdit()
	:GameObject(), myMap_(MAP_WIDTH* MAP_HEIGHT, -1), //�����l��-1��20��20�̔z���z�u
	isInMapEditArea_(false)
{
	mapEditRect_ = { LEFT_MARGIN,TOP_MARGIN,
		MAP_WIDTH * MAP_IMAGE_SIZE,MAP_HEIGHT * MAP_IMAGE_SIZE };
	
}

MapEdit::~MapEdit()
{

}

void MapEdit::SetMap(Point p, int value)
{

	assert(p.x >= 0 && p.x < MAP_WIDTH);
	assert(p.y >= 0 && p.x < MAP_HEIGHT);
	myMap_[p.y * MAP_WIDTH + p.x] = value;

}

int MapEdit::GetMap(Point p) const
{
	assert(p.x >= 0 && p.x < MAP_WIDTH);
	assert(p.y >= 0 && p.x < MAP_HEIGHT);
	return myMap_[p.y * MAP_WIDTH + p.x];
}

void MapEdit::Update()
{
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1) {
		return;
	}
	//�}�E�X�̍��W���}�b�v�G�f�B�^�̈���ɂ��邩�ǂ����𔻒肷��
	isInMapEditArea_ = mousePos.x >= mapEditRect_.x && mousePos.x <= mapEditRect_.w + mapEditRect_.x && 
		mousePos.y >= mapEditRect_.y && mousePos.y <= mapEditRect_.h + mapEditRect_.y;
	
	if (!isInMapEditArea_)
	{
		return;
	}


	int gridX = (mousePos.x - LEFT_MARGIN) / MAP_IMAGE_SIZE;
	int gridY = (mousePos.y - TOP_MARGIN) / MAP_IMAGE_SIZE;
	
	drawAreaRect_ = { LEFT_MARGIN + gridX * MAP_IMAGE_SIZE,TOP_MARGIN + gridY * MAP_IMAGE_SIZE,
	MAP_IMAGE_SIZE,MAP_IMAGE_SIZE };

	if (Input::IsButtonKeep(MOUSE_INPUT_LEFT))
	{
		MapChip* mapChip = FindGameObject<MapChip>();

		if (Input::IsKeepKeyDown(KEY_INPUT_LSHIFT))
		{
			SetMap({ gridX,gridY }, -1);//�}�b�v�ɒl���Z�b�g
		}


		else if (mapChip && mapChip->IsHold())
		{
			SetMap({ gridX,gridY }, mapChip->GetHoldImage());//�}�b�v�ɒl���Z�b�g

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
	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			int value = GetMap({ i,j });
			if (value != 1)
			{
				DrawGraph(LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE,value, true);
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(LEFT_MARGIN, TOP_MARGIN, MAP_WIDTH * MAP_IMAGE_SIZE + LEFT_MARGIN, MAP_HEIGHT * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(255, 255, 0), false, 3);
	
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			DrawLine(i * MAP_IMAGE_SIZE + LEFT_MARGIN, TOP_MARGIN + j * MAP_IMAGE_SIZE, (i + 1) * MAP_IMAGE_SIZE + LEFT_MARGIN, TOP_MARGIN + j * MAP_IMAGE_SIZE, GetColor(255, 255, 255), 0);


			DrawLine(LEFT_MARGIN + i * MAP_IMAGE_SIZE, j * MAP_IMAGE_SIZE + TOP_MARGIN, i * MAP_IMAGE_SIZE + LEFT_MARGIN, (j + 1) * MAP_IMAGE_SIZE + TOP_MARGIN, GetColor(255, 255, 255), 0);
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
	//�撣���ăt�@�C���I���_�C�A���O���o����
	TCHAR filename[255] = "";
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(ofn);
	//�E�B���h�E�̃I�[�i�[���e�E�B���h�E�̃n���h��
	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "�S�Ẵt�@�C�� (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_OVERWRITEPROMPT;


	if (GetSaveFileName(&ofn))
	{
		printfDx("�t�@�C�����I�����ꂽ\n");
		//�t�@�C�����J���āA�Z�[�u
		//std::filesystem �t�@�C�����������o��
		//ofstream���J��
		std::ofstream openfile(filename);
		openfile << "#TinyMapData\n";

		MapChip* mc = FindGameObject<MapChip>();

		for (int j = 0; j < MAP_HEIGHT; j++) {
			for (int i = 0; i < MAP_WIDTH; i++) {

				int index;
				if (myMap_[j * MAP_WIDTH + i] != -1)
					index = mc->GetChipIndex(myMap_[j * MAP_WIDTH + i]);
				else
					index = -1;
				openfile << index << " ";
			}
			openfile << std::endl;
		}

		openfile.close();
	}
	else
	{
		//�t�@�C���̑I�����L�����Z��
		printfDx("�Z�[�u���L�����Z��\n");
		
	}

	printfDx("File Saved!!!\n");

	
	
	
}

void MapEdit::LoadMapData()
{
	//�撣���ăt�@�C���I���_�C�A���O���o����
	TCHAR filename[255] = "";
	OPENFILENAME ifn = { 0 };

	ifn.lStructSize = sizeof(ifn);
	//�E�B���h�E�̃I�[�i�[���e�E�B���h�E�̃n���h��
	ifn.hwndOwner = GetMainWindowHandle();
	ifn.lpstrFilter = "�S�Ẵt�@�C�� (*.*)\0*.*\0";
	ifn.lpstrFile = filename;
	ifn.nMaxFile = 255;
	//ifn.Flags = OFN_OVERWRITEPROMPT;

	//GetOpenFileName()

	if (GetOpenFileName(&ifn))
	{
		printfDx("�t�@�C�����I�����ꂽ��%s\n", filename);
		//�t�@�C�����J���āA�Z�[�u
		//std::filesystem �t�@�C�����������o��
		//ifstream���J�� input file stream
		std::ifstream inputfile(filename);
		//�t�@�C�����I�[�v���������ǂ����̓`�F�b�N���K�v
		std::string line;

		MapChip* mc = FindGameObject<MapChip>();
		myMap_.clear();//�}�b�v�����
		while (std::getline(inputfile, line))
		{
			// ��s�̓X�L�b�v
			if (line.empty()) continue;
			printfDx("%s\n", line.c_str());
			//�����ɓǂݍ��݂̏����������Ă���
			if (line[0] != '#')
			{
				std::istringstream iss(line);
				int tmp;//����Ɉ���ǂݍ���ł���
				while (iss >> tmp) {
					if (tmp == -1)
					{
						myMap_.push_back(-1);
					}
					else
						myMap_.push_back(mc->GetHandle(tmp));
					
				}
			}

		}
	}
	else
	{
		//�t�@�C���̑I�����L�����Z��
		printfDx("�Z�[�u���L�����Z��\n");
	}
	
}


