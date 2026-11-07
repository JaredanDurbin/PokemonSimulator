#include "./../include/stats.hpp"

#include <cmath>
#include <cstdint>

#include "./../include/util/util.h"
#include "./../include/data/natures.h"
#include "./../include/data/types.h"

namespace PokemonDamageCalcCPP
{
namespace Stats
{

ENUMS::StatID ConvertStatID(const ENUMS::StatIDExceptHP stat)
{
   switch (stat)
   {
   case ENUMS::StatIDExceptHP::atk:
      return ENUMS::StatID::atk;

   case ENUMS::StatIDExceptHP::def:
      return ENUMS::StatID::def;

   case ENUMS::StatIDExceptHP::spa:
      return ENUMS::StatID::spa;

   case ENUMS::StatIDExceptHP::spd:
      return ENUMS::StatID::spd;

   case ENUMS::StatIDExceptHP::spe:
      return ENUMS::StatID::spe;
   }

   return ENUMS::StatID::hp;
}

std::string DisplayStat(const ENUMS::StatID stat)
{
   switch (stat) 
   {
   case ENUMS::StatID::hp:
      return "HP";
   case ENUMS::StatID::atk:
      return "Atk";
   case ENUMS::StatID::def:
      return "Def";
   case ENUMS::StatID::spa:
      return "SpA";
   case ENUMS::StatID::spd:
      return "SpD";
   case ENUMS::StatID::spe:
      return "Spe";
   case ENUMS::StatID::spc:
      return "Spc";
   }

   return "";
}

std::string ShortForm(const ENUMS::StatID stat) 
{
   switch (stat) 
   {
   case ENUMS::StatID::hp:
      return "hp";
   case ENUMS::StatID::atk:
      return "at";
   case ENUMS::StatID::def:
      return "df";
   case ENUMS::StatID::spa:
      return "sa";
   case ENUMS::StatID::spd:
      return "sd";
   case ENUMS::StatID::spe:
      return "sp";
   case ENUMS::StatID::spc:
      return "sl";
   }

   return "";
}

int IVToDV(const int iv)
{
   return iv / 2;
}

int DVToIV(const int dv) 
{
   return dv * 2;
}

ENUMS::StatsTable DVsToIVs(const ENUMS::StatsTable& dvs)
{
   ENUMS::StatsTable ivs{};
   for (const auto& [dv, stat] : dvs) 
   {
      ivs[dv] = DVToIV(stat);
   }
   return ivs;
}

int GetHPDV(const ENUMS::StatsTable& ivs)
{
   return ((IVToDV(ivs.at(ENUMS::StatID::atk)) % 2) * 8 + 
           (IVToDV(ivs.at(ENUMS::StatID::def)) % 2) * 4 +
           (IVToDV(ivs.at(ENUMS::StatID::spe)) % 2) * 2 +
           (IVToDV(ivs.at(ENUMS::StatID::spc)) % 2));
}

int CalcStatRBYFromDV(const ENUMS::StatID stat, const int base, const int dv, const int level) 
{
   if (stat == ENUMS::StatID::hp) 
   {
      return ((((base + dv) * 2 + 63) * level) / 100) + level + 10;
   } 
   else 
   {
      return ((((base + dv) * 2 + 63) * level) / 100) + 5;
   }
}

int CalcStatRBY(const ENUMS::StatID stat,const int base, const int iv, const int level)
{
   return CalcStatRBYFromDV(stat, base, IVToDV(iv), level);
}

int CalcStatADV
(
   const ENUMS::StatID stat,
   const int base,
   const int iv,
   const int ev,
   const int level,
   std::optional<std::string> nature
) 
{
   if (stat == ENUMS::StatID::hp) 
   {
      return base == 1 ? base : (((base * 2 + iv + (ev / 4)) * level) / 100) + level + 10;
   } 
   else 
   {
      std::pair<ENUMS::StatID, ENUMS::StatID> mods;
      if (nature) 
      {
         const auto nat = Data::Natures::Instance().GetNatures();
         mods = std::make_pair(ConvertStatID(nat.at(nature.value()).first), ConvertStatID(nat.at(nature.value()).second));
      }
      const float n =
         mods.first == stat && mods.second == stat
         ? 1
         : mods.first == stat
            ? 1.1
            : mods.second == stat
               ? 0.9
               : 1;

      return (((((base * 2 + iv + (ev / 4)) * level) / 100) + 5) * n);
   }
}

int CalcStat
(
   const ENUMS::GenerationNumber gen,
   const ENUMS::StatID stat,
   const int base,
   const int iv,
   const int ev,
   const int level,
   std::optional<std::string> nature
) 
{
   int g = static_cast<int>(gen);
   if (g < 3) return CalcStatRBY(stat, base, iv, level);
   return CalcStatADV(stat, base, iv, ev, level, nature);
}

ENUMS::StatsTable GetHiddenPowerIVs(const ENUMS::GenerationNumber gen, HPTypeName hp_type)
{
   const auto hp = HP.at(hp_type);
   int g = static_cast<int>(gen);
   return g == 2 ? DVsToIVs(hp.second) : hp.first;
}

HiddenPower GetHiddenPower(const ENUMS::GenerationNumber gen, const ENUMS::StatsTable ivs)
{
   const ENUMS::StatsTable stats = 
   {
      {ENUMS::StatID::hp,  31}, 
      {ENUMS::StatID::atk, 31}, 
      {ENUMS::StatID::def, 31}, 
      {ENUMS::StatID::spe, 31}, 
      {ENUMS::StatID::spa, 31}, 
      {ENUMS::StatID::spd, 31}
   };
   int g = static_cast<int>(gen);
   if (g <= 2) 
   {
      // Gen 2 specific Hidden Power check. IVs are still treated 0-31 so we get them 0-15
      uint32_t atk_dv = Util::tr(ivs.at(ENUMS::StatID::atk) / 2);
      uint32_t def_dv = Util::tr(ivs.at(ENUMS::StatID::def) / 2);
      uint32_t spe_dv = Util::tr(ivs.at(ENUMS::StatID::spe) / 2);
      uint32_t spc_dv = Util::tr(ivs.at(ENUMS::StatID::spa) / 2);
      
      return 
      { 
         .type = Data::Types::Instance().StringToTypeNameENUM(HP_TYPES[4 * (atk_dv % 4) + (def_dv % 4)]),
         .power = static_cast<int>(Util::tr((5.0 * ((spc_dv >> 3) + 
                                                    (2 * (spe_dv >> 3)) + 
                                                    (4 * (def_dv >> 3)) + 
                                                    (8 * (atk_dv >> 3))) + 
                                                   (spc_dv % 4)) / 2.0 + 31.0))
      };
   } 
   else 
   {
      // Hidden Power check for Gen 3 onwards
      uint32_t hp_type_x = 0;
      uint32_t hp_power_x = 0;
      uint32_t i = 1;
      for (const auto& [stat, num] : stats) 
      {
         hp_type_x += i * (ivs.at(stat) % 2);
         hp_power_x += i * (Util::tr(ivs.at(stat) / 2) % 2);
         i *= 2;
      }
      return 
      {
         .type = Data::Types::Instance().StringToTypeNameENUM
         (
            HP_TYPES[Util::tr(hp_type_x * 15 / 63)]
         ),
         // After Gen 6, Hidden Power is always 60 base power
         .power = static_cast<int>((g && g < 6) ? Util::tr(hp_power_x * 40 / 63) + 30 : 60),
      };
   }
}

}
}