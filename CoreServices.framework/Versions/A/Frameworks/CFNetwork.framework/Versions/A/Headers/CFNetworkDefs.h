/*
     File:       CFNetwork/CFNetworkDefs.h
 
     Contains:   CoreFoundation Network header
 
     Version:    CFNetwork-219~1
 
     Copyright:  � 2001-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/

#ifndef __CFNETWORK_DEFS_H_
#define __CFNETWORK_DEFS_H_




/* Required to build on platforms that do not have MacTypes.h */
#if !defined(__MACH__)
#ifndef CALLBACK_API_C
    #define CALLBACK_API_C(_type, _name)            _type ( * _name)
#endif
#endif /* __MACH__ */

/* Standard incantation for exporting/importing DLL symbols */
#if defined(__WIN32__)
  #if defined(CFNETWORK_BUILDING_DLL)
        #define APPLE_WIN_API __declspec(dllexport) extern
 #else
      #define APPLE_WIN_API __declspec(dllimport) extern
 #endif
#else
    #define APPLE_WIN_API extern
#endif


#endif //__CFNETWORK_DEFS_H_


