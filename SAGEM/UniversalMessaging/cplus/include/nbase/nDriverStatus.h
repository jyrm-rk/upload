/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fExternalable.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
namespace drivers {
namespace configuration {
class fDriverConfig;
}
}
}
namespace nirvana {
namespace nbase {

using namespace foundation::fbase;
using namespace foundation::io;
using namespace foundation::drivers::configuration;

class nDriverStatus :
    public fExternalable, public Countable {
  public:
    nDriverStatus(void);
    nDriverStatus(fDriverConfig *pCfg);
    virtual ~nDriverStatus(void);

    virtual int getStatus();
    virtual const std::string& getErrorMessage();
    virtual fDriverConfig* getConfig();
    virtual void readExternal(fEventInputStream *pEis);
    virtual void writeExternal(fEventOutputStream *pEos);

    static const int s_stopped = 0;
    static const int s_started = 1;
    static const int s_paused = 2;
    static const int s_error = 3;

  private:
    fDriverConfig *m_pConfig;
    std::string m_errMsg;
    int m_status;
};

}
}
}
}
