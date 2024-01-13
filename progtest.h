#ifndef PROGTEST_H
#define PROGTEST_H

#include "cdate.h"

namespace ProgTest {
    namespace Menu {
        const void pressAnyKeyToContinue();
        const int choiceAndError(int min, int max);
        bool restartOrExist();
    }

    namespace CDateTest {
        const void dateFormatChoice(char numSep = '-', bool m = true, bool a = true, bool c = true);
        const void dateFormatPrint(std::string message, CDate date, CDate::FORMAT format, bool clear = true);
        int mainMenu();
        void currentTIme();
        CDate::TYPE_PERIODE choicePeriode();
        int getNbPeriode(CDate::TYPE_PERIODE periode);
        void addPeriode();
        void diffBetweenTwoDates();
        void compareTwoDate();
        void formatDate();
        void isLeapYear();
        int progTest();
    }
}

#endif // PROGTEST_H
