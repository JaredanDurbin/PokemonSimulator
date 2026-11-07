#ifndef POKEMON_DAMAGE_CALC_CPP_DATA_ABILITIES_H
#define POKEMON_DAMAGE_CALC_CPP_DATA_ABILITIES_H

#include <map>
#include <set>
#include <string>
#include <vector>

namespace PokemonDamageCalcCPP
{
namespace Data
{
class Abilities
{
private:
   struct Ability
   {
      const std::string kind = "Ability";
      std::string id;
      std::string name;
   };

   Abilities();
   ~Abilities() = default;

   static const std::set<std::string> RBY;
   static const std::set<std::string> GSC;
   static const std::set<std::string> ADV;
   static const std::set<std::string> DPP;
   static const std::set<std::string> BW;
   static const std::set<std::string> XY;
   static const std::set<std::string> SM;
   static const std::set<std::string> SS;
   static const std::set<std::string> SV;

   static std::vector<std::set<std::string>> ABILITIES;
   std::vector<std::map<std::string, Ability>> ABILITIES_BY_ID;

public:
   static Abilities& Instance();

   [[nodiscard]]
   const std::set<std::string>& GetRBYAbilities() const;
   const std::set<std::string>& GetGSCAbilities() const;
   const std::set<std::string>& GetADVAbilities() const;
   const std::set<std::string>& GetDPPAbilities() const;
   const std::set<std::string>& GetBWAbilities() const;
   const std::set<std::string>& GetXYAbilities() const;
   const std::set<std::string>& GetSMAbilities() const;
   const std::set<std::string>& GetSSAbilities() const;
   const std::set<std::string>& GetSVAbilities() const;
   const std::set<std::string>& GetAbilitiesByGeneration(const int gen) const;
   //const std::map<std::string, std::string>& GetAbilitiesByIDByGeneration(const int gen) const;
};
}
}

#endif
