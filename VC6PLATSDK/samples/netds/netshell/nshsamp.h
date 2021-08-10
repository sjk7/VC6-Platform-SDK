// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft Netsh Sample.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------
#define UNICODE
#include <windows.h>
#include <guiddef.h>
#include <netsh.h>
#include <stdlib.h>

			 
#define SAMPLE_HELPER_VERSION				1

//
// We need separate GUID's for each context we are registering,
// because each context has a different parent.  Contexts that
// have identical parents need not have differing GUID's
//
const GUID g_ObjectGuid 	=   {0xf7e0bc27, 0xba6e, 0x4145, {0xa1, 0x23, 0x01, 0x2f, 0x19, 0x22, 0xf3, 0xf1}};   
const GUID g_SubContext     =   {0xf7e0bc28, 0xba6e, 0x4145, {0xa1, 0x23, 0x01, 0x2f, 0x19, 0x22, 0xf3, 0xf1}};
const GUID g_SampleInterface=   {0xf7e0bc29, 0xba6e, 0x4145, {0xa1, 0x23, 0x01, 0x2f, 0x19, 0x22, 0xf3, 0xf1}};

//
// We also need to know the GUID's of the "interface" and the 
// root netsh context, so that we can register under them.
//
const GUID g_Interface      =   {0x0705eca1, 0x7aac, 0x11d2, {0x89, 0xdc, 0x00, 0x60, 0x08, 0xb0, 0xe5, 0xb9}};
const GUID g_RootGuid       =   NETSH_ROOT_GUID;


//
// We'll use these declarations to keep track of
// the data the our helpers use.
//
enum ePOTENTIAL
{
    LOW =       0,
    MEDIUM =    1,
    HIGH =      2
};

typedef struct _SAMPLE_HELPER_DATA_
{
    DWORD           WidgetCount;
    DWORD           SprocketCount;
    DWORD           GatewayUserData;
    DWORD           InterfaceID;
    BOOL            bEnabled;
    DWORD           Supermetric;
    ePOTENTIAL      Potential;
} SAMPLE_HELPER_DATA, *PSAMPLE_HELPER_DATA;

//
// Function prototypes.
//
DWORD WINAPI
InitHelperDll(
	IN      DWORD           dwNetshVersion,
	OUT     PVOID	        pReserved
    );
    
DWORD WINAPI
StartHelpers(
    IN      CONST GUID *    pguidParent,
    IN      DWORD           dwVersion
    );

BOOL WINAPI
CheckRunningOnWhistler(
    IN      UINT            CIMOSType,
    IN      UINT            CIMOSProductSuite,           
    IN      LPCWSTR         CIMOSVersion,                
    IN      LPCWSTR         CIMOSBuildNumber,            
    IN      LPCWSTR         CIMServicePackMajorVersion,  
    IN      LPCWSTR         CIMServicePackMinorVersion,  
    IN      UINT            CIMProcessorArchitecture,
    IN      DWORD           dwReserved
    );

DWORD WINAPI
HandleAddObjectCommand(
    IN      LPCWSTR         pwszMachine,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwCurrentIndex,
    IN      DWORD           dwArgCount,
    IN      DWORD           dwFlags,
    IN      LPCVOID         pvData,
    OUT     BOOL            *pbDone
    );
    
DWORD WINAPI
HandleShowObjectCommand(
    IN      LPCWSTR         pwszMachine,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwCurrentIndex,
    IN      DWORD           dwArgCount,
    IN      DWORD           dwFlags,
    IN      LPCVOID         pvData,
    OUT     BOOL            *pbDone
    );
    
DWORD WINAPI
HandleSetObjectCommand(
    IN      LPCWSTR         pwszMachine,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwCurrentIndex,
    IN      DWORD           dwArgCount,
    IN      DWORD           dwFlags,
    IN      LPCVOID         pvData,
    OUT     BOOL            *pbDone
    );
    
DWORD WINAPI
HandleResetWidgetCommand(
    IN      LPCWSTR         pwszMachine,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwCurrentIndex,
    IN      DWORD           dwArgCount,
    IN      DWORD           dwFlags,
    IN      LPCVOID         pvData,
    OUT     BOOL            *pbDone
    );
    
DWORD WINAPI
HandleResetSprocketCommand(
    IN      LPCWSTR         pwszMachine,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwCurrentIndex,
    IN      DWORD           dwArgCount,
    IN      DWORD           dwFlags,
    IN      LPCVOID         pvData,
    OUT     BOOL            *pbDone
    );
    
DWORD WINAPI
HandleResetAllCommand(
    IN      LPCWSTR         pwszMachine,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwCurrentIndex,
    IN      DWORD           dwArgCount,
    IN      DWORD           dwFlags,
    IN      LPCVOID         pvData,
    OUT     BOOL            *pbDone
    );

