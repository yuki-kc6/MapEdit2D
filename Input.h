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
}