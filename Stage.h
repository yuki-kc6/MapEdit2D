#pragma once
#include "Library\\GameObject.h"
#include <vector>//�ϒ��z��
#include "MapChip.h"
#include "MapEdit.h"

class Stage :
    public GameObject
{
   // int *bghandle;//�w�i�摜�̃n���h���̔z��ւ̃|�C���^�i�z�񎩑́j
  //  std::vector<int> bgHandle_;
    MapChip* mapChip_;
    MapEdit* mapEdit_;
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
};
