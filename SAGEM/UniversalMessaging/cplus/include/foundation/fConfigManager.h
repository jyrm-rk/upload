/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fSortedList.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace configuration {

class fConfigObject;

using namespace com::pcbsys::foundation::collections;

class fConfigManager {
  public:
    fConfigManager(void);
    virtual ~fConfigManager(void);

  protected:
    static void addGroup(const std::string& group, fConfigObject *pFco);

  private:
    static fSortedList<std::string, fConfigObject*> m_groups;

    friend class fConfigObject;
};

}
}
}
}
