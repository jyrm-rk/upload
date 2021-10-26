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
#include "nPublished.h"
#include "Poco/Mutex.h"

#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nTransactionAttributes;
class nSession;
class nConsumeEvent;

/**
 * This class enables the client to perform transactional publishing, representing a nirvana transaction
 */
class nTransaction {
  public:
      
    /**
	* Gets the cacheLocalBeforeCommit value- if true then events will be cached before commit.
	*
	* @return a bool
	*/
	DLL static bool getCacheLocalBeforeCommit();

	/**
	* Sets cacheLocalBeforeCommit value- if true then events will be cached before commit.
	* Default value is "false". Can be set in anytime in runtime
	*
	* @param bCacheLocal- the new value of cacheLocalBeforeCommit
	*/
	DLL static void setCacheLocalBeforeCommit(bool bCacheLocal);

    DLL nTransaction(nTransactionAttributes *pAttr);

    nTransaction(nTransactionAttributes *pAttr, longlong oldId);
    virtual ~nTransaction(void);

    /**
    * Commits the transaction id associated to this channel on the server.
    * <p></p>
    * We then wait for the server to respond.  The server responds with the
    * EIDs of the events that have been put on to this channel for the
    * supplied transaction id.  Once this process is complete we remove the
    * supplied transaction id from the list of transactions found within the
    * controlling nSession.
    *
    * @throws nSessionNotConnectedException The session is not currently connected to the server when this call was made
    * @throws nRequestTimedOutException     The server did not respond within the timeout period
    * @throws nChannelNotFoundException     The channel, typically, has been deleted
    * @throws nSecurityException            The client does not have permissions to perform this operation
    * @throws nUnexpectedResponseException  The server responded with with an unknown response, see the message for more information
    * @throws nTransactionNotStartedException
    *                                       The transaction has not been started
    * @throws nTransactionNoSuchTXIDException
    *                                       There is no known TXID, typically the transaction has timed out
    * @throws nTransactionAlreadyCommittedException
    *                                       The transaction has already been committed
    * @throws nTransactionAlreadyAbortedException
    *                                       The transaction has already been aborted
    * @throws nSessionPausedException The session is currently paused
	* @throws nPublishPausedException when publishing is paused server side
    */
    DLL void commit();

    /**
    * Adds the specified collection of nConsumeEvent objects to this transaction.
    * No events will be published until this transaction is committed.
    *
    * @param events the List collection of nConsumeEvent objects to be added to this transaction
    * @throws nSessionNotConnectedException The session is not currently connected to the server when this call was made
    * @throws nSecurityException            The client does not have permissions to perform this operation
    * @throws nTransactionAlreadyCommittedException
    *                                       The transaction has already been committed
    * @throws nTransactionAlreadyAbortedException
    *                                       The transaction has already been aborted
    * @throws nTransactionNoEventsException There are no nConsumeEvents in the list
    * @throws nSessionPausedException The session is currently paused
	* @throws nPublishPausedException when publishing is paused server side
    */
    DLL void publish(std::list<nConsumeEvent*>& events);

    /**
    * Adds the specified nConsumeEvent to this transaction. No events will be published
    * until this transaction is committed
    *
    * @param *pEvt the nConsumeEvent object to be added to this transaction
    * @throws nSessionNotConnectedException The session is not currently connected to the server when this call was made
    * @throws nSecurityException            The client does not have permissions to perform this operation
    * @throws nTransactionAlreadyCommittedException
    *                                       The transaction has already been committed
    * @throws nTransactionAlreadyAbortedException
    *                                       The transaction has already been aborted
    * @throws nSessionPausedException The session is currently paused
	* @throws nPublishPausedException when publishing is paused server side
    */
    DLL void publish(nConsumeEvent *pEvt);

