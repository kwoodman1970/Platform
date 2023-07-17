// ============================================================================================
//
// compiler/watcom.h
//
// ============================================================================================

#ifndef PLATFORM_H
  #error platform.h has not been included yet.
#endif

// ============================================================================================
// PLATFORM PROPERTY MACROS
// ============================================================================================

/*
The following was taken from the help files of Watcom C++ 11O:

  __COMPACT__           The compact memory model is being used.

  __FLAT__              The "flat" memory model is being used for the 80386 processor.  All
			segment registers refer to the same segment.

  __HUGE__              The huge memory model is being used.

  __LARGE__             The large memory model is being used.

  __MEDIUM__            The medium memory model is being used.

  __SMALL__             The small memory model is being used.

  __DOS__               The program is being compiled for use on a DOS operating system.

  __NETWARE_386__       The program is being compiled for use on the Novell Netware 386
			operating system.

  __NT__                The program is being compiled for use on the Windows NT operating
			system.

  __OS2__               The program is being compiled for use on the OS/2 operating system.

  __QNX__               The program is being compiled for use on the QNX operating system.

  __WINDOWS__           The program is being compiled for use with Microsoft Windows.

  __WINDOWS_386__       The program is being compiled for use with Microsoft Windows, using the
			Watcom 32-bit Windows interface.

  __CHEAP_WINDOWS__     The program is being compiled for use with Microsoft Windows using the
			"zW" compiler option [C/16 compiler only].

  __CHAR_SIGNED__       The program is being compiled using the "j" compiler option.  The
                        default char type is treated as a signed quantity.

  __FPI__               The program is being compiled using in-line floating point
                        instructions.

  __INLINE_FUNCTIONS__  The program is being compiled using the "oi" compiler option.

  __WATCOMC__           The compiler being used is the Watcom C/16 or Watcom C/32 compiler.
                        The value of the macro is the version number of the compiler times 100.

  __386__               The program is being compiled for the 80386 processor, using the Watcom
			C/32 compiler.

  MSDOS                 The program is being compiled for use on a DOS operating system.

  _M_IX86               The program is being compiled for a specific target architecture.  The
                        macro is identically equal to 100 times the architecture compiler
                        option value (-0, -1, -2, -3, -4, -5, etc.).  If "-5" (Pentium
                        instruction timings) was specified as a compiler option, then the value
                        of _M_IX86 would be 500.

  M_I86                 The program is being compiled for use on the Intel 80x86 processor.

  M_I386                The program is being compiled for use on the Intel 80386 processor.

  M_I86CM               The compact memory model is being used.

  M_I86HM               The huge memory model is being used.

  M_I86LM               The large memory model is being used.

  M_I86MM               The medium memory model is being used.

  M_I86SM               The small memory model is being used.

  NO_EXT_KEYS           The program is being compiled for ANSI/ISO conformance using the "za"
			(no extended keywords) compiler option.
*/

#ifndef COMPILER_WATCOM_H

  #define PF_COMPILER     PF_WATCOM
  #define PF_COMPILER_VER __WATCOMC__

  #if defined(__DOS__)
    #define PF_OS PF_DOS
  #elif defined(__OS2__)
    #define PF_OS PF_OS2
  #elif defined(__QNX__)
    #define PF_OS PF_QNX
  #elif defined(__NETWARE_386__)
    #define PF_OS PF_NETWARE386
  #elif defined(__WINDOWS__) && !defined(__WINDOWS_386__)
    #define PF_OS PF_WIN16
  #elif defined(__WINDOWS_386__)
    #define PF_OS PF_WIN32
  #else
    #define PF_OS PF_UNKNOWN_OS
  #endif

  #if defined(_M_IX86)
    #define PF_CPU PF_INTEL_80X86
  #else
    #define PF_CPU PF_UNKNOWN_CPU
  #endif

  #define PF_STD_LIB_CALL   _cdecl
  #define PF_MULTI_THREADED 0
  #define PF_DLL_IMPORT
  #define PF_DLL_EXPORT
  #define PF_DLL_CALL

#endif

// ============================================================================================
// PRAGMA DIRECTIVE MACROS
// ============================================================================================

