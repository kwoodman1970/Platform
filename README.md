# Platform (C/C++) &ndash;  Macros for Platform-Independent Code
**Status:**  Inactive<br />
*This project is not being actively developed at this time but has not been abandoned either.*

## About This Project

In the late 1990's, as I was nearing the end of my days as a university student, I was keenly interested in multi-platform software development but dismayed by the diversity of compiler macros that each C/C++ compiler manufacturer used for even the simplest of things (like testing whether or not `<string.h>` had been included).  For example, Borland compilers' `limits.h` would define `__LIMITS_H` while Microsoft compilers' `limits.h` would define `LIMITS_H`.

This project's goal was to bring order to this chaos by implementing a common set of macros that would make multi-platform coding easier.  Instead of coding (for example):

```c
#if ((defined(__TURBOC__) && defined(__WIN32__)) || (defined(_MSC_VER) && defined(_WIN32)))

  // compile Windows-specific fragment

#else

  // compile non-Windows fragment

#endif
  ```

  it would be possible to code:

```c
#if (PF_OS == PF_WIN32)
  // compile Windows-specific fragment
#else
  // compile non-Windows fragment
#endif
```

In the context of Best Practices, it's best to keep platform-specific code together rather than in separate files because if debugging, maintenance or further development is required then the programmer is more likely to see all the relevant code fragments.  If they're in different places &ndash; or even in different files &ndash; then the risk of missing something increases.

## How to Install

Use the green `<> Code` button to either clone this repository or download the zip file.

To install, copy the contents of the `src/headers` directory to a directory for your compiler's 3<sup>rd</sup>-party standard header files.

Do **not** place these files in the same directories as the files that shipped with your compiler &ndash; always use a separate directory (or directories) for 3<sup>rd</sup>-party files.

Each compiler is different &ndash; refer to your compiler's manual for more information.

## How to Use

*All source files are fully documented &ndash; what follows is a summary.*

Generally speaking, in spite of Best Practices, place the following directive in your source files **after** all other `#include` directives:

```c
#include <platform.h>
```

### Macros

The following macros will now be available to you:

```
PF_COMPILER
PF_COMPILER_VER
PF_OS
PF_CPU
PF_STD_LIB_CALL
PF_MULTITHREADED
PF_DLL_IMPORT
PF_DLL_EXPORT
PF_ENDIAN
SHRT_MAX
INT_MAX
LONG_MAX
```

A number of `#pragma` directive macros *may* be available to you (depending on the compiler):

- Precompiled headers control
- Class/structure member packing
- Intrinsic routine/function control
- Recursive inline expansion control
- Enumeration type control
- Static data initialization control
- Class compilation control
- Stack monitoring control
- Compiler output
- Link control
- Browse information gathering control

Additionally, guard macros for the headers that ship with the compiler will all be of the form `[DIR_]NAME_H`.

### Emulate a Missing `bool` Data Type

If you're using an older C++ compiler that doesn't have a built-in `bool` data type then compile the `src/code/bool.cpp` into either an object file or a library file and link it into your project.  It's superior to using enumerations or macros in several ways.

If you're using an older C compiler then you can code your own `<stdbool.h>` header file &ndash; see [opengroup.org](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdbool.h.html) for a good guideline.

### Example

Compile and link `src/example/testplat.cpp` into a command-line executable and run it.  It will output information about the system and the conditions under which it was compiled.

## TODO

- Update existing compilers' macros
- Support more compilers
- Document `src/example/testplat.cpp`
- Create proper documentation (possibly using [Sphinx](https://www.sphinx-doc.org/)) instead of simply saying, "Look at the source files"
- Create a `stdbool.h` file for older C compilers so that programmers don't have to code their own

## How to Contribute

If you'd like to update any of the files in this repository or contribute new ones then please fork this repository and create a pull request.
