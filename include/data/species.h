#ifndef POKEMON_DAMAGE_CALC_CPP_DATA_SPECIES_H
#define POKEMON_DAMAGE_CALC_CPP_DATA_SPECIES_H

#include <map>
#include <set>
#include <string>
#include <vector>

#include "../enums.h"

namespace PokemonDamageCalcCPP
{
namespace Data
{

struct Specie
{
   std::string kind = "Species";
   std::string id = "";
   std::vector<ENUMS::TypeName> types = {};
   ENUMS::StatsTable bs = {};
   float weightkg = 0;
   std::optional<bool> nfe = std::nullopt;
   std::optional<ENUMS::GenderName> gender = std::nullopt;
   std::optional<std::vector<std::string>> other_formes = std::nullopt;
   std::optional<std::string> base_species = std::nullopt;
   std::optional<std::vector<std::string>> abilities = std::nullopt; // ability
};

class Species
{
private:
   static std::map<std::string, Specie> EraseMapOfSpeciesEntry
   (
      const std::map<std::string, Specie>& species_data_list,
      const std::string& entry
   );

   static void UpdateSpecieValues
   (
      Specie& output, 
      const Specie& input
   );

   static std::map<std::string, Specie> ExtendMapOfSpecie
   (
      const std::vector<std::map<std::string, Specie>>& species_data_list
   );

   Species();
   ~Species() = default;

   static const std::map<std::string, Specie> RBY;
   static const std::map<std::string, Specie> GSC_PATCH;
   static const std::map<std::string, Specie> GSC;
   static const std::map<std::string, Specie> ADV_PATCH;
   static const std::map<std::string, Specie> ADV;
   static const std::map<std::string, Specie> DPP_PATCH;
   static const std::map<std::string, Specie> DPP;
   static const std::map<std::string, Specie> BW_PATCH;
   static const std::map<std::string, Specie> BW;
   static const std::map<std::string, Specie> XY_PATCH;
   static const std::map<std::string, Specie> XY;
   static const std::map<std::string, Specie> SM_PATCH;
   static const std::map<std::string, Specie> SM;
   static const std::map<std::string, Specie> SS_PATCH;
   static const std::map<std::string, Specie> SS;
   static const std::map<std::string, Specie> PLA_PATCH;
   static const std::map<std::string, Specie> SV_PATCH;
   static const std::map<std::string, Specie> SV;

   static const std::vector<std::map<std::string, Specie>> SPECIES;
   std::vector<std::map<std::string, Specie>> SPECIES_BY_ID;

public:
   static Species& Instance();

   [[nodiscard]]
   const std::map<std::string, Specie>& GetRBYSpecies() const;
   const std::map<std::string, Specie>& GetGSCSpecies() const;
   const std::map<std::string, Specie>& GetADVSpecies() const;
   const std::map<std::string, Specie>& GetDPPSpecies() const;
   const std::map<std::string, Specie>& GetBWSpecies() const;
   const std::map<std::string, Specie>& GetXYSpecies() const;
   const std::map<std::string, Specie>& GetSMSpecies() const;
   const std::map<std::string, Specie>& GetSSSpecies() const;
   const std::map<std::string, Specie>& GetSVSpecies() const;
   const std::set<std::string> GetSpeciesIDsByGeneration(const int gen) const;
   const Specie& GetSpeciesByGen(const int gen, const std::string& species_name) const;
   const Specie& GetSpeciesByGen_ID(const int gen, const std::string& species_id) const;
   Specie ExtendSpecie(const Specie& output, const std::optional<Specie>& input = std::nullopt);
   
};
}
}

#endif

