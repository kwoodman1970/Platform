// ============================================================================================
//
// platform.h
//
// ============================================================================================

/*
This header file (part of a set of header files) defines macros for cross-platform software
development and attempts to correct some compilers' deficiencies.  Three types of macros are
defined:  platform properties, standard header file detection and pragma directives.

NOTE:  This header file can be included multiple times, though steps are taken to minimize
re-processing.
*/

// ============================================================================================
// DESIGN NOTES
// ============================================================================================

/*
The object of this file is to provide a set of platform-independent macros that, when expanded,
will provide compiler-specific compilation instructions.  Three types of macros are defined:
platform properties, standard header file detection and pragma directives.

Platform property macros provide a common means of identifying such things as compiler,
operating system and CPU.  Each compiler has predefined macros or manifest constants to allow
conditional compilation tailored for different platforms.  Unfortunately, these macros aren't
consistent among compiler manufacturers -- and sometimes even among different versions of the
same family of compilers.  The platform property macros defined here bring order to this chaos.
For example, instead of coding:

  #if (((defined(__TURBOC__) && (defined(__WIN32__)) ||
       ((defined(_MSC_VER) && (defined(_WIN32)))

    // compile Windows-specific fragment

  #else

    // compile non-Windows fragment

  #endif

it would be possible to code:

  #if (PF_OS == PF_WIN32)
    // compile this Windows-specific fragment
  #else
    // compile this non-Windows fragment
  #endif

Standard header file detection macros perform a similar function.  Each compiler uses a
different naming format for the "guard macros" in its standard C/C++ header files.  Sometimes
it's nice to know if a particular header file has been included -- for example, whether or
not to compile stream shift-in and shift-out operators for a class (<iostream.h> could be
included by the class's header file, but what happens if the newer <iostream> has been included
earlier?).  Standard header file detection macros bring order to this chaos by defining macros
for each compiler-supplied header file that's available for inclusion.  The format of these
detection macros is "[x_]y[_z]", where "x" is a subdirectory, "y" is the header name and "z"
is an extension.  For example, if <iostream> has been included then IOSTREAM will be defined;
if <sys/types.h> has been included then SYS_TYPES_H will be defined.

Pragma directive macros are for use in (surprise, surprise) pragma directives.  Again,
different compilers use different pragma directives to accomplish identical tasks.  The pragma
directive macros (stop me if you've heard this before) bring order to this chaos by defining
macros that will expand to compiler-specific directives.  For example, instead of coding:

  #if defined(__TURBOC__)
    #pragma intrinsic -thisRoutineIsntIntrinsic
  #elif defined(_MSC_VER)
    #pragma function(thisRoutineIsntIntrinsic)
  #endif

it would be possible to code:

  #pragma PF_DECLARE_ROUTINE_NON_INTRINSIC(thisRoutineIsntIntrinsic)

DANGER!!!  Not all compilers perform macro replacement before processing #pragma directives,
which means that pragma macros have no effect on these compilers.

This header file can be included multiple times.  This will allow the standard header file
detection macros to be updated.  Suppose the following header files are included (in this
example, assume that this is what the preprocessor sees):

  #include <platform.h>    // included for the first time -- by source file
  #include "eggtimer.h"    // EggTimer class header file
    #include <limits.h>    // required for EggTimer inline methods (included by "eggtimer.h")
    #include <platform.h>  // included for the second time (included by "eggtimer.h")

If <platform.h> were only processed once then LIMITS_H wouldn't be defined for "eggtimer.h".
Note that ANSI C/C++ allows macros to be redeclared provided that they're identical.
*/

// ============================================================================================
// PLATFORM PROPERTY MACRO DEFINITIONS
// ============================================================================================

