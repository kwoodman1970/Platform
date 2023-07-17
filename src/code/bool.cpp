// ============================================================================================
//
// bool.cpp -- "bool" Class for Older C++ Compilers
//
// ============================================================================================

/*
This source file defines a "bool" class for older C++ compilers that don't have built-in "bool"
types.  Its advantage over "typdef char bool" is that it can only hold two values: false or
true.  It's advantage over "typedef enum {false, true} bool" is that it's guarenteed to be one
char in size, whereas an enumeration may be the size of an int (this can be an issue with
different packing alignments or with block reads from & writes to streams).

Two global static constants are also defined here -- "false" and "true".
*/

// ============================================================================================
// DESIGN NOTES
// ============================================================================================

/*
C++ compilers that don't have "bool" built-in use "int" types to handle all Boolean
expressions.  The "bool" class therefore converts to and from "int" types exclusively.

Most of the methods and functions are simple enough to be defined inline, making for the
fastest executable code possible (fast executable code is often a goal in emulators).

If the user includes one of the "iostream" header files before the "bool.h" header file then
a shift-in operator is declared for the "bool" class (an explicit shift-out operator isn't
necessary).  It's not automatically declared because the user may not want to use iostreams,
and it's very bad manners to force the user to use "<iostream.h>" when "<iostream>" is prefered
(mind you, if the compiler is too old to have a built-in "bool" type then it's probably too old
to have an "<iostream>" header as well!).
*/

// ============================================================================================
// INCLUDE FILES
// ============================================================================================

#include <assert.h>
#include <iostream.h>

#include "platform.h"

#ifndef PF_BOOL_NOT_BUILT_IN
  #error "bool" may be a built-in type for this compiler -- check your manual!
#endif

// ============================================================================================
// STATIC MEMBER DEFINITIONS
// ============================================================================================

const char bool::_false = '\000';                                 // 0 represents Boolean false
const char bool::_true  = '\001';                                 // 1 represents Boolean true

// ============================================================================================
// METHOD DEFINITIONS
// ============================================================================================

/*********************************************************************************************/

bool::bool
(
  const int initialValue                               // the initial value for the bool object
):

/*
This is a default/copy constructor.  It accepts an integer as an argument because that's what
"bool"-challenged C++ compilers use when evaluating logic expressions.

Borland C++ 3.0 for DOS is a bit quirky in that it won't compile inline constructor bodies.
Therefore, this constructor has been defined out-of-line instead.

PRECONDITIONS:
None.

POSTCONDITIONS:
If "initialValue" is "0" (default) then the object is initialized to Boolean false; otherwise,
it's initialized to Boolean true.  This is consistent with standard integer-based C/C++ Boolean
logic.
*/

  _value(initialValue ? _true : _false)

{
  return;
}

/*********************************************************************************************/

bool::bool
(
  const bool& initialValue                             // the initial value for the bool object
):

/*
This is a copy constructor.

Borland C++ 3.0 for DOS is a bit quirky in that it won't compile inline constructor bodies.
Therefore, this constructor has been defined out-of-line instead.

PRECONDITIONS:
None.

POSTCONDITIONS:
The object is initialized to the same Boolean value as "initialValue".
*/

  _value(initialValue._value)

{
  assert((_value == _false) || (_value == _true));

  return;
}

// ============================================================================================
// STREAM SHIFT-IN FUNCTION DEFINTION
// ============================================================================================

/*********************************************************************************************/

istream& operator>>
(
  istream& source,                               // the stream to get the Boolean value from
  bool&    target                                // the variable to store that Boolean value in
)

/*
This function reads Boolean values (represented by the integers "0" and "1") from "source".

NOTE:  The corresponding declaration in the header file is wrapped in conditional macros.  The
practical effect is that this function is compiled but only linked if necessary.

PRECONDITIONS:
None.

POSTCONDITIONS:
If anything other than "0" or "1" was shifted in from "source" then "source" will be set to a
bad state.  Otherwise, barring I/O errors, "target" will hold the Boolean value that was
shifted in.
*/

{
  if (source.good())
  {
    int integerValue;           // temporary holder for an integer value shifted in from source

    source >> integerValue;

    if (source.good())
    {
      if ((integerValue == 0) || (integerValue == 1))
        target = integerValue;
      else
        source.clear(ios::badbit);
    }
  }

  return source;
}
