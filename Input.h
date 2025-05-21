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
}