#ifndef BASEDEF_H
#define BASEDEF_H

#include <wtypes.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define PROCESS_ERROR(condition) do \
    { \
        if(!(condition)) { \
            cout<<"ERROR! "<<__FUNCTION__<<" in "<<__FILE__<<":("<<__LINE__<<")"<<endl; \
            goto Exit0; \
        } \
    }while(false); \

#endif // BASEDEF_H
