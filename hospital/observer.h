#pragma once

#include <vector>
using namespace std;

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Observable {
    vector<Observer*> observers;
public:
    virtual void addObservers(Observer* observer) {
        observers.push_back(observer);
    };
    void notify() {
        for (auto &observer: observers) {
            observer->update();
        }
    }
    virtual ~Observable() = default;
};