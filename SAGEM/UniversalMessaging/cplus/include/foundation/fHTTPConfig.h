/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fDriverConfig.h"
#include "fCustomHeader.h"

#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {

class fPluginConfig;

class fHTTPConfig :
    public fDriverConfig {
  public:
    fHTTPConfig(void);
    fHTTPConfig(const std::string& name, const std::string& adapter, int port, bool autostart = true);
    fHTTPConfig(const std::string& name, const std::string& protocol, const std::string& adapter, int port, bool autoStart);
    virtual ~fHTTPConfig(void);

    virtual void readExternal(fEventInputStream *pEis);
    virtual void writeExternal(fEventOutputStream *pEos);
    virtual void readOrigExternal(fEventInputStream *pEis);
    virtual void readOldExternal(fEventInputStream *pEis);

    virtual int getType();
    std::list<fPluginConfig*>& getPlugin();
    virtual void setPlugin(std::list<fPluginConfig*>& className);

    std::list<fCustomHeader*> getCustomHeaders();
    void setCustomHeaders(std::list<fCustomHeader*> newCustomHeaders);
    longlong getAjaxLPActiveDelay();

    void setAjaxLPActiveDelay(longlong ajaxLPActiveDelay);
    longlong getAjaxLPIdleDelay();
    void setAjaxLPIdleDelay(longlong ajaxLPIdleDelay);
    std::string getInitialJavascript();
    void setInitialJavascript(std::string initialJavascript);

    std::string getAllowedOrigins();
    std::string* getAllowedOriginsAsArray(int& len);
    bool isAllowedAllOrigins();
    void setAllowedOrigins(std::string allowed);
    bool isAllowedCrossOriginCredentials();
    void setAllowedCrossOriginCredentials(bool allow);
    void setEnableGZIP(bool flag);
    bool getEnableGZIP();
    int getMinimumBytesBeforeGZIP();
    void setMinimumBytesBeforeGZIP(int len);

  private:
    std::list<fPluginConfig*> m_plugins;
    std::list<fCustomHeader*> myCustomHeaders;
    std::string InitialJavascript;
    longlong AjaxLPIdleDelay;
    longlong AjaxLPActiveDelay;
    std::string allowedOrigins;
    std::string* allowedOriginsArray;
    int allowedOriginsArray_len;
    bool allowedOriginsALL;
    bool allowCrossOriginCredentials;
    int minimumBytesBeforeGZIP;
};

}
}
}
}
}
