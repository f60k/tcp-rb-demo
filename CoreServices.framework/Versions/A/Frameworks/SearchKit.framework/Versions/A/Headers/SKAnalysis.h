/*
     File:       SearchKit/SKAnalysis.h
 
     Contains:   SearchKit Interfaces.
 
     Version:    SearchKit-218~4
 
     Copyright:  � 2003-2006 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __SKANALYSIS__
#define __SKANALYSIS__

#ifndef __CFSTRING__
#include <CoreFoundation/CFString.h>
#endif


/* 
    The possible text analysis properties of an index, used by
    SKIndexCreateWithURL or SKIndexCreateWithMutableData.
 */


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

/*
 *  kSKLanguageTypes
 *  
 *  Summary:
 *    An array of string objects that specify the languages to use for
 *    indexing.
 *  
 *  Discussion:
 *    The kSKLanguageTypes constant is an optional key in the text
 *    analysis properties dictionary whose corresponding value is an
 *    array of string objects that together specify the languages to
 *    use for indexing. Each string should be a two character ISO 639-1
 *    code indicating a language to use. For example, 'en' for English,
 *    'ja' for Japanese, and so on. If this key is not present,
 *    SearchKit uses the Mac OS X preferences system to determine the
 *    primary language from the user's locale.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kSKLanguageTypes                            AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kSKMinTermLength
 *  
 *  Summary:
 *    The minimum term length to index.
 *  
 *  Discussion:
 *    The kSKMinTermLength constant is an optional key in the text
 *    analysis properties dictionary whose corresponding value is a
 *    CFNumber object containing the minimum term length to index. If
 *    this key is not present, SearchKit indexing defaults to a minimum
 *    term length of 1.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kSKMinTermLength                            AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kSKSubstitutions
 *  
 *  Summary:
 *    A dictionary of term substitutions.
 *  
 *  Discussion:
 *    The kSKSubstitutions constant is an optional key in the text
 *    analysis properties dictionary whose corresponding value is a
 *    CFDictionary object containing term substitutions.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kSKSubstitutions                            AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kSKStopWords
 *  
 *  Summary:
 *    A set of stop words--words not to index.
 *  
 *  Discussion:
 *    The kSKStopWords constant is an optional key in the text analysis
 *    properties dictionary whose corresponding value is a CFSet object
 *    containing words not to index.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kSKStopWords                                AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kSKProximityIndexing
 *  
 *  Summary:
 *    The proximity indexing option.
 *  
 *  Discussion:
 *    The kSKProximityIndexing constant is an optional key in the text
 *    analysis properties dictionary whose corresponding value is a
 *    CFBoolean object containing the proximity indexing option. If
 *    this key is not present, SearchKit indexing defaults to not doing
 *    proximity indexing.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kSKProximityIndexing                        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kSKMaximumTerms
 *  
 *  Summary:
 *    The maximum unique terms per document to index.
 *  
 *  Discussion:
 *    The kSKMaximumTerms constant is an optional key in the text
 *    analysis properties dictionary whose corresponding value is a
 *    CFNumber object containing the maximum unique terms per document
 *    to index. If this key is not present, SearchKit indexing defaults
 *    to 2000. If the value of this key is zero, there is no limit of
 *    the maximum unique terms per document to index.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kSKMaximumTerms                             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kSKTermChars
 *  
 *  Summary:
 *    The extra valid characters for indexing.
 *  
 *  Discussion:
 *    The kSKTermCharSet constant is an optional key in the text
 *    analysis properties dictionary whose corresponding value is a
 *    CFString object containing the extra valid characters that a
 *    valid term (word) can contain. Used for indexing and query
 *    processing.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kSKTermChars                                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kSKStartTermChars
 *  
 *  Summary:
 *    The extra valid characters for indexing.
 *  
 *  Discussion:
 *    The kSKStartTermChars constant is an optional key in the text
 *    analysis properties dictionary whose corresponding value is a
 *    CFString object containing the extra valid characters that can
 *    occur as the first character of a term. Overrides the
 *    kSKTermChars for the first character of a term.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kSKStartTermChars                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kSKEndTermChars
 *  
 *  Summary:
 *    The extra valid characters for indexing.
 *  
 *  Discussion:
 *    The kSKEndTermChars constant is an optional key in the text
 *    analysis properties dictionary whose corresponding value is a
 *    CFString object containing the extra valid characters that can
 *    occur as the last character of a term. Overrides the kSKTermChars
 *    for the last character of a term.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kSKEndTermChars                             AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


#endif /* __SKANALYSIS__ */

