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
#include "fBaseObject.h"
#include "fExternalable.h"
#include <stdio.h>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {

using namespace fbase;

class fConnectionDetails :
    public fBaseObject, public fExternalable, public Countable {
  public:
    fConnectionDetails(void);
    DLL fConnectionDetails(std::string URL);
    DLL fConnectionDetails(int type, const std::string& host, int port, const std::string& file);
    virtual ~fConnectionDetails(void);

    std::string getProtocolString();
    static std::string getProtocolString(int type);
    int getProtocolType();
    static int getProtocolType(std::string protocol);
    bool match(int type, std::string protocol);

    std::string parseSHMPath(std::string path);
    DLL int getType();
    DLL const std::string getHost();
    DLL int getPort();
    DLL std::string toString ();
    DLL const std::string getFile();
    DLL std::string* split(std::string, int& length, const std::string& delim);
    DLL bool useConnect();
    virtual void readExternal(fEventInputStream *pEis);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);
    bool getAllowForInterRealm();

    static const int s_nsp = 0;
    static const int s_nhp = 1;
    static const int s_nsps = 2;
    static const int s_nhps = 3;
    static const int s_nrsp = 4;
    static const int s_nrsps = 5;
    static const int s_loop = 6;
    static const int s_amqp = 7;
    static const int s_raw = 8;
    static const int s_comet = 9;
    static const int s_lp = 10;
    static const int s_mqtt = 11;
    static const int s_shm = 12;
    static const int s_rdma = 13;
    static const int s_mlt = 14;
    static const int s_stomp = 15;
    static const int s_xmpp = 16;
    static const int s_ProtocolEnd = 17;

    const std::string m_snsp;
    const std::string m_snhp;
    const std::string m_snsps;
    const std::string m_snhps;
    const std::string m_snrsp;
    const std::string m_snrsps;
    const std::string m_sloop;
    const std::string m_samqp;
    const std::string m_sraw;
    const std::string m_scomet;
    const std::string m_slp;
    const std::string m_smqtt;
    const std::string m_sshm;
    const std::string m_srdma;
    const std::string m_smlt;
    const std::string m_sstomp;
    const std::string m_sxmpp;

    static bool sEnableConnectionDebug;
    std::string getVirtualName();
    void setVirtualName(std::string virtualName);

  protected:
    static int m_sConnectionWeights[s_ProtocolEnd];

  private:
    void parseUrl(std::string aURL);

    int m_type;
    std::string m_host;
    int m_port;
    std::string m_file;
    std::string myVirtualName;
    bool m_bMultiplex;
    bool m_bConnect;
    bool m_bInterRealmComms;
    int m_weight;
};

}
}
}
}

