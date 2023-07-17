// ============================================================================================
//
// compiler/borland.h
//
// ============================================================================================

#ifndef PF_BORLAND
  #error platform.h has not been included yet.
#endif

// ============================================================================================
// PLATFORM PROPERTY MACROS
// ============================================================================================

/*
The following was transcribed from the manual for Turbo C++ 3.0 for DOS:

  __CDECL__       This macro is specific to Borland's C and C++ family of compilers. It signals
                  that the -p flag was not used (the C radio button in the Entry/Exit Code
                  Generation dialog box). Set to the integer constant 1 if calling was not
                  used; otherwise, undefined.

  __COMPACT__     [These] six symbols are defined based on the memory model chosen at compile
  __HUGE__        time.
  __LARGE__
  __MEDIUM__      Only one is defined for any given compilation; the others, by definition, are
  __SMALL__       undefined.  For example, if you compile with the small model, the __SMALL__
  __TINY__        macro is defined and the rest are not, so that the directive

                    #if defined(__SMALL__)

                  will be true, while

                    #if defined(__LARGE__)

                  (or any of the others) will be false. The actual value for any of these
                  defined macros is 1.

  __MSDOS__       This macro is specific to Borland's C and C++ family of compilers. It
                  provides the integer constant 1 for all compilations.

  __OVERLAY__     This macro is specific to Borland's C and C++ family of compilers. It is
                  predefined to be 1 if you compile a module with the -Y option (enable overlay
                  support). If you don't enable overlay support, this macro is undefined.

  __PASCAL__      This macro is specific to Borland's C and C++ family of compilers. It signals
		  that the -p flag or the Pascal calling convention (O|C|C|Exit/Entry) has been
                  used. The macro is set to the integer constant 1 if used; otherwise, it
                  remains undefined.

  __TCPLUSPLUS__  This macro is specific to Borland's C and C++ family of compilers. It is only
                  defined for C++ compilation. If you've selected C++ compilation, it is
                  defined as 0x300, a hexadecimal constant. This numeric value will increase in
                  later releases.

  __TEMPLATES__   This macro is specific to Borland's C and C++ family of compilers. It is
                  defined as 1 for C++ files (meaing that Turbo C++ supports templates); it's
                  undefined otherwise.

  __TURBOC__      This macro is specific to Borland's C and C++ family of compilers. It is
                  defined as 0x400, a hexadecimal constant. This numeric value will increase in
                  later releases.

***********************************************************************************************

The following was taken from the help files of Turbo C++ 4.5 for Windows 3.1:

  __BCOPT__      1      Defined in any compiler that has an optimizer

  __BCPLUSPLUS__ 0x340  Defined if you've selected C++ compilation; will increase in later
                        releases

  __BORLANDC__   0x460  Version number

  __CDECL__      1      Defined if Calling Convention is set to C; otherwise undefined

  __CONSOLE__           Available only for the 32-bit compiler. When defined, the macro
                        indicates that the program is a console application.

  __DLL__        1      Defined if Prolog/Epilog Code Generation is set to Windows DLL;
                        otherwise undefined

  __MSDOS__      1      Integer constant

  __MT__         1      Defined only for the 32-bit compiler if the -WM option is used. It
                        specifies that the multithread library is to be linked.

  __OVERLAY__    1      Specific to the Borland C and C++ family of compilers. It is predefined
                        as 1 if you compile a module with the -Y option (enable overlay
                        support). If you do not enable overlay support, this macro is
                        undefined.

  __PASCAL__     1      Defined if Calling Convention is set to Pascal; otherwise undefined

  __TCPLUSPLUS__ 0x340  Version number

  __TEMPLATES__  1      Specific to the Borland C and C++ family of compilers. It is defined as
                        1 for C++ files (meaning that Turbo C++ for Windows supports
			templates); otherwise, it is undefined.

  __TLS__        1      Always true when the 32-bit compiler is used.

  __TURBOC__     0x460  Will increase in later releases

  __WIN32__      1      Always defined for the 32-bit compiler. It is defined for console and
                        GUI applications.

  _Windows              Defined for Windows 16- and 32-bit compilations

***********************************************************************************************

The following was taken from the help files of Borland C++ 2.0 for OS/2:

  __BCPLUSPLUS__  This macro is specific to Borland's C and C++ family of compilers. It is only
                  defined for C++ compilation. If you've selected C++ compilation, it is
                  defined as 0x320, a hexadecimal constant. This numeric value will increase in
                  later releases.

  __BORLANDC__    This macro is specific to Borland's C and C++ family of compilers. It is
                  defined as 0x400, a hexadecimal constant. This numeric value will increase in
                  later releases.

  __CDECL__       This macro is specific to Borland's C and C++ family of compilers. It signals
                  that the -p flag was not used (the C calling convention in the Code
                  Generation section in the Settings Notebook). Set to the integer constant 1
                  if calling was not used; otherwise, undefined.

  __DLL__         This macro is specific to Borland's C and C++ family of compilers. It is
                  defined as 1 if you compile a module to generate code for PM DLLs; otherwise
                  it remains undefined.

  __MT__          This macro is defined as 1 if the -sm option is used and specifies that the
		  multithread library is to be linked.

  __OS2__         This macro is specific to Borland's C/C++ family of compilers. It provides
                  the integer constant 1 for all compilations.

  __PASCAL__      This macro is specific to Borland's C and C++ family of compilers. It signals
		  that the -p flag or the Pascal calling convention has been used. The macro is
                  set to the integer constant 1 if used; otherwise, it remains undefined.

  __TCPLUSPLUS__  This macro is specific to Borland's C and C++ family of compilers. It is only
		  defined for C++ compilation. If you've selected C++ compilation, it is
                  defined as 0x0320, a hexadecimal constant. This numeric value will increase
		  in later releases.

  __TEMPLATES__   This macro is specific to Borland's C and C++ family of compilers. It is
                  defined as 1 for C++ files (meaning that Borland C++ supports templates);
                  it's undefined otherwise.

  __TURBOC__      This macro is specific to Borland's C and C++ family of compilers. It is
                  defined as 0x0400, a hexadecimal constant. This numeric value will increase
		  in later releases.

***********************************************************************************************

The following was taken from the help files of Borland C++ Builder 1.0 for Windows 9x/NT:

  __BCOPT__         1      Defined in any compiler that has an optimizer.

  __BCPLUSPLUS__    0x520  Defined if you've selected C++ compilation; will increase in later
                           releases.
  __BORLANDC__      0x520  Version number.

  __CDECL__         1      Defined if Calling Convention is set to cdecl; otherwise undefined.

  _CHAR_UNSIGNED    1      Defined by default indicating that the default char is unsigned
                           char. Use the -K option to undefine this macro.

  __CONSOLE__              When defined, the macro indicates that the program is a console
                           application.

  _CPPUNWIND        1      Enable stack unwinding.This is true by default; use -xd- to disable.

  __DLL__           1      Defined whenever the -WD option is used; otherwise undefined.

  _M_IX86           1      Always defined. The default  value is 300. You can change the value
                           to 400 or 500 by using the /4 or /5 options.

   __MSDOS__        1      Integer constant.

  __MT__            1      Defined only if the -WM option is used. It specifies that the
                           multithread library is to be linked.

  __PASCAL__        1      Defined if Calling Convention is set to Pascal; otherwise undefined.

  __TCPLUSPLUS__    0x520  Version number.

  __TEMPLATES__     1      Defined as 1 for C++ files (meaning that templates are supported);
                           otherwise, it is undefined.

  __TLS__           1      Thread Local Storage. Always true in C++Builder.

  __TURBOC__        0x520  Will increase in later releases.

  _WCHAR_T          1      Defined only for C++ programs to indicate that wchar_t is an
                           intrinsically defined data type.

  _WCHAR_T_DEFINED  1      Defined only for C++ programs to indicate that wchar_t is an
                           intrinsically defined data type.

  _Windows                 Defined for Windows-only code.

  __WIN32__         1      Defined for console and GUI applications.

***********************************************************************************************

The following was taken from the help files of Borland C++ Builder 5.0 for Windows 9x/NT:

  __BCOPT__         1               Defined in any compiler that has an optimizer.

  __BCPLUSPLUS__    0x0550          Defined if you've selected C++ compilation; will increase
                                    in later releases.

  __BORLANDC__      0x0550          Version number.

  __CDECL__         1               Defined if Calling Convention is set to cdecl; otherwise
                                    undefined.

  _CHAR_UNSIGNED    1               Defined by default indicating that the default char is
                                    unsigned char. Use the -K compiler option to undefine this
                                    macro.

  __CODEGUARD__                     Defined whenever one of the CodeGuard compiler options is
				    used; otherwise it is undefined.

  __CONSOLE__                       When defined, the macro indicates that the program is a
                                    console application.

  _CPPUNWIND        1               Enable stack unwinding. This is true by default; use -xd-
				    to disable.

  __DLL__           1               Defined whenever the -WD compiler option is used; otherwise
                                    it is undefined.

  __FLAT__          1               Defined when compiling in 32-bit flat memory model.

  __FUNC__          String literal  Name of the current function being processed. More details.

  _M_IX86           1               Always defined. The default value is 300. You can change
                                    the value to 400 or 500 by using the /4 or /5 compiler
                                    options.

  __MSDOS__         1               Integer constant.

  __MT__            1               Defined only if the -tWM option is used. It specifies that
                                    the multithread library is to be linked.

  __PASCAL__        1               Defined if Calling Convention is set to Pascal; otherwise
                                    undefined.

  __STDC__          1               Defined if you compile with the -A compiler option;
                                    otherwise, it is undefined.

  __TCPLUSPLUS__    0x0550          Version number.

  __TEMPLATES__     1               Defined as 1 for C++ files (meaning that templates are
                                    supported); otherwise, it is undefined.

  __TLS__           1               Thread Local Storage. Always true in C++Builder.

  __TURBOC__        0x0550          Will increase in later releases.

  _WCHAR_T          1               Defined only for C++ programs to indicate that wchar_t is
                                    an intrinsically defined data type.

  _WCHAR_T_DEFINED  1               Defined only for C++ programs to indicate that wchar_t is
                                    an intrinsically defined data type.

  _Windows                          Defined for Windows-only code.

  __WIN32__         1               Defined for console and GUI applications.

*/