#ifndef PLATFORM_H

  /*
  Compiler type macros:
  */

  #define PF_UNKNOWN_COMPILER 0
  #define PF_BORLAND          1
  #define PF_GNU              2
  #define PF_MICROSOFT        3
  #define PF_WATCOM           4
  #define PF_DEC              5
  #define PF_NUMCOMPILERTYPES 6

  /*
  OS API type macros:
  */

  #define PF_UNKNOWN_OS  0
  #define PF_DOS         1
  #define PF_MACOS       2
  #define PF_NETWARE386  3
  #define PF_OS2         4
  #define PF_QNX         5
  #define PF_WIN16       6
  #define PF_WIN32       7
  #define PF_UNIX        8
  #define PF_VMS         9
  #define PF_NUMOSTYPES 10

  /*
  CPU type macros:
  */

  #define PF_UNKNOWN_CPU    0
  #define PF_AMD_29000      1
  #define PF_DEC_ALPHA      2
  #define PF_DEC_VAX        3
  #define PF_IBM_POWERPC    4
  #define PF_INTEL_X86      5
  #define PF_MIPS           6
  #define PF_MOTOROLA_68X00 7
  #define PF_NS_32000       8
  #define PF_NUMCPUTYPES    9

  /*
  Endian type macros
  */

  #define PF_ENDIAN_UNKNOWN 0
  #define PF_ENDIAN_BIG     1
  #define PF_ENDIAN_LITTLE  2

#endif

// ============================================================================================
// SYSTEM-SPECIFIC PLATFORM MACRO DEFINITIONS
// ============================================================================================

/*
Each compiler include file contains macros for its particular compiler type (it's organized
this way on the assumption that compiler manufacturers will try to maintain a large degree of
backward compatibility between versions, and most of the predefined macros will be the same or
very close to the same).

Each file MUST define the following macros (even if no value is assigned):

  PF_COMPILER      A "compiler type" value (see above)
  PF_COMPILER_VER  A unique compiler type version description -- preferably a number
  PF_OS            An "OS type" value (see above)
  PF_CPU           A "CPU type" value (see above)
  PF_STD_LIB_CALL  The calling convention for the C/C++ standard library
  PF_MULTITHREADED 1 means thread-safe compilation/linking, 0 means otherwise
  PF_DLL_EXPORT    The calling convention for exporting DLL funcions/routines
  PF_DLL_IMPORT    The calling convention for importing DLL funcions/routines

It's intended that "PF_COMPILER_VER" be used to distinguish between various versions of a
particular compiler type.  If possible, it should be a number so that it can be more easily
compared to other versions.  Most (if not all) compilers have a predefined macro that indicates
the compiler version, and this macro can often be used directly.

"PF_STD_LIB_CALL" is the call modifier for functions & routines that are to be called by the
standard library (for example, a comparison function for "qsort()" or a termination routine for
"atexit()").  This macro is intended to be included in the declarations of such functions &
routines.  For example, a comparison function for "qsort()" might be declared as:

  static PF_STD_LIB_CALL int compareRecords(const void*, const void*);

"PF_DLL_EXPORT" is a call modifier to make a function or routine exportable from a DLL (for
platforms that support DLL's).  "PF_DLL_IMPORT" makes a DLL function or routine available for a
program or another DLL to call.

Additionally, if a compiler doesn't support a native "bool" type then its compiler include file
should define the "PF_BOOL_NOT_BUILT_IN" macro to have a simulated bool type generated later on
by this file.

Each compiler include file should document all predefined macros for its particular compiler.
The standard C and C++ predefined macros  -- "__DATE__", "__FILE__", "__LINE__", "__STDC__",
"__TIME__" and "__cplusplus" -- aren't needed because they're common to all platforms and would
just take up comment space.
*/

#if defined(__TURBOC__)
  #include <platform/borland.h>
#elif defined(__GNUC__)
  #include <platform/gnu.h>
#elif defined(_MSC_VER)
  #include <platform/microsft.h>
#elif defined(__WATCOMC__)
  #include <platform/watcom.h>
#elif !defined(PLATFORM_H)

  /*
  The compiler can't be determined, so there's no way to know anything about the platform.
  Default values are used instead.
  */

  #define PF_COMPILER      PF_UNKNOWN_COMPILER
  #define PF_COMPILER_VER  0
  #define PF_OS            PF_UNKNOWN_OS
  #define PF_CPU           PF_UNKNOWN_CPU
  #define PF_STD_LIB_CALL
  #define PF_MULTITHREADED 0
  #define PF_DLL_IMPORT
  #define PF_DLL_EXPORT

#endif

// ============================================================================================
// SYSTEM-SPECIFIC PLATFORM MACRO DEFINITION VERIFICATIONS
// ============================================================================================

