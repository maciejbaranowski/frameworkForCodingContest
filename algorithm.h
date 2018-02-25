#pragma once

#include "io.h"
#include "utils.h"
#include <limits>
#include <algorithm>

class Algorithm {
public:
  explicit Algorithm(IO && _io) :
  io(std::move(_io)) {
    process();
  }

private:
  struct Biuro {
    unsigned id;
    unsigned cenaWynajecia;
    unsigned czasWynajecia;
    vector<unsigned> jezyki;
  };
  struct Material {
    unsigned id;
    unsigned momentUzyskania;
    unsigned momentStraty;
    unsigned jezykZrodlowy;
    unsigned jezykDocelowy;
    unsigned kosztCzasu;
    unsigned nagroda;
  };
  struct TlumaczeniePrzezBiuro {
    unsigned czasRozpoczecia;
    unsigned biuro;
    unsigned jezykDocelowy;
  };
  struct UkonczoneTlumaczenie {
    unsigned id;
    vector<TlumaczeniePrzezBiuro> tlumaczenia;
  };
  struct WynajecieBiura {
    unsigned id;
    unsigned czas;
  };
  std::pair<bool, Biuro> znajdzNajtanszeBiuro(
    const vector<Biuro> & biura,
    const Material & material)
  {
    auto najniszaCena = numeric_limits<unsigned>::max();
    auto najtanszeBiuro = biura[0];
    for (auto biuro : biura)
    {
      if (biuro.czasWynajecia > material.kosztCzasu and
        biuro.czasWynajecia > material.momentStraty - material.momentUzyskania)
      {
        if (std::find(
          biuro.jezyki.cbegin(),
          biuro.jezyki.cend(),
          material.jezykDocelowy) != biuro.jezyki.end()
          and
          std::find(
          biuro.jezyki.cbegin(),
          biuro.jezyki.cend(),
          material.jezykZrodlowy) != biuro.jezyki.end()
          )
        {
          if (biuro.cenaWynajecia < najniszaCena)
          {
            najniszaCena = biuro.cenaWynajecia;
            najtanszeBiuro = biuro;
          }
        }
      }
    }
    if (najniszaCena != numeric_limits<unsigned>::max())
    {
      return {true, najtanszeBiuro};
    }
    return {false,{}};
  }
  void process() {
    auto T = io.readSingle();
    while (T-->0)
    {
      auto liczbaBiur = io.readSingle<unsigned>();
      auto liczbaMaterialow = io.readSingle<unsigned>();
      vector<Biuro> biura;
      biura.reserve(liczbaBiur);
      for (auto i = 0u; i< liczbaBiur; i++)
      {
        auto id = io.readSingle<unsigned>();
        auto cenaWynajecia = io.readSingle<unsigned>();
        auto czasWynajecia = io.readSingle<unsigned>();
        auto liczbaJezykow = io.readSingle<unsigned>();
        auto jezyki = io.readLine<unsigned>(liczbaJezykow);
        biura.push_back({id,cenaWynajecia,czasWynajecia,jezyki});
      }
      vector<Material> materialy;
      materialy.reserve(liczbaMaterialow);
      for (auto i = 0u; i < liczbaMaterialow; i++)
      {
        unsigned id = io.readSingle<unsigned>();
        unsigned momentUzyskania = io.readSingle<unsigned>();
        unsigned momentStraty = io.readSingle<unsigned>();
        unsigned jezykZrodlowy = io.readSingle<unsigned>();
        unsigned jezykDocelowy = io.readSingle<unsigned>();
        unsigned kosztCzasu = io.readSingle<unsigned>();
        unsigned nagroda = io.readSingle<unsigned>();
        materialy.push_back({id,momentUzyskania,momentStraty,jezykZrodlowy,jezykDocelowy,kosztCzasu,nagroda});
      }
      vector<UkonczoneTlumaczenie> ukonczoneTlumaczenia;
      vector<WynajecieBiura> wynajeciaBiur;
      int suma = 0;

      for (auto material : materialy)
      {
        auto optBiuro = znajdzNajtanszeBiuro(biura, material);
        if (optBiuro.first)
        {
          wynajeciaBiur.push_back({
            optBiuro.second.id,
            material.momentUzyskania});
          suma -= optBiuro.second.cenaWynajecia;
          suma += material.nagroda;
          ukonczoneTlumaczenia.push_back({
            material.id,
            {
              {
                material.momentUzyskania,
                optBiuro.second.id,
                material.jezykDocelowy
              }
            }
          });
        }
      }

      io.writeSingle(wynajeciaBiur.size());
      io << "\n";
      for (auto biuro : wynajeciaBiur) {
        io << biuro.id << " " << biuro.czas << "\n";
      }
      io.writeSingle(ukonczoneTlumaczenia.size());
      io << "\n";
      for (auto tlumaczenie : ukonczoneTlumaczenia) {
        io << tlumaczenie.id << " " <<  tlumaczenie.tlumaczenia.size() << "\n";
        for (auto krokTlumaczenia : tlumaczenie.tlumaczenia)
        {
          io << krokTlumaczenia.czasRozpoczecia << " " <<  krokTlumaczenia.biuro << " " <<  krokTlumaczenia.jezykDocelowy;
        }
        io << "\n";
      }
      io.writeSingle(suma);
      io << "\n";
    }
  }

  IO && io;
};
