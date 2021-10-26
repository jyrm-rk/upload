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

#include <map>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
}
namespace nirvana {
namespace nbase {

using namespace foundation::fbase;
using namespace foundation::io;

class nPluginDetails :
    public fExternalable, public CountableObject {
  public:
    nPluginDetails(void);
    virtual ~nPluginDetails(void);

    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);

    virtual const std::string& getName();
    virtual const std::string& getDescription();
    virtual std::map<std::string, std::string>& getConfig();

  private:
    std::string m_name;
    std::string m_description;
    std::map<std::string, std::string> m_config;
};

}
}
}
}
