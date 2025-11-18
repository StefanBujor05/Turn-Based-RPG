//
// Created by bujor on 11/18/2025.
//

#include "AcademicMagic.h"


    AcademicMagic::AcademicMagic(int progress, bool active): progress(progress), active(active){}

    [[nodiscard]]int AcademicMagic::getProgress() const {
        return progress;
    }

    [[nodiscard]]bool AcademicMagic::getActive() const {
        return active;
    }

    [[nodiscard]]int AcademicMagic::getThreshHold() const {
        return threshHold;
    }

    void AcademicMagic::increaseProgress(int valueAmount) {
        progress += valueAmount;
        if (progress > threshHold)
            progress = threshHold;
    }

    void AcademicMagic::activate() {
        active = true;
    }


std::ostream& operator<<(std::ostream& os, const AcademicMagic& m) {
    os<<m.progress<<" "<<m.threshHold<<m.active<<" \n";
    return os;
}
