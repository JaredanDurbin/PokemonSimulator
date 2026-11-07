#ifndef POKEMON_DAMAGE_CALC_CPP_DATA_TYPES_H
#define POKEMON_DAMAGE_CALC_CPP_DATA_TYPES_H

#include <unordered_map>
#include <set>
#include <string>
#include <vector>

#include "./../enums.h"

namespace PokemonDamageCalcCPP
{
namespace Data
{
using TypeChart = std::unordered_map<ENUMS::TypeName, 
                                     std::unordered_map<ENUMS::TypeName, 
                                                        ENUMS::TypeEffectiveness>>;

class Types
{
private:
   struct Type
   {
      std::string kind = "Type";
      std::string id;
      std::string name;
      std::unordered_map<ENUMS::TypeName, ENUMS::TypeEffectiveness> effectiveness;
   };

   static TypeChart ExtendTypeChart(const TypeChart& original, const TypeChart& additional);

   Types();
   ~Types() = default;

   static const TypeChart RBY;
   static const TypeChart GSC_PATCH;
   static const TypeChart GSC;
   static const TypeChart ADV;
   static const TypeChart DPP;
   static const TypeChart BW;
   static const TypeChart XY_PATCH;
   static const TypeChart XY;
   static const TypeChart SM;
   static const TypeChart SS;
   static const TypeChart SV_PATCH;
   static const TypeChart SV;

   static std::vector<TypeChart> TYPES;
   std::vector<std::map<std::string, Type>> TYPES_BY_ID;

public:
   static Types& Instance();

   [[nodiscard]]
   std::string TypeNameENUMToString(const ENUMS::TypeName type);
   ENUMS::TypeName StringToTypeNameENUM(const std::string type);
   const std::set<std::string> GetTypeIDsByGeneration(const int gen) const;
   const std::unordered_map<ENUMS::TypeName, ENUMS::TypeEffectiveness>& GetTypeEffectivenessByTypeAndGen
   (
      const ENUMS::GenerationNumber gen,
      const ENUMS::TypeName type
   ) const;
   float CalculateTypeEffectiveness
   (
      const ENUMS::TypeEffectiveness eff1,
      const ENUMS::TypeEffectiveness eff2 = ENUMS::TypeEffectiveness::_1
   );
};
}
}

#endif

