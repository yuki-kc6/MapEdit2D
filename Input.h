#pragma once


namespace Input {
	//�L�[�{�[�h�擾�֘A
	void KeyStateUpdate();//�L�[�{�[�h�̏�Ԃ��X�V
	bool IsKeyUP(int keyCode);//�L�[�������ꂽ�u��
	bool IsKeyDown(int keyCode);//�L�[�������ꂽ�u�ԁi���������j
	int IsKeepKeyDown(int keyCode);//�L�[��������Ă����

	bool IsMouseDown();//�}�E�X�̃{�^���������ꂽ�u��
	bool IsMouseUP();//�}�E�X�̃{�^���������ꂽ�u��
	bool IsMouseKeep();//�}�E�X�̃{�^����������Ă��
	bool IsButtonDown(int button);//�{�^���������ꂽ�u��
	bool IsButtonUP(int button);//�{�^���������ꂽ�u��
	bool IsButtonKeep(int button);//�{�^����������Ă����
}

//MOUSE_INPUT_LEFT	=> 0x0001 ->0000 0000 0000 0001
//MOUSE_INPUT_MIDDLE=> 0x0004 ->0000 0000 0000 0100
//MOUSE_INPUT_RIGHT => 0x0002 ->0000 0000 0000 0010
//0x -> 16�i��
//
//0xAB8D -> 1010 1011 1000 1101
// 
//1001 0010 1110 1010 ->0x92EA
//�e�r�b�g��true false�̃t���O�Ƃ��Ďg�����r�b�g�t���O		