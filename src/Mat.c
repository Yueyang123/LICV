#include "Mat.h"

    void(*show)(Mat* mat);
    void (*destory)(Mat* mat); 
    void (*reshape)(Mat* mat, int rows); 
    u16* (*at)(Mat* mat,int x,int y,int Index);
    u16  (*type)(Mat* mat);


#ifdef WINDOWS




#endif 

