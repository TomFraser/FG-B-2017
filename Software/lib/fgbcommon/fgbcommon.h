#include <Arduino.h>

#ifndef fgbcommon_h
#define fgbcommon_h

#define SHIFTARRAY(arr, input){                                 \
    for(int q = sizeof(arr)/sizeof(arr[0]) - 1; q >= 0; q--){   \
        *(arr + q + 1) = *(arr + q);                            \
    }                                                           \
    *(arr + 0) = input;                                         \
}                                                               \



#endif
