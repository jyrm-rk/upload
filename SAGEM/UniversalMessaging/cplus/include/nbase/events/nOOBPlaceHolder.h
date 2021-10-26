/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NOOBPLACEHOLDER_H
#define NOOBPLACEHOLDER_H

#include "nEventFactory.h"
#include "nEvent.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventOutputStream;
class fEventInputStream;
}
}
namespace nirvana {
namespace nbase {
namespace events {
class nOOBPlaceHolder : public nEvent {
  public:
    nOOBPlaceHolder();

    void performWrite(fEventOutputStream* oos);

    void performRead(fEventInputStream* ois);

    nEvent* createInstance();

    int getType();
    const std::string getTypeString();
};
}
}
}
}
}

#endif
