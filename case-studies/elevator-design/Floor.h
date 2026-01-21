// Floor.h
#pragma once
#include <vector>
#include "HallPanel.h"
#include "Display.h"

class Floor {
    int floorNumber;
    std::vector<HallPanel*> panels;
    std::vector<Display*> displays;
public:
    Floor(int floorNumber, int numPanels, int numDisplays, int topFloor)
        : floorNumber(floorNumber)
    {
        for (int i = 0; i < numPanels; ++i)
            panels.push_back(new HallPanel(floorNumber, topFloor));
        for (int i = 0; i < numDisplays; ++i)
            displays.push_back(new Display());
    }
    ~Floor() {
        for (auto p : panels) delete p;
        for (auto d : displays) delete d;
    }
    int getFloorNumber() const { return floorNumber; }
    std::vector<HallPanel*>& getPanels() { return panels; }
    HallPanel* getPanel(int idx) { return panels[idx]; }
    std::vector<Display*>& getDisplays() { return displays; }
    Display* getDisplay(int idx) { return displays[idx]; }
};