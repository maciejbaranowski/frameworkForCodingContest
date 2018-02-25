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
  std::tuple<bool, Biuro, unsigned> znajdzNajtanszeBiuro(
    const vector<Biuro> & biura,
    const Material & material)
  {
    auto najniszaCena = numeric_limits<unsigned>::max();
    auto najtanszeBiuro = biura[0];
    auto ileRazyNajtansze = 0u;
    for (auto biuro : biura)
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
        unsigned teBiuroTrzebabyWynajacIleRazy =
          material.kosztCzasu / biuro.czasWynajecia + 1;
        unsigned prawdziwyKosztTlumaczenia =
          biuro.cenaWynajecia * teBiuroTrzebabyWynajacIleRazy;
        {
          if (prawdziwyKosztTlumaczenia < najniszaCena)
          {
            najniszaCena = prawdziwyKosztTlumaczenia;
            najtanszeBiuro = biuro;
            ileRazyNajtansze = teBiuroTrzebabyWynajacIleRazy;
          }
        }
      }
    }
    if (najniszaCena != numeric_limits<unsigned>::max())
    {
      return {true, najtanszeBiuro, ileRazyNajtansze};
    }
    return {false,{}, 0u};
  }

  pair<bool, UkonczoneTlumaczenie> saDobreBiuraDlaMaterialu(
    const vector<WynajecieBiura> & wynajeciaBiur,
    const vector<Biuro> & biura,
    const Material & material)
  {
    for (auto wynajecie : wynajeciaBiur)
    {
      Biuro biuro = *std::find_if(
        biura.begin(),
        biura.end(),
        [=] (const auto b) {
          return b.id == wynajecie.id;
        });
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
        auto biuroDostepneOd = max(wynajecie.czas, material.momentUzyskania);
        auto biuroDostepneDo = min(wynajecie.czas + biuro.czasWynajecia, material.momentStraty);
        if (biuroDostepneDo < biuroDostepneOd)
          continue;
        if (material.kosztCzasu < biuroDostepneDo - biuroDostepneOd)
        {
          return {true,{
            material.id,
            {
              {biuroDostepneOd, biuro.id, material.jezykDocelowy}
            }
          }};
        }
      }
    }
    return {false,{}};
  }

  void process() {
    auto T = io.readSingle();
    while (T-->0)
    {
      cerr << "TESTCASES LEFT: " << T;
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

        auto idBiuraDlaMaterialu =
          saDobreBiuraDlaMaterialu(wynajeciaBiur, biura, material);
        if (idBiuraDlaMaterialu.first)
        {
          suma += material.nagroda;
          ukonczoneTlumaczenia.push_back(idBiuraDlaMaterialu.second);
          continue;
        }

        auto optBiuro = znajdzNajtanszeBiuro(biura, material);
        if (std::get<0>(optBiuro))
        {
          suma -= std::get<1>(optBiuro).cenaWynajecia*std::get<2>(optBiuro);
          while ((std::get<2>(optBiuro)--)>0)
          {
            wynajeciaBiur.push_back({
              std::get<1>(optBiuro).id,
              material.momentUzyskania + std::get<1>(optBiuro).czasWynajecia*std::get<2>(optBiuro)});
          }
          suma += material.nagroda;
          ukonczoneTlumaczenia.push_back({
            material.id,
            {
              {
                material.momentUzyskania,
                std::get<1>(optBiuro).id,
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
