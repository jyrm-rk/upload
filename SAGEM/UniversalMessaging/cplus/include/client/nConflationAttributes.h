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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

using namespace foundation::fbase;

/**
 * This class represents the conflation attributes that can be used when creating resources which allow conflation.
 */
class nConflationAttributes : public Countable {
  public:

    /**
     * Creates a conflation attributes object defaulting the  action to merging of events within the conflation interval
     *
     * @param interval time in milliseconds that events will be conflated
     */
    DLL nConflationAttributes(longlong interval);
    /**
     * Creates a conflation attribute specifying the action as either drop or merge within the time interval specified
     *
     * @param action Set the action to either drop or merge events
     * @param interval time in milliseconds that events will be conflated
     * @throws nIllegalArgumentException
     */
    DLL nConflationAttributes(int action, longlong interval);
    virtual ~nConflationAttributes(void);

    /**
     * Used in the constructor of nConflationAttributes to represent that action that should be taken during the conflation interval
     */
    static const int sDropEvents = 0;

    /**
     * Used in the constructor of nConflationAttributes to represent that action that should be taken during the conflation interval
     */
    static const int sMergeEvents = 1;
    /**
     * This can be either Drop or Merge
     *
     * @return the configured action
     */
    DLL virtual int getAction();
    /**
     * The time that the configured resource will conflate events
     *
     * @return time in milliseconds
     */
    DLL virtual longlong getInterval();

  protected:
    /**
     * Sets the action for this conflation attribute
     *
     * @param action to use to set
     * @throws nIllegalArgumentException
     */
    virtual void setAction(int action);
    virtual void setInterval(longlong interval);

  private:
    int m_action;
    longlong m_interval;

    friend class nDataGroup;
};

}
}
}
}
