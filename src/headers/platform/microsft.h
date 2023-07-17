// ============================================================================================
//
// compiler/microsft.h
//
// ============================================================================================

#ifndef PLATFORM_H
  #error platform.h has not been included yet.
#endif

// ============================================================================================
// PLATFORM PROPERTY MACROS
// ============================================================================================

/*
The following was taken from the help files of Microsoft Visual C++ 6.0:

  _CHAR_UNSIGNED   Default char type is unsigned. Defined when /J is specified.

  _CPPRTTI	   Defined for code compiled with /GR (Enable Run-Time Type Information).

  _CPPUNWIND       Defined for code compiled with /GX (Enable Exception Handling).

  _DLL	           Defined when /MD or /MDd (Multithread DLL) is specified.

  _M_ALPHA         Defined for DEC ALPHA platforms. It is defined as 1 by the ALPHA compiler,
                   and it is not defined if another compiler is used.

  _M_IX86          Defined for x86 processors. See Table 1.3 for more details.

  _M_MPPC          Defined for Power Macintosh platforms. Default is 601 (/QP601). See Table
                   1.4 for more details.

  _M_MRX000        Defined for MIPS platforms. Default is 4000 (/QMR4000). See Table 1.5 for
                   more details.

  _M_PPC           Defined for PowerPC platforms. Default is 604 (/QP604). See Table 1.6 for
                   more details.

  _MFC_VER         Defines the MFC version. Defined as 0x0421 for Microsoft Foundation Class
                   Library 4.21. Always defined.

  _MSC_EXTENSIONS  This macro is defined when compiling with the /Ze compiler option (the
                   default). Its value, when defined, is 1.

  _MSC_VER         Defines the compiler version. Defined as 1200 for Microsoft Visual C++ 6.0.
		   Always defined.

  _MT              Defined when /MD or /MDd (Multithreaded DLL) or /MT or /MTd (Multithreaded)
                   is specified.

  _WIN32           Defined for applications for Win32©. Always defined.

  As shown in following tables, the compiler generates a value for the preprocessor identifiers
  that reflect the processor option specified.

  Table 1.3 -- Values for _M_IX86

  Option in         Command-Line  Resulting Value
  Developer Studio  Option

  Blend             /GB           _M_IX86 = 500 (Default. Future compilers
                                    will emit a different value to reflect
                                    the dominant processor.)
  Pentium           /G5           _M_IX86 = 500
  Pentium Pro       /G6           _M_IX86 = 600
  80386             /G3           _M_IX86 = 300
  80486             /G4           _M_IX86 = 400

  Table 1.4 Values for _M_MPPC

  Option in development  Command-Line  Resulting Value
  environment            Option

  PowerPC 601            /QP601        _M_MPPC = 601 (Default)
  PowerPC 603            /QP603        _M_MPPC = 603
  PowerPC 604            /QP604        _M_MPPC = 604
  PowerPC 620            /QP620        _M_MPPC = 620

*/

#ifndef COMPILER_MICRSOFT_H

  #define PF_COMPILER     PF_MICROSOFT
  #define PF_COMPILER_VER _MSC_VER

  #if defined(_M_MPPC)
    #define PF_OS PF_MACOS
  #elif defined(_WIN32)
    #define PF_OS PF_WIN32
  #else
    #define PF_OS PF_UNKNOWN_OS
  #endif

  #if defined(_M_ALPHA)
    #define PF_CPU PF_DEC_ALPHA
  #elif defined(_M_MPPC) || defined(_M_PPC)
    #define PF_CPU PF_IBM_POWERPC
  #elif defined(_M_IX86)
    #define PF_CPU PF_INTEL_80X86
  #elif defined(_M_MRX000)
    #define PF_CPU PF_MIPS
  #else
    #define PF_CPU PF_UNKNOWN_CPU
  #endif

  #define PF_STD_LIB_CALL   _cdecl
  #define PF_MULTI_THREADED defined(_MT)
  #define PF_DLL_IMPORT     _import
  #define PF_DLL_EXPORT     _export

#endif

// ============================================================================================
// PRAGMA DIRECTIVE MACROS
// ============================================================================================

