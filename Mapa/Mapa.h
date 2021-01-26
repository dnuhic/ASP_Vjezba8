//
// Created by dzena on 26/01/2021.
//

#ifndef ASP_VJEZBA8_MAPA_H
#define ASP_VJEZBA8_MAPA_H


template <typename TipKljuca, typename TipVrijednosti>
class Mapa {
public:
    Mapa() = default;
    virtual ~Mapa() = default;
    virtual TipVrijednosti operator[](TipKljuca index) const = 0;
    virtual TipVrijednosti &operator[](TipKljuca index) = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const TipKljuca &k) = 0;
};


#endif //ASP_VJEZBA8_MAPA_H
