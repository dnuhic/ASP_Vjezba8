#include <iostream>
#include "BinarnoStablo/BinStabloMapa.h"

int main() {
    int kljucevi[] = {6, 4, 3, 0, 0, 5, 0, 0, 0};
    int vrijednost[] = {6, 4, 3, 0, 0, 5, 0, 0, 0};
    BinStabloMapa<int, int> m(kljucevi, vrijednost, 9);
    std::cout << m.vrh->element.kljuc;
//    m[1] = 1;
//    m[3] = 3;
//    m[2] = 2;
//    m[4] = 4;
//    m[5] = 5;
//    m[60] = 60;
//    m[90] = 90;
//    m[30] = 30;
//    m[80] = 80;
//    m[234] = 234;
//    m[345] = 345;
//    m[78] = 78;
//    m[85] = 85;
//    m[76] = 76;
//    m[23] = 23;
//    m[7] = 7;
//    m[28] = 28;
//    m[1] = 1;
//    m[57] = 57;
//    m[42] = 42;
//    m[58] = 58;
//    std::vector<int> v = m.od_do(1, 10);
//    for(int x : v)
//        std::cout << x << " ";
    return 0;
}