/*
The following was taken from the help files of Microsoft Visual C++ 6.0:

  alloc_text           #pragma alloc_text("textsection", function1, ...)

                       Names the code section where the specified function definitions are to
                       reside.  The pragma must occur between a function declarator and the
                       function definition for the named functions.

                       The alloc_text pragma does not handle C++ member functions or overloaded
                       functions.  It is applicable only to functions declared with C
                       linkage -- that is, functions declared with the extern "C" linkage
                       specification.  If you attempt to use this pragma on a function with C++
                       linkage, a compiler error is generated.

                       Since function addressing using __based is not supported, specifying
                       section locations requires the use of the alloc_text pragma.  The name
                       specified by textsection should be enclosed in double quotation marks.

                       The alloc_text pragma must appear after the declarations of any of the
                       specified functions and before the definitions of these functions.

                       Functions referenced in an alloc_text pragma should be defined in the
                       same module as the pragma.  If this is not done and an undefined
                       function is later compiled into a different text section, the error may
                       or may not be caught.  Although the program will usually run correctly,
                       the function will not be allocated in the intended sections.

                       Other limitations on alloc_text are as follows:

                       * It cannot be used inside a function.

                       * It must be used after the function has been declared, but before the
                         function has been defined.

  auto_inline          #pragma auto_inline([on|off])

                       Excludes any functions defined within the range where off is specified
                       from being considered as candidates for automatic inline expansion.  To
                       use the auto_inline pragma, place it before and immediately after (not
                       in) a function definition.  The pragma takes effect at the first
                       function definition after the pragma is seen.  Pragma auto_inline does
                       not apply to explicit inline functions.

  bss_seg              #pragma bss_seg(["section-name"[, "section-class"]])

		       Specifies the default section for unitialized data.  The data_seg pragma
                       has the same effect but works with initialized or unitialized data.  In
                       some cases, you can use bss_seg to speed up your load time by putting
                       all unitialized data in one section.

                         #pragma bss_seg("MY_DATA")

                       causes uninitialized data allocated following the #pragma statement to
                       be placed in a section called MY_DATA.

                       Data allocated using the bss_seg pragma does not retain any information
                       about its location.

                       The second parameter, section-class, is included for compatibilty with
                       versions of Visual C++ prior to version 2.0, and is now ignored.

  check_stack          #pragma check_stack([on|off])
                       #pragma check_stack [+|-]

                       Instructs the compiler to turn off stack probes if off (or -) is
                       specified, or to turn on stack probes if on (or +) is specified.  If no
                       argument is given, stack probes are treated according to the default.
                       This pragma takes effect at the first function defined after the pragma
                       is seen.  Stack probes are not a part of macros nor of functions that
                       are generated inline.

                       If you don't give an argument for the check_stack pragma, stack checking
		       reverts to the behavior specified on the command line.  For more
                       information, see Compiler Reference.  The interaction of the #pragma
                       check_stack and the /Gs option is summarized here:

                       Syntax                    /Gs option?  Action
                       -----------------------------------------------------
                       #pragma check_stack()     Yes          Turns off stack
                       #pragma check_stack                    checking

                       #pragma check_stack()     No           Turns on stack
                       #pragma check_stack                    checking

                       #pragma check_stack(on)   Yes or no    Turns on stack
                       #pragma check_stack +                  checking

                       #pragma check_stack(off)  Yes or no    Turns off stack
                       #pragma check_stack -                  checking

  code_seg             #pragma code_seg(["section-name"[,"section-class"]])

                       Specifies a code section where functions are to be allocated.  The
                       code_seg pragma specifies the default section for functions.  You can,
                       optionally, specify the class as well as the section name.  Using
                       #pragma code_seg without a section-name string resets allocation to
                       whatever it was when compilation began.

  const_seg            #pragma const_seg(["section-name"[,"section-class"]])

                       Specifies the default section for constant data.  The data_seg pragma
                       has the same effect but works with all data.  You can use this pragma to
                       put all your constant data in one read-only section.

                         #pragma const_seg("MY_DATA")

                       causes constant data allocated following the #pragma statement to be
                       placed in a section called MY_DATA.

                       Data allocated using the const_seg pragma does not retain any
                       information about its location.

                       The second parameter, section-class, is included for compatibilty with
                       versions of Visual C++ prior to version 2.0, and is now ignored.

  comment              #pragma comment(comment-type[, commentstring])

                       Places a comment record into an object file or executable file.  The
		       comment-type is one of five predefined identifiers, described below,
                       that specify the type of comment record.  The optional commentstring is
                       a string literal that provides additional information for some comment
                       types.  Because commentstring is a string literal, it obeys all the
                       rules for string literals with respect to escape characters, embedded
                       quotation marks ("), and concatenation.

                       compiler  Places the name and version number of the compiler in the
                                 object file.  This comment record is ignored by the linker.
                                 If you supply a commentstring parameter for this record type,
                                 the compiler generates a warning.

                       exestr    Places commentstring in the object file.  At link time, this
                                 string is placed in the executable file.  The string is not
                                 loaded into memory when the executable file is loaded;
                                 however, it can be found with a program that finds printable
                                 strings in files.  One use for this comment-record type is to
                                 embed a version number or similar information in an executable
                                 file.

                       lib       Places a library-search record in the object file.  This
                                 comment type must be accompanied by a commentstring parameter
                                 containing the name (and possibly the path) of the library
                                 that you want the linker to search.  Since the library name
                                 precedes the default library-search records in the object
                                 file, the linker searches for this library just as if you had
                                 named it on the command line.  You can place multiple
                                 library-search records in the same source file; each record
                                 appears in the object file in the same order in which it is
                                 encountered in the source file.

                       linker    Places a linker option in the object file.  You can use this
                                 comment-type to specify a linker option instead placing the
                                 option on the Link tab of the Project Settings dialog box.
                                 For example, you can specity the /include option to force the
                                 inclusion of a symbol:

                                   #pragma comment(linker, "/include:__mySymbol")

                       user      Places a general comment in the object file.  The
                                 commentstring parameter contains the text of the comment.
                                 This comment record is ignored by the linker.

                       The following pragma causes the linker to search for the EMAPI.LIB
                       library while linking.  The linker searches first in the current working
                       directory and then in the path specified in the LIB environment
		       variable.

                         #pragma comment(lib, "emapi")

                       The following pragma causes the compiler to place the name and version
                       number of the compiler in the object file:

                         #pragma comment(compiler)

                       Note:  For comments that take a commentstring parameter, you can use a
                       macro in any place where you would use a string literal, provided that
                       the macro expands to a string literal.  You can also concatenate any
                       combination of string literals and macros that expand to string
                       literals.  For example, the following statement is acceptable:

                         #pragma comment(user, "Compiled on " __DATE__ " at " __TIME__)

  component            #pragma component(browser, <on|off>[, references[, name]])
                       #pragma component(minrebuild, <on|off>)

                       Controls the collecting of browse information or dependency information
                       from within source files.

                       Browser

                         You can turn collecting on or off, and you can specify particular
                         names to be ignored as information is collected.

                         Using on or off controls the collection of browse information from the
                         pragma forward.  For example:

                           #pragma component(browser, off)

                         stops the compiler from collecting browse information.

                         Note:  To turn on the collecting of browse information with this
                         pragma, browse information must first be enabled from the Project
                         Settings dialog box or the command line.

                         The references option can be used with or without the name argument.
                         Using references without name turns on or off the collecting of
                         references (other browse information continues to be collected,
                         however).  For example:

                           #pragma component(browser, off, references)

			 stops the compiler from collecting reference information.

                         Using references with name and off prevents references to name from
                         appearing in the browse information window.  Use this syntax to ignore
                         names and types you are not interested in and to reduce the size of
                         browse information files.  For example:

                           #pragma component(browser, off, references, DWORD)

                         ignores references to DWORD from that point forward.  You can turn
                         collecting of references to DWORD back on by using on:

                           #pragma component(browser, on, references, DWORD)

                         This is the only way to resume collecting references to name; you must
                         explicitly turn on any name that you have turned off.

                         To prevent the preprocessor from expanding name (such as expanding
                         NULL to 0), put quotes around it:

                           #pragma component(browser, off, references, "NULL")

                       Minimal Rebuild

                         The Visual C++ minimal rebuild feature requires that the compiler
                         create and store C++ class dependency information, which takes disk
                         space.  To save disk space, you can use #pragma component(minrebuild,
                         off) whenever you don't need to collect dependency information, for
                         instance, in unchanging header files.  Insert #pragma
                         component(minrebuild, on) after unchanging classes to turn dependency
                         collection back on.

                         For more information, see the Enable Minimal Rebuild (/Gm) compiler
                         option.

  data_seg             #pragma data_seg(["section-name"[, "section-class"]])

                       Specifies the default section for data.  For example:

                         #pragma data_seg( "MY_DATA" )

                       causes data allocated following the #pragma statement to be placed in a
                       section called MY_DATA.

                       Data allocated using the data_seg pragma does not retain any information
                       about its location.

                       The second parameter, section-class, is included for compatibilty with
                       versions of Visual C++ prior to version 2.0, and is now ignored.

  function             #pragma function(function1[, ...])

                       Specifies that calls to functions specified in the pragma's argument
                       list be generated.  If you use the intrinsic pragma (or /Oi) to tell the
                       compiler to generate intrinsic functions (intrinsic functions are
                       generated as inline code, not as function calls), you can use the
                       function pragma to explicitly force a function call.  Once a function
                       pragma is seen, it takes effect at the first function definition
                       containing a specified intrinsic function.  The effect continues to the
                       end of the source file or to the appearance of an intrinsic pragma
                       specifying the same intrinsic function.  The function pragma can be used
                       only outside of a function -- at the global level.

                       For lists of the functions that have intrinsic forms, see #pragma
                       intrinsic.

  hdrstop              #pragma hdrstop[("filename")]

                       Controls the way precompiled headers work.  The filename is the name of
                       the precompiled header file to use or create (depending on whether /Yu
                       or /Yc is specified).  If filename does not contain a path
                       specification, the precompiled header file is assumed to be in the same
                       directory as the source file.  Any filename is ignored when /YX, the
                       automatic precompiled header option, is specified.

                       If a C or C++ file contains a hdrstop pragma when compiled with either
                       /YX or /Yc, the compiler saves the state of the compilation up to the
                       location of the pragma.  The compiled state of any code that follows the
                       pragma is not saved.

                       The hdrstop pragma cannot occur inside a header file.  It must occur in
                       the source file at the file level; that is, it cannot occur within any
                       data or function declaration or definition.

                       Note:  The hdrstop pragma is ignored unless either the /YX option is
                       specified or the /Yu or /Yc option is specified without a filename.

                       Use filename to name the precompiled header file in which the compiled
                       state is saved.  A space between hdrstop and filename is optional.  The
                       filename specified in the hdrstop pragma is a string and is therefore
                       subject to the constraints of any C or C++ string.  In particular, you
                       must enclose it in quotation marks as shown in the following example:

                         #pragma hdrstop("c:\projects\include\myinc.pch")

                       The name of the precompiled header file is determined according to the
                       following rules, in order of precedence:

                       * The argument to the /Fp compiler option

                       * The filename argument to #pragma hdrstop

                       * The base name of the source file with a .PCH
                         extension

  include_alias        #pragma include_alias("long_filename", "short_filename")
                       #pragma include_alias(<long_filename>, <short_filename>)

                       Specifies that short_filename is to be used as an alias for
                       long_filename.  Some file systems allow longer header filenames than the
                       8.3 FAT file system limit.  The compiler cannot simply truncate the
		       longer names to 8.3, because the first eight characters of the longer
                       header filenames may not be unique.

                       Whenever the compiler encounters the long_filename string, it
                       substitutes short_filename, and looks for the header file
                       short_filename instead.  This pragma must appear before the
                       corresponding #include directives.  For example:

                         // First eight characters of these two files not unique.
                         #pragma include_alias("AppleSystemHeaderQuickdraw.h", "quickdra.h")
                         #pragma include_alias("AppleSystemHeaderFruit.h", "fruit.h")

                         #pragma include_alias("GraphicsMenu.h", "gramenu.h")

                         #include "AppleSystemHeaderQuickdraw.h"
                         #include "AppleSystemHeaderFruit.h"
                         #include "GraphicsMenu.h"

                       The alias being searched for must match the specification exactly, in
                       case as well as in spelling and in use of double quotation marks or
                       angle brackets.  The include_alias pragma performs simple string
                       matching on the filenames; no other filename validation is performed.
                       For example, given the following directives,

                         #pragma include_alias("mymath.h", "math.h")
                         #include "./mymath.h"
                         #include "sys/mymath.h"

                       no aliasing (substitution) is performed, since the header file strings
                       do not match exactly.  Also, header filenames used as arguments to the
                       /Yu, /Yc, and /YX compiler options, or the hdrstop pragma, are not
                       substituted.  For example, if your source file contains the following
                       directive,

                         #include <AppleSystemHeaderStop.h>

                       the corresponding compiler option should be

                         /YcAppleSystemHeaderStop.h

                       You can use the include_alias pragma to map any header filename to
                       another.  For example:

                         #pragma include_alias("api.h", "c:\version1.0\api.h")
                         #pragma include_alias(<stdio.h>, <newstdio.h>)
                         #include "api.h"
			 #include <stdio.h>

                       Do not mix filenames enclosed in double quotation marks with filenames
                       enclosed in angle brackets.  For example, given the above two #pragma
                       include_alias directives, the compiler performs no substitution on the
                       following #include directives:

                         #include <api.h>
                         #include "stdio.h"

                       Furthermore, the following directive generates an error:

                         // Error
                         #pragma include_alias(<header.h>, "header.h")

                       Note that the filename reported in error messages, or as the value of
                       the predefined __FILE__ macro, is the name of the file after the
                       substitution has been performed.  For example, after the following
                       directives,

                         #pragma include_alias("VeryLongFileName.H", "myfile.h")
                         #include "VeryLongFileName.H"

                       an error in VERYLONGFILENAME.H produces the following error message:

                       myfile.h(15) : error C2059 : syntax error

		       Also note that transitivity is not supported. Given the following
                       directives,

                         #pragma include_alias("one.h", "two.h")
                         #pragma include_alias("two.h", "three.h")
                         #include "one.h"

                       the compiler searches for the file TWO.H rather than THREE.H.

  init_seg             #pragma init_seg(compiler|lib|user|"section-name"[,"func-name"])

                       C++ Specific:

                         Specifies a keyword or code section that affects the order in which
                         startup code is executed.  Because initialization of global static
                         objects can involve executing code, you must specify a keyword that
                         defines when the objects are to be constructed.  It is particularly
                         important to use the init_seg pragma in dynamic-link libraries (DLLs)
                         or libraries requiring initialization.

                         The options to the init_seg pragma are:

                         compiler      Reserved for Microsoft C run-time library
                                       initialization.  Objects in this group are constructed
                                       first.

                         lib           Available for third-party class-library vendors'
                                       initializations.  Objects in this group are constructed
                                       after those marked as compiler but before any others.

                         user          Available to any user.  Objects in this group are
                                       constructed last.

                         section-name  Allows explicit specification of the initialization
                                       section.  Objects in a user-specified section-name are
                                       not implicitly constructed; however, their addresses are
                                       placed in the section named by section-name.

                         func-name     Specifies a function to be called in place of atexit
                                       when the program exits.  The function specified must
                                       have the same signature as the atexit function:

                                         int funcname(void (__cdecl*)(void));

                         If you need to defer initialization (for example, in a DLL), you may
                         choose to specify the section name explicitly.  You must then call the
			 constructors for each static object.

                       END C++ Specific

  inline_depth         #pragma inline_depth([0..255])

                       Controls the number of times inline expansion can occur by controlling
                       the number of times that a series of function calls can be expanded
                       (from 0 to 255 times).  This pragma controls the inlining of functions
                       marked inline and __inline or inlined automatically under the /Ob2
                       option.

                       The inline_depth pragma controls the number of times a series of
                       function calls can be expanded.  For example, if the inline depth is
                       four, and if A calls B and B then calls C,  all three calls will be
                       expanded inline.  However, if the closest inline expansion is two, only
                       A and B are expanded, and C remains as a function call.

                       To use this pragma, you must set the /Ob compiler option to 1 or 2.  The
		       depth set using this pragma takes effect at the first function call
                       after the pragma.  If you do not specify a value within the parentheses,
                       inline_depth sets the inline depth back to its default value of 8.

                       The inline depth can be decreased during expansion but not increased.
                       If the inline depth is six and during expansion the preprocessor
                       encounters an inline_depth pragma with a value of eight, the depth
                       remains six.

                       An inline depth of 0 inhibits inline expansion; an inline depth of 255
                       places no limit on inline expansion.  If either pragma is used without
                       specifying a value, the default value is used.

  inline_recursion     #pragma inline_recursion([on|off])

                       Controls the inline expansion of direct or mutually recursive function
                       calls.  Use this pragma to control functions marked as inline and
                       __inline or functions that the compiler automatically expands under the
                       /Ob2 option.  Use of this pragma requires an /Ob compiler option setting
                       of either 1 or 2.  The default state for inline_recursion is off. This
                       pragma takes effect at the first function call after the pragma is seen
                       and does not affect the definition of the function.

                       The inline_recursion pragma controls how recursive functions are
                       expanded.  If inline_recursion is off, and if an inline function calls
                       itself (either directly or indirectly), the function is expanded only
                       once.  If inline_recursion is on, the function is expanded multiple
		       times until the value of inline_depth is reached or capacity limits are
                       reached.

  intrinsic            #pragma intrinsic(function1[, ...])

                       Specifies that calls to functions specified in the pragma's argument
                       list are intrinsic.  The compiler generates intrinsic functions as
                       inline code, not as function calls.  The library functions with
                       intrinsic forms are listed below.  Once an intrinsic pragma is seen, it
                       takes effect at the first function definition containing a specified
                       intrinsic function.  The effect continues to the end of the source file
                       or to the appearance of a function pragma specifying the same intrinsic
                       function.  The intrinsic pragma can be used only outside of a function
                       definition -- at the global level.

                       The following functions have intrinsic forms:

                         _disable _enable _inp _inpw _lrotl _lrotr _outp _outpw _rotl _rotr
                         _strset abs fabs labs memcmp memcpy memset strcat strcmp strcpy strlen

                       Programs that use intrinsic functions are faster because they do not
                       have the overhead of function calls but may be larger due to the
                       additional code generated.

                       Note:  The _alloca and setjmp functions are always generated inline;
                       this behavior is not affected by the intrinsic pragma.

                       The floating-point functions listed below do not have true intrinsic
                       forms.  Instead they have versions that pass arguments directly to the
                       floating-point chip rather than pushing them onto the program stack:

                         acos asin cosh fmod pow sinh tanh

                       The floating-point functions listed below have true intrinsic forms when
                       you specify both the /Oi and /Og compiler options (or any option that
                       includes /Og: /Ox, /O1, and /O2):

                         atan exp log10 sqrt atan2 log sin tan cos

                       You can use the /Op or /Za compiler option to override generation of
                       true intrinsic floating-point options.  In this case, the functions are
                       generated as library routines that pass arguments directly to the
                       floating-point chip instead of pushing them onto the program stack.

  message              #pragma message(messagestring)

		       Sends a string literal to the standard output without terminating the
                       compilation.  A typical use of the message pragma is to display
                       informational messages at compile time.

                       The following code fragment uses the message pragma to display a message
                       during compilation:

                         #if _M_IX86 == 500
                         #pragma message("Pentium processor build")
                         #endif

                       The messagestring parameter can be a macro that expands to a string
                       literal, and you can concatenate such macros with string literals in any
                       combination.  For example, the following statements display the name of
                       the file being compiled and the date and time when the file was last
                       modified:

                         #pragma message("Compiling " __FILE__)
                         #pragma message("Last modified on " __TIMESTAMP__)

  once                 #pragma once

                       Specifies that the file, in which the pragma resides, will be included
                       (opened) only once by the compiler in a build.  A common use for this
                       pragma is the following:

                         //header.h
                         #pragma once
                         // Your C or C++ code would follow:

  optimize             #pragma optimize("optimization-list", on|off)

                       Code optimization is supported only in Visual C++ Professional and
                       Enterprise Editions.  For more information, see Visual C++ Editions.

                       Specifies optimizations to be performed on a function-by-function basis.
                       The optimize pragma must appear outside a function and takes effect at
                       the first function defined after the pragma is seen.  The on and off
                       arguments turn options specified in the optimization-list on or off.

                       The optimization-list can be zero or more of the parameters shown here:

                       Parameter(s)  Type of optimization
                       ----------------------------------
                       a             Assume no aliasing

		       g             Enable global optimizations

                       p             Improve floating-point consistency

                       s or t        Specify short or fast sequences of machine code

                       w             Assume no aliasing across function calls

                       y             Generate frame pointers on the program stack.

                       These are the same letters used with the /O compiler options.  For
                       example,

                         #pragma optimize("atp", on)

                       Using the optimize pragma with the empty string ("") is a special form
                       of the directive.  It either turns off all optimizations or restores
                       them to their original (or default) settings.

			 #pragma optimize("", off)
                         .
                         .
                         .
                         #pragma optimize("", on)

  pack                 #pragma pack([n])

                       Specifies packing alignment for structure and union members.  Whereas
                       the packing alignment of structures and unions is set for an entire
                       translation unit by the /Zp option, the packing alignment is set at the
                       data-declaration level by the pack pragma.  The pragma takes effect at
                       the first structure or union declaration after the pragma is seen; the
                       pragma has no effect on definitions.

                       When you use #pragma pack(n), where n is 1, 2, 4, 8, or 16, each
                       structure member after the first is stored on the smaller member type or
                       n-byte boundaries.  If you use #pragma pack without an argument,
                       structure members are packed to the value specified by /Zp.  The default
                       /Zp packing size is /Zp8.

                       The compiler also supports the following enhanced syntax:

                         #pragma pack([[push|pop,][ identifier,]][ n])

                       This syntax allows you to combine program components into a single
                       translation unit if the different components use pack pragmas to specify
		       different packing alignments.

                       Each occurrence of a pack pragma with a push argument stores the current
                       packing alignment on an internal compiler stack.  The pragma's argument
                       list is read from left to right.  If you use push, the current packing
                       value is stored.  If you provide a value for n, that value becomes the
                       new packing value.  If you specify an identifier, a name of your
                       choosing, the identifier is associated with the new packing value.

                       Each occurrence of a pack pragma with a pop argument retrieves the value
                       at the top of an internal compiler stack and makes that value the new
                       packing alignment.  If you use pop and the internal compiler stack is
                       empty, the alignment value is that set from the command-line and a
                       warning is issued.  If you use pop and specify a value for n, that value
                       becomes the new packing value.  If you use pop and specify an
                       identifier, all values stored on the stack are removed from the stack
                       until a matching identifier is found.  The packing value associated with
                       the identifier is also removed from the stack and the packing value that
                       existed just before the identifier was pushed becomes the new packing
		       value.  If no matching identifier is found, the packing value set from
                       the command line is used and a level-one warning is issued.  The default
                       packing alignment is 8.

                       The new, enhanced functionality of the pack pragma allows you to write
                       header files that ensure that packing values are the same before and
                       after the header file is encountered:

                         // File name: include1.h
                         //
                         #pragma pack(push, enter_include1)
                         // Your include-file code ...
                         #pragma pack(pop, enter_include1)
                         // End of include1.h

                       In the previous example, the current pack value is associated with the
                       identifier enter_include1 and pushed, remembered, on entry to the header
                       file.  The pack pragma at the end of the header file removes all
                       intervening pack values that may have occurred in the header file and
                       removes the pack value associated with enter_include1.  The header file
                       thus ensures that the pack value is the same before and after the header
                       file.

                       The new functionality also allows you to use code, such as header files,
                       that uses pack pragmas to set packing alignments that differ from the
                       packing value set in your code:

			 #pragma pack( push, before_include1 )
                         #include "include1.h"
                         #pragma pack( pop, before_include1 )

                       In the previous example, your code is protected from any changes to the
                       packing value that might occur in include.h.

  pointers_to_members  #pragma pointers_to_members(pointer-declaration[,
                         most-general-representation])

                       C++ Specific:

                         Specifies whether a pointer to a class member can be declared before
                         its associated class definition and is used to control the pointer
                         size and the code required to interpret the pointer.  You can place a
                         pointers_to_members pragma in your source file as an alternative to
                         using the /vmx compiler options.

                         The pointer-declaration argument specifies whether you have declared a
			 pointer to a member before or after the associated function
                         definition.  The pointer-declaration argument is one of the following
                         two symbols:

                         Argument         Comments
                         full_generality  Generates safe, sometimes nonoptimal code.  You use
                                          full_generality if any pointer to a member is
                                          declared before the associated class definition.
                                          This argument always uses the pointer representation
                                          specified by the most-general-representation
                                          argument.  Equivalent to /vmg.

                          best_case	  Generates safe, optimal code using best-case
                                          representation for all pointers to members.  Requires
                                          defining the class before declaring a pointer to a
                                          member of the class.  The default is best_case.

                         The most-general-representation argument specifies the smallest
                         pointer representation that the compiler can safely use to reference
                         any pointer to a member of a class in a translation unit.  The
                         argument can be one of the following:

                         Argument              Comments
                         single_inheritance    The most general representation is single-
                                               inheritance, pointer to a member function.
                                               Causes an error if the inheritance model of a
                                               class definition for which a pointer to a member
					       is declared is ever either multiple or virtual.

                         multiple_inheritance  The most general representation is multiple-
                                               inheritance, pointer to a member function.
                                               Causes an error if the inheritance model of a
                                               class definition for which a pointer to a member
                                               is declared is virtual.

                         virtual_inheritance   The most general representation is virtual-
                                               inheritance, pointer to a member function.
                                               Never causes an error.  This is the default
                                               argument when #pragma
                                               pointers_to_members(full_generality) is used.

                       END C++ Specific

  setlocale            #pragma setlocale("locale-string")

                       Defines the locale (country and language) to be used when translating
		       wide-character constants and string literals.  Since the algorithm for
                       converting multibyte characters to wide characters may vary by locale or
                       the compilation may take place in a different locale from where an
                       executable file will be run, this pragma provides a way to specify the
                       target locale at compile time.  This guarantees that the wide-character
                       strings will be stored in the correct format.  The default locale-string
                       is "C". The "C" locale maps each character in the string to its value as
                       a wchar_t (unsigned short).

  vtordisp             #pragma vtordisp(on|off)

                       C++ Specific:

                         Enables the addition of the hidden vtordisp construction/destruction
                         displacement member.  The vtordisp pragma is applicable only to code
                         that uses virtual bases.  If a derived class overrides a virtual
                         function that it inherits from a virtual base class, and if a
                         constructor or destructor for the derived class calls that function
                         using a pointer to the virtual base class, the compiler may introduce
                         additional hidden "vtordisp" fields into classes with virtual bases.

                         The vtordisp pragma affects the layout of classes that follow it. The
                         /vd0 and /vd1 options specify the same behavior for complete modules.
                         Specifying off suppresses the hidden vtordisp members.  Specifying on,
                         the default, enables them where they are necessary.  Turn off vtordisp
                         only if there is no possibility that the class's constructors and
                         destructors call virtual functions on the object pointed to by the
			 this pointer.

                           #pragma vtordisp(off)
                           class GetReal : virtual public { ... };
                           #pragma vtordisp(on)

                       END C++ Specific

  warning              #pragma warning(warning-specifier:  warning-number-list[, ...])
                       #pragma warning(push[, n])
                       #pragma warning(pop)

                       Allows selective modification of the behavior of compiler warning
                       messages.  The warning-specifier can be one of the following.

                       Warning-specifier  Meaning
                       once               Display the specified message(s) only once.

                       default            Apply the default compiler behavior to the specified
					  message(s).

                       1, 2, 3, 4         Apply the given warning level to the specified
                                          warning message(s).

                       disable            Do not issue the specified warning message(s).

                       error              Report the specified warnings as errors.

                       The warning-number-list can contain any warning numbers.  Multiple
                       options can be specified in the same pragma directive as follows:

                         #pragma warning( disable : 4507 34; once : 4385; error : 164 )

                       This is functionally equivalent to:

                         #pragma warning(disable:  4507 34)  // Disable warning messages 4507
                                                             //   and 34

                         #pragma warning(once:  4385)        // Issue warning 4385 only once

                         #pragma warning(error:  164)        // Report warning 164 as an error

                       For warning numbers greater than 4699, those associated with code
                       generation, the warning pragma has effect only when placed outside
                       function definitions.  The pragma is ignored if it specifies a number
                       greater than 4699 and is used inside a function.  The following example
		       illustrates the correct placement of warning pragmas to disable, and
                       then restore, the generation of a code-generation warning message:

                         int a;
                         #pragma warning( disable : 4705 )
                         void func()
                         {
                             a;
                         }
                         #pragma warning( default : 4705 )

                       The warning pragma also supports the following syntax:

                         #pragma warning(push[ ,n ])
                         #pragma warning(pop)

                       Where n represents a warning level (1 through 4).

                       The pragma warning( push ) stores the current warning state for all
		       warnings.  The pragma warning(push, n) stores the current state for all
                       warnings and sets the global warning level to n.

                       The pragma warning(pop) pops the last warning state pushed onto the
                       stack.  Any changes made to the warning state between push and pop are
                       undone.  Consider this example:

                         #pragma warning( push )
                         #pragma warning( disable : 4705 )
                         #pragma warning( disable : 4706 )
                         #pragma warning( disable : 4707 )
                         // Some code
                         #pragma warning( pop )

                       At the end of this code, pop restores the state of all warnings
                       (including 4705, 4706, and 4707) to what it was at the beginning of the
                       code.

                       When you write header files, you can use push and pop to ensure that
                       changes to warning states made by the user do not prevent your headers
                       from compiling properly.  Use push at the beginning of the header and
                       pop at the end.  Suppose, for example, you have a header that does not
                       compile cleanly at warning level 4.  The following code changes the
                       warning level to 3, then restores the original warning level at the end
		       of the header:

			 #pragma warning( push, 3 )
			 // Declarations/definitions
			 #pragma warning( pop )

*/

