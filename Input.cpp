#include "Input.h"
#include "DxLib.h"

namespace Input {
	//キーボード取得関連
	const int KEY_MAX = 255;
	char keyBuff[KEY_MAX];		//キーバッファ (現フレーム)
	char keyBuffOld[KEY_MAX];	//1つ前のキーバッファ(前フレーム) 
	char key_down[KEY_MAX];		//押された瞬間 
	char key_up[KEY_MAX];		//離された瞬間 
	char Key_Keep[KEY_MAX];		//押しっぱなし
	int mousePre;//前のフレームのマウス状態
	int mouseNow;//現のフレームのマウス状態
}

void Input::KeyStateUpdate()
{
	memcpy_s(keyBuffOld, sizeof(char) * KEY_MAX, keyBuff, sizeof(char) * KEY_MAX);

	GetHitKeyStateAll(keyBuff);//全てのキーの状態を取得 

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (keyBuff[i] && keyBuffOld[i]) Key_Keep[i]++;
		int key_xor = keyBuff[i] ^ keyBuffOld[i];	//前フレームと現フレームのxor
		if (key_xor) Key_Keep[i] = 0;
		key_down[i] = key_xor & keyBuff[i];		//押された瞬間 = (現フレームとkey_xorのAND) 
		key_up[i] = key_xor & keyBuffOld[i];	//離された瞬間 = (前フレームとkey_xorのAND) 

	}
	mousePre = mouseNow;//前のフレームのマウスの状態を保存
	mouseNow=GetMouseInput();//マウスの状態を取得


}




bool Input::IsKeyUP(int keyCode)
{
	return(key_up[keyCode]);
}

bool Input::IsKeyDown(int keyCode)
{
	return(key_down[keyCode]);
}

int Input::IsKeepKeyDown(int keyCode)
{
	return(Key_Keep[keyCode]);
}

//マウスの状態を取得する関数群
//mouseNow.mousePre==0　押されていない　!=0は押されてる




bool Input::IsMouseDown()
{
	return (mouseNow == 1 && mousePre == 0);
}

bool Input::IsMouseUP()
{
	return (!mouseNow && mousePre);
}

bool Input::IsMouseKeep()
{
	return (mouseNow == 1 && mousePre == 1);
}

bool Input::IsButtonDown(int button)
{
	return(((mousePre & button) == 0) && ((mouseNow & button) != 0));
}

bool Input::IsButtonUP(int button)
{
	return (((mousePre & button) != 0 && (mouseNow & button) == 0));
}

bool Input::IsButtonKeep(int button)
{
	return (((mousePre & button) != 0 && (mouseNow & button) != 0));
}
