#pragma once
#include "HallButton.h"
#include "Direction.h"

class HallPanel {
    HallButton* up;
    HallButton* down;
public:
    HallPanel(int floorNumber, int topFloor)
        : up(floorNumber == topFloor ? nullptr : new HallButton(Direction::UP)),
          down(floorNumber == 0 ? nullptr : new HallButton(Direction::DOWN)) {}
    ~HallPanel() { delete up; delete down; }
    HallButton* getUpButton() const { return up; }
    HallButton* getDownButton() const { return down; }
};