// Precompiled headers control

#define PF_PRECOMPILED_HEADERS_DONE                hdrstop
#define PF_PRECOMPILED_HEADERS_DONE_SET_FILE(file) hdrstop(file)

// Class/structure member packing

#define PF_PACKING_RESET                           pack()
#define PF_PACKING_SET(numBytes)                   pack(numBytes)
#define PF_PACKING_PUSH                            pack(push)
#define PF_PACKING_PUSH_AND_LABEL(label)           pack(push, label)
#define PF_PACKING_POP                             pack(pop)
#define PF_PACKING_POP_TO_LABEL(label)             pack(pop, label)

// Intrinsic routine/function control

#define PF_DECLARE_ROUTINE_INTRINSIC(routine)      intrinsic(routine)
#define PF_DECLARE_ROUTINE_NON_INTRINSIC(routine)  function(routine)

// Recursive inline expansion control

#define PF_INLINE_EXPANSION_DEPTH_RESET            inline_depth()
#define PF_INLINE_EXPANSION_DEPTH_SET(depth)       inline_depth(depth)
#define PF_INLINE_EXPANSION_RECURSION_RESET        inline_recursion()
#define PF_INLINE_EXPANSION_RECURSION_OFF          inline_recursion(off)
#define PF_INLINE_EXPANSION_RECURSION_ON           inline_recursion(on)

