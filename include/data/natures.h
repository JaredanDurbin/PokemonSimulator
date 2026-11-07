#ifndef POKEMON_DAMAGE_CALC_CPP_DATA_NATURES_H
#define POKEMON_DAMAGE_CALC_CPP_DATA_NATURES_H

#include <map>
#include <set>
#include <string>
#include <vector>

#include "../enums.h"

namespace PokemonDamageCalcCPP
{
namespace Data
{
class Natures
{
private:
   struct Nature
   {
      std::string kind = "Nature";
      std::string id;
      std::string name;
      ENUMS::StatIDExceptHP plus;
      ENUMS::StatIDExceptHP minus;
   };

   Natures();
   ~Natures() = default;

   static const std::map<std::string, std::pair<ENUMS::StatIDExceptHP, ENUMS::StatIDExceptHP>> NATURES;
   std::map<std::string, Nature> NATURES_BY_ID;

public:
   static Natures& Instance();

   [[nodiscard]]
   const std::map<std::string, 
                  std::pair<ENUMS::StatIDExceptHP, 
                            ENUMS::StatIDExceptHP>>& GetNatures() const;
   const std::set<std::string> GetNatureIDs() const;
   std::string NatureEnumToString(const ENUMS::NatureName name) const;
};
}
}

#endif