/*
The following was taken from the help files of Watcom C++ 11O:

  These are the pragmas current recognized by the Watcom 16-bit compiler:

  unreferenced

    The "unreferenced" option controls the way Watcom C/C++ handles unused symbols.  For
    example,

      #pragma on (unreferenced);

    will cause Watcom C/C++ to issue warning messages for all unused symbols.  This is the
    default.  Specifying

      #pragma off (unreferenced);

    will cause Watcom C/C++ to ignore unused symbols.  Note that if the warning level is not
    high enough, warning messages for unused symbols will not be issued even if "unreferenced"
    was specified.

  check_stack

    The "check_stack" option controls the way stack overflows are to be handled.  For example,

      #pragma on (check_stack);

    will cause stack overflows to be detected and

      #pragma off (check_stack);

    will cause stack overflows to be ignored.  When "check_stack" is on, Watcom C/C++ will
    generate a run-time call to a stack-checking routine at the start of every routine
    compiled.  This run-time routine will issue an error if a stack overflow occurs when
    invoking the routine.  The default is to check for stack overflows.  Stack overflow
    checking is particularly useful when functions are invoked recursively.  Note that if the
    stack overflows and stack checking has been suppressed, unpredictable results can occur.

    If a stack overflow does occur during execution and you are sure that your program is not
    in error (i.e.  it is not unnecessarily recursing), you must increase the stack size.  This
    is done by linking your application again and specifying the "STACK" option to the Watcom
    Linker with a larger stack size.

    It is also possible to specify more than one option in a pragma as illustrated by the
    following example.

      #pragma on (check_stack unreferenced);

  reuse_duplicate_strings

    (C Only) The "reuse_duplicate_strings" option controls the way Watcom C handles identical
    strings in an expression.  For example,

      #pragma on (reuse_duplicate_strings);

    will cause Watcom C to reuse identical strings in an expression.  This is the default.
    Specifying

      #pragma off (reuse_duplicate_strings);

    will cause Watcom C to generate additional copies of the identical string.  The following
    example shows where this may be of importance to the way the application behaves.

    Example:

      #include <stdio.h>

      #pragma off (reuse_duplicate_strings)

      void poke( char *, char * );

      void main()
        {
          poke( "Hello world\n", "Hello world\n" );
        }

      void poke( char *x, char *y )
        {
          x[3] = 'X';
          printf( x );
          y[4] = 'Y';
          printf( y );
        }

      // Default output:
      // HelXo world
      // HelXY world

  library

    Default libraries are specified in special object module records.  Library names are
    extracted from these special records by the Watcom Linker.  When unresolved references
    remain after processing all object modules specified in linker "FILE" directives, these
    default libraries are searched after all libraries specified in linker "LIBRARY" directives
    have been searched.

    By default, that is if no library pragma is specified, the Watcom C/C++ compiler generates,
    in the object file defining the main program, default libraries corresponding to the memory
    model and floating-point model used to compile the file.  For example, if you have compiled
    the source file containing the main program for the medium memory model and the floating-
    point calls floating-point model, the libraries "clibm" and "mathm" will be placed in the
    object file.

    If you wish to add your own default libraries to this list, you can do so with a library
    pragma.  Consider the following example.

      #pragma library (mylib);

    The name "mylib" will be added to the list of default libraries specified in the object
    file.

    If the library specification contains characters such as '\', ':' or ',' (i.e., any
    character not allowed in a C identifier), you must enclose it in double quotes as in the
    following example.

      #pragma library ("\watcom\lib286\dos\graph.lib");
      #pragma library ("\watcom\lib386\dos\graph.lib");

    If you wish to specify more than one library in a library pragma you must separate them
    with spaces as in the following example.

      #pragma library (mylib "\watcom\lib286\dos\graph.lib");
      #pragma library (mylib "\watcom\lib386\dos\graph.lib");

  alloc_text

    The "alloc_text" pragma can be used to specify the name of the text segment into which the
    generated code for a function, or a list of functions, is to be placed.  The following
    describes the form of the "alloc_text" pragma.

      #pragma alloc_text (seg_name, fn[, ...])[;]

    where seg_name is the name of the text segment and fn is the name of a function.

    Consider the following example.

      extern int fn1(int);
      extern int fn2(void);
      #pragma alloc_text (my_text, fn1, fn2);

    The code for the functions fn1 and fn2 will be placed in the segment my_text.  Note:
    function prototypes for the named functions must exist prior to the "alloc_text" pragma.

  code_seg

    The "code_seg" pragma can be used to specify the name of the text segment into which the
    generated code for functions is to be placed.  The following describes the form of the
    "code_seg" pragma.

      #pragma code_seg (seg_name[, class_name])[;]

    where seg_name is the name of the text segment and class_name is the optional class name of
    the text segment (both parameters enclosed in quotes).  seg_name and class_name may be a
    macros as in:

      #define seg_name "MY_CODE_SEG"
      #pragma code_seg (seg_name);

      #define class_name "MY_CLASS"
      #pragma code_seg ( "MY_CODE_SEG", class_name );

    Consider the following example.

      #pragma code_seg ( "my_text" );

      int incr( int i )
      {
         return( i + 1 );
      }

      int decr( int i )
      {
         return( i - 1 );
      }

    The code for the functions incr and decr will be placed in the segment my_text.

  comment

    The "comment" pragma can be used to place a comment record in an object file or executable
    file.  The following describes the form of the "comment" pragma.

      #pragma comment (comment_type[, "comment_string"])[;]

    where comment_type specifies the type of comment record and "comment_string" is an optional
    string literal that provides additional information for some comment types..  The allowable
    comment types are:

      lib   Default libraries are specified in special object module records.  Library names
            are extracted from these special records by the Watcom Linker.  When unresolved
            references remain after processing all object modules specified in linker "FILE"
            directives, these default libraries are searched after all libraries specified in
            linker "LIBRARY" directives have been searched.

            The "lib" form of this pragma offers the same features as the "library" pragma.

    Consider the following example.

      #pragma comment ( lib, "mylib" );

  data_seg

    The "data_seg" pragma can be used to specify the name of the segment into which data is to
    be placed.  The following describes the form of the "data_seg" pragma.

      #pragma data_seg (seg_name[, class_name])[;]

    where seg_name is the name of the data segment and class_name is the optional class name of
    the data segment (both parameters enclosed in quotes).  seg_name and class_name may be a
    macros as in:

      #define seg_name "MY_DATA_SEG"
      #pragma data_seg (seg_name);

      #define class_name "MY_CLASS"
      #pragma data_seg ("MY_DATA_SEG", class_name);

    Consider the following example.

      #pragma data_seg ( "my_data" );

      static int i;
      static int j;

    The data for i and j will be placed in the segment my_data.

  disable_message

    The "disable_message" pragma disables the issuance of specified diagnostic messages.  The
    form of the "disable_message" pragma is as follows.

      #pragma disable_message (msg_num[, ...])[;]

    where msg_num is the number of the diagnostic message.  This number corresponds to the
    number issued by the compiler.  Make sure to strip all leading zeroes from the message
    number (to avoid interpretation as an octal constant).

  dump_object_model

    The "dump_object_model" pragma causes the C++ compiler to print information about the
    object model for an indicated class or an enumeration name to the diagnostics file.  For
    class names, this information includes the offsets and sizes of fields within the class
    and within base classes.  For enumeration names, this information consists of a list of all
    the enumeration constants with their values.

    The general form of the "dump_object_model" pragma is as follows.

      #pragma dump_object_model class[;]
      #pragma dump_object_model enumeration[;]

    where class is a defined C++ class free of errors and enumeration is a defined C++
    enumeration name.

    This pragma is designed to be used for information purposes only.

  enable_message

    The "enable_message" pragma re-enables the issuance of specified diagnostic messages that
    have been previously disabled.  The form of the "enable_message" pragma is as follows.

      #pragma enable_message (msg_num[, ...])[;]

    where msg_num is the number of the diagnostic message.  This number corresponds to the
    number issued by the compiler.  Make sure to strip all leading zeroes from the message
    number (to avoid interpretation as an octal constant).

  enum

    The "enum" pragma affects the underlying storage-definition for subsequent enum
    declarations.  The forms of the "enum" pragma are as follows.

      #pragma enum <int|minimum|original|pop>[;]

    where int makes int the underlying storage definition (same as the "ei" compiler option),
    minimum minimizes the underlying storage definition (same as not specifying the "ei"
    compiler option), original resets the underlying storage definition back to the original
    compiler option setting (i.e., what was or was not specified on the command line) and pop
    restores the previous setting.

    The first three forms all push the previous setting before establishing the new setting.

  error

    The "error" pragma can be used to issue an error message with the specified text.  The
    following describes the form of the "error" pragma.

      #pragma error "error text"[;]

    where "error text" is the text of the message that you wish to display.

    You should use the ANSI #error directive rather than this pragma.  This pragma is provided
    for compatibility with legacy code.  The following is an example.

        #if defined(__386__)
          ...
        #elif defined(__86__)
          ...
        #else
          #pragma error "neither __386__ or __86__ defined";
        #endif

  extref

    The "extref" pragma is used to generate a reference to an external function or data item.
    The form of the "extref" pragma is as follows.

      #pragma extref name[;]

    where name is the name of an external function or data item.  It must be declared to be an
    external function or data item before the pragma is encountered.  In C++, when name is a
    function, it must not be overloaded.

    This pragma causes an external reference for the function or data item to be emitted into
    the object file even if that function or data item is not referenced in the module.  The
    external reference will cause the linker to include the module containing that name in the
    linked program or DLL.

    This is useful for debugging since you can cause debugging routines (callable from within
    debugger) to be included into a program or DLL to be debugged.

    In C++, you can also force constructors and/or destructors to be called for a data item
    without necessarily referencing the data item anywhere in your code.

  function

    Certain functions, such as those listed in the description of the "oi" and "om" options,
    have intrinsic forms.  These functions are special functions that are recognized by the
    compiler and processed in a special way.  For example, the compiler may choose to generate
    in-line code for the function.  The intrinsic attribute for these special functions is set
    by specifying the"oi" or "om" option or using an "intrinsic" pragma.  The "function" pragma
    can be used to remove the intrinsic attribute for a specified list of functions.

    The following describes the form of the "function" pragma.

      #pragma function (fn[, ...])[;]

    where fn is the name of a function.

    Suppose the following source code was compiled using the "om" option so that when one of
    the special math functions is referenced, the intrinsic form will be used.  In our example,
    we have referenced the function sin which does have an intrinsic form.  By specifying sin
    in a "function" pragma, the intrinsic attribute will be removed, causing the function sin
    to be treated as a regular user-defined function.

      #include <math.h>

      #pragma function( sin );

      double test( double x )
      {
         return( sin( x ) );
      }

  initialize

    The "initialize" pragma sets the priority for initialization of static data in the file.
    This priority only applies to initialization of static data that requires the execution of
    code.  For example, the initialization of a class that contains a constructor requires the
    execution of the constructor.  Note that if the sequence in which initialization of static
    data in your program takes place has no dependencies, the "initialize" pragma need not be
    used.

    The general form of the "initialize" pragma is as follows.

      #pragma initialize [before|after] <n|library|program>[;]

    where n is a number representing the priority and must be in the range 0-255.  The larger
    the priority, the later the point at which initialization will occur.

    Priorities in the range 0-20 are reserved for the C++ compiler.  This is to ensure that
    proper initialization of the C++ run-time system takes place before the execution of your
    program.  The "library" keyword represents a priority of 32 and can be used for class
    libraries that require initialization before the program is initialized.  The "program"
    keyword represents a priority of 64 and is the default priority for any compiled code.
    Specifying "before" adjusts the priority by subtracting one.  Specifying "after" adjusts
    the priority by adding one.

    A source file containing the following "initialize" pragma specifies that the
    initialization of static data in the file will take place before initialization of all
    other static data in the program since a priority of 63 will be assigned.

    Example:

      #pragma initialize before program

    If we specify "after" instead of "before", the initialization of the static data in the
    file will occur after initialization of all other static data in the program since a
    priority of 65 will be assigned.

    Note that the following is equivalent to the "before" example

    Example:

      #pragma initialize 63

    and the following is equivalent to the "after" example.

    Example:

      #pragma initialize 65

    The use of the "before", "after", and "program" keywords are more descriptive in the intent
    of the pragmas.

    It is recommended that a priority of 32 (the priority used when the "library" keyword is
    specified) be used when developing class libraries.  This will ensure that initialization
    of static data defined by the class library will take place before initialization of static
    data defined by the program.  The following "initialize" pragma can be used to achieve
    this.

    Example:

      #pragma initialize library

  inline_depth

    When an in-line function is called, the function call may be replaced by the in-line
    expansion for that function.  This in-line expansion may include calls to other in-line
    functions which can also be expanded.  The "inline_depth" pragma can be used to set the
    number of times this expansion of in-line functions will occur for a call.

    The form of the "inline_depth" pragma is as follows.

      #pragma inline_depth [(]n[)][;]

    where n is the depth of expansion.  If n is 0, no expansion will occur.  If n is 1, only
    the original call is expanded.  If n is 2, the original call and the in-line functions
    invoked by the original function will be expanded.  The default value for n is 3.  The
    maximum value for n is 255.  Note that no expansion of recursive in-line functions occur
    unless enabled using the"inline_recursion" pragma.

  inline_recursion

    The "inline_recursion" pragma controls the recursive expansion of inline functions.  The
    form of the "inline_recursion" pragma is as follows.

      #pragma inline_recursion [(]on|off[)][;]

    Specifying "on" will enable expansion of recursive inline functions.  The depth of
    expansion is specified by the "inline_depth" pragma.  The default depth is 8.  Specifying
    "off" suppresses expansion of recursive inline functions.  This is the default.

  intrinsic

    Certain functions, those listed in the description of the "oi" option, have intrinsic
    forms.  These functions are special functions that are recognized by the compiler and
    processed in a special way.  For example, the compiler may choose to generate in-line code
    for the function.  The intrinsic attribute for these special functions is set by specifying
    the "oi" option or using an "intrinsic" pragma.

    The following describes the form of the "intrinsic" pragma.

         #pragma intrinsic (fn[, ...])[;]

    where fn is the name of a function.

    Suppose the following source code was compiled without using the "oi" option so that no
    function had the intrinsic attribute.  If we wanted the intrinsic form of the sin function
    to be used, we could specify the function in an"intrinsic" pragma.

      #include <math.h>
      #pragma intrinsic( sin );

      double test( double x )
      {
         return( sin( x ) );
      }

  message

    The "message" pragma can be used to issue a message with the specified text to the standard
    output without terminating compilation.  The following describes the form of the "message"
    pragma.

	 #pragma message ("message text")[;]

    where "message text" is the text of the message that you wish to display.

    The following is an example.

      #if defined(__386__)
        ...
      #else
        #pragma message ( "assuming 16-bit compile" );
      #endif

  once

    The "once" pragma can be used to indicate that the file which contains this pragma should
    only be opened and processed "once".  The following describes the form of the "once"
    pragma.

      #pragma once[;]

    Assume that the file "foo.h" contains the following text.

    Example:

      #ifndef _FOO_H_INCLUDED
      #define _FOO_H_INCLUDED
      #pragma once
         .
         .
         .
      #endif

    The first time that the compiler processes "foo.h" and encounters the "once" pragma, it
    records the file's name.  Subsequently, whenever the compiler encounters a #include
    statement that refers to "foo.h", it will not open the include file again.  This can help
    speed up processing of #include files and reduce the time required to compile an
    application.

  pack

    The "pack" pragma can be used to control the way in which structures are stored in memory.
    By default, Watcom C/C++ aligns all structures and its fields on a byte boundary.  There
    are 4 forms of the "pack" pragma.

    The following form of the "pack" pragma can be used to change the alignment of structures
    and their fields in memory.

      #pragma pack ([n])[;]

    where n is 1, 2, 4, 8 or 16 and specifies the method of alignment.

    The alignment of structure members is described in the following table.  If the size of the
    member is 1, 2, 4, 8 or 16, the alignment is given for each of the "zp" options.  If the
    member of the structure is an array or structure, the alignment is described by the row
    "x".

                         zp1     zp2     zp4     zp8     zp16
      sizeof(member) \---------------------------------------
             1       |   0       0       0       0       0
             2       |   0       2       2       2       2
             4       |   0       2       4       4       4
             8       |   0       2       4       8       8
             16      |   0       2       4       8       16
             x       |   aligned to largest member

    An alignment of 0 means no alignment, 2 means word boundary, 4 means doubleword boundary,
    etc.  If the largest member of structure "x" is 1 byte then "x" is not aligned.  If the
    largest member of structure "x" is 2 bytes then "x" is aligned according to row 2.  If the
    largest member of structure"x" is 4 bytes then "x" is aligned according to row 4.  If the
    largest member of structure "x" is 8 bytes then "x" is aligned according to row 8.  If the
    largest member of structure "x" is 16 bytes then "x" is aligned according to row 16.

    If no value is specified in the "pack" pragma, a default value of 2 is used.  Note that the
    default value can be changed with the "zp" Watcom C/C++ compiler command line option.

    The following form of the "pack" pragma can be used to save the current alignment amount on
    an internal stack.

      #pragma pack (push)[;]

    The following form of the "pack" pragma can be used to save the current alignment amount on
    an internal stack and set the current alignment.

      #pragma pack (push, number)[;]

    The following form of the "pack" pragma can be used to restore the previous alignment
    amount from an internal stack.

      #pragma pack (pop)[;]

  template_depth

    The "template_depth" pragma provides a hard limit for the amount of nested template
    expansions allowed so that infinite expansion can be detected.

    The form of the "template_depth" pragma is as follows.

      #pragma template_depth [(]n[)][;]

    where n is the depth of expansion.  If the value of n is less than 2, if will default to 2.
    If n is not specified, a warning message will be issued and the default value for n will be
    100.

    The following example of recursive template expansion illustrates why this pragma can be
    useful.

    Example:

      #pragma template_depth(10);

      template <class T>
      struct S {
         S<T*> x;
      };

      S<char> v;

  warning

    The "warning" pragma sets the level of warning messages.  The form of the "warning" pragma
    is as follows.

      #pragma warning msg_num level[;]

    where msg_num is the number of the warning message.  This number corresponds to the number
    issued by the compiler.  If msg_num is "*", the level of all warning messages is changed to
    the specified level.  Make sure to strip all leading zeroes from the message number (to
    avoid interpretation as an octal constant).

    level is a number from 0 to 9 and represents the level of the warning message.  When a
    value of zero is specified, the warning becomes an error.

  Auxiliary pragmas are used to describe attributes that affect code generation.  Initially,
  the compiler defines a default set of attributes.  Each auxiliary pragma refers to one of the
  following.

  1.	a symbol (such as a variable or function)

  2.	a type definition that resolves to a function type

  3.	the default set of attributes defined by the compiler

  When an auxiliary pragma refers to a particular symbol, a copy of the current set of default
  attributes is made and merged with the attributes specified in the auxiliary pragma.  The
  resulting attributes are assigned to the specified symbol and can only be changed by another
  auxiliary pragma that refers to the same symbol.

  An example of a type definition that resolves to a function type is the following.

    typedef void (*func_type)();

  When an auxiliary pragma refers to a such a type definition, a copy of the current set of
  default attributes is made and merged with the attributes specified in the auxiliary pragma.
  The resulting attributes are assigned to each function whose type matches the specified type
  definition.

  When "default" is specified instead of a symbol name, the attributes specified by the
  auxiliary pragma change the default set of attributes.  The resulting attributes are used by
  all symbols that have not been specifically referenced by a previous auxiliary pragma.

  Note that all auxiliary pragmas are processed before code generation begins.  Consider the
  following example.

    code in which symbol x is referenced
    #pragma aux y <attrs_1>;
    code in which symbol y is referenced
    code in which symbol z is referenced
    #pragma aux default <attrs_2>;
    #pragma aux x <attrs_3>;

  Auxiliary attributes are assigned to x, y and z in the following way.

    1.  Symbol x is assigned the initial default attributes merged with the attributes
        specified by <attrs_2> and <attrs_3>.

    2.  Symbol y is assigned the initial default attributes merged with the attributes
        specified by <attrs_1>.

    3.  Symbol z is assigned the initial default attributes merged with the attributes
        specified by <attrs_2>.

  When a symbol referred to by an auxiliary pragma includes an alias name, the attributes of
  the alias name are also assumed by the specified symbol.

  There are two methods of specifying alias information.  In the first method, the symbol
  assumes only the attributes of the alias name; no additional attributes can be specified.
  The second method is more general since it is possible to specify an alias name as well as
  additional auxiliary information.  In this case, the symbol assumes the attributes of the
  alias name as well as the attributes specified by the additional auxiliary information.

  The simple form of the auxiliary pragma used to specify an alias is as follows.

    #pragma aux (sym, alias)[;]

  where sym is any valid C/C++ identifier and alias is the alias name and is any valid C/C++
  identifier.  Consider the following example.

    #pragma aux push_args parm [] ;
    #pragma aux ( rtn, push_args ) ;

  The routine rtn assumes the attributes of the alias name push_args which specifies that the
  arguments to rtn are passed on the stack.

  Let us look at an example in which the symbol is a type definition.

    typedef void (func_type)(int);

    #pragma aux push_args parm [];

    #pragma aux (func_type, push_args);

    extern func_type rtn1;
    extern func_type rtn2;

  The first auxiliary pragma defines an alias name called push_args that specifies the
  mechanism to be used to pass arguments.  The mechanism is to pass all arguments on the stack.
  The second auxiliary pragma associates the attributes specified in the first pragma with the
  type definition func_type.  Since rtn1 and rtn2 are of type func_type, arguments to either of
  those functions will be passed on the stack.

  The general form of an auxiliary pragma that can be used to specify an alias is as follows.

    #pragma aux (alias) sym aux_attrs[;]

  where alias is the alias name and is any valid C/C++ identifier, sym is any valid C/C++
  identifier, and aux_attrs are attributes that can be specified with the auxiliary pragma.

  Consider the following example.

    #pragma aux MS_C "_*"                                                                     \
		     parm caller []                                                           \
                     value struct float struct routine [ax]                                   \
                     modify [ax bx cx dx es];
    #pragma aux (MS_C) rtn1;
    #pragma aux (MS_C) rtn2;
    #pragma aux (MS_C) rtn3;

  The routines rtn1, rtn2 and rtn3 assume the same attributes as the alias name MS_C which
  defines the calling convention used by the Microsoft C compiler.  Whenever calls are made to
  rtn1, rtn2 and rtn3, the Microsoft C calling convention will be used.

  Note that if the attributes of MS_C change, only one pragma needs to be changed.  If we had
  not used an alias name and specified the attributes in each of the three pragmas for rtn1,
  rtn2 and rtn3, we would have to change all three pragmas.  This approach also reduces the
  amount of memory required by the compiler to process the source file.

  WARNING!  The alias name MS_C is just another symbol.  If MS_C appeared in your source code,
  it would assume the attributes specified in the pragma for MS_C.

  A number of symbols are predefined by the compiler with a set of attributes that describe a
  particular calling convention.  These symbols can be used as aliases.  The following is a
  list of these symbols.

    __cdecl   __cdecl or cdecl defines the calling convention used by Microsoft compilers.

    __pascal  __pascal or pascal defines the calling convention used by OS/2 1.x and Windows
              3.x API functions.

  The following describes the attributes of the above alias names.

    #pragma aux __cdecl "_*"                                                                  \
                        parm caller []                                                        \
                        value struct float struct routine [ax]                                \
                        modify [ax bx cx dx es]

      Notes:

      1.  All symbols are preceded by an underscore character.

      2.  Arguments are pushed on the stack from right to left.  That is, the last argument is
          pushed first.  The calling routine will remove the arguments from the stack.

      3.  Floating-point values are returned in the same way as structures.  When a structure
          is returned, the called routine allocates space for the return value and returns a
          pointer to the return value in register AX.

      4.  Registers AX, BX, CX and DX, and segment register ES are not saved and restored when
          a call is made.

    #pragma aux __pascal "^"                                                                  \
                         parm reverse routine []                                              \
                         value struct float struct caller []                                  \
                         modify [ax bx cx dx es]

      Notes:

      1.  All symbols are mapped to upper case.

      2.  Arguments are pushed on the stack in reverse order.  That is, the first argument is
          pushed first, the second argument is pushed next, and so on.  The routine being
          called will remove the arguments from the stack.

      3.  Floating-point values are returned in the same way as structures.  When a structure
          is returned, the caller allocates space on the stack.  The address of the allocated
          space will be pushed on the stack immediately before the call instruction.  Upon
          returning from the call, register AX will contain address of the space allocated for
          the return value. 4.  Registers AX, BX, CX and DX, and segment register ES are not
          saved and restored when a call is made.

  The following form of the auxiliary pragma can be used to describe the mapping of a symbol
  from its source form to its object form.

    #pragma aux sym obj_name[;]

  where sym is any valid C/C++ identifier and obj_name is any character string enclosed in
  double quotes.

  When specifying obj_name, the asterisk character ('*') has a special meaning; it is a
  placeholder for sym.

  In the following example, the name "myrtn" will be replaced by "myrtn_" in the object file.

    #pragma aux myrtn "*_";

  This is the default for all function names.

  In the following example, the name "myvar" will be replaced by "_myvar" in the object file.

    #pragma aux myvar "_*";

  This is the default for all variable names.

  The default mapping for all symbols can also be changed as illustrated by the following
  example.

    #pragma aux default "_*_";

  The above auxiliary pragma specifies that all names will be prefixed and suffixed by an
  underscore character ('_').

  The '^' character also has a special meaning.  Whenever it is encountered in obj_name, it is
  replaced by the upper case version of sym.

  In the following example, the name "myrtn" will be replaced by "MYRTN" in the object file.

    #pragma aux myrtn "^";

  The following form of the auxiliary pragma can be used to describe the way a function is to
  be called.

    #pragma aux sym far[;]
    #pragma aux sym near[;]
    #pragma aux sym = <const|seg id|offset id|reloff id|float fpinst|"asm">

  where sym is a function name, const is a valid C/C++ integer constant, id is any valid C/C++
  identifier, fpinst is a sequence of bytes that forms a valid 80x87 instruction (the keyword
  float must precede fpinst so that special fixups are applied to the 80x87 instruction), seg
  specifies the segment of the symbol id, offset specifies the offset of the symbol id, reloff
  specifies the relative offset of the symbol id for near control transfers, and asm is an
  assembly language instruction or directive.

  In the following example, Watcom C/C++ will generate a far call to the function myrtn.

    #pragma aux myrtn far;

  Note that this overrides the calling sequence that would normally be generated for a
  particular memory model.  In other words, a far call will be generated even if you are
  compiling for a memory model with a small code model.

  In the following example, Watcom C/C++ will generate a near call to the function myrtn.

    #pragma aux myrtn near;

  Note that this overrides the calling sequence that would normally be generated for a
  particular memory model.  In other words, a near call will be generated even if you are
  compiling for a memory model with a big code model.

  In the following DOS example, Watcom C/C++ will generate the sequence of bytes following the
  "=" character in the auxiliary pragma whenever a call to mode4 is encountered.  mode4 is
  called an in-line function.

    void mode4(void);
    #pragma aux mode4 = 0xb4 0x00                                                 \ // mov AH,0
                        0xb0 0x04                                                 \ // mov AL,4
                        0xcd 0x10                                                 \ // int 10H
                        modify [ AH AL ];

  The sequence in the above DOS example represents the following lines of assembly language
  instructions.

    mov   AH,0       ; select function "set mode"
    mov   AL,4       ; specify mode (mode 4)

    int   10H        ; BIOS video call

  The above example demonstrates how to generate BIOS function calls in-line without writing an
  assembly language function and calling it from your C/C++ program.  The C prototype for the
  function mode4 is not necessary but is included so that we can take advantage of the argument
  type checking provided by Watcom C/C++.

  The following DOS example is equivalent to the above example but mnemonics for the assembly
  language instructions are used instead of the binary encoding of the assembly language
  instructions.

    void mode4(void);
    #pragma aux mode4 = "mov AH,0",                                                           \
                        "mov AL,4",                                                           \
                        "int 10H"                                                             \
                        modify [ AH AL ];

  If a sequence of in-line assembly language instructions contains 80x87 floating-point
  instructions, each floating-point instruction must be preceded by "float".  Note that this is
  only required if you have specified the "fpi" compiler option; otherwise it will be ignored.

  The following example generates the 80x87 "square root" instruction.

    double mysqrt(double);
    #pragma aux mysqrt parm [8087] = float 0xd9 0xfa;  // fsqrt

  A sequence of in-line assembly language instructions may contain symbolic references.  In the
  following example, a near call to the function myalias is made whenever myrtn is called.

    extern void myalias(void);

    void myrtn(void);
    #pragma aux myrtn = 0xe8 offset myalias;  // near call

  In the following example, a far call to the function myalias is made whenever myrtn is
  called.

    extern void myalias(void);
    void myrtn(void);
    #pragma aux myrtn = 0x9a offset myalias seg myalias;  // far call

  An application may have been compiled so that the segment register DS does not contain the
  segment address of the default data segment (group "DGROUP").  This is usually the case if
  you are using a large data memory model.  Suppose you wish to call a function that assumes
  that the segment register DS contains the segment address of the default data segment.  It
  would be very cumbersome if you were forced to compile your application so that the segment
  register DS contained the default data segment (a small data memory model).

  The following form of the auxiliary pragma will cause the segment register DS to be loaded
  with the segment address of the default data segment before calling the specified function.

    #pragma aux sym parm loadds[;]

  where sym is a function name.

  Alternatively, the following form of the auxiliary pragma will cause the segment register DS
  to be loaded with the segment address of the default data segment as part of the prologue
  sequence for the specified function.

    #pragma aux sym loadds[;]

  where sym is a function name.

  An exported symbol in a dynamic link library is a symbol that can be referenced by an
  application that is linked with that dynamic link library.  Normally, symbols in dynamic link
  libraries are exported using the Watcom Linker "EXPORT" directive.  An alternative method is
  to use the following form of the auxiliary pragma.

    #pragma aux sym export[;]

  where sym is a function name.

  When compiling a Microsoft Windows application, you must use the "zW" option so that special
  prologue/epilogue sequences are generated.  Furthermore, callback functions require larger
  prologue/epilogue sequences than those generated when the "zW" compiler option is specified.
  The following form of the auxiliary pragma will cause a callback prologue/epilogue sequence
  to be generated for a callback function when compiled using the "zW" option.

    #pragma aux sym export[;]

  where sym is a callback function name.

  Alternatively, the "zw" compiler option can be used to generate callback prologue/epilogue
  sequences.  However, all functions contained in a module compiled using the "zw" option will
  have a callback prologue/epilogue sequence even if the functions are not callback functions.

  Normally, a function contains a stack frame if arguments are passed on the stack or an
  automatic variable is allocated on the stack.  No stack frame will be generated if the above
  conditions are not satisfied.  The following form of the auxiliary pragma will force a stack
  frame to be generated under any circumstance.

    #pragma aux sym frame[;]

  where sym is a function name.

  Using auxiliary pragmas, you can describe the calling convention that Watcom C/C++ is to use
  for calling functions.  This is particularly useful when interfacing to functions that have
  been compiled by other compilers or functions written in other programming languages.

  The general form of an auxiliary pragma that describes argument passing is the following.

    #pragma aux sym parm <pop_info|routine|reverse|reg_set>[;]

  where sym is a function name and reg_set is called a register set.

  The register sets specify the registers that are to be used for argument passing.  A register
  set is a list of registers separated by spaces and enclosed in square brackets. The following
  form of the auxiliary pragma can be used to specify the registers that are to be used to pass
  arguments to a particular function.

    #pragma aux sym parm <reg_set>[;]

  where sym is a function name and reg_set is called a register set.

  The register sets specify the registers that are to be used for argument passing.  A register
  set is a list of registers separated by spaces and enclosed in square brackets.

  Register sets establish a priority for register allocation during argument list processing.
  Register sets are processed from left to right.  However, within a register set, registers
  are chosen in any order.  Once all register sets have been processed, any remaining arguments
  are pushed on the stack.

  Note that regardless of the register sets specified, only certain combinations of registers
  will be selected for arguments of a particular type.

  Note that arguments of type float and double are always pushed on the stack when the "fpi" or
  "fpi87" option is used.

  double

    Arguments of type double can only be passed in the following register combination:
    AX:BX:CX:DX.  For example, if the following register set was specified for a routine having
    an argument of type double,

      [AX BX SI DI]

    the argument would be pushed on the stack since a valid register combination for 8-byte
    arguments is not contained in the register set.  Note that this method for passing
    arguments of type double is supported only when the "fpc" option is used.  Note that this
    argument passing method does not include the passing of 8-byte structures.

  far pointer

    A far pointer can only be passed in one of the following register pairs: DX:AX, CX:BX,
    CX:AX, CX:SI, DX:BX, DI:AX, CX:DI, DX:SI, DI:BX, SI:AX, CX:DX, DX:DI, DI:SI, SI:BX, BX:AX,
    DS:CX, DS:DX, DS:DI, DS:SI, DS:BX, DS:AX, ES:CX, ES:DX, ES:DI, ES:SI, ES:BX or ES:AX.  For
    example, if a far pointer is passed to a function with the following register set,

      [ES BP]

    the argument would be pushed on the stack since a valid register combination for a far
    pointer is not contained in the register set.

  long int, float

    The only registers that will be assigned to 4-byte arguments (e.g., arguments of type long
    int,) are:  DX:AX, CX:BX, CX:AX, CX:SI, DX:BX, DI:AX, CX:DI, DX:SI, DI:BX, SI:AX, CX:DX,
    DX:DI, DI:SI, SI:BX and BX:AX.  For example, if the following register set was specified
    for a routine with one argument of type long int,

      [ES DI]

    the argument would be pushed on the stack since a valid register combination for 4-byte
    arguments is not contained in the register set.  Note that this argument passing method
    includes 4-byte structures.  Note that this argument passing method includes arguments of
    type float but only when the "fpc" option is used.

  int

    The only registers that will be assigned to 2-byte arguments (e.g., arguments of type int)
    are:  AX, BX, CX, DX, SI and DI.  For example, if the following register set was specified
    for a routine with one argument of type int,

      [BP]

    the argument would be pushed on the stack since a valid register combination for 2-byte
    arguments is not contained in the register set.

  char

    Arguments whose size is 1 byte (e.g., arguments of type char) are promoted to 2 bytes and
    are then assigned registers as if they were 2-byte arguments.

  others

    Arguments that do not fall into one of the above categories cannot be passed in registers
    and are pushed on the stack.  Once an argument has been assigned a position on the stack,
    all remaining arguments will be assigned a position on the stack even if all register sets
    have not yet been exhausted.

  Notes:

  1.  The default register set is [AX BX CX DX].

  2.  Specifying registers AH and AL is equivalent to specifying register AX.  Specifying
      registers DH and DL is equivalent to specifying register DX.  Specifying registers CH and
      CL is equivalent to specifying register CX. Specifying registers BH and BL is equivalent
      to specifying register BX.

  3.  If you are compiling for a memory model with a small data model, or the "zdp" compiler
      option is specified, any register combination containing register DS becomes illegal.  In
      a small data model, segment register DS must remain unchanged as it points to the
      program's data segment.  Note that the "zdf" compiler option can be used to specify that
      register DS does not contain that segment address of the program's data segment.  In this
      case, register combinations containing register DS are legal.

  Consider the following example.

    #pragma aux myrtn parm [ax bx cx dx] [bp si];

  Suppose myrtn is a routine with 3 arguments each of type long int.

    1.  The first argument will be passed in the register pair DX:AX.

    2.  The second argument will be passed in the register pair CX:BX.

    3.  The third argument will be pushed on the stack since BP:SI is not a valid register pair
        for arguments of type long int.

  It is possible for registers from the second register set to be used before registers from
  the first register set are used.  Consider the following example.

    #pragma aux myrtn parm [ax bx cx dx] [si di];

  Suppose myrtn is a routine with 3 arguments, the first of type int and the second and third
  of type long int.

    1.  The first argument will be passed in the register AX.

    2.  The second argument will be passed in the register pair CX:BX.

    3.  The third argument will be passed in the register set DI:SI.

  Note that registers are no longer selected from a register set after registers are selected
  from subsequent register sets, even if all registers from the original register set have not
  been exhausted.

  An empty register set is permitted.  All subsequent register sets appearing after an empty
  register set are ignored; all remaining arguments are pushed on the stack.

  Notes:

  1.  If a single empty register set is specified, all arguments are passed on the stack.

  2.  If no register set is specified, the default register set [AX BX CX DX] is used.

  It is possible to force arguments into specific registers.  Suppose you have a function, say
  "mycopy", that copies data.  The first argument is the source, the second argument is the
  destination, and the third argument is the length to copy.  If we want the first argument to
  be passed in the register SI, the second argument to be passed in register DI and the third
  argument to be passed in register CX, the following auxiliary pragma can be used.

    void mycopy( char near *, char *, int );

    #pragma aux mycopy parm [DI] [SI] [CX];

  Note that you must be aware of the size of the arguments to ensure that the arguments get
  passed in the appropriate registers.

  For functions whose code is generated by Watcom C/C++ and whose argument list is described by
  an auxiliary pragma, Watcom C/C++ has some freedom in choosing how arguments are assigned to
  registers.  Since the code for in-line functions is specified by the programmer, the
  description of the argument list must be very explicit.  To achieve this, Watcom C/C++
  assumes that each register set corresponds to an argument.  Consider the following DOS
  example of an in-line function called scrollactivepgup.

    void scrollactivepgup(char,char,char,char,char,char);
    #pragma aux scrollactivepgup = "mov AH,6"                                                 \
                                   "int 10h"                                                  \
                                   parm [ch] [cl] [dh] [dl] [al] [bh]                         \
                                   modify [ah];

  The BIOS video call to scroll the active page up requires the following arguments.

    1.  The row and column of the upper left corner of the scroll window is passed in registers
        CH and CL respectively.

    2.  The row and column of the lower right corner of the scroll window is passed in
        registers DH and DL respectively.

    3.  The number of lines blanked at the bottom of the window is passed in register AL.

    4.  The attribute to be used on the blank lines is passed in register BH.

  When passing arguments, Watcom C/C++ will convert the argument so that it fits in the
  register(s) specified in the register set for that argument.  For example, in the above
  example, if the first argument to scrollactivepgup was called with an argument whose type was
  int, it would first be converted to char before assigning it to register CH.  Similarly, if
  an in-line function required its argument in register pair DX:AX and the argument was of type
  short int, the argument would be converted to long int before assigning it to register pair
  DX:AX.

  In general, Watcom C/C++ assigns the following types to register sets.

    1.  A register set consisting of a single 8-bit register (1 byte) is assigned a type of
	unsigned char.

    2.  A register set consisting of a single 16-bit register (2 bytes) is assigned a type of
        unsigned short int.

    3.  A register set consisting of two 16-bit registers (4 bytes) is assigned a type of
        unsigned long int.

    4.  A register set consisting of four 16-bit registers (8 bytes) is assigned a type of
        double.

  The following form of the auxiliary pragma specifies who removes from the stack arguments
  that were pushed on the stack.

    #pragma aux sym parm (caller|routine)[;]

  where sym is a function name.

  "caller" specifies that the caller will pop the arguments from the stack; "routine" specifies
  that the called routine will pop the arguments from the stack.  If "caller" or "routine" is
  omitted, "routine" is assumed unless the default has been changed in a previous auxiliary
  pragma, in which case the new default is assumed.

  The following form of the auxiliary pragma specifies that arguments are passed in the reverse
  order.

    #pragma aux sym parm reverse[;]

  where sym is a function name.

  Normally, arguments are processed from left to right.  The leftmost arguments are passed in
  registers and the rightmost arguments are passed on the stack (if the registers used for
  argument passing have been exhausted).  Arguments that are passed on the stack are pushed
  from right to left.

  When arguments are reversed, the rightmost arguments are passed in registers and the leftmost
  arguments are passed on the stack (if the registers used for argument passing have been
  exhausted).  Arguments that are passed on the stack are pushed from left to right.

  Reversing arguments is most useful for functions that require arguments to be passed on the
  stack in an order opposite from the default.  The following auxiliary pragma demonstrates
  such a function.

    #pragma aux rtn parm reverse [];

  Using auxiliary pragmas, you can describe the way functions are to return values.  This is
  particularly useful when interfacing to functions that have been compiled by other compilers
  or functions written in other programming languages.

  The general form of an auxiliary pragma that describes the way a function returns its value
  is the following.

    #pragma aux sym value <no8087|reg_set|float|struct|routine|caller|reg_set>[;]

  where sym is a function name and reg_set is called a register set.

  The register sets specify the registers that are to be used for argument passing.  A register
  set is a list of registers separated by spaces and enclosed in square brackets.

  The following form of the auxiliary pragma can be used to specify the registers that are to
  be used to return a function's value.

    #pragma aux sym value reg_set[;]

  where sym is a function name and reg_set is a register set.

  Note that the method described below for returning values of type float or double is
  supported only when the "fpc" option is used.

  Depending on the type of the return value, only certain registers are allowed in reg_set.

  1-byte

    For 1-byte return values, only the following registers are allowed:  AL, AH, DL, DH, BL,
    BH, CL or CH.  If no register set is specified, register AL will be used.


  2-byte

    For 2-byte return values, only the following registers are allowed:  AX, DX, BX, CX, SI or
    DI.  If no register set is specified, register AX will be used.


  4-byte

    For 4-byte return values (except far pointers), only the following register pairs are
    allowed:  DX:AX, CX:BX, CX:AX, CX:SI, DX:BX, DI:AX, CX:DI, DX:SI, DI:BX, SI:AX, CX:DX,
    DX:DI, DI:SI, SI:BX or BX:AX.  If no register set is specified, registers DX:AX will be
    used.  This form of the auxiliary pragma is legal for functions of type float when using
    the "fpc" option only.


  far pointer

    For functions that return far pointers, the following register pairs are allowed:  DX:AX,
    CX:BX, CX:AX, CX:SI, DX:BX, DI:AX, CX:DI, DX:SI, DI:BX, SI:AX, CX:DX, DX:DI, DI:SI, SI:BX,
    BX:AX, DS:CX, DS:DX, DS:DI, DS:SI, DS:BX, DS:AX, ES:CX, ES:DX, ES:DI, ES:SI, ES:BX or
    ES:AX.  If no register set is specified, the registers DX:AX will be used.

  8-byte

    For 8-byte return values (including functions of type double), only the following register
    combination is allowed:  AX:BX:CX:DX.  If no register set is specified, the registers
    AX:BX:CX:DX will be used.  This form of the auxiliary pragma is legal for functions of type
    double when using the "fpc" option only.

  Notes:

  1.  An empty register set is not allowed.

  2.  If you are compiling for a memory model which has a small data model, any of the above
      register combinations containing register DS becomes illegal.  In a small data model,
      segment register DS must remain unchanged as it points to the program's data segment.

  Typically, structures are not returned in registers.  Instead, the caller allocates space on
  the stack for the return value and sets register SI to point to it.  The called routine then
  places the return value at the location pointed to by register SI.

  The following form of the auxiliary pragma can be used to specify the register that is to be
  used to point to the return value.

    #pragma aux sym value struct <caller|routine> reg_set[;]

  where sym is a function name and reg_set is a register set.

  "caller" specifies that the caller will allocate memory for the return value.  The address of
  the memory allocated for the return value is placed in the register specified in the register
  set by the caller before the function is called.  If an empty register set is specified, the
  address of the memory allocated for the return value will be pushed on the stack immediately
  before the call and will be returned in register AX by the called routine.  It is assumed
  that the memory for the return value is allocated from the stack segment (the stack segment
  is contained in segment register SS).

  "routine" specifies that the called routine will allocate memory for the return value.  Upon
  returning to the caller, the register specified in the register set will contain the address
  of the return value.  An empty register set is not allowed.

  Only the following registers are allowed in the register set:  AX, DX, BX, CX, SI or DI.
  Note that in a big data model, the address in the return register is assumed to be in the
  segment specified by the value in the SS segment register.

  If the size of the structure being returned is 1, 2 or 4 bytes, it will be returned in
  registers.  The return register will be selected from the register set in the following way.

    1.  A 1-byte structure will be returned in one of the following registers:  AL, AH, DL, DH,
        BL, BH, CL or CH.  If no register set is specified, register AL will be used.

    2.  A 2-byte structure will be returned in one of the following registers:  AX, DX, BX, CX,
        SI or DI.  If no register set is specified, register AX will be used.

    3.  A 4-byte structure will be returned in one of the following register pairs:  DX:AX,
        CX:BX, CX:AX, CX:SI, DX:BX, DI:AX, CX:DI, DX:SI, DI:BX, SI:AX, CX:DX, DX:DI, DI:SI,
        SI:BX or BX:AX.  If no register set is specified, register pair DX:AX will be used.

  The following form of the auxiliary pragma can be used to specify that structures whose size
  is 1, 2 or 4 bytes are not to be returned in registers.  Instead, the caller will allocate
  space on the stack for the structure return value and point register SI to it.

    #pragma aux sym value struct struct[;]

  where sym is a function name.

  There are a few ways available for specifying how the value for a function whose type is
  float or double is to be returned.

  The following form of the auxiliary pragma can be used to specify that function return values
  whose type is float or double are not to be returned in registers.  Instead, the caller will
  allocate space on the stack for the return value and point register SI to it.

    #pragma aux sym value struct float[;]

  where sym is a function name.

  In other words, floating-point values are to be returned in the same way structures are
  returned.

  The following form of the auxiliary pragma can be used to specify that function return values
  whose type is float or double are not to be returned in 80x87 registers when compiling with
  the "fpi" or "fpi87" option.  Instead, the value will be returned in 80x86 registers.  This
  is the default behaviour for the "fpc" option.  Function return values whose type is float
  will be returned in registers DX:AX.  Function return values whose type is double will be
  returned in registers AX:BX:CX:DX.  This is the default method for the "fpc" option.

    #pragma aux sym value no8087[;]

  where sym is a function name.

  The following form of the auxiliary pragma can be used to specify that function return values
  whose type is float or double are to be returned in ST(0) when compiling with the "fpi" or
  "fpi87" option.  This form of the auxiliary pragma is not legal for the "fpc" option.

    #pragma aux sym value [8087][;]

  where sym is a function name.

  The following form of the auxiliary pragma can be used to describe a function that does not
  return to the caller.

    #pragma aux sym aborts[;]

  where sym is a function name.

  Consider the following example.

    #pragma aux exitrtn aborts;
    extern void exitrtn(void);

    void rtn()
      {
        exitrtn();
      }

  exitrtn is defined to be a function that does not return.  For example, it may call exit to
  return to the system.  In this case, Watcom C/C++ generates a "jmp" instruction instead of a
  "call" instruction to invoke exitrtn.

  The following form of the auxiliary pragma can be used to describe a function that does not
  modify any memory (i.e., global or static variables) that is used directly or indirectly by
  the caller.

    #pragma aux sym modify nomemory[;]

  where sym is a function name.

  Consider the following example.

    #pragma off (check_stack);

    extern void myrtn(void);

    int i = { 1033 };

    extern Rtn() {
        while( i < 10000 ) {
            i += 383;
        }
        myrtn();
        i += 13143;
    };

  To compile the above program, "rtn.c", we issue the following command.

    C>wcc rtn /oai /d1

    C>wpp rtn /oai /d1
    C>wcc386 rtn /oai /d1
    C>wpp386 rtn /oai /d1

  For illustrative purposes, we omit loop optimizations from the list of code optimizations
  that we want the compiler to perform.  The "d1" compiler option is specified so that the
  object file produced by Watcom C/C++ contains source line information.

  We can generate a file containing a disassembly of RTN.OBJ by issuing the following command.

    C>wdis rtn /l /s /r

  The "s" option is specified so that the listing file produced by the Watcom Disassembler
  contains source lines taken from RTN.C.  The listing file RTN.LST appears as follows.

    Module: rtn.c
    Group: 'DGROUP' CONST,_DATA

    Segment: '_TEXT' BYTE  0026 bytes

    #pragma off (check_stack);

    extern void MyRtn( void );

    int i = { 1033 };


    extern Rtn()

      {
     0000  52                Rtn_            push    DX
     0001  8b 16 00 00                       mov     DX,_i

        while( i < 10000 ) {
     0005  81 fa 10 27       L1              cmp     DX,2710H
     0009  7d 06                             jge     L2

            i += 383;
        }
     000b  81 c2 7f 01                       add     DX,017fH
     000f  eb f4                             jmp     L1

        MyRtn();
     0011  89 16 00 00       L2              mov     _i,DX
     0015  e8 00 00                          call    MyRtn_
     0018  8b 16 00 00                       mov     DX,_i

        i += 13143;
     001c  81 c2 57 33                       add     DX,3357H
     0020  89 16 00 00                       mov     _i,DX

      };
     0024  5a                                pop     DX

     0025  c3                                ret


    No disassembly errors

    ------------------------------------------------------------

    Segment: '_DATA' WORD  0002 bytes
     0000  09 04                   _i              - ..

    No disassembly errors

    ------------------------------------------------------------

  Let us add the following auxiliary pragma to the source file.

    #pragma aux myrtn modify nomemory;

  If we compile the source file with the above pragma and disassemble the object file using the
  Watcom Disassembler, we get the following listing file.

    Module: rtn.c
    Group: 'DGROUP' CONST,_DATA

    Segment: '_TEXT' BYTE  0022 bytes

    #pragma off (check_stack);

    extern void MyRtn( void );
    #pragma aux MyRtn modify nomemory;

    int i = { 1033 };

    extern Rtn()
      {
     0000  52                Rtn_            push    DX
     0001  8b 16 00 00                       mov     DX,_i

        while( i < 10000 ) {
     0005  81 fa 10 27       L1              cmp     DX,2710H
     0009  7d 06                             jge     L2

            i += 383;
        }
     000b  81 c2 7f 01                       add     DX,017fH

     000f  eb f4                             jmp     L1


        MyRtn();
     0011  89 16 00 00       L2              mov     _i,DX
     0015  e8 00 00                          call    MyRtn_

        i += 13143;
     0018  81 c2 57 33                       add     DX,3357H
     001c  89 16 00 00                       mov     _i,DX

      };
     0020  5a                                pop     DX

     0021  c3                                ret


    No disassembly errors

    ------------------------------------------------------------

    Segment: '_DATA' WORD  0002 bytes
     0000  09 04                   _i              - ..

    No disassembly errors

    ------------------------------------------------------------

  Notice that the value of i is in register DX after completion of the "while" loop.  After the
  call to myrtn, the value of i is not loaded from memory into a register to perform the final
  addition.  The auxiliary pragma informs the compiler that myrtn does not modify any memory
  (i.e., global or static variables) that is used directly or indirectly by Rtn and hence
  register DX contains the correct value of i.

  The preceding auxiliary pragma deals with routines that modify memory.  Let us consider the
  case where routines reference memory.  The following form of the auxiliary pragma can be used
  to describe a function that does not reference any memory (i.e., global or static variables)
  that is used directly or indirectly by the caller.

    #pragma aux <sym> parm nomemory modify nomemory[;]

  where sym is a function name.

  Notes:

    1.  You must specify both "parm nomemory" and "modify nomemory".

  Let us replace the auxiliary pragma in the above example with the following auxiliary pragma.

    #pragma aux myrtn parm nomemory modify nomemory;

  If you now compile our source file and disassemble the object file using WDIS, the result is
  the following listing file.

    Module: rtn.c
    Group: 'DGROUP' CONST,_DATA

    Segment: '_TEXT' BYTE  001e bytes

    #pragma off (check_stack);

    extern void MyRtn( void );
    #pragma aux MyRtn parm nomemory modify nomemory;

    int i = { 1033 };


    extern Rtn()
      {
     0000  52                Rtn_            push    DX
     0001  8b 16 00 00                       mov     DX,_i

        while( i < 10000 ) {
     0005  81 fa 10 27       L1              cmp     DX,2710H
     0009  7d 06                             jge     L2

            i += 383;
        }
     000b  81 c2 7f 01                       add     DX,017fH
     000f  eb f4                             jmp     L1


	MyRtn();
     0011  e8 00 00          L2              call    MyRtn_

        i += 13143;
     0014  81 c2 57 33                       add     DX,3357H
     0018  89 16 00 00                       mov     _i,DX

      };

     001c  5a                                pop     DX
     001d  c3                                ret


    No disassembly errors

    ------------------------------------------------------------

    Segment: '_DATA' WORD  0002 bytes
     0000  09 04                   _i              - ..

    No disassembly errors

    ------------------------------------------------------------

  Notice that after completion of the "while" loop we did not have to update i with the value
  in register DX before calling myrtn.  The auxiliary pragma informs the compiler that myrtn
  does not reference any memory (i.e., global or static variables) that is used directly or
  indirectly by myrtn so updating i was not necessary before calling myrtn.

  The following form of the auxiliary pragma can be used to describe the registers that a
  function will use without saving.

    #pragma aux <sym> modify [exact] <reg_set>[;]

  where sym is a function name and reg_set is a register set.

  Specifying a register set informs Watcom C/C++ that the registers belonging to the register
  set are modified by the function.  That is, the value in a register before calling the
  function is different from its value after execution of the function.

  Registers that are used to pass arguments are assumed to be modified and hence do not have to
  be saved and restored by the called function.  Also, since the AX register is frequently used
  to return a value, it is always assumed to be modified.  If necessary, the caller will
  contain code to save and restore the contents of registers used to pass arguments.  Note that
  saving and restoring the contents of these registers may not be necessary if the called
  function does not modify them.  The following form of the auxiliary pragma can be used to
  describe exactly those registers that will be modified by the called function.

    #pragma aux <sym> modify exact <reg_set>[;]

  where sym is a function name and reg_set is a register set.

  The above form of the auxiliary pragma tells Watcom C/C++ not to assume that the registers
  used to pass arguments will be modified by the called function.  Instead, only the registers
  specified in the register set will be modified.  This will prevent generation of the code
  which unnecessarily saves and restores the contents of the registers used to pass arguments.

  Also, any registers that are specified in the value register set are assumed to be unmodified
  unless explicitly listed in the exact register set.  In the following example, the code
  generator will not generate code to save and restore the value of the stack pointer register
  since we have told it that"GetSP" does not modify any register whatsoever.

  Example:

    unsigned GetSP(void);
    #if defined(__386__)
    #pragma aux GetSP = value [esp] modify exact [];
    #else
    #pragma aux GetSP = value [sp] modify exact [];
    #endif

  As mentioned in an earlier section, the following pragma defines the calling convention for
  functions compiled by Microsoft C.

    #pragma aux MS_C "_*"                                                                     \
                     parm caller []                                                           \
                     value struct float struct routine [ax]                                   \
                     modify [ax bx cx dx es];

  Let us discuss this pragma in detail.

  "_*"

    specifies that all function and variable names are preceded by the underscore character (_)
    when translated from source form to object form.

  parm caller []

    specifies that all arguments are to be passed on the stack (an empty register set was
    specified) and the caller will remove the arguments from the stack.

  value struct

    marks the section describing how the called routine returns structure information.

  float

    specifies that floating-point arguments are returned in the same way as structures are
    returned.

  struct

    specifies that 1, 2 and 4-byte structures are not to be returned in registers.

  routine

    specifies that the called routine allocates storage for the return structure and returns
    with a register pointing at it.

  [ax]

    specifies that register AX is used to point to the structure return value.

  modify [ax bx cx dx es]

    specifies that registers AX, BX, CX, DX and ES are not preserved by the called routine.

  Note that the default method of returning integer values is used; 1-byte characters are
  returned in register AL, 2-byte integers are returned in register AX, and 4-byte integers are
  returned in the register pair DX:AX.

  This section deals with those aspects of auxiliary pragmas that are specific to the 80x87.
  The discussion in this chapter assumes that one of the "fpi" or "fpi87" options is used to
  compile functions.  The following areas are affected by the use of these options.

  1.  passing floating-point arguments to functions,

  2.  returning floating-point values from functions and

  3.  which 80x87 floating-point registers are allowed to be modified by the called routine.

  By default, floating-point arguments are passed on the 80x86 stack.  The 80x86 registers are
  never used to pass floating-point arguments when a function is compiled with the "fpi" or
  "fpi87" option.  However, they can be used to pass arguments whose type is not floating-point
  such as arguments of type "int".

  The following form of the auxiliary pragma can be used to describe the registers that are to
  be used to pass arguments to functions.

    #pragma aux <sym> parm <reg_set>[;]

  where sym is a function name and reg_set is a register set.  The register set can contain
  80x86 registers and/or the string "8087".

  Notes:

  1.  If an empty register set is specified, all arguments, including floating-point arguments,
      will be passed on the 80x86 stack.

  When the string "8087" appears in a register set, it simply means that floating-point
  arguments can be passed in 80x87 floating-point registers if the source file is compiled with
  the "fpi" or "fpi87" option.  Before discussing argument passing in detail, some general
  notes on the use of the 80x87 floating-point registers are given.

  The 80x87 contains 8 floating-point registers which essentially form a stack.  The stack
  pointer is called ST and is a number between 0 and 7 identifying which 80x87 floating-point
  register is at the top of the stack.  ST is initially 0.  80x87 instructions reference these
  registers by specifying a floating-point register number.  This number is then added to the
  current value of ST.  The sum (taken modulo 8) specifies the 80x87 floating-point register to
  be used.  The notation ST(n), where "n" is between 0 and 7, is used to refer to the position
  of an 80x87 floating-point register relative to ST.

  When a floating-point value is loaded onto the 80x87 floating-point register stack, ST is
  decremented (modulo 8), and the value is loaded into ST(0). When a floating-point value is
  stored and popped from the 80x87 floating-point register stack, ST is incremented (modulo 8)
  and ST(1) becomes ST(0).  The following illustrates the use of the 80x87 floating-point
  registers as a stack, assuming that the value of ST is 4 (4 values have been loaded onto the
  80x87 floating-point register stack).

                +----------------+
          0     | 4th from top   |  ST(4)
                +----------------+
	  1     | 5th from top   |  ST(5)
                +----------------+
          2     | 6th from top   |  ST(6)
                +----------------+
          3     | 7th from top   |  ST(7)
                +----------------+
    ST -> 4     | top of stack   |  ST(0)
                +----------------+
          5     | 1st from top   |  ST(1)
                +----------------+
          6     | 2nd from top   |  ST(2)
                +----------------+
	  7     | 3rd from top   |  ST(3)
                +----------------+

  Starting with version 9.5, the Watcom compilers use all eight of the 80x87 registers as a
  stack.  The initial state of the 80x87 register stack is empty before a program begins
  execution.

  Note:

    For compatibility with code compiled with version 9.0 and earlier, you can compile with the
    "fpr" option.  In this case only four of the eight 80x87 registers are used as a stack.
    These four registers were used to pass arguments.  The other four registers form what was
    called the 80x87 cache. The cache was used for local floating-point variables.  The state
    of the 80x87 registers before a program began execution was as follows.

      1.  The four 80x87 floating-point registers that form the stack are uninitialized.

      2.  The four 80x87 floating-point registers that form the 80x87 cache are initialized
          with zero.

    Hence, initially the 80x87 cache was comprised of ST(0), ST(1), ST(2) and ST(3).  ST had
    the value 4 as in the above diagram.  When a floating-point value was pushed on the stack
    (as is the case when passing floating-point arguments), it became ST(0) and the 80x87 cache
    was comprised of ST(1), ST(2), ST(3) and ST(4).  When the 80x87 stack was full, ST(0),
    ST(1), ST(2) and ST(3) formed the stack and ST(4), ST(5), ST(6) and ST(7) formed the 80x87
    cache.  Version 9.5 and later no longer use this strategy. The rules for passing arguments
    are as follows.

    1.  If the argument is not floating-point, use the procedure described earlier in this
        chapter.

    2.  If the argument is floating-point, and a previous argument has been assigned a position
        on the 80x86 stack (instead of the 80x87 stack), the floating-point argument is also
        assigned a position on the 80x86 stack. Otherwise proceed to the next step.

    3.  If the string "8087" appears in a register set in the pragma, and if the 80x87 stack is
        not full, the floating-point argument is assigned floating-point register ST(0) (the
        top element of the 80x87 stack).  The previous top element (if there was one) is now in
        ST(1).  Since arguments are pushed on the stack from right to left, the leftmost
        floating-point argument will be in ST(0).  Otherwise the floating-point argument is
        assigned a position on the 80x86 stack.

  Consider the following example.

    #pragma aux myrtn parm [8087];

    void main()
    {
        float    x;
        double   y;
        int      i;
        long int j;

        x = 7.7;
        i = 7;
        y = 77.77;
        j = 77;
        myrtn( x, i, y, j );
    }

  myrtn is an assembly language function that requires four arguments.  The first argument of
  type float (4 bytes), the second argument is of type int (2 bytes), the third argument is of
  type double (8 bytes) and the fourth argument is of type long int (4 bytes).  These arguments
  will be passed to myrtn in the following way.

  1.  Since "8087" was specified in the register set, the first argument, being of type float,
      will be passed in an 80x87 floating-point register.

  2.  The second argument will be passed on the stack since no 80x86 registers were specified
      in the register set.

  3.  The third argument will also be passed on the stack.  Remember the following rule:  once
      an argument is assigned a position on the stack, all remaining arguments will be assigned
      a position on the stack.  Note that the above rule holds even though there are some 80x87
      floating-point registers available for passing floating-point arguments.

  4.  The fourth argument will also be passed on the stack.

  Let us change the auxiliary pragma in the above example as follows.

    #pragma aux myrtn parm [ax 8087];

  The arguments will now be passed to myrtn in the following way.

  1.  Since "8087" was specified in the register set, the first argument, being of type float
      will be passed in an 80x87 floating-point register.

  2.  The second argument will be passed in register AX, exhausting the set of available 80x86
      registers for argument passing.

  3.  The third argument, being of type double, will also be passed in an 80x87 floating-point
      register.

  4.  The fourth argument will be passed on the stack since no 80x86 registers remain in the
      register set.

  The following form of the auxiliary pragma can be used to describe a function that returns a
  floating-point value in ST(0).

    #pragma aux <sym> value <reg_set>[;]

  where sym is a function name and reg_set is a register set containing the string "8087" (i.e.
  [8087]).

  The code generator assumes that all eight 80x87 floating-point registers are available for
  use within a function unless the "fpr" option is used to generate backward compatible code
  (older Watcom compilers used four registers as a cache).  The following form of the auxiliary
  pragma specifies that the floating-point registers in the 80x87 cache may be modified by the
  specified function.

    #pragma aux <sym> modify <reg_set>[;]

  where sym is a function name and reg_set is a register set containing the string "8087" (i.e.
  [8087]).

  This instructs Watcom C/C++ to save any local variables that are located in the 80x87 cache
  before calling the specified routine.

*/

