#include "./../include/pokemon.hpp"

#include "./../include/data/moves.h"
#include "./../include/util/util.h"
#include "./../include/stats.hpp"
#include "./../include/data/natures.h"

namespace PokemonDamageCalcCPP
{
namespace Pokemon
{

ENUMS::StatsTable Pokemon::WithDefault
(
   ENUMS::GenerationNumber gen_in,
   ENUMS::StatsTable current,
   int val,
   bool match
) 
{
   const int g = static_cast<int>(gen_in);

   ENUMS::StatsTable cur = 
   {
      {ENUMS::StatID::hp, val},
      {ENUMS::StatID::atk, val},
      {ENUMS::StatID::def, val},
      {ENUMS::StatID::spa, val},
      {ENUMS::StatID::spd, val},
      {ENUMS::StatID::spe, val},
   };
   for (const auto& [key, value] : current) 
   {
      if (key != ENUMS::StatID::spc) 
      {
         cur[key] = value;
      }
   }

   if (current.contains(ENUMS::StatID::spc)) 
   {
      cur[ENUMS::StatID::spa] = current.at(ENUMS::StatID::spc);
      cur[ENUMS::StatID::spd] = current.at(ENUMS::StatID::spc);
   }
   if (match && g <= 2 && cur[ENUMS::StatID::spa] != cur[ENUMS::StatID::spd]) 
   {
      // Just make one equal the other.
      cur[ENUMS::StatID::spa] = cur[ENUMS::StatID::spd];
   }
   return cur;
}

int Pokemon::CalcStat(const ENUMS::GenerationNumber gen_in, const ENUMS::StatID stat_in)
{
   return Stats::CalcStat
   (
      gen_in,
      stat_in,
      (gen_in == ENUMS::GenerationNumber::__1 && 
         (stat_in == ENUMS::StatID::spa || stat_in == ENUMS::StatID::spd))
            ? species.bs.at(ENUMS::StatID::spc) : species.bs.at(stat_in),
      ivs.at(stat_in),
      evs.at(stat_in),
      level,
      Data::Natures::Instance().NatureEnumToString(nature)
   );
}

Pokemon::Pokemon
(
   const ENUMS::GenerationNumber gen_in,
   const std::string& name_in,
   const State::Pokemon& options
)
{
   const int g = static_cast<int>(gen_in);

   if (options.overrides)
   {
      species = Data::Species::Instance().ExtendSpecie
      (
         Data::Species::Instance().GetSpeciesByGen_ID(g, Util::ToID(name_in)), 
         options.overrides.value()
      );
   }
   else
   {
      species = Data::Species::Instance().ExtendSpecie
      (
         Data::Species::Instance().GetSpeciesByGen_ID(g, Util::ToID(name_in))
      );
   }

   gen = gen_in;
   name = options.name ? options.name.value() : name_in;
   types = species.types;
   weightkg = species.weightkg;

   level = options.level ? options.level.value() : 100;
   gender = options.gender ? options.gender.value() 
                           : species.gender ? species.gender.value() 
                                            : ENUMS::GenderName::M;
   ability = options.ability ? options.ability.value() 
                             : species.abilities ? species.abilities.value().at(0) 
                                                 : "";
   ability_on = options.ability_on;

   is_dynamaxed = options.is_dynamaxed;
   dynamax_level = is_dynamaxed
      ? (options.dynamax_level ? options.dynamax_level : 10) : std::nullopt;
   is_salt_cure = options.is_salt_cure;
   allies_fainted = options.allies_fainted;
   boosted_stat = options.boosted_stat;
   tera_type = options.tera_type;
   item = options.item;
   nature = options.nature ? options.nature.value() : ENUMS::NatureName::Serious;
   ivs = WithDefault(gen, options.ivs ? options.ivs.value() : ENUMS::StatsTable{}, 31);
   evs = WithDefault
   (
      gen, 
      options.evs ? options.evs.value() : ENUMS::StatsTable{}, 
      g >= 3 ? 0 : 252
   );
   boosts = WithDefault
   (
      gen, 
      options.boosts ? options.boosts.value() : ENUMS::StatsTable{}, 
      0, 
      false
   );

   // Gigantamax 'forms' inherit weight from their base species when not dynamaxed
   // TODO: clean this up with proper Gigantamax support
   if (weightkg == 0 && is_dynamaxed && !is_dynamaxed.value() && species.base_species) 
   {
      weightkg = Data::Species::Instance()
         .GetSpeciesByGen_ID(g, Util::ToID(species.base_species.value()))
         .weightkg;
   }

   if (g < 3) 
   {
      ivs.at(ENUMS::StatID::hp) = Stats::DVToIV
      (
         Stats::GetHPDV
         ({
            {ENUMS::StatID::atk, ivs.at(ENUMS::StatID::atk)},
            {ENUMS::StatID::def, ivs.at(ENUMS::StatID::def)},
            {ENUMS::StatID::spe, ivs.at(ENUMS::StatID::spe)},
            {ENUMS::StatID::spc, ivs.at(ENUMS::StatID::spa)},
         })
      );
   }

   raw_stats = {};
   stats = {};
   for (const auto stat : STATS) 
   {
      const int val = CalcStat(gen, stat);
      raw_stats[stat] = val;
      stats[stat] = val;
   }

   const int cur_hp = options.cur_hp ? options.cur_hp.value() 
                                     : options.original_cur_hp ? options.original_cur_hp.value()
                                                               : 0;
   original_cur_hp = (cur_hp && cur_hp <= raw_stats.at(ENUMS::StatID::hp)) 
                     ? cur_hp
                     : raw_stats.at(ENUMS::StatID::hp);
   status = options.status ? options.status.value() : ENUMS::StatusName::_;
   toxic_counter = options.toxic_counter ? options.toxic_counter.value() : 0;
   moves = options.moves ? options.moves.value() : std::vector<std::string>{};
}

int Pokemon::MaxHP(bool original) const
{
   // Shedinja still has 1 max HP during the effect even if its Dynamax Level is maxed (DaWoblefet)
   if (!original && is_dynamaxed  && is_dynamaxed.value() && species.bs.at(ENUMS::StatID::hp) != 1) 
   {
      return (raw_stats.at(ENUMS::StatID::hp) * (150 + 5 * (dynamax_level.value()))) / 100;
   }

   return raw_stats.at(ENUMS::StatID::hp);
}

