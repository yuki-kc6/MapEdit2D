#pragma once


namespace Input {
	//キーボード取得関連
	void KeyStateUpdate();//キーボードの状態を更新
	bool IsKeyUP(int keyCode);//キーが離された瞬間
	bool IsKeyDown(int keyCode);//キーが押された瞬間（押し下げ）
	int IsKeepKeyDown(int keyCode);//キーが押されている間

	bool IsMouseDown();//マウスのボタンが押された瞬間
	bool IsMouseUP();//マウスのボタンが離された瞬間
	bool IsMouseKeep();//マウスのボタンが押されてる間
	bool IsButtonDown(int button);//ボタンが押された瞬間
	bool IsButtonUP(int button);//ボタンが離された瞬間
	bool IsButtonKeep(int button);//ボタンが押されている間
}

//MOUSE_INPUT_LEFT	=> 0x0001 ->0000 0000 0000 0001
//MOUSE_INPUT_MIDDLE=> 0x0004 ->0000 0000 0000 0100
//MOUSE_INPUT_RIGHT => 0x0002 ->0000 0000 0000 0010
//0x -> 16進数
//
//0xAB8D -> 1010 1011 1000 1101
// 
//1001 0010 1110 1010 ->0x92EA
//各ビットをtrue falseのフラグとして使う→ビットフラグ		