//
// Created by dzena on 26/01/2021.
//

#ifndef ASP_VJEZBA8_BINSTABLOMAPA_H
#define ASP_VJEZBA8_BINSTABLOMAPA_H


#include <iostream>
#include <stdexcept>
#include "../Mapa/Mapa.h"
#include "../Cvor/Cvor.h"
#include <vector>

template <typename TipKljuca, typename TipVrijednosti>
class BinStabloMapa : public Mapa<TipKljuca, TipVrijednosti> {
    int brEl;
    Cvor<TipKljuca, TipVrijednosti> *dajLokacijuUStablu(TipKljuca index) const;
    void postOrderBrisanje(Cvor<TipKljuca, TipVrijednosti> *parent);
    bool LijeviIliDesni(Cvor<TipKljuca, TipVrijednosti> *parent, Cvor<TipKljuca, TipVrijednosti> *trenutni) const;
    void preOrderKopiranje(Cvor<TipKljuca, TipVrijednosti> *parent);
public:
    Cvor<TipKljuca, TipVrijednosti> *vrh;
    BinStabloMapa(TipKljuca *nizKjuceva, TipVrijednosti *nizVrijednosti, int vel);
    BinStabloMapa() : vrh(nullptr), brEl(0) {}
    ~BinStabloMapa() override;
    BinStabloMapa(const BinStabloMapa &m);
    BinStabloMapa &operator =(const BinStabloMapa &m);
    TipVrijednosti operator[](TipKljuca index) const override;
    TipVrijednosti &operator[](TipKljuca index) override;
    int brojElemenata() const override;
    void obrisi() override;
    void obrisi(const TipKljuca &k) override;
    bool operator<(const BinStabloMapa &rhs) const;
    bool operator>(const BinStabloMapa &rhs) const;
    template <typename TipKljuc, typename TipVrijednost>
    TipVrijednosti prviManji(const TipKljuc& kljuc);
//    void ispisi() const {
//        postOrder(vrh);
//        std::cout << std::endl;
//        inOrder(vrh);
//        std::cout << std::endl;
//        preOrder(vrh);
//    }
//    void postOrder(Cvor<TipKljuca, TipVrijednosti> *par) const {
//        if(!par) return;
//        postOrder(par->leftChild);
//        postOrder(par->rightChild);
//        std::cout << par->element.kljuc << " ";
//    }
    void reverseInOrder(Cvor<TipKljuca, TipVrijednosti> *par, const TipKljuca& a, const TipKljuca& b, std::vector<TipVrijednosti> &v) const {
        if(!par) return;
        if(b < par->element.kljuc) return;
        reverseInOrder(par->rightChild, a, b, v);
        if(a > par->element.kljuc) return;
        v.push_back(par->element.vrijednost);
        reverseInOrder(par->leftChild, a, b, v);
    }
    void preOrderKreiranje(Cvor<TipKljuca, TipVrijednosti> *par, TipKljuca *nizKjuceva, TipVrijednosti *nizVrijednosti, int *i, Cvor<TipKljuca, TipVrijednosti> *roditelj, int vel, bool desni) {\
        std::cout << "epic";
        if(*i == vel) return;
        bool nastavi = true;
        if(nizKjuceva[*i] != 0) {
            par = new Cvor<TipKljuca, TipVrijednosti>{{nizKjuceva[*i], nizVrijednosti[*i]}, nullptr, nullptr, roditelj};
            brEl++;
            if(*i != 0)
                if(desni) roditelj->rightChild = par;
                else roditelj->leftChild = par;
        } else {
            (*i)++;
            nastavi = false;
        }
        if(nastavi)
            preOrderKreiranje(par->leftChild, nizKjuceva, nizVrijednosti, i, par, vel, false);
        else return;
        if(nastavi)
            preOrderKreiranje(par->rightChild, nizKjuceva, nizVrijednosti, i, par, vel, true);
        else return;
        //ne radi
    }
    std::vector<TipVrijednosti> od_do(const TipKljuca& a, const TipKljuca& b) {
        std::vector<TipVrijednosti> v;
        reverseInOrder(vrh, a, b, v);
        return v;
    }


};

template<typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca, TipVrijednosti>::~BinStabloMapa() {
    postOrderBrisanje(vrh);
}

template<typename TipKljuca, typename TipVrijednosti>
TipVrijednosti BinStabloMapa<TipKljuca, TipVrijednosti>::operator[](TipKljuca index) const {
    Cvor<TipKljuca, TipVrijednosti> *temp = dajLokacijuUStablu(index);
    if(temp == nullptr) return TipVrijednosti();
    return temp->element.vrijednost;
}

