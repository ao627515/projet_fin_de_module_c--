// #include <iostream>
#include "cdate.h"

// using namespace std;

int main()
{
    CDate d1;
    d1.displayDate(); // -> 1/1/1970 v

    CDate d2(14,7,2003);
    d2.displayDate(); // -> 14/7/2003 v

    CDate d3(14,7) ;
    d3.displayDate(); // -> 14/7/2023 v

    CDate d4(14);
    d4.displayDate(); // -> 14/12/2023 v

    CDate d5(0);
    d5.displayDate(); // -> 30/12/2023 v

    CDate d6(d2);
    d6.displayDate();

    CDate d7 = d1;
    d7.displayDate();

    return 0;
}
