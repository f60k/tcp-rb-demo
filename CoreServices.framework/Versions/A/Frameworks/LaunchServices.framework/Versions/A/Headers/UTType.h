/*
     File:       LaunchServices/UTType.h
 
     Contains:   Public interfaces for Uniform Type Identification
 
     Version:    LaunchServices-283~1
 
     Copyright:  � 2003-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __UTTYPE__
#define __UTTYPE__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif


#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================================================== */
/* Uniform Type Identification API                                                                          */
/* ======================================================================================================== */
/*
    Uniform Type Identification Primer

    Uniform Type Identifiers (or UTIs) are strings which uniquely identify
    abstract types. They can be used to describe a file format or an
    in-memory data type, but can also be used to describe the type of
    other sorts of entities, such as directories, volumes, or packages.

    The syntax of a uniform type identifier looks like a bundle identifier.
    It has the form of a reversed DNS name, although some special top-level 
    UTI domains are reserved by Apple and are outside the current IANA 
    top-level Internet domain name space.

    Examples:

        public.jpeg
        public.utf16-plain-text
        com.apple.xml-property-list
        com.apple.appleworks.doc

    Types which are standard or not controlled by any one organization 
    are declared in the "public" domain. Currently, public types may  
    be declared only by Apple.

    Types specific to Mac OS are declared with identifiers in the 
    com.apple.macos domain.

    Third parties should declare their own uniform type identifiers
    in their respective registered Internet domain spaces.

    Type declarations appear in bundle property lists and tell
    the system several things about a type, including the following:

    Conformance

    A type may "conform" to one or more other types. For example, the
    type com.apple.xml-property-list conforms to both the
    com.apple.property-list and public.xml types. The public.xml 
    type in turn conforms to type public.text. Finally, type public.text  
    conforms to public.data, which is the base type for all types 
    describing bytes stream formats. Conformance relationships between 
    types are established in type declarations.

    Conformance relationships establish a multiple inheritanace hierarchy
    between types. Type property values may be inherited at runtime
    according to the conformance relationships for each type. When a type's 
    declaration does not include a value for particular type property, 
    then the type's supertypes are searched for a value. Supertypes are 
    searched depth-first, in the order given in the type declaration. 
    This is the only way in which the declared order of the conforms-to 
    supertypes is significant.

    Tags

    A "tag" is a string which indicates a type in some other type 
    identification space, such as a filename extension, MIME Type,
    or NSPboardType. Each type declaration may include a 
    "tag specification", which is a dictionary listing all of the 
    tags associated with the type.

    A tag's "class" is the namespace of a tag: filename extension, 
    MIME type, OSType, etc. Tag classes are themselves identified by 
    uniform type identifiers so that the set of valid tag classes is 
    easily extendend in the future.

    Other Type Properties

    Type declarations may include several other properties: a localizable
    user description of the type, the name of an icon resource in
    the declaring bundle, a reference URL identifying technical 
    documentation about the type itself, and finally a version number, 
    which can be incremented as a type evolves. All of these properties
    are optional.

    Exported vs. Imported Type Declarations

    Type declarations are either exported or imported. An exported
    type declaration means that the type itself is defined or owned 
    by the organization making the declaration. For example, a propietary
    document type declaration should only be exported by the application
    which controls the document format.

    An imported declatation is for applications which depend on the
    existence of someone else's type declaration. If application A can
    open application B's document format, then application A makes
    an imported declaration of application B's document type so that
    even if application B is not present on the system, there is an
    acessible declaration of its document type.

    An exported declaration of a particular type identifier is always
    preferred over an imported declaration.

    Example XML Type Declaration

    Appearing below is an XML excerpt from a bundle Info.plist file which 
    declares the public type "public.jpeg":
    
        <key>UTExportedTypeDeclarations</key>
        <array>
            <dict>
                <key>UTTypeIdentifier</key>
                <string>public.jpeg</string>
                <key>UTTypeDescription</key>
                <string>JPEG image</string>
                <key>UTTypeIconFile</key>
                <string>public.jpeg.icns</string>
                <key>UTTypeConformsTo</key>
                <array>
                    <string>public.image</string>
                </array>
                <key>UTTypeTagSpecification</key>
                <dict>
                    <key>com.apple.ostype</key>
                    <string>JPEG</string>
                    <key>public.filename-extension</key>
                    <array>
                        <string>jpeg</string>
                        <string>jpg</string>
                    </array>
                    <key>public.mime-type</key>
                    <string>image/jpeg</string>
                </dict>
            </dict>
        </array>


    Dynamic Type Identifiers

    Uniform Type Identifiation uses dynamic type identifiers to
    represent types for which no identifier has been declared. A
    dynamic type identifier is syntactially a regular uniform
    type identifier in the "dyn" domain. However, after the
    initial domain label, a dynamic type identifier is an 
    opaque encoding of a tag specification. Dynamic type 
    identifiers cannot be declared. They are generated on-demand
    with whatever type information is available at the time, often 
    a single (otherwise unknown) type tag.

    A dynamic identifier therefore carries within it a minimal
    amount of type information, but enough to work well with the
    Uniform Type Identification API. For example, a client can
    extract from a dynamic type identifier the original tag
    specification with which it was created. A client can also
    test a dynamic type identifier for equality to another
    uniform type identifier. If the dynamic identifier's
    tag specification is a subset of the other identifier's
    tags, the two are considered equal.

    Dynamic type identifiers do not express the full richness
    of type information associated with a declared type 
    identifier, but dynamic type identifiers allow the behavior
    to degrade gracefully in the presence of incomplete 
    declared type information.

    A dynamic type identifier may be transmitted across processes
    on a given system, but it should never be stored persistently
    or transmitted over the wire to another system. In particular,
    dynamic identifiers should not appear in bundle info property
    lists, and they will generally be ignored when they do. Apple 
    reserves the right to change the opaque format of dynamic
    identifiers in future versions of Mac OS X.
*/