#ifndef COMPILER_BORLAND_H

  #define PF_COMPILER       PF_BORLAND

  #ifdef __TCPLUSPLUS__
    #define PF_COMPILER_VER __TCPLUSPLUS__
  #else
    #define PF_COMPILER_VER __TURBOC__
  #endif

  #if (defined(__MSDOS__) && !defined(_Windows))
    #define PF_OS           PF_DOS
  #elif defined(__OS2__)
    #define PF_OS           PF_OS2
  #elif (defined(_Windows) && !defined(__WIN32__))
    #define PF_OS           PF_WIN16
  #elif defined(__WIN32__)
    #define PF_OS           PF_WIN32
  #else
    #define PF_OS           PF_UNKNOWN_OS
  #endif

  #define PF_CPU            PF_INTEL_X86

  #if (defined(_Windows) || defined(__OS2__))
    #define PF_STD_LIB_CALL _USERENTRY
  #else
    #define PF_STD_LIB_CALL
  #endif

  #ifdef __MT__
    #define PF_MULTITHREADED 1
  #else
    #define PF_MULTITHREADED 0
  #endif

  #ifdef __WIN32__
    #define PF_DLL_IMPORT   _import
  #else
    #define PF_DLL_IMPORT
  #endif

  #if (defined(_Windows) || defined(__OS2__))
    #define PF_DLL_EXPORT   _export
  #else
    #define PF_DLL_EXPORT
  #endif

