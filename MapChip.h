#pragma once
#include "Library/GameObject.h"
#include <vector>

struct Point
{
    int x;
    int y;
};
struct Rect
{
    int x,y;
    int w,h;
};

class MapChip :
    public GameObject

{
    std::vector<int> bgHandle_;
    std::vector<Rect> bgRects_;
    bool isUpdate_;
    bool isInMapChipArea_;
    Point selected_;//�I�������}�b�v�`�b�v�̍��W
    int selectedIndex_;//�I�������}�b�v�`�b�v�̃C���f�b�N�X

public:
    MapChip();
    ~MapChip();
    void Update() override;
    void Draw() override;

};