template<typename TipKljuca, typename TipVrijednosti>
TipVrijednosti &BinStabloMapa<TipKljuca, TipVrijednosti>::operator[](TipKljuca index) {
    if(brEl == 0) {
        vrh = new Cvor<TipKljuca, TipVrijednosti>{{index, TipVrijednosti()}, nullptr, nullptr, nullptr};
        brEl++;
        return vrh->element.vrijednost;
    }
    Cvor<TipKljuca, TipVrijednosti> *temp = dajLokacijuUStablu(index);
    if(!temp) {
        temp = vrh;
        while(true) {
            if(index > temp->element.kljuc) {
                if(!temp->rightChild) {
                    temp->rightChild = new Cvor<TipKljuca, TipVrijednosti>{{index, TipVrijednosti()}, nullptr, nullptr, temp};
                    temp = temp->rightChild;
                    break;
                }
                temp = temp->rightChild;
            }
            else {
                if(!temp->leftChild) {
                    temp->leftChild = new Cvor<TipKljuca, TipVrijednosti>{{index, TipVrijednosti()}, nullptr, nullptr, temp};
                    temp = temp->leftChild;
                    break;
                }
                temp = temp->leftChild;
            }
        }
        brEl++;
    }
    return temp->element.vrijednost;
}

template<typename TipKljuca, typename TipVrijednosti>
int BinStabloMapa<TipKljuca, TipVrijednosti>::brojElemenata() const {
    return brEl;
}

template<typename TipKljuca, typename TipVrijednosti>
void BinStabloMapa<TipKljuca, TipVrijednosti>::obrisi() {
    postOrderBrisanje(vrh);
    vrh = nullptr;
    brEl = 0;
}

template<typename TipKljuca, typename TipVrijednosti>
void BinStabloMapa<TipKljuca, TipVrijednosti>::postOrderBrisanje(Cvor<TipKljuca, TipVrijednosti> *parent) {
    if(!parent) return;
    postOrderBrisanje(parent->leftChild);
    postOrderBrisanje(parent->rightChild);
    delete parent;
}

template<typename TipKljuca, typename TipVrijednosti>
void BinStabloMapa<TipKljuca, TipVrijednosti>::obrisi(const TipKljuca &k) {
    if(brEl == 1) {
        delete vrh, vrh = nullptr, brEl--;
        return;
    }
    Cvor<TipKljuca, TipVrijednosti> *temp = dajLokacijuUStablu(k);
    if(!temp)
        throw std::domain_error("Ne postoji vrijednost sa tim kljucem");
    if(!temp->rightChild && !temp->leftChild) {
        if(LijeviIliDesni(temp->parent, temp))
            temp->parent->rightChild = nullptr;
        else
            temp->parent->leftChild = nullptr;
        delete temp;
    }
    else if(!temp->rightChild) {
        if(temp == vrh) {
            auto pom = vrh;
            vrh = temp->leftChild;
            vrh->parent = nullptr;
            brEl--;
            delete pom;
            return;
        }
        if(LijeviIliDesni(temp->parent, temp))
            temp->parent->rightChild = temp->leftChild;
        else
            temp->parent->leftChild = temp->leftChild;
        temp->leftChild->parent = temp->parent;
        delete temp;
    }
    else if(!temp->leftChild) {
        if(temp == vrh) {
            auto pom = vrh;
            vrh = temp->rightChild;
            vrh->parent = nullptr;
            brEl--;
            delete pom;
            return;
        }
        if(LijeviIliDesni(temp->parent, temp))
            temp->parent->rightChild = temp->rightChild;
        else
            temp->parent->leftChild = temp->rightChild;
        temp->rightChild->parent = temp->parent;
        delete temp;
    }
    else {
        Cvor<TipKljuca, TipVrijednosti> *sljedeciPoVelicni = temp->rightChild;
        while(sljedeciPoVelicni->leftChild)
            sljedeciPoVelicni = sljedeciPoVelicni->leftChild;
        TipKljuca pom1 = sljedeciPoVelicni->element.kljuc;
        TipVrijednosti pom2 = sljedeciPoVelicni->element.vrijednost;
        obrisi(sljedeciPoVelicni->element.kljuc);
        brEl++;
        temp->element.kljuc = pom1;
        temp->element.vrijednost = pom2;
    }
    brEl--;
}

template<typename TipKljuca, typename TipVrijednosti>
Cvor<TipKljuca, TipVrijednosti> *BinStabloMapa<TipKljuca, TipVrijednosti>::dajLokacijuUStablu(TipKljuca index) const {
    Cvor<TipKljuca, TipVrijednosti> *temp = vrh;
    while(temp != nullptr) {
        if(index == temp->element.kljuc)
            break;
        else if(index > temp->element.kljuc)
            temp = temp->rightChild;
        else
            temp = temp->leftChild;
    }
    return temp;
}

