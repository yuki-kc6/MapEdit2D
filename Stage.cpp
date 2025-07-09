#include "Stage.h"
#include "Input.h"
#include "Source/Screen.h"
namespace
{
	//const int IMAGE_SIZE = { 32 };//�摜�̃T�C�Y
	//const int MAP_WIDTH = { 32 };
	//const int MAP_HEIGHT = { 22 };
	//const int MAP_CHIP_WIDTH = { 16 };
	//const int MAP_CHIP_HEIGHT = { 12 };

	//const int myMap[MAP_HEIGHT][MAP_WIDTH]
	//{
	//	{55,55,55,55,0,0,0,0,0,0,0,102,0,0,0,0,0,0,0,0,0,6,57,57,57,57,57,57,57,57,57,57},
	//	{55,55,55,55,0,102,0,0,0,0,0,0,0,0,0,0,0,102,0,0,0,6,57,57,57,57,57,57,57,57,57,57},
	//	{55,55,55,55,0,0,0,102,0,0,102,0,0,102,0,102,0,0,0,0,0,6,57,57,57,57,57,57,57,57,57,57},
	//	{55,55,55,55,0,102,0,0,0,0,102,102,0,0,0,0,0,102,0,0,0,0,6,57,57,57,57,57,57,57,57,57},
	//	{55,55,55,55,0,0,0,0,0,102,0,0,0,0,102,0,0,0,0,0,0,0,6,57,57,57,57,57,57,57,57,57},
	//	{55,55,55,55,0,0,102,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,57,57,57,57,57,57,57,57,57},
	//	{55,55,55,55,0,0,0,0,0,0,0,0,0,102,0,5,0,0,0,0,0,0,6,6,57,57,57,57,57,57,57,57},
	//	{55,55,55,55,0,0,0,0,0,54,54,54,54,0,0,5,0,0,0,0,0,0,0,6,6,57,57,57,57,57,57,57},
	//	{55,55,55,55,0,0,0,54,54,54,54,54,0,0,0,5,0,0,0,0,0,0,0,6,6,57,57,57,57,57,57,57},
	//	{55,55,55,55,0,0,54,54,54,54,0,54,0,0,0,5,0,0,0,0,0,0,0,0,6,6,57,57,57,57,57,57},
	//	{55,55,55,55,54,54,54,54,54,0,54,54,5,0,0,5,0,0,0,0,0,0,0,0,0,6,6,6,57,57,57,57},
	//	{55,55,55,55,54,54,54,0,0,54,0,0,5,0,0,5,0,0,5,0,0,0,0,0,0,0,0,6,6,57,57,57},
	//	{55,55,55,55,0,0,0,0,0,0,0,0,5,0,0,5,0,0,5,0,0,0,0,0,0,0,0,0,6,57,57,57},
	//	{55,55,55,55,0,0,0,0,0,0,0,0,5,5,0,5,5,5,0,0,0,0,0,0,0,0,0,0,6,6,6,57},
	//	{55,55,55,55,0,0,0,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,8,8,8,8,8},
	//	{55,55,55,55,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,105},
	//	{55,55,55,55,0,0,0,0,0,0,0,0,5,5,5,5,5,5,0,0,0,0,0,8,8,8,8,8,8,8,105,105},
	//	{55,55,55,55,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,8,8,8,8,8,105,105,105,105,105},
	//	{55,55,55,55,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,8,8,8,105,105,105,105,105,105,105,105},
	//	{55,55,55,55,0,0,0,0,0,0,0,0,0,0,5,5,0,5,0,17,24,8,105,105,105,105,105,105,105,105,105,105},
	//	{55,55,55,55,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0,17,105,105,105,105,105,105,105,105,105,105,105,105},
	//	{55,55,55,55,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,17,17,105,105,105,105,105,105,105,105,105,105,105 }
	//};
}


Stage::Stage()
	:GameObject()
{

	////bgHandle_ = new int[MAP_WIDTH * MAP_HEIGHT];//�K�v�Ȏ��ɕK�v�Ȑ������z�������������@
	//bgHandle_ = std::vector<int>(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT,-1);
	////bgHandle_=LoadGraph("./bg.png");
	//LoadDivGraph("./bg.png", MAP_CHIP_WIDTH*MAP_CHIP_HEIGHT, MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT,
	//				IMAGE_SIZE, IMAGE_SIZE, bgHandle_.data());
	mapChip_ = new MapChip();//�}�b�v�`�b�v�̃C���X�^���X
	mapEdit_ = new MapEdit();//�}�b�v�G�f�B�^�̃C���X�^���X
	//mousePos_.x = -10; //�}�E�X�̍��W��������
	//mousePos_.y = -10;//�}�E�X�̍��W��������	
	
}

Stage::~Stage()
{
	/*for (int i = 0; i < MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT; i++)
	{
		if (bgHandle_[i] != -1)
		{
			DeleteGraph(bgHandle_[i]);
			bgHandle_[i] = -1;
		}
	}*/
	//delete[] bgHandle_;//�z��̉���@�����ŎB�������͎̂����ŏ���
	delete mapChip_;
	//delete mapEdit_;
}

void Stage::Update()
{



	//if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	//{
	//	//�����ꂽ�u�Ԃ̏���
	//	DxLib::printfDx("���������ꂽ!!\n");
	//}
	//if (Input::IsButtonDown(MOUSE_INPUT_RIGHT))
	//{
	//	//�����ꂽ�u�Ԃ̏���
	//	DxLib::printfDx("�E�������ꂽ!!\n");
	//}
	//if (Input::IsButtonKeep(MOUSE_INPUT_LEFT))
	//{
	//	//������Ă���Ԃ̏���
	//	DxLib::printfDx("����������Ă���!!\n");
	//}
	//if (Input::IsButtonKeep(MOUSE_INPUT_RIGHT))
	//{
	//	//������Ă���Ԃ̏���
	//	DxLib::printfDx("�E��������Ă���!!\n");
	//}
	//if (Input::IsButtonUP(MOUSE_INPUT_LEFT))
	//{
	//	//�����ꂽ�u�Ԃ̏���
	//	DxLib::printfDx("���������ꂽ!!\n");
	//}
	//if (Input::IsButtonUP(MOUSE_INPUT_RIGHT))
	//{
	//	//�����ꂽ�u�Ԃ̏���
	//	DxLib::printfDx("�E�������ꂽ!!\n");
	//}
	//int mx=-1, my=-1;
	//if (GetMousePoint(&mx, &my) == 0)
	//{
	////	DxLib::printfDx("�}�E�X�̍��W(%d,%d)\n", mx, my);
	//}
	//else
	//{
	//	DxLib::printfDx("�}�E�X�̍��W�擾���s\n");
	//}
}

void Stage::Draw()
{
	//{
		//for (int j = 0; j < MAP_HEIGHT; j++) 
		//{
		//	for (int i = 0; i < MAP_WIDTH; i++)
		//	{

		//		/*int col = myMap[j][i] % MAP_CHIP_WIDTH;
		//		int row = myMap[j][i] / MAP_CHIP_WIDTH;*/
		//		if (bgHandle_[myMap[j][i]] != -1)
		//			DrawGraph(i * IMAGE_SIZE, j * IMAGE_SIZE, bgHandle_[myMap[j][i]], true);
		//		//DrawRectGraph(i * IMAGE_SIZE, j * IMAGE_SIZE, col*IMAGE_SIZE, row*IMAGE_SIZE , IMAGE_SIZE, IMAGE_SIZE, bgHandle_, true,false);
		//	}
		//}
	

	
}
