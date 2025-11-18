//
// Created by bujor on 11/18/2025.
//

#ifndef ACADEMICMAGIC_H
#define ACADEMICMAGIC_H

#include<iostream>

class AcademicMagic {

    int progress = 0;
    const int threshHold = 5;
    bool active = false;


public:

    AcademicMagic(int progress, bool active);

    [[nodiscard]]int getProgress() const;

    [[nodiscard]]bool getActive() const;

    [[nodiscard]]int getThreshHold() const;

    void increaseProgress(int valueAmount);

    void activate();

    friend std::ostream& operator<<(std::ostream& os, const AcademicMagic& m);
};

#endif //ACADEMICMAGIC_H
