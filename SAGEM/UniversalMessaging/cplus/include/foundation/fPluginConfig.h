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

#include <map>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {

using namespace com::pcbsys::foundation::fbase;

class fPluginConfig :
    public fExternalable {
  public:
    fPluginConfig(void);
    fPluginConfig(const std::string& name, const std::string& mount, std::map<std::string, std::string>& config);
    virtual ~fPluginConfig(void);

    virtual const std::string& getName();
    virtual const std::string& getMount();
    virtual std::map<std::string, std::string>& getConfig();

    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);

  private:
    std::string m_name;
    std::string m_mount;
    std::map<std::string, std::string> m_configuration;
};

}
}
}
}
}
