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

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

using namespace foundation::fbase;

/**
 * Represents the stream used to deliver data
 * @since 6.0
 */
class nDataStream : public Countable {
  public:
    DLL nDataStream(void);
    virtual ~nDataStream(void);
    /**
     * Get the name of the stream
     * @return the stream name
     */
    virtual const std::string& getName();
    /**
     * Get the subject associated with the stream
     * @return the subject
     */
    virtual const std::string& getSubject();

  protected:
    nDataStream(const std::string& name, const std::string& subject);

    std::string m_name;
    std::string m_subject;

    friend class nDataGroup;
    friend class nSession;
};

}
}
}
}
