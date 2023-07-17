// ============================================================================================
//
// compiler/gnu.h
//
// ============================================================================================

#ifndef PLATFORM_H
  #error platform.h has not been included yet.
#endif

// ============================================================================================
// PLATFORM PROPERTY MACROS
// ============================================================================================

/*
The following was taken from the GNU C online help pages:

  __STDC_VERSION__       This macro expands to the C Standard's version number, a long integer
                         constant of the form `yyyymmL' where yyyy and mm are the year and
                         month of the Standard version. This signifies which version of the C
                         Standard the preprocessor conforms to. Like `__STDC__', whether this
                         version number is accurate for the entire implementation depends on
                         what C compiler will operate on the output from the preprocessor. This
                         macro is not defined if the `-traditional' option is used.

  __GNUC__               This macro is defined if and only if this is GNU C. This macro is
                         defined only when the entire GNU C compiler is in use; if you invoke
                         the preprocessor directly, `__GNUC__' is undefined. The value
                         identifies the major version number of GNU CC (`1' for GNU CC version
                         1, which is now obsolete, and `2' for version 2).

  __GNUC_MINOR__         The macro contains the minor version number of the compiler. This can
                         be used to work around differences between different releases of the
                         compiler (for example, if gcc 2.6.3 is known to support a feature, you
                         can test for __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 6)).
                         The last number, `3' in the example above, denotes the bugfix level of
                         the compiler; no macro contains this value.

  __GNUG__               The GNU C compiler defines this when the compilation language is C++;
                         use `__GNUG__' to distinguish between GNU C and GNU C++.

  __STRICT_ANSI__        GNU C defines this macro if and only if the `-ansi' switch was
                         specified when GNU C was invoked. Its definition is the null string.
                         This macro exists primarily to direct certain GNU header files not to
                         define certain traditional Unix constructs which are incompatible with
                         ANSI C.

  __BASE_FILE__          This macro expands to the name of the main input file, in the form of
                         a C string constant. This is the source file that was specified as an
                         argument when the C compiler was invoked.

  __INCLUDE_LEVEL__      This macro expands to a decimal integer constant that represents the
                         depth of nesting in include files. The value of this macro is
                         incremented on every `#include' directive and decremented at every end
                         of file. For input files specified by command line arguments, the
                         nesting level is zero.

  __VERSION__            This macro expands to a string constant which describes the version
                         number of GNU C. The string is normally a sequence of decimal numbers
                         separated by periods, such as `"2.6.0"'.

  __OPTIMIZE__           GNU CC defines this macro in optimizing compilations. It causes
                         certain GNU header files to define alternative macro definitions for
                         some system library functions. You should not refer to or test the
                         definition of this macro unless you make very sure that programs will
                         execute with the same effect regardless.

  __CHAR_UNSIGNED__      GNU C defines this macro if and only if the data type char is unsigned
                         on the target machine. It exists to cause the standard header file
                         `limits.h' to work correctly. You should not refer to this macro
                         yourself; instead, refer to the standard macros defined in `limits.h'.
                         The preprocessor uses this macro to determine whether or not to
                         sign-extend large character constants written in octal; see section
                         The`#if' Directive.

  __REGISTER_PREFIX__    This macro expands to a string (not a string constant) describing the
                         prefix applied to CPU registers in assembler code. You can use it to
                         write assembler code that is usable in multiple environments. For
                         example, in the `m68k-aout' environment it expands to the null string,
                         but in the `m68k-coff' environment it expands to the string `%'.

  __USER_LABEL_PREFIX__  Similar to __REGISTER_PREFIX__, but describes the prefix applied to
                         user generated labels in assembler code. For example, in the
                         `m68k-aout' environment it expands to the string `_', but in the
                         `m68k-coff' environment it expands to the null string. This does
                         not work with the `-mno-underscores' option that the i386 OSF/rose and
                         m88k targets provide nor with the `-mcall*' options of the rs6000
                         System V Release 4 target.

  __unix__               `__unix__' is normally predefined on all Unix systems.

  __BSD__                `__BSD__' is predefined on recent versions of Berkeley Unix (perhaps
			 only in version 4.3).

  __vax__                `__vax__' is predefined on Vax computers.

  __mc68000__            `__mc68000__' is predefined on most computers whose CPU is a Motorola
			 68000, 68010 or 68020.

  __m68k__               `__m68k__' is also predefined on most computers whose CPU is a 68000,
			 68010 or 68020; however, some makers use `__mc68000__' and some use
			 `__m68k__'. Some predefine both names. What happens in GNU C depends
			 on the system you are using it on.

  __M68020__             `__M68020__' has been observed to be predefined on some systems that
			 use 68020 CPUs--in addition to `__mc68000__' and `__m68k__', which are
			 less specific.

  _AM29K                 Both `_AM29K' and `_AM29000' are predefined for the AMD 29000 CPU
  _AM29000               family.

  __ns32000__            `__ns32000__' is predefined on computers which use the National
			 Semiconductor 32000 series CPU.

  __sun__                `__sun__' is predefined on all models of Sun computers.

  __pyr__                `__pyr__' is predefined on all models of Pyramid computers.

  __sequent__            `__sequent__' is predefined on all models of Sequent computers.

*/

#ifndef COMPILER_GNU_H

  #define PF_COMPILER     PF_GNU
  #define PF_COMPILER_VER __GNUC__##.##__GNUC_MINOR__

  #if defined(__unix__)
    #define PF_OS PF_UNIX
  #elif defined(__vax__)
    #define PF_OS PF_VMS
  #else
    #define PF_OS PF_UNKNOWN_OS
  #endif

  #if defined(_AM29K) || defined(_AM29000)
    #define PF_CPU PF_AMD_29000
  #elif defined(__mc68000__) || defined(__m68k__) || defined(__M68020__)
    #define PF_CPU PF_MOTOROLA_68X00
  #elif defined(__ns32000__)
    #define PF_CPU PF_NS_32000
  #elif defined(__vax__)
    #define PF_CPU PF_VAX
  #else
    #define PF_CPU PF_UNKNOWN_CPU
  #endif

  #define PF_STD_LIB_CALL
  #define PF_MULTI_THREADED 0
  #define PF_DLL_IMPORT
  #define PF_DLL_EXPORT
  #define PF_DLL_CALL

#endif

// ============================================================================================
// GUARD MACRO DEFINITION
// ============================================================================================

#ifndef COMPILER_GNU_H
  #define COMPILER_GNU_H
#endif

