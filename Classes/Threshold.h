//
// Created by bujor on 12/21/2025.
//

#ifndef THRESHOLD_H
#define THRESHOLD_H


template<typename T>
class Threshold {
    T value;
public:
    explicit Threshold(T value): value(value) {}

    bool isMet(T currentValue) {
        return currentValue >= value;
    }

    T getValue() const{ return value; }
};

template<typename T>
Threshold<T> MakeThreshold(const T& data) {
    return Threshold<T>(data);
}



#endif //THRESHOLD_H