#ifndef COMPILER_WATCOM_H

  // Class/structure member packing

  #define PF_PACKING_RESET                             pack ()
  #define PF_PACKING_SET(numBytes)                     pack (numBytes)
  #define PF_PACKING_POP                               pack (pop)
  #define PF_PACKING_PUSH                              pack (push)

  // Intrinsic routine/function control

  #define PF_DECLARE_ROUTINE_INTRINSIC(routine)        intrinsic (routine)
  #define PF_DECLARE_ROUTINE_NON_INTRINSIC(routine)    function (routine)

  // Recursive inline expansion control

  #define PF_INLINE_EXPANSION_DEPTH_SET(depth)         inline_depth depth
  #define PF_INLINE_EXPANSION_RECURSION_OFF            inline_recursion off
  #define PF_INLINE_EXPANSION_RECURSION_ON             inline_recursion on

  // Enumeration type control

  #define PF_ENUM_TYPE_RESET                           enum original
  #define PF_ENUM_TYPE_PUSH_AND_SET_INT                enum int
  #define PF_ENUM_TYPE_PUSH_AND_SET_MINIMAL            enum minimum
  #define PF_ENUM_TYPE_POP                             enum pop

  // Static data initialization control

  #define PF_STATIC_DATA_INITIALIZE_PRIORITY(priority) initialize priority
  #define PF_STATIC_DATA_INITIALIZE_PRIORITY_LIBRARY   initialize library
  #define PF_STATIC_DATA_INITIALIZE_PRIORITY_PROGRAM   initialize program

  // Stack monitoring control

  #define PF_STACK_CHECKING_OFF                        off (check_stack);
  #define PF_STACK_CHECKING_ON                         on (check_stack);

  // Compiler output

  #define PF_OUTPUT_ON_COMPILE(text)                   message (text)
  #define PF_OUTPUT_ON_COMPILE_CLASS                   dump_object_model class
  #define PF_OUTPUT_ON_COMPILE_ENUM                    dump_object_model enumeration
  #define PF_PUT_TEXT_IN_TARGET(target, text)          comment (target, #text)

  // Link control

  #define PF_LINK_WITH(file)                           library (file)

  // Miscellaneous

  #define PF_INCLUDE_ONCE_ONLY                         once
  #define PF_REUSE_DUPLICATE_STRINGS_OFF               off (reuse_duplicate_strings);
  #define PF_REUSE_DUPLICATE_STRINGS_ON                on (reuse_duplicate_strings);
  #define PF_TEMPLATE_RECURSIVE_EXPANSION_LIMIT(limit) template_depth n

#endif

// ============================================================================================
// GUARD MACRO DEFINITION
// ============================================================================================

#ifndef COMPILER_WATCOM_H
  #define COMPILER_WATCOM_H
#endif
