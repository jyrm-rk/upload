/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nAPIAuditEvent;

/**
 * Classes that extend this class can register with the nRealmNode.addAuditListener() to receive
 * the realm's audit events. These events will contain information on who did what, to which objects and
 * when these operations were performed.
 */
class nAuditListener {
  public:
    nAuditListener(void);
    virtual ~nAuditListener(void);

   /**
    * This method is called by the nRealmNode to inform the user object of a new audit event. The event
    * contains the date/time, the object name, the object type, the subject that performed the operation
    * and values associated with the operation, such as acl bitmasks for before and after the operation
    *
    * @param pEvt the audit event generated on the realm
    */
    virtual void audit(nAPIAuditEvent *pEvt) = 0;
};

}
}
}
}