template<typename TipKljuca, typename TipVrijednosti>
bool BinStabloMapa<TipKljuca, TipVrijednosti>::LijeviIliDesni(Cvor<TipKljuca, TipVrijednosti> *parent, Cvor<TipKljuca, TipVrijednosti> *trenutni) const {
    if(parent->rightChild && parent->rightChild == trenutni)
        return true;
    return false;
}

template<typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca, TipVrijednosti>::BinStabloMapa(const BinStabloMapa<TipKljuca, TipVrijednosti> &m) {
    brEl = 0;
    preOrderKopiranje(m.vrh);
}

template<typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca, TipVrijednosti> &BinStabloMapa<TipKljuca, TipVrijednosti>::operator =(const BinStabloMapa<TipKljuca, TipVrijednosti> &m) {
    if(this == &m) return *this;
    brEl = 0;
    postOrderBrisanje(vrh);
    preOrderKopiranje(m.vrh);
    return *this;
}

template<typename TipKljuca, typename TipVrijednosti>
void BinStabloMapa<TipKljuca, TipVrijednosti>::preOrderKopiranje(Cvor<TipKljuca, TipVrijednosti> *parent) {
    if(!parent) return;
    operator [](parent->element.kljuc) = parent->element.vrijednost;
    preOrderKopiranje(parent->leftChild);
    preOrderKopiranje(parent->rightChild);
}

template<typename TipKljuca, typename TipVrijednosti>
bool BinStabloMapa<TipKljuca, TipVrijednosti>::operator<(const BinStabloMapa &m) const {
    if(m.brEl == 0 || brEl == 0)
        throw std::domain_error("Jedno od stabala prazno");
    Cvor<TipKljuca, TipVrijednosti> *temp = m.vrh;
    while(temp->leftChild) {
        temp = temp->leftChild;
    }
    TipKljuca min = temp->element.kljuc;
    Cvor<TipKljuca, TipVrijednosti> *temp2 = vrh;
    while(temp2->rightChild) {
        if(temp2->element.kljuc > min) return false;
        temp2 = temp2->rightChild;
    }
    return true;
}

template<typename TipKljuca, typename TipVrijednosti>
bool BinStabloMapa<TipKljuca, TipVrijednosti>::operator>(const BinStabloMapa &m) const {
    if(m.brEl == 0 || brEl == 0)
        throw std::domain_error("Jedno od stabala prazno");
    Cvor<TipKljuca, TipVrijednosti> *temp = m.vrh;
    while(temp->rightChild) {
        temp = temp->rightChild;
    }
    TipKljuca max = temp->element.kljuc;
    Cvor<TipKljuca, TipVrijednosti> *temp2 = vrh;
    while(temp2->leftChild) {
        if(temp2->element.kljuc < max) return false;
        temp2 = temp2->leftChild;
    }
    return true;
}

template<typename TipKljuca, typename TipVrijednosti>
template<typename TipKljuc, typename TipVrijednost>
TipVrijednosti BinStabloMapa<TipKljuca, TipVrijednosti>::prviManji(const TipKljuc &kljuc) {
    Cvor<TipKljuca, TipVrijednosti> *temp = vrh;
    while(temp) {
        if(kljuc == temp->element.kljuc) {
            if(temp->leftChild)
                return temp->leftChild->element.vrijednost;
            else if(temp->parent) {
                if(temp->parent->rightChild == temp)
                    return temp->parent->element.vrijednost;
                else if(temp->parent->parent && temp->parent->parent->rightChild == temp->parent)
                    return temp->parent->parent->element.vrijednost;
                else
                    throw std::domain_error("Prvi manji ne postoji");
            }
            else
                throw std::domain_error("Prvi manji ne postoji");
        }
        else if(kljuc > temp->element.kljuc)
            temp = temp->rightChild;
        else
            temp = temp->leftChild;
    }
    throw std::domain_error("Kljuc ne postoji u mapi");
}

template<typename TipKljuca, typename TipVrijednosti>
BinStabloMapa<TipKljuca, TipVrijednosti>::BinStabloMapa(TipKljuca *nizKjuceva, TipVrijednosti *nizVrijednosti, int vel) {
    int *i = new int(0);
    preOrderKreiranje(vrh, nizKjuceva, nizVrijednosti, i, nullptr, vel, false);
    delete i;
}

#endif //ASP_VJEZBA8_BINSTABLOMAPA_H
