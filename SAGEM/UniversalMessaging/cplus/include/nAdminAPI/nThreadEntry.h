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

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

/**
 * This class is used to represent instances of tasks within a thread pool
 * running within a Nirvana realm
 *
 * Each entry consists of a label and an execution time in milliseconds
 *
 * @see nThreadPool
 * @since 4.0
 */
class nThreadEntry {
  public:
    nThreadEntry(const std::string& name, longlong time);
    virtual ~nThreadEntry(void);

  private:
    std::string m_name;
    longlong m_executionTime;
};

}
}
}
}
