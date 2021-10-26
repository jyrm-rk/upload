/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nDataStream.h"
#include "fBase.h"
#include "fSortedList.h"

#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nBaseDataGroup;
}
namespace client {

class nDataGroupListener;
class nSession;
class nRegisteredEvent;
class nConflationAttributes;

using namespace foundation::collections;
using namespace nbase;
/**
 * This class represents a individual data group object.
 *
 * @since 6.0
 */
class nDataGroup :
    public nDataStream {
  public:
    virtual ~nDataGroup(void);
    /**
     * Add a new stream to this data group
     *
     * @param *pStream - the stream to add
     * @throws nSecurityException
     * @throws nRequestTimedOutException
     * @throws nSessionPausedException
     * @throws nSessionNotConnectedException
     * @throws nDataGroupDeletedException
     * @throws nDataGroupIsReadOnlyException
     * @throws nUnexpectedResponseException
     */
    DLL virtual void add(nDataStream *pStream);

    /**
     * Add a new snoop stream to this data group
     *
     * @param *pStream - the stream to add
     * @throws nSecurityException
     * @throws nRequestTimedOutException
     * @throws nSessionPausedException
     * @throws nSessionNotConnectedException
     * @throws nDataGroupDeletedException
     * @throws nDataGroupIsReadOnlyException
     * @throws nUnexpectedResponseException
     */
    DLL virtual void addSnoop(nDataStream *pStream);
    /**
     * Flag indicating whether this group is nested within one of more other groups
     *
     * @return true if nested else false
     */
    DLL bool isNested();
    /**
     * Flag to indicate whether this group is read only. If it is, it will be the default Data Group object
     *
     * @return true is default Data Group
     */
    DLL bool isReadOnly();
    /**
     * Returns true if this group has been deleted
     *
     * @return true if deleted
     */
    DLL bool isClosed();
    /**
     * Add a list of new streams to this data group
     *
     * @param streams -  the list of streams to add
     * @throws nSecurityException
     * @throws nRequestTimedOutException
     * @throws nSessionPausedException
     * @throws nSessionNotConnectedException
     * @throws nDataGroupDeletedException
     * @throws nDataGroupIsReadOnlyException
     * @throws nUnexpectedResponseException
     */
    DLL void add(std::list<nDataStream*>& streams);
    /**
     * Adds an existing data group to this data group, allowing groups to be cascaded
     *
     * @param *pGroup - group to be added
     * @throws nSecurityException
     * @throws nRequestTimedOutException
     * @throws nSessionPausedException
     * @throws nSessionNotConnectedException
     * @throws nDataGroupDeletedException
     * @throws nDataGroupIsReadOnlyException
     * @throws nUnexpectedResponseException
     */
    DLL virtual void add(nDataGroup *pGroup);

    /**
     * Remove the stream Id from this data group
     *
     * @param *pStream - the stream to remove from this data group
     * @throws nSecurityException
     * @throws nRequestTimedOutException
     * @throws nSessionPausedException
     * @throws nSessionNotConnectedException
     * @throws nDataGroupDeletedException
     * @throws nDataGroupIsReadOnlyException
     * @throws nUnexpectedResponseException
     */
    DLL virtual void remove(nDataStream *pStream);

    /**
     * Remove the snoop stream Id from this data group
     *
     * @param *pStream - the stream to remove from this data group
     * @throws nSecurityException
     * @throws nRequestTimedOutException
     * @throws nSessionPausedException
     * @throws nSessionNotConnectedException
     * @throws nDataGroupDeletedException
     * @throws nDataGroupIsReadOnlyException
     * @throws nUnexpectedResponseException
     */
    DLL virtual void removeSnoop(nDataStream *pStream);
    /**
     * Remove the specified data group from this one
     *
     * @param *pGroup the group to remove
     * @throws nSecurityException
     * @throws nRequestTimedOutException
     * @throws nSessionPausedException
     * @throws nSessionNotConnectedException
     * @throws nDataGroupDeletedException
     * @throws nDataGroupIsReadOnlyException
     * @throws nUnexpectedResponseException
     */
    DLL virtual void remove(nDataGroup *pGroup);
    /**
    * Return the total number of streams contained in this group
    *
    * @return the number of streams in this group
    * @throws nDataGroupDeletedException
    */
    DLL virtual int size();
    /**
     * Allow the specified subject to be allowed to publish to this group
     *
     * @param subject the subject to give permissions to
     * @throws nDataGroupIsReadOnlyException
     * @throws nDataGroupDeletedException
     * @throws nIllegalArgumentException
     */
    DLL virtual void addPublisher(const std::string& subject);
    /**
     * Remove the specified subject from the list of authorised publishers for this group
     *
     * @param subject the subject to remove permissions from
     * @throws nDataGroupIsReadOnlyException
     * @throws nDataGroupDeletedException
     * @throws nIllegalArgumentException
     */
    DLL virtual void removePublisher(const std::string& subject);
    /**
     * Registers a new nRegisteredEvent with the data stream allowing updates only to be sent through to the clients
     *
     * @return nRegisteredEvent object
     * @throws nIllegalStateException
     * @see nRegisteredEvent
     */
    DLL nRegisteredEvent* createRegisteredEvent();
    /**
     * Add a new listener to this group so that when Streams or Groups are added or deleted the listener is notified
     *
     * @param *pListener the listener to receive callbacks on this data group
     * @throws nDataGroupDeletedException
     */
    DLL virtual void addListener(nDataGroupListener *pListener);
    DLL virtual nDataGroupListener* getListener();
    /**
     * Return the name of the group
     *
     * @return the name of this Data Group
     */
    DLL virtual const std::string& getName();
    /**
     * Returns the DataGroup specified, if it is contained within this group.
     *
     * @param groupName to find
     * @return nDataGroup the group matching the groupName
     * @throws nDataGroupDeletedException
     */
    DLL virtual nDataGroup* getGroup(const std::string& groupName);
    /**
     * Returns the size of the DataGroups (if any) contained within this group.
     *
     * @return int size the number of data groups contained within this group
     * @throws nDataGroupDeletedException
     */
    DLL int getGroupCount();
    /**
     * Returns the DataGroups (if any) contained within this group.
     *
     * @return nDataGroup list of the contained data groups
     * @throws nDataGroupDeletedException
     */
    DLL virtual std::list<nDataGroup*>* getGroups();
    virtual fSortedList<std::string, nDataGroup*>& _getGroups();
    /**
     * Get the nDataStream object corresponding to the name
     *
     * @param streamId the name of the stream
     * @return the stream object
     * @throws nDataGroupDeletedException
     */
    DLL virtual nDataStream* getStream(const std::string& streamId);
    /**
     * Get the nDataStream snoop object corresponding to the name
     *
     * @param streamId the name of the stream
     * @return the stream object
     * @throws nDataGroupDeletedException
     */
    DLL virtual nDataStream* getSnoopStream(const std::string& streamId);
    /**
     * Checks if the stream id exists in this group
     *
     * @param *pStream the stream to test for
     * @return true if this group contains the specified stream id
     * @throws nDataGroupDeletedException if this nDataGroup is now closed
     */
    DLL virtual bool contains(nDataStream *pStream);
    /**
     * Checks if the snoop stream id exists in this group
     *
     * @param streamId the name of the stream or group to test for
     * @return true if this group contains the specified stream id
     * @throws nDataGroupDeletedException
     */
    DLL virtual bool contains(const std::string& streamId);
    virtual bool _contains(const std::string&  streamId);

    /**
    * Checks if the stream id exists in this group
    *
    * @param *pStream the stream to test for
    * @return true if this group contains the specified stream id
    * @throws nDataGroupDeletedException if this nDataGroup is now closed
    */
    DLL virtual bool containsSnoop(nDataStream *pStream);
    /**
     * Checks if the snoop stream id exists in this group
     *
     * @param streamId the name of the stream or group to test for
     * @return true if this group contains the specified stream id
     * @throws nDataGroupDeletedException
     */
    DLL virtual bool containsSnoop(const std::string& streamId);
    virtual bool _containsSnoop(const std::string&  streamId);
    /**
     * Obtain a list of the nDataStream objects contained within this group
     *
     * @return a list of known streams
     * @throws nDataGroupDeletedException if this nDataGroup is now closed
     */
    DLL virtual std::list<nDataStream*>* getStreams();
    virtual fSortedList<std::string, nDataStream*>& _getStreams();
    /**
     * Obtain a list of publisher ids
     *
     * @return an fSortedList of currently allowed publishers
     * @throws nDataGroupDeletedException if this nDataGroup is now closed
     */
    DLL virtual fSortedList<std::string, std::string>& getPublishers();
    /**
     * Return the id of this nDataGroup object
     *
     * @return the unique long value representing this nDataGroup
     */
    DLL virtual longlong getID();
    /**
     * Locate the groups that currently contain this group
     *
     * @param nGroup - the number of groups returned
     * @return an array of nDataGroup objects containing the group
     */
    DLL nDataGroup** getGroupsContaining(int& nGroup);

    /**
     * Mark the nDataGroup as read only
     */
    virtual void setReadOnly();
    /**
     * Get the conflation attributes for this data group if they exist
     *
     * @return the conflation attributes if they exist
     */
    DLL nConflationAttributes* getConflationAttributes();

    /**
     * Checks if the stream id exists in this group
     *
     * @param stream the stream to test for
     * @return true if this group contains the specified stream id
     * @throws nDataGroupDeletedException if this nDataGroup is now closed
     */
    DLL bool contains(nDataGroup *pGroup);

	/**
	* Returns the session associated with this data group instance
	*
	* @return the session associated with this data group instance
	*/
	DLL nSession* getSession();

  protected:
    nDataGroup(const std::string& name, longlong id, nSession *pSession, nConflationAttributes *pAttr, int priorityLevel);
    nDataGroup(nBaseDataGroup *pGroups, nSession *pSession, nConflationAttributes *pAtt, int priorityLevel);
    nDataGroup(nBaseDataGroup *pBgrp, nSession *pSession, int priorityLevel);

    virtual void addStream(const std::string& group, nDataStream *pStream, bool isSnoop=false);
    void addStream(const std::string& group, std::list<nDataStream*>& streams, bool isSnoop=false);
    virtual void delStream(const std::string& group, const std::string& name, bool isSnoop);
    void addGroup(const std::string& group, nDataGroup *pGroup);
    void delGroup(const std::string& group, const std::string& name);
    virtual void addPublisher(const std::string& group, const std::string& name);
    virtual void delPublisher(const std::string& group, const std::string& name);
    virtual void close();
    virtual void removeFromList(nDataGroup *pGrp);
    virtual void removeFromList(nDataStream *pStream, bool serverInduced);
    virtual void removeFromSnoopList(nDataStream *pStream);
    void addToGroup(nDataGroup *pGroup);
    virtual void addToStream(nDataStream *pStream);
    virtual void addToSnoopStream(nDataStream *pStream);
    void addToStream(std::list<nDataStream*>& stream);
    virtual int getPriority();
	void initStreams(nBaseDataGroup *pBase, nSession* pSession, int priority);


    int _size();
    nDataGroupListener *m_pListener;

  private:
	  void initStreams(nBaseDataGroup *pBase, nSession* pSession, nConflationAttributes* pAtt, int priority);
  private:
    nSession *m_pSession;
    bool m_bClosed;

    longlong m_ID;

    fSortedList<std::string, nDataStream*> m_streams;
    fSortedList<std::string, nDataGroup*> m_groups;
    fSortedList<std::string, std::string> m_publishers;
    fSortedList<std::string, nDataStream*> mySnoopStreams;
    bool m_bReadOnly;
    bool m_bNested;
    nConflationAttributes *m_pConflation;

    int priority;

	Poco::Mutex	m_streamsMutex;

    friend class EventSink;
    friend class nSession;
};

}
}
}
}