DWORD WINAPI
HandleShowErrorCommand(
    IN      LPCWSTR         pwszMachine,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwCurrentIndex,
    IN      DWORD           dwArgCount,
    IN      DWORD           dwFlags,
    IN      LPCVOID         pvData,
    OUT     BOOL            *pbDone
    );
    
DWORD WINAPI
HandleSetInterfaceCommand(
    IN      LPCWSTR         pwszMachine,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwCurrentIndex,
    IN      DWORD           dwArgCount,
    IN      DWORD           dwFlags,
    IN      LPCVOID         pvData,
    OUT     BOOL            *pbDone
    );
    
DWORD WINAPI
HandleSetGatewayCommand(
    IN      LPCWSTR         pwszMachine,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwCurrentIndex,
    IN      DWORD           dwArgCount,
    IN      DWORD           dwFlags,
    IN      LPCVOID         pvData,
    OUT     BOOL            *pbDone
    );
    
DWORD WINAPI
HandleShowRandomSettingsCommand(
    IN      LPCWSTR         pwszMachine,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwCurrentIndex,
    IN      DWORD           dwArgCount,
    IN      DWORD           dwFlags,
    IN      LPCVOID         pvData,
    OUT     BOOL            *pbDone
    );
    
DWORD WINAPI
DumpSampleInterface(
    IN      LPCWSTR         pwszRouter,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwArgCount,
    IN      LPCVOID         pvData
    );
    
DWORD WINAPI
DumpSample(
    IN      LPCWSTR         pwszRouter,
    IN OUT  LPWSTR          *ppwcArguments,
    IN      DWORD           dwArgCount,
    IN      LPCVOID         pvData
    );

//
// Common defs..
//

//
// These are context names.
//
#define TOKEN_SAMPLE                    L"sample"
#define TOKEN_SUBCONTEXT                L"subcontext"
#define TOKEN_SAMPLEINTERFACE           L"sampleinterface"

//
// These are all command names, group or otherwise.
//
#define TOKEN_ADD                       L"add"
#define TOKEN_WIDGETS                   L"widgets"
#define TOKEN_SPROCKETS                 L"sprockets"
#define TOKEN_ALL                       L"all"
#define TOKEN_SHOW                      L"show"
#define TOKEN_SET                       L"set"
#define TOKEN_RESET                     L"reset"
#define TOKEN_SHOWERROR                 L"showerror"
#define TOKEN_INTERFACE                 L"interface"
#define TOKEN_GATEWAY                   L"gateway"
#define TOKEN_USERDATA                  L"userdata"
#define TOKEN_ID                        L"id"
#define TOKEN_ENABLED                   L"enabled"
#define TOKEN_DISABLED                  L"disabled"
#define TOKEN_SUPERMETRIC               L"supermetric"
#define TOKEN_POTENTIAL                 L"potential"
#define TOKEN_HIGH                      L"high"
#define TOKEN_MEDIUM                    L"medium"
#define TOKEN_LOW                       L"low"
#define TOKEN_X86                       L"x86"
#define TOKEN_IA64                      L"ia64"
#define TOKEN_UNKNOWN                   L"unknown"

//
// We'll associate some of our commands with numbers.
// This isn't necessary, just done to show how some netsh
// functionality easily works with respect to enumeration-type
// structures.
//
#define WIDGETS                         0
#define SPROCKETS                       1
#define ALL                             2

#define ID                              0
#define ENABLED                         1
#define DISABLED                        2
#define SUPERMETRIC                     3
#define POTENTIAL                       4

//
// Set up some sort of system to keep track help
// id's.  This is just to make the code more 
// readable, as there are quite a few help id's.
//
#define HLP_SAMP_BASE                   10000

#define HLP_ADD_OBJECT_BASE             0
#define HLP_SHOW_OBJECT_BASE            100
#define HLP_SET_OBJECT_BASE             200
#define HLP_RESET_OBJECT_BASE           300
#define HLP_SHOWERROR_BASE              400
#define HLP_RANDOM_BASE                 500

//
// Command groups - we're creating two 'set' command groups 
// so we can have different help strings for each in different
// contexts.
//
#define CMD_RESET_OBJECT                TOKEN_RESET
#define HLP_RESET_OBJECT                HLP_SAMP_BASE + HLP_RESET_OBJECT_BASE

#define CMD_SET_RANDOM_STUFF            TOKEN_SET
#define HLP_SET_RANDOM_STUFF            HLP_SAMP_BASE + HLP_RANDOM_BASE


//
// Commands - top level commands listed first.
//

//////////
//
// Commands in the "sample" context.
//
#define CMD_ADD_OBJECT                  TOKEN_ADD
#define HLP_ADD_OBJECT                  HLP_SAMP_BASE + HLP_ADD_OBJECT_BASE + 10
#define HLP_ADD_OBJECT_EX               HLP_SAMP_BASE + HLP_ADD_OBJECT_BASE + 11

