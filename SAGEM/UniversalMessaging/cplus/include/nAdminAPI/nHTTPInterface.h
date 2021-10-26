/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nInterface.h"
#include "fCustomHeader.h"
#include "nCustomHeader.h"

#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fHTTPConfig;
}
}
}
namespace nirvana {
namespace nAdminAPI {

class nCustomHeader;
class nInterfaceManager;
class nPluginConfiguration;

using namespace com::pcbsys::foundation::drivers::configuration;

/**
 * Creates a HTTP interface on the supplied adapter:port
 *
 * @param adapter to bind to
 * @param port to bind to
 * @throws nAdminIllegalArgumentException if adapter is null or the port range is invalid
 */
class nHTTPInterface :
    public nInterface {
  public:
    /**
     * Creates a new HTTP interface
     *
     * @param *pCfg configuration to use
     * @param *pIM interface manager for this interface
     */
    nHTTPInterface(fHTTPConfig *pCfg, nInterfaceManager *pIm);
    virtual ~nHTTPInterface(void);
    nHTTPInterface(const std::string& adapter, int port, bool autostart = true);

    virtual std::list<nPluginConfiguration*>& getPlugin();
    virtual int getType ();

    /**
    * Returns true if HTTP 1.1 is enabled.
    * @return true if HTTP 1.1 is enabled
    */
    bool isHTTP_1_1_Enabled();

    /**
     * set the use of HTTP1.1
     *
     * @param flag if true, interface will use HTTP 1.1
     */
    void enabled_HTTP_1_1(bool flag);

    /**
     * Returns true if WebSockets are enabled
     * @return  true if WebSockets are enabled
     */
    bool isWebSocketEnabled();

    /**
     * Sets the use of WebSockets
     *
     * @param flag if true, interface will use websockets
     */
    void enabledWebSockets(bool flag);

    /**
     * Returns the time to wait (for additional events) before delivering to Long Poll style subscribers
     * @return  the time in milliseconds
     */
    longlong getAjaxLPActiveDelay();

    /**
     * Sets the time to wait (for additional events) before delivering to Long Poll style subscribers
     * @param ajaxLPActiveDelay the time to wait in milliseconds
     */
    void setAjaxLPActiveDelay(longlong ajaxLPActiveDelay);

    /**
     * Returns the time to wait before returning from a Long Poll call if no events have been received
     * @return  the time in milliseconds
     */
    longlong getAjaxLPIdleDelay();

    /**
     * Set the time to wait before returning from a Long Poll call if no events have been received
     * @param ajaxLPIdleDelay the time in milliseconds
     */
    void setAjaxLPIdleDelay(longlong ajaxLPIdleDelay);

    /**
     * Returns the javascript code that will be sent to comet / iframe users on initialisation. This can be used, for example to set document.domain
     * @return  the javascript code to send on initialisation
     */
    std::string getInitialJavascript();

    /**
     * Set the javascript code that will be sent to comet / iframe users on initialisation. This can be used, for example, to set document.domain
     * @param initialJavascript the javascript code to send to comet users on initialisation
     */
    void setInitialJavascript(std::string initialJavascript);

    /**
     *  Returns whether this interface has javascript enabled or not
     * @return  whether this interface has javascript enabled
     */
    bool isNativeCometAllowed();

    /**
     *  Sets whether javascript is enabled on the interface
     *  @param nativeCometAllowed true to enable javascript communication via this interface
     */
    void setNativeCometAllowed(bool nativeCometAllowed);

    /**
     *  Returns a List of nCustomHeader which will be sent to javascript clients
     * @return  a List of nCustomHeader
     */
    std::list<nCustomHeader*>* getCustomHeaders();

    /**
     *  Sets the custom headers that will be sent to javascript clients
     *  @param customHeaders List of nCustomHeader
     */
    void setCustomHeaders(std::list<nCustomHeader*>* customHeaders);

  protected:
    nHTTPInterface(const std::string& name, const std::string& protocol, const std::string& adapter, int port, bool autostart);
    void setPlugin(std::list<nPluginConfiguration*>& config);
    virtual fDriverConfig* convert();
    void convert(fHTTPConfig *pCfg);
    bool nativeCometAllowed;

  private:
    std::list<nPluginConfiguration*> m_plugin;
    bool _isHTTP_11_Enabled;
    bool _isWebSocketEnabled;

    longlong AjaxLPActiveDelay;
    longlong AjaxLPIdleDelay;
    std::string InitialJavascript;
    std::list<fCustomHeader*> myCustomHeaders;
};

}
}
}
}
