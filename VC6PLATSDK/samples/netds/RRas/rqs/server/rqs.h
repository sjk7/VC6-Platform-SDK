//+--------------------------------------------------------------------------
//
//      File:       Rqs.h
//
//      Synopsis:   Main include for ras quarantine removal utility (server)
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#pragma once

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#include <rasutil.h>
#include <mprapi.h>
#include <rtutils.h>
#include <iprtrmib.h>
#include <iphlpapi.h>
#include <mprerror.h>

#include "rqsmsg.h"
#include "RqsClient.h"
#include "clntlst.h"
#include "RqsConfig.h"
#include "RqsEngine.h"

#define IP1(x) ((x>>24) & 0xff)
#define IP2(x) ((x>>16) & 0xff)
#define IP3(x) ((x>>8) & 0xff)
#define IP4(x) (x & 0xff)
