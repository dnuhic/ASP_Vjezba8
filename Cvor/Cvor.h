//
// Created by dzena on 26/01/2021.
//

#ifndef ASP_VJEZBA8_CVOR_H
#define ASP_VJEZBA8_CVOR_H

#include "../Par/Par.h"

template <typename TipKljuca, typename TipVrijednosti>
struct Cvor {
    Par<TipKljuca, TipVrijednosti> element;
    Cvor *leftChild, *rightChild, *parent;
};


#endif //ASP_VJEZBA8_CVOR_H
