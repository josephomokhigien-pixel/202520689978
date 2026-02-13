#ifndef MATHSLIBADDERH
#define MATHSLIBADDERH

#if defined(_WIN32)
  #ifdef mathsSTATIC
    #define MATHSLIBAPI
  #else
    #ifdef mathsEXPORTS
      #define MATHSLIBAPI __declspec(dllexport)
    #else
      #define MATHSLIBAPI __declspec(dllimport)
    #endif
  #endif
#else
  #define MATHSLIBAPI
#endif

MATHSLIBAPI int add(int a, int b);

#endif