    /**
    * Pushes the specified nConsumeEvent to this transaction. No events will be published
    * until this transaction is committed
    *
    * @param *pEvt the nConsumeEvent object to be added to this transaction
    * @throws nSessionNotConnectedException is thrown if the session is not connected
    * @throws nTransactionAlreadyCommittedException
    *                                       is thrown if the transaction is already committed
    * @throws nTransactionNoEventsException is thrown if the transaction has no events pushed
    * @throws nSecurityException            is thrown if the user has insufficient privileges
    * @throws nTransactionAlreadyAbortedException
    *                                       is thrown if the transaction has been aborted.
    * @throws nSessionPausedException The session is currently paused
	* @throws nPublishPausedException when publishing is paused server side
    */

    DLL void push(nConsumeEvent *pEvt);

    /**
    * Gets the end transaction id associated with this transaction
    *
    * @return a long specifying the  transaction ID
    */
    DLL longlong getTXID();

    /**
    * Aborts the transaction associated with the txid provided and this channel.
    *
    * @throws nSessionNotConnectedException The session is not currently connected to the server when this call was made
    * @throws nRequestTimedOutException     The server did not respond within the timeout period
    * @throws nChannelNotFoundException     The channel, typically, has been deleted
    * @throws nSecurityException            The client does not have permissions to perform this operation
    * @throws nUnexpectedResponseException  The server responded with with an unknown response, see the message for more information
    * @throws nTransactionNotStartedException
    *                                       The transaction has not been started
    * @throws nTransactionNoSuchTXIDException
    *                                       There is no known TXID, typically the transaction has timed out
    * @throws nTransactionAlreadyCommittedException
    *                                       The transaction has already been committed
    * @throws nTransactionAlreadyAbortedException
    *                                       The transaction has already been aborted
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void abort();

    /**
    *
    * Commits the transaction id associated to this channel on the server. This
    * method allows the transaction to be delayed until t+delay before it is committed
    *
    * <p></p>
    * We then wait for the server to respond.  The server responds with the
    * EIDs of the events that have been put on to this channel for the
    * supplied transaction id.  Once this process is complete we remove the
    * supplied transaction id from the list of transactions found within the
    * controlling nSession.
    *
    * @param delay - the number of milliseconds to delay the commit for at the server
    * @throws nSessionNotConnectedException The session is not currently connected to the server when this call was made
    * @throws nRequestTimedOutException     The server did not respond within the timeout period
    * @throws nChannelNotFoundException     The channel, typically, has been deleted
    * @throws nSecurityException            The client does not have permissions to perform this operation
    * @throws nUnexpectedResponseException  The server responded with with an unknown response, see the message for more information
    * @throws nTransactionNotStartedException
    *                                       The transaction has not been started
    * @throws nTransactionNoSuchTXIDException
    *                                       There is no known TXID, typically the transaction has timed out
    * @throws nTransactionAlreadyCommittedException
    *                                       The transaction has already been committed
    * @throws nTransactionAlreadyAbortedException
    *                                       The transaction has already been aborted
    * @throws nSessionPausedException The session is currently paused
	* @throws nPublishPausedException when publishing is paused server side
    */

    DLL void commit(longlong delay);

    /**
    * Commits the transaction id associated to this channel on the server. This method
    * allows the transaction to be committed at a future date, rather than immediately.
    * <p></p>
    * We then wait for the server to respond.  The server responds with the
    * EIDs of the events that have been put on to this channel for the
    * supplied transaction id.  Once this process is complete we remove the
    * supplied transaction id from the list of transactions found within the
    * controlling nSession.
    *
    * @param timeToPublish date at which the transaction will be committed
    * @param millisecsToPublish the number of milliseconds after timeToPublish to publish
    *
    * @throws nSessionNotConnectedException The session is not currently connected to the server when this call was made
    * @throws nRequestTimedOutException     The server did not respond within the timeout period
    * @throws nChannelNotFoundException     The channel, typically, has been deleted
    * @throws nSecurityException            The client does not have permissions to perform this operation
    * @throws nUnexpectedResponseException  The server responded with with an unknown response, see the message for more information
    * @throws nTransactionNotStartedException
    *                                       The transaction has not been started
    * @throws nTransactionNoSuchTXIDException
    *                                       There is no known TXID, typically the transaction has timed out
    * @throws nTransactionAlreadyCommittedException
    *                                       The transaction has already been committed
    * @throws nTransactionAlreadyAbortedException
    *                                       The transaction has already been aborted
    * @throws nSessionPausedException The session is currently paused
	* @throws nPublishPausedException when publishing is paused server side
    */

