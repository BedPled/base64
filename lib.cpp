#include <iostream>
#include "lib.h"
#include <string>

using namespace std;

const string STRbase64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";



char getIndex(int a) {
    return STRbase64[a];
}

char getNumberSTRbase64 (char a) {
    for (int i = 0; i < STRbase64.length(); i++) {
        if ((int)STRbase64[i] == (int)a) {
            return i;
        }
    }
    return 0;
}

string threeToBase64 (char let1, char let2, char let3) {
    // 123456 78|1234 5678|12 345678
    string outBase64;
    char help = 0;
    char b1 = 48; //00110000
    char b2 = 15; //00001111
    char b3 = 63; //00111111

    // 1 символ base64
    help = let1;
    help = help >> 2;
    outBase64 +=  (char)getIndex(help);

    // 2 символ base64
    let1 = let1 << 4;                               // 56780000
    let1 = let1 & b1;                               // 00780000
    help = let2;                                    // 12345678
    help = help >> 4;                               // 00001234
    outBase64 += (char) getIndex(help | let1);    // 00781234

    if (let2 == 0) {
        outBase64 += "==";
        return outBase64;
    }


    // 3 символ base64
    let2 = let2 & b2;                               // 00005678
    let2 = let2 << 2;                               // 00567800
    help = let3;                                    // 12345678
    help = help >> 6;                               // 00000012
    outBase64 += (char) getIndex(help | let2);   // 00567812

    if (let3 == 0) {
        outBase64 += "=";
        return outBase64;
    }

    // 4 символ base64
    let3 = let3 & b3;
    outBase64 += (char)getIndex(let3);

    return outBase64;
}

string asciiToBase64 (string inStr) {
    string outStr = "";
    int countLetters = inStr.length();

    for (int i = 0; i < countLetters - countLetters % 3; i+=3) {
        outStr += threeToBase64(inStr[i], inStr[i + 1], inStr[i + 2]);
    }

    if (countLetters % 3 != 0) {
        int ch2, ch3;

        if (inStr[countLetters - countLetters % 3 + 1] == '\0') {
            ch2 = 0;
            ch3 = 0;
        } else if (inStr[countLetters - countLetters % 3 + 2] == '\0') {
            ch2 = inStr[countLetters - countLetters % 3 + 1];
            ch3 = 0;
        }

        outStr += threeToBase64(inStr[countLetters - countLetters % 3], ch2, ch3);
    }

    return outStr;
}

string fourToAscii (char let1, char let2, char let3, char let4) {
    // 123456 12|3456 1234|56 123456
    let1 =  getNumberSTRbase64(let1);
    let2 =  getNumberSTRbase64(let2);
    let3 =  getNumberSTRbase64(let3);
    let4 =  getNumberSTRbase64(let4);

    string outAscii = "";
    char help = 0;

    // 00****** 00**@@@@ 00@@@@++ 00++++++

    help = let2;                // 00**@@@@
    let1 = let1 << 2;           // ******00
    help = help >> 4;           // 000000**
    help = let1 | help;         // ********
    outAscii += help;


    let2 = let2 << 4;           // @@@@0000
    help = let3;                // 00@@@@++
    help = help >> 2;           // 0000@@@@
    help = let2 | help;         // @@@@@@@@

    if (help != 61) {
        outAscii += help;
    } else {
        return outAscii;
    }

    let3 = let3 << 6;           // ++000000
    help = let3 | let4;         // ++++++++

    if (help != 61) {
        outAscii += help;
    } else {
        return outAscii;
    }

    return outAscii;
}

string base64ToAscii (string inStr) {
    string outStr = "";
    int countLetters = inStr.length();

    if (countLetters % 4 != 0) {
        return "Ошибочная входная строка в кодировке Base64. Кол-во символов должно нацело делиться на 4";
    }

    for (int i = 0; i < countLetters - countLetters % 4; i+=4) {
        outStr += fourToAscii(inStr[i], inStr[i + 1], inStr[i + 2], inStr[i + 3]);
    }

    return outStr;
}