#endif

// ============================================================================================
// STANDARD HEADER FILE DETECTION MACROS
// ============================================================================================

// Standard C/C++ header files

#ifdef assert
  #define ASSERT_H              // no guard macro for this file -- using educated guess instead
#endif
#ifdef __CSTRING_H
  #define CSTRING_H
#endif
#ifdef __CTYPE_H
  #define CTYPE_H
#endif
#ifdef __ERRNO_H
  #define ERRNO_H
#endif
#ifdef __EXCEPT_H
  #define EXCEPT_H
#endif
#ifdef __FLOAT_H
  #define FLOAT_H
#endif
#ifdef __FSTREAM_H
  #define FSTREAM_H
#endif
#ifdef __IOMANIP_H
  #define IOMANIP_H
#endif
#ifdef __IOSTREAM_H
  #define IOSTREAM_H
#endif
#ifdef __LIMITS_H
  #define LIMITS_H
#endif
#ifdef __LOCALE_H
  #define LOCALE_H
#endif
#ifdef __MATH_H
  #define MATH_H
#endif
#ifdef __NEW_H
  #define NEW_H
#endif
#ifdef __SETJMP_H
  #define SETJMP_H
#endif
#ifdef __SIGNAL_H
  #define SIGNAL_H
#endif
#ifdef __STDARG_H
  #define STDARG_H
#endif
#ifdef __STDDEF_H
  #define STDDEF_H
#endif
#ifdef __STDIO_H
  #define STDIO_H