    DLL void commit(time_t timeToPublish, int millisecsToPublish);

    /**
    * Gets the transaction attributes object associated with this transaction
    *
    * @return a nTransactionAttributes object with the attributes for this transaction
    */

    DLL nTransactionAttributes* getAttributes();

    /**
    * Gets the start event id of the range to be published by this transaction
    *
    * @return a long specifying the start event id of the range to be published by this transaction
    * @throws nTransactionNotCommittedException
    *          is thrown if the transaction is not yet committed
    */

    DLL longlong getStartEID();

    /**
    * Gets the end event id of the range to be published by this transaction
    *
    * @return a long specifying the end event id of the range to be published by this transaction
    * @throws nTransactionNotCommittedException
    *          is thrown if the transaction is not yet committed
    */

    DLL longlong getEndEID();

    /**
    * Checks if this transaction is aborted
    *
    * @return a bool value specifying if this transaction has been aborted
    * @throws nSessionNotConnectedException The session is not currently connected to the server when this call was made
    * @throws nRequestTimedOutException     The server did not respond within the timeout period
    * @throws nSessionPausedException The session is currently paused
    * @throws nTransactionIncompleteException the transaction is invalid or incomplete
    */

    DLL bool isAborted();

    /**
    * Checks if this transaction is committed
    *
    * @return a bool value specifying if this transaction has been committed
    * @throws nSessionNotConnectedException The session is not currently connected to the server when this call was made
    * @throws nRequestTimedOutException     The server did not respond within the timeout period
    * @throws nSessionPausedException The session is currently paused
    * @throws nTransactionIncompleteException the transaction is invalid or incomplete
    * @throws nUnknownTransactionIdException the transaction id is not known on this server
    */

    DLL bool isCommitted();

    /**
    * Method that checks if this transaction is aborted
    *
    * @param forceRemoteCheck if false, the transaction will check its local state first before checking with the realm server, if true, it will check with the realm server only
    * @return a bool value specifying if the transaction has been aborted
    * @throws nSessionNotConnectedException The session is not currently connected to the server when this call was made
    * @throws nRequestTimedOutException     The server did not respond within the timeout period
    * @throws nSessionPausedException The session is currently paused
    * @throws nTransactionIncompleteException the transaction is invalid or incomplete
    */

    DLL bool isAborted(bool forceRemoteCheck);

    /**
    * Method that checks if this transaction is committed
    *
    * @param forceRemoteCheck if false, the transaction will check its local state first before checking with the realms server, if true, it will check with the realm server only
    * @return a bool value specifying if the transaction has been committed
    * @throws nSessionNotConnectedException The session is not currently connected to the server when this call was made
    * @throws nRequestTimedOutException     The server did not respond within the timeout period
    * @throws nSessionPausedException The session is currently paused
    * @throws nTransactionIncompleteException the transaction is invalid or incomplete
    * @throws nUnknownTransactionIdException the transaction id is not known on this server
    */

    DLL bool isCommitted(bool forceRemoteCheck);

  private:
    
    static bool cacheLocalBeforeCommit;

    std::string generateStringId();
      
    void publishCommit(longlong delay);
	void cleanupRequests(std::list<com::pcbsys::nirvana::nbase::events::nPublished *>& snd);

    nTransactionAttributes *m_pAttributes;
    nSession *m_pSession;
    longlong m_TXId;
    longlong m_channelId;
    bool m_bHasPublished;
    bool m_bHasCommitted;
    bool m_bHasAborted;
	std::list<com::pcbsys::nirvana::nbase::events::nPublished *> m_publishStorage;
    longlong m_startEID;
    longlong m_endEID;
    bool m_bIsFirstPublish;
	Poco::Mutex m_txMutex;
};

}
}
}
}
