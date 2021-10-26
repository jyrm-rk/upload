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
namespace foundation {
namespace fbase {
class fEventDictionary;
}
}
namespace nirvana {
namespace client {

using namespace com::pcbsys::foundation::fbase;

/**
* Class that contains additional properties that can be set on the channel or queue
*/
class nStoreProperties {
  public:
    nStoreProperties(fEventDictionary *pDic);
    virtual ~nStoreProperties(void);

    
  /**
   * Returns the currently configured fanout archive target name, if supplied else null.
   *
   * @return Name of class which implements interface nMergeEngineExtension.
   * @deprecated This method is deprecated since 10.5. The Archive functionality is not complete and has various limitations.
   * It will be removed from the product in the next releases
   */
    UM_DEPRECATED DLL std::string getFanoutArchiveTarget();
        
    
  /**
   * This allows the client to specify the name of an existing channel or queue which will be used to
   * archive every single event that the server fans out to this channel's subscribers, stamped with fanout information.
   * The functionality only applies to channels, will have no effect if used on a queue.
   *
   * @param name of the existing channel or queue to use
   * @deprecated This method is deprecated since 10.5. The Archive functionality is not complete and has various limitations.
   * It will be removed from the product in the next releases
   */
    UM_DEPRECATED DLL void setFanoutArchiveTarget(const std::string& name);

    /**
    * Returns the currently configured merge class name, if supplied else null.
    *
    * @return Name of class which implements interface nMergeEngineExtension.
    *
    * @see com.pcbsys.nirvana.server.plugins.extensions.mergeEngine.nMergeEngineExtension
    */
    DLL std::string getClientMergeEngineClassname();
    
    
/**
   * This allows the client to specify the class used to merge events to form one event within the server.
   * The class must implement the interface nMergeEngineExtension and the channel must have the merge engine active
   * else this will not be used by the server
   *
   * @param name of the class to use
   */
    DLL void setClientMergeEngineClassname(const std::string& mergeEngineClass);

    /**
    * When a server restarts it will scan all file based stores and check for corruption. During this test the default behaviour
    * is to disable caching to conserve memory, however, in some instances it would be better if the server had actually cached the events
    * in memory for fast replay.
    *
    * @return The current state, if false (default behaviour) no events are kept in memory during reload
    */
    DLL bool getCacheOnReload();
    
 /**
   * Allows the client to control the caching algorithm within the server, if you set caching to false, all events will be
   * read from the file store else if ther server has room in memory, they will be stored in memory and reused.
   *
   * Only applicable for mixed and persistent stores
   *
   * @param flag true to enable caching (default behaviour)
   */    
    DLL void setCacheOnReload(bool flag);
    
    /**
    * Whether each write to the store will also call sync on the file system to ensure all data is written to the Disk
    * @return true or false
    */
    DLL bool canSyncOnEachWrite();
    
    /**
    * Sets whether each write to the store will also call sync on the file system to ensure all data is written to the Disk
    * @param flag true or false
    */    
    DLL void setSyncOnEachWrite(bool flag);
    
    /**
    * Whether each write to the store will also call sync on the file system to ensure all data is written to the Disk
    * @return true or false
    */
    DLL int getSyncMaxBatchSize();


    /**
     * Sets whether each write to the store will also call sync on the file system to ensure all data is written to the Disk
     * @param size value between 1 and 1000;
     */
    DLL void setSyncMaxBatchSize(int size);

    /**
    * Whether each write to the store will also call sync on the file system to ensure all data is written to the Disk
    * @return true or false
    */
    DLL int getSyncBatchTime();
    
    
    /**
     * Sets whether each write to the store will also call sync on the file system to ensure all data is written to the Disk
     * @param time true or false
     */
    DLL void setSyncBatchTime(int size);

    /**
    * Returns true if the server will cache events in memory or will always refer back to the file backed store. Used by mixed and persistent
    * store types to improve performance by caching the event in memory. In certain instances this is not desirable and the events should
    * not be cached, some examples would be very large stores where the application will periodically scan from the start to the finish.
    *
    * @return true if enabled, this is the default behaviour
    */
    DLL bool getEnableCaching();

  /**
   * Allows the client to control the caching algorithm within the server, if you set caching to false, all events will be
   * read from the file store else if ther server has room in memory, they will be stored in memory and reused.
   *
   * Only applicable for mixed and persistent stores
   *
   * @param flag true to enable caching (default behaviour)
   */
    DLL void setEnableCaching(bool flag);
    
    /**
    * Returns the current state of read buffering for the store, if true, then reads will be buffered to optimize the I/O access
    * to the file based store. If false then no buffering will be done and each read will result in a disk I/O, reducing overall performance
    * of the server.
    *
    * @return boolean indicating if read buffering is enabled or not. By default it is enabled
    * @deprecated This function is deprecated since 10.3. Read buffering is always enabled.
    */
    UM_DEPRECATED DLL bool getEnableReadBuffering();
    
    
    /**
    * Allows the client to control the read buffering logic for the store on the server. If true then the server will optimize its
    * reading of the file based store and reduce the number of disk I/O's performed. Only works on file backed stores like
    * mixed and persistent.
    *
    * @param flag to enable/disable the read buffering
    * @deprecated This function is deprecated since 10.3. Read buffering is always enabled.
    */
    UM_DEPRECATED DLL void setEnableReadBuffering(bool flag);
    
