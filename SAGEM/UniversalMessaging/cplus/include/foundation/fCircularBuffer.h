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
#include "Poco/SynchronizedObject.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class Object;
}
namespace collections {

using namespace fbase;

class fCircularBuffer : public Poco::SynchronizedObject {
  public:
    fCircularBuffer(int size);
    fCircularBuffer(int size, bool overwrite);
    virtual ~fCircularBuffer(void);

    int size();
    void reset();
    CountableObject* get();
    int length();
    void resize(int newSize);
    void put(CountableObject *pObject);
    CountableObject* look();
    bool wouldOverwrite();

  private:
    CountableObject** m_pBuffer;
    int m_endIdx;
    int m_startIdx;
    int m_size;
    int m_length;
    bool m_bAllowOverwrite;
};

}
}
}
}