#endif
#ifdef __STDLIB_H
  #define STDLIB_H
#endif
#ifdef __STRING_H
  #define STRING_H
#endif
#ifdef __STRSTREAM_H
  #define STRSTREAM_H
#endif
#ifdef __TIME_H
  #define TIME_H
#endif
#ifdef __TYPEINFO_H
  #define TYPEINFO_H
#endif

// Non-standard header files.

#ifdef __ALLOC_H
  #define ALLOC_H
#endif
#ifdef __BCD_H
  #define BCD_H
#endif
#ifdef __BIOS_H
  #define BIOS_H
#endif
#ifdef __BWCC_H
  #define BWCC_H
#endif
#ifdef __CHECKS_H
  #define CHECKS_H
#endif
#ifdef __COMPLEX_H
  #define COMPLEX_H
#endif
#ifdef __CONIO_H
  #define CONIO_H
#endif
#ifdef __CONSTREA_H
  #define CONSTREAM_H
#endif
#if (((__TURBOC__ == 0x400) && defined(__DEFS_H)) || defined(___DEFS_H))
  #define _DEFS_H
#endif
#ifdef __DIR_H
  #define DIR_H
#endif
#ifdef __DIRECT_H
  #define DIRECT_H
#endif
#ifdef __DIRENT_H
  #define DIRENT_H
#endif
#ifdef __DOS_H
  #define DOS_H
#endif
#ifdef __EXCPT_H
  #define EXCPT_H
#endif
#ifdef __FCNTL_H
  #define FCNTL_H
#endif
#ifdef __GENERIC_H
  #define GENERIC_H
#endif
#ifdef __GRAPHICS_H
  #define GRAPHICS_H
#endif
#ifdef __IO_H
  #define IO_H
#endif
#ifdef __LOCKING_H
  #if ((__TURBOC__ == 0x400) && !defined(__OS2__))
    #define LOCKING_H
  #else
    #define SYS_LOCKING_H
  #endif
#endif
#ifdef __MALLOC_H
  #define MALLOC_H
#endif
#ifdef __MEM_H
  #define MEM_H
  #define MEMORY_H              // no guard macro for this file -- using educated guess instead
#endif
#ifdef ___NFILE_H
  #define _NFILE_H
#endif
#ifdef NULL
  #define _NULL_H              // no guard macro for this file -- using educated guess instead
#endif
#ifdef __OS2_H__
  #define OS2_H
#endif
#ifdef __PROCESS_H
  #define PROCESS_H
#endif
#ifdef REXXSAA_INCLUDED
  #define REXXSAA_H
#endif
#ifdef __SEARCH_H
  #define SEARCH_H
#endif
#ifdef __SHARE_H
  #define SHARE_H
#endif
#ifdef __STAT_H
  #define STAT_H
#endif
#ifdef __STDSTREAM_H
  #define STDIOSTREAM_H
#endif
#ifdef __STAT_H
  #define SYS_STAT_H
#endif
#ifdef __TIMEB_H
  #define SYS_TIMEB_H
#endif
#if (((__TURBOC__ == 0x400) && !defined(__OS2__) && defined(_TIME_T)) || defined(__TYPES_H))
  #define SYS_TYPES_H
#endif
#ifdef __UTIME_H
  #define UTIME_H
#endif
#ifdef __VALUES_H
  #define VALUES_H
#endif
#ifdef __VARARGS_H
  #define VARARGS_H
#endif
#if (((__TURBOC__ >= 0x520) && defined(_WINDOWS_)) || defined(__WINDOWS_H))
  #define WINDOWS_H
#endif

// ============================================================================================
// PRAGMA DIRECTIVE MACROS
// ============================================================================================

/*
Unfortunately, none of the preprocessors for the Borland compilers supported by this header
file perform macro replacement within pragma directives.  :-(

Perhaps Borland can supply preprocessors that will.  In case they can, all documentation and
all macro definitions can be found in "borland.txt".

To be continued... maybe...
*/

// ============================================================================================
// COMPILER DEFICIENCY CORRECTIONS
// ============================================================================================

#ifndef COMPILER_BORLAND_H

  #if (defined(__TCPLUSPLUS__) && (__TCPLUSPLUS__ < 0x520))
    #define PF_BOOL_NOT_BUILT_IN
  #endif

#endif

// ============================================================================================
// GUARD MACRO DEFINITION
// ============================================================================================

#ifndef COMPILER_BORLAND_H
  #define COMPILER_BORLAND_H
#endif