/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBaseTransportObject.h"
#include "fSortedList.h"
#include "fBase.h"
#include <limits.h>

namespace com {
namespace pcbsys {
namespace foundation {
namespace configuration {

using namespace fbase;
using namespace com::pcbsys::foundation::collections;

class fConfigurationListener;

class fConfigObject :
    public fBaseTransportObject, public CountableObject {
  public:
    fConfigObject();
    fConfigObject(const std::string& group, const std::string& description, bool readonlyFlag = false, bool globalFlag = false);
    virtual ~fConfigObject(void);

  public:
    virtual std::string getValue(const std::string& key);
    virtual std::string getDescription(const std::string& key);
    virtual std::string getWarning(const std::string& key);
    virtual bool isReadOnly();

    virtual fSortedList<std::string, std::string>& getKeys();
    const std::string& getGroupName();
    const std::string& getGroupDescription();

    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);

    virtual int getType(const std::string& key);
    int getType() {
        return CountableObject::getType();
    };
    virtual longlong getMin(const std::string& key);
    virtual longlong getMax(const std::string& key);
    virtual bool isAdvanced(const std::string& key);

    virtual void addType(const std::string& key, int type);
    virtual void addMin(const std::string& key, longlong min);
    virtual void addMax(const std::string& key, longlong max);
    virtual void addIsAdvanced(const std::string& key, bool isAdvanced);

    virtual void changeKeyValuePair(const std::string& key, const std::string& value, bool doUpdate, const std::string& prefix = "");

    static const longlong fConfig_NO_MIN = LLONG_MIN;
    static const longlong fConfig_NO_MAX = LLONG_MAX;

    static const int fConfig_UNKNONW = -100;
    static const int fConfig_STRING = 0;
    static const int fConfig_INT = 1;
    static const int fConfig_LONG = 2;
    static const int fConfig_BOOLEAN = 3;

  protected:
    virtual void update(const std::string& prefix);

  private:
    void loadOrCreate ();

    std::string m_group;
    std::string m_description;
    bool m_bReadonly;
    bool m_bGlobal;
    fSortedList<std::string, std::string> m_hash;
    fSortedList<std::string, std::string> m_warningHash;
    fSortedList<std::string, std::string> m_descriptionHash;
    fSortedList<std::string, int> m_typeHash;
    fSortedList<std::string, longlong> m_maxHash;
    fSortedList<std::string, longlong> m_minHash;
    fSortedList<std::string, bool> m_isAdvancedHash;
    std::list<fConfigurationListener*> m_listeners;
};

}
}
}
}
