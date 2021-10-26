/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nChannelAttributes;
}
namespace nAdminAPI {

class nNode;
class nACL;
class nCommandStatus;

using namespace com::pcbsys::nirvana::client;

/**
 * All classes that can be copied from one part of the namespace to another implement
 * this interface. This facilitates manipulation of the nirvana namespace nodes.
 */
class nCopyable {
  public:
    nCopyable(void);
    virtual ~nCopyable(void);

    /**
     * This method enables the copy of the object from one node to another, specifying a name
     * for the destination node, and whether the operation should wait until complete before returning
     *
     * @param *pToNode the container node to copy this node to
     * @param toName the new name of the node to copy this node as.
     * @param bWaitForCompletion a boolean specifying whether the method should return immediately or after the command
     * is completed.
     * @param *pAcl an optional initial acl object that will be set on the object being copied
     * @param *pCmdStatus an optional nCommandStatus object so that you can query the status of the command whether waiting
     * for completion or not (useful for progress bars etc.)
     *
     * @deprecated As of version 2.0, please use copy(boolean p_waitForCompletion, nChannelAttributes p_attrib, nCommandStatus cmdStatus)
     * @exception nUnsupportedCopyException if the copy operation can not be performed with the parameters specified.
     */
    virtual void copy(nNode *pToNode, std::string& toName, bool bWaitForCompletion, nACL *pAcl, nCommandStatus *pCmdStatus) = 0;

    /**
     * This method enables the copy of the object locally within the current node, specifying
     * a name so there are no duplicates, and whether the operation should wait until complete
     * before returning
     *
     * @param toName the new name of the node to copy this node as.
     * @param bWaitForCompletion a boolean specifying whether the method should return immediately or after the command
     * is completed.
     * @param *pAcl an optional initial acl object that will be set on the object being copied
     * @param *pCmdStatus an optional nCommandStatus object so that you can query the status of the command whether waiting
     * for completion or not (useful for progress bars etc.)
     *
     * @deprecated As of version 2.0, please use copy(boolean p_waitForCompletion, nChannelAttributes p_attrib, nCommandStatus cmdStatus)
     * @exception nUnsupportedCopyException if the copy operation can not be performed with the parameters specified.
     */
    virtual void copy(std::string& toName, bool bWaitForCompletion, nACL *pAcl, nCommandStatus *pCmdStatus) = 0;

    /**
     * This method enables the copy of the object from one node to another, specifying a name
     * for the destination node, and whether the operation should wait until complete before returning
     * as well as specifying new channel attributes
     *
     * @param *pToNode the name of the container node to copy this node to
     * @param bWaitForCompletion a boolean specifying whether the method should return immediately or after the command
     * is completed.
     * @param *pAttrib the nChannelAttributes specifying the new nNode parameters
     * (Name, Type, Capacity, TTL etc.) @see com.pcbsys.nirvana.client.nChannelAttributes
     * @param *pAcl an optional initial acl object that will be set on the object being copied
     * @param *pCmdStatus an optional nCommandStatus object so that you can query the status of the command whether waiting
     * for completion or not (useful for progress bars etc.)
     *
     * @exception nUnsupportedCopyException if the copy operation can not be performed with the parameters specified.
     */
    virtual void copy(nNode *pToNode, bool bWaitForCompletion, nChannelAttributes *pAttrib, nACL *pAcl, nCommandStatus *pCmdStatus) = 0;

    /**
     * This method enables the copy of the object locally within the current node, specifying
     * a name so there are no duplicates, and whether the operation should wait until complete
     * before returning, as well as specifying new channel attributes
     *
     * @param bWaitForCompletion a boolean specifying whether the method should return immediately or after the command
     * is completed.
     * @param *pAttrib the nChannelAttributes specifying the new nNode parameters
     * (Name, Type, Capacity, TTL etc.) @see com.pcbsys.nirvana.client.nChannelAttributes
     * @param *pAcl an optional initial acl object that will be set on the object being copied
     * @param *pCmdStatus an optional nCommandStatus object so that you can query the status of the command whether waiting
     * for completion or not (useful for progress bars etc.)
     *
     * @exception nUnsupportedCopyException if the copy operation can not be performed with the parameters specified.
     */
    virtual void copy(bool bWaitForCompletion, nChannelAttributes *pAttrib, nACL *pAcl, nCommandStatus *pCmdStatus) = 0;
};

}
}
}
}
