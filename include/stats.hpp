#ifndef POKEMON_DAMAGE_CALC_CPP_STATS_HPP
#define POKEMON_DAMAGE_CALC_CPP_STATS_HPP

#include <vector>

#include "enums.h"

namespace PokemonDamageCalcCPP
{
namespace Stats
{

struct HiddenPower
{
   ENUMS::TypeName type;
   int power;
};

const std::vector<ENUMS::StatID> RBY = 
{
   ENUMS::StatID::hp,
   ENUMS::StatID::atk, 
   ENUMS::StatID::def,
   ENUMS::StatID::spc, 
   ENUMS::StatID::spe
};
const std::vector<ENUMS::StatID> GSC = 
{
   ENUMS::StatID::hp,
   ENUMS::StatID::atk, 
   ENUMS::StatID::def,
   ENUMS::StatID::spa,
   ENUMS::StatID::spd,
   ENUMS::StatID::spe
};
const std::vector<ENUMS::StatID> ADV = GSC;
const std::vector<ENUMS::StatID> DPP = GSC;
const std::vector<ENUMS::StatID> BW = GSC;
const std::vector<ENUMS::StatID> XY = GSC;
const std::vector<ENUMS::StatID> SM = GSC;
const std::vector<ENUMS::StatID> SS = GSC;
const std::vector<ENUMS::StatID> SV = GSC;

const std::vector<std::vector<ENUMS::StatID>> STATS = 
{{}, RBY, GSC, ADV, DPP, BW, XY, SM, SS, SV};

enum HPTypeName
{
   Fighting,
   Flying,
   Poison,
   Ground,
   Rock,
   Bug,
   Ghost,
   Steel,
   Fire,
   Water,
   Grass,
   Electric,
   Psychic,
   Ice,
   Dragon,
   Dark
};

const std::vector<std::string> HP_TYPES = 
{
  "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel",
  "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon", "Dark",
};

// The pair here is IVs and DVs respectively.
const std::map<HPTypeName, std::pair<ENUMS::StatsTable, ENUMS::StatsTable>> HP = 
{
   {
      HPTypeName::Bug, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 30},
            {ENUMS::StatID::def, 30},
            {ENUMS::StatID::spd, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 13},
            {ENUMS::StatID::def, 13},
         }
      )
   },
   {
      HPTypeName::Dark, 
      std::make_pair
      (
         ENUMS::StatsTable
         {}, 
         ENUMS::StatsTable
         {}
      )
   },
   {
      HPTypeName::Dragon, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::def, 14},
         }
      )
   },
   {
      HPTypeName::Electric, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::spa, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 14},
         }
      )
   },
   {
      HPTypeName::Fighting, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::def, 30},
            {ENUMS::StatID::spa, 30},
            {ENUMS::StatID::spd, 30},
            {ENUMS::StatID::spe, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 12},
            {ENUMS::StatID::def, 12},
         }
      )
   },
   {
      HPTypeName::Fire, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::def, 30},
            {ENUMS::StatID::spa, 30},
            {ENUMS::StatID::spe, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 14},
            {ENUMS::StatID::def, 12},
         }
      )
   },
   {
      HPTypeName::Flying, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::hp, 30},
            {ENUMS::StatID::atk, 30},
            {ENUMS::StatID::def, 30},
            {ENUMS::StatID::spa, 30},
            {ENUMS::StatID::spd, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 12},
            {ENUMS::StatID::def, 13},
         }
      )
   },
   {
      HPTypeName::Ghost, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::def, 30},
            {ENUMS::StatID::spd, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 13},
            {ENUMS::StatID::def, 14},
         }
      )
   },
   {
      HPTypeName::Grass, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 30},
            {ENUMS::StatID::spa, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 14},
            {ENUMS::StatID::def, 14},
         }
      )
   },
   {
      HPTypeName::Ground, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::spa, 30},
            {ENUMS::StatID::spd, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 12},
         }
      )
   },
   {
      HPTypeName::Ice, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 30},
            {ENUMS::StatID::def, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 12},
         }
      )
   },
   {
      HPTypeName::Poison, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::def, 30},
            {ENUMS::StatID::spa, 30},
            {ENUMS::StatID::spd, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 12},
            {ENUMS::StatID::def, 14},
         }
      )
   },
   {
      HPTypeName::Psychic, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 30},
            {ENUMS::StatID::spe, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::def, 12},
         }
      )
   },
   {
      HPTypeName::Rock, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::def, 30},
            {ENUMS::StatID::spd, 30},
            {ENUMS::StatID::spe, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 13},
            {ENUMS::StatID::def, 12},
         }
      )
   },
   {
      HPTypeName::Steel, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::spd, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 13},
         }
      )
   },
   {
      HPTypeName::Water, 
      std::make_pair
      (
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 30},
            {ENUMS::StatID::def, 30},
            {ENUMS::StatID::spa, 30},
         }, 
         ENUMS::StatsTable
         {
            {ENUMS::StatID::atk, 14},
            {ENUMS::StatID::def, 13},
         }
      )
   },
};

ENUMS::StatID ConvertStatID(const ENUMS::StatIDExceptHP stat);
std::string DisplayStat(const ENUMS::StatID stat);
std::string ShortForm(const ENUMS::StatID stat);
int IVToDV(const int iv);
int DVToIV(const int dv);
ENUMS::StatsTable DVsToIVs(const ENUMS::StatsTable& dvs);
int GetHPDV(const ENUMS::StatsTable& ivs);
int CalcStatRBYFromDV(const ENUMS::StatID stat, const int base, const int dv, const int level);
int CalcStatRBY(const ENUMS::StatID stat,const int base, const int iv, const int level);
int CalcStatADV
(
   const ENUMS::StatID stat,
   const int base,
   const int iv,
   const int ev,
   const int level,
   std::optional<std::string> nature
);

int CalcStat
(
   const ENUMS::GenerationNumber gen,
   const ENUMS::StatID stat,
   const int base,
   const int iv,
   const int ev,
   const int level,
   std::optional<std::string> nature
);
   
ENUMS::StatsTable GetHiddenPowerIVs(const ENUMS::GenerationNumber gen, HPTypeName hp_type);
HiddenPower GetHiddenPower(const ENUMS::GenerationNumber gen, const ENUMS::StatsTable ivs);

}
}


#endif