/*
    Type Declaration Dictionary Keys

    The following keys are used in type declarations
*/
/*
 *  kUTExportedTypeDeclarationsKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTExportedTypeDeclarationsKey              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTImportedTypeDeclarationsKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTImportedTypeDeclarationsKey              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTTypeIdentifierKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeIdentifierKey                        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTTypeTagSpecificationKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeTagSpecificationKey                  AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTTypeConformsToKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeConformsToKey                        AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTTypeDescriptionKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeDescriptionKey                       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTTypeIconFileKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeIconFileKey                          AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTTypeReferenceURLKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeReferenceURLKey                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTTypeVersionKey
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTypeVersionKey                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


/*
    Type Tag Classes

    The following constant strings identify tag classes for use 
    when converting uniform type identifiers to and from
    equivalent tags.
*/
/*
 *  kUTTagClassFilenameExtension
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTagClassFilenameExtension                AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTTagClassMIMEType
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTagClassMIMEType                         AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTTagClassNSPboardType
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTagClassNSPboardType                     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
/*
 *  kUTTagClassOSType
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kUTTagClassOSType                           AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 *  UTTypeCreatePreferredIdentifierForTag()
 *  
 *  Discussion:
 *    Creates a uniform type identifier for the type indicated by the
 *    specified tag. This is the primary function to use for going from
 *    tag (extension/MIMEType/OSType) to uniform type identifier.
 *    Optionally, the returned type identifiers must conform to the
 *    identified "conforming-to" type argument. This is a hint to the
 *    implementation to constrain the search to a particular tree of
 *    types. For example, the client may want to know the type
 *    indicated by a particular extension tag. If the client knows that
 *    the extension is associated with a directory (rather than a
 *    file), the client may specify "public.directory" for the
 *    conforming-to argument. This will allow the implementation to
 *    ignore all types associated with byte data formats (public.data
 *    base type). If more than one type is indicated, preference is
 *    given to a public type over a non-public type on the theory that
 *    instances of public types are more common, and therefore more
 *    likely to be correct. When there a choice must be made between
 *    multiple public types or multiple non-public types, the selection
 *    rules are undefined. Clients needing finer control should use
 *    UTTypeCreateAllIdentifiersWithTag. If no declared type is
 *    indicated, a dynamic type identifier is generated which satisfies
 *    the parameters.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inTagClass:
 *      the class identifier of the tag argument
 *    
 *    inTag:
 *      the tag string
 *    
 *    inConformingToUTI:
 *      the identifier of a type to which the result must conform
 *  
 *  Result:
 *    a new CFStringRef containing the type identifier, or NULL if
 *    inTagClass is not a known tag class
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
UTTypeCreatePreferredIdentifierForTag(
  CFStringRef   inTagClass,
  CFStringRef   inTag,
  CFStringRef   inConformingToUTI)       /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  UTTypeCreateAllIdentifiersForTag()
 *  
 *  Discussion:
 *    Creates an array of all uniform type identifiers indicated by the
 *    specified tag. An overloaded tag (e.g., an extension used by
 *    several applications for different file formats) may indicate
 *    multiple types. If no declared type identifiers have the
 *    specified tag, then a single dynamic type identifier will be
 *    created for the tag. Optionally, the returned type identifiers
 *    must conform to the identified "conforming-to" type argument.
 *    This is a hint to the implementation to constrain the search to a
 *    particular tree of types. For example, the client may want to
 *    know the type indicated by a particular extension tag. If the
 *    client knows that the extension is associated with a directory
 *    (rather than a file), the client may specify "public.directory"
 *    for the conforming-to argument. This will allow the
 *    implementation to ignore all types associated with byte data
 *    formats (public.data base type).
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inTagClass:
 *      the class identifier of the tag argument
 *    
 *    inTag:
 *      the tag string
 *    
 *    inConformingToUTI:
 *      the identifier of a type to which the results must conform
 *  
 *  Result:
 *    An array of uniform type identifiers, or NULL if inTagClass is
 *    not a known tag class
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern CFArrayRef 
UTTypeCreateAllIdentifiersForTag(
  CFStringRef   inTagClass,
  CFStringRef   inTag,
  CFStringRef   inConformingToUTI)       /* can be NULL */    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  UTTypeCopyPreferredTagWithClass()
 *  
 *  Discussion:
 *    Returns the identified type's preferred tag with the specified
 *    tag class as a CFString. This is the primary function to use for
 *    going from uniform type identifier to tag. If the type
 *    declaration included more than one tag with the specified class,
 *    the first tag in the declared tag array is the preferred tag.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *    
 *    inTagClass:
 *      the class of tags to return
 *  
 *  Result:
 *    an array of tags (as CFStrings), or NULL if there are no tags
 *    with the specified class.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
