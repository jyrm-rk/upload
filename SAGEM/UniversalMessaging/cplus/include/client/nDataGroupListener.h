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

class nDataGroup;
class nDataStream;

/**
 * Listener interface used to manage changes to membership of data groups
 *
 * @since 6.0
 */
class DLL nDataGroupListener {
  public:
    nDataGroupListener(void);
    virtual ~nDataGroupListener(void);

    /**
     * Called when a new stream has been added to the data group
     *
     * @param *pGroup the nDataGroup that the stream has been added to
     * @param *pStream the nDataStream that has been added
     * @param count the current count of members
     */
    virtual void addedStream(nDataGroup *pGroup, nDataStream *pStream, int count) = 0;

    /**
     * Called when a stream has been deleted from the data group
     *
     * @param *pGroup the nDataGroup that the stream has been deleted from
     * @param *pStream the nDataStream that has been deleted
     * @param count the current count of members
     * @param serverRemoved whether the stream was removed from the group by the server
     */
    virtual void deletedStream(nDataGroup *pGroup, nDataStream *pStream, int count, bool serverRemoved) = 0;

    /**
     * Called when a group has been created
     *
     * @param *pGroup the nDataGroup that has been added
     */
    virtual void createdGroup(nDataGroup *pGroup) = 0;

    /**
     * Called when a group has been deleted
     *
     * @param *pGroup the nDataGroup that has been deleted
     */
    virtual void deletedGroup(nDataGroup *pGroup) = 0;


    /**
     * Called when a group has been added to the 'to' data group
     *
     * @param *pTo the nDataGroup that the data group has been added to
     * @param *pGroup the nDataGroup that has been added
     * @param count the current count of member streams of the 'to' group
     */
    virtual void addedGroup(nDataGroup *pTo, nDataGroup *pGroup, int count) = 0;

    /**
     * Called when a group has been removed from the 'from' data group
     *
     * @param *pFrom the nDataGroup that the data group has been added to
     * @param *pGroup the nDataGroup that has been added
     * @param count the current count of member streams of the 'from' group
     */
    virtual void removedGroup(nDataGroup *pFrom, nDataGroup *pGroup, int count) = 0;
};

}
}
}
}
