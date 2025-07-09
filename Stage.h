#pragma once
#include "Library\\GameObject.h"
#include <vector>//可変長配列
#include "MapChip.h"
#include "MapEdit.h"

class Stage :
    public GameObject
{
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
private:
    // int *bghandle;//背景画像のハンドルの配列へのポインタ（配列自体）
//  std::vector<int> bgHandle_;
    MapChip* mapChip_;//マップチップのポイント
    MapEdit* mapEdit_;//マップエディタのポインタ

};