 int Pokemon::CurHP(bool original) const
{
   // Shedinja still has 1 max HP during the effect even if its Dynamax Level is maxed (DaWoblefet)
   if (!original && is_dynamaxed  && is_dynamaxed.value() && species.bs.at(ENUMS::StatID::hp) != 1)  
   {
      return std::ceil((original_cur_hp * (150 + 5 * dynamax_level.value())) / 100);
   }

   return original_cur_hp;
}

bool Pokemon::HasAbility(const std::initializer_list<std::string>& abilities) const
{
   if (!ability) return false;
   return std::find(abilities.begin(), abilities.end(), ability.value()) != abilities.end();
}

bool Pokemon::HasAbility(const std::vector<std::string>& abilities) const
{
   if (!ability) return false;
   return std::find(abilities.begin(), abilities.end(), ability.value()) != abilities.end();
}

bool Pokemon::HasItem(const std::initializer_list<std::string>& items) const
{
   if (!item) return false;
   return std::find(items.begin(), items.end(), item.value()) != items.end();
}

bool Pokemon::HasItem(const std::vector<std::string>& items) const
{
   if (!item) return false;
   return std::find(items.begin(), items.end(), item.value()) != items.end();
}

bool Pokemon::HasStatus(const std::initializer_list<ENUMS::StatusName>& statuses) const
{
   return std::find(statuses.begin(), statuses.end(), status) != statuses.end();
}

bool Pokemon::HasType(const std::initializer_list<ENUMS::TypeName>& types_in) const
{
   for (const auto& type : types_in)
   {
      if (tera_type.has_value())
      {
         if (*tera_type == type)
         {
            return true;
         }
      }
      else
      {
         if (std::find(types.begin(), types.end(), type) != types.end())
         {
            return true;
         }
      }
   }

   return false;
}

bool Pokemon::HasOriginalType(const std::initializer_list<ENUMS::TypeName>& types_in) const
{
   for (const auto& type : types_in)
   {
      if (std::find(types.begin(), types.end(), type) != types.end())
      {
         return true;
      }
   }

   return false;
}

bool Pokemon::Named(const std::initializer_list<std::string>& names) const
{
   return std::find(names.begin(), names.end(), name) != names.end();
}

std::string GetForme
(
   const ENUMS::GenerationNumber gen,
   const std::string& species_name,
   const std::optional<std::string> item,
   const std::optional<std::string> move_name
)
{
   int g = static_cast<int>(gen);
   const Data::Specie curr_species = Data::Species::Instance().GetSpeciesByGen_ID(g, Util::ToID(species_name));
   if (!curr_species.other_formes) 
   {
      return species_name;
   }

   int i = 0;
   if 
   (
      (item &&
      ((item.value().find("ite") != std::string::npos && !item.value().find("ite Y") != std::string::npos) ||
         (species_name == "Groudon" && item.value() == "Red Orb") ||
         (species_name == "Kyogre" && item == "Blue Orb"))) ||
      (move_name && species_name == "Meloetta" && move_name.value() == "Relic Song") ||
      (species_name == "Rayquaza" && move_name.value() == "Dragon Ascent")
   ) 
   {
      i = 1;
   } 
   else if (item && item.value().find("ite Y") != std::string::npos) 
   {
      i = 2;
   }

   return i ? curr_species.other_formes.value().at(i - 1) : species_name;
}

}
}