//////////

#define CMD_SHOW_OBJECT                 TOKEN_SHOW
#define HLP_SHOW_OBJECT                 HLP_SAMP_BASE + HLP_SHOW_OBJECT_BASE + 10
#define HLP_SHOW_OBJECT_EX              HLP_SAMP_BASE + HLP_SHOW_OBJECT_BASE + 11

//////////

#define CMD_SET_OBJECT                  TOKEN_SET
#define HLP_SET_OBJECT                  HLP_SAMP_BASE + HLP_SET_OBJECT_BASE + 10
#define HLP_SET_OBJECT_EX               HLP_SAMP_BASE + HLP_SET_OBJECT_BASE + 11

//
// These commands will be grouped together, which is why there is a 
// entry for each possible group name, ie "reset widgets" instead
// of one top level command that just handles "reset" and parses
// what comes after "reset" on its own.
//
#define CMD_RESET_OBJECT_WIDGETS        TOKEN_WIDGETS
#define HLP_RESET_OBJECT_WIDGETS        HLP_SAMP_BASE + HLP_RESET_OBJECT_BASE + 10
#define HLP_RESET_OBJECT_WIDGETS_EX     HLP_SAMP_BASE + HLP_RESET_OBJECT_BASE + 11

#define CMD_RESET_OBJECT_SPROCKETS      TOKEN_SPROCKETS
#define HLP_RESET_OBJECT_SPROCKETS      HLP_SAMP_BASE + HLP_RESET_OBJECT_BASE + 20
#define HLP_RESET_OBJECT_SPROCKETS_EX   HLP_SAMP_BASE + HLP_RESET_OBJECT_BASE + 21

#define CMD_RESET_OBJECT_ALL            TOKEN_ALL
#define HLP_RESET_OBJECT_ALL            HLP_SAMP_BASE + HLP_RESET_OBJECT_BASE + 30
#define HLP_RESET_OBJECT_ALL_EX         HLP_SAMP_BASE + HLP_RESET_OBJECT_BASE + 31

//////////
//
// Commands in the "subcontext" context (only one.)
//
#define CMD_SHOWERROR                   TOKEN_SHOWERROR
#define HLP_SHOWERROR                   HLP_SAMP_BASE + HLP_SHOWERROR_BASE + 10
#define HLP_SHOWERROR_EX                HLP_SAMP_BASE + HLP_SHOWERROR_BASE + 11

//////////
//
// Commands in the "subinterface" context.
//
#define CMD_SET_INTERFACE               TOKEN_INTERFACE
#define HLP_SET_INTERFACE               HLP_SAMP_BASE + HLP_RANDOM_BASE + 10
#define HLP_SET_INTERFACE_EX            HLP_SAMP_BASE + HLP_RANDOM_BASE + 11

#define CMD_SET_GATEWAY                 TOKEN_GATEWAY
#define HLP_SET_GATEWAY                 HLP_SAMP_BASE + HLP_RANDOM_BASE + 20
#define HLP_SET_GATEWAY_EX              HLP_SAMP_BASE + HLP_RANDOM_BASE + 21

#define CMD_SHOW_RANDOM                 TOKEN_SHOW
#define HLP_SHOW_RANDOM                 HLP_SAMP_BASE + HLP_RANDOM_BASE + 30
#define HLP_SHOW_RANDOM_EX              HLP_SAMP_BASE + HLP_RANDOM_BASE + 31

//
// Error messages.
//
#define ERR_SAMP_BASE                   20000
#define ERR_NO_VALID_COUNT              ERR_SAMP_BASE + 1
#define ERR_INVALID_NUM_ARGS            ERR_NO_VALID_COUNT + 1
#define ERR_INVALID_ERROR_CODE          ERR_INVALID_NUM_ARGS + 1

//
// General messages.
//
#define GEN_SAMP_BASE                   30000
#define GEN_CMD_OKAY                    GEN_SAMP_BASE + 1
#define GEN_CURRENT_COUNT               GEN_CMD_OKAY + 1
#define GEN_SAMPLEINTERFACE_SETTINGS    GEN_CURRENT_COUNT + 1
#define GEN_SAMPLEGATEWAY_SETTINGS      GEN_SAMPLEINTERFACE_SETTINGS + 1
#define GEN_CONNECT_SHOWSTRING          GEN_SAMPLEGATEWAY_SETTINGS + 1

//
// Dump related string ids.
//
#define DUMP_SAMP_BASE                  40000
#define DUMP_SAMP                       DUMP_SAMP_BASE + 1
#define DUMP_SAMPINTERFACE              DUMP_SAMP + 1