#if (defined(NDEBUG) && !defined(PLATFORM_H))

  #ifndef PF_COMPILER
    #error The compiler ID wasn't defined.
  #elif ((PF_COMPILER < PF_COMPILER_UNKNOWN) || (PF_COMPILER >= PF_NUMCOMPILERTYPES))
    #error The compiler ID isn't valid.
  #endif

  #ifndef PF_COMPILER_VER
    #error The compiler version wasn't defined.
  #endif

  #ifndef PF_OS
    #error The operating system type wasn't defined.
  #elif ((PF_OS < PF_OS_UNKNOWN) || (PF_OS >= PF_NUMOSTYPES))
    #error The operating system type isn't valid.
  #endif

  #ifndef PF_CPU
    #error The CPU type wasn't defined.
  #elif ((PF_CPU < PF_CPU_UNKNOWN) || (PF_CPU >= PF_NUMCPUTYPES))
    #error The CPU type isn't valid.
  #endif

  #ifndef PF_STD_LIB_CALL
    #error The standard library call style wasn't defined.
  #endif

  #ifndef PF_MULTITHREADED
    #error The single-or-multithreaded compilation mode wasn't defined.
  #endif

  #ifndef PF_DLL_IMPORT
    #error The DLL import call style wasn't defined.
  #endif

  #ifndef PF_DLL_EXPORT
    #error The DLL export call style wasn't defined.
  #endif

#endif

// ============================================================================================
// MORE GENERAL PLATFORM MACRO DEFINITIONS
// ============================================================================================

#ifndef PLATFORM_H

  #if (PF_CPU == PF_INTEL_X86)
    #define PF_ENDIAN PF_ENDIAN_LITTLE
  #endif

  #if (PF_CPU == PF_MOTOROLA_68X00)
    #define PF_ENDIAN PF_ENDIAN_BIG
  #endif

  #ifndef PF_ENDIAN
    #define PF_ENDIAN PF_ENDIAN_UNKNOWN
  #endif

  /*
  Need to determine endian for the following CPU's:

    PF_AMD_29000,
    PF_DEC_ALPHA,
    PF_DEC_VAX,
    PF_IBM_POWERPC,
    PF_MIPS,
    PF_NS_32000,
  */

#endif

// ============================================================================================
// COMPILER DEFICIENCY CORRECTIONS
// ============================================================================================

/*
If "bool" isn't a built-in C++ type then the "bool" class is included to simulate one.
*/

#ifdef PF_BOOL_NOT_BUILT_IN
  #include <platform/bool.h>
#endif

/*
The limits.h standard header file contains macros for the maxima and minima of all built-in
integer types but doesn't indicate how many bits each type have.  Bit sizes for these types are
defined here.

"sizeof()" can't be used to determine bit sizes because these macros may be used in "#if"
directives and ANSI C++ stipulates that "sizeof()" cannot appear in an "#if" directive.
Therefore, educated guesses are used instead.
*/

#ifdef LIMITS_H

  #if (SHRT_MAX == 0x7f)
    #define SHRT_BIT 8
  #elif (SHRT_MAX == 0x7fff)
    #define SHRT_BIT 16
  #elif (SHRT_MAX == 0x7fffffff)
    #define SHRT_BIT 32
  #elif (SHRT_MAX == 0x7fffffffffffffff)
    #define SHRT_BIT 64
  #elif (SHRT_MAX == 0x7fffffffffffffffffffffffffffffff)
    #define SHRT_BIT 128
  #else
    #error Can't determine the bit size of a short int.
  #endif

  #if (INT_MAX == 0x7f)
    #define INT_BIT 8
  #elif (INT_MAX == 0x7fff)
    #define INT_BIT 16
  #elif (INT_MAX == 0x7fffffff)
    #define INT_BIT 32
  #elif (INT_MAX == 0x7fffffffffffffff)
    #define INT_BIT 64
  #elif (INT_MAX == 0x7fffffffffffffffffffffffffffffff)
    #define INT_BIT 128
  #else
    #error Can't determine the bit size of an int.
  #endif

  #if (LONG_MAX == 0x7f)
    #define LONG_BIT 8
  #elif (LONG_MAX == 0x7fff)
    #define LONG_BIT 16
  #elif (LONG_MAX == 0x7fffffff)
    #define LONG_BIT 32
  #elif (LONG_MAX == 0x7fffffffffffffff)
    #define LONG_BIT 64
  #elif (LONG_MAX == 0x7fffffffffffffffffffffffffffffff)
    #define LONG_BIT 128
  #else
    #error Can't determine the bit size of a long int.
  #endif

#endif

// ============================================================================================
// GUARD MACRO DEFINITION
// ============================================================================================

#ifndef PLATFORM_H
  #define PLATFORM_H
#endif