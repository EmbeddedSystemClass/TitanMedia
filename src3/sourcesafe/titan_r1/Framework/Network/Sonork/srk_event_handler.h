#if !defined(SRK_EVENT_HANDLER_H)
#define SRK_EVENT_HANDLER_H
#include "srk_client_defs.h"

/*
	Sonork Messaging System

	Portions Copyright (C) 2001 Sonork SRL:

	This program is free software; you can redistribute it and/or modify
	it under the terms of the Sonork Source Code License (SSCL) Version 1.

	You should have received a copy of the SSCL	along with this program;
	if not, write to sscl@sonork.com.

	You should NOT use this source code before reading and accepting the
	Sonork Source Code License (SSCL), doing so will indicate your agreement
	to the the terms which may be differ for each version of the software.

	This comment section, indicating the existence and requirement of
	acceptance of the SSCL may not be removed from the source code.
*/




struct TSonorkSvrLoginReqPacket;

class TSonorkEventHandler
{
friend class TSonorkClient;
private:
	virtual void   	ProcessSonorkEvent(void*,TSonorkClientEvent*){}
protected:
	TSonorkEventHandler();
	virtual ~TSonorkEventHandler(){};
public:

};
#endif