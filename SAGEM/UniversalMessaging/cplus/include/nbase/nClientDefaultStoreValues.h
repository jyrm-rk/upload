/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
class nClientDefaultStoreValues
{
private:
	nClientDefaultStoreValues(){};
public:
	static const int CLIENT_EVENTS_PER_SPINDLE = 50000;
	static const bool CLIENT_CAPACITY_HONORING = true;
	static const bool CLIENT_AUTO_MAINTANANCE = true;
};

