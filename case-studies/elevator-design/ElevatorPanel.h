#pragma once
#include <vector>
#include "ElevatorButton.h"
#include "DoorButton.h"
#include "EmergencyButton.h"

class ElevatorPanel {
    std::vector<ElevatorButton*> floorButtons;
    DoorButton openButton;
    DoorButton closeButton;
    EmergencyButton emergencyButton;
public:
    ElevatorPanel(int numFloors) {
        for (int i = 0; i < numFloors; ++i)
            floorButtons.push_back(new ElevatorButton(i));
    }
    ~ElevatorPanel() {
        for (auto b : floorButtons) delete b;
    }
    std::vector<ElevatorButton*>& getFloorButtons() { return floorButtons; }
    DoorButton& getOpenButton() { return openButton; }
    DoorButton& getCloseButton() { return closeButton; }
    EmergencyButton& getEmergencyButton() { return emergencyButton; }
    void enterEmergency() { emergencyButton.pressDown(); }
    void exitEmergency() { emergencyButton.reset(); }
};