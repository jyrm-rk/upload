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

class nEventListener;
class nMessageValidator;

/**
 * This class is used to construct a Queue Reader.
 */
class nQueueReaderContext : public CountableObject {
  public:

    /**
    * Default constructor, useful for creating a standard synchronous queue reader.
    */
    DLL nQueueReaderContext(void);

    /**
    * This constructor supports an asynchronous queue reader, if applied to a synchronous queue reader the listener is ignored.
    * The message selector will be applied to all events prior to being delivered to the client from the server.
    *
    *
    * @param *pListener Asynchronous callback object
    * @param selector Message selector to be applied to the events prior to being delivered to the client
    * @param windowSize Number of events that the server will deliver prior to expecting a commit or rollback
    */
    DLL nQueueReaderContext(nEventListener *pListener, const std::string& selector, int windowSize = 0);

    /**
    * This constructor supports an asynchronous queue reader, if applied to a synchronous queue reader the listener is ignored.
    *
    * @param *pListener Asynchronous callback object
    * @param windowSize Number of events that the server will deliver prior to expecting a commit or rollback
    */

    DLL nQueueReaderContext(nEventListener *pListener, int windowSize = 0);

    /**
    * This constructor supports a standard synchronous queue reader with the message selector applied.
    *
    * @param selector Message selector to be applied to the events prior to being delivered to the client
    */

    DLL nQueueReaderContext(const std::string& selector);
    virtual ~nQueueReaderContext(void);


    /**
    * Sets the window size. This function has no effect on synchronous readers and if the asynchronous reader is constructed prior
    * to this method then it will not take effect until the reader is destroyed and recreated.
    *
    * @param window the window size to use
    */
    DLL void setWindow(int window);

    /**
    * Retrieves the current window size. This is the number of events the server will send prior to expecting an <code>rollback</code>
    * or a <code>commit</code>. No more events will be sent when this number is reached an no call is made.
    *
    * @return  current window size
    */
    DLL int getWindow();

    /**
    * Returns the current selector that this context was constructed with, could be null.
    * @return Message Selector
    */
    DLL std::string getSelector();

    /**
    * Returns the current event listener being used
    *
    * @return current listener
    */
    DLL nEventListener* getListener();

    /**
    * Retrieves the current message validator. This could be null.
    *
    * @return Message Validator
    */

    DLL nMessageValidator* getValidator();

    /**
    * Sets the current listener. This has no effect if the reader has been created prior to calling this method. The reader
    * will need to be destroyed and recreated.
    *
    * @param *pListener Event listener.
    */

    DLL void setListener(nEventListener *pListener);

    /**
    * Sets the message selector. If the reader has already been created this method does nothing.
    * If the reader is an asynchronous queue reader then the existing reader must
    * be destroyed and recreated before this selector will take effect else the next <code>pop</code> will take this
    * into account
    *
    * @param selector a Message selector
    */

    DLL void setSelector(const std::string& selector);

    /**
    * Sets the current message validator. It has no effect if the reader is an asynchronous queue reader and the reader will
    * need to be destroyed and recreated prior to this taking effect. If the reader is an synchronous queue reader the next
    * event popped will use the message validator.
    *
    * @param *pValidator The message validator to use.
    */

    DLL void setValidator(nMessageValidator *pValidator);
    
    /**
     * Retrieves the current peek batch size.
     *
     * @return peek batch size
     */
    DLL int getPeekBatchSize();
    
    /**
     * Sets the peek batch size, this is hte number of events a single call to the server will return
     *
     * @param peekBatchSize the peek batch size to use
     */
    
    DLL void setPeekBatchSize(int peekBatchSize);


  private:
    nEventListener* m_pListener;
    std::string m_selector;
    int m_window;
    nMessageValidator* m_pValidator;
    int m_peekBatchSize;
};

}
}
}
}