    /**
    * If ReadBuffering is enabled then this function returns the size in bytes of the buffer to use
    *
    * @return The number of bytes to use for buffering reads for the store
    * @deprecated This function is deprecated since 10.3. Stores will always use the global 'StoreReadBufferSize' realm configuration.
    */
    UM_DEPRECATED DLL ulonglong getReadBufferSize();

  /**
   * If read buffering is enabled then this allows the client set the number of bytes used for buffering. By default the
   * server uses 10K
   *
   * @param bufferSize number of bytes to use
   * @deprecated This function is deprecated since 10.3. Stores will always use the global 'StoreReadBufferSize' realm configuration.
   */    
    UM_DEPRECATED DLL void setReadBufferSize(ulonglong size);
    
    
    /**
    * Whether the channel / queue capacity setting will prevent publishing of any more data once full.
    * If true, the client will get an exception on further publishes
    * @return true or false
    */
    DLL bool getHonorCapacityWhenFull();

  /**
   * Sets whether the channel / queue capacity setting will prevent publishing of events once full.
   * If true, the client will get an exception on further publishes
   * @param flag true and no more events after max events will be published
   */    
    DLL void setHonorCapacityWhenFull(bool flag);

    
    /**
    * Whether the store will be have automatic maintenance as events are being removed
    * @return true or false
    */
    DLL bool getPerformAutomaticMaintenance();
    
   /**
    * Sets whether the store will be have automatic maintenance as events are being removed
    * @param flag true or false
    */
    DLL void setPerformAutomaticMaintenance(bool flag);
    

    /**
    * Returns the priority for the associated resource
    * @return an integer between 0 and 9, representing the inherited priority for events on this channel
    */
    DLL unsigned int getPriority();

    /* Sets the new priority for this resource. The new priority must be a value between 0 and 9.
    * @param newPriority an integer between 0 and 9
    */

  /**
   * Sets the default message priority for events on this channel.
   *
   * @param newPriority an integer priority between 1 and 10, where 10 is the highest priority.
   * @throws IllegalArgumentException if the value of newPriority is not between 1 and 10, this exception will be thrown.
   */
    DLL void setPriority(unsigned int newPriority);

	/**
	* Get the StampDictionary setting value of this store.
	*
	* @return <ul>
	* <li><code>com.pcbsys.nirvana.client.nChannelAttributes#DICTIONARY_STAMPING_ENABLED</code> if dictionary stamping is explicitly enabled for this channel</li>
	* <li><code>com.pcbsys.nirvana.client.nChannelAttributes#DICTIONARY_STAMPING_DISABLED</code> if dictionary stamping is explicitly disabled for this channel</li>
	* <li><code>com.pcbsys.nirvana.client.nChannelAttributes#DICTIONARY_STAMPING_DEFAULT</code> if dictionary stamping is not explicitly configured for this channel (the server will behave according to the default (server-wide) configuration setting)</li>
	* </ul>
	*
	*/
	DLL int getStampDictionary();

	/**
	* Configure explicitly the value of the StampDictionary setting of this store.
	* This configuration setting will override the default server behavior when processing events on this channel.
	* <br/>
	*
	* @param stampDictionary the new value of the configuration setting. Valid values are: <br/>
	* <ul>
	* <li><code>com.pcbsys.nirvana.client.nChannelAttributes#DICTIONARY_STAMPING_ENABLED</code> to explicitly enable dictionary stamping for this channel</li>
	* <li><code>com.pcbsys.nirvana.client.nChannelAttributes#DICTIONARY_STAMPING_DISABLED</code> to explicitly disable dictionary stamping for this channel</li>
	* <li><code>com.pcbsys.nirvana.client.nChannelAttributes#DICTIONARY_STAMPING_DEFAULT</code> to configure this channel to fall back to the default (server-wide) configuration setting</li>
	* </ul>
	*/
	DLL void setStampDictionary(int stampDictionary);

    /**
    * Returns the number of events that are stored per individual files for a single store
    * @return  The number of events per file spindle
    */
    DLL int getMultiFileEventsPerSpindle();

    /**
    * Sets the number of events that will be stored per individual file for a store. Setting this number too low will create to many files and utilise a large number of file descriptors
    * @param count  The number of events per individual file
    */
    DLL void setMultiFileEventsPerSpindle(unsigned int count);

    DLL bool isMulticastEnabled();
    
    DLL void setMulticastEnable(bool flag);
    
    
  protected:
    fEventDictionary *m_pParameters;
};

}
}
}
}
