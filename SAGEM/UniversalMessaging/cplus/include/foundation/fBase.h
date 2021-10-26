/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#ifdef WIN32
#pragma warning(disable:4267) // Only while we sort out other warnings first
#endif

#include "Poco/Mutex.h"
#include "Poco/Event.h"
#include <vector>
#include <map>
#include <list>
#include <string>
#include <string.h>
#include <stdio.h>
#include <limits.h>


//#define TRACE(format, ...) _CrtDbgReport(_CRT_WARN, NULL, NULL, "This", format, __VA_ARGS__)
#define TRACE

#ifndef WIN32

#define DLL
typedef long long int longlong;
typedef unsigned long long int ulonglong;
#define mem_barrier() __asm__ __volatile__("" ::: "memory");

#else

#define DllImport __declspec (dllimport)
#define DllExport __declspec (dllexport)
typedef __int64 longlong;
typedef unsigned _int64 ulonglong;
#define mem_barrier() MemoryBarrier()

#ifdef Nirvana_EXPORTS
#define DLL DllExport
#else
#define DLL DllImport
#endif

#endif

#ifdef __GNUC__
#define UM_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define UM_DEPRECATED __declspec(deprecated)
#else
#pragma message("WARNING: UM_DEPRECATED has not been implemented for this compiler")
#define UM_DEPRECATED
#endif

