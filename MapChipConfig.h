#pragma once
struct MapChipConfig
{
	int TILES_PIX_SIZE;//1�^�C���̃s�N�Z���T�C�Y
	int TILES_X;	   //�}�b�v�`�b�v�V�[�g�̃}�b�v�`�b�v�̉����ѐ�
	int TILES_Y;	   //�}�b�v�`�b�v�V�[�g�̃}�b�v�`�b�v�̏c���ѐ�
	int MAPCHIP_VIEW_X;//�}�b�v�`�b�v�E�B���h�E�̉����ѐ�
	int MAPCHIP_VIEW_Y;//�}�b�v�`�b�v�E�B���h�E�̏c���ѐ�
	int MAPCHIP_WIN_WIDTH;//
	int MAPCHIP_WIN_HEIGHT;//
};

const MapChipConfig& GetMapChipConfig();



