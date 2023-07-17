#ifndef PLATFORM_BOOL_H
#define PLATFORM_BOOL_H

// ============================================================================================
//
// bool.h -- "bool" Class for Older C++ Compilers
//
// ============================================================================================

#ifndef PF_BOOL_NOT_BUILT_IN
  #error "bool" may be a built-in type for this compiler -- check your manual!
#endif

// ============================================================================================
// INCLUDE FILES
// ============================================================================================

#include <assert.h>

// ============================================================================================
// CLASS DEFINITION
// ============================================================================================

class bool
{
  public:
    bool(const int = 0);
    bool(const bool&);

    bool& operator=(const int source)                               // assign-from-int operator
    {
      assert((_value == _false) || (_value == _true));

      _value = (source ? _true : _false);
      return *this;
    }

    bool& operator=(const bool& source)                            // assign-from-bool operator
    {
      assert((_value == _false) || (_value == _true));
      assert((source._value == _false) || (source._value == _true));

      _value = source._value;
      return *this;
    }

    operator const int() const                                       // convert-to-int operator
    {
      assert((_value == _false) || (_value == _true));

      return (int)_value;
    }

  private:
    static const char _false;                // the character representation of Boolean false
    static const char _true;                 // the character representation of Boolean true

    char _value;                             // the character representation of a Boolean value
};

// ============================================================================================
// STATIC CONSTANT DECLARATIONS
// ============================================================================================

/*
Ideally, these would be defined in "bool.cpp", but Borland C++ 2.0 for OS/2 wasn't initializing
them properly in the resulting library.
*/

static const bool false(0);                                       // 0 represents Boolean false
static const bool true(1);                                        // 1 represents Boolean true

#endif

// ============================================================================================
// STREAM SHIFT-IN DECLARATION
// ============================================================================================

#if !defined(PLATFORM_BOOL_H_ISTREAM) && (defined(IOSTREAM_H) || defined(IOSTREAM))
  #define PLATFORM_BOOL_H_ISTREAM

  istream& operator>>(istream&, bool&);

#endif