UTTypeCopyPreferredTagWithClass(
  CFStringRef   inUTI,
  CFStringRef   inTagClass)                                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  UTTypeEqual()
 *  
 *  Discussion:
 *    Compares two identified types for equality. Types are equal if
 *    their identifier strings are equal using a case-insensitive
 *    comparison. In addition, if one or both of the identifiers is a
 *    dynamic identifier, then the types are equal if either
 *    identifier's tag specification is a subset of the other
 *    identifier's tag specification.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI1:
 *      a uniform type identifier
 *    
 *    inUTI2:
 *      another uniform type identifier
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
UTTypeEqual(
  CFStringRef   inUTI1,
  CFStringRef   inUTI2)                                       AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  UTTypeConformsTo()
 *  
 *  Discussion:
 *    Tests for a conformance relationship between the two identified
 *    types. Returns true if the types are equal, or if the first type
 *    conforms, directly or indirectly, to the second type.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier to test
 *    
 *    inConformsToUTI:
 *      the uniform type identifier against which to test conformance.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
UTTypeConformsTo(
  CFStringRef   inUTI,
  CFStringRef   inConformsToUTI)                              AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  UTTypeCopyDescription()
 *  
 *  Discussion:
 *    Returns the localized, user-readable type description string
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *  
 *  Result:
 *    a localized string, or NULL of no type description is available
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
UTTypeCopyDescription(CFStringRef inUTI)                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  UTTypeCopyDeclaration()
 *  
 *  Discussion:
 *    Returns the identified type's declaration dictionary, as it
 *    appears in the declaring bundle's info property list. This the
 *    access path to other type properties for which direct access is
 *    rarely needed.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *  
 *  Result:
 *    a tag declaration dictionary, or NULL if the type is not declared
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern CFDictionaryRef 
UTTypeCopyDeclaration(CFStringRef inUTI)                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  UTTypeCopyDeclaringBundleURL()
 *  
 *  Discussion:
 *    Returns the URL of the bundle containing the type declaration of
 *    the identified type.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inUTI:
 *      the uniform type identifier
 *  
 *  Result:
 *    a URL, or NULL if the bundle cannot be located.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern CFURLRef 
UTTypeCopyDeclaringBundleURL(CFStringRef inUTI)               AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  UTCreateStringForOSType()
 *  
 *  Discussion:
 *    A helper function to canonically encode an OSType as a CFString
 *    suitable for use as a tag argument.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inOSType:
 *      the OSType value to encode
 *  
 *  Result:
 *    a new CFString representing the OSType, or NULL if the argument
 *    is 0 or '????'
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
UTCreateStringForOSType(OSType inOSType)                      AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;



/*
 *  UTGetOSTypeFromString()
 *  
 *  Discussion:
 *    A helper function to canonically decode a string-encoded OSType
 *    back to the original OSType value.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inString:
 *      the string to decode
 *  
 *  Result:
 *    the OSType value encoded in the string, or 0 if the string is not
 *    a valid encoding of an OSType
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in ApplicationServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSType 
UTGetOSTypeFromString(CFStringRef inString)                   AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;




#ifdef __cplusplus
}
#endif

#endif /* __UTTYPE__ */