void checkpointCountable();
void dumpCountable();

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {

class fBase {
  public:
    static DLL void decode (unsigned char *pBuffer, int size, std::string& str);
    static DLL unsigned char* encode (const std::string& str, unsigned int& size);
    static DLL int compareNoCase (const std::string& string1, const std::string& string2);
    static DLL std::string toLower (std::string& string);
	static DLL std::string trim(const std::string& string);
	static DLL std::vector<std::string> tokenize(const std::string& string, const char separator);
	static int findNextPowerOfTwo(const int value);

    /*
     * Load a sequence and ensure instructions after, happen after.
     */
    template <typename T>
    static inline T load_acquire(volatile T* sequencePtr) {
        T sequence = *sequencePtr;
        mem_barrier();
        return sequence;
    }

    /*
     * Store a sequence and ensure previous stores, happen before.
     */
    template <typename T>
    static inline void store_release(volatile T* sequencePtr, T sequence) {
        mem_barrier();
        *sequencePtr = sequence;
    }

    static const int EMPTYEVENT = 1000;
    static const int SERVERHANDSHAKE = 1001;
    static const int CONNECTIONSUBSCRIBE = 1002;
    static const int USERSUBSCRIBE = 1003;
    static const int CANCELREQUESTS = 1004;
    static const int SECURITY = 1005;
    static const int USERFIND = 1006;
    static const int REDIRECTION = 1007;
    static const int EXCEPTIONEVENT = 1008;
    static const int GETLASTEID = 1009;
    static const int FLOWCONTROL = 1010;
    static const int REMOVESUB = 1011;
    static const int SERVERDISCONNECT = 1012;
    static const int PURGE = 1013;
    static const int PUBLISHED = 1014;
    static const int PUBLISHEDJOIN = 1015;
    static const int TIMEOUTUPDATE = 1016;
    static const int CONNECTIONUPDATE = 1017;
    static const int EVENTSIGNATUREPAIR = 1018;
    static const int CONSUMEEVENT = 1019;
    static const int BASEMULTIPLEXER = 1020;
    static const int ACKEVENT = 1021;
    static const int QUEUETRANSACTIONSTATUS = 1022;
    static const int PUBLISHREQUEST = 1023;
    static const int MAKECHANNEL = 1024;
    static const int DELETECHANNEL = 1025;
    static const int GETLASTSTOREDEID = 1026;
    static const int TXPUBLISHREQUEST = 1027;
    static const int TXCOMMIT = 1028;
    static const int TXABORT = 1029;
    static const int PEEKQUEUE = 1030;
    static const int POPQUEUE = 1031;
    static const int GETDETAILS = 1032;
    static const int TXISCOMMITTED = 1033;
    static const int ADDJOIN = 1034;
    static const int DELJOIN = 1035;
    static const int GETJOIN = 1036;
    static const int ADDREALM = 1037;
    static const int DELREALM = 1038;
    static const int GETREALM = 1039;
    static const int SERVERREDIRECT = 1040;
    static const int HEARTBEAT = 1041;
    static const int CLIENTHEARTBEAT = 1042;
    static const int TXPUBLISHCOMMIT = 1042;
    static const int GETCHANNELLIST = 1043;
    static const int MANAGENAMEDSUB = 1044;
    static const int CHANNELITERATE = 1045;
    static const int EVENTCONSUMERWRAPPER = 1046;
    static const int SERVICEWORKER = 1047;
    static const int DISCONNECTTHREAD = 1048;
    static const int RECONNECTTHREAD = 1049;
    static const int SERVERSERVICE = 1050;
    static const int CHANNELSUBSCRIBER = 1051;
    static const int LEAFNODE = 1052;
    static const int SERVICENODE = 1053;
    static const int CONFIGURATION = 1054;
    static const int CONTAINER = 1055;
    static const int REALMNODE = 1056;
    static const int LOOPCONFIG = 1057;
    static const int DRIVERCONFIG = 1058;
    static const int GETADAPTERS = 1058;
    static const int PLUGINREQUEST = 1059;
    static const int INTERFACEMANAGER = 1060;
    static const int INTERFACEVIAENTRY = 1062;
    static const int CLUSTERREQUEST = 1063;
    static const int LINKNODE = 1064;
    static const int CLUSTERNODE = 1065;
    static const int PKGCONFIGLISTENER = 1066;
    static const int EVENTMAPPING = 1067;
    static const int MANAGEADAPTERS = 1068;
    static const int CONTROLADAPTERS = 1068;
    static const int REALMACLENTRY = 1069;
    static const int CHANGEATTRIBUTES = 1070;
    static const int CHANNELMAP = 1071;
    static const int SECURITYEVENT = 1072;
    static const int PKGLEAFCOPY = 1073;
    static const int CONFIGENTRY = 1074;
    static const int REALMMAP = 1075;
    static const int PKGLEAFNODEINDEX = 1076;
    static const int ACLENTRYREQUESTS = 1077;
    static const int AUDITEVENT = 1078;
    static const int CLUSTEREVENT = 1079;
    static const int LOGEVENT = 1080;
    static const int SCHEDULERREQUEST = 1081;
    static const int STATUSUPDATE = 1082;
    static const int ADMINCONTAINER = 1083;
    static const int CHANNELACLENTRY = 1084;
    static const int SERVERMAP = 1085;
    static const int CHANNELCONNECTIONDETAILS = 1086;
    static const int CONFIGGROUP = 1087;
    static const int CHANNELWATCHER = 1088;
    static const int ACLENTRY = 1089;
    static const int QUEUE = 1090;
    static const int SECURECHANNEL = 1091;
    static const int CHANNELMAINTENANCE = 1092;
    static const int DIAGEVENT = 1093;
    static const int DISCONNECTIONREQUESTEVENT = 1094;
    static const int BASEDATASTREAM = 1095;
    static const int BASEDATAGROUP = 1096;
    static const int DATAGROUPADMIN = 1097;
    static const int DATASTREAMPUBLISH = 1098;
    static const int FINDANDSUBSCRIBE = 1099;
    static const int STREAMSTATUSUPDATE = 1100;
    static const int STRING = 1101;
    static const int REGISTEREDEVENTLISTENER = 1102;
    static const int REGISTEREDEVENTUPDATELISTENER = 1103;
    static const int BATCHPUBLISH = 1104;
    static const int DATASTREAMNODE = 1105;
    static const int DATAGROUPSCONTAINER = 1106;
    static const int DATAGROUPNODE = 1107;
    static const int EVENTLISTENER = 1108;
    static const int MULTICASTCONFIG = 1109;
    static const int SHMDRIVER = 1111;
    static const int MULTICASTCONFIGURATION = 1112;
    static const int SSLCONFIG = 1113;
    static const int HTTPSCONFIG = 1114;
    static const int SOCKETCONFIG = 1115;
    static const int HTTPCONFIG = 1116;
    static const int SHAREDMEMORYCONFIG = 1117;
    static const int FDEREGISTERGROUPUPDATE = 1118;
    static const int SECURITYGROUP = 1119;
    static const int ACLGROUP = 1120;
    static const int SERVEREXTENSIONCALLBACK = 1121;
    static const int SERVEREXTENSION = 1122;
	static const int ZONEEVENT= 1123;
	static const int MANAGEREMOTEINTEREST= 1124;
	static const int CHANNELNOTFOUNDEXCEPTIONEVENT = 1125;
    static const int USERPAUSE = 1126;
};

class DLL MutexHelper {
public:
	MutexHelper(Poco::Mutex *pMutex) :m_pMutex(pMutex){
		m_pMutex->lock();
	}
	~MutexHelper(){
		m_pMutex->unlock();
	}

protected:
	Poco::Mutex *m_pMutex;
};


class DLL MutexRelockHelper {
public:
	MutexRelockHelper(Poco::Mutex *pMutex) :m_pMutex(pMutex){
		m_pMutex->unlock();
	}
	~MutexRelockHelper(){
		m_pMutex->lock();
	}

protected:
	Poco::Mutex *m_pMutex;
};

class Countable : public Poco::Mutex {
  public:
    DLL Countable();
    DLL virtual ~Countable();

    DLL virtual void addRef();
    DLL virtual bool delRef();
    int getRefCount();

  private:
    int m_refCount;
};

class Object {
  public:
    virtual int getType() = 0;
    DLL virtual bool isArray ();
    virtual ~Object() {}
};

class ObjectArray : public Object {
  public:
    int getSize ();
    Object* getAt (int index);
    virtual bool isArray ();

  protected:
    std::vector<Object*> m_objects;
};

class CountableObject : public Object, public Countable {
  public:
    DLL CountableObject();
    DLL virtual ~CountableObject();

    virtual DLL int getType();
};

class NotifyableCountableObject : public CountableObject {
  public:
    DLL NotifyableCountableObject():CountableObject() {}
    DLL virtual ~NotifyableCountableObject() {}

    void notify() const {
        _event.set();
    }

    void wait() const {
        _event.wait();
    }

    void wait(long milliseconds) const {
        _event.wait(milliseconds);
    }

    bool tryWait(long milliseconds) const {
        return _event.tryWait(milliseconds);
    }

	void waitUnlock() const {
		MutexRelockHelper helper((Poco::Mutex*)this);
		_event.wait();
	}

	void waitUnlock(long milliseconds) const {
		MutexRelockHelper helper((Poco::Mutex*)this);
		_event.wait(milliseconds);
	}

	bool tryWaitUnlock(long milliseconds) const {
		MutexRelockHelper helper((Poco::Mutex*)this);
		return _event.tryWait(milliseconds);
	}

  private:
    mutable Poco::Event _event;
};


class BitArray {
  public:
    DLL BitArray(int size);
    DLL BitArray(BitArray *pArray);
    virtual ~BitArray();

    DLL void Set (int bit, bool bSet);
    DLL bool Equals (BitArray *pArray);
    DLL int Length ();
    DLL bool Get (int bit);

    DLL bool isEmpty();

    DLL std::string toString();

  protected:
    int m_size;
    bool *m_pFlags;
};

class Stack {
  public:
    Stack();
    virtual ~Stack();

    void Push(void *pNew);
    void* Pop();
    int Count();

  protected:
    void** m_ppStack;
    int m_nStack;
};

class String : public Object {
  public:
    DLL String(const std::string& string);
    DLL virtual ~String();

    DLL const std::string& get();
    DLL virtual int getType ();

  protected:
    std::string m_string;
};



}
}
}
}
