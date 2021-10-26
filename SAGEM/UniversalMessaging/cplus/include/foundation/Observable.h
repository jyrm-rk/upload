/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBase.h"

#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class Observer;

class Observable : public NotifyableCountableObject {
  public:
    Observable(void);
    virtual ~Observable(void);

    DLL void addObserver(Observer *pObs);
    void deleteObserver(Observer *pObs);
    void notifyObservers(Object *pArg = NULL);
    void deleteObservers();
    bool hasChanged();
    int countObservers();

  protected:
    void setChanged();
    void clearChanged();

  private:
    bool m_bChanged;
    std::list<Observer*> m_obs;
};

}
}
}
}
