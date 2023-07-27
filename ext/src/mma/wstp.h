/*************************************************************************

        Copyright 1986 through 2019 by Wolfram Research Inc.
        All rights reserved

*************************************************************************/

#ifndef _WSTP_H
#define _WSTP_H

#ifndef _WSVERS_H
#define _WSVERS_H

#ifndef _MLPLATFM_H
#define _MLPLATFM_H


#if !WINDOWS_MATHLINK && !WINDOWS_WSTP && !UNIX_MATHLINK && !UNIX_WSTP
#	define	UNIX_MATHLINK	1
#	define	UNIX_WSTP	1
#endif

#if defined(__GNUC__)
#if defined(__GNUC_PATCHLEVEL__)
#define GCC_MATHLINK_VERSION (__GNUC__ * 10000 \
						+ __GNUC_MINOR__ * 100 \
						+ __GNUC_PATCHLEVEL__)
#else
#define GCC_MATHLINK_VERSION (__GNUC__ * 10000 \
						+ __GNUC_MINOR__ * 100)
#endif
#endif

#if WINDOWS_MATHLINK
#define LITTLEENDIAN_NUMERIC_TYPES 1
#if defined(WIN64) || defined(_WIN64)
#define WIN64_MATHLINK 1
#if( _M_X64 || __x86_64 || __x86_64__ || x86_64)
#define X64_WINDOWS_MATHLINK 1
#else
/*\ syntax\ error\ */\ )
#endif
#elif defined(WIN32) || defined(_WIN32)
#define WIN32_MATHLINK 1
#if( _M_IX86 || __i386 || __i386__ || i386)
#define I86_WINDOWS_MATHLINK 1
#else
/*\ syntax\ error\ */\ )
#endif
#elif defined(__CYGWIN__)
#define CYGWIN_MATHLINK 1
#endif
#elif UNIX_MATHLINK
#if (__MACH || __MACH__ || MACH) && !defined(DARWIN_MATHLINK)
#define LITTLEENDIAN_NUMERIC_TYPES 1
#define DARWIN_MATHLINK 1
#if __i386 || __i386__ || i386
#define INTEL_DARWIN_MATHLINK 1
#define X86_DARWIN_MATHLINK 1
#elif __x86_64 || __x86_64__ || x86_64
#define INTEL_DARWIN_MATHLINK 1
#define X86_64_DARWIN_MATHLINK 1
#elif __arm__
#define ARM_DARWIN_MATHLINK 1
#elif __arm64__
#define ARM64_DARWIN_MATHLINK 1
#else
			#error not yet implemented
#endif

#if __DARWIN_UNIX03
#define DARWIN_MATHLINK_UNIX03 1
#endif /* __DARWIN_UNIX03 */

#if __clang__
#define CLANG_MATHLINK 1
#endif
#elif (__linux || __linux__ || linux) && !defined(LINUX_MATHLINK)
#define LITTLEENDIAN_NUMERIC_TYPES 1
#define LINUX_MATHLINK 1
#if __x86_64 || __x86_64__ || x86_64
#define X86_64_LINUX_MATHLINK 1
#elif __i386 || __i386__ || i386
#define I86_LINUX_MATHLINK 1
#elif __ANDROID || __ANDROID__ || ANDROID
#define ANDROID_LINUX_MATHLINK 1
#if __arm || __arm__ || arm
#define ANDROID_ARM_LINUX_MATHLINK 1
#endif
#elif __arm || __arm__ || arm
#define ARM_LINUX_MATHLINK 1
#else
			not yet implemented
#endif
#else
/*\ syntax\ error\ */\ )
#endif
#endif



#ifndef NO_GLOBAL_DATA
#define NO_GLOBAL_DATA 0
#endif

#if !defined(LITTLEENDIAN_NUMERIC_TYPES) && !defined(BIGENDIAN_NUMERIC_TYPES)
/*\ syntax\ error\ */\ )
#endif


#endif /* _MLPLATFM_H */


#if WSINTERFACE <= 3
#ifndef WSVERSION
#define WSVERSION 4
#endif
#endif

#if WSINTERFACE >= 4
#ifndef WSVERSION
                /* feature greeting version */
#define WSVERSION 6
#endif
#endif


/*
 * WSTP adopts a simple versioning strategy that can be adapted to many
 * compile-time and run-time environments.  In particular, it is amenable to
 * the various shared library facilities in use.  (Although certain of these
 * facilities provide more sophisticated mechanisms than are required by the
 * following simple strategy.)
 *
 * WSTP evolves by improving its implementation and by improving its
 * interface.  The values of WSREVISION or WSINTERFACE defined here are
 * incremented whenever an improvement is made and released.
 *
 * WSREVISION is the current revision number. It is incremented every time
 * a change is made to the source and WSTP is rebuilt and distributed
 * on any platform.  (Bug fixes, optimizations, or other improvements
 * transparent to the interface increment only this number.)
 *
 * WSINTERFACE is a name for a documented interface to WSTP.  This
 * number is incremented whenever a named constant or function is added,
 * removed, or its behavior is changed in a way that could break existing
 * correct* client programs.  It is expected that the interface to WSTP
 * is improved over time so that implemenations of higher numbered
 * interfaces are more complete or more convenient to use for writing
 * effective client programs.  In particular, a specific interface provides
 * all the useful functionality of an earlier interface.
 *
 *     *(It is possible that an incorrect WSTP program still works
 *     because it relies on some undocumented detail of a particular
 *     revision.  It may not always be possible to change the interface
 *     number when such a detail changes.  For example, one program may
 *     be relying on a bug in WSTP that a great many other programs
 *     need fixed.  In this case, we would likely choose to potentially
 *     break the incorrect program in order to fix the correct programs
 *     by incrementing the revision number leaving the interface number
 *     unchanged.  It is possible to bind to a particular revision of a
 *     WSTP interface if that is important for some programs.  One
 *     could use a statically linked version of the library, make use of
 *     the search algorithm used by the runtime loader, or dynamically
 *     load the WSTP library manually.)
 *
 *
 * If a distributed WSTP implmentation were labeled with its revision
 * and interface numbers in dotted notation so that, say, WS.1.6 means the
 * sixth revision of interface one, then the following may represent the
 * distribution history of WSTP.
 *
 *     first distribution
 *         WS.1.5   (Perhaps earlier revisions were never
 *                   distributed for this platform.)
 *
 *     second distribution
 *         WS.1.6   (Bug fixes or other improvements were
 *                   made that don't affect the interface.)
 *
 *     third distribution
 *         WS.2.7   (Perhaps some new functions were added.)
 *
 *         WS.1.7   (And improvements were made that don't
 *                   affect the old interface.)
 *
 *     fourth distribution
 *         WS.3.8   (Perhaps the return values of an existing
 *                   function changed.)
 *         WS.2.8   (Revision 8 also adds improvements transparent
 *                   to interface 2.)
 *         WS.1.7   (Clients of interface 1 see no improvements
 *                   in this eighth revision.)
 *
 * Note that the distribution history may not be the same on different
 * platforms.  But revision numbers represent a named body of source code
 * across all platforms.
 *
 * The mechanism for deploying this strategy differs between platforms
 * because of differing platform-specific facilities and conventions.
 * The interface and revision numbers may form part of the filename of
 * the WSTP library, or they may not.  This information is always
 * available in some conventional form so that it is easy and natural for
 * client programs to bind with and use the best available implementation
 * of a particular WSTP interface.  The details are described in the
 * WSTP Developer's Guide for each platform.
 */

#define WSREVISION 40
#define WSMATHVERSION 11.2.0

#ifndef WSCREATIONID
#define WSCREATIONID 114411
#endif

#define WSAPI4REVISION 25  /* the first revision to support interface 4 */


#ifndef WSINTERFACE
#define WSINTERFACE 4
#define WSAPIREVISION WSAPI4REVISION
#else
#if WSINTERFACE == 4
#define WSAPIREVISION WSAPI4REVISION
#else
/*\ syntax\ error\ */\ )
#endif
#endif


/* It may be possible for an implementation of one WSTP interface to
 * fully support an earlier interface.  WSNewParameters() may succeed when
 * passed an interface number less than the value of WSAPIREVISION when the
 * library was built.  This would happen, if the newer interface is a proper
 * superset of the older interface, or if the implementation can adjust its
 * behavior at runtime to conform to the older requested interface.
 */

#ifndef WSOLDDEFINITION
#if WSINTERFACE == 4
#define WSOLDDEFINITION WSAPI4REVISION /* WSPI4 is as old as it gets */
#else
/*\ syntax\ error\ */\ )
#endif
#endif


#endif /* _WSVERS_H */




/*****************************************************************************
 * START - ReBrand
 *  Note: ReBrand section is temporary. It is to map names between ML and WS.
 *  This section will be removed when all the public symbols are refactored.
 *****************************************************************************/
#ifndef _REBRAND_H_
#define _REBRAND_H_


#define MLActivate	WSActivate
#define MLAlert	WSAlert
#define MLAlertCast	WSAlertCast
#define MLAlign	WSAlign
#define MLAllocParameter	WSAllocParameter
#define MLAllocatorCast	WSAllocatorCast
#define MLBegin	WSBegin
#define MLBrowseForLinkServices	WSBrowseForLinkServices
#define MLBytesToGet	WSBytesToGet
#define MLBytesToPut	WSBytesToPut
#define MLCallMessageHandler	WSCallMessageHandler
#define MLCallYieldFunction	WSCallYieldFunction
#define MLCharacterOffset	WSCharacterOffset
#define MLCheckFunction	WSCheckFunction
#define MLCheckFunctionWithArgCount	WSCheckFunctionWithArgCount
#define MLClearAllSymbolReplacements	WSClearAllSymbolReplacements
#define MLClearError	WSClearError
#define MLClearSymbolReplacement	WSClearSymbolReplacement
#define MLClose	WSClose
#define MLCompilerID	WSCompilerID
#define MLConfirm	WSConfirm
#define MLConfirmCast	WSConfirmCast
#define MLConnect	WSConnect
#define MLContextFromLinkServer	WSContextFromLinkServer
#define MLConvertByteString	WSConvertByteString
#define MLConvertByteStringNL	WSConvertByteStringNL
#define MLConvertCharacter	WSConvertCharacter
#define MLConvertDoubleByteString	WSConvertDoubleByteString
#define MLConvertDoubleByteStringNL	WSConvertDoubleByteStringNL
#define MLConvertNewLine	WSConvertNewLine
#define MLConvertUCS2String	WSConvertUCS2String
#define MLConvertUCS2StringNL	WSConvertUCS2StringNL
#define MLConvertUTF16String	WSConvertUTF16String
#define MLConvertUTF16StringNL	WSConvertUTF16StringNL
#define MLConvertUTF32String	WSConvertUTF32String
#define MLConvertUTF32StringNL	WSConvertUTF32StringNL
#define MLConvertUTF8String	WSConvertUTF8String
#define MLConvertUTF8StringNL	WSConvertUTF8StringNL
#define MLCountYP	WSCountYP
#define MLCreateLinkWithExternalProtocol	WSCreateLinkWithExternalProtocol
#define MLCreateMark	WSCreateMark
#define MLCreateMessageHandler	WSCreateMessageHandler
#define MLCreateYieldFunction	WSCreateYieldFunction
#define MLDeallocatorCast	WSDeallocatorCast
#define MLDefaultYieldFunction	WSDefaultYieldFunction
#define MLDeinit	WSDeinit
#define MLDeinitialize	WSDeinitialize
#define MLDestroyMark	WSDestroyMark
#define MLDestroyMessageHandler	WSDestroyMessageHandler
#define MLDestroyYieldFunction	WSDestroyYieldFunction
#define MLDeviceInformation	WSDeviceInformation
#define MLDisableLinkLock	WSDisableLinkLock
#define MLDisableLoggingStream	WSDisableLoggingStream
#define MLDoNotHandleSignalParameter	WSDoNotHandleSignalParameter
#define MLDuplicateLink	WSDuplicateLink
#define MLEnableLinkLock	WSEnableLinkLock
#define MLEnableLoggingStream	WSEnableLoggingStream
#define MLEnclosingEnvironment	WSEnclosingEnvironment
#define MLEnd	WSEnd
#define MLEndPacket	WSEndPacket
#define MLEnvironmentData	WSEnvironmentData
#define MLError	WSError
#define MLErrorMessage	WSErrorMessage
#define MLErrorParameter	WSErrorParameter
#define MLErrorString	WSErrorString
#define MLEstablish	WSEstablish
#define MLEstablishString	WSEstablishString
#define MLExpressionsToGet	WSExpressionsToGet
#define MLFeatureString	WSFeatureString
#define MLFill	WSFill
#define MLFilterArgv	WSFilterArgv
#define MLFlush	WSFlush
#define MLForwardReset	WSForwardReset
#define MLFromLinkID	WSFromLinkID
#define MLGet7BitCharacters	WSGet7BitCharacters
#define MLGet8BitCharacters	WSGet8BitCharacters
#define MLGetAvailableLinkProtocolNames	WSGetAvailableLinkProtocolNames
#define MLGetArgCount	WSGetArgCount
#define MLGetArrayDimensions	WSGetArrayDimensions
#define MLGetArrayType	WSGetArrayType
#define MLGetArrayTypeWithDepthAndLeafType	WSGetArrayTypeWithDepthAndLeafType
#define MLGetBinaryNumber	WSGetBinaryNumber
#define MLGetBinaryNumberArray	WSGetBinaryNumberArray
#define MLGetBinaryNumberArrayData	WSGetBinaryNumberArrayData
#define MLGetBinaryNumberArrayDataWithHeads	WSGetBinaryNumberArrayDataWithHeads
#define MLGetBinaryNumberArrayWithLeafType	WSGetBinaryNumberArrayWithLeafType
#define MLGetBinaryNumberList	WSGetBinaryNumberList
#define MLGetByteArray	WSGetByteArray
#define MLGetByteArrayData	WSGetByteArrayData
#define MLGetByteString	WSGetByteString
#define MLGetByteSymbol	WSGetByteSymbol
#define MLGetData	WSGetData
#define MLGetDomainNameList	WSGetDomainNameList
#define MLGetDouble	WSGetDouble
#define MLGetDoubleArray	WSGetDoubleArray
#define MLGetDoubleArrayData	WSGetDoubleArrayData
#define MLGetFloat	WSGetFloat
#define MLGetFloatArray	WSGetFloatArray
#define MLGetFloatArrayData	WSGetFloatArrayData
#define MLGetFunction	WSGetFunction
#define MLGetInteger	WSGetInteger
#define MLGetInteger16	WSGetInteger16
#define MLGetInteger16Array	WSGetInteger16Array
#define MLGetInteger16ArrayData	WSGetInteger16ArrayData
#define MLGetInteger16List	WSGetInteger16List
#define MLGetInteger32	WSGetInteger32
#define MLGetInteger32Array	WSGetInteger32Array
#define MLGetInteger32ArrayData	WSGetInteger32ArrayData
#define MLGetInteger32List	WSGetInteger32List
#define MLGetInteger64	WSGetInteger64
#define MLGetInteger64Array	WSGetInteger64Array
#define MLGetInteger64ArrayData	WSGetInteger64ArrayData
#define MLGetInteger64List	WSGetInteger64List
#define MLGetInteger8	WSGetInteger8
#define MLGetInteger8Array	WSGetInteger8Array
#define MLGetInteger8ArrayData	WSGetInteger8ArrayData
#define MLGetInteger8List	WSGetInteger8List
#define MLGetIntegerArray	WSGetIntegerArray
#define MLGetIntegerArrayData	WSGetIntegerArrayData
#define MLGetIntegerList	WSGetIntegerList
#define MLGetLinkedEnvIDString	WSGetLinkedEnvIDString
#define MLGetLinksFromEnvironment	WSGetLinksFromEnvironment
#define MLGetLongDouble	WSGetLongDouble
#define MLGetLongDoubleArray	WSGetLongDoubleArray
#define MLGetLongDoubleArrayData	WSGetLongDoubleArrayData
#define MLGetLongInteger	WSGetLongInteger
#define MLGetLongIntegerArray	WSGetLongIntegerArray
#define MLGetLongIntegerArrayData	WSGetLongIntegerArrayData
#define MLGetMessage	WSGetMessage
#define MLGetMessageHandler	WSGetMessageHandler
#define MLGetNetworkAddressList	WSGetNetworkAddressList
#define MLGetNext	WSGetNext
#define MLGetNextRaw	WSGetNextRaw
#define MLGetNumberAsByteString	WSGetNumberAsByteString
#define MLGetNumberAsString	WSGetNumberAsString
#define MLGetNumberAsUCS2String	WSGetNumberAsUCS2String
#define MLGetNumberAsUTF16String	WSGetNumberAsUTF16String
#define MLGetNumberAsUTF32String	WSGetNumberAsUTF32String
#define MLGetNumberAsUTF8String	WSGetNumberAsUTF8String
#define MLGetRawArgCount	WSGetRawArgCount
#define MLGetRawData	WSGetRawData
#define MLGetRawType	WSGetRawType
#define MLGetReal	WSGetReal
#define MLGetReal128	WSGetReal128
#define MLGetReal128Array	WSGetReal128Array
#define MLGetReal128ArrayData	WSGetReal128ArrayData
#define MLGetReal128List	WSGetReal128List
#define MLGetReal32	WSGetReal32
#define MLGetReal32Array	WSGetReal32Array
#define MLGetReal32ArrayData	WSGetReal32ArrayData
#define MLGetReal32List	WSGetReal32List
#define MLGetReal64	WSGetReal64
#define MLGetReal64Array	WSGetReal64Array
#define MLGetReal64ArrayData	WSGetReal64ArrayData
#define MLGetReal64List	WSGetReal64List
#define MLGetRealArray	WSGetRealArray
#define MLGetRealList	WSGetRealList
#define MLGetShortInteger	WSGetShortInteger
#define MLGetShortIntegerArray	WSGetShortIntegerArray
#define MLGetShortIntegerArrayData	WSGetShortIntegerArrayData
#define MLGetString	WSGetString
#define MLGetSymbol	WSGetSymbol
#define MLGetType	WSGetType
#define MLGetUCS2Characters	WSGetUCS2Characters
#define MLGetUCS2Function	WSGetUCS2Function
#define MLGetUCS2String	WSGetUCS2String
#define MLGetUCS2Symbol	WSGetUCS2Symbol
#define MLGetUTF16Characters	WSGetUTF16Characters
#define MLGetUTF16Function	WSGetUTF16Function
#define MLGetUTF16String	WSGetUTF16String
#define MLGetUTF16Symbol	WSGetUTF16Symbol
#define MLGetUTF32Characters	WSGetUTF32Characters
#define MLGetUTF32Function	WSGetUTF32Function
#define MLGetUTF32String	WSGetUTF32String
#define MLGetUTF32Symbol	WSGetUTF32Symbol
#define MLGetUTF8Characters	WSGetUTF8Characters
#define MLGetUTF8Function	WSGetUTF8Function
#define MLGetUTF8String	WSGetUTF8String
#define MLGetUTF8Symbol	WSGetUTF8Symbol
#define MLGetYieldFunction	WSGetYieldFunction
#define MLHandlerCast	WSHandlerCast
#define MLHandleSignal	WSHandleSignal
#define MLInit	WSInit
#define MLInitialize	WSInitialize
#define MLInterfaceFromLinkServer	WSInterfaceFromLinkServer
#define MLIsLinkLoopback	WSIsLinkLoopback
#define MLinkEnvironment	WLinkEnvironment
#define MLLinkEnvironment	WSLinkEnvironment
#define MLLinkName	WSLinkName
#define MLLogFileNameForLink	WSLogFileNameForLink
#define MLLogStreamToFile	WSLogStreamToFile
#define MLLoopbackOpen	WSLoopbackOpen
#define MLLowLevelDeviceName	WSLowLevelDeviceName
#define MLMessageHandler	WSMessageHandler
#define MLMessageReady	WSMessageReady
#define MLName	WSName
#define MLNewLinkServer	WSNewLinkServer
#define MLNewLinkServerWithPort	WSNewLinkServerWithPort
#define MLNewLinkServerWithPortAndInterface	WSNewLinkServerWithPortAndInterface
#define MLNewPacket	WSNewPacket
#define MLNewParameters	WSNewParameters
#define MLNewUnicodeContainer	WSNewUnicodeContainer
#define MLNextCharacter	WSNextCharacter
#define MLNextCharacterFromStringWithLength	WSNextCharacterFromStringWithLength
#define MLNextPacket	WSNextPacket
#define MLNumber	WSNumber
#define MLNumericsQuery	WSNumericsQuery
#define MLOldConvertByteString	WSOldConvertByteString
#define MLOldConvertUCS2String	WSOldConvertUCS2String
#define MLOldPutCharToString	WSOldPutCharToString
#define MLOldStringCharFun	WSOldStringCharFun
#define MLOldStringFirstPosFun	WSOldStringFirstPosFun
#define MLOldStringNextPosFun	WSOldStringNextPosFun
#define MLOpen	WSOpen
#define MLOpenArgcArgv	WSOpenArgcArgv
#define MLOpenArgv	WSOpenArgv
#define MLOpenInEnv	WSOpenInEnv
#define MLOpenString	WSOpenString
#define MLPortFromLinkServer	WSPortFromLinkServer
#define MLPrintArgv	WSPrintArgv
#define MLPut7BitCharacters	WSPut7BitCharacters
#define MLPut7BitCount	WSPut7BitCount
#define MLPut8BitCharacters	WSPut8BitCharacters
#define MLPutArgCount	WSPutArgCount
#define MLPutArray	WSPutArray
#define MLPutArrayLeaves	WSPutArrayLeaves
#define MLPutArrayType	WSPutArrayType
#define MLPutBinaryNumber	WSPutBinaryNumber
#define MLPutBinaryNumberArray	WSPutBinaryNumberArray
#define MLPutBinaryNumberArrayData	WSPutBinaryNumberArrayData
#define MLPutBinaryNumberArrayDataWithHeads	WSPutBinaryNumberArrayDataWithHeads
#define MLPutBinaryNumberList	WSPutBinaryNumberList
#define MLPutByteArray	WSPutByteArray
#define MLPutByteArrayData	WSPutByteArrayData
#define MLPutByteString	WSPutByteString
#define MLPutByteSymbol	WSPutByteSymbol
#define MLPutComposite	WSPutComposite
#define MLPutData	WSPutData
#define MLPutDouble	WSPutDouble
#define MLPutDoubleArray	WSPutDoubleArray
#define MLPutDoubleArrayData	WSPutDoubleArrayData
#define MLPutFloat	WSPutFloat
#define MLPutFloatArray	WSPutFloatArray
#define MLPutFloatArrayData	WSPutFloatArrayData
#define MLPutFunction	WSPutFunction
#define MLPutInteger	WSPutInteger
#define MLPutInteger16	WSPutInteger16
#define MLPutInteger16Array	WSPutInteger16Array
#define MLPutInteger16ArrayData	WSPutInteger16ArrayData
#define MLPutInteger16List	WSPutInteger16List
#define MLPutInteger32	WSPutInteger32
#define MLPutInteger32Array	WSPutInteger32Array
#define MLPutInteger32ArrayData	WSPutInteger32ArrayData
#define MLPutInteger32List	WSPutInteger32List
#define MLPutInteger64	WSPutInteger64
#define MLPutInteger64Array	WSPutInteger64Array
#define MLPutInteger64ArrayData	WSPutInteger64ArrayData
#define MLPutInteger64List	WSPutInteger64List
#define MLPutInteger8	WSPutInteger8
#define MLPutInteger8Array	WSPutInteger8Array
#define MLPutInteger8ArrayData	WSPutInteger8ArrayData
#define MLPutInteger8List	WSPutInteger8List
#define MLPutIntegerArray	WSPutIntegerArray
#define MLPutIntegerArrayData	WSPutIntegerArrayData
#define MLPutIntegerList	WSPutIntegerList
#define MLPutLongDouble	WSPutLongDouble
#define MLPutLongDoubleArray	WSPutLongDoubleArray
#define MLPutLongDoubleArrayData	WSPutLongDoubleArrayData
#define MLPutLongInteger	WSPutLongInteger
#define MLPutLongIntegerArray	WSPutLongIntegerArray
#define MLPutLongIntegerArrayData	WSPutLongIntegerArrayData
#define MLPutMessage	WSPutMessage
#define MLPutMessageWithArg	WSPutMessageWithArg
#define MLPutNext	WSPutNext
#define MLPutRawData	WSPutRawData
#define MLPutRawSize	WSPutRawSize
#define MLPutReal	WSPutReal
#define MLPutReal128	WSPutReal128
#define MLPutReal128Array	WSPutReal128Array
#define MLPutReal128ArrayData	WSPutReal128ArrayData
#define MLPutReal128List	WSPutReal128List
#define MLPutReal32	WSPutReal32
#define MLPutReal32Array	WSPutReal32Array
#define MLPutReal32ArrayData	WSPutReal32ArrayData
#define MLPutReal32List	WSPutReal32List
#define MLPutReal64	WSPutReal64
#define MLPutReal64Array	WSPutReal64Array
#define MLPutReal64ArrayData	WSPutReal64ArrayData
#define MLPutReal64List	WSPutReal64List
#define MLPutRealArray	WSPutRealArray
#define MLPutRealList	WSPutRealList
#define MLPutRealNumberAsByteString	WSPutRealNumberAsByteString
#define MLPutRealNumberAsString	WSPutRealNumberAsString
#define MLPutRealNumberAsUCS2String	WSPutRealNumberAsUCS2String
#define MLPutRealNumberAsUTF16String	WSPutRealNumberAsUTF16String
#define MLPutRealNumberAsUTF32String	WSPutRealNumberAsUTF32String
#define MLPutRealNumberAsUTF8String	WSPutRealNumberAsUTF8String
#define MLPutShortInteger	WSPutShortInteger
#define MLPutShortIntegerArray	WSPutShortIntegerArray
#define MLPutShortIntegerArrayData	WSPutShortIntegerArrayData
#define MLPutSize	WSPutSize
#define MLPutString	WSPutString
#define MLPutSymbol	WSPutSymbol
#define MLPutType	WSPutType
#define MLPutUCS2Characters	WSPutUCS2Characters
#define MLPutUCS2Function	WSPutUCS2Function
#define MLPutUCS2String	WSPutUCS2String
#define MLPutUCS2Symbol	WSPutUCS2Symbol
#define MLPutUTF16Characters	WSPutUTF16Characters
#define MLPutUTF16Function	WSPutUTF16Function
#define MLPutUTF16String	WSPutUTF16String
#define MLPutUTF16Symbol	WSPutUTF16Symbol
#define MLPutUTF32Characters	WSPutUTF32Characters
#define MLPutUTF32Function	WSPutUTF32Function
#define MLPutUTF32String	WSPutUTF32String
#define MLPutUTF32Symbol	WSPutUTF32Symbol
#define MLPutUTF8Characters	WSPutUTF8Characters
#define MLPutUTF8Function	WSPutUTF8Function
#define MLPutUTF8String	WSPutUTF8String
#define MLPutUTF8Symbol	WSPutUTF8Symbol
#define MLRawBytesToGet	WSRawBytesToGet
#define MLReady	WSReady
#define MLReadyParallel	WSReadyParallel
#define MLRegisterCallbackFunctionWithLinkServer	WSRegisterCallbackFunctionWithLinkServer
#define MLRegisterLinkService	WSRegisterLinkService
#define MLRegisterLinkServiceFromLinkServer	WSRegisterLinkServiceFromLinkServer
#define MLRegisterLinkServiceWithHostname	WSRegisterLinkServiceWithHostname
#define MLRegisterLinkServiceWithPortAndHostname	WSRegisterLinkServiceWithPortAndHostname
#define MLReleaseBinaryNumberArray	WSReleaseBinaryNumberArray
#define MLReleaseBinaryNumberList	WSReleaseBinaryNumberList
#define MLReleaseByteArray	WSReleaseByteArray
#define MLReleaseByteString	WSReleaseByteString
#define MLReleaseByteSymbol	WSReleaseByteSymbol
#define MLReleaseCompilerID	WSReleaseCompilerID
#define MLReleaseDomainNameList	WSReleaseDomainNameList
#define MLReleaseDoubleArray	WSReleaseDoubleArray
#define MLReleaseEnvIDString	WSReleaseEnvIDString
#define MLReleaseErrorMessage	WSReleaseErrorMessage
#define MLReleaseFloatArray	WSReleaseFloatArray
#define MLReleaseGetArrayState	WSReleaseGetArrayState
#define MLReleaseInteger16Array	WSReleaseInteger16Array
#define MLReleaseInteger16List	WSReleaseInteger16List
#define MLReleaseInteger32Array	WSReleaseInteger32Array
#define MLReleaseInteger32List	WSReleaseInteger32List
#define MLReleaseInteger64Array	WSReleaseInteger64Array
#define MLReleaseInteger64List	WSReleaseInteger64List
#define MLReleaseInteger8Array	WSReleaseInteger8Array
#define MLReleaseInteger8List	WSReleaseInteger8List
#define MLReleaseIntegerArray	WSReleaseIntegerArray
#define MLReleaseIntegerList	WSReleaseIntegerList
#define MLReleaseInterfaceFromLinkServer	WSReleaseInterfaceFromLinkServer
#define MLReleaseLinkName	WSReleaseLinkName
#define MLReleaseLinkProtocolNames	WSReleaseLinkProtocolNames
#define MLReleaseLinksFromEnvironment	WSReleaseLinksFromEnvironment
#define MLReleaseLogFileNameForLink	WSReleaseLogFileNameForLink
#define MLReleaseLongDoubleArray	WSReleaseLongDoubleArray
#define MLReleaseLongIntegerArray	WSReleaseLongIntegerArray
#define MLReleaseLowLevelDeviceName	WSReleaseLowLevelDeviceName
#define MLReleaseNetworkAddressList	WSReleaseNetworkAddressList
#define MLReleaseParameters	WSReleaseParameters
#define MLReleasePutArrayState	WSReleasePutArrayState
#define MLReleaseReal128Array	WSReleaseReal128Array
#define MLReleaseReal128List	WSReleaseReal128List
#define MLReleaseReal32Array	WSReleaseReal32Array
#define MLReleaseReal32List	WSReleaseReal32List
#define MLReleaseReal64Array	WSReleaseReal64Array
#define MLReleaseReal64List	WSReleaseReal64List
#define MLReleaseRealArray	WSReleaseRealArray
#define MLReleaseRealList	WSReleaseRealList
#define MLReleaseShortIntegerArray	WSReleaseShortIntegerArray
#define MLReleaseString	WSReleaseString
#define MLReleaseSymbol	WSReleaseSymbol
#define MLReleaseUCS2CompilerID	WSReleaseUCS2CompilerID
#define MLReleaseUCS2ErrorMessage	WSReleaseUCS2ErrorMessage
#define MLReleaseUCS2LinkName	WSReleaseUCS2LinkName
#define MLReleaseUCS2String	WSReleaseUCS2String
#define MLReleaseUCS2Symbol	WSReleaseUCS2Symbol
#define MLReleaseUnicodeContainer	WSReleaseUnicodeContainer
#define MLReleaseUTF16CompilerID	WSReleaseUTF16CompilerID
#define MLReleaseUTF16ErrorMessage	WSReleaseUTF16ErrorMessage
#define MLReleaseUTF16LinkName	WSReleaseUTF16LinkName
#define MLReleaseUTF16String	WSReleaseUTF16String
#define MLReleaseUTF16Symbol	WSReleaseUTF16Symbol
#define MLReleaseUTF32CompilerID	WSReleaseUTF32CompilerID
#define MLReleaseUTF32ErrorMessage	WSReleaseUTF32ErrorMessage
#define MLReleaseUTF32LinkName	WSReleaseUTF32LinkName
#define MLReleaseUTF32String	WSReleaseUTF32String
#define MLReleaseUTF32Symbol	WSReleaseUTF32Symbol
#define MLReleaseUTF8CompilerID	WSReleaseUTF8CompilerID
#define MLReleaseUTF8ErrorMessage	WSReleaseUTF8ErrorMessage
#define MLReleaseUTF8LinkName	WSReleaseUTF8LinkName
#define MLReleaseUTF8String	WSReleaseUTF8String
#define MLReleaseUTF8Symbol	WSReleaseUTF8Symbol
#define MLRequest	WSRequest
#define MLRequestArgv	WSRequestArgv
#define MLRequestArgvCast	WSRequestArgvCast
#define MLRequestCast	WSRequestCast
#define MLRequestToInteract	WSRequestToInteract
#define MLRequestToInteractCast	WSRequestToInteractCast
#define MLResolveLinkService	WSResolveLinkService
#define MLScanString	WSScanString
#define MLSeekMark	WSSeekMark
#define MLSeekToMark	WSSeekToMark
#define MLServiceProtocolFromReference	WSServiceProtocolFromReference
#define MLSetAllocParameter	WSSetAllocParameter
#define MLSetDefaultYieldFunction	WSSetDefaultYieldFunction
#define MLSetDeviceParameter	WSSetDeviceParameter
#define MLSetDialogFunction	WSSetDialogFunction
#define MLSetEncodingParameter	WSSetEncodingParameter
#define MLSetEnvIDString	WSSetEnvIDString
#define MLSetEnvironmentData	WSSetEnvironmentData
#define MLSetError	WSSetError
#define MLSetMessageHandler	WSSetMessageHandler
#define MLSetName	WSSetName
#define MLSetResourceParameter	WSSetResourceParameter
#define MLSetSignalHandler	WSSetSignalHandler
#define MLSetSignalHandlerFromFunction	WSSetSignalHandlerFromFunction
#define MLSetSymbolReplacement	WSSetSymbolReplacement
#define MLSetThreadSafeLinksParameter	WSSetThreadSafeLinksParameter
#define MLSetUserBlock	WSSetUserBlock
#define MLSetUserData	WSSetUserData
#define MLSetYieldFunction	WSSetYieldFunction
#define MLShutdownLinkServer	WSShutdownLinkServer
#define MLSleepYP	WSSleepYP
#define MLStopBrowsingForLinkServices	WSStopBrowsingForLinkServices
#define MLStopHandlingSignal	WSStopHandlingSignal
#define MLStopLoggingStream	WSStopLoggingStream
#define MLStopLoggingStreamToFile	WSStopLoggingStreamToFile
#define MLStopRegisteringLinkService	WSStopRegisteringLinkService
#define MLStopResolvingLinkService	WSStopResolvingLinkService
#define MLStopRegisteringLinkServiceForLink	WSStopRegisteringLinkServiceForLink
#define MLStringCharacter	WSStringCharacter
#define MLStringFirstPosFun	WSStringFirstPosFun
#define MLStringToArgv	WSStringToArgv
#define MLTakeLast	WSTakeLast
#define MLTestHead	WSTestHead
#define MLTestHeadWithArgCount	WSTestHeadWithArgCount
#define MLTestString	WSTestString
#define MLTestSymbol	WSTestSymbol
#define MLTestUCS2Head	WSTestUCS2Head
#define MLTestUCS2HeadWithArgCount	WSTestUCS2HeadWithArgCount
#define MLTestUCS2String	WSTestUCS2String
#define MLTestUCS2Symbol	WSTestUCS2Symbol
#define MLTestUTF16Head	WSTestUTF16Head
#define MLTestUTF16HeadWithArgCount	WSTestUTF16HeadWithArgCount
#define MLTestUTF16String	WSTestUTF16String
#define MLTestUTF16Symbol	WSTestUTF16Symbol
#define MLTestUTF32Head	WSTestUTF32Head
#define MLTestUTF32HeadWithArgCount	WSTestUTF32HeadWithArgCount
#define MLTestUTF32String	WSTestUTF32String
#define MLTestUTF32Symbol	WSTestUTF32Symbol
#define MLTestUTF8Head	WSTestUTF8Head
#define MLTestUTF8HeadWithArgCount	WSTestUTF8HeadWithArgCount
#define MLTestUTF8String	WSTestUTF8String
#define MLTestUTF8Symbol	WSTestUTF8Symbol
#define MLToLinkID	WSToLinkID
#define MLTransferExpression	WSTransferExpression
#define MLTransferToEndOfLoopbackLink	WSTransferToEndOfLoopbackLink
#define MLUCS2CompilerID	WSUCS2CompilerID
#define MLUCS2ErrorMessage	WSUCS2ErrorMessage
#define MLUCS2LinkName	WSUCS2LinkName
#define MLUTF16CompilerID	WSUTF16CompilerID
#define MLUTF16ErrorMessage	WSUTF16ErrorMessage
#define MLUTF16LinkName	WSUTF16LinkName
#define MLUTF32CompilerID	WSUTF32CompilerID
#define MLUTF32ErrorMessage	WSUTF32ErrorMessage
#define MLUTF32LinkName	WSUTF32LinkName
#define MLUTF8CompilerID	WSUTF8CompilerID
#define MLUTF8ErrorMessage	WSUTF8ErrorMessage
#define MLUTF8LinkName	WSUTF8LinkName
#define MLUnsetSignalHandler	WSUnsetSignalHandler
#define MLUserBlock	WSUserBlock
#define MLUserCast	WSUserCast
#define MLUserData	WSUserData
#define MLValid	WSValid
#define MLVersionNumbers	WSVersionNumbers
#define MLWaitForLinkActivity	WSWaitForLinkActivity
#define MLWaitForLinkActivityWithCallback	WSWaitForLinkActivityWithCallback
#define MLWaitForNewLinkFromLinkServer	WSWaitForNewLinkFromLinkServer
#define MLYieldFunction	WSYieldFunction
#define MLYielderCast	WSYielderCast


/*---------------------------------------------------------------------
 * Public API related symbols
 */
/* in mltypes.h */
#define MLPointer  WSPointer
#define MLENV  WSENV
#define MLEnvironment  WSEnvironment
#define MLEnvironmentParameter  WSEnvironmentParameter
#define MLINK  WSLINK
#define MLMARK  WSMARK


/*---------------------------------------------------------------------
 * Public API related symbols used for function return type
 */
/* used by kernel and FE */
#define MLMessageHandlerObject  WSMessageHandlerObject
#define mlint64  wsint64
#define mlextended_double wsextended_double

/* 
 * ATTENTION: mlapi_result , mlapi_token , mldlg_result
 * Use 'int' instead of these. These were replaced with int for MLINTERFACE >=3.
 * Used in a few places in kernel and FE.
 *
 * ATTENTION: MLSUCCESS , MLFAILURE
 * defined in mltypes.h. This is for internal use.
 * These is related to the above types. Return type is changed to int for MLINTERFACE >=3,
 * thus use 0 for MLFAILURE  1 for MLSUCCESS as described in document.
 */


/* part of API, but not used in kernel nor FE. may remove later */
#define MLMessageHandlerType  WSMessageHandlerType


/*---------------------------------------------------------------------
 * Public API related symbols used for function argement type
 */
/* used by kernel or FE */
#define MLLinkWaitCallBackObject  WSLinkWaitCallBackObject
#define MLServiceRef  WSServiceRef
#define MLSignalHandlerType  WSSignalHandlerType
#define MLUserFunction  WSUserFunction
#define MLUserFunctionType  WSUserFunctionType
#define MLUserFunctionTypePointer  WSUserFunctionTypePointer
#define MLYieldFunctionObject  WSYieldFunctionObject
#define MLYieldParameters  WSYieldParameters

/* part of APIs but not used in kernel nor FE. may remove later */
#define MLAllocator  WSAllocator
#define MLAllocatorp  WSAllocatorp
#define MLDeallocator  WSDeallocator
#define MLDeallocatorp  WSDeallocatorp
#define MLLinkServer  WSLinkServer
#define MLNewLinkCallbackFunction  WSNewLinkCallbackFunction
#define MLOldStringPositionPointer  WSOldStringPositionPointer
#define MLUnicodeContainer  WSUnicodeContainer
#define MLAllocatorProcPtr  WSAllocatorProcPtr
#define MLDeallocatorProcPtr  WSDeallocatorProcPtr
#define MLHandlerProcPtr  WSHandlerProcPtr
#define MLUserProcPtr  WSUserProcPtr
#define MLYielderProcPtr  WSYielderProcPtr
#define MLYieldFunctionType  WSYieldFunctionType
/* in mlalert.h */
#define MLDialogProcPtr  WSDialogProcPtr
#define MLAlertProcPtr  WSAlertProcPtr
#define MLRequestProcPtr  WSRequestProcPtr
#define MLConfirmProcPtr  WSConfirmProcPtr
#define MLRequestArgvProcPtr  WSRequestArgvProcPtr
#define MLRequestToInteractProcPtr  WSRequestToInteractProcPtr


/*---------------------------------------------------------------------
 * Public symbol from typedef
 */
#define mltimeval wstimeval  /* may capitalize to distingush public symbol */
#define MLParametersPointer  WSParametersPointer


/*---------------------------------------------------------------------
 * Public symbols from enum
 */
/* values for devinfo_selector */
#define MLTerminateMessage  WSTerminateMessage
#define MLInterruptMessage  WSInterruptMessage
#define MLAbortMessage  WSAbortMessage
#define MLEndPacketMessage  WSEndPacketMessage
#define MLSynchronizeMessage  WSSynchronizeMessage
#define MLImDyingMessage  WSImDyingMessage
#define MLWaitingAcknowledgment  WSWaitingAcknowledgment
#define MLMarkTopLevelMessage  WSMarkTopLevelMessage
#define MLLinkClosingMessage  WSLinkClosingMessage
#define MLAuthenticateFailure  WSAuthenticateFailure
#define MLSuspendActivitiesMessage  WSSuspendActivitiesMessage
#define MLResumeActivitiesMessage  WSResumeActivitiesMessage
#define MLFirstUserMessage  WSFirstUserMessage
#define MLLastUserMessage  WSLastUserMessage

/* MLSetDialogFunction() args for long funcnum */
#define MLAlertFunction  WSAlertFunction
#define MLRequestFunction  WSRequestFunction
#define MLConfirmFunction  WSConfirmFunction
#define MLRequestArgvFunction  WSRequestArgvFunction
#define MLRequestToInteractFunction  WSRequestToInteractFunction
#define MLDialogFunctionType  WSDialogFunctionType

/* MLNewUnicodeContainer arg enum type */
#define MLUnicodeContainerType  WSUnicodeContainerType


/*---------------------------------------------------------------------
 * MPREP symbols
 */
/* public */
#define mlapi_packet wsapi_packet

#if !defined(MLINTERFACE) && defined(WSINTERFACE)
#define MLINTERFACE WSINTERFACE
#endif

#endif /* _REBRAND_H_ */
/*****************************************************************************
 * END - ReBrand
 *****************************************************************************/




#ifndef ML_EXTERN_C

#if defined(__cplusplus)
#define ML_C "C"
#define ML_EXTERN_C extern "C" {
#define ML_END_EXTERN_C }
#define WS_C "C"
#define WS_EXTERN_C extern "C" {
#define WS_END_EXTERN_C }
#else
#define ML_C
#define ML_EXTERN_C
#define ML_END_EXTERN_C
#define WS_C
#define WS_EXTERN_C
#define WS_END_EXTERN_C
#endif

#endif





#if WINDOWS_MATHLINK && (MPREP_REVISION || !defined(APIENTRY) || !defined(FAR))

#if defined(WIN32_LEAN_AND_MEAN) && defined(WIN32_EXTRA_LEAN)
#include <windows.h>
#elif defined( WIN32_LEAN_AND_MEAN)
#define WIN32_EXTRA_LEAN
#include <windows.h>
#undef WIN32_EXTRA_LEAN
#elif defined( WIN32_EXTRA_LEAN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#else
#define WIN32_EXTRA_LEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_EXTRA_LEAN
#undef WIN32_LEAN_AND_MEAN
#endif


#endif


#ifndef _MLDEVICE_H
#define _MLDEVICE_H



#ifndef P


#ifndef MLPROTOTYPES
#define MLPROTOTYPES 1
#endif

#if MLPROTOTYPES || __STDC__ || defined(__cplusplus) || ! UNIX_MATHLINK
#define P(s) s
#undef MLPROTOTYPES
#define MLPROTOTYPES 1
#else
#define P(s) ()
#undef MLPROTOTYPES
#define MLPROTOTYPES 0
#endif
#endif


#ifndef _MLFAR_H
#define _MLFAR_H

#ifndef FAR


#if WINDOWS_MATHLINK

#ifndef FAR
/*\ syntax\ error\ */\ )
#endif
#else
#define FAR
#endif


#endif

/* //rename this file mlfarhuge.h */

#ifndef MLHUGE
#if WINDOWS_MATHLINK && !(WIN32_MATHLINK || WIN64_MATHLINK)
#define MLHUGE huge
#else
#define MLHUGE
#endif
#endif

#endif /* _MLFAR_H */


#ifndef _MLTYPES_H
#define _MLTYPES_H






#ifndef _MLBASICTYPES_H
#define _MLBASICTYPES_H




#ifndef _MLINT64_H
#define _MLINT64_H


#if WIN64_MATHLINK || X86_64_LINUX_MATHLINK || ARM64_DARWIN_MATHLINK || X86_64_DARWIN_MATHLINK
#define ML64BIT_MATHLINK 1
#endif

#endif /* MLINT64_H */



#if ML64BIT_MATHLINK
#define ML_SMALLEST_SIGNED_64BIT        -9223372036854775807L - 1
#define ML_LARGEST_SIGNED_64BIT         9223372036854775807L
#define ML_LARGEST_UNSIGNED_64BIT       18446744073709551615UL
#else
#define ML_SMALLEST_SIGNED_64BIT        -9223372036854775807LL - 1
#define ML_LARGEST_SIGNED_64BIT         9223372036854775807LL
#define ML_LARGEST_UNSIGNED_64BIT       18446744073709551615ULL
#endif /* ML64BIT_MATHLINK */

#ifndef NO_INT64_STRUCT
#define NO_INT64_STRUCT

#if ML64BIT_MATHLINK
typedef unsigned int wint;
#else
typedef unsigned long wint;
#endif /* ML64BIT_MATHLINK */

#if LITTLEENDIAN_NUMERIC_TYPES
typedef struct _wint{
	wint low, hi;
} wint64;
#else
typedef struct _wint{
	wint hi, low;
} wint64;
#endif /* LITTLEENDIAN_NUMERIC_TYPES */


#endif /* NO_INT64_STRUCT */


#if MLINTERFACE >= 4
#if WIN64_MATHLINK || WIN32_MATHLINK

typedef long mllong32;
typedef long wslong32;
typedef unsigned long mlulong32;
typedef unsigned long wsulong32;


typedef __int64 mlint64;
typedef __int64 wsint64;
typedef unsigned __int64 mluint64;
typedef unsigned __int64 wsuint64;

#if WIN64_MATHLINK
typedef mlint64 mlbigint;
typedef wsint64 wsbigint;
typedef mluint64 mlbiguint;
typedef wsuint64 wsbiguint;
#else
typedef mllong32 mlbigint;
typedef wslong32 wsbigint;
typedef mlulong32 mlbiguint;
typedef wsulong32 wsbiguint;
#endif


#elif X86_64_LINUX_MATHLINK || ARM64_DARWIN_MATHLINK || X86_64_DARWIN_MATHLINK

typedef int mllong32;
typedef int wslong32;
typedef unsigned int mlulong32;
typedef unsigned int wsulong32;


typedef long mlint64;
typedef long wsint64;
typedef unsigned long mluint64;
typedef unsigned long wsuint64;

typedef mlint64 mlbigint;
typedef mluint64 mlbiguint;

#else /* All other 32 bit platforms */

typedef long mllong32;
typedef long wslong32;
typedef unsigned long mlulong32;
typedef unsigned long wsulong32;


typedef long long mlint64;
typedef long long wsint64;
typedef unsigned long long mluint64;
typedef unsigned long long wsuint64;

typedef mllong32 mlbigint;
typedef mlulong32 mlbiguint;

#endif /* WIN64_MATHLINK || WIN32_MATHLINK */



#endif /* MLINTERFACE >= 4 */




#if MLINTERFACE < 4

#if WIN64_MATHLINK


typedef __int64 mlint64;
typedef unsigned __int64 mluint64;

#elif X86_64_LINUX_MATHLINK || ARM64_DARWIN_MATHLINK || X86_64_DARWIN_MATHLINK


typedef long mlint64;
typedef long wsint64;
typedef unsigned long mluint64;
typedef unsigned long wsuint64;

#else /* All other 32 bit platforms */


#ifndef NO_MLINT64_STRUCT
#define NO_MLINT64_STRUCT

typedef wint64 mlint64;
typedef wint64 wsint64;
typedef wint64 mluint64;
typedef wint64 wsuint64;

#endif /* NO_MLINT64_STRUCT */

#endif


#endif /* MLINTERFACE < 4 */


#endif /* _MLBASICTYPES_H */



#if WINDOWS_MATHLINK

#ifndef	APIENTRY
#define APIENTRY far pascal
#endif
#ifndef CALLBACK
#define CALLBACK APIENTRY
#endif
#if (WIN32_MATHLINK || WIN64_MATHLINK || CYGWIN_MATHLINK)
 /* try this #define MLEXPORT __declspec(dllexport) */
#define MLEXPORT
#define WSEXPORT
#else
#define MLEXPORT __export
#define WSEXPORT __export
#endif
#define MLCB APIENTRY MLEXPORT
#define WSCB APIENTRY WSEXPORT
#define MLAPI APIENTRY
#define WSAPI APIENTRY

#else
#define MLCB
#define WSCB
#define MLAPI
#define WSAPI
#define MLEXPORT
#define WSEXPORT
#endif

#if defined(LINUX_MATHLINK)
#define MLATTR __attribute__ ((visibility("default")))
#define WSATTR __attribute__ ((visibility("default")))
#else
#define MLATTR
#define WSATTR
#endif

#define MLAPI_ MLAPI


#ifndef MLDEFN
#define MLDEFN( rtype, name, params) extern MLATTR rtype MLAPI MLEXPORT name params
#endif
#ifndef MLDECL
#define MLDECL( rtype, name, params) extern rtype MLAPI name P(params)
#endif

#ifndef WSDEFN
#define WSDEFN( rtype, name, params) extern WSATTR rtype WSAPI WSEXPORT name params
#endif
#ifndef WSDECL
#define WSDECL( rtype, name, params) extern rtype WSAPI name P(params)
#endif

#ifndef ML_DEFN
#define ML_DEFN( rtype, name, params) extern rtype MLAPI_ MLEXPORT name params
#endif
#ifndef ML_DECL
#define ML_DECL( rtype, name, params) extern ML_C rtype MLAPI_ name P(params)
#endif



#ifndef MLCBPROC
#define MLCBPROC( rtype, name, params) typedef rtype (MLCB * name) P(params)
#endif
#ifndef MLCBDECL
#define MLCBDECL( rtype, name, params) extern rtype MLCB name P(params)
#endif
#ifndef MLCBDEFN
#define MLCBDEFN( rtype, name, params) extern rtype MLCB name params
#endif

#ifndef WSCBPROC
#define WSCBPROC( rtype, name, params) typedef rtype (WSCB * name) P(params)
#endif
#ifndef WSCBDECL
#define WSCBDECL( rtype, name, params) extern rtype WSCB name P(params)
#endif
#ifndef WSCBDEFN
#define WSCBDEFN( rtype, name, params) extern rtype WSCB name params
#endif




/* move into mlalert.h */
#ifndef MLDPROC
#define MLDPROC MLCBPROC
#endif
#ifndef WSDPROC
#define WSDPROC WSCBPROC
#endif
#ifndef MLDDECL
#define MLDDECL MLCBDECL
#endif
#ifndef WSDDECL
#define WSDDECL WSCBDECL
#endif
#ifndef MLDDEFN
#define MLDDEFN MLCBDEFN
#endif
#ifndef WSDDEFN
#define WSDDEFN WSCBDEFN
#endif




/* move into ml3state.h or mlstrenv.h */
#ifndef MLTPROC
#define MLTPROC MLCBPROC
#endif
#ifndef WSTPROC
#define WSTPROC WSCBPROC
#endif
#ifndef MLTDECL
#define MLTDECL MLCBDECL
#endif
#ifndef WSTDECL
#define WSTDECL WSCBDECL
#endif
#ifndef MLTDEFN
#define MLTDEFN MLCBDEFN
#endif
#ifndef WSTDEFN
#define WSTDEFN WSCBDEFN
#endif


/* move into mlnumenv.h */
#ifndef MLNPROC
#define MLNPROC MLCBPROC
#endif
#ifndef WSNPROC
#define WSNPROC WSCBPROC
#endif
#ifndef MLNDECL
#define MLNDECL MLCBDECL
#endif
#ifndef WSNDECL
#define WSNDECL WSCBDECL
#endif
#ifndef MLNDEFN
#define MLNDEFN MLCBDEFN
#endif
#ifndef WSNDEFN
#define WSNDEFN WSCBDEFN
#endif


/* move into mlalloc.h */
#ifndef MLAPROC
#define MLAPROC MLCBPROC
#endif
#ifndef MLADECL
#define MLADECL MLCBDECL
#endif
#ifndef MLADEFN
#define MLADEFN MLCBDEFN
#endif
#ifndef MLFPROC
#define MLFPROC MLCBPROC
#endif
#ifndef MLFDECL
#define MLFDECL MLCBDECL
#endif
#ifndef MLFDEFN
#define MLFDEFN MLCBDEFN
#endif
#ifndef MLRAPROC
#define MLRAPROC MLCBPROC
#endif
#ifndef MLRADECL
#define MLRADECL MLCBDECL
#endif
#ifndef MLRADEFN
#define MLRADEFN MLCBDEFN
#endif


/* move into mlstddev.h */
#ifndef MLYPROC
#define MLYPROC MLCBPROC
#endif
#ifndef WSYPROC
#define WSYPROC WSCBPROC
#endif
#ifndef MLYDECL
#define MLYDECL MLCBDECL
#endif
#ifndef WSYDECL
#define WSYDECL WSCBDECL
#endif
#ifndef MLYDEFN
#define MLYDEFN MLCBDEFN
#endif
#ifndef WSYDEFN
#define WSYDEFN WSCBDEFN
#endif
#ifndef MLMPROC
#define MLMPROC MLCBPROC
#endif
#ifndef WSMPROC
#define WSMPROC WSCBPROC
#endif
#ifndef MLMDECL
#define MLMDECL MLCBDECL
#endif
#ifndef WSMDECL
#define WSMDECL WSCBDECL
#endif
#ifndef MLMDEFN
#define MLMDEFN MLCBDEFN
#endif
#ifndef WSMDEFN
#define WSMDEFN WSCBDEFN
#endif


/* move into mlmake.h */
#ifndef MLUPROC
#define MLUPROC MLCBPROC
#endif
#ifndef MLUDECL
#define MLUDECL MLCBDECL
#endif
#ifndef MLUDEFN
#define MLUDEFN MLCBDEFN
#endif


/* move into mlmake.h */
#ifndef MLBPROC
#define MLBPROC MLCBPROC
#endif
#ifndef MLBDECL
#define MLBDECL MLCBDECL
#endif
#ifndef MLBDEFN
#define MLBDEFN MLCBDEFN
#endif

#ifndef MLDMPROC
#define MLDMPROC MLCBPROC
#endif
#ifndef MLDMDECL
#define MLDMDECL MLCBDECL
#endif
#ifndef MLDMDEFN
#define MLDMDEFN MLCBDEFN
#endif

#if MLINTERFACE >= 4
#ifndef MLWPROC
#define MLWPROC MLCBPROC
#endif
#endif

#ifndef __uint_ct__
#define __uint_ct__ unsigned int
#endif
#ifndef __int_ct__
#define __int_ct__ int
#endif


typedef unsigned char        uchar_ct;
typedef uchar_ct       FAR * ucharp_ct;
typedef ucharp_ct      FAR * ucharpp_ct;
typedef ucharpp_ct     FAR * ucharppp_ct;
typedef unsigned short       ushort_ct;
typedef ushort_ct      FAR * ushortp_ct;
typedef ushortp_ct     FAR * ushortpp_ct;
typedef ushortpp_ct    FAR * ushortppp_ct;
typedef __uint_ct__          uint_ct;
typedef __uint_ct__    FAR * uintp_ct;
typedef uintp_ct       FAR * uintpp_ct;
typedef __int_ct__           int_ct;
typedef void           FAR * voidp_ct;
typedef voidp_ct       FAR * voidpp_ct;
typedef char           FAR * charp_ct;
typedef charp_ct       FAR * charpp_ct;
typedef charpp_ct      FAR * charppp_ct;
typedef long                 long_ct;
typedef long_ct        FAR * longp_ct;
typedef longp_ct       FAR * longpp_ct;
typedef unsigned long        ulong_ct;
typedef ulong_ct       FAR * ulongp_ct;




#ifndef MLCONST
#if MLPROTOTYPES
#define MLCONST const
#else
#define MLCONST
#endif
#endif

typedef MLCONST unsigned short FAR * kushortp_ct;
typedef MLCONST unsigned short FAR * FAR * kushortpp_ct;
typedef MLCONST unsigned int FAR * kuintp_ct;
typedef MLCONST unsigned int FAR * FAR * kuintpp_ct;
typedef MLCONST unsigned char FAR * kucharp_ct;
typedef MLCONST unsigned char FAR * FAR * kucharpp_ct;
typedef MLCONST char FAR * kcharp_ct;
typedef MLCONST char FAR * FAR * kcharpp_ct;
typedef MLCONST void FAR * kvoidp_ct;


typedef void FAR * MLPointer;

#ifndef __MLENVPARAM__
	typedef void FAR * MLENVPARAM;
	typedef MLENVPARAM MLEnvironmentParameter;
#define __MLENVPARAM__
#endif

#ifndef __MLENV__
	typedef struct ml_environment FAR *MLENV;
	typedef MLENV MLEnvironment;
#define __MLENV__
#endif

#ifndef __MLINK__
	typedef struct MLink FAR *MLINK;
#define __MLINK__
#endif

#ifndef __MLMARK__
	typedef struct MLinkMark FAR *MLMARK;
	typedef MLMARK MLINKMark;
#define __MLMARK__
#endif

#ifndef __mlapi_token__
#define __mlapi_token__ int_ct
#endif
typedef __mlapi_token__   mlapi_token;


typedef unsigned long      mlapi__token;
typedef mlapi__token FAR * mlapi__tokenp;

#ifndef __mlapi_packet__
#define __mlapi_packet__ int_ct
#endif
typedef __mlapi_packet__  mlapi_packet;


typedef long mlapi_error;
typedef long mlapi__error;

typedef long  long_st;
typedef longp_ct longp_st;
typedef longp_st* longpp_st;

typedef long long_et;


#ifndef __mlapi_result__
#define __mlapi_result__ int_ct
#endif
typedef __mlapi_result__ mlapi_result;


#define MLSUCCESS (1) /*bugcheck:  this stuff doesnt belong where it can be seen at MLAPI_ layer */
#define MLFAILURE (0)

ML_EXTERN_C

#if WINDOWS_MATHLINK
typedef int (CALLBACK *__MLProcPtr__)();
#else
typedef long (* __MLProcPtr__)(void);
#endif

ML_END_EXTERN_C

#endif /* _MLTYPES_H */



#if WINDOWS_MATHLINK

#ifndef	APIENTRY
#define	APIENTRY far pascal
#endif
#define MLBN APIENTRY /* bottleneck function: upper layer calls lower layer */
#else
#define MLBN
#endif

#define BN MLBN

/* #include "mlcfm.h" */


ML_EXTERN_C



typedef void FAR * dev_voidp;
typedef dev_voidp dev_type;
typedef dev_type FAR * dev_typep;
typedef long devproc_error;
typedef unsigned long devproc_selector;


#define MLDEV_WRITE_WINDOW  0
#define MLDEV_WRITE         1
#define MLDEV_HAS_DATA      2
#define MLDEV_READ          3
#define MLDEV_READ_COMPLETE 4
#define MLDEV_ACKNOWLEDGE   5

#define T_DEV_WRITE_WINDOW  MLDEV_WRITE_WINDOW
#define T_DEV_WRITE         MLDEV_WRITE
#define T_DEV_HAS_DATA      MLDEV_HAS_DATA
#define T_DEV_READ          MLDEV_READ
#define T_DEV_READ_COMPLETE MLDEV_READ_COMPLETE


#ifndef SCATTERED
#define SCATTERED 0
#undef NOT_SCATTERED
#define NOT_SCATTERED 1
#endif


typedef struct read_buf {
	unsigned short length;
	unsigned char* ptr;
} read_buf;

typedef read_buf FAR * read_bufp;
typedef read_bufp FAR * read_bufpp;

MLDMPROC( devproc_error, MLDeviceProcPtr, ( dev_type dev, devproc_selector selector, dev_voidp p1, dev_voidp p2));
MLDMDECL( devproc_error, MLDeviceMain, ( dev_type dev, devproc_selector selector, dev_voidp p1, dev_voidp p2));

typedef MLDeviceProcPtr MLDeviceUPP;
#define CallMLDeviceProc(userRoutine, thing, selector, p1, p2) (*(userRoutine))((thing), (selector), (dev_voidp)(p1), (dev_voidp)(p2))
#define NewMLDeviceProc(userRoutine) (userRoutine)

typedef MLDeviceUPP dev_main_type;
typedef dev_main_type FAR * dev_main_typep;

ML_END_EXTERN_C


#endif /* _MLDEVICE_H */



#ifndef _MLAPI_H
#define _MLAPI_H









ML_EXTERN_C

#ifndef _MLALLOC_H
#define _MLALLOC_H




/* #include "mlcfm.h" */


#if WIN64_MATHLINK
MLAPROC( void*, MLAllocatorProcPtr, (unsigned __int64));
#else
MLAPROC( void*, MLAllocatorProcPtr, (unsigned long));
#endif



typedef MLAllocatorProcPtr MLAllocatorUPP;
#define CallMLAllocatorProc(userRoutine, size) (*(userRoutine))((size))
#define NewMLAllocatorProc(userRoutine) (userRoutine)




MLFPROC( void, MLDeallocatorProcPtr, (void*));

typedef MLDeallocatorProcPtr MLDeallocatorUPP;
#define CallMLDeallocatorProc(userRoutine, p) (*(userRoutine))((p))
#define NewMLDeallocatorProc(userRoutine) (userRoutine)



#endif /* _MLALLOC_H */


/* explicitly not protected by _MLALLOC_H in case MLDECL is redefined for multiple inclusion */


/* just some type-safe casts */
MLDECL( __MLProcPtr__, MLAllocatorCast,   ( MLAllocatorProcPtr f));
MLDECL( __MLProcPtr__, MLDeallocatorCast, ( MLDeallocatorProcPtr f));

ML_END_EXTERN_C


typedef MLAllocatorUPP MLAllocator;
typedef MLAllocator FAR * MLAllocatorp;
#define MLCallAllocator CallMLAllocatorProc
#define MLNewAllocator NewMLAllocatorProc

typedef MLDeallocatorUPP MLDeallocator;
typedef MLDeallocator FAR * MLDeallocatorp;
#define MLCallDeallocator CallMLDeallocatorProc
#define MLNewDeallocator NewMLDeallocatorProc

#define MLallocator MLAllocator
#define MLdeallocator MLDeallocator

#endif /* _MLAPI_H */



#ifndef _WSNTYPES_H
#define _WSNTYPES_H





#ifndef _WSNUMENV_H
#define _WSNUMENV_H






/* wsne__s2 must convert empty strings to zero */



ML_EXTERN_C


#define REALBIT 4
#define REAL_MASK (1 << REALBIT)
#define XDRBIT 5
#define XDR_MASK (1 << XDRBIT)
#define BINARYBIT 7
#define BINARY_MASK (1 << BINARYBIT)
#define SIZEVARIANTBIT 6
#define SIZEVARIANT_MASK (1 << SIZEVARIANTBIT)


#define WSTK_INVALID                                          155


#define WSNE__IMPLIED_SIZE( tok, num_dispatch) ((tok) & XDR_MASK || !((tok) & SIZEVARIANT_MASK) \
		? (tok) & 0x08 ? (tok) & (0x0E + 2) : (1 << ((tok)>>1 & 0x03)) \
		: call_num_dispatch( (num_dispatch), WSNE__SIZESELECTOR((tok)), 0,0,0))

/* Range[-128, 127] */
/* 160 -> ((unsigned char)'\240') */
#define	WSTK_8BIT_SIGNED_2sCOMPLEMENT_INTEGER                 160
/* Range[0, 255] */
/* 161 -> ((unsigned char)'\241') */
#define	WSTK_8BIT_UNSIGNED_2sCOMPLEMENT_INTEGER               161
#define WSTK_8BIT_UNSIGNED_INTEGER WSTK_8BIT_UNSIGNED_2sCOMPLEMENT_INTEGER

/* Range[-32768, 32767] */
/* 162 -> ((unsigned char)'\242') */
#define	WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER      162
/* Range[0, 65535] */
/* 163 -> ((unsigned char)'\243') */
#define	WSTK_16BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER    163
#define	WSTK_16BIT_UNSIGNED_BIGENDIAN_INTEGER WSTK_16BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
/* Range[-2147483648, 2147483647] */
/* 164 -> ((unsigned char)'\244') */
#define	WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER      164
/* Range[0, 4294967295] */
/* 165 -> ((unsigned char)'\245') */
#define	WSTK_32BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER    165
#define	WSTK_32BIT_UNSIGNED_BIGENDIAN_INTEGER WSTK_32BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
/* Range[-9223372036854775808, 9223372036854775807] */
/* 166 -> ((unsigned char)'\246') */
#define	WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER      166
/* Range[0, 18446744073709551615] */
/* 167 -> ((unsigned char)'\247') */
#define	WSTK_64BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER    167
#define	WSTK_64BIT_UNSIGNED_BIGENDIAN_INTEGER WSTK_64BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER


/* Range[-32768, 32767] */
/* 226 -> ((unsigned char)'\342') */
#define	WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER   226
/* Range[0, 65535] */
/* 227 -> ((unsigned char)'\343') */
#define	WSTK_16BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER 227
#define	WSTK_16BIT_UNSIGNED_LITTLEENDIAN_INTEGER WSTK_16BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
/* Range[-2147483648, 2147483647] */
/* 228 -> ((unsigned char)'\344') */
#define	WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER   228
/* Range[0, 4294967295] */
/* 229 -> ((unsigned char)'\345') */
#define	WSTK_32BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER 229
#define	WSTK_32BIT_UNSIGNED_LITTLEENDIAN_INTEGER WSTK_32BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
/* Range[-9223372036854775808, 9223372036854775807] */
/* 230 -> ((unsigned char)'\346') */
#define	WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER   230
/* Range[0, 18446744073709551615] */
/* 231 -> ((unsigned char)'\347') */
#define	WSTK_64BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER 231
#define	WSTK_64BIT_UNSIGNED_LITTLEENDIAN_INTEGER WSTK_64BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER

/* Interval[{-3.402823e+38, 3.402823e+38}] */
/* 180 -> ((unsigned char)'\264')    10110100   */
#define	WSTK_BIGENDIAN_IEEE754_SINGLE	                      180
/* Interval[{-1.79769313486232e+308, 1.79769313486232e+308}] */
/* 182 -> ((unsigned char)'\266')    10110110   */
#define	WSTK_BIGENDIAN_IEEE754_DOUBLE	                      182

/* 184 -> ((unsigned char)'\270')    10111000   */
#define WSTK_BIGENDIAN_128BIT_DOUBLE                          184

/* Interval[{-3.402823e+38, 3.402823e+38}] */
/* 244 -> ((unsigned char)'\364')    11110100   */
#define	WSTK_LITTLEENDIAN_IEEE754_SINGLE	                  244
/* Interval[{-1.79769313486232e+308, 1.79769313486232e+308}] */
/* 246 -> ((unsigned char)'\366')    11110110   */
#define	WSTK_LITTLEENDIAN_IEEE754_DOUBLE	                  246

/* 248 -> ((unsigned char)'\370')    11111000   */
#define WSTK_LITTLEENDIAN_128BIT_DOUBLE                       248


/* Note, if the future brings...
 * #define WSTK_128BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER   ((unsigned char)'\257')
 * with  Range[0, 340282366920938463463374607431768211456 (*approximately 3.40282e+38*)]
 * the dynamic range is still a monotonically increasing function of the token value.
 * An implementation might choose to set the high varient bit to mainain this property
 * and dispatch more efficiently by avoiding overflow checks
 */

#if USE_WSNE__SELECTOR_FUNCTION
int WSNE__SELECTOR(int dtok, int stok);
#else
#define WSNE__SELECTOR( dtok, stok) \
	(((dtok) << 8) | (stok)) /* maybe should mask of high word and cast stok */
#endif
#define WSNE__SIZESELECTOR( tok) WSNE__SELECTOR( 0, tok)
#define WSNE__INITSELECTOR (0)
#define WSNE__TOSTRINGSELECTOR( tok) WSNE__SELECTOR( WSNE__IS_REAL(tok) ? WSTKREAL : WSTKINT, tok)
#define WSNE__FROMSTRINGSELECTOR( dtok, stok) WSNE__SELECTOR( dtok, stok)

#define WSNE__STOK( selector) ( (selector) & 0x000000FF)
#define WSNE__DTOK( selector) ( ((selector) & 0x0000FF00)>>8)

#define WSNE__IS_BINARY( tok) ((tok) & BINARY_MASK)
#define WSNE__IS_REAL( tok) ((tok) & REAL_MASK)
#define WSNE__TEXT_TOKEN( tok) (WSNE__IS_REAL( tok) ? WSTKREAL : WSTKINT)




ML_END_EXTERN_C


#endif /* _WSNUMENV_H */



#ifndef WSINTERFACE
/*\ syntax\ error\ */\ )
#endif


/****************  Special Token types: ****************/

/* WSTK_CSHORT_P         193
   WSTK_CINT_P           194
   WSTK_CLONG_P          195
   WSTK_CFLOAT_P         209
   WSTK_CDOUBLE_P        210
   WSTK_CLONGDOUBLE_P    211 */

#define WSTK_CSHORT_P       (( BINARY_MASK | SIZEVARIANT_MASK | 1))
#define WSTK_CINT_P         (( BINARY_MASK | SIZEVARIANT_MASK | 2))
#define WSTK_CLONG_P        (( BINARY_MASK | SIZEVARIANT_MASK | 3))
#define WSTK_CFLOAT_P       (( BINARY_MASK | SIZEVARIANT_MASK | REAL_MASK | 1))
#define WSTK_CDOUBLE_P      (( BINARY_MASK | SIZEVARIANT_MASK | REAL_MASK | 2))
#define WSTK_CLONGDOUBLE_P  (( BINARY_MASK | SIZEVARIANT_MASK | REAL_MASK | 3))


#define WSTK_64BIT_LITTLEENDIAN_STRUCTURE 196
#define WSTK_64BIT_BIGENDIAN_STRUCTURE    197

/* 158 -> ((unsigned char)'\236') - used in Solaris numerics definitions */
#define WSTK_128BIT_EXTENDED 158
#define WSTK_128BIT_LONGDOUBLE 158


/* Interval[{-1.189731495357231765e+4932, 1.189731495357231765e+4932}] */
/* 218 -> ((unsigned char)'\332') */
#define WSTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED 218

/* Interval[{-1.189731495357231765e+4932, 1.189731495357231765e+4932}] */
/* ((unsigned char)'\330') */
#define WSTK_INTEL_80BIT_EXTENDED 216

/********************  MASTIFF  ****************************/
#define WSMASTIFF_NUMERICS_ID    "mastiff"
#define WSMASTIFF_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSMASTIFF_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSMASTIFF_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSMASTIFF_CINT64         WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSMASTIFF_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSMASTIFF_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSMASTIFF_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSMASTIFF_CLONGDOUBLE    WSTK_128BIT_EXTENDED
#define WSMASTIFF_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSMASTIFF_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSMASTIFF_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSMASTIFF_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSMASTIFF_WSINT64        WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSMASTIFF_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSMASTIFF_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSMASTIFF_WSLONGDOUBLE   WSTK_128BIT_EXTENDED

/********************  JAPANESECHIN  ****************************/
#define WSJAPANESECHIN_NUMERICS_ID    "japanesechin"
#define WSJAPANESECHIN_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSJAPANESECHIN_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSJAPANESECHIN_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSJAPANESECHIN_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSJAPANESECHIN_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSJAPANESECHIN_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSJAPANESECHIN_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSJAPANESECHIN_CLONGDOUBLE    WSTK_128BIT_EXTENDED
#define WSJAPANESECHIN_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSJAPANESECHIN_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSJAPANESECHIN_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSJAPANESECHIN_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSJAPANESECHIN_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSJAPANESECHIN_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSJAPANESECHIN_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSJAPANESECHIN_WSLONGDOUBLE   WSTK_128BIT_EXTENDED

/********************  BORZOI  ****************************/
/* The borzoi numerics environment specifically does not have WSBORZOI_CLONGDOUBLE or
WSBORZOI_WSLONGDOUBLE */

#define WSBORZOI_NUMERICS_ID          "borzoi"
#define WSBORZOI_CSHORT               WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORZOI_CINT                 WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORZOI_CLONG                WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORZOI_CSIZE_T              WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORZOI_CINT64               WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSBORZOI_CFLOAT               WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBORZOI_CDOUBLE              WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBORZOI_WSSHORT              WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORZOI_WSINT                WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORZOI_WSLONG               WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORZOI_WSSIZE_T             WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORZOI_WSINT64              WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSBORZOI_WSFLOAT              WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBORZOI_WSDOUBLE             WSTK_BIGENDIAN_IEEE754_DOUBLE

/********************  BRIARD  ****************************/
/* The briard numerics environment purposefully does not have WSBRIARD_CLONGDOUBLE or
WSBRIARD_WSLONGDOUBLE */

#define WSBRIARD_NUMERICS_ID          "briard"
#define WSBRIARD_CSHORT               WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBRIARD_CINT                 WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBRIARD_CLONG                WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBRIARD_CINT64               WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBRIARD_CSIZE_T              WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBRIARD_CFLOAT               WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBRIARD_CDOUBLE              WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBRIARD_WSSHORT              WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBRIARD_WSINT                WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBRIARD_WSLONG               WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBRIARD_WSINT64              WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBRIARD_WSSIZE_T             WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBRIARD_WSFLOAT              WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBRIARD_WSDOUBLE             WSTK_BIGENDIAN_IEEE754_DOUBLE

/********************  KEESHOND  ****************************/
#define WSKEESHOND_NUMERICS_ID    "keeshond"
#define WSKEESHOND_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKEESHOND_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKEESHOND_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKEESHOND_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKEESHOND_CINT64         WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSKEESHOND_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSKEESHOND_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSKEESHOND_CLONGDOUBLE    WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSKEESHOND_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKEESHOND_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKEESHOND_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKEESHOND_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKEESHOND_WSINT64        WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSKEESHOND_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSKEESHOND_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSKEESHOND_WSLONGDOUBLE   WSTK_BIGENDIAN_IEEE754_DOUBLE

/********************  KOMONDOR  ****************************/
#define WSKOMONDOR_NUMERICS_ID    "komondor"
#define WSKOMONDOR_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKOMONDOR_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKOMONDOR_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKOMONDOR_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKOMONDOR_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKOMONDOR_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSKOMONDOR_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSKOMONDOR_CLONGDOUBLE    WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSKOMONDOR_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKOMONDOR_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKOMONDOR_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKOMONDOR_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKOMONDOR_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSKOMONDOR_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSKOMONDOR_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSKOMONDOR_WSLONGDOUBLE   WSTK_BIGENDIAN_IEEE754_DOUBLE

/********************  NORWEGIANELKHOUND  ****************************/
#define WSNORWEGIANELKHOUND_NUMERICS_ID    "norwegianelkhound"
#define WSNORWEGIANELKHOUND_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWEGIANELKHOUND_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWEGIANELKHOUND_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWEGIANELKHOUND_CINT64         WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSNORWEGIANELKHOUND_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWEGIANELKHOUND_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSNORWEGIANELKHOUND_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSNORWEGIANELKHOUND_CLONGDOUBLE    WSTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED
#define WSNORWEGIANELKHOUND_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWEGIANELKHOUND_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWEGIANELKHOUND_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWEGIANELKHOUND_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWEGIANELKHOUND_WSINT64        WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSNORWEGIANELKHOUND_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSNORWEGIANELKHOUND_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSNORWEGIANELKHOUND_WSLONGDOUBLE   WSTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED

/********************  NORWICHTERRIOR  ****************************/
#define WSNORWICHTERRIOR_NUMERICS_ID    "norwichterrior"
#define WSNORWICHTERRIOR_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWICHTERRIOR_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWICHTERRIOR_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWICHTERRIOR_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWICHTERRIOR_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWICHTERRIOR_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSNORWICHTERRIOR_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSNORWICHTERRIOR_CLONGDOUBLE    WSTK_LITTLEENDIAN_128BIT_DOUBLE
#define WSNORWICHTERRIOR_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWICHTERRIOR_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWICHTERRIOR_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWICHTERRIOR_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWICHTERRIOR_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSNORWICHTERRIOR_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSNORWICHTERRIOR_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSNORWICHTERRIOR_WSLONGDOUBLE   WSTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  SAINTBERNARD  ****************************/
#define WSSAINTBERNARD_NUMERICS_ID    "saintbernarnd"
#define WSSAINTBERNARD_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAINTBERNARD_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAINTBERNARD_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAINTBERNARD_CINT64         WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSSAINTBERNARD_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAINTBERNARD_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSSAINTBERNARD_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSSAINTBERNARD_CLONGDOUBLE    WSTK_BIGENDIAN_128BIT_DOUBLE
#define WSSAINTBERNARD_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAINTBERNARD_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAINTBERNARD_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAINTBERNARD_WSINT64        WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSSAINTBERNARD_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAINTBERNARD_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSSAINTBERNARD_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSSAINTBERNARD_WSLONGDOUBLE   WSTK_BIGENDIAN_128BIT_DOUBLE

/********************  BERNESEMOUNTAINDOG  ****************************/
#define WSBERNESEMOUNTAINDOG_NUMERICS_ID    "bernesemountaindog"
#define WSBERNESEMOUNTAINDOG_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBERNESEMOUNTAINDOG_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBERNESEMOUNTAINDOG_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBERNESEMOUNTAINDOG_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBERNESEMOUNTAINDOG_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBERNESEMOUNTAINDOG_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBERNESEMOUNTAINDOG_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBERNESEMOUNTAINDOG_CLONGDOUBLE    WSTK_BIGENDIAN_128BIT_DOUBLE
#define WSBERNESEMOUNTAINDOG_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBERNESEMOUNTAINDOG_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBERNESEMOUNTAINDOG_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBERNESEMOUNTAINDOG_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBERNESEMOUNTAINDOG_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBERNESEMOUNTAINDOG_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBERNESEMOUNTAINDOG_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBERNESEMOUNTAINDOG_WSLONGDOUBLE   WSTK_BIGENDIAN_128BIT_DOUBLE

/********************  SETTER  ****************************/
#define WSSETTER_NUMERICS_ID    "setter"
#define WSSETTER_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSETTER_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSETTER_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSETTER_CINT64         WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSSETTER_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSETTER_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSSETTER_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSSETTER_CLONGDOUBLE    WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSSETTER_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSETTER_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSETTER_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSETTER_WSINT64        WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSSETTER_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSETTER_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSSETTER_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSSETTER_WSLONGDOUBLE   WSTK_INTEL_80BIT_EXTENDED

/********************  FRENCH_BULLDOG  ****************************/
#define WSFRENCH_BULLDOG_NUMERICS_ID    "french_bulldog"
#define WSFRENCH_BULLDOG_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSFRENCH_BULLDOG_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSFRENCH_BULLDOG_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSFRENCH_BULLDOG_CINT64         WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSFRENCH_BULLDOG_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSFRENCH_BULLDOG_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSFRENCH_BULLDOG_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSFRENCH_BULLDOG_CLONGDOUBLE    WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSFRENCH_BULLDOG_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSFRENCH_BULLDOG_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSFRENCH_BULLDOG_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSFRENCH_BULLDOG_WSINT64        WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSFRENCH_BULLDOG_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSFRENCH_BULLDOG_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSFRENCH_BULLDOG_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSFRENCH_BULLDOG_WSLONGDOUBLE   WSTK_LITTLEENDIAN_IEEE754_DOUBLE

/********************  BICHON_FRISE  ****************************/
#define WSBICHON_FRISE_NUMERICS_ID    "bichon_frise"
#define WSBICHON_FRISE_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBICHON_FRISE_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBICHON_FRISE_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBICHON_FRISE_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBICHON_FRISE_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBICHON_FRISE_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBICHON_FRISE_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBICHON_FRISE_CLONGDOUBLE    WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBICHON_FRISE_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBICHON_FRISE_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBICHON_FRISE_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBICHON_FRISE_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBICHON_FRISE_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBICHON_FRISE_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBICHON_FRISE_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBICHON_FRISE_WSLONGDOUBLE   WSTK_LITTLEENDIAN_IEEE754_DOUBLE

/********************  HELEN  ****************************/
#define WSHELEN_NUMERICS_ID    "helen"
#define WSHELEN_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSHELEN_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSHELEN_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSHELEN_CINT64         WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSHELEN_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSHELEN_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSHELEN_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSHELEN_CLONGDOUBLE    WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSHELEN_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSHELEN_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSHELEN_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSHELEN_WSINT64        WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSHELEN_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSHELEN_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSHELEN_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSHELEN_WSLONGDOUBLE   WSTK_LITTLEENDIAN_IEEE754_DOUBLE

/********************  BEAGLE  ****************************/
#define WSBEAGLE_NUMERICS_ID    "beagle"
#define WSBEAGLE_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBEAGLE_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBEAGLE_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBEAGLE_CINT64         WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSBEAGLE_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBEAGLE_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBEAGLE_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBEAGLE_CLONGDOUBLE    WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBEAGLE_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBEAGLE_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBEAGLE_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBEAGLE_WSINT64        WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSBEAGLE_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBEAGLE_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBEAGLE_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBEAGLE_WSLONGDOUBLE   WSTK_BIGENDIAN_IEEE754_DOUBLE

/********************  BULLTERRIER  ****************************/
#define WSBULLTERRIER_NUMERICS_ID    "bullterrier"
#define WSBULLTERRIER_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBULLTERRIER_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBULLTERRIER_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBULLTERRIER_CINT64         WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSBULLTERRIER_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBULLTERRIER_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBULLTERRIER_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBULLTERRIER_CLONGDOUBLE    WSTK_BIGENDIAN_128BIT_DOUBLE
#define WSBULLTERRIER_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBULLTERRIER_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBULLTERRIER_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBULLTERRIER_WSINT64        WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSBULLTERRIER_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBULLTERRIER_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBULLTERRIER_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBULLTERRIER_WSLONGDOUBLE   WSTK_BIGENDIAN_128BIT_DOUBLE

/********************  BORDERTERRIER  ****************************/
#define WSBORDERTERRIER_NUMERICS_ID    "borderterrier"
#define WSBORDERTERRIER_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORDERTERRIER_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORDERTERRIER_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORDERTERRIER_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORDERTERRIER_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORDERTERRIER_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBORDERTERRIER_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBORDERTERRIER_CLONGDOUBLE    WSTK_BIGENDIAN_128BIT_DOUBLE
#define WSBORDERTERRIER_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORDERTERRIER_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORDERTERRIER_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORDERTERRIER_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORDERTERRIER_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSBORDERTERRIER_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSBORDERTERRIER_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSBORDERTERRIER_WSLONGDOUBLE   WSTK_BIGENDIAN_128BIT_DOUBLE

/********************  BASENJI  ****************************/
#define WSBASENJI_NUMERICS_ID    "basenji"
#define WSBASENJI_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBASENJI_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBASENJI_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBASENJI_CINT64         WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSBASENJI_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBASENJI_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBASENJI_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBASENJI_CLONGDOUBLE    WSTK_LITTLEENDIAN_128BIT_DOUBLE
#define WSBASENJI_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBASENJI_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBASENJI_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBASENJI_WSINT64        WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSBASENJI_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBASENJI_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBASENJI_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBASENJI_WSLONGDOUBLE   WSTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  SHARPEI  ****************************/
#define WSSHARPEI_NUMERICS_ID    "sharpei"
#define WSSHARPEI_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHARPEI_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHARPEI_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHARPEI_CINT64         WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSSHARPEI_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHARPEI_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSSHARPEI_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSSHARPEI_CLONGDOUBLE    WSTK_LITTLEENDIAN_128BIT_DOUBLE
#define WSSHARPEI_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHARPEI_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHARPEI_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHARPEI_WSINT64        WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSSHARPEI_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHARPEI_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSSHARPEI_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSSHARPEI_WSLONGDOUBLE   WSTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  TIBETANMASTIFF  ****************************/
#define WSTIBETANMASTIFF_NUMERICS_ID    "tibetanmastiff"
#define WSTIBETANMASTIFF_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSTIBETANMASTIFF_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSTIBETANMASTIFF_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSTIBETANMASTIFF_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSTIBETANMASTIFF_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSTIBETANMASTIFF_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSTIBETANMASTIFF_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSTIBETANMASTIFF_CLONGDOUBLE    WSTK_LITTLEENDIAN_128BIT_DOUBLE
#define WSTIBETANMASTIFF_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSTIBETANMASTIFF_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSTIBETANMASTIFF_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSTIBETANMASTIFF_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSTIBETANMASTIFF_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSTIBETANMASTIFF_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSTIBETANMASTIFF_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSTIBETANMASTIFF_WSLONGDOUBLE   WSTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  GREATDANE  ****************************/
#define WSGREATDANE_NUMERICS_ID    "greatdane"
#define WSGREATDANE_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSGREATDANE_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSGREATDANE_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSGREATDANE_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSGREATDANE_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSGREATDANE_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSGREATDANE_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSGREATDANE_CLONGDOUBLE    WSTK_LITTLEENDIAN_128BIT_DOUBLE
#define WSGREATDANE_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSGREATDANE_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSGREATDANE_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSGREATDANE_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSGREATDANE_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSGREATDANE_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSGREATDANE_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSGREATDANE_WSLONGDOUBLE   WSTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  REDDOG  ****************************/
#define WSREDDOG_NUMERICS_ID    "reddog"
#define WSREDDOG_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSREDDOG_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSREDDOG_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSREDDOG_CINT64         WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSREDDOG_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSREDDOG_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSREDDOG_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSREDDOG_CLONGDOUBLE    WSTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED
#define WSREDDOG_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSREDDOG_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSREDDOG_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSREDDOG_WSINT64        WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSREDDOG_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSREDDOG_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSREDDOG_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSREDDOG_WSLONGDOUBLE   WSTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED

/********************  AUSTRALIANCATTLEDOG  ****************************/
#define WSAUSTRALIANCATTLEDOG_NUMERICS_ID    "australiancattledog"
#define WSAUSTRALIANCATTLEDOG_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAUSTRALIANCATTLEDOG_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAUSTRALIANCATTLEDOG_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAUSTRALIANCATTLEDOG_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAUSTRALIANCATTLEDOG_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAUSTRALIANCATTLEDOG_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSAUSTRALIANCATTLEDOG_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSAUSTRALIANCATTLEDOG_CLONGDOUBLE    WSTK_LITTLEENDIAN_128BIT_DOUBLE
#define WSAUSTRALIANCATTLEDOG_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAUSTRALIANCATTLEDOG_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAUSTRALIANCATTLEDOG_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAUSTRALIANCATTLEDOG_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAUSTRALIANCATTLEDOG_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAUSTRALIANCATTLEDOG_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSAUSTRALIANCATTLEDOG_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSAUSTRALIANCATTLEDOG_WSLONGDOUBLE   WSTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  BOXER  ****************************/
#define WSBOXER_NUMERICS_ID    "boxer"
#define WSBOXER_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOXER_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOXER_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOXER_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOXER_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOXER_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBOXER_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBOXER_CLONGDOUBLE    WSTK_LITTLEENDIAN_128BIT_DOUBLE
#define WSBOXER_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOXER_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOXER_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOXER_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOXER_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOXER_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBOXER_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBOXER_WSLONGDOUBLE   WSTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  AKITAINU  ****************************/
#define WSAKITAINU_NUMERICS_ID    "akitainu"
#define WSAKITAINU_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAKITAINU_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAKITAINU_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAKITAINU_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAKITAINU_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAKITAINU_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSAKITAINU_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSAKITAINU_CLONGDOUBLE    WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSAKITAINU_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAKITAINU_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAKITAINU_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAKITAINU_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAKITAINU_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSAKITAINU_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSAKITAINU_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSAKITAINU_WSLONGDOUBLE   WSTK_LITTLEENDIAN_IEEE754_DOUBLE

/********************  CHIHUAHUA  ****************************/
#define WSCHIHUAHUA_NUMERICS_ID    "chihuahua"
#define WSCHIHUAHUA_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHIHUAHUA_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHIHUAHUA_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHIHUAHUA_CINT64         WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSCHIHUAHUA_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHIHUAHUA_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSCHIHUAHUA_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSCHIHUAHUA_CLONGDOUBLE    WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSCHIHUAHUA_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHIHUAHUA_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHIHUAHUA_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHIHUAHUA_WSINT64        WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSCHIHUAHUA_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHIHUAHUA_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSCHIHUAHUA_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSCHIHUAHUA_WSLONGDOUBLE   WSTK_LITTLEENDIAN_IEEE754_DOUBLE

/********************  ROTTWEILER  ****************************/
#define WSROTTWEILER_NUMERICS_ID    "rottweiler"
#define WSROTTWEILER_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSROTTWEILER_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSROTTWEILER_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSROTTWEILER_CINT64         WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSROTTWEILER_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSROTTWEILER_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSROTTWEILER_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSROTTWEILER_CLONGDOUBLE    WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSROTTWEILER_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSROTTWEILER_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSROTTWEILER_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSROTTWEILER_WSINT64        WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSROTTWEILER_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSROTTWEILER_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSROTTWEILER_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSROTTWEILER_WSLONGDOUBLE   WSTK_BIGENDIAN_IEEE754_DOUBLE

/********************  PHARAOHHOUND  ****************************/
#define WSPHARAOHHOUND_NUMERICS_ID    "pharaohhound"
#define WSPHARAOHHOUND_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPHARAOHHOUND_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPHARAOHHOUND_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPHARAOHHOUND_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPHARAOHHOUND_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPHARAOHHOUND_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSPHARAOHHOUND_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSPHARAOHHOUND_CLONGDOUBLE    WSTK_BIGENDIAN_128BIT_DOUBLE
#define WSPHARAOHHOUND_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPHARAOHHOUND_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPHARAOHHOUND_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPHARAOHHOUND_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPHARAOHHOUND_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPHARAOHHOUND_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSPHARAOHHOUND_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSPHARAOHHOUND_WSLONGDOUBLE   WSTK_BIGENDIAN_128BIT_DOUBLE

/********************  TROUT  ****************************/
#define WSTROUT_NUMERICS_ID    "trout"
#define WSTROUT_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSTROUT_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSTROUT_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSTROUT_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSTROUT_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSTROUT_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSTROUT_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSTROUT_CLONGDOUBLE    WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSTROUT_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSTROUT_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSTROUT_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSTROUT_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSTROUT_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSTROUT_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSTROUT_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSTROUT_WSLONGDOUBLE   WSTK_BIGENDIAN_IEEE754_DOUBLE

/********************  PUG  ****************************/
#define WSPUG_NUMERICS_ID    "pug"
#define WSPUG_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPUG_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPUG_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPUG_CINT64         WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSPUG_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPUG_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSPUG_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSPUG_CLONGDOUBLE    WSTK_BIGENDIAN_128BIT_DOUBLE
#define WSPUG_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPUG_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPUG_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPUG_WSINT64        WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSPUG_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPUG_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSPUG_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSPUG_WSLONGDOUBLE   WSTK_BIGENDIAN_128BIT_DOUBLE

/********************  POINTER  ****************************/
#define WSPOINTER_NUMERICS_ID    "pointer"
#define WSPOINTER_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPOINTER_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPOINTER_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPOINTER_CINT64         WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSPOINTER_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPOINTER_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSPOINTER_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSPOINTER_CLONGDOUBLE    WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSPOINTER_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPOINTER_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPOINTER_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPOINTER_WSINT64        WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSPOINTER_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSPOINTER_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSPOINTER_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSPOINTER_WSLONGDOUBLE   WSTK_BIGENDIAN_IEEE754_DOUBLE

/********************  SAMOYED  ****************************/
#define WSSAMOYED_NUMERICS_ID    "samoyed"
#define WSSAMOYED_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAMOYED_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAMOYED_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAMOYED_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAMOYED_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAMOYED_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSSAMOYED_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSSAMOYED_CLONGDOUBLE    WSTK_BIGENDIAN_128BIT_DOUBLE
#define WSSAMOYED_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAMOYED_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAMOYED_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAMOYED_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAMOYED_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSAMOYED_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSSAMOYED_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSSAMOYED_WSLONGDOUBLE   WSTK_BIGENDIAN_128BIT_DOUBLE

/********************  SIBERIANHUSKY  ****************************/
#define WSSIBERIANHUSKY_NUMERICS_ID    "siberianhusky"
#define WSSIBERIANHUSKY_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSIBERIANHUSKY_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSIBERIANHUSKY_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSIBERIANHUSKY_CINT64         WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSSIBERIANHUSKY_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSIBERIANHUSKY_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSSIBERIANHUSKY_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSSIBERIANHUSKY_CLONGDOUBLE    WSTK_BIGENDIAN_128BIT_DOUBLE
#define WSSIBERIANHUSKY_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSIBERIANHUSKY_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSIBERIANHUSKY_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSIBERIANHUSKY_WSINT64        WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSSIBERIANHUSKY_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSSIBERIANHUSKY_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSSIBERIANHUSKY_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSSIBERIANHUSKY_WSLONGDOUBLE   WSTK_BIGENDIAN_128BIT_DOUBLE

/********************  SHIBAINU  ****************************/
#define WSSHIBAINU_NUMERICS_ID    "shibainu"
#define WSSHIBAINU_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHIBAINU_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHIBAINU_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHIBAINU_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHIBAINU_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHIBAINU_CFLOAT         WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSSHIBAINU_CDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSSHIBAINU_CLONGDOUBLE    WSTK_LITTLEENDIAN_128BIT_DOUBLE
#define WSSHIBAINU_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHIBAINU_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHIBAINU_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHIBAINU_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHIBAINU_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSSHIBAINU_WSFLOAT        WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSSHIBAINU_WSDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSSHIBAINU_WSLONGDOUBLE   WSTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  NEWFOUNDLAND  ****************************/
#define WSNEWFOUNDLAND_NUMERICS_ID    "newfoundland"
#define WSNEWFOUNDLAND_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSNEWFOUNDLAND_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSNEWFOUNDLAND_CLONG          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSNEWFOUNDLAND_CINT64         WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSNEWFOUNDLAND_CSIZE_T        WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSNEWFOUNDLAND_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSNEWFOUNDLAND_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSNEWFOUNDLAND_CLONGDOUBLE    WSTK_BIGENDIAN_128BIT_DOUBLE
#define WSNEWFOUNDLAND_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSNEWFOUNDLAND_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSNEWFOUNDLAND_WSLONG         WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSNEWFOUNDLAND_WSINT64        WSTK_64BIT_BIGENDIAN_STRUCTURE
#define WSNEWFOUNDLAND_WSSIZE_T       WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSNEWFOUNDLAND_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSNEWFOUNDLAND_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSNEWFOUNDLAND_WSLONGDOUBLE   WSTK_BIGENDIAN_128BIT_DOUBLE

/********************  AFFENPINSCHER  ****************************/
#define WSAFFENPINSCHER_NUMERICS_ID    "affenpinscher"
#define WSAFFENPINSCHER_CSHORT         WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSAFFENPINSCHER_CINT           WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSAFFENPINSCHER_CLONG          WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSAFFENPINSCHER_CINT64         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSAFFENPINSCHER_CSIZE_T        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSAFFENPINSCHER_CFLOAT         WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSAFFENPINSCHER_CDOUBLE        WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSAFFENPINSCHER_CLONGDOUBLE    WSTK_BIGENDIAN_128BIT_DOUBLE
#define WSAFFENPINSCHER_WSSHORT        WSTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSAFFENPINSCHER_WSINT          WSTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSAFFENPINSCHER_WSLONG         WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSAFFENPINSCHER_WSINT64        WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSAFFENPINSCHER_WSSIZE_T       WSTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define WSAFFENPINSCHER_WSFLOAT        WSTK_BIGENDIAN_IEEE754_SINGLE
#define WSAFFENPINSCHER_WSDOUBLE       WSTK_BIGENDIAN_IEEE754_DOUBLE
#define WSAFFENPINSCHER_WSLONGDOUBLE   WSTK_BIGENDIAN_128BIT_DOUBLE

/********************  BEAUCERON  ****************************/
#define WSBEAUCERON_NUMERICS_ID        "beauceron"
#define WSBEAUCERON_CSHORT             WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBEAUCERON_CINT               WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBEAUCERON_CLONG              WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBEAUCERON_CINT64             WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBEAUCERON_CSIZE_T            WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBEAUCERON_CFLOAT             WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBEAUCERON_CDOUBLE            WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBEAUCERON_CLONGDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBEAUCERON_WSSHORT            WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBEAUCERON_WSINT              WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBEAUCERON_WSLONG             WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBEAUCERON_WSINT64            WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBEAUCERON_WSSIZE_T           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBEAUCERON_WSFLOAT            WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBEAUCERON_WSDOUBLE           WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBEAUCERON_WSLONGDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE


/********************  BERGAMASCO  ****************************/
#define WSBERGAMASCO_NUMERICS_ID       "bergamasco"
#define WSBERGAMASCO_CSHORT             WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBERGAMASCO_CINT               WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBERGAMASCO_CLONG              WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBERGAMASCO_CINT64             WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBERGAMASCO_CSIZE_T            WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBERGAMASCO_CFLOAT             WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBERGAMASCO_CDOUBLE            WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBERGAMASCO_CLONGDOUBLE        WSTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED
#define WSBERGAMASCO_WSSHORT            WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBERGAMASCO_WSINT              WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBERGAMASCO_WSLONG             WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBERGAMASCO_WSINT64            WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBERGAMASCO_WSSIZE_T           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBERGAMASCO_WSFLOAT            WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBERGAMASCO_WSDOUBLE           WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBERGAMASCO_WSLONGDOUBLE       WSTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED


/********************  BOERBOEL  ****************************/
#define WSBOERBOEL_NUMERICS_ID       "boerboel"
#define WSBOERBOEL_CSHORT             WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOERBOEL_CINT               WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOERBOEL_CLONG              WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOERBOEL_CINT64             WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOERBOEL_CSIZE_T            WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOERBOEL_CFLOAT             WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBOERBOEL_CDOUBLE            WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBOERBOEL_CLONGDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBOERBOEL_WSSHORT            WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOERBOEL_WSINT              WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOERBOEL_WSLONG             WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOERBOEL_WSINT64            WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOERBOEL_WSSIZE_T           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSBOERBOEL_WSFLOAT            WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSBOERBOEL_WSDOUBLE           WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSBOERBOEL_WSLONGDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE


/********************  CHINOOK  ****************************/
#define WSCHINOOK_NUMERICS_ID       "chinook"
#define WSCHINOOK_CSHORT             WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHINOOK_CINT               WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHINOOK_CLONG              WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHINOOK_CINT64             WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHINOOK_CSIZE_T            WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHINOOK_CFLOAT             WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSCHINOOK_CDOUBLE            WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSCHINOOK_CLONGDOUBLE        WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSCHINOOK_WSSHORT            WSTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHINOOK_WSINT              WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHINOOK_WSLONG             WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHINOOK_WSINT64            WSTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHINOOK_WSSIZE_T           WSTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define WSCHINOOK_WSFLOAT            WSTK_LITTLEENDIAN_IEEE754_SINGLE
#define WSCHINOOK_WSDOUBLE           WSTK_LITTLEENDIAN_IEEE754_DOUBLE
#define WSCHINOOK_WSLONGDOUBLE       WSTK_LITTLEENDIAN_IEEE754_DOUBLE



/********************  OLD_WIN_ENV  ****************************/
#define WSOLD_WIN_ENV_NUMERICS_ID    "Sep 13 1996, 13:46:34"
#define WSOLD_WIN_ENV_CSHORT         WSTK_CSHORT_P
#define WSOLD_WIN_ENV_CINT           WSTK_CINT_P
#define WSOLD_WIN_ENV_CLONG          WSTK_CLONG_P
#define WSOLD_WIN_ENV_CINT64         WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSOLD_WIN_ENV_CSIZE_T        WSTK_CLONG_P
#define WSOLD_WIN_ENV_CFLOAT         WSTK_CFLOAT_P
#define WSOLD_WIN_ENV_CDOUBLE        WSTK_CDOUBLE_P
#define WSOLD_WIN_ENV_CLONGDOUBLE    WSTK_CLONGDOUBLE_P
#define WSOLD_WIN_ENV_WSSHORT        WSTK_CSHORT_P
#define WSOLD_WIN_ENV_WSINT          WSTK_CINT_P
#define WSOLD_WIN_ENV_WSLONG         WSTK_CLONG_P
#define WSOLD_WIN_ENV_WSINT64        WSTK_64BIT_LITTLEENDIAN_STRUCTURE
#define WSOLD_WIN_ENV_WSSIZE_T       WSTK_CLONG_P
#define WSOLD_WIN_ENV_WSFLOAT        WSTK_CFLOAT_P
#define WSOLD_WIN_ENV_WSDOUBLE       WSTK_CDOUBLE_P
#define WSOLD_WIN_ENV_WSLONGDOUBLE   WSTK_CLONGDOUBLE_P


#define WSTK_CUCHAR  WSTK_8BIT_UNSIGNED_INTEGER
#define WSTK_WSUCHAR WSTK_8BIT_UNSIGNED_INTEGER

#if UNIX_MATHLINK /* hueristic that works for now */
	typedef unsigned int _uint32_nt;
	typedef signed int _sint32_nt;
#else
	typedef unsigned long _uint32_nt;
	typedef signed long _sint32_nt;
#endif



#if (WIN32_MATHLINK || WIN64_MATHLINK)
#if WIN32_MATHLINK
#define WSTP_NUMERICS_ENVIRONMENT_ID  WSBOERBOEL_NUMERICS_ID

#define WSTK_CSHORT        WSBOERBOEL_CSHORT
#define WSTK_CINT          WSBOERBOEL_CINT
#define WSTK_CLONG         WSBOERBOEL_CLONG
#define WSTK_CINT64        WSBOERBOEL_CINT64
#define WSTK_CSIZE_T       WSBOERBOEL_CSIZE_T
#define WSTK_CFLOAT        WSBOERBOEL_CFLOAT
#define WSTK_CDOUBLE       WSBOERBOEL_CDOUBLE
#define WSTK_CLONGDOUBLE   WSBOERBOEL_CLONGDOUBLE

#define WSTK_WSSHORT       WSBOERBOEL_WSSHORT
#define WSTK_WSINT         WSBOERBOEL_WSINT
#define WSTK_WSLONG        WSBOERBOEL_WSLONG
#define WSTK_WSINT64       WSBOERBOEL_WSINT64
#define WSTK_WSSIZE_T      WSBOERBOEL_WSSIZE_T
#define WSTK_WSFLOAT       WSBOERBOEL_WSFLOAT
#define WSTK_WSDOUBLE      WSBOERBOEL_WSDOUBLE
#define WSTK_WSLONGDOUBLE  WSBOERBOEL_WSLONGDOUBLE
#elif WIN64_MATHLINK
#define WSTP_NUMERICS_ENVIRONMENT_ID  WSBICHON_FRISE_NUMERICS_ID

#define WSTK_CSHORT        WSBICHON_FRISE_CSHORT
#define WSTK_CINT          WSBICHON_FRISE_CINT
#define WSTK_CLONG         WSBICHON_FRISE_CLONG
#define WSTK_CINT64        WSBICHON_FRISE_CINT64
#define WSTK_CSIZE_T       WSBICHON_FRISE_CSIZE_T
#define WSTK_CFLOAT        WSBICHON_FRISE_CFLOAT
#define WSTK_CDOUBLE       WSBICHON_FRISE_CDOUBLE
#define WSTK_CLONGDOUBLE   WSBICHON_FRISE_CLONGDOUBLE

#define WSTK_WSSHORT       WSBICHON_FRISE_WSSHORT
#define WSTK_WSINT         WSBICHON_FRISE_WSINT
#define WSTK_WSLONG        WSBICHON_FRISE_WSLONG
#define WSTK_WSINT64       WSBICHON_FRISE_WSINT64
#define WSTK_WSSIZE_T      WSBICHON_FRISE_WSSIZE_T
#define WSTK_WSFLOAT       WSBICHON_FRISE_WSFLOAT
#define WSTK_WSDOUBLE      WSBICHON_FRISE_WSDOUBLE
#define WSTK_WSLONGDOUBLE  WSBICHON_FRISE_WSLONGDOUBLE
#endif /* WIN32_MATHLINK || WIN64_MATHLINK */

#elif DARWIN_MATHLINK
#if X86_DARWIN_MATHLINK
#define WSTP_NUMERICS_ENVIRONMENT_ID WSBEAUCERON_NUMERICS_ID

#define WSTK_CSHORT        WSBEAUCERON_CSHORT
#define WSTK_CINT          WSBEAUCERON_CINT
#define WSTK_CLONG         WSBEAUCERON_CLONG
#define WSTK_CINT64        WSBEAUCERON_CINT64
#define WSTK_CSIZE_T       WSBEAUCERON_CSIZE_T
#define WSTK_CFLOAT        WSBEAUCERON_CFLOAT
#define WSTK_CDOUBLE       WSBEAUCERON_CDOUBLE
#define WSTK_CLONGDOUBLE   WSBEAUCERON_CLONGDOUBLE

#define WSTK_WSSHORT       WSBEAUCERON_WSSHORT
#define WSTK_WSINT         WSBEAUCERON_WSINT
#define WSTK_WSLONG        WSBEAUCERON_WSLONG
#define WSTK_WSINT64       WSBEAUCERON_WSINT64
#define WSTK_WSSIZE_T      WSBEAUCERON_WSSIZE_T
#define WSTK_WSFLOAT       WSBEAUCERON_WSFLOAT
#define WSTK_WSDOUBLE      WSBEAUCERON_WSDOUBLE
#define WSTK_WSLONGDOUBLE  WSBEAUCERON_WSLONGDOUBLE
#elif X86_64_DARWIN_MATHLINK
#define WSTP_NUMERICS_ENVIRONMENT_ID  WSGREATDANE_NUMERICS_ID

#define WSTK_CSHORT        WSGREATDANE_CSHORT
#define WSTK_CINT          WSGREATDANE_CINT
#define WSTK_CLONG         WSGREATDANE_CLONG
#define WSTK_CINT64        WSGREATDANE_CINT64
#define WSTK_CSIZE_T       WSGREATDANE_CSIZE_T
#define WSTK_CFLOAT        WSGREATDANE_CFLOAT
#define WSTK_CDOUBLE       WSGREATDANE_CDOUBLE
#define WSTK_CLONGDOUBLE   WSGREATDANE_CLONGDOUBLE

#define WSTK_WSSHORT       WSGREATDANE_WSSHORT
#define WSTK_WSINT         WSGREATDANE_WSINT
#define WSTK_WSLONG        WSGREATDANE_WSLONG
#define WSTK_WSINT64       WSGREATDANE_WSINT64
#define WSTK_WSSIZE_T      WSGREATDANE_WSSIZE_T
#define WSTK_WSFLOAT       WSGREATDANE_WSFLOAT
#define WSTK_WSDOUBLE      WSGREATDANE_WSDOUBLE
#define WSTK_WSLONGDOUBLE  WSGREATDANE_WSLONGDOUBLE

#elif ARM_DARWIN_MATHLINK
#define WSTP_NUMERICS_ENVIRONMENT_ID WSSHARPEI_NUMERICS_ID

#define WSTK_CSHORT        WSSHARPEI_CSHORT
#define WSTK_CINT          WSSHARPEI_CINT
#define WSTK_CLONG         WSSHARPEI_CLONG
#define WSTK_CINT64        WSSHARPEI_CINT64
#define WSTK_CSIZE_T       WSSHARPEI_CSIZE_T
#define WSTK_CFLOAT        WSSHARPEI_CFLOAT
#define WSTK_CDOUBLE       WSSHARPEI_CDOUBLE
#define WSTK_CLONGDOUBLE   WSSHARPEI_CLONGDOUBLE

#define WSTK_WSSHORT       WSSHARPEI_WSSHORT
#define WSTK_WSINT         WSSHARPEI_WSINT
#define WSTK_WSLONG        WSSHARPEI_WSLONG
#define WSTK_WSINT64       WSSHARPEI_WSINT64
#define WSTK_WSSIZE_T      WSSHARPEI_WSSIZE_T
#define WSTK_WSFLOAT       WSSHARPEI_WSFLOAT
#define WSTK_WSDOUBLE      WSSHARPEI_WSDOUBLE
#define WSTK_WSLONGDOUBLE  WSSHARPEI_WSLONGDOUBLE
#elif ARM64_DARWIN_MATHLINK
#define WSTP_NUMERICS_ENVIRONMENT_ID WSTIBETANMASTIFF_NUMERICS_ID

#define WSTK_CSHORT        WSTIBETANMASTIFF_CSHORT
#define WSTK_CINT          WSTIBETANMASTIFF_CINT
#define WSTK_CLONG         WSTIBETANMASTIFF_CLONG
#define WSTK_CINT64        WSTIBETANMASTIFF_CINT64
#define WSTK_CSIZE_T       WSTIBETANMASTIFF_CSIZE_T
#define WSTK_CFLOAT        WSTIBETANMASTIFF_CFLOAT
#define WSTK_CDOUBLE       WSTIBETANMASTIFF_CDOUBLE
#define WSTK_CLONGDOUBLE   WSTIBETANMASTIFF_CLONGDOUBLE

#define WSTK_WSSHORT       WSTIBETANMASTIFF_WSSHORT
#define WSTK_WSINT         WSTIBETANMASTIFF_WSINT
#define WSTK_WSLONG        WSTIBETANMASTIFF_WSLONG
#define WSTK_WSINT64       WSTIBETANMASTIFF_WSINT64
#define WSTK_WSSIZE_T      WSTIBETANMASTIFF_WSSIZE_T
#define WSTK_WSFLOAT       WSTIBETANMASTIFF_WSFLOAT
#define WSTK_WSDOUBLE      WSTIBETANMASTIFF_WSDOUBLE
#define WSTK_WSLONGDOUBLE  WSTIBETANMASTIFF_WSLONGDOUBLE
#endif

#elif I86_LINUX_MATHLINK
#define WSTP_NUMERICS_ENVIRONMENT_ID  WSBERGAMASCO_NUMERICS_ID

#define WSTK_CSHORT        WSBERGAMASCO_CSHORT
#define WSTK_CINT          WSBERGAMASCO_CINT
#define WSTK_CLONG         WSBERGAMASCO_CLONG
#define WSTK_CINT64        WSBERGAMASCO_CINT64
#define WSTK_CSIZE_T       WSBERGAMASCO_CSIZE_T
#define WSTK_CFLOAT        WSBERGAMASCO_CFLOAT
#define WSTK_CDOUBLE       WSBERGAMASCO_CDOUBLE
#define WSTK_CLONGDOUBLE   WSBERGAMASCO_CLONGDOUBLE

#define WSTK_WSSHORT       WSBERGAMASCO_WSSHORT
#define WSTK_WSINT         WSBERGAMASCO_WSINT
#define WSTK_WSLONG        WSBERGAMASCO_WSLONG
#define WSTK_WSINT64       WSBERGAMASCO_WSINT64
#define WSTK_WSSIZE_T      WSBERGAMASCO_WSSIZE_T
#define WSTK_WSFLOAT       WSBERGAMASCO_WSFLOAT
#define WSTK_WSDOUBLE      WSBERGAMASCO_WSDOUBLE
#define WSTK_WSLONGDOUBLE  WSBERGAMASCO_WSLONGDOUBLE

#elif X86_64_LINUX_MATHLINK
#define WSTP_NUMERICS_ENVIRONMENT_ID  WSBOXER_NUMERICS_ID

#define WSTK_CSHORT        WSBOXER_CSHORT
#define WSTK_CINT          WSBOXER_CINT
#define WSTK_CLONG         WSBOXER_CLONG
#define WSTK_CINT64        WSBOXER_CINT64
#define WSTK_CSIZE_T       WSBOXER_CSIZE_T
#define WSTK_CFLOAT        WSBOXER_CFLOAT
#define WSTK_CDOUBLE       WSBOXER_CDOUBLE
#define WSTK_CLONGDOUBLE   WSBOXER_CLONGDOUBLE

#define WSTK_WSSHORT       WSBOXER_WSSHORT
#define WSTK_WSINT         WSBOXER_WSINT
#define WSTK_WSLONG        WSBOXER_WSLONG
#define WSTK_WSINT64       WSBOXER_WSINT64
#define WSTK_WSSIZE_T      WSBOXER_WSSIZE_T
#define WSTK_WSFLOAT       WSBOXER_WSFLOAT
#define WSTK_WSDOUBLE      WSBOXER_WSDOUBLE
#define WSTK_WSLONGDOUBLE  WSBOXER_WSLONGDOUBLE

#elif ARM_LINUX_MATHLINK
#define WSTP_NUMERICS_ENVIRONMENT_ID  WSCHINOOK_NUMERICS_ID

#define WSTK_CSHORT        WSCHINOOK_CSHORT
#define WSTK_CINT          WSCHINOOK_CINT
#define WSTK_CLONG         WSCHINOOK_CLONG
#define WSTK_CINT64        WSCHINOOK_CINT64
#define WSTK_CSIZE_T       WSCHINOOK_CSIZE_T
#define WSTK_CFLOAT        WSCHINOOK_CFLOAT
#define WSTK_CDOUBLE       WSCHINOOK_CDOUBLE
#define WSTK_CLONGDOUBLE   WSCHINOOK_CLONGDOUBLE

#define WSTK_WSSHORT       WSCHINOOK_WSSHORT
#define WSTK_WSINT         WSCHINOOK_WSINT
#define WSTK_WSLONG        WSCHINOOK_WSLONG
#define WSTK_WSINT64       WSCHINOOK_WSINT64
#define WSTK_WSSIZE_T      WSCHINOOK_WSSIZE_T
#define WSTK_WSFLOAT       WSCHINOOK_WSFLOAT
#define WSTK_WSDOUBLE      WSCHINOOK_WSDOUBLE
#define WSTK_WSLONGDOUBLE  WSCHINOOK_WSLONGDOUBLE

#else
#define WSTP_NUMERICS_ENVIRONMENT_ID  WSOLD_WIN_ENV_NUMERICS_ID

#define WSTK_CSHORT        WSOLD_WIN_ENV_CSHORT
#define WSTK_CINT          WSOLD_WIN_ENV_CINT
#define WSTK_CLONG         WSOLD_WIN_ENV_CLONG
#define WSTK_CINT64        WSOLD_WIN_ENV_CINT64
#define WSTK_CSIZE_T       WSOLD_WIN_ENV_CSIZE_T
#define WSTK_CFLOAT        WSOLD_WIN_ENV_CFLOAT
#define WSTK_CDOUBLE       WSOLD_WIN_ENV_CDOUBLE
#define WSTK_CLONGDOUBLE   WSOLD_WIN_ENV_CLONGDOUBLE

#define WSTK_WSSHORT       WSOLD_WIN_ENV_WSSHORT
#define WSTK_WSINT         WSOLD_WIN_ENV_WSINT
#define WSTK_WSLONG        WSOLD_WIN_ENV_WSLONG
#define WSTK_WSINT64       WSOLD_WIN_ENV_WSINT64
#define WSTK_WSSIZE_T      WSOLD_WIN_ENV_WSSIZE_T
#define WSTK_WSFLOAT       WSOLD_WIN_ENV_WSFLOAT
#define WSTK_WSDOUBLE      WSOLD_WIN_ENV_WSDOUBLE
#define WSTK_WSLONGDOUBLE  WSOLD_WIN_ENV_WSLONGDOUBLE

#endif

/* Objects of these numeric types exist in MathLink only in the numerics
 * environment and, unfortunately, in the "stack frames" of the functions that
 * put atomic numbers like WSPutInteger.  These C types are used by client
 * programs solely for type-checked access to the BinaryNumber functions.
 */
typedef unsigned char uchar_nt;
typedef uchar_nt     FAR * ucharp_nt;
typedef ucharp_nt    FAR * ucharpp_nt;

typedef short              short_nt;
typedef short_nt     FAR * shortp_nt;
typedef shortp_nt    FAR * shortpp_nt;

typedef int                int_nt;
typedef int_nt       FAR * intp_nt;
typedef intp_nt      FAR * intpp_nt;

typedef long               long_nt;
typedef long_nt      FAR * longp_nt;
typedef longp_nt     FAR * longpp_nt;

typedef wsint64            int64_nt;
typedef int64_nt         * int64p_nt;
typedef int64p_nt        * int64pp_nt;

typedef float              float_nt;
typedef float_nt     FAR * floatp_nt;
typedef floatp_nt    FAR * floatpp_nt;

typedef double             double_nt;
typedef double_nt    FAR * doublep_nt;
typedef doublep_nt   FAR * doublepp_nt;

#ifndef CC_SUPPORTS_LONG_DOUBLE
#if defined( __STDC__) || defined(__cplusplus) || ! UNIX_MATHLINK
#define CC_SUPPORTS_LONG_DOUBLE 1
#else

#define CC_SUPPORTS_LONG_DOUBLE MLPROTOTYPES
#endif
#endif

struct _i87extended_nt { unsigned short w[5];};

#if CC_SUPPORTS_LONG_DOUBLE
#ifndef __extended_nt__
#if WINDOWS_MATHLINK && (WSTK_CLONGDOUBLE != WSTK_WSLONGDOUBLE) /* subtle predicate that works for old and new windows numenvs */
#define __extended_nt__ struct _i87extended_nt
#define EXTENDED_NT_TO_I87_EXTENDED(a,b) a = b
#define I87_EXTENDED_TO_EXTENDED_NT(a,b) a = b
#else
#define __extended_nt__ long double
#define EXTENDED_NT_TO_I87_EXTENDED(a,b) \
				{ \
					int i; \
					unsigned short *c = (unsigned short *)&b; \
					for(i = 0; i < 5; i++) a.w[i] = 0; \
					for(i = 1; i < 5; i++) a.w[i] = *(c + i); \
				}
#define I87_EXTENDED_TO_EXTENDED_NT(a,b) \
				{ \
					int i; \
					unsigned short *c = (unsigned short *)&a; \
					a = 0; \
					for(i = 1; i < 5; i++) *(c + i) = b.w[i]; \
				}
#endif
#endif

	typedef __extended_nt__    wsextended_double;

	typedef __extended_nt__    extended_nt;
	typedef extended_nt  FAR * extendedp_nt;
	typedef extendedp_nt FAR * extendedpp_nt;
#endif /* CC_SUPPORTS_LONG_DOUBLE */

#endif /* _WSNTYPES_H */



ML_EXTERN_C

#ifndef _MLSTDDEV_H
#define _MLSTDDEV_H






#ifndef _MLVERS_H
#define _MLVERS_H



#if MLINTERFACE <= 3
#ifndef MLVERSION
#define MLVERSION 4
#endif
#endif

#if MLINTERFACE >= 4
#ifndef MLVERSION
                /* feature greeting version */
#define MLVERSION 6
#endif
#endif

#if !OLD_VERSIONING


/*
 * MathLink adopts a simple versioning strategy that can be adapted to many
 * compile-time and run-time environments.  In particular, it is amenable to
 * the various shared library facilities in use.  (Although certain of these
 * facilities provide more sophisticated mechanisms than are required by the
 * following simple strategy.)
 *
 * MathLink evolves by improving its implementation and by improving its
 * interface.  The values of MLREVISION or MLINTERFACE defined here are
 * incremented whenever an improvement is made and released.
 *
 * MLREVISION is the current revision number. It is incremented every time
 * a change is made to the source and MathLink is rebuilt and distributed
 * on any platform.  (Bug fixes, optimizations, or other improvements
 * transparent to the interface increment only this number.)
 *
 * MLINTERFACE is a name for a documented interface to MathLink.  This
 * number is incremented whenever a named constant or function is added,
 * removed, or its behavior is changed in a way that could break existing
 * correct* client programs.  It is expected that the interface to MathLink
 * is improved over time so that implemenations of higher numbered
 * interfaces are more complete or more convenient to use for writing
 * effective client programs.  In particular, a specific interface provides
 * all the useful functionality of an earlier interface.
 *
 *     *(It is possible that an incorrect MathLink program still works
 *     because it relies on some undocumented detail of a particular
 *     revision.  It may not always be possible to change the interface
 *     number when such a detail changes.  For example, one program may
 *     be relying on a bug in MathLink that a great many other programs
 *     need fixed.  In this case, we would likely choose to potentially
 *     break the incorrect program in order to fix the correct programs
 *     by incrementing the revision number leaving the interface number
 *     unchanged.  It is possible to bind to a particular revision of a
 *     MathLink interface if that is important for some programs.  One
 *     could use a statically linked version of the library, make use of
 *     the search algorithm used by the runtime loader, or dynamically
 *     load the MathLink library manually.)
 *
 *
 * If a distributed MathLink implmentation were labeled with its revision
 * and interface numbers in dotted notation so that, say, ML.1.6 means the
 * sixth revision of interface one, then the following may represent the
 * distribution history of MathLink.
 *
 *     first distribution
 *         ML.1.5   (Perhaps earlier revisions were never
 *                   distributed for this platform.)
 *
 *     second distribution
 *         ML.1.6   (Bug fixes or other improvements were
 *                   made that don't affect the interface.)
 *
 *     third distribution
 *         ML.2.7   (Perhaps some new functions were added.)
 *
 *         ML.1.7   (And improvements were made that don't
 *                   affect the old interface.)
 *
 *     fourth distribution
 *         ML.3.8   (Perhaps the return values of an existing
 *                   function changed.)
 *         ML.2.8   (Revision 8 also adds improvements transparent
 *                   to interface 2.)
 *         ML.1.7   (Clients of interface 1 see no improvements
 *                   in this eighth revision.)
 *
 * Note that the distribution history may not be the same on different
 * platforms.  But revision numbers represent a named body of source code
 * across all platforms.
 *
 * The mechanism for deploying this strategy differs between platforms
 * because of differing platform-specific facilities and conventions.
 * The interface and revision numbers may form part of the filename of
 * the MathLink library, or they may not.  This information is always
 * available in some conventional form so that it is easy and natural for
 * client programs to bind with and use the best available implementation
 * of a particular MathLink interface.  The details are described in the
 * MathLink Developer's Guide for each platform.
 */

#define MLREVISION 42
#define MLMATHVERSION 12.0.0

#ifndef MLCREATIONID
#define MLCREATIONID 114411
#endif

#define MLAPI1REVISION 1   /* the first revision to support interface 1 */
#define MLAPI2REVISION 6   /* the first revision to support interface 2 */
#define MLAPI3REVISION 16  /* the first revision to support interface 3 */
#define MLAPI4REVISION 25  /* the first revision to support interface 4 */


#ifndef MLINTERFACE
#define MLINTERFACE 4
#define MLAPIREVISION MLAPI4REVISION

		/*
		 * Interface 4 adds the following exported functions:
         *
         * MLCreateLinkWithExternalProtocol
         * MLDoNotHandleSignalParameter
         * MLEnableLinkLock
         * MLFilterArgv
         * MLGetAvailableLinkProtocolNames
         * MLGetInteger8
         * MLGetInteger8Array
         * MLGetInteger8ArrayData
         * MLGetInteger8List
         * MLGetLinksFromEnvironment
         * MLGetNumberAsByteString
         * MLGetNumberAsString
         * MLGetNumberAsUCS2String
         * MLGetNumberAsUTF16String
         * MLGetNumberAsUTF32String
         * MLGetNumberAsUTF8String
         * MLHandleSignal
         * MLIsLinkLoopback
         * MLLinkEnvironment
         * MLLogFileNameForLink
         * MLLogStreamToFile
         * MLLowLevelDeviceName
         * MLPutInteger8
         * MLPutInteger8Array
         * MLPutInteger8ArrayData
         * MLPutInteger8List
         * MLPutRealNumberAsUCS2String
         * MLPutRealNumberAsUTF16String
         * MLPutRealNumberAsUTF32String
         * MLPutRealNumberAsUTF8String
         * MLReleaseInteger8Array
         * MLReleaseInteger8List
         * MLReleaseLinkProtocolNames
         * MLReleaseLinksFromEnvironment
         * MLReleaseLogFileNameForLink
         * MLReleaseLowLevelDeviceName
         * MLReleaseParameters
         * MLSetThreadSafeLinksParameter
         * MLStopHandlingSignal
         * MLStopLoggingStream
         * MLValid
         * MLWaitForLinkActivity
         * MLWaitForLinkActivityWithCallback
         *
         * Interface 4 removes the following API functions.
         *
         * MLCreate0
         * MLDestroy
         * MLDoNotHandleSignalParameter0
         * MLFilterArgv0
         * MLGetByteString0
         * MLGetLinkedEnvIDString0
         * MLGetString0
         * MLGetUCS2String0
         * MLGetUTF16String0
         * MLGetUTF32String0
         * MLGetUTF8String0
         * MLGetUnicodeString0
         * MLHandleSignal0
         * MLLinkSelect
         * MLLoopbackOpen0
         * MLMake
         * MLPutRealByteString0
         * MLPutRealUCS2String0
         * MLPutRealUTF16String0
         * MLPutRealUTF32String0
         * MLPutRealUTF8String0
         * MLPutRealUnicodeString0
         * MLSetEnvIDString0
         * MLSetMessageHandler0
         * MLSetSignalHandler0
         * MLSetYieldFunction0
         * MLStopHandlingSignal0
         * MLUnsetSignalHandler0
         * MLValid0
         * MLVersionNumber0
         *
		 */


                /*
                 * Interface 3 adds the following exported functions:
                 *      MLClearAllSymbolReplacements
                 *      MLClearSymbolReplacement
                 *      MLConvertUCS2String
                 *      MLConvertUCS2StringNL
                 *      MLConvertUTF8String
                 *      MLConvertUTF8StringNL
                 *      MLConvertUTF16String
                 *      MLConvertUTF16StringNL
                 *      MLConvertUTF32String
                 *      MLConvertUTF32StringNL
                 *      MLEnvironmentData
                 *      MLGetDomainNameList
                 *      MLGetInteger16
                 *      MLGetInteger16Array
                 *      MLGetInteger16ArrayData
                 *      MLGetInteger16List
                 *      MLGetInteger32
                 *      MLGetInteger32Array
                 *      MLGetInteger32ArrayData
                 *      MLGetInteger32List
                 *      MLGetInteger64
                 *      MLGetInteger64Array
                 *      MLGetInteger64ArrayData
                 *      MLGetInteger64List
                 *      MLGetLinkedEnvIDString
                 *      MLGetMessageHandler
                 *      MLGetNetworkAddressList
                 *      MLGetReal128
                 *      MLGetReal128Array
                 *      MLGetReal128ArrayData
                 *      MLGetReal128List
                 *      MLGetReal32
                 *      MLGetReal32Array
                 *      MLGetReal32ArrayData
                 *      MLGetReal32List
                 *      MLGetReal64
                 *      MLGetReal64Array
                 *      MLGetReal64ArrayData
                 *      MLGetReal64List
                 *      MLGetUCS2Characters
                 *      MLGetUCS2String
                 *      MLGetUCS2Symbol
                 *      MLGetUTF16Characters
                 *      MLGetUTF16String
                 *      MLGetUTF16Symbol
                 *      MLGetUTF32Characters
                 *      MLGetUTF32String
                 *      MLGetUTF32Symbol
                 *      MLGetUTF8Characters
                 *      MLGetUTF8String
                 *      MLGetUTF8Symbol
                 *      MLGetYieldFunction
                 *      MLLinkName
                 *      MLOldConvertUCS2String
                 *      MLOpenArgcArgv
                 *      MLPutInteger16
                 *      MLPutInteger16Array
                 *      MLPutInteger16ArrayData
                 *      MLPutInteger16List
                 *      MLPutInteger32
                 *      MLPutInteger32Array
                 *      MLPutInteger32ArrayData
                 *      MLPutInteger32List
                 *      MLPutInteger64
                 *      MLPutInteger64Array
                 *      MLPutInteger64ArrayData
                 *      MLPutInteger64List
                 *      MLPutMessageWithArg
                 *      MLPutReal128
                 *      MLPutReal128Array
                 *      MLPutReal128ArrayData
                 *      MLPutReal128List
                 *      MLPutReal32
                 *      MLPutReal32Array
                 *      MLPutReal32ArrayData
                 *      MLPutReal32List
                 *      MLPutReal64
                 *      MLPutReal64Array
                 *      MLPutReal64ArrayData
                 *      MLPutReal64List
                 *      MLPutUCS2Characters
                 *      MLPutUCS2String
                 *      MLPutUCS2Symbol
                 *      MLPutUTF16Characters
                 *      MLPutUTF16String
                 *      MLPutUTF16Symbol
                 *      MLPutUTF32Characters
                 *      MLPutUTF32String
                 *      MLPutUTF32Symbol
                 *      MLPutUTF8Characters
                 *      MLPutUTF8String
                 *      MLPutUTF8Symbol
                 *      MLReadyParallel
                 *      MLReleaseBinaryNumberArray
                 *      MLReleaseByteArray
                 *      MLReleaseByteString
                 *      MLReleaseByteSymbol
                 *      MLReleaseDomainNameList
                 *      MLReleaseInteger16Array
                 *      MLReleaseInteger16List
                 *      MLReleaseInteger32Array
                 *      MLReleaseInteger32List
                 *      MLReleaseInteger64Array
                 *      MLReleaseInteger64List
                 *      MLReleaseNetworkAddressList
                 *      MLReleaseReal128Array
                 *      MLReleaseReal128List
                 *      MLReleaseReal32Array
                 *      MLReleaseReal32List
                 *      MLReleaseReal64Array
                 *      MLReleaseReal64List
                 *      MLReleaseString
                 *      MLReleaseSymbol
                 *      MLReleaseUCS2String
                 *      MLReleaseUCS2Symbol
                 *      MLReleaseUTF16String
                 *      MLReleaseUTF16Symbol
                 *      MLReleaseUTF32String
                 *      MLReleaseUTF32Symbol
                 *      MLReleaseUTF8String
                 *      MLReleaseUTF8Symbol
                 *      MLSetEncodingParameter
                 *      MLSetEnvIDString
                 *      MLSetEnvironmentData
                 *      MLSetSignalHandler
                 *      MLSetSignalHandlerFromFunction
                 *      MLSetSymbolReplacement
                 *      MLTestHead
                 *      MLUnsetSignalHandler
                 *      MLVersionNumbers
                 *
                 *      Interface 3 removes all the special MathLink types such as kcharp_ct, long_st, etc.
                 *      The API functions now all take standard C data types.
                 */

       		/*
                 * Interface 2 adds the following exported functions:
                 *      MLGetBinaryNumberArray0
                 *      MLTransfer0
                 *      MLNextCharacter0
                 * And, for WINDOWS_MATHLINK, some constants in "mlntypes.h"
                 * were changed in a way that causes MLGetRawType to return
                 * different values.
                 *
                 */
#else
#if MLINTERFACE == 1
/*\ syntax\ error\ */\ )
#elif MLINTERFACE == 2
/*\ syntax\ error\ */\ )
#elif MLINTERFACE == 3
#define MLAPIREVISION MLAPI3REVISION
#elif MLINTERFACE == 4
#define MLAPIREVISION MLAPI4REVISION
#else
/*\ syntax\ error\ */\ )
#endif
#endif


/* It may be possible for an implementation of one MathLink interface to
 * fully support an earlier interface.  MLNewParameters() may succeed when
 * passed an interface number less than the value of MLAPIREVISION when the
 * library was built.  This would happen, if the newer interface is a proper
 * superset of the older interface, or if the implementation can adjust its
 * behavior at runtime to conform to the older requested interface.
 */

#ifndef MLOLDDEFINITION
#if WINDOWS_MATHLINK
#if MLINTERFACE == 3
#define MLOLDDEFINITION MLAPI2REVISION
#elif MLINTERFACE == 4
#define MLOLDDEFINITION MLAPI3REVISION
#else
/*\ syntax\ error\ */\ )
#endif
#else
#define MLOLDDEFINITION MLAPI1REVISION
#endif
#endif




#else
/*\ syntax\ error\ */\ )
#endif

#endif /* _MLVERS_H */



#if WINDOWS_MATHLINK

#endif


typedef void FAR * dev_world;
typedef MLINK dev_cookie;

typedef dev_world FAR * dev_worldp;
typedef dev_cookie FAR * dev_cookiep;


typedef  MLAllocatorUPP dev_allocator;
#define call_dev_allocator CallMLAllocatorProc
#define new_dev_allocator NewMLAllocatorProc

typedef  MLDeallocatorUPP dev_deallocator;
#define call_dev_deallocator CallMLDeallocatorProc
#define new_dev_deallocator NewMLDeallocatorProc

typedef dev_main_type world_main_type;

#define MLSTDWORLD_INIT        16
#define MLSTDWORLD_DEINIT      17
#define MLSTDWORLD_MAKE        18

#if UNIX_MATHLINK
#define MLSTDWORLD_GET_SIGNAL_HANDLERS      29
#define MLSTDWORLD_RELEASE_SIGNAL_HANDLERS  30
#endif

#define MLSTDWORLD_PROTOCOL        31
#define MLSTDWORLD_MODES           32
#define MLSTDWORLD_STREAMCAPACITY  33
#define MLSTDWORLD_ID              34

#define MLSTDDEV_CONNECT_READY 19
#define MLSTDDEV_CONNECT       20
#define MLSTDDEV_DESTROY       21

#define MLSTDDEV_SET_YIELDER   22
#define MLSTDDEV_GET_YIELDER   23

#define MLSTDDEV_WRITE_MSG     24
#define MLSTDDEV_HAS_MSG       25
#define MLSTDDEV_READ_MSG      26
#define MLSTDDEV_SET_HANDLER   27
#define MLSTDDEV_GET_HANDLER   28

#if 0
#if UNIX_MATHLINK
#define MLSTDDEV_GET_SIGNAL_HANDLERS        29
#define MLSTDDEV_RELEASE_SIGNAL_HANDLERS    30
#endif
#endif


#define T_WORLD_INIT        MLSTDWORLD_INIT
#define T_WORLD_DEINIT      MLSTDWORLD_DEINIT
#define T_WORLD_MAKE        MLSTDWORLD_MAKE
#define T_DEV_CONNECT_READY MLSTDDEV_CONNECT_READY
#define T_DEV_CONNECT       MLSTDDEV_CONNECT
#define T_DEV_DESTROY       MLSTDDEV_DESTROY

#define T_DEV_SET_YIELDER   MLSTDDEV_SET_YIELDER
#define T_DEV_GET_YIELDER   MLSTDDEV_GET_YIELDER

#define T_DEV_WRITE_MSG     MLSTDDEV_WRITE_MSG
#define T_DEV_HAS_MSG       MLSTDDEV_HAS_MSG
#define T_DEV_READ_MSG      MLSTDDEV_READ_MSG
#define T_DEV_SET_HANDLER   MLSTDDEV_SET_HANDLER
#define T_DEV_GET_HANDLER   MLSTDDEV_GET_HANDLER


typedef unsigned long dev_mode;
/* edit here and in mathlink.r */
#define NOMODE           ((dev_mode)0x0000)
#define LOOPBACKBIT      ((dev_mode)0x0001)
#define LISTENBIT        ((dev_mode)0x0002)
#define CONNECTBIT       ((dev_mode)0x0004)
#define LAUNCHBIT        ((dev_mode)0x0008)
#define PARENTCONNECTBIT ((dev_mode)0x0010)
#define READBIT          ((dev_mode)0x0020)
#define WRITEBIT         ((dev_mode)0x0040)
#define SERVERBIT        ((dev_mode)0x0080)
#define ANYMODE          (~(dev_mode)0)

typedef dev_mode FAR * dev_modep;





typedef unsigned long dev_options;

#define _DefaultOptions              ((dev_options)0x00000000)

#define _NetworkVisibleMask          ((dev_options)0x00000003)
#define _BrowseMask                  ((dev_options)0x00000010)
#define _NonBlockingMask             ((dev_options)0x00000020)
#define _InteractMask                ((dev_options)0x00000100)
#define _YieldMask                   ((dev_options)0x00000200)
#define _UseIPV6Mask                 ((dev_options)0x00010000)
#define _UseIPV4Mask                 ((dev_options)0x00020000)
#define _VersionMask                 ((dev_options)0x0F000000)
#define _UseNewTCPIPConnectionMask   ((dev_options)0x00100000)
#define _UseOldTCPIPConnectionMask   ((dev_options)0x00200000)
#define _UseUUIDTCPIPConnectionMask  ((dev_options)0x00000004)
#define _UseAnyNetworkAddressMask    ((dev_options)0x00000008)

#define _NetworkVisible              ((dev_options)0x00000000)
#define _LocallyVisible              ((dev_options)0x00000001)
#define _InternetVisible             ((dev_options)0x00000002)

#define _Browse                      ((dev_options)0x00000000)
#define _DontBrowse                  ((dev_options)0x00000010)

#define _NonBlocking                 ((dev_options)0x00000000)
#define _Blocking                    ((dev_options)0x00000020)

#define _Interact                    ((dev_options)0x00000000)
#define _DontInteract                ((dev_options)0x00000100)

#define _ForceYield                  ((dev_options)0x00000200)
#define _UseIPV6                     ((dev_options)0x00010000)
#define _UseIPV4                     ((dev_options)0x00020000)
#define _UseNewTCPIPConnection       ((dev_options)0x00100000)
#define _UseOldTCPIPConnection       ((dev_options)0x00200000)
#define _UseUUIDTCPIPConnection      ((dev_options)0x00000004)
#define _UseAnyNetworkAddress        ((dev_options)0x00000008)


/* DEVICE selector and WORLD selector masks */
#define INFO_MASK (1UL << 31)
#define INFO_TYPE_MASK ((1UL << 31) - 1UL)
#define INFO_SWITCH_MASK (1UL << 30)
#define MLDEVICE_MASK INFO_MASK
#define WORLD_MASK (INFO_MASK | (1UL << 30))

/* values returned by selector MLDEVICE_TYPE */
#define UNREGISTERED_TYPE  0
#define UNIXPIPE_TYPE      1
#define UNIXSOCKET_TYPE    2
#define LOOPBACK_TYPE      5
#define WINLOCAL_TYPE      9
#define WINFMAP_TYPE       10
#define WINSHM_TYPE        11
#define SOCKET2_TYPE       12
#define GENERIC_TYPE	   13  /* Internal use only, not valid for MLDeviceInformation */
#define UNIXSHM_TYPE       14
#define INTRAPROCESS_TYPE  15

/* selectors */
#define MLDEVICE_TYPE          MLDEVICE_MASK + 0UL                                        /* long */
#define MLDEVICE_NAME          MLDEVICE_MASK + 1UL                                        /* char */
#define MLDEVICE_NAME_SIZE     MLDEVICE_MASK + 2UL                                   /* long */
#define MLDEVICE_WORLD_ID      MLDEVICE_MASK + 5UL                                    /* char */
#define SHM_FD                 MLDEVICE_MASK + (UNIXSHM_TYPE * 256UL + 0UL)      /* int */
#define PIPE_FD                MLDEVICE_MASK + (UNIXPIPE_TYPE * 256UL + 0UL)     /* int */
#define PIPE_CHILD_PID         MLDEVICE_MASK + (UNIXPIPE_TYPE * 256UL + 1UL)     /* int */
#define SOCKET_FD              MLDEVICE_MASK + (UNIXSOCKET_TYPE * 256UL + 0UL)   /* int */
#define INTRA_FD               MLDEVICE_MASK + (INTRAPROCESS_TYPE * 256UL + 0UL) /* int */
#define SOCKET_PARTNER_ADDR    MLDEVICE_MASK + (UNIXSOCKET_TYPE * 256UL + 1UL)   /* unsigned long */
#define SOCKET_PARTNER_PORT    MLDEVICE_MASK + (UNIXSOCKET_TYPE * 256UL + 2UL)   /* unsigned short */
#define LOOPBACK_FD            MLDEVICE_MASK + (LOOPBACK_TYPE * 256UL + 0UL)     /* int */
#define INTRAPROCESS_FD        MLDEVICE_MASK + (INTRAPROCESS_TYPE * 256 + 0)     /* int */

#define	WINDOWS_SET_NOTIFY_WINDOW     MLDEVICE_MASK + 2330UL /* HWND */
#define	WINDOWS_REMOVE_NOTIFY_WINDOW  MLDEVICE_MASK + 2331UL /* HWND */
#define WINDOWS_READY_CONDITION       MLDEVICE_MASK + 2332UL /* HANDLE */

/* info selectors */
#define WORLD_THISLOCATION (1UL + WORLD_MASK)        /* char */
#define WORLD_MODES (2UL + WORLD_MASK)               /* dev_mode */
#define WORLD_PROTONAME (3UL + WORLD_MASK)           /* char */
#define WORLD_STREAMCAPACITY (4UL + WORLD_MASK)      /* long */ /*this belongs in mlolddev.h*/
#define WORLD_ID (5UL + WORLD_MASK)    /* char */


#ifndef MATHLINK_DEVICE_WORLD_ID
#define MATHLINK_DEVICE_WORLD_ID (__DATE__ ", " __TIME__)
#endif


#if MLINTERFACE >= 4
#define MLDEVICE_MODE      MLDEVICE_MASK + 6UL                                    /* long */
#define MLDEVICE_OPTIONS   MLDEVICE_MASK + 7UL                                    /* long */
#endif



#define YIELDVERSION 1

typedef long devyield_result;
typedef long devyield_place;
typedef long devyield_count;
typedef unsigned long devyield_sleep;

#define INTERNAL_YIELDING 0
#define MAKE_YIELDING 1
#define CONNECT_YIELDING 2
#define READ_YIELDING 3
#define WRITE_YIELDING 4
#define DESTROY_YIELDING 5
#define READY_YIELDING 6


typedef struct MLYieldParams FAR * MLYieldParameters;


#define MAX_SLEEP (600)
typedef struct MLYieldData{
	union {long l; double d; void FAR * p;} private_data[8];
} FAR * MLYieldDataPointer;

void MLNewYieldData P(( MLYieldDataPointer ydp   /* , dev_allocator, dev_deallocator */));
void MLFreeYieldData P(( MLYieldDataPointer ydp));
MLYieldParameters MLResetYieldData P(( MLYieldDataPointer ydp, devyield_place func_id));
int   MLSetYieldParameter P(( MLYieldParameters yp, unsigned long selector, void* data, unsigned long* len));
int   MLYieldParameter P(( MLYieldParameters yp, unsigned long selector, void* data, unsigned long* len));
devyield_sleep MLSetSleepYP P(( MLYieldParameters yp, devyield_sleep sleep));
devyield_count MLSetCountYP P(( MLYieldParameters yp, devyield_count count));


enum { MLSleepParameter = 1, MLCountParameter, MLPlaceParameter};





MLYPROC( int, MLYielderProcPtr, (MLINK mlp, MLYieldParameters yp));
typedef	MLYielderProcPtr MLDeviceYielderProcPtr;

typedef MLYielderProcPtr MLYielderUPP, MLDeviceYielderUPP;
#define NewMLYielderProc(userRoutine) (userRoutine)

#define NewMLDeviceYielderProc NewMLYielderProc

typedef  MLYielderUPP MLYieldFunctionType;

typedef MLYielderUPP MLYieldFunctionObject;

typedef  MLYieldFunctionObject dev_yielder;
typedef dev_yielder FAR* dev_yielderp;


typedef unsigned long dev_message;
typedef dev_message FAR * dev_messagep;


MLMPROC( void, MLHandlerProcPtr, (MLINK mlp, int m, int n));
typedef MLHandlerProcPtr MLDeviceHandlerProcPtr;


typedef MLHandlerProcPtr MLHandlerUPP, MLDeviceHandlerUPP;
#define NewMLHandlerProc(userRoutine) (userRoutine)

#define NewMLDeviceHandlerProc NewMLHandlerProc

typedef  MLHandlerUPP MLMessageHandlerType;

typedef MLHandlerUPP MLMessageHandlerObject;


typedef  MLMessageHandlerObject dev_msghandler;
typedef dev_msghandler FAR* dev_msghandlerp;



#endif /* _MLSTDDEV_H */

#ifndef MLINTERFACE
/*\ syntax\ error\ */\ )
#endif


/* explicitly not protected by _MLSTDDEV_H in case MLDECL is redefined for multiple inclusion */

/*bugcheck //should the rest of YP stuff be exported? */
MLDECL( devyield_sleep,         MLSleepYP,               ( MLYieldParameters yp));
MLDECL( devyield_count,         MLCountYP,               ( MLYieldParameters yp));

MLDECL( MLYieldFunctionObject,  MLCreateYieldFunction,   ( MLEnvironment ep, MLYieldFunctionType yf, void* reserved)); /* reserved must be 0 */

#if MLINTERFACE == 3
MLDECL( MLYieldFunctionObject,  MLCreateYieldFunction0,   ( MLEnvironment ep, MLYieldFunctionType yf, void* reserved)); /* reserved must be 0 */
#endif

MLDECL( MLYieldFunctionType,    MLDestroyYieldFunction,  ( MLYieldFunctionObject yfo));

MLDECL( int,        MLCallYieldFunction,     ( MLYieldFunctionObject yfo, MLINK mlp, MLYieldParameters p));

MLDECL( MLMessageHandlerObject, MLCreateMessageHandler,  ( MLEnvironment ep, MLMessageHandlerType mh, void* reserved)); /* reserved must be 0 */

#if MLINTERFACE <= 3
MLDECL( MLMessageHandlerObject, MLCreateMessageHandler0,  ( MLEnvironment ep, MLMessageHandlerType mh, void* reserved)); /* reserved must be 0 */
#endif

MLDECL( MLMessageHandlerType,   MLDestroyMessageHandler, ( MLMessageHandlerObject mho));

MLDECL( void,                   MLCallMessageHandler,    ( MLMessageHandlerObject mho, MLINK mlp, int m, int n));


/* just some type-safe casts */
MLDECL( __MLProcPtr__, MLYielderCast, ( MLYielderProcPtr yp));
MLDECL( __MLProcPtr__, MLHandlerCast, ( MLHandlerProcPtr mh));

ML_END_EXTERN_C






#ifndef MLSIGNAL_H
#define MLSIGNAL_H

MLYPROC( void, MLSigHandlerProcPtr, (int signal));

typedef MLSigHandlerProcPtr MLSignalHandlerType;
typedef void * MLSignalHandlerObject;

#endif /* MLSIGNAL_H */





#ifndef _WSMAKE_H
#define _WSMAKE_H












/* --binding layer-- */
/*************** Starting MathLink ***************/

#define MLPARAMETERSIZE_R1 256
#define MLPARAMETERSIZE 356

typedef char FAR * MLParametersPointer;
typedef char MLParameters[MLPARAMETERSIZE];

#define MLLoopBackOpen MLLoopbackOpen



ML_EXTERN_C
MLUPROC( void, MLUserProcPtr, (MLINK));
ML_END_EXTERN_C

typedef MLUserProcPtr MLUserUPP;
#define NewMLUserProc(userRoutine) (userRoutine)

typedef MLUserUPP MLUserFunctionType;
typedef MLUserFunctionType FAR * MLUserFunctionTypePointer;

typedef MLUserUPP MLUserFunction;


/* The following defines are
 * currently for internal use only.
 */


/* edit here and in mldevice.h and mathlink.r */
#define MLNetworkVisibleMask         ((unsigned long)0x00000003)          /* 00000000000000000000011 */
#define MLBrowseMask                 ((unsigned long)0x00000010)          /* 00000000000000000010000 */
#define MLNonBlockingMask            ((unsigned long)0x00000020)          /* 00000000000000000110000 */
#define MLInteractMask               ((unsigned long)0x00000100)          /* 00000000000000100000000 */
#define MLYieldMask                  ((unsigned long)0x00000200)          /* 00000000000001000000000 */
#define MLUseIPV6Mask                ((unsigned long)0x00010000)          /* 00000010000000000000000 */
#define MLUseIPV4Mask                ((unsigned long)0x00020000)          /* 00000100000000000000000 */
#define MLVersionMask                ((unsigned long)0x0000F000)          /* 00000001111000000000000 */
#define MLUseNewTCPIPConnectionMask  ((unsigned long)0x00100000)          /* 00100000000000000000000 */
#define MLUseOldTCPIPConnectionMask  ((unsigned long)0x00200000)          /* 01000000000000000000000 */
#define MLUseUUIDTCPIPConnectionMask ((unsigned long)0x00000004)          /* 00000000000000000000110 */
#define MLUseAnyNetworkAddressMask   ((unsigned long)0x00000008)          /* 00000000000000000001000 */

                                                                          /* 01100111111001100111111 */

#define MLDefaultOptions             ((unsigned long)0x00000000)
#define MLNetworkVisible             ((unsigned long)0x00000000)
#define MLLocallyVisible             ((unsigned long)0x00000001)
#define MLInternetVisible            ((unsigned long)0x00000002)

#define MLBrowse                     ((unsigned long)0x00000000)
#define MLDontBrowse                 ((unsigned long)0x00000010)

#define MLNonBlocking                ((unsigned long)0x00000000)
#define MLBlocking                   ((unsigned long)0x00000020)

#define MLInteract                   ((unsigned long)0x00000000)
#define MLDontInteract               ((unsigned long)0x00000100)

#define MLForceYield                 ((unsigned long)0x00000200)
#define MLUseIPV6                    ((unsigned long)0x00010000)
#define MLUseIPV4                    ((unsigned long)0x00020000)

#define MLUseNewTCPIPConnection      ((unsigned long)0x00100000)
#define MLUseOldTCPIPConnection      ((unsigned long)0x00200000)
#define MLUseUUIDTCPIPConnection     ((unsigned long)0x00000004)

#define MLUseAnyNetworkAddress       ((unsigned long)0x00000008)

/* Encoding types for use with MLSetEncodingParameter */
#define MLASCII_ENC		1
#define MLBYTES_ENC		2
#define MLUCS2_ENC		3
#define MLOLD_ENC		4
#define MLUTF8_ENC		5
#define MLUTF16_ENC		6
#define MLUTF32_ENC		8

#define MLTOTAL_TEXT_ENCODINGS 8

#if MLINTERFACE >= 4
#define MLLOGERROR              0
#define MLLOGWARNING            1
#define MLLOGNOTICE             2
#define MLLOGINFO               3
#define MLLOGDEBUG              4
#define MLLOGDEBUG1             5
#define MLLOGDEBUG2             6
#define MLLOGDEBUG3             7
#define MLLOGDEBUG4             8
#endif

#endif /* _WSMAKE_H */


/* explicitly not protected by _WSMAKE_H in case MLDECL is redefined for multiple inclusion */


ML_EXTERN_C

#if MLINTERFACE >= 4
MLDECL( MLEnvironmentParameter, MLNewParameters, (unsigned long rev, unsigned long apirev));
MLDECL( void,                   MLReleaseParameters, (MLEnvironmentParameter ep));
MLDECL( void, MLSetAllocParameter, (MLEnvironmentParameter ep, MLAllocator allocator, MLDeallocator deallocator));
MLDECL( long, MLSetThreadSafeLinksParameter, (MLEnvironmentParameter ep));
MLDECL( int,  MLAllocParameter,       (MLEnvironmentParameter ep, MLAllocator* allocator, MLDeallocator* deallocator));
MLDECL( long, MLSetResourceParameter, (MLEnvironmentParameter ep, const char *path));
MLDECL( long, MLSetDeviceParameter,   (MLEnvironmentParameter ep, const char *devspec));
MLDECL( long, MLErrorParameter,       (MLEnvironmentParameter ep));
MLDECL( long, MLSetEncodingParameter, (MLEnvironmentParameter ep, unsigned int etype));
MLDECL( long, MLDoNotHandleSignalParameter,    (MLEnvironmentParameter ep, int signum));
#endif /* MLINTERFACE >= 4 */

#if MLINTERFACE <= 3
MLDECL( unsigned long, MLNewParameters,     ( char* p, unsigned long rev, unsigned long apirev));
MLDECL( void,          MLSetAllocParameter, ( char* p, MLAllocator allocator, MLDeallocator deallocator));
#endif /* MLINTERFACE <= 3 */


#if MLINTERFACE == 3
MLDECL( int,      MLAllocParameter,       (char* p, MLAllocator* allocator, MLDeallocator* deallocator));
MLDECL( long,     MLSetResourceParameter, (char* p, const char *path));
MLDECL( long,     MLSetDeviceParameter,   (char* p, const char *devspec));
MLDECL( long,     MLErrorParameter,       (char* p));
MLDECL( long,     MLSetEncodingParameter, (char *p, unsigned int etype));
MLDECL( long,     MLDoNotHandleSignalParameter0,    (char *p, int signum));
#endif /* MLINTERFACE == 3 */

#if MLINTERFACE >= 4
MLDECL( void,          MLStopHandlingSignal, (MLEnvironment env, int signum));
MLDECL( void,          MLHandleSignal,       (MLEnvironment env, int signum));
#endif /* MLINTERFACE >= 4 */

#if MLINTERFACE == 3
MLDECL( void,          MLStopHandlingSignal0,          ( MLEnvironment env, int signum));
MLDECL( void,          MLHandleSignal0,                ( MLEnvironment env, int signum));
#endif /* MLINTERFACE == 3 */

MLDECL( long,          MLSetEnvironmentData,           ( MLEnvironment env, void *cookie));
MLDECL( void *,        MLEnvironmentData,              ( MLEnvironment env));
MLDECL( int,           MLSetSignalHandler,             ( MLEnvironment env, int signum, void *so));
MLDECL( int,           MLSetSignalHandlerFromFunction, ( MLEnvironment env, int signum, MLSignalHandlerType sigfunc));
MLDECL( int,           MLUnsetSignalHandler,           ( MLEnvironment env, int signum, MLSignalHandlerType sigfunc));

MLDECL( long,          MLSetSymbolReplacement,         ( MLINK mlp, const char *priv, int prlen, const char *pub, int pblen));
MLDECL( int,           MLClearSymbolReplacement,       ( MLINK mlp, long index));
MLDECL( void,          MLClearAllSymbolReplacements,   ( MLINK mlp));

#if MLINTERFACE <= 3
MLDECL( long,          MLSetSignalHandler0, ( MLEnvironment env, int signum, MLSignalHandlerObject so));
MLDECL( long,          MLUnsetSignalHandler0, ( MLEnvironment env, int signum, MLSignalHandlerObject so));
#endif /* MLINTERFACE <= 3 */

#if MLINTERFACE >= 4
MLDECL(MLEnvironment,  MLInitialize,   ( MLEnvironmentParameter ep));
#endif

#if MLINTERFACE <= 3
MLDECL( MLEnvironment, MLInitialize,   ( char* p)); /* pass in NULL */
#endif /* MLINTERFACE <= 3 */

MLDECL( void,          MLDeinitialize, ( MLEnvironment env));

/*************** MathLink Revsion Number/Interface Number ************/
#if MLINTERFACE <= 3
MLDECL( void,          MLVersionNumber0, ( MLEnvironment env, long *inumb, long *rnumb));
#endif /* MLINTERFACE <= 3 */

MLDECL( void,          MLVersionNumbers, ( MLEnvironment env, int *inumb, int *rnumb, int *bnumb));

#if MLINTERFACE >= 4
MLDECL( int,               MLCompilerID, (MLEnvironment env, const char **id));
MLDECL( void,       MLReleaseCompilerID, (MLEnvironment env, const char *id));

MLDECL( int,           MLUCS2CompilerID, (MLEnvironment env, unsigned short **id, int *length));
MLDECL( void,   MLReleaseUCS2CompilerID, (MLEnvironment env, unsigned short *id, int length));

MLDECL( int,           MLUTF8CompilerID, (MLEnvironment env, unsigned char **id, int *length));
MLDECL( void,   MLReleaseUTF8CompilerID, (MLEnvironment env, unsigned char *id, int length));

MLDECL( int,          MLUTF16CompilerID, (MLEnvironment env, unsigned short **id, int *length));
MLDECL( void,  MLReleaseUTF16CompilerID, (MLEnvironment env, unsigned short *id, int length));

MLDECL( int,          MLUTF32CompilerID, (MLEnvironment env, unsigned int **id, int *length));
MLDECL( void,  MLReleaseUTF32CompilerID, (MLEnvironment env, unsigned int *id, int length));
#endif

/********************************************************************/

/* or, if you use MLOpenArgcArgv, ...*/

#if MLINTERFACE >= 4
MLDECL( MLEnvironment, MLBegin, (MLEnvironmentParameter ep));
#endif

#if MLINTERFACE <= 3
MLDECL( MLEnvironment, MLBegin, ( char* p)); /* pass in NULL */
#endif // MLINTERFACE <= 3

MLDECL( void,          MLEnd,   ( MLEnvironment env));

/*************** Environment Identification Interface ***************/

MLDECL( int, MLSetEnvIDString, ( MLEnvironment ep, const char *environment_id)); /* APPIDSERV */
MLDECL( int, MLGetLinkedEnvIDString, (MLINK mlp, const char **environment_id)); /* APPIDSERV */
MLDECL( void, MLReleaseEnvIDString, (MLINK mlp, const char *environment_id));

#if MLINTERFACE <= 3
MLDECL( long, MLSetEnvIDString0, ( MLEnvironment ep, const char *environment_id)); /* APPIDSERV */
MLDECL( long, MLGetLinkedEnvIDString0, ( MLINK mlp, const char *environment_id)); /* APPIDSERV */
#endif /* MLINTERFACE <= 3 */

/*********************************************************************/


/**************** Network Interface List API *************************/
MLDECL( char **,    MLGetNetworkAddressList, ( MLEnvironment ep, unsigned long *size ));
MLDECL( void,   MLReleaseNetworkAddressList, ( MLEnvironment ep, char **addresses, unsigned long size));

#if MLINTERFACE <= 3
/* MLDisownNetworkAddressList is for internal use only. */
MLDECL( void,   MLDisownNetworkAddressList, ( MLEnvironment ep, char **addresses, unsigned long size));
#endif

MLDECL( char **,        MLGetDomainNameList, ( MLEnvironment ep, unsigned long *size ));
MLDECL( void,       MLReleaseDomainNameList, ( MLEnvironment ep, char **dnsnames, unsigned long size));

#if MLINTERFACE <= 3
/* MLDisownDomainNameList is for internal use only */
MLDECL( void,        MLDisownDomainNameList, ( MLEnvironment ep, char **dnsnames, unsigned long size));
#endif

/*********************************************************************/


/************************* Runtime Device Inspection API ***************************/
#if MLINTERFACE >= 4
MLDECL(int, MLGetAvailableLinkProtocolNames, (MLEnvironment ep, char ***protocolNames, int *length));
MLDECL(void,     MLReleaseLinkProtocolNames, (MLEnvironment ep, char **protocolNames, int length));
#endif /* MLINTERFACE >= 4 */
/*********************************************************************/


/************************* Enumerate Open Links in an Env *************/
#if MLINTERFACE >= 4
MLDECL(int,       MLGetLinksFromEnvironment, (MLEnvironment ep, MLINK **links, int *length));
MLDECL(void,  MLReleaseLinksFromEnvironment, (MLEnvironment ep, MLINK *links, int length));
#endif /* MLINTERFACE >= 4 */
/*********************************************************************/



#if MLNTESTPOINTS < 1
#undef MLNTESTPOINTS
#define MLNTESTPOINTS 1
#endif

#if MLINTERFACE <= 3
MLDECL( long, MLTestPoint1, ( MLEnvironment ep, unsigned long selector, void *p1, void *p2, long *np));
#endif /* MLINTERFACE <= 3 */

#if MLNTESTPOINTS < 2
#undef MLNTESTPOINTS
#define MLNTESTPOINTS 2
#endif

#if MLINTERFACE <= 3
MLDECL( void,    MLTestPoint2,     ( MLINK mlp));
#endif

#if MLNTESTPOINTS < 3
#undef MLNTESTPOINTS
#define MLNTESTPOINTS 3
#endif

#if MLINTERFACE <= 3
MLDECL( unsigned long,    MLTestPoint3,     ( MLINK mlp));
#endif /* MLINTERFACE <= 3 */

#if MLNTESTPOINTS < 4
#undef MLNTESTPOINTS
#define MLNTESTPOINTS 4
#endif

#if MLINTERFACE <= 3
MLDECL( unsigned long,    MLTestPoint4,     ( MLINK mlp));
#endif /* MLINTERFACE <= 3 */

#if MLINTERFACE >= 4
MLDECL( long, MLNumericsQuery, ( MLEnvironment ep, unsigned long selector, void *p1, void *p2, long *np));
#else
MLDECL( long, MLNumberControl0, ( MLEnvironment ep, unsigned long selector, void *p1, void *p2, long *np));
#endif


/*************** Connection interface ***************/




#if MLINTERFACE >= 4
MLDECL( int,                            MLValid, ( MLINK mlp));
MLDECL( MLINK, MLCreateLinkWithExternalProtocol, ( MLEnvironment ep, dev_type dev, dev_main_type dev_main, int *errp));
#endif

#if MLINTERFACE <= 3
MLDECL( MLINK,         MLCreate0,       ( MLEnvironment ep, dev_type dev, dev_main_type dev_main, int *errp));
#endif /* MLINTERFACE <= 3 */


#if MLINTERFACE <= 3
MLDECL( MLINK,         MLMake,          ( void* ep, dev_type dev, dev_main_type dev_main, int *errp));

MLDECL( void,          MLDestroy,       ( MLINK mlp, dev_typep devp, dev_main_typep dev_mainp));
MLDECL( int,           MLValid0,        ( MLINK mlp));
#endif /* MLINTERFACE <= 3 */

#if MLINTERFACE <= 3
MLDECL( MLINK,         MLLoopbackOpen0, ( MLEnvironment ep, const char *features, int *errp));
#endif /* MLINTERFACE <= 3 */

#if MLINTERFACE >= 4
MLDECL( char **,       MLFilterArgv,   ( MLEnvironment ep, char **argv, char **argv_end));
#else
MLDECL( char **,       MLFilterArgv0,   ( MLEnvironment ep, char **argv, char **argv_end));
#endif // MLINTERFACE >= 4


MLDECL( long,          MLFeatureString, ( MLINK mlp, char *buf, long buffsize));
MLDECL( MLINK,         MLOpenArgv,      ( MLEnvironment ep, char **argv, char **argv_end, int *errp));
MLDECL( MLINK,         MLOpenArgcArgv,  ( MLEnvironment ep, int argc, char **argv, int *errp));
MLDECL( MLINK,         MLOpenString,    ( MLEnvironment ep, const char *command_line, int *errp));
MLDECL( MLINK,         MLLoopbackOpen,  ( MLEnvironment ep, int *errp));
MLDECL( int,           MLStringToArgv,  ( const char *commandline, char *buf, char **argv, int len));
MLDECL( long,          MLScanString,    ( char **argv, char ***argv_end, char **commandline, char **buf));
MLDECL( long,          MLPrintArgv,     ( char *buf, char **buf_endp, char ***argvp, char **argv_end));

MLDECL( const char *,     MLErrorMessage,  ( MLINK mlp));
MLDECL( const char *,     MLErrorString,   ( MLEnvironment env, long err));

#if MLINTERFACE >= 4
MLDECL( const unsigned short *,  MLUCS2ErrorMessage,  (MLINK mlp, int *length));
MLDECL( const unsigned char *,   MLUTF8ErrorMessage,  (MLINK mlp, int *length));
MLDECL( const unsigned short *,  MLUTF16ErrorMessage, (MLINK mlp, int *length));
MLDECL( const unsigned int *,    MLUTF32ErrorMessage, (MLINK mlp, int *length));

MLDECL(void,  MLReleaseErrorMessage,      (MLINK mlp, const char *message));
MLDECL(void,  MLReleaseUCS2ErrorMessage,  (MLINK mlp, const unsigned short *message, int length));
MLDECL(void,  MLReleaseUTF8ErrorMessage,  (MLINK mlp, const unsigned char *message, int length));
MLDECL(void,  MLReleaseUTF16ErrorMessage, (MLINK mlp, const unsigned short *message, int length));
MLDECL(void,  MLReleaseUTF32ErrorMessage, (MLINK mlp, const unsigned int *message, int length));
#endif

MLDECL( MLINK,         MLOpen,          ( int argc, char **argv));
MLDECL( MLINK,         MLOpenInEnv,     ( MLEnvironment env, int argc, char **argv, int *errp));

#if MLINTERFACE == 3
MLDECL( MLINK,         MLOpenS,         ( const char *command_line));
#endif

MLDECL( MLINK,         MLDuplicateLink,   ( MLINK parentmlp, const char *name, int *errp ));

MLDECL( int,  MLConnect,         ( MLINK mlp));
MLDECL( int,  MLActivate,        ( MLINK mlp));

#ifndef __feature_setp__
#define __feature_setp__
typedef struct feature_set* feature_setp;
#endif
MLDECL( int,  MLEstablish,       ( MLINK mlp, feature_setp features));

MLDECL( int,  MLEstablishString, ( MLINK mlp, const char *features));

MLDECL( void,          MLClose,           ( MLINK mlp));

MLDECL( void,          MLSetUserData,   ( MLINK mlp, void* data, MLUserFunction f));
MLDECL( void*,         MLUserData,      ( MLINK mlp, MLUserFunctionType *fp));
MLDECL( void,          MLSetUserBlock,  ( MLINK mlp, void* userblock));
MLDECL( void*,         MLUserBlock,     ( MLINK mlp));

/* just a type-safe cast */
MLDECL( __MLProcPtr__, MLUserCast, ( MLUserProcPtr f));


#if MLINTERFACE >= 4
MLDECL(int,            MLLogStreamToFile, (MLINK mlp, const char *name));
MLDECL(int,       MLDisableLoggingStream, (MLINK mlp));
MLDECL(int,        MLEnableLoggingStream, (MLINK mlp));
MLDECL(int,    MLStopLoggingStreamToFile, (MLINK mlp, const char *name));
MLDECL(int,          MLStopLoggingStream, (MLINK mlp));

MLDECL(int,         MLLogFileNameForLink, (MLINK mlp, const char **name));
MLDECL(void, MLReleaseLogFileNameForLink, (MLINK mlp, const char *name));
#endif

/* MLLinkName returns a pointer to the link's name.
 * Links are generally named when they are created
 * and are based on information that is potentially
 * useful and is available at that time.
 * Do not attempt to deallocate the name's storage
 * through this pointer.  The storage should be
 * considered in read-only memory.
 */

MLDECL( const char *, MLName,    ( MLINK mlp));
MLDECL( const char *, MLLinkName,    ( MLINK mlp));

#if MLINTERFACE >= 4
MLDECL( const unsigned short *, MLUCS2LinkName,  (MLINK mlp, int *length));
MLDECL( const unsigned char *,  MLUTF8LinkName,  (MLINK mlp, int *length));
MLDECL( const unsigned short *, MLUTF16LinkName, (MLINK mlp, int *length));
MLDECL( const unsigned int *,   MLUTF32LinkName, (MLINK mlp, int *length));

MLDECL(void, MLReleaseLinkName,      (MLINK mlp, const char *name));
MLDECL(void, MLReleaseUCS2LinkName,  (MLINK mlp, const unsigned short *name, int length));
MLDECL(void, MLReleaseUTF8LinkName,  (MLINK mlp, const unsigned char *name, int length));
MLDECL(void, MLReleaseUTF16LinkName, (MLINK mlp, const unsigned short *name, int length));
MLDECL(void, MLReleaseUTF32LinkName, (MLINK mlp, const unsigned int *name, int length));
#endif

MLDECL( long,      MLNumber,  ( MLINK mlp));
MLDECL( long,  MLToLinkID,  ( MLINK mlp));
MLDECL( MLINK, MLFromLinkID, ( MLEnvironment ep, long n));

MLDECL( char *,  MLSetName, ( MLINK mlp, const char *name));

/* The following functions are
 * currently for internal use only.
 */

MLDECL( void*, MLInit,   ( MLallocator alloc, MLdeallocator dealloc, void* enclosing_environment));
MLDECL( void,  MLDeinit, ( void* env));
MLDECL( void*, MLEnclosingEnvironment, ( void* ep));
MLDECL( void*, MLinkEnvironment, ( MLINK mlp));


#if MLINTERFACE >= 4
MLDECL(void, MLEnableLinkLock,  (MLINK mlp));
MLDECL(void, MLDisableLinkLock, (MLINK mlp));
#endif /* MLINTERFACE >= 4 */


#if MLINTERFACE >= 4
MLDECL( MLEnvironment, MLLinkEnvironment, (MLINK mlp));
#endif /* MLINTERFACE >= 4 */


#if MLINTERFACE >= 4
MLDECL( int,  MLIsLinkLoopback, (MLINK mlp));
#endif

/* the following two functions are for internal use only */
MLDECL( MLYieldFunctionObject, MLDefaultYieldFunction,    ( MLEnvironment env));

MLDECL( int,          MLSetDefaultYieldFunction, ( MLEnvironment env, MLYieldFunctionObject yf));


ML_END_EXTERN_C





#ifndef MLLINKSERVER_H
#define MLLINKSERVER_H






#if MLINTERFACE >= 4

ML_EXTERN_C

typedef void * MLLinkServer;

typedef void (*MLNewLinkCallbackFunction)(MLLinkServer server, MLINK link);

MLDECL(MLLinkServer, MLNewLinkServer, (MLEnvironment env, void *context, int *error));

MLDECL(MLLinkServer, MLNewLinkServerWithPort, (MLEnvironment env, unsigned short port, void *context,
    int *error));

MLDECL(MLLinkServer, MLNewLinkServerWithPortAndInterface, (MLEnvironment env, unsigned short port, const char *iface,
    void *context, int *error));

MLDECL(void, MLShutdownLinkServer, (MLLinkServer server));

MLDECL(void, MLRegisterCallbackFunctionWithLinkServer, (MLLinkServer server, MLNewLinkCallbackFunction function));

MLDECL(MLINK, MLWaitForNewLinkFromLinkServer, (MLLinkServer server, int *error));

MLDECL(unsigned short, MLPortFromLinkServer, (MLLinkServer server, int *error));

MLDECL(const char *, MLInterfaceFromLinkServer, (MLLinkServer server, int *error));

MLDECL(void *, MLContextFromLinkServer, (MLLinkServer server, int *error));

MLDECL(void, MLReleaseInterfaceFromLinkServer, (MLLinkServer server, const char *iface));

ML_END_EXTERN_C

#endif /* MLINTERFACE >= 4 */

#endif /* MLLINKSERVER_H */




#ifndef MLSERVICEDISCOVERYAPI_H
#define MLSERVICEDISCOVERYAPI_H







#if MLINTERFACE >= 4

ML_EXTERN_C

#define MLSDADDSERVICE      0x0001
#define MLSDREMOVESERVICE   0x0002
#define MLSDBROWSEERROR     0x0003
#define MLSDRESOLVEERROR    0x0004
#define MLSDREGISTERERROR   0x0005
#define MLSDMORECOMING      0x0010
#define MLSDNAMECONFLICT    0x0007

typedef void * MLServiceRef;

typedef void (*MLBrowseCallbackFunction)(MLEnvironment env, MLServiceRef ref, int flag,
	const char *serviceName, void *context);

MLDECL(int,     MLBrowseForLinkServices, (MLEnvironment env,
    MLBrowseCallbackFunction callbackFunction, const char *serviceProtocol,
    const char *domain, void *context, MLServiceRef *ref));

MLDECL(void, MLStopBrowsingForLinkServices, (MLEnvironment env, MLServiceRef ref));

typedef void (*MLResolveCallbackFunction)(MLEnvironment env, MLServiceRef ref, const char *serviceName,
	const char *linkName, const char *protocol, int options, void *context);

MLDECL(int, MLResolveLinkService, (MLEnvironment env,
    MLResolveCallbackFunction, const char *serviceProtocol,
    const char *serviceName, void *context, MLServiceRef *ref));

MLDECL(void, MLStopResolvingLinkService, (MLEnvironment env, MLServiceRef ref));

typedef void (*MLRegisterCallbackFunction)(MLEnvironment env, MLServiceRef ref, int flag, const char *serviceName,
	void *context);

MLDECL(MLINK, MLRegisterLinkServiceWithPortAndHostname, (MLEnvironment env, const char *serviceProtocol,
    const char *serviceName, unsigned short port, const char *hostname, MLRegisterCallbackFunction function,
    const char *domain, void *context, MLServiceRef *ref, int *error));

MLDECL(MLINK, MLRegisterLinkServiceWithHostname, (MLEnvironment env, const char *serviceProtocol,
    const char *serviceName, const char *hostname, MLRegisterCallbackFunction function,
    const char *domain, void *context, MLServiceRef *ref, int *error));

MLDECL(MLINK, MLRegisterLinkService, (MLEnvironment env, const char *serviceProtocol,
    const char *serviceName, MLRegisterCallbackFunction function,
    const char *domain, void *context, MLServiceRef *, int *error));

MLDECL(MLINK, MLRegisterLinkServiceUsingLinkProtocol, (MLEnvironment env, const char *serviceProtocol,
	const char *serviceName, unsigned short port, const char *hostname, const char *protocol,
	MLRegisterCallbackFunction function, const char *domain, void *context, MLServiceRef *ref, int *error));

MLDECL(void, MLRegisterLinkServiceFromLinkServer, (MLEnvironment env, const char *serviceProtocol,
    const char *serviceName, MLLinkServer server, MLRegisterCallbackFunction function, const char *domain,
    void *context, MLServiceRef *ref, int *error));

MLDECL(void, MLStopRegisteringLinkService, (MLEnvironment env, MLServiceRef ref));

MLDECL(void, MLStopRegisteringLinkServiceForLink, (MLEnvironment env, MLINK link, MLServiceRef ref));

MLDECL(const char *, MLServiceProtocolFromReference, (MLEnvironment env, MLServiceRef ref));

ML_END_EXTERN_C

#endif /* MLINTERFACE >= 4 */

#endif /* end of include guard: MLSERVICEDISCOVERYAPI_H */



#ifndef _WSERRNO_H
#define _WSERRNO_H

/* edit here and in mlerrstr.h */

#define WSEUNKNOWN          -1
#define WSEOK                0
#define WSEDEAD              1
#define WSEGBAD              2
#define WSEGSEQ              3
#define WSEPBTK              4
#define WSEPSEQ              5
#define WSEPBIG              6
#define WSEOVFL              7
#define WSEMEM               8
#define WSEACCEPT            9
#define WSECONNECT          10
#define WSECLOSED           11
#define WSEDEPTH            12  /* internal error */
#define WSENODUPFCN         13  /* stream cannot be duplicated */

#define WSENOACK            15  /* */
#define WSENODATA           16  /* */
#define WSENOTDELIVERED     17  /* */
#define WSENOMSG            18  /* */
#define WSEFAILED           19  /* */

#define WSEGETENDEXPR       20
#define WSEPUTENDPACKET     21 /* unexpected call of WSEndPacket */
                               /* currently atoms aren't
                                * counted on the way out so this error is raised only when
                                * WSEndPacket is called in the midst of an atom
                                */
#define WSENEXTPACKET       22
#define WSEUNKNOWNPACKET    23
#define WSEGETENDPACKET     24
#define WSEABORT            25
#define WSEMORE             26 /* internal error */
#define WSENEWLIB           27
#define WSEOLDLIB           28
#define WSEBADPARAM         29
#define WSENOTIMPLEMENTED   30


#define WSEINIT             32
#define WSEARGV             33
#define WSEPROTOCOL         34
#define WSEMODE             35
#define WSELAUNCH           36
#define WSELAUNCHAGAIN      37
#define WSELAUNCHSPACE      38
#define WSENOPARENT         39
#define WSENAMETAKEN        40
#define WSENOLISTEN         41
#define WSEBADNAME          42
#define WSEBADHOST          43
#define WSERESOURCE         44  /* a required resource was missing */
#define WSELAUNCHFAILED     45
#define WSELAUNCHNAME       46
#define WSEPDATABAD         47
#define WSEPSCONVERT        48
#define WSEGSCONVERT        49
#define WSENOTEXE           50
#define WSESYNCOBJECTMAKE   51
#define WSEBACKOUT          52
#define WSEBADOPTSYM        53
#define WSEBADOPTSTR        54
#define WSENEEDBIGGERBUFFER 55
#define WSEBADNUMERICSID    56
#define WSESERVICENOTAVAILABLE 57
#define WSEBADARGUMENT      58
#define WSEBADDISCOVERYHOSTNAME         59
#define WSEBADDISCOVERYDOMAINNAME       60
#define WSEBADSERVICENAME               61
#define WSEBADDISCOVERYSTATE            62
#define WSEBADDISCOVERYFLAGS            63
#define WSEDISCOVERYNAMECOLLISION       64
#define WSEBADSERVICEDISCOVERY          65
#define WSELAST WSESERVICENOTAVAILABLE

#define WSETRACEON         996  /* */
#define WSETRACEOFF        997  /* */
#define WSEDEBUG           998  /* */
#define WSEASSERT          999  /* an internal assertion failed */
#define WSEUSER           1000  /* start of user defined errors */


#endif /* _WSERRNO_H */


#ifndef _MLERRORS_H
#define _MLERRORS_H




/*************** MathLink errors ***************/
/*
 * When some problem is detected within MathLink, routines
 * will return a simple indication of failure and store
 * an error code internally. (For routines that have nothing
 * else useful to return, success is indicated by returning
 * non-zero and failure by returning 0.)  MLerror() returns
 * the current error code;  MLErrorMessage returns an English
 * language description of the error.
 * The error MLEDEAD is irrecoverable.  For the others, MLClearError()
 * will reset the error code to MLEOK.
 */



#ifndef _MLERRNO_H
#define _MLERRNO_H

/* edit here and in mlerrstr.h */

#define MLEUNKNOWN          -1
#define MLEOK                0
#define MLEDEAD              1
#define MLEGBAD              2
#define MLEGSEQ              3
#define MLEPBTK              4
#define MLEPSEQ              5
#define MLEPBIG              6
#define MLEOVFL              7
#define MLEMEM               8
#define MLEACCEPT            9
#define MLECONNECT          10
#define MLECLOSED           11
#define MLEDEPTH            12  /* internal error */
#define MLENODUPFCN         13  /* stream cannot be duplicated */

#define MLENOACK            15  /* */
#define MLENODATA           16  /* */
#define MLENOTDELIVERED     17  /* */
#define MLENOMSG            18  /* */
#define MLEFAILED           19  /* */

#define MLEGETENDEXPR       20
#define MLEPUTENDPACKET     21 /* unexpected call of MLEndPacket */
                               /* currently atoms aren't
                                * counted on the way out so this error is raised only when
                                * MLEndPacket is called in the midst of an atom
                                */
#define MLENEXTPACKET       22
#define MLEUNKNOWNPACKET    23
#define MLEGETENDPACKET     24
#define MLEABORT            25
#define MLEMORE             26 /* internal error */
#define MLENEWLIB           27
#define MLEOLDLIB           28
#define MLEBADPARAM         29
#define MLENOTIMPLEMENTED   30


#define MLEINIT             32
#define MLEARGV             33
#define MLEPROTOCOL         34
#define MLEMODE             35
#define MLELAUNCH           36
#define MLELAUNCHAGAIN      37
#define MLELAUNCHSPACE      38
#define MLENOPARENT         39
#define MLENAMETAKEN        40
#define MLENOLISTEN         41
#define MLEBADNAME          42
#define MLEBADHOST          43
#define MLERESOURCE         44  /* a required resource was missing */
#define MLELAUNCHFAILED     45
#define MLELAUNCHNAME       46
#define MLEPDATABAD         47
#define MLEPSCONVERT        48
#define MLEGSCONVERT        49
#define MLENOTEXE           50
#define MLESYNCOBJECTMAKE   51
#define MLEBACKOUT          52
#if MLINTERFACE == 3
#define MLELAST MLEBACKOUT
#else /* MLINTERFACE >= 4 */
#define MLEBADOPTSYM        53
#define MLEBADOPTSTR        54
#define MLENEEDBIGGERBUFFER 55
#define MLEBADNUMERICSID    56
#define MLESERVICENOTAVAILABLE 57
#define MLEBADARGUMENT      58
#define MLEBADDISCOVERYHOSTNAME         59
#define MLEBADDISCOVERYDOMAINNAME       60
#define MLEBADSERVICENAME               61
#define MLEBADDISCOVERYSTATE            62
#define MLEBADDISCOVERYFLAGS            63
#define MLEDISCOVERYNAMECOLLISION       64
#define MLEBADSERVICEDISCOVERY          65
#define MLELAST MLESERVICENOTAVAILABLE
#endif

#define MLETRACEON         996  /* */
#define MLETRACEOFF        997  /* */
#define MLEDEBUG           998  /* */
#define MLEASSERT          999  /* an internal assertion failed */
#define MLEUSER           1000  /* start of user defined errors */


#endif /* _MLERRNO_H */



#endif /* _MLERRORS_H */

/* explicitly not protected by _MLERRORS_H in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C
MLDECL( int,  MLError,        ( MLINK mlp));
MLDECL( int,  MLClearError,   ( MLINK mlp));
MLDECL( int,  MLSetError,     ( MLINK mlp, int err));
ML_END_EXTERN_C



#ifndef _MLYLDMSG_H
#define _MLYLDMSG_H









enum {	MLTerminateMessage = 1, MLInterruptMessage, MLAbortMessage,
	MLEndPacketMessage, MLSynchronizeMessage, MLImDyingMessage,
	MLWaitingAcknowledgment, MLMarkTopLevelMessage, MLLinkClosingMessage,
	MLAuthenticateFailure, MLSuspendActivitiesMessage, MLResumeActivitiesMessage,
	MLFirstUserMessage = 128, MLLastUserMessage = 255 };

typedef unsigned long devinfo_selector;


#endif /* _MLYLDMSG_H */

/* explicitly not protected by _MLYLDMSG_H in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C

#ifndef MLINTERFACE
/*\ syntax\ error\ */\ )
#endif

MLDECL( int,   MLPutMessage,   ( MLINK mlp, int  msg));
MLDECL( int,   MLGetMessage,   ( MLINK mlp, int *mp, int *np));
MLDECL( int,   MLMessageReady, ( MLINK mlp));

MLDECL( int,   MLPutMessageWithArg, ( MLINK mlp, int msg, int arg));


MLDECL( MLMessageHandlerObject, MLGetMessageHandler,    ( MLINK mlp));
MLDECL( MLMessageHandlerObject, MLMessageHandler,    ( MLINK mlp));

MLDECL( MLYieldFunctionObject,  MLGetYieldFunction,     ( MLINK mlp));
MLDECL( MLYieldFunctionObject,  MLYieldFunction,     ( MLINK mlp));

MLDECL( int,  MLSetMessageHandler, ( MLINK mlp, MLMessageHandlerObject h));
MLDECL( int,  MLSetYieldFunction,  ( MLINK mlp, MLYieldFunctionObject yf));

#if MLINTERFACE > 1 && MLINTERFACE < 4
MLDECL( int,  MLSetYieldFunction0,  ( MLINK mlp, MLYieldFunctionObject yf, MLINK cookie));
MLDECL( int,  MLSetMessageHandler0, ( MLINK mlp, MLMessageHandlerObject func, MLINK cookie));
#endif /* MLINTERFACE > 1 && MLINTERFACE < 4 */

MLDECL( int, MLDeviceInformation, ( MLINK mlp, devinfo_selector selector, void* buf, long *buflen));

#if MLINTERFACE >= 4
MLDECL( int,         MLLowLevelDeviceName, (MLINK mlp, const char **name));
MLDECL( void, MLReleaseLowLevelDeviceName, (MLINK mlp, const char *name));
#endif


ML_END_EXTERN_C


/*************** Textual interface ***************/


#ifndef _MLGET_H
#define _MLGET_H




#endif /* _MLGET_H */

/* explicitly not protected by _MLGET_H in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C

MLDECL( int,   MLGetNext,          ( MLINK mlp));
MLDECL( int,   MLGetNextRaw,       ( MLINK mlp));
MLDECL( int,   MLGetType,          ( MLINK mlp));
MLDECL( int,   MLGetRawType,       ( MLINK mlp));
MLDECL( int,   MLGetRawData,       ( MLINK mlp, unsigned char *data, int size, int *gotp));
MLDECL( int,   MLGetData,          ( MLINK mlp, char *data, int size, int *gotp));
MLDECL( int,   MLGetArgCount,      ( MLINK mlp, int *countp));
MLDECL( int,   MLGetRawArgCount,   ( MLINK mlp, int *countp));
MLDECL( int,   MLBytesToGet,       ( MLINK mlp, int *leftp));
MLDECL( int,   MLRawBytesToGet,    ( MLINK mlp, int *leftp));
MLDECL( int,   MLExpressionsToGet, ( MLINK mlp, int *countp));

MLDECL( int,   MLNewPacket,        ( MLINK mlp));

MLDECL( int,   MLTakeLast,         ( MLINK mlp, int eleft));

MLDECL( int,   MLFill,             ( MLINK mlp));
ML_END_EXTERN_C



#ifndef _MLPUT_H
#define _MLPUT_H






#define MLPutExpression is obsolete, use MLPutComposite

#endif /* _MLPUT_H */

/* explicitly not protected by _MLPUT_H in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C

MLDECL( int,   MLPutNext,      ( MLINK mlp, int tok));
MLDECL( int,   MLPutType,      ( MLINK mlp, int tok));
MLDECL( int,   MLPutRawSize,   ( MLINK mlp, int size));
MLDECL( int,   MLPutRawData,   ( MLINK mlp, const unsigned char *data, int len));
MLDECL( int,   MLPutArgCount,  ( MLINK mlp, int argc));
MLDECL( int,   MLPutComposite, ( MLINK mlp, int argc));
MLDECL( int,   MLBytesToPut,   ( MLINK mlp, int *leftp));
MLDECL( int,   MLEndPacket,    ( MLINK mlp));
MLDECL( int,   MLFlush,        ( MLINK mlp));

ML_END_EXTERN_C



#ifndef _WSTK_H
#define _WSTK_H

#define	WSTKOLDINT     'I'		/* 73 Ox49 01001001 */ /* integer leaf node */
#define	WSTKOLDREAL    'R'		/* 82 Ox52 01010010 */ /* real leaf node */


#define	WSTKFUNC    'F'		/* 70 Ox46 01000110 */ /* non-leaf node */

#define	WSTKERROR   (0)		/* bad token */
#define	WSTKERR     (0)		/* bad token */

/* text token bit patterns: 0010x01x --exactly 2 bits worth chosen to make things somewhat readable */
#define WSTK__IS_TEXT( tok) ( (tok & 0x00F6) == 0x0022)


#define	WSTKSTR     '"'         /* 34 0x22 00100010 */
#define	WSTKSYM     '#'         /* 35 0x23 # 00100011 */

#if WSINTERFACE >= 4
#define WSTKOPTSYM  'O'       /* 79 00101010 */
#define WSTKOPTSTR  'Q'       /* 81 01010001 */
#endif

#define	WSTKREAL    '*'         /* 42 0x2A 00101010 */
#define	WSTKINT     '+'         /* 43 0x2B 00101011 */



/* The following defines are for internal use only */
#define	WSTKPCTEND  ']'     /* at end of top level expression */
#define	WSTKAPCTEND '\n'    /* at end of top level expression */
#define	WSTKEND     '\n'
#define	WSTKAEND    '\r'
#define	WSTKSEND    ','

#define	WSTKCONT    '\\'
#define	WSTKELEN    ' '

#define	WSTKNULL    '.'
#define	WSTKOLDSYM  'Y'     /* 89 0x59 01011001 */
#define	WSTKOLDSTR  'S'     /* 83 0x53 01010011 */


typedef unsigned long decoder_mask;
#define	WSTKPACKED	'P'     /* 80 0x50 01010000 */
#define	WSTKARRAY	'A'     /* 65 0x41 01000001 */
#define	WSTKDIM		'D'     /* 68 0x44 01000100 */

#define WSLENGTH_DECODER        ((decoder_mask) 1<<16)
#define WSTKPACKED_DECODER      ((decoder_mask) 1<<17)
#define WSTKARRAY_DECODER	    ((decoder_mask) 1<<18)
#define WSTKMODERNCHARS_DECODER ((decoder_mask) 1<<19)
#define WSTKNULLSEQUENCE_DECODER ((decoder_mask) 0)
#define WSTKALL_DECODERS (WSLENGTH_DECODER | WSTKPACKED_DECODER | WSTKARRAY_DECODER | WSTKMODERNCHARS_DECODER | WSTKNULLSEQUENCE_DECODER)

#define WSTK_FIRSTUSER '\x30' /* user token */
#define WSTK_LASTUSER  '\x3F'

#endif /* _WSTK_H */


/*************** mlint64 interface ***************/


#ifndef _MLINTEGER64_H
#define _MLINTEGER64_H



#if MLINTERFACE == 3

ML_EXTERN_C

MLDECL(mlint64,              MLInteger64_FromInteger16,    (short a));
MLDECL(mlint64,              MLInteger64_FromInteger32,    (int a));
MLDECL(short,                  MLInteger64_ToInteger16,    (mlint64 a));
MLDECL(int,                    MLInteger64_ToInteger32,    (mlint64 a));

MLDECL(int,                          MLInteger64_Equal,    (mlint64 a, mlint64 b));
MLDECL(int,                       MLInteger64_NotEqual,    (mlint64 a, mlint64 b));
MLDECL(int,                      MLInteger64_LessEqual,    (mlint64 a, mlint64 b));
MLDECL(int,                           MLInteger64_Less,    (mlint64 a, mlint64 b));
MLDECL(int,                   MLInteger64_GreaterEqual,    (mlint64 a, mlint64 b));
MLDECL(int,                        MLInteger64_Greater,    (mlint64 a, mlint64 b));

MLDECL(int,    MLInteger64_GreaterThanLargestInteger32,    (mlint64 a));

MLDECL(mlint64,                     MLInteger64_BitAnd,    (mlint64 a, mlint64 b));
MLDECL(mlint64,                      MLInteger64_BitOr,    (mlint64 a, mlint64 b));
MLDECL(mlint64,                     MLInteger64_BitXor,    (mlint64 a, mlint64 b));
MLDECL(mlint64,                     MLInteger64_BitNot,    (mlint64 a));
MLDECL(mlint64,                        MLInteger64_Neg,    (mlint64 a));

MLDECL(mlint64,                       MLInteger64_Plus,    (mlint64 a, mlint64 b));
MLDECL(mlint64,                  MLInteger64_Increment,    (mlint64 a, mlint64 b));
MLDECL(mlint64,                MLInteger64_Increment32,    (mlint64 a, int b));
MLDECL(mlint64,                   MLInteger64_Subtract,    (mlint64 a, mlint64 b));
MLDECL(mlint64,                  MLInteger64_Decrement,    (mlint64 a, mlint64 b));
MLDECL(mlint64,                MLInteger64_Decrement32,    (mlint64 a, int b));
MLDECL(mlint64,                      MLInteger64_Times,    (mlint64 a, mlint64 b));
MLDECL(mlint64,                     MLInteger64_Divide,    (mlint64 a, mlint64 b));
MLDECL(mlint64,                        MLInteger64_Mod,    (mlint64 a, mlint64 b));

ML_END_EXTERN_C

#endif /* MLINTERFACE == 3 */

#endif /* _MLINTEGER64_H */


/*************** Native C types interface ***************/

#define MLGETNUMBERS_HPP
#define MLGETSTRINGS_HPP
#define MLGETSYMBOLS_HPP
#define MLPUTNUMBERS_HPP
#define MLPUTSTRINGS_HPP
#define MLPUTSYMBOLS_HPP



#ifndef MLGETNUMBERS_HPP
#define MLGETNUMBERS_HPP




#ifndef _MLNTYPES_H
#define _MLNTYPES_H





#ifndef _MLNUMENV_H
#define _MLNUMENV_H






/* mlne__s2 must convert empty strings to zero */



ML_EXTERN_C


#define REALBIT 4
#define REAL_MASK (1 << REALBIT)
#define XDRBIT 5
#define XDR_MASK (1 << XDRBIT)
#define BINARYBIT 7
#define BINARY_MASK (1 << BINARYBIT)
#define SIZEVARIANTBIT 6
#define SIZEVARIANT_MASK (1 << SIZEVARIANTBIT)


#define MLTK_INVALID                                          155


#define MLNE__IMPLIED_SIZE( tok, num_dispatch) ((tok) & XDR_MASK || !((tok) & SIZEVARIANT_MASK) \
		? (tok) & 0x08 ? (tok) & (0x0E + 2) : (1 << ((tok)>>1 & 0x03)) \
		: call_num_dispatch( (num_dispatch), MLNE__SIZESELECTOR((tok)), 0,0,0))

/* Range[-128, 127] */
/* 160 -> ((unsigned char)'\240') */
#define	MLTK_8BIT_SIGNED_2sCOMPLEMENT_INTEGER                 160
/* Range[0, 255] */
/* 161 -> ((unsigned char)'\241') */
#define	MLTK_8BIT_UNSIGNED_2sCOMPLEMENT_INTEGER               161
#define MLTK_8BIT_UNSIGNED_INTEGER MLTK_8BIT_UNSIGNED_2sCOMPLEMENT_INTEGER

/* Range[-32768, 32767] */
/* 162 -> ((unsigned char)'\242') */
#define	MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER      162
/* Range[0, 65535] */
/* 163 -> ((unsigned char)'\243') */
#define	MLTK_16BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER    163
#define	MLTK_16BIT_UNSIGNED_BIGENDIAN_INTEGER MLTK_16BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
/* Range[-2147483648, 2147483647] */
/* 164 -> ((unsigned char)'\244') */
#define	MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER      164
/* Range[0, 4294967295] */
/* 165 -> ((unsigned char)'\245') */
#define	MLTK_32BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER    165
#define	MLTK_32BIT_UNSIGNED_BIGENDIAN_INTEGER MLTK_32BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
/* Range[-9223372036854775808, 9223372036854775807] */
/* 166 -> ((unsigned char)'\246') */
#define	MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER      166
/* Range[0, 18446744073709551615] */
/* 167 -> ((unsigned char)'\247') */
#define	MLTK_64BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER    167
#define	MLTK_64BIT_UNSIGNED_BIGENDIAN_INTEGER MLTK_64BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER


/* Range[-32768, 32767] */
/* 226 -> ((unsigned char)'\342') */
#define	MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER   226
/* Range[0, 65535] */
/* 227 -> ((unsigned char)'\343') */
#define	MLTK_16BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER 227
#define	MLTK_16BIT_UNSIGNED_LITTLEENDIAN_INTEGER MLTK_16BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
/* Range[-2147483648, 2147483647] */
/* 228 -> ((unsigned char)'\344') */
#define	MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER   228
/* Range[0, 4294967295] */
/* 229 -> ((unsigned char)'\345') */
#define	MLTK_32BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER 229
#define	MLTK_32BIT_UNSIGNED_LITTLEENDIAN_INTEGER MLTK_32BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
/* Range[-9223372036854775808, 9223372036854775807] */
/* 230 -> ((unsigned char)'\346') */
#define	MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER   230
/* Range[0, 18446744073709551615] */
/* 231 -> ((unsigned char)'\347') */
#define	MLTK_64BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER 231
#define	MLTK_64BIT_UNSIGNED_LITTLEENDIAN_INTEGER MLTK_64BIT_UNSIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER

/* Interval[{-3.402823e+38, 3.402823e+38}] */
/* 180 -> ((unsigned char)'\264')    10110100   */
#define	MLTK_BIGENDIAN_IEEE754_SINGLE	                      180
/* Interval[{-1.79769313486232e+308, 1.79769313486232e+308}] */
/* 182 -> ((unsigned char)'\266')    10110110   */
#define	MLTK_BIGENDIAN_IEEE754_DOUBLE	                      182

/* 184 -> ((unsigned char)'\270')    10111000   */
#define MLTK_BIGENDIAN_128BIT_DOUBLE                          184

/* Interval[{-3.402823e+38, 3.402823e+38}] */
/* 244 -> ((unsigned char)'\364')    11110100   */
#define	MLTK_LITTLEENDIAN_IEEE754_SINGLE	                  244
/* Interval[{-1.79769313486232e+308, 1.79769313486232e+308}] */
/* 246 -> ((unsigned char)'\366')    11110110   */
#define	MLTK_LITTLEENDIAN_IEEE754_DOUBLE	                  246

/* 248 -> ((unsigned char)'\370')    11111000   */
#define MLTK_LITTLEENDIAN_128BIT_DOUBLE                       248


/* Note, if the future brings...
 * #define MLTK_128BIT_UNSIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER   ((unsigned char)'\257')
 * with  Range[0, 340282366920938463463374607431768211456 (*approximately 3.40282e+38*)]
 * the dynamic range is still a monotonically increasing function of the token value.
 * An implementation might choose to set the high varient bit to mainain this property
 * and dispatch more efficiently by avoiding overflow checks
 */

#if USE_MLNE__SELECTOR_FUNCTION
int MLNE__SELECTOR(int dtok, int stok);
#else
#define MLNE__SELECTOR( dtok, stok) \
	(((dtok) << 8) | (stok)) /* maybe should mask of high word and cast stok */
#endif
#define MLNE__SIZESELECTOR( tok) MLNE__SELECTOR( 0, tok)
#define MLNE__INITSELECTOR (0)
#define MLNE__TOSTRINGSELECTOR( tok) MLNE__SELECTOR( MLNE__IS_REAL(tok) ? MLTKREAL : MLTKINT, tok)
#define MLNE__FROMSTRINGSELECTOR( dtok, stok) MLNE__SELECTOR( dtok, stok)

#define MLNE__STOK( selector) ( (selector) & 0x000000FF)
#define MLNE__DTOK( selector) ( ((selector) & 0x0000FF00)>>8)

#define MLNE__IS_BINARY( tok) ((tok) & BINARY_MASK)
#define MLNE__IS_REAL( tok) ((tok) & REAL_MASK)
#define MLNE__TEXT_TOKEN( tok) (MLNE__IS_REAL( tok) ? MLTKREAL : MLTKINT)




ML_END_EXTERN_C


#endif /* _MLNUMENV_H */




/****************  Special Token types: ****************/

/* MLTK_CSHORT_P         193
   MLTK_CINT_P           194
   MLTK_CLONG_P          195
   MLTK_CFLOAT_P         209
   MLTK_CDOUBLE_P        210
   MLTK_CLONGDOUBLE_P    211 */

#define MLTK_CSHORT_P       (( BINARY_MASK | SIZEVARIANT_MASK | 1))
#define MLTK_CINT_P         (( BINARY_MASK | SIZEVARIANT_MASK | 2))
#define MLTK_CLONG_P        (( BINARY_MASK | SIZEVARIANT_MASK | 3))
#define MLTK_CFLOAT_P       (( BINARY_MASK | SIZEVARIANT_MASK | REAL_MASK | 1))
#define MLTK_CDOUBLE_P      (( BINARY_MASK | SIZEVARIANT_MASK | REAL_MASK | 2))
#define MLTK_CLONGDOUBLE_P  (( BINARY_MASK | SIZEVARIANT_MASK | REAL_MASK | 3))


#define MLTK_64BIT_LITTLEENDIAN_STRUCTURE 196
#define MLTK_64BIT_BIGENDIAN_STRUCTURE    197

/* 158 -> ((unsigned char)'\236') - used in Solaris numerics definitions */
#define MLTK_128BIT_EXTENDED 158
#define MLTK_128BIT_LONGDOUBLE 158


/* Interval[{-1.189731495357231765e+4932, 1.189731495357231765e+4932}] */
/* 218 -> ((unsigned char)'\332') */
#define MLTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED 218

/* Interval[{-1.189731495357231765e+4932, 1.189731495357231765e+4932}] */
/* ((unsigned char)'\330') */
#define MLTK_INTEL_80BIT_EXTENDED 216

/********************  MASTIFF  ****************************/
#define MLMASTIFF_NUMERICS_ID    "mastiff"
#define MLMASTIFF_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLMASTIFF_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLMASTIFF_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLMASTIFF_CINT64         MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLMASTIFF_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLMASTIFF_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLMASTIFF_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLMASTIFF_CLONGDOUBLE    MLTK_128BIT_EXTENDED
#define MLMASTIFF_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLMASTIFF_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLMASTIFF_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLMASTIFF_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLMASTIFF_MLINT64        MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLMASTIFF_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLMASTIFF_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLMASTIFF_MLLONGDOUBLE   MLTK_128BIT_EXTENDED

/********************  JAPANESECHIN  ****************************/
#define MLJAPANESECHIN_NUMERICS_ID    "japanesechin"
#define MLJAPANESECHIN_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLJAPANESECHIN_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLJAPANESECHIN_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLJAPANESECHIN_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLJAPANESECHIN_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLJAPANESECHIN_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLJAPANESECHIN_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLJAPANESECHIN_CLONGDOUBLE    MLTK_128BIT_EXTENDED
#define MLJAPANESECHIN_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLJAPANESECHIN_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLJAPANESECHIN_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLJAPANESECHIN_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLJAPANESECHIN_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLJAPANESECHIN_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLJAPANESECHIN_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLJAPANESECHIN_MLLONGDOUBLE   MLTK_128BIT_EXTENDED

/********************  BORZOI  ****************************/
/* The borzoi numerics environment specifically does not have MLBORZOI_CLONGDOUBLE or
MLBORZOI_MLLONGDOUBLE */

#define MLBORZOI_NUMERICS_ID          "borzoi"
#define MLBORZOI_CSHORT               MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORZOI_CINT                 MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORZOI_CLONG                MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORZOI_CSIZE_T              MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORZOI_CINT64               MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLBORZOI_CFLOAT               MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBORZOI_CDOUBLE              MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBORZOI_MLSHORT              MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORZOI_MLINT                MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORZOI_MLLONG               MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORZOI_MLSIZE_T             MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORZOI_MLINT64              MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLBORZOI_MLFLOAT              MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBORZOI_MLDOUBLE             MLTK_BIGENDIAN_IEEE754_DOUBLE

/********************  BRIARD  ****************************/
/* The briard numerics environment purposefully does not have MLBRIARD_CLONGDOUBLE or
MLBRIARD_MLLONGDOUBLE */

#define MLBRIARD_NUMERICS_ID          "briard"
#define MLBRIARD_CSHORT               MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBRIARD_CINT                 MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBRIARD_CLONG                MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBRIARD_CINT64               MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBRIARD_CSIZE_T              MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBRIARD_CFLOAT               MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBRIARD_CDOUBLE              MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBRIARD_MLSHORT              MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBRIARD_MLINT                MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBRIARD_MLLONG               MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBRIARD_MLINT64              MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBRIARD_MLSIZE_T             MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBRIARD_MLFLOAT              MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBRIARD_MLDOUBLE             MLTK_BIGENDIAN_IEEE754_DOUBLE

/********************  KEESHOND  ****************************/
#define MLKEESHOND_NUMERICS_ID    "keeshond"
#define MLKEESHOND_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKEESHOND_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKEESHOND_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKEESHOND_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKEESHOND_CINT64         MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLKEESHOND_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLKEESHOND_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLKEESHOND_CLONGDOUBLE    MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLKEESHOND_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKEESHOND_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKEESHOND_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKEESHOND_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKEESHOND_MLINT64        MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLKEESHOND_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLKEESHOND_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLKEESHOND_MLLONGDOUBLE   MLTK_BIGENDIAN_IEEE754_DOUBLE

/********************  KOMONDOR  ****************************/
#define MLKOMONDOR_NUMERICS_ID    "komondor"
#define MLKOMONDOR_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKOMONDOR_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKOMONDOR_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKOMONDOR_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKOMONDOR_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKOMONDOR_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLKOMONDOR_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLKOMONDOR_CLONGDOUBLE    MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLKOMONDOR_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKOMONDOR_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKOMONDOR_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKOMONDOR_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKOMONDOR_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLKOMONDOR_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLKOMONDOR_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLKOMONDOR_MLLONGDOUBLE   MLTK_BIGENDIAN_IEEE754_DOUBLE

/********************  NORWEGIANELKHOUND  ****************************/
#define MLNORWEGIANELKHOUND_NUMERICS_ID    "norwegianelkhound"
#define MLNORWEGIANELKHOUND_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWEGIANELKHOUND_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWEGIANELKHOUND_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWEGIANELKHOUND_CINT64         MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLNORWEGIANELKHOUND_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWEGIANELKHOUND_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLNORWEGIANELKHOUND_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLNORWEGIANELKHOUND_CLONGDOUBLE    MLTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED
#define MLNORWEGIANELKHOUND_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWEGIANELKHOUND_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWEGIANELKHOUND_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWEGIANELKHOUND_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWEGIANELKHOUND_MLINT64        MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLNORWEGIANELKHOUND_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLNORWEGIANELKHOUND_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLNORWEGIANELKHOUND_MLLONGDOUBLE   MLTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED

/********************  NORWICHTERRIOR  ****************************/
#define MLNORWICHTERRIOR_NUMERICS_ID    "norwichterrior"
#define MLNORWICHTERRIOR_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWICHTERRIOR_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWICHTERRIOR_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWICHTERRIOR_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWICHTERRIOR_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWICHTERRIOR_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLNORWICHTERRIOR_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLNORWICHTERRIOR_CLONGDOUBLE    MLTK_LITTLEENDIAN_128BIT_DOUBLE
#define MLNORWICHTERRIOR_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWICHTERRIOR_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWICHTERRIOR_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWICHTERRIOR_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWICHTERRIOR_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLNORWICHTERRIOR_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLNORWICHTERRIOR_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLNORWICHTERRIOR_MLLONGDOUBLE   MLTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  SAINTBERNARD  ****************************/
#define MLSAINTBERNARD_NUMERICS_ID    "saintbernarnd"
#define MLSAINTBERNARD_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAINTBERNARD_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAINTBERNARD_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAINTBERNARD_CINT64         MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLSAINTBERNARD_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAINTBERNARD_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLSAINTBERNARD_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLSAINTBERNARD_CLONGDOUBLE    MLTK_BIGENDIAN_128BIT_DOUBLE
#define MLSAINTBERNARD_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAINTBERNARD_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAINTBERNARD_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAINTBERNARD_MLINT64        MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLSAINTBERNARD_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAINTBERNARD_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLSAINTBERNARD_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLSAINTBERNARD_MLLONGDOUBLE   MLTK_BIGENDIAN_128BIT_DOUBLE

/********************  BERNESEMOUNTAINDOG  ****************************/
#define MLBERNESEMOUNTAINDOG_NUMERICS_ID    "bernesemountaindog"
#define MLBERNESEMOUNTAINDOG_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBERNESEMOUNTAINDOG_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBERNESEMOUNTAINDOG_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBERNESEMOUNTAINDOG_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBERNESEMOUNTAINDOG_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBERNESEMOUNTAINDOG_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBERNESEMOUNTAINDOG_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBERNESEMOUNTAINDOG_CLONGDOUBLE    MLTK_BIGENDIAN_128BIT_DOUBLE
#define MLBERNESEMOUNTAINDOG_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBERNESEMOUNTAINDOG_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBERNESEMOUNTAINDOG_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBERNESEMOUNTAINDOG_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBERNESEMOUNTAINDOG_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBERNESEMOUNTAINDOG_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBERNESEMOUNTAINDOG_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBERNESEMOUNTAINDOG_MLLONGDOUBLE   MLTK_BIGENDIAN_128BIT_DOUBLE

/********************  SETTER  ****************************/
#define MLSETTER_NUMERICS_ID    "setter"
#define MLSETTER_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSETTER_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSETTER_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSETTER_CINT64         MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLSETTER_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSETTER_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLSETTER_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLSETTER_CLONGDOUBLE    MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLSETTER_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSETTER_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSETTER_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSETTER_MLINT64        MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLSETTER_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSETTER_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLSETTER_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLSETTER_MLLONGDOUBLE   MLTK_INTEL_80BIT_EXTENDED

/********************  FRENCH_BULLDOG  ****************************/
#define MLFRENCH_BULLDOG_NUMERICS_ID    "french_bulldog"
#define MLFRENCH_BULLDOG_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLFRENCH_BULLDOG_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLFRENCH_BULLDOG_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLFRENCH_BULLDOG_CINT64         MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLFRENCH_BULLDOG_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLFRENCH_BULLDOG_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLFRENCH_BULLDOG_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLFRENCH_BULLDOG_CLONGDOUBLE    MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLFRENCH_BULLDOG_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLFRENCH_BULLDOG_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLFRENCH_BULLDOG_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLFRENCH_BULLDOG_MLINT64        MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLFRENCH_BULLDOG_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLFRENCH_BULLDOG_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLFRENCH_BULLDOG_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLFRENCH_BULLDOG_MLLONGDOUBLE   MLTK_LITTLEENDIAN_IEEE754_DOUBLE

/********************  BICHON_FRISE  ****************************/
#define MLBICHON_FRISE_NUMERICS_ID    "bichon_frise"
#define MLBICHON_FRISE_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBICHON_FRISE_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBICHON_FRISE_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBICHON_FRISE_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBICHON_FRISE_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBICHON_FRISE_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBICHON_FRISE_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBICHON_FRISE_CLONGDOUBLE    MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBICHON_FRISE_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBICHON_FRISE_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBICHON_FRISE_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBICHON_FRISE_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBICHON_FRISE_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBICHON_FRISE_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBICHON_FRISE_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBICHON_FRISE_MLLONGDOUBLE   MLTK_LITTLEENDIAN_IEEE754_DOUBLE

/********************  HELEN  ****************************/
#define MLHELEN_NUMERICS_ID    "helen"
#define MLHELEN_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLHELEN_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLHELEN_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLHELEN_CINT64         MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLHELEN_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLHELEN_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLHELEN_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLHELEN_CLONGDOUBLE    MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLHELEN_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLHELEN_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLHELEN_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLHELEN_MLINT64        MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLHELEN_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLHELEN_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLHELEN_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLHELEN_MLLONGDOUBLE   MLTK_LITTLEENDIAN_IEEE754_DOUBLE

/********************  BEAGLE  ****************************/
#define MLBEAGLE_NUMERICS_ID    "beagle"
#define MLBEAGLE_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBEAGLE_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBEAGLE_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBEAGLE_CINT64         MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLBEAGLE_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBEAGLE_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBEAGLE_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBEAGLE_CLONGDOUBLE    MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBEAGLE_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBEAGLE_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBEAGLE_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBEAGLE_MLINT64        MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLBEAGLE_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBEAGLE_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBEAGLE_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBEAGLE_MLLONGDOUBLE   MLTK_BIGENDIAN_IEEE754_DOUBLE

/********************  BULLTERRIER  ****************************/
#define MLBULLTERRIER_NUMERICS_ID    "bullterrier"
#define MLBULLTERRIER_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBULLTERRIER_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBULLTERRIER_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBULLTERRIER_CINT64         MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLBULLTERRIER_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBULLTERRIER_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBULLTERRIER_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBULLTERRIER_CLONGDOUBLE    MLTK_BIGENDIAN_128BIT_DOUBLE
#define MLBULLTERRIER_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBULLTERRIER_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBULLTERRIER_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBULLTERRIER_MLINT64        MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLBULLTERRIER_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBULLTERRIER_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBULLTERRIER_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBULLTERRIER_MLLONGDOUBLE   MLTK_BIGENDIAN_128BIT_DOUBLE

/********************  BORDERTERRIER  ****************************/
#define MLBORDERTERRIER_NUMERICS_ID    "borderterrier"
#define MLBORDERTERRIER_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORDERTERRIER_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORDERTERRIER_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORDERTERRIER_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORDERTERRIER_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORDERTERRIER_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBORDERTERRIER_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBORDERTERRIER_CLONGDOUBLE    MLTK_BIGENDIAN_128BIT_DOUBLE
#define MLBORDERTERRIER_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORDERTERRIER_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORDERTERRIER_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORDERTERRIER_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORDERTERRIER_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLBORDERTERRIER_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLBORDERTERRIER_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLBORDERTERRIER_MLLONGDOUBLE   MLTK_BIGENDIAN_128BIT_DOUBLE

/********************  BASENJI  ****************************/
#define MLBASENJI_NUMERICS_ID    "basenji"
#define MLBASENJI_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBASENJI_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBASENJI_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBASENJI_CINT64         MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLBASENJI_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBASENJI_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBASENJI_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBASENJI_CLONGDOUBLE    MLTK_LITTLEENDIAN_128BIT_DOUBLE
#define MLBASENJI_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBASENJI_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBASENJI_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBASENJI_MLINT64        MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLBASENJI_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBASENJI_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBASENJI_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBASENJI_MLLONGDOUBLE   MLTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  SHARPEI  ****************************/
#define MLSHARPEI_NUMERICS_ID    "sharpei"
#define MLSHARPEI_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHARPEI_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHARPEI_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHARPEI_CINT64         MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLSHARPEI_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHARPEI_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLSHARPEI_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLSHARPEI_CLONGDOUBLE    MLTK_LITTLEENDIAN_128BIT_DOUBLE
#define MLSHARPEI_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHARPEI_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHARPEI_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHARPEI_MLINT64        MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLSHARPEI_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHARPEI_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLSHARPEI_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLSHARPEI_MLLONGDOUBLE   MLTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  TIBETANMASTIFF  ****************************/
#define MLTIBETANMASTIFF_NUMERICS_ID    "tibetanmastiff"
#define MLTIBETANMASTIFF_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLTIBETANMASTIFF_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLTIBETANMASTIFF_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLTIBETANMASTIFF_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLTIBETANMASTIFF_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLTIBETANMASTIFF_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLTIBETANMASTIFF_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLTIBETANMASTIFF_CLONGDOUBLE    MLTK_LITTLEENDIAN_128BIT_DOUBLE
#define MLTIBETANMASTIFF_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLTIBETANMASTIFF_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLTIBETANMASTIFF_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLTIBETANMASTIFF_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLTIBETANMASTIFF_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLTIBETANMASTIFF_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLTIBETANMASTIFF_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLTIBETANMASTIFF_MLLONGDOUBLE   MLTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  GREATDANE  ****************************/
#define MLGREATDANE_NUMERICS_ID    "greatdane"
#define MLGREATDANE_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLGREATDANE_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLGREATDANE_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLGREATDANE_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLGREATDANE_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLGREATDANE_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLGREATDANE_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLGREATDANE_CLONGDOUBLE    MLTK_LITTLEENDIAN_128BIT_DOUBLE
#define MLGREATDANE_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLGREATDANE_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLGREATDANE_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLGREATDANE_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLGREATDANE_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLGREATDANE_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLGREATDANE_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLGREATDANE_MLLONGDOUBLE   MLTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  REDDOG  ****************************/
#define MLREDDOG_NUMERICS_ID    "reddog"
#define MLREDDOG_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLREDDOG_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLREDDOG_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLREDDOG_CINT64         MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLREDDOG_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLREDDOG_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLREDDOG_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLREDDOG_CLONGDOUBLE    MLTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED
#define MLREDDOG_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLREDDOG_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLREDDOG_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLREDDOG_MLINT64        MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLREDDOG_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLREDDOG_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLREDDOG_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLREDDOG_MLLONGDOUBLE   MLTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED

/********************  AUSTRALIANCATTLEDOG  ****************************/
#define MLAUSTRALIANCATTLEDOG_NUMERICS_ID    "australiancattledog"
#define MLAUSTRALIANCATTLEDOG_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAUSTRALIANCATTLEDOG_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAUSTRALIANCATTLEDOG_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAUSTRALIANCATTLEDOG_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAUSTRALIANCATTLEDOG_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAUSTRALIANCATTLEDOG_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLAUSTRALIANCATTLEDOG_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLAUSTRALIANCATTLEDOG_CLONGDOUBLE    MLTK_LITTLEENDIAN_128BIT_DOUBLE
#define MLAUSTRALIANCATTLEDOG_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAUSTRALIANCATTLEDOG_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAUSTRALIANCATTLEDOG_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAUSTRALIANCATTLEDOG_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAUSTRALIANCATTLEDOG_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAUSTRALIANCATTLEDOG_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLAUSTRALIANCATTLEDOG_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLAUSTRALIANCATTLEDOG_MLLONGDOUBLE   MLTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  BOXER  ****************************/
#define MLBOXER_NUMERICS_ID    "boxer"
#define MLBOXER_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOXER_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOXER_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOXER_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOXER_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOXER_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBOXER_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBOXER_CLONGDOUBLE    MLTK_LITTLEENDIAN_128BIT_DOUBLE
#define MLBOXER_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOXER_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOXER_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOXER_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOXER_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOXER_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBOXER_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBOXER_MLLONGDOUBLE   MLTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  AKITAINU  ****************************/
#define MLAKITAINU_NUMERICS_ID    "akitainu"
#define MLAKITAINU_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAKITAINU_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAKITAINU_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAKITAINU_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAKITAINU_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAKITAINU_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLAKITAINU_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLAKITAINU_CLONGDOUBLE    MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLAKITAINU_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAKITAINU_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAKITAINU_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAKITAINU_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAKITAINU_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLAKITAINU_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLAKITAINU_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLAKITAINU_MLLONGDOUBLE   MLTK_LITTLEENDIAN_IEEE754_DOUBLE

/********************  CHIHUAHUA  ****************************/
#define MLCHIHUAHUA_NUMERICS_ID    "chihuahua"
#define MLCHIHUAHUA_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHIHUAHUA_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHIHUAHUA_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHIHUAHUA_CINT64         MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLCHIHUAHUA_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHIHUAHUA_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLCHIHUAHUA_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLCHIHUAHUA_CLONGDOUBLE    MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLCHIHUAHUA_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHIHUAHUA_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHIHUAHUA_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHIHUAHUA_MLINT64        MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLCHIHUAHUA_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHIHUAHUA_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLCHIHUAHUA_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLCHIHUAHUA_MLLONGDOUBLE   MLTK_LITTLEENDIAN_IEEE754_DOUBLE

/********************  ROTTWEILER  ****************************/
#define MLROTTWEILER_NUMERICS_ID    "rottweiler"
#define MLROTTWEILER_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLROTTWEILER_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLROTTWEILER_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLROTTWEILER_CINT64         MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLROTTWEILER_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLROTTWEILER_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLROTTWEILER_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLROTTWEILER_CLONGDOUBLE    MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLROTTWEILER_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLROTTWEILER_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLROTTWEILER_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLROTTWEILER_MLINT64        MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLROTTWEILER_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLROTTWEILER_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLROTTWEILER_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLROTTWEILER_MLLONGDOUBLE   MLTK_BIGENDIAN_IEEE754_DOUBLE

/********************  PHARAOHHOUND  ****************************/
#define MLPHARAOHHOUND_NUMERICS_ID    "pharaohhound"
#define MLPHARAOHHOUND_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPHARAOHHOUND_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPHARAOHHOUND_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPHARAOHHOUND_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPHARAOHHOUND_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPHARAOHHOUND_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLPHARAOHHOUND_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLPHARAOHHOUND_CLONGDOUBLE    MLTK_BIGENDIAN_128BIT_DOUBLE
#define MLPHARAOHHOUND_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPHARAOHHOUND_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPHARAOHHOUND_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPHARAOHHOUND_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPHARAOHHOUND_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPHARAOHHOUND_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLPHARAOHHOUND_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLPHARAOHHOUND_MLLONGDOUBLE   MLTK_BIGENDIAN_128BIT_DOUBLE

/********************  TROUT  ****************************/
#define MLTROUT_NUMERICS_ID    "trout"
#define MLTROUT_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLTROUT_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLTROUT_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLTROUT_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLTROUT_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLTROUT_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLTROUT_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLTROUT_CLONGDOUBLE    MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLTROUT_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLTROUT_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLTROUT_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLTROUT_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLTROUT_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLTROUT_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLTROUT_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLTROUT_MLLONGDOUBLE   MLTK_BIGENDIAN_IEEE754_DOUBLE

/********************  PUG  ****************************/
#define MLPUG_NUMERICS_ID    "pug"
#define MLPUG_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPUG_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPUG_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPUG_CINT64         MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLPUG_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPUG_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLPUG_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLPUG_CLONGDOUBLE    MLTK_BIGENDIAN_128BIT_DOUBLE
#define MLPUG_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPUG_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPUG_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPUG_MLINT64        MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLPUG_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPUG_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLPUG_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLPUG_MLLONGDOUBLE   MLTK_BIGENDIAN_128BIT_DOUBLE

/********************  POINTER  ****************************/
#define MLPOINTER_NUMERICS_ID    "pointer"
#define MLPOINTER_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPOINTER_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPOINTER_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPOINTER_CINT64         MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLPOINTER_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPOINTER_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLPOINTER_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLPOINTER_CLONGDOUBLE    MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLPOINTER_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPOINTER_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPOINTER_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPOINTER_MLINT64        MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLPOINTER_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLPOINTER_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLPOINTER_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLPOINTER_MLLONGDOUBLE   MLTK_BIGENDIAN_IEEE754_DOUBLE

/********************  SAMOYED  ****************************/
#define MLSAMOYED_NUMERICS_ID    "samoyed"
#define MLSAMOYED_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAMOYED_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAMOYED_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAMOYED_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAMOYED_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAMOYED_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLSAMOYED_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLSAMOYED_CLONGDOUBLE    MLTK_BIGENDIAN_128BIT_DOUBLE
#define MLSAMOYED_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAMOYED_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAMOYED_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAMOYED_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAMOYED_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSAMOYED_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLSAMOYED_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLSAMOYED_MLLONGDOUBLE   MLTK_BIGENDIAN_128BIT_DOUBLE

/********************  SIBERIANHUSKY  ****************************/
#define MLSIBERIANHUSKY_NUMERICS_ID    "siberianhusky"
#define MLSIBERIANHUSKY_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSIBERIANHUSKY_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSIBERIANHUSKY_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSIBERIANHUSKY_CINT64         MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLSIBERIANHUSKY_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSIBERIANHUSKY_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLSIBERIANHUSKY_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLSIBERIANHUSKY_CLONGDOUBLE    MLTK_BIGENDIAN_128BIT_DOUBLE
#define MLSIBERIANHUSKY_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSIBERIANHUSKY_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSIBERIANHUSKY_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSIBERIANHUSKY_MLINT64        MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLSIBERIANHUSKY_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLSIBERIANHUSKY_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLSIBERIANHUSKY_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLSIBERIANHUSKY_MLLONGDOUBLE   MLTK_BIGENDIAN_128BIT_DOUBLE

/********************  SHIBAINU  ****************************/
#define MLSHIBAINU_NUMERICS_ID    "shibainu"
#define MLSHIBAINU_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHIBAINU_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHIBAINU_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHIBAINU_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHIBAINU_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHIBAINU_CFLOAT         MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLSHIBAINU_CDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLSHIBAINU_CLONGDOUBLE    MLTK_LITTLEENDIAN_128BIT_DOUBLE
#define MLSHIBAINU_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHIBAINU_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHIBAINU_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHIBAINU_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHIBAINU_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLSHIBAINU_MLFLOAT        MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLSHIBAINU_MLDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLSHIBAINU_MLLONGDOUBLE   MLTK_LITTLEENDIAN_128BIT_DOUBLE

/********************  NEWFOUNDLAND  ****************************/
#define MLNEWFOUNDLAND_NUMERICS_ID    "newfoundland"
#define MLNEWFOUNDLAND_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLNEWFOUNDLAND_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLNEWFOUNDLAND_CLONG          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLNEWFOUNDLAND_CINT64         MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLNEWFOUNDLAND_CSIZE_T        MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLNEWFOUNDLAND_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLNEWFOUNDLAND_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLNEWFOUNDLAND_CLONGDOUBLE    MLTK_BIGENDIAN_128BIT_DOUBLE
#define MLNEWFOUNDLAND_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLNEWFOUNDLAND_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLNEWFOUNDLAND_MLLONG         MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLNEWFOUNDLAND_MLINT64        MLTK_64BIT_BIGENDIAN_STRUCTURE
#define MLNEWFOUNDLAND_MLSIZE_T       MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLNEWFOUNDLAND_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLNEWFOUNDLAND_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLNEWFOUNDLAND_MLLONGDOUBLE   MLTK_BIGENDIAN_128BIT_DOUBLE

/********************  AFFENPINSCHER  ****************************/
#define MLAFFENPINSCHER_NUMERICS_ID    "affenpinscher"
#define MLAFFENPINSCHER_CSHORT         MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLAFFENPINSCHER_CINT           MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLAFFENPINSCHER_CLONG          MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLAFFENPINSCHER_CINT64         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLAFFENPINSCHER_CSIZE_T        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLAFFENPINSCHER_CFLOAT         MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLAFFENPINSCHER_CDOUBLE        MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLAFFENPINSCHER_CLONGDOUBLE    MLTK_BIGENDIAN_128BIT_DOUBLE
#define MLAFFENPINSCHER_MLSHORT        MLTK_16BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLAFFENPINSCHER_MLINT          MLTK_32BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLAFFENPINSCHER_MLLONG         MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLAFFENPINSCHER_MLINT64        MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLAFFENPINSCHER_MLSIZE_T       MLTK_64BIT_SIGNED_2sCOMPLEMENT_BIGENDIAN_INTEGER
#define MLAFFENPINSCHER_MLFLOAT        MLTK_BIGENDIAN_IEEE754_SINGLE
#define MLAFFENPINSCHER_MLDOUBLE       MLTK_BIGENDIAN_IEEE754_DOUBLE
#define MLAFFENPINSCHER_MLLONGDOUBLE   MLTK_BIGENDIAN_128BIT_DOUBLE

/********************  BEAUCERON  ****************************/
#define MLBEAUCERON_NUMERICS_ID        "beauceron"
#define MLBEAUCERON_CSHORT             MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBEAUCERON_CINT               MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBEAUCERON_CLONG              MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBEAUCERON_CINT64             MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBEAUCERON_CSIZE_T            MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBEAUCERON_CFLOAT             MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBEAUCERON_CDOUBLE            MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBEAUCERON_CLONGDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBEAUCERON_MLSHORT            MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBEAUCERON_MLINT              MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBEAUCERON_MLLONG             MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBEAUCERON_MLINT64            MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBEAUCERON_MLSIZE_T           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBEAUCERON_MLFLOAT            MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBEAUCERON_MLDOUBLE           MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBEAUCERON_MLLONGDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE


/********************  BERGAMASCO  ****************************/
#define MLBERGAMASCO_NUMERICS_ID       "bergamasco"
#define MLBERGAMASCO_CSHORT             MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBERGAMASCO_CINT               MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBERGAMASCO_CLONG              MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBERGAMASCO_CINT64             MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBERGAMASCO_CSIZE_T            MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBERGAMASCO_CFLOAT             MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBERGAMASCO_CDOUBLE            MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBERGAMASCO_CLONGDOUBLE        MLTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED
#define MLBERGAMASCO_MLSHORT            MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBERGAMASCO_MLINT              MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBERGAMASCO_MLLONG             MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBERGAMASCO_MLINT64            MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBERGAMASCO_MLSIZE_T           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBERGAMASCO_MLFLOAT            MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBERGAMASCO_MLDOUBLE           MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBERGAMASCO_MLLONGDOUBLE       MLTK_96BIT_HIGHPADDED_INTEL_80BIT_EXTENDED


/********************  BOERBOEL  ****************************/
#define MLBOERBOEL_NUMERICS_ID       "boerboel"
#define MLBOERBOEL_CSHORT             MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOERBOEL_CINT               MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOERBOEL_CLONG              MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOERBOEL_CINT64             MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOERBOEL_CSIZE_T            MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOERBOEL_CFLOAT             MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBOERBOEL_CDOUBLE            MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBOERBOEL_CLONGDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBOERBOEL_MLSHORT            MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOERBOEL_MLINT              MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOERBOEL_MLLONG             MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOERBOEL_MLINT64            MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOERBOEL_MLSIZE_T           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLBOERBOEL_MLFLOAT            MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLBOERBOEL_MLDOUBLE           MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLBOERBOEL_MLLONGDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE


/********************  CHINOOK  ****************************/
#define MLCHINOOK_NUMERICS_ID       "chinook"
#define MLCHINOOK_CSHORT             MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHINOOK_CINT               MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHINOOK_CLONG              MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHINOOK_CINT64             MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHINOOK_CSIZE_T            MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHINOOK_CFLOAT             MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLCHINOOK_CDOUBLE            MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLCHINOOK_CLONGDOUBLE        MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLCHINOOK_MLSHORT            MLTK_16BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHINOOK_MLINT              MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHINOOK_MLLONG             MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHINOOK_MLINT64            MLTK_64BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHINOOK_MLSIZE_T           MLTK_32BIT_SIGNED_2sCOMPLEMENT_LITTLEENDIAN_INTEGER
#define MLCHINOOK_MLFLOAT            MLTK_LITTLEENDIAN_IEEE754_SINGLE
#define MLCHINOOK_MLDOUBLE           MLTK_LITTLEENDIAN_IEEE754_DOUBLE
#define MLCHINOOK_MLLONGDOUBLE       MLTK_LITTLEENDIAN_IEEE754_DOUBLE



/********************  OLD_WIN_ENV  ****************************/
#define MLOLD_WIN_ENV_NUMERICS_ID    "Sep 13 1996, 13:46:34"
#define MLOLD_WIN_ENV_CSHORT         MLTK_CSHORT_P
#define MLOLD_WIN_ENV_CINT           MLTK_CINT_P
#define MLOLD_WIN_ENV_CLONG          MLTK_CLONG_P
#define MLOLD_WIN_ENV_CINT64         MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLOLD_WIN_ENV_CSIZE_T        MLTK_CLONG_P
#define MLOLD_WIN_ENV_CFLOAT         MLTK_CFLOAT_P
#define MLOLD_WIN_ENV_CDOUBLE        MLTK_CDOUBLE_P
#define MLOLD_WIN_ENV_CLONGDOUBLE    MLTK_CLONGDOUBLE_P
#define MLOLD_WIN_ENV_MLSHORT        MLTK_CSHORT_P
#define MLOLD_WIN_ENV_MLINT          MLTK_CINT_P
#define MLOLD_WIN_ENV_MLLONG         MLTK_CLONG_P
#define MLOLD_WIN_ENV_MLINT64        MLTK_64BIT_LITTLEENDIAN_STRUCTURE
#define MLOLD_WIN_ENV_MLSIZE_T       MLTK_CLONG_P
#define MLOLD_WIN_ENV_MLFLOAT        MLTK_CFLOAT_P
#define MLOLD_WIN_ENV_MLDOUBLE       MLTK_CDOUBLE_P
#define MLOLD_WIN_ENV_MLLONGDOUBLE   MLTK_CLONGDOUBLE_P


#define MLTK_CUCHAR  MLTK_8BIT_UNSIGNED_INTEGER
#define MLTK_MLUCHAR MLTK_8BIT_UNSIGNED_INTEGER

#if UNIX_MATHLINK /* hueristic that works for now */
	typedef unsigned int _uint32_nt;
	typedef signed int _sint32_nt;
#else
	typedef unsigned long _uint32_nt;
	typedef signed long _sint32_nt;
#endif


#if WINDOWS_MATHLINK
#define NEW_WIN32_NUMENV 1
#endif


/* #	define MATHLINK_NUMERICS_ENVIRONMENT_ID "Sep 16 1996, 23:14:20" M68KMACINTOSH_MATHLINK */
/* #	define MATHLINK_NUMERICS_ENVIRONMENT_ID_NUMB 33 */

/* #	define MATHLINK_NUMERICS_ENVIRONMENT_ID "newdog" POWERMACINTOSH_MATHLINK */
/* #	define MATHLINK_NUMERICS_ENVIRONMENT_ID_NUMB 24 */



#if (WIN32_MATHLINK || WIN64_MATHLINK) && NEW_WIN32_NUMENV
#if WIN32_MATHLINK
#if MLINTERFACE < 4
#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLFRENCH_BULLDOG_NUMERICS_ID

#define MLTK_CSHORT        MLFRENCH_BULLDOG_CSHORT
#define MLTK_CINT          MLFRENCH_BULLDOG_CINT
#define MLTK_CLONG         MLFRENCH_BULLDOG_CLONG
#define MLTK_CINT64        MLFRENCH_BULLDOG_CINT64
#define MLTK_CSIZE_T       MLFRENCH_BULLDOG_CSIZE_T
#define MLTK_CFLOAT        MLFRENCH_BULLDOG_CFLOAT
#define MLTK_CDOUBLE       MLFRENCH_BULLDOG_CDOUBLE
#define MLTK_CLONGDOUBLE   MLFRENCH_BULLDOG_CLONGDOUBLE

#define MLTK_MLSHORT       MLFRENCH_BULLDOG_MLSHORT
#define MLTK_MLINT         MLFRENCH_BULLDOG_MLINT
#define MLTK_MLLONG        MLFRENCH_BULLDOG_MLLONG
#define MLTK_MLINT64       MLFRENCH_BULLDOG_MLINT64
#define MLTK_MLSIZE_T      MLFRENCH_BULLDOG_MLSIZE_T
#define MLTK_MLFLOAT       MLFRENCH_BULLDOG_MLFLOAT
#define MLTK_MLDOUBLE      MLFRENCH_BULLDOG_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLFRENCH_BULLDOG_MLLONGDOUBLE
#endif /* MLINTERFACE < 4 */

#if MLINTERFACE >= 4
#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLBOERBOEL_NUMERICS_ID

#define MLTK_CSHORT        MLBOERBOEL_CSHORT
#define MLTK_CINT          MLBOERBOEL_CINT
#define MLTK_CLONG         MLBOERBOEL_CLONG
#define MLTK_CINT64        MLBOERBOEL_CINT64
#define MLTK_CSIZE_T       MLBOERBOEL_CSIZE_T
#define MLTK_CFLOAT        MLBOERBOEL_CFLOAT
#define MLTK_CDOUBLE       MLBOERBOEL_CDOUBLE
#define MLTK_CLONGDOUBLE   MLBOERBOEL_CLONGDOUBLE

#define MLTK_MLSHORT       MLBOERBOEL_MLSHORT
#define MLTK_MLINT         MLBOERBOEL_MLINT
#define MLTK_MLLONG        MLBOERBOEL_MLLONG
#define MLTK_MLINT64       MLBOERBOEL_MLINT64
#define MLTK_MLSIZE_T      MLBOERBOEL_MLSIZE_T
#define MLTK_MLFLOAT       MLBOERBOEL_MLFLOAT
#define MLTK_MLDOUBLE      MLBOERBOEL_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLBOERBOEL_MLLONGDOUBLE
#endif /* MLINTERFACE > 4 */
#elif WIN64_MATHLINK
#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLBICHON_FRISE_NUMERICS_ID

#define MLTK_CSHORT        MLBICHON_FRISE_CSHORT
#define MLTK_CINT          MLBICHON_FRISE_CINT
#define MLTK_CLONG         MLBICHON_FRISE_CLONG
#define MLTK_CINT64        MLBICHON_FRISE_CINT64
#define MLTK_CSIZE_T       MLBICHON_FRISE_CSIZE_T
#define MLTK_CFLOAT        MLBICHON_FRISE_CFLOAT
#define MLTK_CDOUBLE       MLBICHON_FRISE_CDOUBLE
#define MLTK_CLONGDOUBLE   MLBICHON_FRISE_CLONGDOUBLE

#define MLTK_MLSHORT       MLBICHON_FRISE_MLSHORT
#define MLTK_MLINT         MLBICHON_FRISE_MLINT
#define MLTK_MLLONG        MLBICHON_FRISE_MLLONG
#define MLTK_MLINT64       MLBICHON_FRISE_MLINT64
#define MLTK_MLSIZE_T      MLBICHON_FRISE_MLSIZE_T
#define MLTK_MLFLOAT       MLBICHON_FRISE_MLFLOAT
#define MLTK_MLDOUBLE      MLBICHON_FRISE_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLBICHON_FRISE_MLLONGDOUBLE
#endif /* WIN32_MATHLINK || WIN64_MATHLINK */

#elif DARWIN_MATHLINK

#if X86_DARWIN_MATHLINK
#if MLINTERFACE < 4
#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLBASENJI_NUMERICS_ID

#define MLTK_CSHORT        MLBASENJI_CSHORT
#define MLTK_CINT          MLBASENJI_CINT
#define MLTK_CLONG         MLBASENJI_CLONG
#define MLTK_CINT64        MLBASENJI_CINT64
#define MLTK_CSIZE_T       MLBASENJI_CSIZE_T
#define MLTK_CFLOAT        MLBASENJI_CFLOAT
#define MLTK_CDOUBLE       MLBASENJI_CDOUBLE
#define MLTK_CLONGDOUBLE   MLBASENJI_CLONGDOUBLE

#define MLTK_MLSHORT       MLBASENJI_MLSHORT
#define MLTK_MLINT         MLBASENJI_MLINT
#define MLTK_MLLONG        MLBASENJI_MLLONG
#define MLTK_MLINT64       MLBASENJI_MLINT64
#define MLTK_MLSIZE_T      MLBASENJI_MLSIZE_T
#define MLTK_MLFLOAT       MLBASENJI_MLFLOAT
#define MLTK_MLDOUBLE      MLBASENJI_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLBASENJI_MLLONGDOUBLE
#endif /* MLINTERFACE < 4 */

#if MLINTERFACE >= 4
#define MATHLINK_NUMERICS_ENVIRONMENT_ID MLBEAUCERON_NUMERICS_ID

#define MLTK_CSHORT        MLBEAUCERON_CSHORT
#define MLTK_CINT          MLBEAUCERON_CINT
#define MLTK_CLONG         MLBEAUCERON_CLONG
#define MLTK_CINT64        MLBEAUCERON_CINT64
#define MLTK_CSIZE_T       MLBEAUCERON_CSIZE_T
#define MLTK_CFLOAT        MLBEAUCERON_CFLOAT
#define MLTK_CDOUBLE       MLBEAUCERON_CDOUBLE
#define MLTK_CLONGDOUBLE   MLBEAUCERON_CLONGDOUBLE

#define MLTK_MLSHORT       MLBEAUCERON_MLSHORT
#define MLTK_MLINT         MLBEAUCERON_MLINT
#define MLTK_MLLONG        MLBEAUCERON_MLLONG
#define MLTK_MLINT64       MLBEAUCERON_MLINT64
#define MLTK_MLSIZE_T      MLBEAUCERON_MLSIZE_T
#define MLTK_MLFLOAT       MLBEAUCERON_MLFLOAT
#define MLTK_MLDOUBLE      MLBEAUCERON_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLBEAUCERON_MLLONGDOUBLE

#endif /* MLINTERFACE >= 4 */
#elif X86_64_DARWIN_MATHLINK
#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLGREATDANE_NUMERICS_ID

#define MLTK_CSHORT        MLGREATDANE_CSHORT
#define MLTK_CINT          MLGREATDANE_CINT
#define MLTK_CLONG         MLGREATDANE_CLONG
#define MLTK_CINT64        MLGREATDANE_CINT64
#define MLTK_CSIZE_T       MLGREATDANE_CSIZE_T
#define MLTK_CFLOAT        MLGREATDANE_CFLOAT
#define MLTK_CDOUBLE       MLGREATDANE_CDOUBLE
#define MLTK_CLONGDOUBLE   MLGREATDANE_CLONGDOUBLE

#define MLTK_MLSHORT       MLGREATDANE_MLSHORT
#define MLTK_MLINT         MLGREATDANE_MLINT
#define MLTK_MLLONG        MLGREATDANE_MLLONG
#define MLTK_MLINT64       MLGREATDANE_MLINT64
#define MLTK_MLSIZE_T      MLGREATDANE_MLSIZE_T
#define MLTK_MLFLOAT       MLGREATDANE_MLFLOAT
#define MLTK_MLDOUBLE      MLGREATDANE_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLGREATDANE_MLLONGDOUBLE

#elif ARM_DARWIN_MATHLINK
#define MATHLINK_NUMERICS_ENVIRONMENT_ID MLSHARPEI_NUMERICS_ID

#define MLTK_CSHORT        MLSHARPEI_CSHORT
#define MLTK_CINT          MLSHARPEI_CINT
#define MLTK_CLONG         MLSHARPEI_CLONG
#define MLTK_CINT64        MLSHARPEI_CINT64
#define MLTK_CSIZE_T       MLSHARPEI_CSIZE_T
#define MLTK_CFLOAT        MLSHARPEI_CFLOAT
#define MLTK_CDOUBLE       MLSHARPEI_CDOUBLE
#define MLTK_CLONGDOUBLE   MLSHARPEI_CLONGDOUBLE

#define MLTK_MLSHORT       MLSHARPEI_MLSHORT
#define MLTK_MLINT         MLSHARPEI_MLINT
#define MLTK_MLLONG        MLSHARPEI_MLLONG
#define MLTK_MLINT64       MLSHARPEI_MLINT64
#define MLTK_MLSIZE_T      MLSHARPEI_MLSIZE_T
#define MLTK_MLFLOAT       MLSHARPEI_MLFLOAT
#define MLTK_MLDOUBLE      MLSHARPEI_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLSHARPEI_MLLONGDOUBLE
#elif ARM64_DARWIN_MATHLINK
#define MATHLINK_NUMERICS_ENVIRONMENT_ID MLTIBETANMASTIFF_NUMERICS_ID

#define MLTK_CSHORT        MLTIBETANMASTIFF_CSHORT
#define MLTK_CINT          MLTIBETANMASTIFF_CINT
#define MLTK_CLONG         MLTIBETANMASTIFF_CLONG
#define MLTK_CINT64        MLTIBETANMASTIFF_CINT64
#define MLTK_CSIZE_T       MLTIBETANMASTIFF_CSIZE_T
#define MLTK_CFLOAT        MLTIBETANMASTIFF_CFLOAT
#define MLTK_CDOUBLE       MLTIBETANMASTIFF_CDOUBLE
#define MLTK_CLONGDOUBLE   MLTIBETANMASTIFF_CLONGDOUBLE

#define MLTK_MLSHORT       MLTIBETANMASTIFF_MLSHORT
#define MLTK_MLINT         MLTIBETANMASTIFF_MLINT
#define MLTK_MLLONG        MLTIBETANMASTIFF_MLLONG
#define MLTK_MLINT64       MLTIBETANMASTIFF_MLINT64
#define MLTK_MLSIZE_T      MLTIBETANMASTIFF_MLSIZE_T
#define MLTK_MLFLOAT       MLTIBETANMASTIFF_MLFLOAT
#define MLTK_MLDOUBLE      MLTIBETANMASTIFF_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLTIBETANMASTIFF_MLLONGDOUBLE
#endif

#elif I86_LINUX_MATHLINK
#if MLINTERFACE < 4
#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLREDDOG_NUMERICS_ID

#define MLTK_CSHORT        MLREDDOG_CSHORT
#define MLTK_CINT          MLREDDOG_CINT
#define MLTK_CLONG         MLREDDOG_CLONG
#define MLTK_CINT64        MLREDDOG_CINT64
#define MLTK_CSIZE_T       MLREDDOG_CSIZE_T
#define MLTK_CFLOAT        MLREDDOG_CFLOAT
#define MLTK_CDOUBLE       MLREDDOG_CDOUBLE
#define MLTK_CLONGDOUBLE   MLREDDOG_CLONGDOUBLE

#define MLTK_MLSHORT       MLREDDOG_MLSHORT
#define MLTK_MLINT         MLREDDOG_MLINT
#define MLTK_MLLONG        MLREDDOG_MLLONG
#define MLTK_MLINT64       MLREDDOG_MLINT64
#define MLTK_MLSIZE_T      MLREDDOG_MLSIZE_T
#define MLTK_MLFLOAT       MLREDDOG_MLFLOAT
#define MLTK_MLDOUBLE      MLREDDOG_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLREDDOG_MLLONGDOUBLE
#endif /* MLINTERFACE < 4 */

#if MLINTERFACE >= 4
#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLBERGAMASCO_NUMERICS_ID

#define MLTK_CSHORT        MLBERGAMASCO_CSHORT
#define MLTK_CINT          MLBERGAMASCO_CINT
#define MLTK_CLONG         MLBERGAMASCO_CLONG
#define MLTK_CINT64        MLBERGAMASCO_CINT64
#define MLTK_CSIZE_T       MLBERGAMASCO_CSIZE_T
#define MLTK_CFLOAT        MLBERGAMASCO_CFLOAT
#define MLTK_CDOUBLE       MLBERGAMASCO_CDOUBLE
#define MLTK_CLONGDOUBLE   MLBERGAMASCO_CLONGDOUBLE

#define MLTK_MLSHORT       MLBERGAMASCO_MLSHORT
#define MLTK_MLINT         MLBERGAMASCO_MLINT
#define MLTK_MLLONG        MLBERGAMASCO_MLLONG
#define MLTK_MLINT64       MLBERGAMASCO_MLINT64
#define MLTK_MLSIZE_T      MLBERGAMASCO_MLSIZE_T
#define MLTK_MLFLOAT       MLBERGAMASCO_MLFLOAT
#define MLTK_MLDOUBLE      MLBERGAMASCO_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLBERGAMASCO_MLLONGDOUBLE
#endif /* MLINTERFACE >= 4 */

#elif X86_64_LINUX_MATHLINK
#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLBOXER_NUMERICS_ID

#define MLTK_CSHORT        MLBOXER_CSHORT
#define MLTK_CINT          MLBOXER_CINT
#define MLTK_CLONG         MLBOXER_CLONG
#define MLTK_CINT64        MLBOXER_CINT64
#define MLTK_CSIZE_T       MLBOXER_CSIZE_T
#define MLTK_CFLOAT        MLBOXER_CFLOAT
#define MLTK_CDOUBLE       MLBOXER_CDOUBLE
#define MLTK_CLONGDOUBLE   MLBOXER_CLONGDOUBLE

#define MLTK_MLSHORT       MLBOXER_MLSHORT
#define MLTK_MLINT         MLBOXER_MLINT
#define MLTK_MLLONG        MLBOXER_MLLONG
#define MLTK_MLINT64       MLBOXER_MLINT64
#define MLTK_MLSIZE_T      MLBOXER_MLSIZE_T
#define MLTK_MLFLOAT       MLBOXER_MLFLOAT
#define MLTK_MLDOUBLE      MLBOXER_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLBOXER_MLLONGDOUBLE

#elif ARM_LINUX_MATHLINK
#if MLINTERFACE < 4
#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLCHIHUAHUA_NUMERICS_ID

#define MLTK_CSHORT        MLCHIHUAHUA_CSHORT
#define MLTK_CINT          MLCHIHUAHUA_CINT
#define MLTK_CLONG         MLCHIHUAHUA_CLONG
#define MLTK_CINT64        MLCHIHUAHUA_CINT64
#define MLTK_CSIZE_T       MLCHIHUAHUA_CSIZE_T
#define MLTK_CFLOAT        MLCHIHUAHUA_CFLOAT
#define MLTK_CDOUBLE       MLCHIHUAHUA_CDOUBLE
#define MLTK_CLONGDOUBLE   MLCHIHUAHUA_CLONGDOUBLE

#define MLTK_MLSHORT       MLCHIHUAHUA_MLSHORT
#define MLTK_MLINT         MLCHIHUAHUA_MLINT
#define MLTK_MLLONG        MLCHIHUAHUA_MLLONG
#define MLTK_MLINT64       MLCHIHUAHUA_MLINT64
#define MLTK_MLSIZE_T      MLCHIHUAHUA_MLSIZE_T
#define MLTK_MLFLOAT       MLCHIHUAHUA_MLFLOAT
#define MLTK_MLDOUBLE      MLCHIHUAHUA_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLCHIHUAHUA_MLLONGDOUBLE
#else /* MLINTERFACE >= 4 */

#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLCHINOOK_NUMERICS_ID

#define MLTK_CSHORT        MLCHINOOK_CSHORT
#define MLTK_CINT          MLCHINOOK_CINT
#define MLTK_CLONG         MLCHINOOK_CLONG
#define MLTK_CINT64        MLCHINOOK_CINT64
#define MLTK_CSIZE_T       MLCHINOOK_CSIZE_T
#define MLTK_CFLOAT        MLCHINOOK_CFLOAT
#define MLTK_CDOUBLE       MLCHINOOK_CDOUBLE
#define MLTK_CLONGDOUBLE   MLCHINOOK_CLONGDOUBLE

#define MLTK_MLSHORT       MLCHINOOK_MLSHORT
#define MLTK_MLINT         MLCHINOOK_MLINT
#define MLTK_MLLONG        MLCHINOOK_MLLONG
#define MLTK_MLINT64       MLCHINOOK_MLINT64
#define MLTK_MLSIZE_T      MLCHINOOK_MLSIZE_T
#define MLTK_MLFLOAT       MLCHINOOK_MLFLOAT
#define MLTK_MLDOUBLE      MLCHINOOK_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLCHINOOK_MLLONGDOUBLE
#endif /* MLINTERFACE < 4 */

#else
#define MATHLINK_NUMERICS_ENVIRONMENT_ID  MLOLD_WIN_ENV_NUMERICS_ID

#define MLTK_CSHORT        MLOLD_WIN_ENV_CSHORT
#define MLTK_CINT          MLOLD_WIN_ENV_CINT
#define MLTK_CLONG         MLOLD_WIN_ENV_CLONG
#define MLTK_CINT64        MLOLD_WIN_ENV_CINT64
#define MLTK_CSIZE_T       MLOLD_WIN_ENV_CSIZE_T
#define MLTK_CFLOAT        MLOLD_WIN_ENV_CFLOAT
#define MLTK_CDOUBLE       MLOLD_WIN_ENV_CDOUBLE
#define MLTK_CLONGDOUBLE   MLOLD_WIN_ENV_CLONGDOUBLE

#define MLTK_MLSHORT       MLOLD_WIN_ENV_MLSHORT
#define MLTK_MLINT         MLOLD_WIN_ENV_MLINT
#define MLTK_MLLONG        MLOLD_WIN_ENV_MLLONG
#define MLTK_MLINT64       MLOLD_WIN_ENV_MLINT64
#define MLTK_MLSIZE_T      MLOLD_WIN_ENV_MLSIZE_T
#define MLTK_MLFLOAT       MLOLD_WIN_ENV_MLFLOAT
#define MLTK_MLDOUBLE      MLOLD_WIN_ENV_MLDOUBLE
#define MLTK_MLLONGDOUBLE  MLOLD_WIN_ENV_MLLONGDOUBLE

#endif

/* Objects of these numeric types exist in MathLink only in the numerics
 * environment and, unfortunately, in the "stack frames" of the functions that
 * put atomic numbers like MLPutInteger.  These C types are used by client
 * programs solely for type-checked access to the BinaryNumber functions.
 */
typedef unsigned char uchar_nt;
typedef uchar_nt     FAR * ucharp_nt;
typedef ucharp_nt    FAR * ucharpp_nt;

typedef short              short_nt;
typedef short_nt     FAR * shortp_nt;
typedef shortp_nt    FAR * shortpp_nt;

typedef int                int_nt;
typedef int_nt       FAR * intp_nt;
typedef intp_nt      FAR * intpp_nt;

typedef long               long_nt;
typedef long_nt      FAR * longp_nt;
typedef longp_nt     FAR * longpp_nt;

typedef mlint64            int64_nt;
typedef int64_nt         * int64p_nt;
typedef int64p_nt        * int64pp_nt;

typedef float              float_nt;
typedef float_nt     FAR * floatp_nt;
typedef floatp_nt    FAR * floatpp_nt;

typedef double             double_nt;
typedef double_nt    FAR * doublep_nt;
typedef doublep_nt   FAR * doublepp_nt;

#ifndef CC_SUPPORTS_LONG_DOUBLE
#if defined( __STDC__) || defined(__cplusplus) || ! UNIX_MATHLINK
#define CC_SUPPORTS_LONG_DOUBLE 1
#else

#define CC_SUPPORTS_LONG_DOUBLE MLPROTOTYPES
#endif
#endif

struct _i87extended_nt { unsigned short w[5];};

#if CC_SUPPORTS_LONG_DOUBLE
#ifndef __extended_nt__
#if WINDOWS_MATHLINK && (MLTK_CLONGDOUBLE != MLTK_MLLONGDOUBLE) /* subtle predicate that works for old and new windows numenvs */
#define __extended_nt__ struct _i87extended_nt
#define EXTENDED_NT_TO_I87_EXTENDED(a,b) a = b
#define I87_EXTENDED_TO_EXTENDED_NT(a,b) a = b
#else
#define __extended_nt__ long double
#define EXTENDED_NT_TO_I87_EXTENDED(a,b) \
				{ \
					int i; \
					unsigned short *c = (unsigned short *)&b; \
					for(i = 0; i < 5; i++) a.w[i] = 0; \
					for(i = 1; i < 5; i++) a.w[i] = *(c + i); \
				}
#define I87_EXTENDED_TO_EXTENDED_NT(a,b) \
				{ \
					int i; \
					unsigned short *c = (unsigned short *)&a; \
					a = 0; \
					for(i = 1; i < 5; i++) *(c + i) = b.w[i]; \
				}
#endif
#endif

	typedef __extended_nt__    mlextended_double;

	typedef __extended_nt__    extended_nt;
	typedef extended_nt  FAR * extendedp_nt;
	typedef extendedp_nt FAR * extendedpp_nt;
#endif /* CC_SUPPORTS_LONG_DOUBLE */

#endif /* _MLNTYPES_H */




#endif /* MLGETNUMBERS_HPP */


/* explicitly not protected by MLGETNUMBERS_HPP in case MLDECL is redefined for multiple inclusion */


ML_EXTERN_C

MLDECL( int,   MLGetBinaryNumber,  ( MLINK mlp, void *np, long type));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:

MLGetShortInteger   - MLGetInteger16
MLGetInteger        - MLGetInteger32
MLGetLongInteger    - MLGetInteger64 for 64-bit integers or MLGetInteger32 for 32-bit integers
*/
MLDECL( int,   MLGetShortInteger,  ( MLINK mlp, short *hp));
MLDECL( int,   MLGetInteger,       ( MLINK mlp, int *ip));
MLDECL( int,   MLGetLongInteger,   ( MLINK mlp, long *lp));


MLDECL( int,   MLGetInteger16,  ( MLINK mlp, short *hp));
MLDECL( int,   MLGetInteger32,  ( MLINK mlp, int *ip));
MLDECL( int,   MLGetInteger64,  ( MLINK mlp, mlint64 *wp));


#if MLINTERFACE >= 4
MLDECL(int, MLGetInteger8, (MLINK mlp, unsigned char *cp));
#endif


/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:

MLGetFloat      - MLGetReal32
MLGetDouble     - MLGetReal64
MLGetReal       - MLGetReal64
MLGetLongDouble - MLGetReal128
*/
MLDECL( int,   MLGetFloat,         ( MLINK mlp, float *fp));
MLDECL( int,   MLGetDouble,        ( MLINK mlp, double *dp));
MLDECL( int,   MLGetReal,          ( MLINK mlp, double *dp));
#if CC_SUPPORTS_LONG_DOUBLE
MLDECL( int,   MLGetLongDouble,    ( MLINK mlp, mlextended_double *xp));
#endif


MLDECL( int,   MLGetReal32,         ( MLINK mlp, float *fp));
MLDECL( int,   MLGetReal64,        ( MLINK mlp, double *dp));
MLDECL( int,   MLGetReal128,          ( MLINK mlp, mlextended_double *dp));

ML_END_EXTERN_C




#ifndef MLGETSTRINGS_HPP
#define MLGETSTRINGS_HPP







#endif /* MLGETSTRINGS_HPP */

/* explicitly not protected by MLGETSTRINGS_HPP in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C

/*
As of MLINTERFACE 3 MLGet16BitCharacters has been deprecated.  Use the suggested function in its
place:

MLGet16BitCharacters   - MLGetUCS2Characters
*/

#if MLINTERFACE == 3
MLDECL( int,   MLGet16BitCharacters,  ( MLINK mlp, long *chars_left, unsigned short *buf, long cardof_buf, long *got));
#endif

MLDECL( int,   MLGet8BitCharacters,   ( MLINK mlp, long *chars_left, unsigned char *buf, long cardof_buf, long *got, long missing));
MLDECL( int,   MLGet7BitCharacters,   ( MLINK mlp, long *chars_left, char *buf, long cardof_buf, long *got));

MLDECL( int,   MLGetUCS2Characters,   ( MLINK mlp, int *chars_left, unsigned short *buf, int cardof_buf, int *got));
MLDECL( int,   MLGetUTF8Characters,   ( MLINK mlp, int *chars_left, unsigned char *buf, int cardof_buf, int *got));
MLDECL( int,   MLGetUTF16Characters,  ( MLINK mlp, int *chars_left, unsigned short *buf, int cardof_buf, int *got));
MLDECL( int,   MLGetUTF32Characters,  ( MLINK mlp, int *chars_left, unsigned int *buf, int cardof_buf, int *got));

/*
As of MLINTERFACE 3 MLGetUnicodeString has been deprecated.  Use the suggested function in its
place:

MLGetUnicodeString - MLGetUCS2String
*/

#if MLINTERFACE == 3
MLDECL( int,   MLGetUnicodeString,    ( MLINK mlp, const unsigned short **sp, long *lenp));
#endif

MLDECL( int,   MLGetByteString,       ( MLINK mlp, const unsigned char **sp, int *lenp, long missing));
MLDECL( int,   MLGetString,           ( MLINK mlp, const char **sp));

MLDECL( int,   MLGetUCS2String,       ( MLINK mlp, const unsigned short **sp, int *lenp));
MLDECL( int,   MLGetUTF8String,       ( MLINK mlp, const unsigned char **sp, int *bytes, int *chars));
MLDECL( int,   MLGetUTF16String,      ( MLINK mlp, const unsigned short **sp, int *ncodes, int *chars));
MLDECL( int,   MLGetUTF32String,      ( MLINK mlp, const unsigned int **sp, int *len));

#ifndef MLINTERFACE
/*\ syntax\ error\ */\ )
#endif

/*
As of MLINTERFACE 3 MLGetUnicodeString0 has been deprecated.  Use the suggested function in its
place:

MLGetUnicodeString0 - MLGetUCS2String0
*/

#if MLINTERFACE >= 4

MLDECL( int,   MLGetNumberAsByteString,      ( MLINK mlp, const unsigned char **sp, long *lenp, long missing));
MLDECL( int,   MLGetNumberAsString,          ( MLINK mlp, const char **sp));

MLDECL( int,   MLGetNumberAsUCS2String,      ( MLINK mlp, const unsigned short **sp, int *lenp));
MLDECL( int,   MLGetNumberAsUTF8String,      ( MLINK mlp, const unsigned char **sp, int *bytes, int *chars));
MLDECL( int,   MLGetNumberAsUTF16String,     ( MLINK mlp, const unsigned short **sp, int *ncodes, int *chars));
MLDECL( int,   MLGetNumberAsUTF32String,     ( MLINK mlp, const unsigned int **sp, int *lenp));
#else
MLDECL( int,   MLGetUnicodeString0,   ( MLINK mlp, const unsigned short **sp, long *lenp));
MLDECL( int,   MLGetByteString0,      ( MLINK mlp, const unsigned char **sp, long *lenp, long missing));
MLDECL( int,   MLGetString0,          ( MLINK mlp, const char **sp));

MLDECL( int,   MLGetUCS2String0,      ( MLINK mlp, const unsigned short **sp, int *lenp));
MLDECL( int,   MLGetUTF8String0,      ( MLINK mlp, const unsigned char **sp, int *bytes, int *chars));
MLDECL( int,   MLGetUTF16String0,     ( MLINK mlp, const unsigned short **sp, int *ncodes, int *chars));
MLDECL( int,   MLGetUTF32String0,     ( MLINK mlp, const unsigned int **sp, int *lenp));
#endif /* MLINTERFACE >= 4 */


/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:

MLDisownUnicodeString - MLReleaseUCS2String
MLDisownByteString    - MLReleaseByteString
MLDisownString        - MLReleaseString
*/

#if MLINTERFACE == 3
MLDECL( void,           MLDisownUnicodeString, ( MLINK mlp, const unsigned short *s,   long len));
MLDECL( void,           MLDisownByteString,    ( MLINK mlp, const unsigned char * s,   long len));
MLDECL( void,           MLDisownString,        ( MLINK mlp, const char *s));
#endif

MLDECL( void,           MLReleaseUCS2String,   ( MLINK mlp, const unsigned short *s,   int len));
MLDECL( void,           MLReleaseUTF8String,   ( MLINK mlp, const unsigned char *s, int len));
MLDECL( void,           MLReleaseUTF16String,  ( MLINK mlp, const unsigned short *s, int len));
MLDECL( void,           MLReleaseUTF32String,  ( MLINK mlp, const unsigned int *s, int len));
MLDECL( void,           MLReleaseByteString,   ( MLINK mlp, const unsigned char * s,   int len));
MLDECL( void,           MLReleaseString,       ( MLINK mlp, const char *s));

#if MLINTERFACE <= 3
MLDECL( int,   MLCheckString,   ( MLINK mlp, const char *name));
#endif

#if MLINTERFACE >= 4
MLDECL( int,    MLTestString,      ( MLINK mlp, const char *name));
MLDECL( int,    MLTestUCS2String,  ( MLINK mlp, const unsigned short *name, int length));
MLDECL( int,    MLTestUTF8String,  ( MLINK mlp, const unsigned char *name, int length));
MLDECL( int,    MLTestUTF16String, ( MLINK mlp, const unsigned short *name, int length));
MLDECL( int,    MLTestUTF32String, ( MLINK mlp, const unsigned int *name, int length));
#endif // MLINTERFACE >= 4

ML_END_EXTERN_C




#ifndef MLGETSYMBOLS_HPP
#define MLGETSYMBOLS_HPP







#endif /* MLGETSYMBOLS_HPP */

/* explicitly not protected by MLGETSYMBOLS_HPP in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C

/*
As of MLINTERFACE 3 MLGetUnicodeSymbol has been deprecated.  Use the suggested function in its
place:

MLGetUnicodeSymbol - MLGetUCS2Symbol
*/

#if MLINTERFACE == 3
MLDECL( int,   MLGetUnicodeSymbol,    ( MLINK mlp, const unsigned short **sp, long *lenp));
#endif

MLDECL( int,   MLGetByteSymbol,       ( MLINK mlp, const unsigned char ** sp, int *lenp, long missing));
MLDECL( int,   MLGetSymbol,           ( MLINK mlp, const char **          sp));

MLDECL( int,   MLGetUCS2Symbol,       ( MLINK mlp, const unsigned short **sp, int *lenp));
MLDECL( int,   MLGetUTF8Symbol,       ( MLINK mlp, const unsigned char **sp, int *bytes, int *chars));
MLDECL( int,   MLGetUTF16Symbol,      ( MLINK mlp, const unsigned short **sp, int *ncodes, int *chars));
MLDECL( int,   MLGetUTF32Symbol,      ( MLINK mlp, const unsigned int **sp, int *lenp));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:
MLDisownUnicodeSymbol - MLReleaseUCS2Symbol
MLDisownByteSymbol    - MLReleaseByteSymbol
MLDisownSymbol        - MLReleaseSymbol
*/

#if MLINTERFACE == 3
MLDECL( void,           MLDisownUnicodeSymbol, ( MLINK mlp, const unsigned short *s,   long len));
MLDECL( void,           MLDisownByteSymbol,    ( MLINK mlp, const unsigned char * s,   long len));
MLDECL( void,           MLDisownSymbol,        ( MLINK mlp, const char *s));
#endif

MLDECL( void,           MLReleaseUCS2Symbol,   ( MLINK mlp, const unsigned short *s,   int len));
MLDECL( void,           MLReleaseUTF8Symbol,   ( MLINK mlp, const unsigned char *s, int len));
MLDECL( void,           MLReleaseUTF16Symbol,  ( MLINK mlp, const unsigned short *s, int len));
MLDECL( void,           MLReleaseUTF32Symbol,  ( MLINK mlp, const unsigned int *s, int len));
MLDECL( void,           MLReleaseByteSymbol,   ( MLINK mlp, const unsigned char * s,   int len));
MLDECL( void,           MLReleaseSymbol,       ( MLINK mlp, const char *s));

#if MLINTERFACE == 3
MLDECL( int,            MLCheckSymbol,         ( MLINK mlp, const char *name));
#endif

#if MLINTERFACE >= 4
MLDECL( int,            MLTestSymbol,          ( MLINK mlp, const char *name));
MLDECL( int,            MLTestUCS2Symbol,      ( MLINK mlp, const unsigned short *name, int length));
MLDECL( int,            MLTestUTF8Symbol,      ( MLINK mlp, const unsigned char *name, int length));
MLDECL( int,            MLTestUTF16Symbol,     ( MLINK mlp, const unsigned short *name, int length));
MLDECL( int,            MLTestUTF32Symbol,     ( MLINK mlp, const unsigned int *name, int length));
#endif

MLDECL( int,            MLGetFunction,         ( MLINK mlp, const char **sp, int *countp));

#if MLINTERFACE >= 4
MLDECL( int,            MLGetUCS2Function,     ( MLINK mlp, const unsigned short **sp, int *length, int *countp));
MLDECL( int,            MLGetUTF8Function,     ( MLINK mlp, const unsigned char **sp, int *length, int *countp));
MLDECL( int,            MLGetUTF16Function,    ( MLINK mlp, const unsigned short **sp, int *length, int *countp));
MLDECL( int,            MLGetUTF32Function,    ( MLINK mlp, const unsigned int **sp, int *length, int *countp));
#endif

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:

MLCheckFunction             - MLTestHead
MLCheckFunctionWithArgCount - MLTestHead
*/

MLDECL( int,   MLCheckFunction, ( MLINK mlp, const char *s, long *countp));
MLDECL( int,   MLCheckFunctionWithArgCount, ( MLINK mlp, const char *s, long *countp));

MLDECL( int,   MLTestHead,      ( MLINK mlp, const char *s, int *countp));

#if MLINTERFACE >= 4

/*
For a limited time convenience define the following:
*/

MLDECL( int,      MLTestHeadWithArgCount, (MLINK mlp, const char *s, int *countp));
MLDECL( int,  MLTestUCS2HeadWithArgCount, (MLINK mlp, const unsigned short *s, int length, int *countp));
MLDECL( int, MLTestUTF16HeadWithArgCount, (MLINK mlp, const unsigned short *s, int length, int *countp));
MLDECL( int, MLTestUTF32HeadWithArgCount, (MLINK mlp, const unsigned int *s, int length, int *countp));
MLDECL( int,  MLTestUTF8HeadWithArgCount, (MLINK mlp, const unsigned char *s, int length, int *countp));

MLDECL( int,   MLTestUCS2Head,  ( MLINK mlp, const unsigned short *s, int length, int *countp));
MLDECL( int,   MLTestUTF8Head,  ( MLINK mlp, const unsigned char *s, int length, int *countp));
MLDECL( int,   MLTestUTF16Head, ( MLINK mlp, const unsigned short *s, int length, int *countp));
MLDECL( int,   MLTestUTF32Head, ( MLINK mlp, const unsigned int *s, int length, int *countp));
#endif // MLINTERFACE >= 4

ML_END_EXTERN_C






#ifndef MLPUTNUMBERS_HPP
#define MLPUTNUMBERS_HPP







#endif /* MLPUTNUMBERS_HPP */


/* explicitly not protected by MLPUTNUMBERS_HPP in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C

MLDECL( int,   MLPutBinaryNumber,  ( MLINK mlp, void *np, long type));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the following new functions as their replacement:

MLPutShortInteger  - MLPutInteger16
MLPutInteger       - MLPutInteger32
MLPutLongInteger   - MLPutInteger64 for 64-bit integers or MLPutInteger32 for 32-bit integers.
*/
MLDECL( int,   MLPutShortInteger,  ( MLINK mlp, int h));
MLDECL( int,   MLPutInteger,       ( MLINK mlp, int i));
MLDECL( int,   MLPutLongInteger,   ( MLINK mlp, long l));

MLDECL( int,   MLPutInteger16,     ( MLINK mlp, int h));
MLDECL( int,   MLPutInteger32,     ( MLINK mlp, int i));
MLDECL( int,   MLPutInteger64,     ( MLINK mlp, mlint64 w));

#if MLINTERFACE >= 4
MLDECL( int, MLPutInteger8,   (MLINK mlp, unsigned char i));
#endif

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the following new functions as their replacement:

MLPutFloat      - MLPutReal32
MLPutDouble     - MLPutReal64
MLPutReal       - MLPutReal64
MLPutLongDouble - MLPutReal128
*/
MLDECL( int,   MLPutFloat,         ( MLINK mlp, double f));
MLDECL( int,   MLPutDouble,        ( MLINK mlp, double d));
MLDECL( int,   MLPutReal,          ( MLINK mlp, double d));
#if CC_SUPPORTS_LONG_DOUBLE
MLDECL( int,   MLPutLongDouble,    ( MLINK mlp, mlextended_double x));
#endif

MLDECL( int,   MLPutReal32,         ( MLINK mlp, double f));
MLDECL( int,   MLPutReal64,         ( MLINK mlp, double d));
MLDECL( int,   MLPutReal128,        ( MLINK mlp, mlextended_double x));

ML_END_EXTERN_C




#ifndef MLPUTSTRINGS_HPP
#define MLPUTSTRINGS_HPP








#endif /* MLPUTSTRINGS_HPP */

/* explicitly not protected by MLPUTSTRINGS_HPP in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C

/*
As of MLINTERFACE 3 MLPut16BitCharacters has been deprecated.  Use the suggested function in its
place:

MLPut16BitCharacters   - MLPutUCS2Characters
*/

#if MLINTERFACE == 3
MLDECL( int,   MLPut16BitCharacters, ( MLINK mlp, long chars_left, const unsigned short *codes, long ncodes));
#endif

MLDECL( int,   MLPut8BitCharacters,  ( MLINK mlp, long chars_left, const unsigned char *bytes, long nbytes));
MLDECL( int,   MLPut7BitCount,       ( MLINK mlp, long count, long size));
MLDECL( int,   MLPut7BitCharacters,  ( MLINK mlp, long chars_left, const char *bytes, long nbytes, long nchars_now));

MLDECL( int,   MLPutUCS2Characters,  ( MLINK mlp, int chars_left, const unsigned short *codes, int ncodes));
MLDECL( int,   MLPutUTF8Characters,  ( MLINK mlp, int chars_left, const unsigned char *codes, int ncodes));
MLDECL( int,   MLPutUTF16Characters, ( MLINK mlp, int chars_left, const unsigned short *codes, int ncodes));
MLDECL( int,   MLPutUTF32Characters, ( MLINK mlp, int chars_left, const unsigned int *codes, int ncodes));

/*
As of MLINTERFACE 3 MLPutUnicodeString has been deprecated.  Use the suggested function in its
place:

MLPutUnicodeString - MLPutUCS2String
*/

#if MLINTERFACE == 3
MLDECL( int,   MLPutUnicodeString, ( MLINK mlp, const unsigned short *s, long len));
#endif

MLDECL( int,   MLPutByteString,    ( MLINK mlp, const unsigned char *s, long len));
MLDECL( int,   MLPutString,        ( MLINK mlp, const char *s));

MLDECL( int,   MLPutUCS2String,    ( MLINK mlp, const unsigned short *s, int len));
MLDECL( int,   MLPutUTF8String,    ( MLINK mlp, const unsigned char *s, int len));
MLDECL( int,   MLPutUTF16String,   ( MLINK mlp, const unsigned short *s, int len));
MLDECL( int,   MLPutUTF32String,   ( MLINK mlp, const unsigned int *s, int len));

#ifndef MLINTERFACE
/*\ syntax\ error\ */\ )
#endif

/*
As of MLINTERFACE 3 MLPutRealUnicodeString0 has been deprecated.  Use the suggested function in its
place:

MLPutRealUnicodeString0 - MLPutRealUCS2String0
*/

#if MLINTERFACE >= 4
MLDECL( int,   MLPutRealNumberAsString,        ( MLINK mlp, const char *s));
MLDECL( int,   MLPutRealNumberAsByteString,    ( MLINK mlp, const unsigned char *s));
MLDECL( int,   MLPutRealNumberAsUCS2String,    ( MLINK mlp, const unsigned short *s));
MLDECL( int,   MLPutRealNumberAsUTF8String,    ( MLINK mlp, const unsigned char *s, int nbytes));
MLDECL( int,   MLPutRealNumberAsUTF16String,   ( MLINK mlp, const unsigned short *s, int ncodes));
MLDECL( int,   MLPutRealNumberAsUTF32String,   ( MLINK mlp, const unsigned int *s, int nchars));
#endif /* MLINTERFACE >= 4 */

#if MLINTERFACE == 3
MLDECL( int,   MLPutRealUnicodeString0, ( MLINK mlp, unsigned short *s));
MLDECL( int,   MLPutRealByteString0,    ( MLINK mlp, unsigned char *s));

MLDECL( int,   MLPutRealUCS2String0,    ( MLINK mlp, unsigned short *s));
MLDECL( int,   MLPutRealUTF8String0,    ( MLINK mlp, unsigned char *s, int nbytes));
MLDECL( int,   MLPutRealUTF16String0,   ( MLINK mlp, unsigned short *s, int ncodes));
MLDECL( int,   MLPutRealUTF32String0,   ( MLINK mlp, unsigned int *s, int nchars));
#endif /* MLINTERFACE == 3 */

MLDECL( int,   MLPutSize,          ( MLINK mlp, int size));
MLDECL( int,   MLPutData,          ( MLINK mlp, const char *buff, int len));

ML_END_EXTERN_C




#ifndef MLPUTSYMBOLS_HPP
#define MLPUTSYMBOLS_HPP








#endif /* MLPUTSYMBOLS_HPP */

/* explicitly not protected by MLPUTSYMBOLS_HPP in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C

/*
As of MLINTERFACE 3 MLPutUnicodeSymbol has been deprecated.  Use the suggested function in its
place:

MLPutUnicodeSymbol - MLPutUCS2Symbol
*/

#if MLINTERFACE == 3
MLDECL( int,   MLPutUnicodeSymbol, ( MLINK mlp, const unsigned short *s, long len));
#endif

MLDECL( int,   MLPutByteSymbol,    ( MLINK mlp, const unsigned char *s, long len));
MLDECL( int,   MLPutSymbol,        ( MLINK mlp, const char *s));

MLDECL( int,   MLPutUCS2Symbol,    ( MLINK mlp, const unsigned short *s, int len));

MLDECL( int,   MLPutUTF8Symbol,    ( MLINK mlp, const unsigned char *s, int len));
MLDECL( int,   MLPutUTF16Symbol,   ( MLINK mlp, const unsigned short *s, int len));
MLDECL( int,   MLPutUTF32Symbol,   ( MLINK mlp, const unsigned int *s, int len));


MLDECL( int,   MLPutFunction,      ( MLINK mlp, const char *s, int argc));

#if MLINTERFACE >= 4
MLDECL( int,   MLPutUCS2Function,  ( MLINK mlp, const unsigned short *s, int length, int argn));
MLDECL( int,   MLPutUTF8Function,  ( MLINK mlp, const unsigned char *s, int length, int argn));
MLDECL( int,   MLPutUTF16Function, ( MLINK mlp, const unsigned short *s, int length, int argn));
MLDECL( int,   MLPutUTF32Function, ( MLINK mlp, const unsigned int *s, int length, int argn));
#endif // MLINTERFACE >= 4


ML_END_EXTERN_C




#ifndef _WSSTRING_H
#define _WSSTRING_H










#define MAX_BYTES_PER_OLD_CHARACTER 3
#if WSINTERFACE < 3
#define MAX_BYTES_PER_NEW_CHARACTER 6
#else
#define MAX_BYTES_PER_NEW_CHARACTER 10
#endif

#define WS_MAX_BYTES_PER_CHARACTER MAX_BYTES_PER_NEW_CHARACTER

/* for source code compatibility with earlier versions of MathLink */

typedef struct {
#if WSINTERFACE >= 3
	const char *str;
	const char *end;
#else
	kcharp_ct str;
	kcharp_ct end;
#endif /* WSINTERFACE >= 3 */
} WSStringPosition;

typedef WSStringPosition FAR * WSStringPositionPointer;

#define WSStringFirstPos(s,pos) WSStringFirstPosFun( s, &(pos))

#define WSforString( s, pos) \
	for( WSStringFirstPos(s,pos); WSStringCharacter( (pos).str, (pos).end) >= 0; WSNextCharacter(&(pos).str, (pos).end))

#define WSStringChar( pos) WSStringCharacter( (pos).str, (pos).end)

#define WSPutCharToString WSConvertCharacter


/* for internal use only */

typedef struct {
#if WSINTERFACE >= 3
	unsigned char *cc;
	int  mode;
	int  more;
	unsigned char *head;
#else
	ucharp_ct cc;
	int_ct  mode;
	int_ct  more;
	ucharp_ct head;
#endif /* WSINTERFACE >= 3 */
} WSOldStringPosition;

typedef WSOldStringPosition FAR * WSOldStringPositionPointer;


#define WSOldforString( s, pos) \
  for ( WSOldStringFirstPos( s, pos); (pos).more; WSOldStringNextPos( pos))

#define WSOldStringChar(pos) \
  ( ((pos).mode <= 1) ? (uint_ct)(*(ucharp_ct)((pos).cc)) : WSOldStringCharFun( &pos) )


#define WSOldStringFirstPos(s,pos) WSOldStringFirstPosFun( s, &(pos))

#define WSOldStringNextPos(pos)  ( \
	((pos).mode == 0) \
		? ((*(*(pos).cc ? ++(pos).cc : (pos).cc) ? 0 : ((pos).more = 0)), (pos).cc) \
		: WSOldStringNextPosFun( &pos) )

#endif /* _WSSTRING_H */




/* explicitly not protected by _WSXDATA_H in case WSDECL is redefined for multiple inclusion */

WS_EXTERN_C
/* assumes *startp aligned on char boundary, if n == -1, returns ~(char_count) */

#if WSINTERFACE >= 3
WSDECL( long, WSCharacterOffset,           ( const char **startp, const char *end, long n));
WSDECL( long, WSStringCharacter,           ( const char * start,  const char *end));
WSDECL( long, WSNextCharacter,             ( const char **startp, const char *end));
#else
WSDECL( long, WSCharacterOffset,           ( kcharpp_ct startp, kcharp_ct end, long n));
WSDECL( long, WSStringCharacter,           ( kcharp_ct  start,  kcharp_ct end));
WSDECL( long, WSNextCharacter,             ( kcharpp_ct startp, kcharp_ct end));
#endif /* WSINTERFACE >= 3 */


#ifndef WSINTERFACE
/*\ syntax\ error\ */\ )
#endif
#if WSINTERFACE > 1
#if WSINTERFACE >= 4
WSDECL( long, WSNextCharacterFromStringWithLength, (const char *str, long *indexp, long len));
#else
#if WSINTERFACE == 3
WSDECL( long, WSNextCharacter0,            ( const char *str, long *indexp, long len));
#else
WSDECL( long, WSNextCharacter0,            ( kcharp_ct str, longp_ct indexp, long len));
#endif /* WSINTERFACE == 3 */
#endif // WSINTERFACE >= 4
#endif // WSINTERFACE > 1

#if WSINTERFACE >= 3
WSDECL( long, WSConvertNewLine,            ( char **sp));
WSDECL( long, WSConvertCharacter,          ( unsigned long ch, char **sp));
WSDECL( long, WSConvertByteString,         ( unsigned char *codes, long len, char **strp, char *str_end));
WSDECL( long, WSConvertByteStringNL,       ( unsigned char *codes, long len, char **strp, char *str_end, unsigned long nl));
#if WSINTERFACE == 3
WSDECL( long, WSConvertUnicodeString,      ( unsigned short *codes, long len, char **strp, char *str_end));
WSDECL( long, WSConvertUnicodeStringNL,    ( unsigned short *codes, long len, char **strp, char *str_end, unsigned long nl));
#endif
WSDECL( long, WSConvertDoubleByteString,   ( unsigned char *codes, long len, char **strp, char *str_end));
WSDECL( long, WSConvertDoubleByteStringNL, ( unsigned char *codes, long len, char **strp, char *str_end, unsigned long nl));

WSDECL( long, WSConvertUCS2String,         ( unsigned short *codes, long len, char **strp, char *str_end));
WSDECL( long, WSConvertUCS2StringNL,       ( unsigned short *codes, long len, char **strp, char *str_end, unsigned long nl));
WSDECL( long, WSConvertUTF8String,         ( unsigned char *codes, long len, char **strp, char *str_end));
WSDECL( long, WSConvertUTF8StringNL,       ( unsigned char *codes, long len, char **strp, char *str_end, unsigned long nl));
WSDECL( long, WSConvertUTF16String,        ( unsigned short *codes, long len, char **strp, char *str_end));
WSDECL( long, WSConvertUTF16StringNL,      ( unsigned short *codes, long len, char **strp, char *str_end, unsigned long nl));
WSDECL( long, WSConvertUTF32String,        ( unsigned int *codes, long len, char **strp, char *str_end));
WSDECL( long, WSConvertUTF32StringNL,      ( unsigned int *codes, long len, char **strp, char *str_end, unsigned long nl));



#else
WSDECL( long, WSConvertNewLine,            ( charpp_ct sp));
WSDECL( long, WSConvertCharacter,          ( ulong_ct ch, charpp_ct sp));
WSDECL( long, WSConvertByteString,         ( ucharp_ct  codes, long len, charpp_ct strp, charp_ct str_end));
WSDECL( long, WSConvertByteStringNL,       ( ucharp_ct  codes, long len, charpp_ct strp, charp_ct str_end, ulong_ct nl));
WSDECL( long, WSConvertUnicodeString,      ( ushortp_ct codes, long len, charpp_ct strp, charp_ct str_end));
WSDECL( long, WSConvertUnicodeStringNL,    ( ushortp_ct codes, long len, charpp_ct strp, charp_ct str_end, ulong_ct nl));
WSDECL( long, WSConvertDoubleByteString,   ( ucharp_ct  codes, long len, charpp_ct strp, charp_ct str_end));
WSDECL( long, WSConvertDoubleByteStringNL, ( ucharp_ct  codes, long len, charpp_ct strp, charp_ct str_end, ulong_ct nl));
#endif /* WSINTERFACE >= 3 */







/* for source code compatibility with earlier versions of MathLink */
#if WSINTERFACE >= 3
WSDECL( const char *,     WSStringFirstPosFun,  ( const char *s, WSStringPositionPointer p));
#else
WSDECL( kcharp_ct,        WSStringFirstPosFun,  ( kcharp_ct s, WSStringPositionPointer p));
#endif /* WSINTERFACE >= 3 */

/* for internal use only */
#if WSINTERFACE >= 3
WSDECL( int,                WSOldPutCharToString,      ( unsigned int ch, char **sp));
WSDECL( unsigned char *,    WSOldStringNextPosFun,     ( WSOldStringPositionPointer p));
WSDECL( unsigned char *,    WSOldStringFirstPosFun,    ( char *s, WSOldStringPositionPointer p));
WSDECL( unsigned int,       WSOldStringCharFun,        ( WSOldStringPositionPointer p));
WSDECL( long,               WSOldConvertByteString,    ( unsigned char *codes, long len, char **strp, char *str_end));

#if WSINTERFACE == 3
WSDECL( long,               WSOldConvertUnicodeString, ( unsigned short *codes, long len, char **strp, char *str_end));
#endif

WSDECL( long,               WSOldConvertUCS2String,    ( unsigned short *codes, long len, char **strp, char *str_end));
#else
WSDECL( WSapi_result,       WSOldPutCharToString,      ( uint_ct ch, charpp_ct sp));
WSDECL( ucharp_ct,          WSOldStringNextPosFun,     ( WSOldStringPositionPointer p));
WSDECL( ucharp_ct,          WSOldStringFirstPosFun,    ( charp_ct s, WSOldStringPositionPointer p));
WSDECL( uint_ct,            WSOldStringCharFun,        ( WSOldStringPositionPointer p));
WSDECL( long,               WSOldConvertByteString,    ( ucharp_ct  codes, long len, charpp_ct strp, charp_ct str_end));
WSDECL( long,               WSOldConvertUnicodeString, ( ushortp_ct codes, long len, charpp_ct strp, charp_ct str_end));
#endif /* WSINTERFACE >= 3 */

/* Internal functions */
WSDECL( long, WSCharOffset,           ( const char **startp, const char *end, long n, int more));
WSDECL( long, WSNextChar,             ( const char **startp, const char *end, int more, int useSurrogates, int *wasSurrogatePair));


WS_END_EXTERN_C



#ifndef _MLCAPUT_H
#define _MLCAPUT_H






#ifndef MLINTERFACE
/*\ syntax\ error\ */\ )
#endif

#ifndef __array_meterp__
#define __array_meterp__
typedef struct array_meter FAR * array_meterp;
typedef array_meterp FAR * array_meterpp;
#endif


#endif /* _MLCAPUT_H */


/* explicitly not protected by _MLCAPUT_H in case MLDECL is redefined for multiple inclusion */

/*bugcheck: bugcheck need FAR here */
ML_EXTERN_C
MLDECL( int,   MLPutArray,                  ( MLINK mlp, array_meterp meterp));

#if MLINTERFACE >= 4
MLDECL( int,   MLPutBinaryNumberArrayData,  ( MLINK mlp, array_meterp meterp, const void *         datap, long count, long type));
MLDECL( int,   MLPutByteArrayData,          ( MLINK mlp, array_meterp meterp, const unsigned char *datap, long count));
MLDECL( int,   MLPutShortIntegerArrayData,  ( MLINK mlp, array_meterp meterp, const short *        datap, long count));
MLDECL( int,   MLPutIntegerArrayData,       ( MLINK mlp, array_meterp meterp, const int *          datap, long count));
MLDECL( int,   MLPutLongIntegerArrayData,   ( MLINK mlp, array_meterp meterp, const long *         datap, long count));

MLDECL( int,   MLPutInteger8ArrayData,      ( MLINK mlp, array_meterp meterp, const unsigned char * datap, int count));
MLDECL( int,   MLPutInteger16ArrayData,     ( MLINK mlp, array_meterp meterp, const short *        datap, int count));
MLDECL( int,   MLPutInteger32ArrayData,     ( MLINK mlp, array_meterp meterp, const int *          datap, int count));
MLDECL( int,   MLPutInteger64ArrayData,     ( MLINK mlp, array_meterp meterp, const mlint64 *      datap, int count));
#else
MLDECL( int,   MLPutBinaryNumberArrayData,  ( MLINK mlp, array_meterp meterp, void *         datap, long count, long type));
MLDECL( int,   MLPutByteArrayData,          ( MLINK mlp, array_meterp meterp, unsigned char *datap, long count));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the following new functions as their replacement:

MLPutShortIntegerArrayData  - MLPutInteger16ArrayData
MLPutIntegerArrayData       - MLPutInteger32ArrayData
MLPutLongIntegerArrayData   - MLPutInteger64ArrayData for 64-bit integers or MLPutInteger32ArrayData for 32-bit integers
*/
MLDECL( int,   MLPutShortIntegerArrayData,  ( MLINK mlp, array_meterp meterp, short *        datap, long count));
MLDECL( int,   MLPutIntegerArrayData,       ( MLINK mlp, array_meterp meterp, int *          datap, long count));
MLDECL( int,   MLPutLongIntegerArrayData,   ( MLINK mlp, array_meterp meterp, long *         datap, long count));

MLDECL( int,   MLPutInteger16ArrayData,     ( MLINK mlp, array_meterp meterp, short *        datap, int count));
MLDECL( int,   MLPutInteger32ArrayData,     ( MLINK mlp, array_meterp meterp, int *          datap, int count));
MLDECL( int,   MLPutInteger64ArrayData,     ( MLINK mlp, array_meterp meterp, mlint64 *      datap, int count));
#endif /* MLINTERFACE >= 4 */




#if MLINTERFACE >= 4
MLDECL( int,   MLPutFloatArrayData,         ( MLINK mlp, array_meterp meterp, const float * datap, long count));
MLDECL( int,   MLPutDoubleArrayData,        ( MLINK mlp, array_meterp meterp, const double *datap, long count));
#if CC_SUPPORTS_LONG_DOUBLE
MLDECL( int,   MLPutLongDoubleArrayData,    ( MLINK mlp, array_meterp meterp, const mlextended_double *datap, long count));
#endif

MLDECL( int,   MLPutReal32ArrayData,        ( MLINK mlp, array_meterp meterp, const float * datap, int count));
MLDECL( int,   MLPutReal64ArrayData,        ( MLINK mlp, array_meterp meterp, const double *datap, int count));
MLDECL( int,   MLPutReal128ArrayData,       ( MLINK mlp, array_meterp meterp, const mlextended_double *datap, int count));
#else
/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the following new functions as their replacement:

MLPutFloatArrayData      - MLPutReal32ArrayData
MLPutDoubleArrayData     - MLPutReal64ArrayData
MLPutLongDoubleArrayData - MLPutReal128ArrayData
*/
MLDECL( int,   MLPutFloatArrayData,         ( MLINK mlp, array_meterp meterp, float * datap, long count));
MLDECL( int,   MLPutDoubleArrayData,        ( MLINK mlp, array_meterp meterp, double *datap, long count));
#if CC_SUPPORTS_LONG_DOUBLE
MLDECL( int,   MLPutLongDoubleArrayData,    ( MLINK mlp, array_meterp meterp, mlextended_double *datap, long count));
#endif

MLDECL( int,   MLPutReal32ArrayData,        ( MLINK mlp, array_meterp meterp, float * datap, int count));
MLDECL( int,   MLPutReal64ArrayData,        ( MLINK mlp, array_meterp meterp, double *datap, int count));
MLDECL( int,   MLPutReal128ArrayData,       ( MLINK mlp, array_meterp meterp, mlextended_double *datap, int count));
#endif /* MLINTERFACE >= 4 */

#ifndef ML_USES_NEW_PUTBYTEARRAY_API
#define ML_USES_NEW_PUTBYTEARRAY_API 1
#endif


#if MLINTERFACE >= 4
MLDECL( int,   MLPutBinaryNumberArray,  ( MLINK mlp, const void *         data, const long *dimp, const char **heads, long depth, long type));
MLDECL( int,   MLPutByteArray,          ( MLINK mlp, const unsigned char *data, const int *dims, const char **heads, int depth));
MLDECL( int,   MLPutShortIntegerArray,  ( MLINK mlp, const short *        data, const long *dims, const char **heads, long depth));
MLDECL( int,   MLPutIntegerArray,       ( MLINK mlp, const int *          data, const long *dims, const char **heads, long depth));
MLDECL( int,   MLPutLongIntegerArray,   ( MLINK mlp, const long *         data, const long *dims, const char **heads, long depth));

MLDECL( int,   MLPutInteger8Array,      ( MLINK mlp, const unsigned char *data, const int *dims, const char **heads, int depth));
MLDECL( int,   MLPutInteger16Array,     ( MLINK mlp, const short *        data, const int *dims, const char **heads, int depth));
MLDECL( int,   MLPutInteger32Array,     ( MLINK mlp, const int *          data, const int *dims, const char **heads, int depth));
MLDECL( int,   MLPutInteger64Array,     ( MLINK mlp, const mlint64 *      data, const int *dims, const char **heads, int depth));
#else
MLDECL( int,   MLPutBinaryNumberArray,  ( MLINK mlp, void *         data, long *dimp, char **heads, long depth, long type));
MLDECL( int,   MLPutByteArray,          ( MLINK mlp, unsigned char *data, int *dims, char **heads, int depth));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the following new functions as their replacement:

MLPutShortIntegerArray  - MLPutInteger16Array
MLPutIntegerArray       - MLPutInteger32Array
MLPutLongIntegerArray   - MLPutInteger64Array for 64-bit integers or MLPutInteger32Array for 32-bit integers
*/
MLDECL( int,   MLPutShortIntegerArray,  ( MLINK mlp, short *        data, long *dims, char **heads, long depth));
MLDECL( int,   MLPutIntegerArray,       ( MLINK mlp, int *          data, long *dims, char **heads, long depth));
MLDECL( int,   MLPutLongIntegerArray,   ( MLINK mlp, long *         data, long *dims, char **heads, long depth));

MLDECL( int,   MLPutInteger16Array,     ( MLINK mlp, short *        data, int *dims, char **heads, int depth));
MLDECL( int,   MLPutInteger32Array,     ( MLINK mlp, int *          data, int *dims, char **heads, int depth));
MLDECL( int,   MLPutInteger64Array,     ( MLINK mlp, mlint64 *      data, int *dims, char **heads, int depth));
#endif /* MLINTERFACE >= 4 */


#if MLINTERFACE >= 4
MLDECL( int,   MLPutFloatArray,         ( MLINK mlp, const float * data, const long *dims, const char **heads, long depth));
MLDECL( int,   MLPutDoubleArray,        ( MLINK mlp, const double *data, const long *dims, const char **heads, long depth));
MLDECL( int,   MLPutRealArray,          ( MLINK mlp, const double *data, const long *dims, const char **heads, long depth));
#if CC_SUPPORTS_LONG_DOUBLE
MLDECL( int,   MLPutLongDoubleArray,    ( MLINK mlp, const mlextended_double *data, const long *dims, const char **heads, long depth));
#endif

MLDECL( int,   MLPutReal32Array,        ( MLINK mlp, const float * data, const int *dims, const char **heads, int depth));
MLDECL( int,   MLPutReal64Array,        ( MLINK mlp, const double *data, const int *dims, const char **heads, int depth));
MLDECL( int,   MLPutReal128Array,       ( MLINK mlp, const mlextended_double *data, const int *dims, const char **heads, int depth));
#else
/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the following new functions as their replacement:

MLPutFloatArray      - MLPutReal32Array
MLPutDoubleArray     - MLPutReal64Array
MLPutRealArray       - MLPutReal64Array
MLPUtLongDoubleArray - MLPutReal128Array
*/
MLDECL( int,   MLPutFloatArray,         ( MLINK mlp, float * data, long *dims, char **heads, long depth));
MLDECL( int,   MLPutDoubleArray,        ( MLINK mlp, double *data, long *dims, char **heads, long depth));
MLDECL( int,   MLPutRealArray,          ( MLINK mlp, double *data, long *dims, char **heads, long depth));
#if CC_SUPPORTS_LONG_DOUBLE
MLDECL( int,   MLPutLongDoubleArray,    ( MLINK mlp, mlextended_double *data, long *dims, char **heads, long depth));
#endif

MLDECL( int,   MLPutReal32Array,        ( MLINK mlp, float * data, int *dims, char **heads, int depth));
MLDECL( int,   MLPutReal64Array,        ( MLINK mlp, double *data, int *dims, char **heads, int depth));
MLDECL( int,   MLPutReal128Array,       ( MLINK mlp, mlextended_double *data, int *dims, char **heads, int depth));
#endif /* MLINTERFACE >= 4 */


#if MLINTERFACE >= 4
MLDECL( int,   MLPutBinaryNumberList, ( MLINK mlp, const void *  data, long count, long type));
MLDECL( int,   MLPutIntegerList,      ( MLINK mlp, const int *   data, long count));
MLDECL( int,   MLPutRealList,         ( MLINK mlp, const double *data, long count));

MLDECL( int,   MLPutInteger8List,     ( MLINK mlp, const unsigned char *data, int count));
MLDECL( int,   MLPutInteger16List,    ( MLINK mlp, const short *   data, int count));
MLDECL( int,   MLPutInteger32List,    ( MLINK mlp, const int *     data, int count));
MLDECL( int,   MLPutInteger64List,    ( MLINK mlp, const mlint64 * data, int count));

MLDECL( int,   MLPutReal32List,       ( MLINK mlp, const float * data, int count));
MLDECL( int,   MLPutReal64List,       ( MLINK mlp, const double *data, int count));
MLDECL( int,   MLPutReal128List,      ( MLINK mlp, const mlextended_double *data, int count));
#else
MLDECL( int,   MLPutBinaryNumberList, ( MLINK mlp, void *  data, long count, long type));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the following new functions as their replacement:

MLPutIntegerList  - MLPutInteger32List
MLPutRealList     - MLPutReal64List
*/
MLDECL( int,   MLPutIntegerList,      ( MLINK mlp, int *   data, long count));
MLDECL( int,   MLPutRealList,         ( MLINK mlp, double *data, long count));

MLDECL( int,   MLPutInteger16List,    ( MLINK mlp, short *   data, int count));
MLDECL( int,   MLPutInteger32List,    ( MLINK mlp, int *     data, int count));
MLDECL( int,   MLPutInteger64List,    ( MLINK mlp, mlint64 * data, int count));

MLDECL( int,   MLPutReal32List,       ( MLINK mlp, float * data, int count));
MLDECL( int,   MLPutReal64List,       ( MLINK mlp, double *data, int count));
MLDECL( int,   MLPutReal128List,      ( MLINK mlp, mlextended_double *data, int count));
#endif /* MLINTERFACE >= 4 */


#if MLINTERFACE >= 4
MLDECL( int, MLPutArrayType,             ( MLINK mlp, MLINK heads, long depth, array_meterpp meterpp));
MLDECL( int, MLReleasePutArrayState,     ( MLINK mlp, MLINK heads, array_meterp meterp));
#else
MLDECL( int, MLPutArrayType0,             ( MLINK mlp, MLINK heads, long depth, array_meterpp meterpp));
MLDECL( int, MLReleasePutArrayState0,     ( MLINK mlp, MLINK heads, array_meterp meterp));
#endif /* MLINTERFACE >= 4 */

#if MLINTERFACE >= 4
MLDECL( int, MLPutArrayLeaves,           ( MLINK mlp, MLINK heads, array_meterp meterp, MLINK leaves, long count));
MLDECL( int, MLPutBinaryNumberArrayDataWithHeads, ( MLINK mlp, MLINK heads, array_meterp meterp, const void *datap, long count, long type));
#else
MLDECL( int, MLPutArrayLeaves0,           ( MLINK mlp, MLINK heads, array_meterp meterp, MLINK leaves, long count));
MLDECL( int, MLPutBinaryNumberArrayData0, ( MLINK mlp, MLINK heads, array_meterp meterp, void *datap, long count, long type));
#endif /* MLINTERFACE >= 4 */


ML_END_EXTERN_C



#ifndef _MLCAGET_H
#define _MLCAGET_H






#ifndef MLINTERFACE
/*\ syntax\ error\ */\ )
#endif

#ifndef __array_meterp__
#define __array_meterp__
typedef struct array_meter FAR * array_meterp;
typedef array_meterp FAR * array_meterpp;
#endif

#endif /* _MLCAGET_H */



/* explicitly not protected by _MLCAGET_H in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C

MLDECL( int,   MLGetArrayDimensions,       ( MLINK mlp, array_meterp meterp));
MLDECL( int,   MLGetArrayType,             ( MLINK mlp, array_meterp meterp));

MLDECL( int,  MLGetBinaryNumberList, ( MLINK mlp, void **datap, long *countp, long type));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:

MLGetIntegerList  - MLGetInteger32List
MLGetRealList     - MLGetReal64List
*/
MLDECL( int,  MLGetIntegerList,      ( MLINK mlp, int **datap, long *countp));
MLDECL( int,  MLGetRealList,         ( MLINK mlp, double **datap, long *countp));

MLDECL( int,  MLGetInteger16List,      ( MLINK mlp, short **   datap, int *countp));
MLDECL( int,  MLGetInteger32List,      ( MLINK mlp, int **     datap, int *countp));
MLDECL( int,  MLGetInteger64List,      ( MLINK mlp, mlint64 ** datap, int *countp));

MLDECL( int,  MLGetReal32List,         ( MLINK mlp, float **                 datap, int *countp));
MLDECL( int,  MLGetReal64List,         ( MLINK mlp, double **                datap, int *countp));
MLDECL( int,  MLGetReal128List,         ( MLINK mlp, mlextended_double **    datap, int *countp));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:

MLDisownBinaryNumberList  - MLReleaseBinaryNumberList
MLDisownIntegerList       - MLReleaseInteger32List
MLDisownRealList          - MLReleaseReal64List
*/

#if MLINTERFACE == 3
MLDECL( void, MLDisownBinaryNumberList, ( MLINK mlp, void *data, long count, long type));
MLDECL( void, MLDisownIntegerList,      ( MLINK mlp, int *data, long count));
MLDECL( void, MLDisownRealList,         ( MLINK mlp, double *data, long count));
#endif

#if MLINTERFACE >= 4
MLDECL( void, MLReleaseIntegerList,     ( MLINK mlp, int *data, long count));
MLDECL( void, MLReleaseRealList,        ( MLINK mlp, double *data, long count));
#endif

MLDECL( void, MLReleaseBinaryNumberList,   ( MLINK mlp, void *data, int count, long type));
MLDECL( void, MLReleaseInteger16List,      ( MLINK mlp, short *data, int count));
MLDECL( void, MLReleaseInteger32List,      ( MLINK mlp, int *data, int count));
MLDECL( void, MLReleaseInteger64List,      ( MLINK mlp, mlint64 *data, int count));

MLDECL( void, MLReleaseReal32List,         ( MLINK mlp, float *data, int count));
MLDECL( void, MLReleaseReal64List,         ( MLINK mlp, double *data, int count));
MLDECL( void, MLReleaseReal128List,        ( MLINK mlp, mlextended_double *data, int count));

MLDECL( int,   MLGetBinaryNumberArrayData,  ( MLINK mlp, array_meterp meterp, void *datap, long count, long type));
MLDECL( int,   MLGetByteArrayData,          ( MLINK mlp, array_meterp meterp, unsigned char * datap, long count));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:

MLGetShortIntegerArrayData  - MLGetInteger16ArrayData
MLGetIntegerArrayData       - MLGetInteger32ArrayData
MLGetLongIntegerArrayData   - MLGetInteger64ArrayData for 64-bit integers or MLGetInteger32ArrayData for 32-bit integers.
*/

MLDECL( int,   MLGetShortIntegerArrayData,  ( MLINK mlp, array_meterp meterp, short *         datap, long count));
MLDECL( int,   MLGetIntegerArrayData,       ( MLINK mlp, array_meterp meterp, int *           datap, long count));
MLDECL( int,   MLGetLongIntegerArrayData,   ( MLINK mlp, array_meterp meterp, long *          datap, long count));

MLDECL( int,   MLGetInteger16ArrayData,     ( MLINK mlp, array_meterp meterp, short *         datap, int count));
MLDECL( int,   MLGetInteger32ArrayData,     ( MLINK mlp, array_meterp meterp, int *           datap, int count));
MLDECL( int,   MLGetInteger64ArrayData,     ( MLINK mlp, array_meterp meterp, mlint64 *       datap, int count));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:

MLGetFloatArrayData        - MLGetReal32ArrayData
MLGetDoubleArrayData       - MLGetReal64ArrayData
MLGetLongDoubleArrayData   - MLGetReal128ArrayData
*/

MLDECL( int,   MLGetFloatArrayData,         ( MLINK mlp, array_meterp meterp, float *datap, long count));
MLDECL( int,   MLGetDoubleArrayData,        ( MLINK mlp, array_meterp meterp, double *datap, long count));
#if CC_SUPPORTS_LONG_DOUBLE
MLDECL( int,   MLGetLongDoubleArrayData,   ( MLINK mlp, array_meterp meterp, mlextended_double *datap, long count));
#endif

MLDECL( int,   MLGetReal32ArrayData,         ( MLINK mlp, array_meterp meterp, float *datap, int count));
MLDECL( int,   MLGetReal64ArrayData,        ( MLINK mlp, array_meterp meterp, double *datap, int count));
MLDECL( int,   MLGetReal128ArrayData,   ( MLINK mlp, array_meterp meterp, mlextended_double *datap, int count));


#if MLINTERFACE >= 4
MLDECL(int, MLGetInteger8List, (MLINK mlp, unsigned char **datap, int *countp));
MLDECL(int, MLGetInteger8ArrayData, (MLINK mlp, array_meterp meterp, unsigned char *datap, int count));
MLDECL(void, MLReleaseInteger8List, (MLINK mlp, unsigned char *data, int count));
#endif

#if MLINTERFACE == 3
MLDECL( int,   MLGetArrayType0,             ( MLINK mlp, MLINK heads, array_meterpp meterpp, long *depthp, mlapi__token *leaf_tokp));
#else /* MLINTERFACE >= 4 */
MLDECL( int,   MLGetArrayTypeWithDepthAndLeafType, ( MLINK mlp, MLINK heads, array_meterpp meterpp,
	long *depthp, mlapi__token *leaf_tokp));
#endif

#if MLINTERFACE >= 4
MLDECL( int,   MLGetBinaryNumberArrayDataWithHeads, ( MLINK mlp, MLINK heads, array_meterp  meterp, void *datap, long *countp, long type));
#else
MLDECL( int,   MLGetBinaryNumberArrayData0, ( MLINK mlp, MLINK heads, array_meterp  meterp, void *datap, long *countp, long type));
#endif

#if MLINTERFACE >= 4
MLDECL( void,  MLReleaseGetArrayState,     ( MLINK mlp, MLINK heads, array_meterp  meterp));
#else
MLDECL( void,  MLReleaseGetArrayState0,     ( MLINK mlp, MLINK heads, array_meterp  meterp));
#endif

#if MLINTERFACE == 3
MLDECL( int,   MLGetBinaryNumberArray0,   ( MLINK mlp, void **datap, long **dimpp, char ***headsp, long *depthp, long type, mlapi__token *leaf_tokp));
#else /* MLINTERFACE >= 4 */
MLDECL( int,   MLGetBinaryNumberArrayWithLeafType,   ( MLINK mlp, void **datap, long **dimpp, char ***headsp, long *depthp, long type, mlapi__token *leaf_tokp));
#endif



MLDECL( int,   MLGetBinaryNumberArray,    ( MLINK mlp, void **          datap, long **dimpp, char ***headsp, long *depthp, long type));
MLDECL( int,   MLGetByteArray,            ( MLINK mlp, unsigned char ** datap, int **dimsp, char ***headsp, int *depthp));

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:

MLGetShortIntegerArray   - MLGetInteger16Array
MLGetIntegerArray        - MLGetInteger32Array
MLGetLongIntegerArray    - MLGetInteger64Array for 64-bit integers or MLGetInteger32Array from 32-bit integers.
*/

MLDECL( int,   MLGetShortIntegerArray,    ( MLINK mlp, short **         datap, long **dimsp, char ***headsp, long *depthp));
MLDECL( int,   MLGetIntegerArray,         ( MLINK mlp, int **           datap, long **dimsp, char ***headsp, long *depthp));
MLDECL( int,   MLGetLongIntegerArray,     ( MLINK mlp, long **          datap, long **dimsp, char ***headsp, long *depthp));

MLDECL( int,   MLGetInteger16Array,       ( MLINK mlp, short **         datap, int **dimsp, char ***headsp, int *depthp));
MLDECL( int,   MLGetInteger32Array,       ( MLINK mlp, int **           datap, int **dimsp, char ***headsp, int *depthp));
MLDECL( int,   MLGetInteger64Array,       ( MLINK mlp, mlint64 **       datap, int **dimsp, char ***headsp, int *depthp));


#if MLINTERFACE >= 4
MLDECL(int,  MLGetInteger8Array,  (MLINK mlp, unsigned char **datap, int **dimsp, char ***headsp, int *depthp));
#endif

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the suggested functions in their
place:

MLGetFloatArray      - MLGetReal32Array
MLGetDoubleArray     - MLGetReal64Array
MLGetRealArray       - MLGetReal64Array
MLGetLongDoubleArray - MLGetReal128Array
*/

MLDECL( int,   MLGetFloatArray,           ( MLINK mlp, float ** datap, long **dimsp, char ***headsp, long *depthp));
MLDECL( int,   MLGetDoubleArray,          ( MLINK mlp, double **datap, long **dimsp, char ***headsp, long *depthp));
MLDECL( int,   MLGetRealArray,            ( MLINK mlp, double **datap, long **dimsp, char ***headsp, long *depthp));
#if CC_SUPPORTS_LONG_DOUBLE
MLDECL( int,   MLGetLongDoubleArray,      ( MLINK mlp, mlextended_double **datap, long **dimsp, char ***headsp, long *depthp));
#endif

MLDECL( int,   MLGetReal32Array,          ( MLINK mlp, float ** datap, int **dimsp, char ***headsp, int *depthp));
MLDECL( int,   MLGetReal64Array,          ( MLINK mlp, double **datap, int **dimsp, char ***headsp, int *depthp));
MLDECL( int,   MLGetReal128Array,         ( MLINK mlp, mlextended_double **datap, int **dimsp, char ***headsp, int *depthp));


/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the following new functions as their replacement:

MLDisownBinaryNumberArray - MLReleaseBinaryNumberArray
MLDisownByteArray         - MLReleaseByteArray
MLDisownShortIntegerArray - MLReleaseInteger16Array
MLDisownIntegerArray      - MLReleaseInteger32Array
MLDisownLongIntegerArray  - Use MLReleaseInteger32Array for 32-bit integers or MLReleaseInteger64Array for 64-bit integers.
*/

#if MLINTERFACE == 3
MLDECL( void,           MLDisownBinaryNumberArray,  ( MLINK mlp, void *         data, long *dimp, char **heads, long len, long type));
#endif

#if MLINTERFACE == 3
MLDECL( void,           MLDisownByteArray,          ( MLINK mlp, unsigned char *data, long *dims, char **heads, long depth));
MLDECL( void,           MLDisownShortIntegerArray,  ( MLINK mlp, short *        data, long *dims, char **heads, long depth));
MLDECL( void,           MLDisownIntegerArray,       ( MLINK mlp, int *          data, long *dims, char **heads, long depth));
MLDECL( void,           MLDisownLongIntegerArray,   ( MLINK mlp, long *         data, long *dims, char **heads, long depth));
#endif

#if MLINTERFACE >= 4
MLDECL( void,           MLReleaseShortIntegerArray, ( MLINK mlp, short *        data, long *dims, char **heads, long depth));
MLDECL( void,           MLReleaseIntegerArray,      ( MLINK mlp, int *          data, long *dims, char **heads, long depth));
MLDECL( void,           MLReleaseLongIntegerArray,  ( MLINK mlp, long *         data, long *dims, char **heads, long depth));
#endif

MLDECL( void,           MLReleaseBinaryNumberArray,  ( MLINK mlp, void *         data, int *dimp, char **heads, int len, long type));
MLDECL( void,           MLReleaseByteArray,          ( MLINK mlp, unsigned char *data, int *dims, char **heads, int depth));
MLDECL( void,           MLReleaseInteger16Array,     ( MLINK mlp, short *        data, int *dims, char **heads, int depth));
MLDECL( void,           MLReleaseInteger32Array,     ( MLINK mlp, int *          data, int *dims, char **heads, int depth));
MLDECL( void,           MLReleaseInteger64Array,     ( MLINK mlp, mlint64 *      data, int *dims, char **heads, int depth));

#if MLINTERFACE >= 4
MLDECL(void,   MLReleaseInteger8Array,   (MLINK mlp, unsigned char *data, int *dimp, char **heads, int depth));
#endif

/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the following new functions as their replacement:

MLDisownFloatArray  - MLReleaseReal32Array
MLDisownDoubleArray - MLReleaseReal64Array
MLDisownRealArray   - MLReleaseReal64Array
*/

#if MLINTERFACE == 3
MLDECL( void,           MLDisownFloatArray,         ( MLINK mlp, float * data, long *dims, char **heads, long depth));
MLDECL( void,           MLDisownDoubleArray,        ( MLINK mlp, double *data, long *dims, char **heads, long depth));
MLDECL( void,           MLDisownRealArray,          ( MLINK mlp, double *data, long *dims, char **heads, long depth));
#endif

#if MLINTERFACE >= 4
MLDECL( void,           MLReleaseFloatArray,         ( MLINK mlp, float * data, long *dims, char **heads, long depth));
MLDECL( void,           MLReleaseDoubleArray,        ( MLINK mlp, double *data, long *dims, char **heads, long depth));
MLDECL( void,           MLReleaseRealArray,          ( MLINK mlp, double *data, long *dims, char **heads, long depth));
#endif

MLDECL( void,           MLReleaseReal32Array,         ( MLINK mlp, float * data, int *dims, char **heads, int depth));
MLDECL( void,           MLReleaseReal64Array,          ( MLINK mlp, double *data, int *dims, char **heads, int depth));


#if CC_SUPPORTS_LONG_DOUBLE
/*
As of MLINTERFACE 3 the following functions have been deprecated.  Use the following new functions as their replacement:

MLDisownLongDoubleArray - MLReleaseReal128Array
*/

#if MLINTERFACE == 3
MLDECL( void,           MLDisownLongDoubleArray,   ( MLINK mlp, mlextended_double *data, long *dims, char **heads, long depth));
#endif

MLDECL( void,           MLReleaseReal128Array,     ( MLINK mlp, mlextended_double *data, int *dims, char **heads, int depth));

#if MLINTERFACE >= 4
MLDECL( void,           MLReleaseLongDoubleArray,  ( MLINK mlp, mlextended_double *data, long *dims, char **heads, long depth));
#endif

#endif /* CC_SUPPORTS_LONG_DOUBLE */


ML_END_EXTERN_C


/*************** Unicode Container for mprep templates ***************/


#ifndef MLUNICODECONTAINER_HPP
#define MLUNICODECONTAINER_HPP







ML_EXTERN_C

#if MLINTERFACE >= 4
enum MLUnicodeContainerType
{
	UCS2ContainerType,
	UTF8ContainerType,
	UTF16ContainerType,
	UTF32ContainerType
};

typedef struct _MLUnicodeContainer
{
	union _pointer
	{
		unsigned short *ucs2;
		unsigned char *utf8;
		unsigned short *utf16;
		unsigned int *utf32;
	} pointer;

	int length;
	enum MLUnicodeContainerType type;
} MLUnicodeContainer;

#define MLUCS2String(container)   container->pointer.ucs2
#define MLUTF8String(container)   container->pointer.utf8
#define MLUTF16String(container)  container->pointer.utf16
#define MLUTF32String(container)  container->pointer.utf32
#define MLUnicodeStringLength(container) container->length
#define MLUnicodeStringType(container) container->type

MLDECL(MLUnicodeContainer *, MLNewUnicodeContainer, (const void *string, int length, enum MLUnicodeContainerType type));
MLDECL(void,    MLReleaseUnicodeContainer, (MLUnicodeContainer *string));

#endif /* MLINTERFACE >= 4 */

ML_END_EXTERN_C


#endif /* MLUNICODECONTAINER_HPP */



/*************** seeking, transfering  and synchronization ***************/

#ifndef _MLMARK_H
#define _MLMARK_H




#endif /* _MLMARK_H */

/* explicitly not protected by _MLMARK_H in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C
MLDECL( MLINKMark,  MLCreateMark,  ( MLINK mlp));
MLDECL( MLINKMark,  MLSeekToMark,  ( MLINK mlp, MLINKMark mark, int index));
MLDECL( MLINKMark,  MLSeekMark,    ( MLINK mlp, MLINKMark mark, int index));
MLDECL( void,       MLDestroyMark, ( MLINK mlp, MLINKMark mark));
ML_END_EXTERN_C



#ifndef _MLXFER_H
#define _MLXFER_H





#endif /* _MLXFER_H */

/* explicitly not protected by _MLXFER_H in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C

#ifndef MLINTERFACE
/*\ syntax\ error\ */\ )
#endif

MLDECL( int, MLTransferExpression, ( MLINK dmlp, MLINK smlp));
MLDECL( int, MLTransferToEndOfLoopbackLink, ( MLINK dmlp, MLINK smlp));


#if MLINTERFACE == 3
MLDECL( int, MLTransfer0, ( MLINK dmlp, MLINK smlp, unsigned long sequence_no));
#endif /* MLINTERFACE == 3 */
ML_END_EXTERN_C



#ifndef _MLSYNC_H
#define _MLSYNC_H




/* export mls__wait and mls__align(mlsp) */

#endif /* _MLSYNC_H */

/* explicitly not protected by _MLSYNC_H in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C
/* in response to a reset message */
MLDECL( int, MLForwardReset, ( MLINK mlp, unsigned long marker));


MLDECL( int, MLAlign,        ( MLINK lmlp, MLINK rmlp));
ML_END_EXTERN_C


/*************************************************************/


#ifndef _MLPKT_H
#define _MLPKT_H

/*************** Mathematica packet interface ***************/

			/* MLNextPacket returns one of... */


/* edit here and in mlpktstr.h */

#ifndef _MLPKTNO_H
#define _MLPKTNO_H

#define ILLEGALPKT      0

#define CALLPKT         7
#define EVALUATEPKT    13
#define RETURNPKT       3

#define INPUTNAMEPKT    8
#define ENTERTEXTPKT   14
#define ENTEREXPRPKT   15
#define OUTPUTNAMEPKT   9
#define RETURNTEXTPKT   4
#define RETURNEXPRPKT  16

#define DISPLAYPKT     11
#define DISPLAYENDPKT  12

#define MESSAGEPKT      5
#define TEXTPKT         2

#define INPUTPKT        1
#define INPUTSTRPKT    21
#define MENUPKT         6
#define SYNTAXPKT      10

#define SUSPENDPKT     17
#define RESUMEPKT      18

#define BEGINDLGPKT    19
#define ENDDLGPKT      20

#define FIRSTUSERPKT  128
#define LASTUSERPKT   255


#endif /* _MLPKTNO_H */



#endif /* _MLPKT_H */

/* explicitly not protected by _MLPKT_H in case MLDECL is redefined for multiple inclusion */

ML_EXTERN_C
MLDECL( int,  MLNextPacket, ( MLINK mlp));
ML_END_EXTERN_C



#ifndef _MLALERT_H
#define _MLALERT_H







ML_EXTERN_C
/*************** User interaction--for internal use only ***************/

#if WIN64_MATHLINK
typedef __int64 mldlg_result;
#else
typedef long mldlg_result;
#endif

MLDPROC( mldlg_result, MLAlertProcPtr,             ( MLEnvironment env, const char *message));
MLDPROC( mldlg_result, MLRequestProcPtr,           ( MLEnvironment env, const char *prompt, char *response, long sizeof_response));
MLDPROC( mldlg_result, MLConfirmProcPtr,           ( MLEnvironment env, const char *question, mldlg_result default_answer));
MLDPROC( mldlg_result, MLRequestArgvProcPtr,       ( MLEnvironment env, char **argv, long cardof_argv, char *buf, long sizeof_buf));
MLDPROC( mldlg_result, MLRequestToInteractProcPtr, ( MLEnvironment env, mldlg_result wait_for_permission));
MLDPROC( mldlg_result, MLDialogProcPtr,            ( MLEnvironment env));


typedef MLDialogProcPtr MLDialogUPP;
typedef MLAlertProcPtr MLAlertUPP;
typedef MLRequestProcPtr MLRequestUPP;
typedef MLConfirmProcPtr MLConfirmUPP;
typedef MLRequestArgvProcPtr MLRequestArgvUPP;
typedef MLRequestToInteractProcPtr MLRequestToInteractUPP;
#define NewMLAlertProc(userRoutine) MLAlertCast((userRoutine))
#define NewMLRequestProc(userRoutine) MLRequestCast((userRoutine))
#define NewMLConfirmProc(userRoutine) MLConfirmCast((userRoutine))
#define NewMLRequestArgvProc(userRoutine) MLRequestArgvCast((userRoutine))
#define NewMLRequestToInteractProc(userRoutine) MLRequestToInteractCast((userRoutine))

typedef MLAlertUPP MLAlertFunctionType;
typedef MLRequestUPP MLRequestFunctionType;
typedef MLConfirmUPP MLConfirmFunctionType;
typedef MLRequestArgvUPP MLRequestArgvFunctionType;
typedef MLRequestToInteractUPP MLRequestToInteractFunctionType;
typedef MLDialogUPP MLDialogFunctionType;



/*
	MLDDECL( mldlg_result, alert_user, ( MLEnvironment env, kcharp_ct message));
	MLDDEFN( mldlg_result, alert_user, ( MLEnvironment env, kcharp_ct message))
	{
		fprintf( stderr, "%s\n", message);
	}


	...
	MLDialogFunctionType f = NewMLAlertProc(alert_user);
	MLSetDialogFunction( ep, MLAlertFunction, f);
	...
	or
	...
	MLSetDialogFunction( ep, MLAlertFunction, NewMLAlertProc(alert_user));
	...
*/



enum {	MLAlertFunction = 1, MLRequestFunction, MLConfirmFunction,
	MLRequestArgvFunction, MLRequestToInteractFunction };


#define ML_DEFAULT_DIALOG ( (MLDialogFunctionType) 1)
#define ML_IGNORE_DIALOG ( (MLDialogFunctionType) 0)
#define ML_SUPPRESS_DIALOG ML_IGNORE_DIALOG



#if WINDOWS_MATHLINK

#ifndef _MLWIN_H
#define _MLWIN_H





ML_EXTERN_C
MLDDECL( mldlg_result, MLAlert_win,   ( MLEnvironment ep, const char *alertstr));
MLDDECL( mldlg_result, MLRequest_win, ( MLEnvironment ep, const char *prompt, char *response, long n));
MLDDECL( mldlg_result, MLConfirm_win, ( MLEnvironment ep, const char *okcancelquest, mldlg_result default_answer));
MLDDECL( mldlg_result, MLPermit_win,  ( MLEnvironment ep, mldlg_result wait));
ML_END_EXTERN_C

/* edit here and in mlwin.rc -- in both places because of command-line length limitations in dos */
#define DLG_LINKNAME                101
#define DLG_TEXT                    102
#define RIDOK                       1
#define RIDCANCEL                   104

#endif /* _MLWIN_H */

#define MLALERT         MLAlert_win
#define MLREQUEST       MLRequest_win
#define MLCONFIRM       MLConfirm_win
#define MLPERMIT        MLPermit_win
#define MLREQUESTARGV	default_request_argv
#endif

#if UNIX_MATHLINK
#if DARWIN_MATHLINK  && ! defined(IOS_MATHLINK) && defined (USE_CF_DIALOGS)

#ifndef _MLDARWIN_H
#define _MLDARWIN_H





ML_EXTERN_C

MLDDECL( mldlg_result, MLAlert_darwin,   ( MLEnvironment env, const char *message));
MLDDECL( mldlg_result, MLRequest_darwin, ( MLEnvironment env, const char *prompt, char *response, long sizeof_response));
MLDDECL( mldlg_result, MLConfirm_darwin, ( MLEnvironment env, const char *question, mldlg_result default_answer));
MLDDECL( mldlg_result, MLPermit_darwin,  ( MLEnvironment env, mldlg_result wait_for_permission));
MLDDECL( mldlg_result, MLDontPermit_darwin, ( MLEnvironment ep, mldlg_result wait_for_permission));

ML_END_EXTERN_C

#endif /* _MLDARWIN_H */

#define MLALERT  	MLAlert_darwin
#define MLREQUEST	MLRequest_darwin
#define MLCONFIRM	MLConfirm_darwin
#define MLPERMIT 	MLPermit_darwin
#define MLREQUESTARGV	default_request_argv
#else /* !(DARWIN_MATHLINK && ! defined(IOS_MATHLINK) && defined (USE_CF_DIALOGS)) */

#ifndef _MLUNIX_H
#define _MLUNIX_H





ML_EXTERN_C

MLDDECL( mldlg_result, MLAlert_unix,   ( MLEnvironment env, const char *message));
MLDDECL( mldlg_result, MLRequest_unix, ( MLEnvironment env, const char *prompt, char *response, long sizeof_response));
MLDDECL( mldlg_result, MLConfirm_unix, ( MLEnvironment env, const char *question, mldlg_result default_answer));
MLDDECL( mldlg_result, MLPermit_unix,  ( MLEnvironment env, mldlg_result wait_for_permission));

ML_END_EXTERN_C

#endif /* _MLUNIX_H */

#define MLALERT  	MLAlert_unix
#define MLREQUEST	MLRequest_unix
#define MLCONFIRM	MLConfirm_unix
#define MLPERMIT 	MLPermit_unix
#define MLREQUESTARGV	default_request_argv
#endif /* DARWIN_MATHLINK && ! defined(IOS_MATHLINK) && defined (USE_CF_DIALOGS) */
#endif


MLDDECL( mldlg_result, default_request_argv, ( MLEnvironment ep, char **argv, long len, char *buff, long size));
ML_END_EXTERN_C

#endif /* _MLALERT_H */


/* explicitly not protected by _MLXDATA_H in case MLDECL is redefined for multiple inclusion */
ML_EXTERN_C

MLDECL( mldlg_result,  MLAlert,             ( MLEnvironment env, const char *message));
MLDECL( mldlg_result,  MLRequest,           ( MLEnvironment env, const char *prompt, char *response, long sizeof_response)); /* initialize response with default*/
MLDECL( mldlg_result,  MLConfirm,           ( MLEnvironment env, const char *question, mldlg_result default_answer));
MLDECL( mldlg_result,  MLRequestArgv,       ( MLEnvironment env, char **argv, long cardof_argv, char *buff, long size));

MLDECL( mldlg_result,  MLRequestToInteract, ( MLEnvironment env, mldlg_result wait_for_permission));
MLDECL( int,  MLSetDialogFunction, ( MLEnvironment env, long funcnum, MLDialogFunctionType func));

/* just some type-safe casts */
MLDECL( MLDialogProcPtr, MLAlertCast, ( MLAlertProcPtr f));
MLDECL( MLDialogProcPtr, MLRequestCast, ( MLRequestProcPtr f));
MLDECL( MLDialogProcPtr, MLConfirmCast, ( MLConfirmProcPtr f));
MLDECL( MLDialogProcPtr, MLRequestArgvCast, ( MLRequestArgvProcPtr f));
MLDECL( MLDialogProcPtr, MLRequestToInteractCast, ( MLRequestToInteractProcPtr f));
ML_END_EXTERN_C


/*************************************************************/

#define WSWAITSUCCESS         1
#define WSWAITERROR           2
#define WSWAITTIMEOUT         3
#define WSWAITCALLBACKABORTED 4

#ifndef _MLREADY_H
#define _MLREADY_H

#ifndef _MLTIME_H
#define _MLTIME_H


typedef struct _mltimeval{
	unsigned long tv_sec;
	unsigned long tv_usec;
} mltimeval;


#endif /* _MLTIME_H */



ML_EXTERN_C
MLDECL( int,   MLReady,            ( MLINK mlp));
ML_END_EXTERN_C



#if defined(__cplusplus)
#define MLINFINITEWAIT static_cast<mltimeval>({-1, -1})
#else
#define MLINFINITEWAIT {-1, -1}
#endif /* __cplusplus */

#define MLREADYPARALLELERROR -1
#define MLREADYPARALLELTIMEDOUT -2
#define MLREADYPARALLELINVALIDARGUMENT -3

typedef void *MLREADYPARALLELENV;

ML_EXTERN_C
MLDECL(int,              MLReadyParallel, (MLENV, MLINK *, int, mltimeval));
ML_END_EXTERN_C


#if MLINTERFACE >= 4
ML_EXTERN_C
MLWPROC(int, MLLinkWaitCallBackObject, (MLINK, void *));

MLDECL(int, MLWaitForLinkActivity, (MLINK mlp));
MLDECL(int, MLWaitForLinkActivityWithCallback, (MLINK mlp, MLLinkWaitCallBackObject callback));
ML_END_EXTERN_C


#define MLWAITSUCCESS         1
#define MLWAITERROR           2
#define MLWAITTIMEOUT         3
#define MLWAITCALLBACKABORTED 4
#endif

#endif /* _MLREADY_H */


/********************************************************/


#ifndef _WSTM_H
#define _WSTM_H




/*************** Template interface ***************/

/* The following are useful only when using template files as
 * their definitions are produced by mprep.
 */

ML_EXTERN_C
extern WSLINK stdlink;
extern WSEnvironment stdenv;

extern WSYieldFunctionObject stdyielder;
extern WSMessageHandlerObject stdhandler;

extern int WSMain P((int, char **)); /* pass in argc and argv */
extern int WSMainString P(( char *commandline));
extern int WSMainArgv P(( char** argv, char** argv_end)); /* note not FAR pointers */

extern int WSInstall P((WSLINK));
extern wsapi_packet WSAnswer P((WSLINK));
extern int WSDoCallPacket P((WSLINK));
extern int WSEvaluate P(( WSLINK, char *));
extern int WSEvaluateString P(( WSLINK, char *));
ML_END_EXTERN_C

WSMDECL( void, WSDefaultHandler, ( WSLINK, int, int));
WSYDECL( int, WSDefaultYielder, ( WSLINK, WSYieldParameters));

ML_EXTERN_C
#if WINDOWS_WSTP
extern HWND WSInitializeIcon P(( HINSTANCE hinstCurrent, int nCmdShow));
extern HANDLE WSInstance;
extern HWND WSIconWindow;
#endif
extern int WSAbort, WSDone;
extern long WSSpecialCharacter;
ML_END_EXTERN_C

#endif /* _WSTM_H */


/********************************************************/



/*****************************************************************************
 * START - Unbrand
 *  Note: Unbrand section is temporary. It is to unmap names between ML and WS.
 *  This section will be removed when all the public symbols are refactored.
 *****************************************************************************/
#ifndef _UNBRAND_H_
#define _UNBRAND_H_


#undef MLActivate
#undef MLAlert
#undef MLAlertCast
#undef MLAlign
#undef MLAllocParameter
#undef MLAllocatorCast
#undef MLBegin
#undef MLBrowseForLinkServices
#undef MLBytesToGet
#undef MLBytesToPut
#undef MLCallMessageHandler
#undef MLCallYieldFunction
#undef MLCharacterOffset
#undef MLCheckFunction
#undef MLCheckFunctionWithArgCount
#undef MLClearAllSymbolReplacements
#undef MLClearError
#undef MLClearSymbolReplacement
#undef MLClose
#undef MLCompilerID
#undef MLConfirm
#undef MLConfirmCast
#undef MLConnect
#undef MLContextFromLinkServer
#undef MLConvertByteString
#undef MLConvertByteStringNL
#undef MLConvertCharacter
#undef MLConvertDoubleByteString
#undef MLConvertDoubleByteStringNL
#undef MLConvertNewLine
#undef MLConvertUCS2String
#undef MLConvertUCS2StringNL
#undef MLConvertUTF16String
#undef MLConvertUTF16StringNL
#undef MLConvertUTF32String
#undef MLConvertUTF32StringNL
#undef MLConvertUTF8String
#undef MLConvertUTF8StringNL
#undef MLCountYP
#undef MLCreateLinkWithExternalProtocol
#undef MLCreateMark
#undef MLCreateMessageHandler
#undef MLCreateYieldFunction
#undef MLDeallocatorCast
#undef MLDefaultYieldFunction
#undef MLDeinit
#undef MLDeinitialize
#undef MLDestroyMark
#undef MLDestroyMessageHandler
#undef MLDestroyYieldFunction
#undef MLDeviceInformation
#undef MLDisableLinkLock
#undef MLDisableLoggingStream
#undef MLDoNotHandleSignalParameter
#undef MLDuplicateLink
#undef MLEnableLinkLock
#undef MLEnableLoggingStream
#undef MLEnclosingEnvironment
#undef MLEnd
#undef MLEndPacket
#undef MLEnvironmentData
#undef MLError
#undef MLErrorMessage
#undef MLErrorParameter
#undef MLErrorString
#undef MLEstablish
#undef MLEstablishString
#undef MLExpressionsToGet
#undef MLFeatureString
#undef MLFill
#undef MLFilterArgv
#undef MLFlush
#undef MLForwardReset
#undef MLFromLinkID
#undef MLGet7BitCharacters
#undef MLGet8BitCharacters
#undef MLGetAvailableLinkProtocolNames
#undef MLGetArgCount
#undef MLGetArrayDimensions
#undef MLGetArrayType
#undef MLGetArrayTypeWithDepthAndLeafType
#undef MLGetBinaryNumber
#undef MLGetBinaryNumberArray
#undef MLGetBinaryNumberArrayData
#undef MLGetBinaryNumberArrayDataWithHeads
#undef MLGetBinaryNumberArrayWithLeafType
#undef MLGetBinaryNumberList
#undef MLGetByteArray
#undef MLGetByteArrayData
#undef MLGetByteString
#undef MLGetByteSymbol
#undef MLGetData
#undef MLGetDomainNameList
#undef MLGetDouble
#undef MLGetDoubleArray
#undef MLGetDoubleArrayData
#undef MLGetFloat
#undef MLGetFloatArray
#undef MLGetFloatArrayData
#undef MLGetFunction
#undef MLGetInteger
#undef MLGetInteger16
#undef MLGetInteger16Array
#undef MLGetInteger16ArrayData
#undef MLGetInteger16List
#undef MLGetInteger32
#undef MLGetInteger32Array
#undef MLGetInteger32ArrayData
#undef MLGetInteger32List
#undef MLGetInteger64
#undef MLGetInteger64Array
#undef MLGetInteger64ArrayData
#undef MLGetInteger64List
#undef MLGetInteger8
#undef MLGetInteger8Array
#undef MLGetInteger8ArrayData
#undef MLGetInteger8List
#undef MLGetIntegerArray
#undef MLGetIntegerArrayData
#undef MLGetIntegerList
#undef MLGetLinkedEnvIDString
#undef MLGetLinksFromEnvironment
#undef MLGetLongDouble
#undef MLGetLongDoubleArray
#undef MLGetLongDoubleArrayData
#undef MLGetLongInteger
#undef MLGetLongIntegerArray
#undef MLGetLongIntegerArrayData
#undef MLGetMessage
#undef MLGetMessageHandler
#undef MLGetNetworkAddressList
#undef MLGetNext
#undef MLGetNextRaw
#undef MLGetNumberAsByteString
#undef MLGetNumberAsString
#undef MLGetNumberAsUCS2String
#undef MLGetNumberAsUTF16String
#undef MLGetNumberAsUTF32String
#undef MLGetNumberAsUTF8String
#undef MLGetRawArgCount
#undef MLGetRawData
#undef MLGetRawType
#undef MLGetReal
#undef MLGetReal128
#undef MLGetReal128Array
#undef MLGetReal128ArrayData
#undef MLGetReal128List
#undef MLGetReal32
#undef MLGetReal32Array
#undef MLGetReal32ArrayData
#undef MLGetReal32List
#undef MLGetReal64
#undef MLGetReal64Array
#undef MLGetReal64ArrayData
#undef MLGetReal64List
#undef MLGetRealArray
#undef MLGetRealList
#undef MLGetShortInteger
#undef MLGetShortIntegerArray
#undef MLGetShortIntegerArrayData
#undef MLGetString
#undef MLGetSymbol
#undef MLGetType
#undef MLGetUCS2Characters
#undef MLGetUCS2String
#undef MLGetUCS2Symbol
#undef MLGetUTF16Characters
#undef MLGetUTF16String
#undef MLGetUTF16Symbol
#undef MLGetUTF32Characters
#undef MLGetUTF32String
#undef MLGetUTF32Symbol
#undef MLGetUTF8Characters
#undef MLGetUTF8String
#undef MLGetUTF8Symbol
#undef MLGetYieldFunction
#undef MLHandlerCast
#undef MLHandleSignal
#undef MLInit
#undef MLInitialize
#undef MLInterfaceFromLinkServer
#undef MLIsLinkLoopback
#undef MLLinkEnvironment
#undef MLLinkName
#undef MLLogFileNameForLink
#undef MLLogStreamToFile
#undef MLLoopbackOpen
#undef MLLowLevelDeviceName
#undef MLMessageHandler
#undef MLMessageReady
#undef MLName
#undef MLNewLinkServer
#undef MLNewLinkServerWithPort
#undef MLNewLinkServerWithPortAndInterface
#undef MLNewPacket
#undef MLNewParameters
#undef MLNewUnicodeContainer
#undef MLNextCharacter
#undef MLNextCharacterFromStringWithLength
#undef MLNextPacket
#undef MLNumber
#undef MLNumericsQuery
#undef MLOldConvertByteString
#undef MLOldConvertUCS2String
#undef MLOldPutCharToString
#undef MLOldStringCharFun
#undef MLOldStringFirstPosFun
#undef MLOldStringNextPosFun
#undef MLOpen
#undef MLOpenArgcArgv
#undef MLOpenArgv
#undef MLOpenInEnv
#undef MLOpenString
#undef MLPortFromLinkServer
#undef MLPrintArgv
#undef MLPut7BitCharacters
#undef MLPut7BitCount
#undef MLPut8BitCharacters
#undef MLPutArgCount
#undef MLPutArray
#undef MLPutArrayLeaves
#undef MLPutArrayType
#undef MLPutBinaryNumber
#undef MLPutBinaryNumberArray
#undef MLPutBinaryNumberArrayData
#undef MLPutBinaryNumberArrayDataWithHeads
#undef MLPutBinaryNumberList
#undef MLPutByteArray
#undef MLPutByteArrayData
#undef MLPutByteString
#undef MLPutByteSymbol
#undef MLPutComposite
#undef MLPutData
#undef MLPutDouble
#undef MLPutDoubleArray
#undef MLPutDoubleArrayData
#undef MLPutFloat
#undef MLPutFloatArray
#undef MLPutFloatArrayData
#undef MLPutFunction
#undef MLPutInteger
#undef MLPutInteger16
#undef MLPutInteger16Array
#undef MLPutInteger16ArrayData
#undef MLPutInteger16List
#undef MLPutInteger32
#undef MLPutInteger32Array
#undef MLPutInteger32ArrayData
#undef MLPutInteger32List
#undef MLPutInteger64
#undef MLPutInteger64Array
#undef MLPutInteger64ArrayData
#undef MLPutInteger64List
#undef MLPutInteger8
#undef MLPutInteger8Array
#undef MLPutInteger8ArrayData
#undef MLPutInteger8List
#undef MLPutIntegerArray
#undef MLPutIntegerArrayData
#undef MLPutIntegerList
#undef MLPutLongDouble
#undef MLPutLongDoubleArray
#undef MLPutLongDoubleArrayData
#undef MLPutLongInteger
#undef MLPutLongIntegerArray
#undef MLPutLongIntegerArrayData
#undef MLPutMessage
#undef MLPutMessageWithArg
#undef MLPutNext
#undef MLPutRawData
#undef MLPutRawSize
#undef MLPutReal
#undef MLPutReal128
#undef MLPutReal128Array
#undef MLPutReal128ArrayData
#undef MLPutReal128List
#undef MLPutReal32
#undef MLPutReal32Array
#undef MLPutReal32ArrayData
#undef MLPutReal32List
#undef MLPutReal64
#undef MLPutReal64Array
#undef MLPutReal64ArrayData
#undef MLPutReal64List
#undef MLPutRealArray
#undef MLPutRealList
#undef MLPutRealNumberAsByteString
#undef MLPutRealNumberAsString
#undef MLPutRealNumberAsUCS2String
#undef MLPutRealNumberAsUTF16String
#undef MLPutRealNumberAsUTF32String
#undef MLPutRealNumberAsUTF8String
#undef MLPutShortInteger
#undef MLPutShortIntegerArray
#undef MLPutShortIntegerArrayData
#undef MLPutSize
#undef MLPutString
#undef MLPutSymbol
#undef MLPutType
#undef MLPutUCS2Characters
#undef MLPutUCS2Function
#undef MLPutUCS2String
#undef MLPutUCS2Symbol
#undef MLPutUTF16Characters
#undef MLPutUTF16Function
#undef MLPutUTF16String
#undef MLPutUTF16Symbol
#undef MLPutUTF32Characters
#undef MLPutUTF32Function
#undef MLPutUTF32String
#undef MLPutUTF32Symbol
#undef MLPutUTF8Characters
#undef MLPutUTF8Function
#undef MLPutUTF8String
#undef MLPutUTF8Symbol
#undef MLRawBytesToGet
#undef MLReady
#undef MLReadyParallel
#undef MLRegisterCallbackFunctionWithLinkServer
#undef MLRegisterLinkService
#undef MLRegisterLinkServiceFromLinkServer
#undef MLRegisterLinkServiceWithHostname
#undef MLRegisterLinkServiceWithPortAndHostname
#undef MLReleaseBinaryNumberArray
#undef MLReleaseBinaryNumberList
#undef MLReleaseByteArray
#undef MLReleaseByteString
#undef MLReleaseByteSymbol
#undef MLReleaseCompilerID
#undef MLReleaseDomainNameList
#undef MLReleaseDoubleArray
#undef MLReleaseEnvIDString
#undef MLReleaseErrorMessage
#undef MLReleaseFloatArray
#undef MLReleaseGetArrayState
#undef MLReleaseInteger16Array
#undef MLReleaseInteger16List
#undef MLReleaseInteger32Array
#undef MLReleaseInteger32List
#undef MLReleaseInteger64Array
#undef MLReleaseInteger64List
#undef MLReleaseInteger8Array
#undef MLReleaseInteger8List
#undef MLReleaseIntegerArray
#undef MLReleaseIntegerList
#undef MLReleaseInterfaceFromLinkServer
#undef MLReleaseLinkName
#undef MLReleaseLinkProtocolNames
#undef MLReleaseLinksFromEnvironment
#undef MLReleaseLogFileNameForLink
#undef MLReleaseLongDoubleArray
#undef MLReleaseLongIntegerArray
#undef MLReleaseLowLevelDeviceName
#undef MLReleaseNetworkAddressList
#undef MLReleaseParameters
#undef MLReleasePutArrayState
#undef MLReleaseReal128Array
#undef MLReleaseReal128List
#undef MLReleaseReal32Array
#undef MLReleaseReal32List
#undef MLReleaseReal64Array
#undef MLReleaseReal64List
#undef MLReleaseRealArray
#undef MLReleaseRealList
#undef MLReleaseShortIntegerArray
#undef MLReleaseString
#undef MLReleaseSymbol
#undef MLReleaseUCS2CompilerID
#undef MLReleaseUCS2ErrorMessage
#undef MLReleaseUCS2LinkName
#undef MLReleaseUCS2String
#undef MLReleaseUCS2Symbol
#undef MLReleaseUnicodeContainer
#undef MLReleaseUTF16CompilerID
#undef MLReleaseUTF16ErrorMessage
#undef MLReleaseUTF16LinkName
#undef MLReleaseUTF16String
#undef MLReleaseUTF16Symbol
#undef MLReleaseUTF32CompilerID
#undef MLReleaseUTF32ErrorMessage
#undef MLReleaseUTF32LinkName
#undef MLReleaseUTF32String
#undef MLReleaseUTF32Symbol
#undef MLReleaseUTF8CompilerID
#undef MLReleaseUTF8ErrorMessage
#undef MLReleaseUTF8LinkName
#undef MLReleaseUTF8String
#undef MLReleaseUTF8Symbol
#undef MLRequest
#undef MLRequestArgv
#undef MLRequestArgvCast
#undef MLRequestCast
#undef MLRequestToInteract
#undef MLRequestToInteractCast
#undef MLResolveLinkService
#undef MLScanString
#undef MLSeekMark
#undef MLSeekToMark
#undef MLServiceProtocolFromReference
#undef MLSetAllocParameter
#undef MLSetDefaultYieldFunction
#undef MLSetDeviceParameter
#undef MLSetDialogFunction
#undef MLSetEncodingParameter
#undef MLSetEnvIDString
#undef MLSetEnvironmentData
#undef MLSetError
#undef MLSetMessageHandler
#undef MLSetName
#undef MLSetResourceParameter
#undef MLSetSignalHandler
#undef MLSetSignalHandlerFromFunction
#undef MLSetSymbolReplacement
#undef MLSetThreadSafeLinksParameter
#undef MLSetUserBlock
#undef MLSetUserData
#undef MLSetYieldFunction
#undef MLShutdownLinkServer
#undef MLSleepYP
#undef MLStopBrowsingForLinkServices
#undef MLStopHandlingSignal
#undef MLStopLoggingStream
#undef MLStopLoggingStreamToFile
#undef MLStopRegisteringLinkService
#undef MLStopResolvingLinkService
#undef MLStopRegisteringLinkServiceForLink
#undef MLStringCharacter
#undef MLStringFirstPosFun
#undef MLStringToArgv
#undef MLTakeLast
#undef MLTestHead
#undef MLTestHeadWithArgCount
#undef MLTestString
#undef MLTestSymbol
#undef MLTestUCS2Head
#undef MLTestUCS2HeadWithArgCount
#undef MLTestUCS2String
#undef MLTestUCS2Symbol
#undef MLTestUTF16Head
#undef MLTestUTF16HeadWithArgCount
#undef MLTestUTF16String
#undef MLTestUTF16Symbol
#undef MLTestUTF32Head
#undef MLTestUTF32HeadWithArgCount
#undef MLTestUTF32String
#undef MLTestUTF32Symbol
#undef MLTestUTF8Head
#undef MLTestUTF8HeadWithArgCount
#undef MLTestUTF8String
#undef MLTestUTF8Symbol
#undef MLToLinkID
#undef MLTransferExpression
#undef MLTransferToEndOfLoopbackLink
#undef MLUCS2CompilerID
#undef MLUCS2ErrorMessage
#undef MLUCS2LinkName
#undef MLUTF16CompilerID
#undef MLUTF16ErrorMessage
#undef MLUTF16LinkName
#undef MLUTF32CompilerID
#undef MLUTF32ErrorMessage
#undef MLUTF32LinkName
#undef MLUTF8CompilerID
#undef MLUTF8ErrorMessage
#undef MLUTF8LinkName
#undef MLUnsetSignalHandler
#undef MLUserBlock
#undef MLUserCast
#undef MLUserData
#undef MLValid
#undef MLVersionNumbers
#undef MLWaitForLinkActivity
#undef MLWaitForLinkActivityWithCallback
#undef MLWaitForNewLinkFromLinkServer
#undef MLYieldFunction
#undef MLYielderCast
#undef MLinkEnvironment


/*---------------------------------------------------------------------
 * Public API related symbols
 */
/* in mltypes.h */
#undef MLPointer
#undef MLENV
#undef MLEnvironment
#undef MLEnvironmentParameter
#undef MLINK
#undef MLMARK


/*---------------------------------------------------------------------
 * Public API related symbols used for function return type
 */
/* used by kernel and FE */
#undef MLMessageHandlerObject
#undef MLYieldFunctionObject
#undef mlint64
#undef mlextended_double

/* 
 * ATTENTION: mlapi_result , mlapi_token , mldlg_result
 * Use 'int' instead of these. These were replaced with int for MLINTERFACE >=3.
 * Used in a few places in kernel and FE.
 *
 * ATTENTION: MLSUCCESS , MLFAILURE
 * defined in mltypes.h. This is for internal use.
 * These is related to the above types. Return type is changed to int for MLINTERFACE >=3,
 * thus use 0 for MLFAILURE  1 for MLSUCCESS as described in document.
 */


/* part of API, but not used in kernel nor FE. may remove later */
#undef MLMessageHandlerType
#undef MLYieldFunctionType


/*---------------------------------------------------------------------
 * Public API related symbols used for function argement type
 */
/* used by kernel or FE */
#undef MLLinkWaitCallBackObject
#undef MLServiceRef
#undef MLSignalHandlerType
#undef MLUserFunction
#undef MLUserFunctionType
#undef MLUserFunctionTypePointer
#undef MLYieldFunctionObject
#undef MLYieldParameters

/* part of APIs but not used in kernel nor FE. may remove later */
#undef MLAllocator
#undef MLAllocatorp
#undef MLDeallocator
#undef MLDeallocatorp
#undef MLLinkServer
#undef MLNewLinkCallbackFunction
#undef MLOldStringPositionPointer
#undef MLStringFirstPosFun
#undef MLUnicodeContainer
#undef MLUnicodeContainerType
#undef MLAllocatorProcPtr
#undef MLDeallocatorProcPtr
#undef MLHandlerProcPtr
#undef MLUserProcPtr
#undef MLYielderProcPtr
#undef MLYieldFunctionType
/* in mlalert.h */
#undef MLDialogProcPtr
#undef MLAlertProcPtr
#undef MLRequestProcPtr
#undef MLConfirmProcPtr
#undef MLRequestArgvProcPtr
#undef MLRequestToInteractProcPtr


/* in mlvers.h used by NewParameters() */
#undef MLREVISION
#undef MLAPIREVISION


/*---------------------------------------------------------------------
 * Public symbol from typedef
 */
#undef mltimeval  /* may capitalize to distingush public symbol */
#undef MLParametersPointer


/*---------------------------------------------------------------------
 * Public symbols from enum
 */
/* values for devinfo_selector */
#undef MLTerminateMessage
#undef MLInterruptMessage
#undef MLAbortMessage
#undef MLEndPacketMessage
#undef MLSynchronizeMessage
#undef MLImDyingMessage
#undef MLWaitingAcknowledgment
#undef MLMarkTopLevelMessage
#undef MLLinkClosingMessage
#undef MLAuthenticateFailure
#undef MLSuspendActivitiesMessage
#undef MLResumeActivitiesMessage
#undef MLFirstUserMessage
#undef MLLastUserMessage

/* MLSetDialogFunction() args for long funcnum */
#undef MLAlertFunction
#undef MLRequestFunction
#undef MLConfirmFunction
#undef MLRequestArgvFunction
#undef MLRequestToInteractFunction
#undef MLDialogFunctionType

/* MLNewUnicodeContainer arg enum type */
#undef MLUnicodeContainerType


/*---------------------------------------------------------------------
 * MPREP symbols
 */
/* public */
#undef mlapi_packet
#undef MLMain

#endif /* _UNBRAND_H_ */
/*****************************************************************************
 * END - Unbrand
 *****************************************************************************/




/********************************************************/


#endif /* _WSTP_H */