// Class compilation control

#define PF_CLASS_DEPENDENCY_TRACKING_OFF           component(minrebuild, off)
#define PF_CLASS_DEPENDENCY_TRACKING_ON            component(minrebuild, on)
#define PF_CLASS_HIDDEN_DISPS_VIRTUAL_BASES_OFF    vtordisp(off)
#define PF_CLASS_HIDDEN_DISPS_VIRTUAL_BASES_ON     vtordisp(on)

// Stack monitoring control

#define PF_STACK_CHECKING_OFF                      check_stack(off)
#define PF_STACK_CHECKING_ON                       check_stack(on)
#define PF_STACK_CHECKING_RESET                    check_stack()

// Compiler output

#define PF_OUTPUT_ON_COMPILE(text)                 message(text)
#define PF_PUT_TEXT_IN_TARGET(target, text)        comment(target, text)
#define PF_PUT_COMPILER_INFO_TEXT_IN_OBJ_FILE      comment(compiler)

// Browse information gathering control

#define PF_BROWSE_INFO_GATHER_REFS_TO_OFF(name)    component(browser, references, off, name)
#define PF_BROWSE_INFO_GATHER_REFS_TO_ON(name)     component(browser, references, on, name)
#define PF_BROWSE_INFO_GATHER_REFERENCES_OFF       component(browser, references, off)
#define PF_BROWSE_INFO_GATHER_REFERENCES_ON        component(browser, references, on)
#define PF_BROWSE_INFO_GATHERING_OFF               component(browser, off)
#define PF_BROWSE_INFO_GATHERING_ON                component(browser, on)

// Miscellaneous

#define PF_HEADER_FILE_ALIAS(alias, actual)        include(alias, actual)
#define PF_INCLUDE_ONCE_ONLY                       once
#define PF_SETLOCALE(locale)                       setlocale(locale)

// init_seg?
// pointers_to_members?
// optimize?
// warning?

// ============================================================================================
// COMPILER DEFICIENCY CORRECTIONS
// ============================================================================================

// This addresses an annoying feature of many PC compilers that needlessly stick to the "8.3"
// name format for their standard C/C++ header files:

#pragma include_alias(<strstream.h>   <strstrea.h>)
#pragma include_alias(<stdiostream.h> <stdiostr.h>)

// ============================================================================================
// GUARD MACRO DEFINITION
// ============================================================================================

#ifndef COMPILER_MICROSFT_H
  #define COMPILER_MICROSFT_H
#endif
