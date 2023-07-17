#include <iostream.h>
#ifdef FAT_FILENAMES
  #include <strstrea.h>
#else
  #include <strstream.h>
#endif
#include <assert.h>

#include <platform.h>

#define NUM_ENDIAN_TYPES 3

typedef struct
{
  int         value;
  const char* textualRepresentation;
}
ValueTextPair;

static const char *const lookup(const ValueTextPair *const, const int, const int);

int main()
{
  const ValueTextPair compilers[PF_NUMCOMPILERTYPES] =
		      {
			{PF_UNKNOWN_COMPILER, "Unknown"},
			{PF_BORLAND,          "Borland"},
			{PF_GNU,              "Gnu"},
			{PF_MICROSOFT,        "Microsoft"},
			{PF_WATCOM,           "Watcom"},
			{PF_DEC,              "DEC"}
		      };

  const ValueTextPair osApis[PF_NUMOSTYPES] =
                      {
                        {PF_UNKNOWN_OS, "Unknown"},
                        {PF_DOS,        "DOS"},
                        {PF_MACOS,      "MAC OS"},
                        {PF_NETWARE386, "Novell Netware 386"},
                        {PF_OS2,        "OS/2"},
                        {PF_QNX,        "QNX"},
                        {PF_WIN16,      "16-bit Windows"},
                        {PF_WIN32,      "32-bit Windows"},
                        {PF_UNIX,       "Unix"},
                        {PF_VMS,        "VMS"}
                       };

  const ValueTextPair cpus[PF_NUMCPUTYPES] =
                      {
                        {PF_UNKNOWN_CPU,    "Unknown"},
                        {PF_AMD_29000,      "AMD 29000"},
                        {PF_DEC_ALPHA,      "DEC Alpha"},
                        {PF_DEC_VAX,        "DEC VAX"},
                        {PF_IBM_POWERPC,    "IBM PowerPC"},
                        {PF_INTEL_X86,      "Intel x86 or compatible"},
                        {PF_MIPS,           "MIPS"},
                        {PF_MOTOROLA_68X00, "Motorola 68x00 series"},
                        {PF_NS_32000,       "National Semiconductor 32000"}
                      };

  const ValueTextPair endians[NUM_ENDIAN_TYPES] =
                      {
                        {PF_ENDIAN_UNKNOWN, "Unknown"},
                        {PF_ENDIAN_LITTLE,  "Little (least "},
                        {PF_ENDIAN_BIG,     "Big (most "}
                      };

  cout << "Compiler:          " << lookup(compilers, PF_NUMCOMPILERTYPES, PF_COMPILER) << endl;
  cout << "Compiler version:  " << hex << PF_COMPILER_VER << dec << endl;
  cout << "OS API:            " << lookup(osApis, PF_NUMOSTYPES, PF_OS) << endl;
  cout << "CPU:               " << lookup(cpus, PF_NUMCPUTYPES, PF_CPU) << endl;
  cout << "CPU endian:        " << lookup(endians, NUM_ENDIAN_TYPES, PF_ENDIAN) <<
                                     "significant bytes come first)" << endl;
  cout << "Multithreaded:     " << (PF_MULTITHREADED ? "Yes" : "No") << endl;

  cout << endl;

  #ifdef IOSTREAM_H
    cout << "iostream.h was included (as expected)." << endl;
  #else
    cout << "iostream.h was not included (unexpected -- and how can you read this?)." << endl;
  #endif

  #ifdef ASSERT_H
    cout << "assert.h was included (as expected)." << endl;
  #else
    cout << "assert.h was not included (unexpected)." << endl;
  #endif

  #ifdef STDARG_H
    cout << "stdarg.h was included (unexpected)." << endl;
  #else
    cout << "stdarg.h was not included (as expected)." << endl;
  #endif

  cout << endl;

  #ifdef PF_PACKING_SMALLEST
    #pragma option -a-

    struct PackedSmallest
    {
      char     character;
      long int integer;
    };

    cout << "struct PackedSmallest occupies " << sizeof(PackedSmallest) << " chars." << endl;

    #pragma PF_PACKING_RESET
  #else
    cout << "No pack-smallest directive available on this platform." << endl;
  #endif

  #ifdef PF_PACKING_FASTEST
    #pragma PF_PACKING_FASTEST

    struct PackedFastest
    {
      char     character;
      long int integer;
    };

    cout << "struct PackedFastest occupies " << sizeof(PackedFastest) << " chars." << endl;

    #pragma PF_PACKING_RESET
  #else
    cout << "No pack-fastest directive available on this platform." << endl;
  #endif

  #ifdef PF_PACKING_SET
    #pragma PF_PACKING_SET(2)

    struct Packed2
    {
      char     character;
      long int integer;
    };

    cout << "struct Packed2 occupies " << sizeof(Packed2) << " chars." << endl;

    #pragma PF_PACKING_SET(4)

    struct Packed4
    {
      char     character;
      long int integer;
    };

    cout << "struct Packed4 occupies " << sizeof(Packed4) << " chars." << endl;

    #pragma PF_PACKING_SET(8)

    struct Packed8
    {
      char     character;
      long int integer;
    };

    cout << "struct Packed8 occupies " << sizeof(Packed8) << " chars." << endl;

    #pragma PF_PACKING_RESET
  #else
    cout << "No pack-specific-alignment directive available on this platform." << endl;
  #endif

  cout << endl;

  #ifdef PLATFORM_BOOL_H
    cout << "\"bool\" is being simulated by a class." << endl;
  #else
    cout << "\"bool\" is a built-in type." << endl;
  #endif

  cout << "The size of \"bool\" is " << sizeof(bool) << "." << endl;
  cout << "The value of false is " << false << "; the value of true is " << true << "." <<
    endl;

  istrstream falseValue("0 ");
  istrstream trueValue("1 ");
  istrstream invalidValue("2 ");
  bool       boolTest;

  falseValue >> boolTest;
  assert(falseValue.good());
  cout << "0 was shifted into a bool as " << (boolTest ? "true" : "false");
  trueValue >> boolTest;
  assert(trueValue.good());
  cout << "; 1 was shifted into a bool as " << (boolTest ? "true." : "false.") << endl;
  invalidValue >> boolTest;
  if (invalidValue.good())
    cout << "2 was shifted into a bool as " << (boolTest ? "true." : "false.") << endl;
  else
    cout << "2 couldn't be shifted into a bool." << endl;

  return 0;
}

/**********************************************************************************************/

static const char *const lookup
(
  const ValueTextPair *const table,
  const int                  numTableEntries,
  const int                  valueToFind
)

{
  assert((table != NULL) == (numTableEntries > 0));

  const char* textFound = "";

  if (numTableEntries > 0)
  {
    int index = 0;

    while ((index < numTableEntries) && (table[index].value != valueToFind))
      index++;

    if (index < numTableEntries)
      textFound = table[index].textualRepresentation;
  }

  return textFound;
}