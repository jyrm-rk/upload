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
#include "fBaseTransportObject.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventOutputStream;
class fEventInputStream;
}

namespace security {

using namespace fbase;
using namespace io;

class fPrincipal :
    public fBaseTransportObject, public Countable {
  public:
    fPrincipal();
    fPrincipal(std::string& name);
    virtual ~fPrincipal(void);

    void writeExternal(fEventOutputStream *pOstream);
    std::string getName();
    virtual void readExternal(fEventInputStream *pIstream);
    std::string toString();

  private:
    std::string m_name;
    unsigned char *m_pNameBytes;
    unsigned int m_lengthName;
    int m_hashCode;
};

}
}
}
}

