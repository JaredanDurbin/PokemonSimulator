#include "./../include/calc_util.hpp"

#include "./../include/data/types.h"
#include "./../include/description.hpp"
#include "./../include/util/csv_util.h"

namespace PokemonDamageCalcCPP
{
namespace CalcUtil
{

int GetModifiedStat
(
   const int stat, 
   const int mod, 
   const std::optional<ENUMS::GenerationNumber> gen
)
{
   int stat_out = 0;

   if (gen && static_cast<int>(*gen) < 3) 
   {
      if (mod >= 0) 
      {
         const std::vector<float> past_gen_boost_table{1, 1.5, 2, 2.5, 3, 3.5, 4};
         stat_out = std::floor(stat * past_gen_boost_table[mod]);
      } 
      else 
      {
         const std::vector<int> numerators{100, 66, 50, 40, 33, 28, 25};
         stat_out = (stat * numerators[-mod]) / 100;
      }
      return std::min(999, std::max(1, stat));
   }

   const std::vector<std::pair<int, int>> modern_gen_boost_table = 
   {
      std::make_pair(2, 8),
      std::make_pair(2, 7),
      std::make_pair(2, 6),
      std::make_pair(2, 5),
      std::make_pair(2, 4),
      std::make_pair(2, 3),
      std::make_pair(2, 2),
      std::make_pair(3, 2),
      std::make_pair(4, 2),
      std::make_pair(5, 2),
      std::make_pair(6, 2),
      std::make_pair(7, 2),
      std::make_pair(8, 2)
   };
   stat_out = OF16(stat * modern_gen_boost_table[6 + mod].first);
   stat_out = (stat_out / modern_gen_boost_table[6 + mod].second);

   return stat_out;
}

bool IsQPActive
(
   const Pokemon::Pokemon pokemon,
   const State::Field field
)
{
   if (!pokemon.GetBoostedStat()) 
   {
      return false;
   }

   return 
   (
      (pokemon.HasAbility({"Protosynthesis"}) &&
         (field.HasWeather({ENUMS::Weather::Sun}) || 
          pokemon.HasItem({"Booster Energy"}))) ||
      (pokemon.HasAbility({"Quark Drive"}) &&
         (field.HasTerrain({ENUMS::Terrain::Electric_t}) || 
          pokemon.HasItem({"Booster Energy"}))) ||
      (pokemon.GetBoostedStat().value() != ENUMS::StatIDExceptHP::_auto)
   );
}

/**
 * Get which stat will be boosted by Quark Drive or Protosynthesis
 * In the case that `pokemon.boosted_stat` is set, it will always return that stat
 * In the case that two stats have equal value, stat choices will be prioritized
 * in the following order:
 * Attack, Defense, Special Attack, Special Defense, and Speed
 *
 * @param modifiedStats
 * @returns
 */
ENUMS::StatID GetQPBoostedStat
(
   const Pokemon::Pokemon& pokemon,
   const ENUMS::GenerationNumber gen
)
{
   if (pokemon.GetBoostedStat() && 
       pokemon.GetBoostedStat().value() != ENUMS::StatIDExceptHP::_auto) 
   {
      return Stats::ConvertStatID(pokemon.GetBoostedStat().value()); // override.
   }

   ENUMS::StatIDExceptHP best_stat = ENUMS::StatIDExceptHP::atk;
   std::vector<ENUMS::StatIDExceptHP> stats = 
   {
      ENUMS::StatIDExceptHP::def, 
      ENUMS::StatIDExceptHP::spa,
      ENUMS::StatIDExceptHP::spd,
      ENUMS::StatIDExceptHP::spe
   };
   for (const auto stat : stats) 
   {
      if 
      (
         // proto/quark ignore boosts when considering their boost
         GetModifiedStat(pokemon.GetRawStats().at(Stats::ConvertStatID(stat)), 
                         pokemon.GetBoosts().at(Stats::ConvertStatID(stat)), gen) >
         GetModifiedStat(pokemon.GetRawStats().at(Stats::ConvertStatID(best_stat)), 
                         pokemon.GetBoosts().at(Stats::ConvertStatID(best_stat)), gen)
      ) 
      {
         best_stat = stat;
      }
   }
   return Stats::ConvertStatID(best_stat);
}

int ChainMods(std::vector<int> mods, int lower_bound, int upper_bound)
{
   int M = 4096;
   for (const int mod : mods) 
   {
      if (mod != 4096) 
      {
         M = (M * mod + 2048) >> 12;
      }
   }
   return std::max(std::min(M, upper_bound), lower_bound);
}

int GetFinalSpeed
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& pokemon,
   const State::Field& field,
   const State::Side& side
)
{
   int speed = GetModifiedStat
   (
      pokemon.GetRawStats().at(ENUMS::StatID::spe), 
      pokemon.GetBoosts().at(ENUMS::StatID::spe), 
      gen
   );
   std::vector<int> speed_mods{};

   if (side.is_tailwind) speed_mods.push_back(8192);
   // Pledge swamp would Get applied here when implemented
   // speed_mods.push_back(1024);

   if ((pokemon.HasAbility({"Unburden"}) && pokemon.GetAbilityOn()) ||
       (pokemon.HasAbility({"Chlorophyll"}) && field.HasWeather({ENUMS::Weather::Sun})) ||
       (pokemon.HasAbility({"Sand Rush"}) && field.HasWeather({ENUMS::Weather::Sand})) ||
       (pokemon.HasAbility({"Swift Swim"}) && field.HasWeather({ENUMS::Weather::Rain})) ||
       (pokemon.HasAbility({"Slush Rush"}) && 
          field.HasWeather({ENUMS::Weather::Hail, ENUMS::Weather::Snow})) ||
       (pokemon.HasAbility({"Surge Surfer"}) && field.HasTerrain({ENUMS::Terrain::Electric_t})))
   {
      speed_mods.push_back(8192);
   } 
   else if (pokemon.HasAbility({"Quick Feet"}) && pokemon.HasStatus()) 
   {
      speed_mods.push_back(6144);
   } 
   else if (pokemon.HasAbility({"Slow Start"}) && pokemon.GetAbilityOn()) 
   {
      speed_mods.push_back(2048);
   } 
   else if (IsQPActive(pokemon, field) && GetQPBoostedStat(pokemon, gen) == ENUMS::StatID::spe) 
   {
      speed_mods.push_back(6144);
   }

   auto temp = EV_ITEMS;
   temp.push_back("Iron Ball");
   if (pokemon.HasItem({"Choice Scarf"})) 
   {
      speed_mods.push_back(6144);
   } 
   else if (pokemon.HasItem(temp)) 
   {
      speed_mods.push_back(2048);
   } 
   else if (pokemon.HasItem({"Quick Powder"}) && pokemon.Named({"Ditto"})) 
   {
      speed_mods.push_back(8192);
   }

   speed = OF32(PokeRound((speed * ChainMods(speed_mods, 410, 131172)) / 4096));
   if (pokemon.HasStatus({ENUMS::StatusName::par}) && !pokemon.HasAbility({"Quick Feet"})) 
   {
      speed = (OF32(speed * (static_cast<int>(gen) < 7 ? 25 : 50)) / 100);
   }

   speed = std::min(static_cast<int>(gen) <= 2 ? 999 : 10000, speed);
   return std::max(0, speed);
}

void ComputeFinalStats
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon& attacker,
   Pokemon::Pokemon& defender,
   State::Field& field,
   std::vector<ENUMS::StatID> stats
)
{
   std::vector<std::pair<Pokemon::Pokemon, State::Side>> sides = 
   {
      std::make_pair(attacker, field.attacker_side), 
      std::make_pair(defender, field.defender_side)
   };

   for (auto& [pokemon, side] : sides) 
   {
      for (const auto& stat : stats) 
      {
         if (stat == ENUMS::StatID::spe) 
         {
            pokemon.SetStat(stat, GetFinalSpeed(gen, pokemon, field, side));
         } 
         else 
         {
            pokemon.SetStat
            (
               stat, 
               GetModifiedStat(pokemon.GetRawStats().at(stat), pokemon.GetBoosts().at(stat), gen)
            );
         }
      }
   }
}

int HandleFixedDamageMoves(const Pokemon::Pokemon attacker, const Move::Move move)
{
   if (move.Named({"Seismic Toss", "Night Shade"})) 
   {
      return attacker.GetLevel();
   } 
   else if (move.Named({"Dragon Rage"})) 
   {
      return 40;
   } 
   else if (move.Named({"Sonic Boom"})) 
   {
      return 20;
   }
   
   return 0;
}

float GetMoveEffectiveness
(
   const ENUMS::GenerationNumber gen,
   const Move::Move& move,
   const ENUMS::TypeName type,
   bool is_ghost_revealed,
   bool is_gravity,
   bool is_ring_tarGet
) 
{
   if ((is_ring_tarGet || is_ghost_revealed) && 
       type == ENUMS::TypeName::Ghost && 
       move.HasType({ENUMS::TypeName::Normal, ENUMS::TypeName::Fighting})) 
   {
      return 1;
   } 
   else if ((is_ring_tarGet || is_gravity) && 
            type == ENUMS::TypeName::Flying && 
            move.HasType({ENUMS::TypeName::Ground})) 
   {
      return 1;
   } 
   else if (move.Named({"Freeze-Dry"}) && type == ENUMS::TypeName::Water) 
   {
      return 2;
   } 
   else if (move.Named({"Flying Press"})) 
   {
      auto type_eff1 = Data::Types::Instance()
         .GetTypeEffectivenessByTypeAndGen(gen, ENUMS::TypeName::Fighting).at(type);
      auto type_eff2 = Data::Types::Instance()
         .GetTypeEffectivenessByTypeAndGen(gen, ENUMS::TypeName::Flying).at(type);

      return Data::Types::Instance().CalculateTypeEffectiveness(type_eff1, type_eff2);
   } 
   else 
   {
      auto type_eff = Data::Types::Instance()
         .GetTypeEffectivenessByTypeAndGen(gen, move.GetType()).at(type);

      return Data::Types::Instance().CalculateTypeEffectiveness(type_eff);
   }
}

std::string GetStatDescriptionText
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& pokemon,
   const ENUMS::StatID stat,
   const std::optional<ENUMS::NatureName> nature_name
)
{
   std::pair<ENUMS::StatIDExceptHP, ENUMS::StatIDExceptHP> nature 
      = nature_name 
      ? Data::Natures::Instance().GetNatures().at(
         Data::Natures::Instance().NatureEnumToString(nature_name.value()))
      : std::make_pair<ENUMS::StatIDExceptHP, ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::atk,
                                                                     ENUMS::StatIDExceptHP::atk);
   std::string desc = pokemon.GetEVs().at(stat) +
      (stat == ENUMS::StatID::hp || nature.first == nature.second ? ""
      : Stats::ConvertStatID(nature.first) == stat ? "+"
      : Stats::ConvertStatID(nature.second) == stat ? "-"
      : "") + std::string(" ") +
      Stats::DisplayStat(stat);
   int iv = pokemon.GetIVs().at(stat);
   if (iv != 31) desc += " " + std::to_string(iv) + " IVs";
   return desc;
}

void CheckAirLock(const Pokemon::Pokemon& pokemon, State::Field& field) 
{
   if (pokemon.HasAbility({"Air Lock", "Cloud Nine"})) 
   {
      field.weather = std::nullopt;
   }
}

void CheckForecast
(
   Pokemon::Pokemon& pokemon, 
   std::optional<ENUMS::Weather> weather
) 
{
   if (pokemon.HasAbility({"Forecast"}) && pokemon.Named({"Castform"}) && weather) 
   {
      switch (weather.value()) 
      {
      case ENUMS::Weather::Sun:
      case ENUMS::Weather::HarshSunshine:
         pokemon.SetType({ENUMS::TypeName::Fire});
         break;
      case ENUMS::Weather::Rain:
      case ENUMS::Weather::HeavyRain:
         pokemon.SetType({ENUMS::TypeName::Water});
         break;
      case ENUMS::Weather::Hail:
      case ENUMS::Weather::Snow:
         pokemon.SetType({ENUMS::TypeName::Ice});
         break;
      default:
         pokemon.SetType({ENUMS::TypeName::Normal});
      }
   }
}

void CheckIntimidate
(
   const ENUMS::GenerationNumber gen, 
   const Pokemon::Pokemon& source, 
   Pokemon::Pokemon& tarGet
) 
{
   bool blocked =
      tarGet.HasAbility({"Clear Body", "White Smoke", "Hyper Cutter", "Full Metal Body"}) ||
      // More abilities now block Intimidate in Gen 8+ (DaWoblefet, Cloudy Mistral)
      (static_cast<int>(gen) >= 8 && 
       tarGet.HasAbility({"Inner Focus", "Own Tempo", "Oblivious", "Scrappy"})) ||
      tarGet.HasItem({"Clear Amulet"});
   if (source.HasAbility({"Intimidate"}) && source.GetAbilityOn() && !blocked) 
   {
      if (tarGet.HasAbility({"Contrary", "Defiant", "Guard Dog"})) 
      {
         tarGet.SetBoost(ENUMS::StatID::atk, 
                         std::min(6, tarGet.GetBoosts().at(ENUMS::StatID::atk) + 1));
      } 
      else if (tarGet.HasAbility({"Simple"})) 
      {
         tarGet.SetBoost(ENUMS::StatID::atk, 
                         std::max(-6, tarGet.GetBoosts().at(ENUMS::StatID::atk) - 2));
      } 
      else 
      {
         tarGet.SetBoost(ENUMS::StatID::atk, 
                         std::max(-6, tarGet.GetBoosts().at(ENUMS::StatID::atk) - 1));
      }
      if (tarGet.HasAbility({"Competitive"})) 
      {
         tarGet.SetBoost(ENUMS::StatID::spa, 
                         std::min(6, tarGet.GetBoosts().at(ENUMS::StatID::spa) + 2));
      }
   }
}

// NOTE: We only need to handle guaranteed, damage-relevant boosts here for multi-hit accuracy
std::pair<bool, bool> CheckMultihitBoost
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon& attacker,
   Pokemon::Pokemon& defender,
   const Move::Move& move,
   State::Field& field,
   Description::RawDescription& desc,
   bool attacker_used_item,
   bool defender_used_item
) 
{
   // NOTE: attacker.GetAbility() must be Parental Bond for these moves to be multi-hit
   if (move.Named({"Gyro Ball", "Electro Ball"}) && defender.HasAbility({"Gooey", "Tangling Hair"})) 
   {
      // Gyro Ball (etc) makes contact into Gooey (etc) whenever its inflicting multiple hits because
      // this can only happen if the attacker ability is Parental Bond (and thus can"t be Long Reach)
      if (attacker.HasItem({"White Herb"}) && !attacker_used_item) 
      {
         desc.attacker_item = attacker.GetItem();
         attacker_used_item = true;
      } 
      else 
      {
         attacker.SetBoost(ENUMS::StatID::spe, 
                           std::max(attacker.GetBoosts().at(ENUMS::StatID::spe) - 1, -6));
         attacker.SetStat(ENUMS::StatID::spe, 
                          GetFinalSpeed(gen, attacker, field, field.attacker_side));
         desc.defender_ability = defender.GetAbility();
      }
      // BUG: Technically Sitrus/Figy Berry + Unburden can also affect the defender"s speed, but
      // this goes far beyond what we care to implement (especially once Gluttony is considered) now
   } 
   else if (move.Named({"Power-Up Punch"})) 
   {
      attacker.SetBoost(ENUMS::StatID::atk, 
                        std::min(attacker.GetBoosts().at(ENUMS::StatID::atk) + 1, 6));
      attacker.SetStat
      (
         ENUMS::StatID::atk, 
         GetModifiedStat
         (
            attacker.GetRawStats().at(ENUMS::StatID::atk), 
            attacker.GetBoosts().at(ENUMS::StatID::atk), 
            gen
         )
      );
   }

   int atk_simple = attacker.HasAbility({"Simple"}) ? 2 : 1;
   int def_simple = defender.HasAbility({"Simple"}) ? 2 : 1;

   if ((!defender_used_item) &&
       (defender.HasItem({"Luminous Moss"}) && 
        move.HasType({ENUMS::TypeName::Water})) ||
       (defender.HasItem({"Maranga Berry"}) && 
        move.GetMoveCategory() == ENUMS::MoveCategory::Special) ||
       (defender.HasItem({"Kee Berry"}) && 
        move.GetMoveCategory() == ENUMS::MoveCategory::Physical)) 
   {
      ENUMS::StatID def_stat = defender.HasItem({"Kee Berry"}) ? ENUMS::StatID::def 
                                                               : ENUMS::StatID::spd;
      if (attacker.HasAbility({"Unaware"})) 
      {
         desc.attacker_ability = attacker.GetAbility();
      } 
      else 
      {
         if (defender.HasAbility({"Contrary"})) 
         {
            desc.defender_ability = defender.GetAbility();
            if (defender.HasItem({"White Herb"}) && !defender_used_item) {
               desc.defender_item = defender.GetItem();
               defender_used_item = true;
            } 
            else 
            {
               defender.SetBoost(def_stat, std::max(-6, defender.GetBoosts().at(def_stat) - def_simple));
            }
         } 
         else 
         {
            defender.SetBoost(def_stat, std::min(6, defender.GetBoosts().at(def_stat) + def_simple));
         }
         if (def_simple == 2) desc.defender_ability = defender.GetAbility();
         defender.SetBoost
         (
            def_stat, 
            GetModifiedStat
            (  
               defender.GetRawStats().at(def_stat),
               defender.GetBoosts().at(def_stat),
               gen
            )
         );
         desc.defender_item = defender.GetItem();
         defender_used_item = true;
      }
   }

   if (defender.HasAbility({"Seed Sower"})) 
   {
      field.terrain = ENUMS::Terrain::Grassy_t;
   }
   if (defender.HasAbility({"Sand Spit"})) 
   {
      field.weather = ENUMS::Weather::Sand;
   }

   if (defender.HasAbility({"Stamina"})) 
   {
      if (attacker.HasAbility({"Unaware"})) 
      {
         desc.attacker_ability = attacker.GetAbility();
      } 
      else 
      {
         defender.SetBoost(ENUMS::StatID::def, 
                           std::min(defender.GetBoosts().at(ENUMS::StatID::def) + 1, 6));
         defender.SetStat
         (
            ENUMS::StatID::def, 
            GetModifiedStat
            (
               defender.GetRawStats().at(ENUMS::StatID::def), 
               defender.GetBoosts().at(ENUMS::StatID::def), 
               gen
            )
         );
         desc.defender_ability = defender.GetAbility();
      }
   } 
   else if (defender.HasAbility({"Water Compaction"}) && move.HasType({ENUMS::TypeName::Water})) 
   {
      if (attacker.HasAbility({"Unaware"})) 
      {
         desc.attacker_ability = attacker.GetAbility();
      } 
      else 
      {
         defender.SetBoost(ENUMS::StatID::def, 
                           std::min(defender.GetBoosts().at(ENUMS::StatID::def) + 2, 6));
         defender.SetStat
         (
            ENUMS::StatID::def, 
            GetModifiedStat
            (
               defender.GetRawStats().at(ENUMS::StatID::def), 
               defender.GetBoosts().at(ENUMS::StatID::def), 
               gen
            )
         );
         desc.defender_ability = defender.GetAbility();
      }
   } 
   else if (defender.HasAbility({"Weak Armor"})) 
   {
      if (attacker.HasAbility({"Unaware"})) 
      {
         desc.attacker_ability = attacker.GetAbility();
      } 
      else 
      {
         if (defender.HasItem({"White Herb"}) && 
             !defender_used_item && 
             defender.GetBoosts().at(ENUMS::StatID::def) == 0) 
         {
            desc.defender_item = defender.GetItem();
            defender_used_item = true;
         } 
         else 
         {
            defender.SetBoost(ENUMS::StatID::def, 
                              std::max(defender.GetBoosts().at(ENUMS::StatID::def) - 1, -6));
            defender.SetStat
            (
               ENUMS::StatID::def, 
               GetModifiedStat
               (
                  defender.GetRawStats().at(ENUMS::StatID::def), 
                  defender.GetBoosts().at(ENUMS::StatID::def), 
                  gen
               )
            );
         }
         desc.defender_ability = defender.GetAbility();
      }
      defender.SetBoost(ENUMS::StatID::spe, 
                        std::min(defender.GetBoosts().at(ENUMS::StatID::spe) + 2, 6));
      defender.SetStat(ENUMS::StatID::spe, 
                       GetFinalSpeed(gen, defender, field, field.defender_side));
   }

   if (move.GetDropsStats()) 
   {
      if (attacker.HasAbility({"Unaware"})) 
      {
         desc.attacker_ability = attacker.GetAbility();
      } 
      else 
      {
         // No move with GetDropsStats() Has fancy logic regarding category here
         ENUMS::StatID stat = move.GetMoveCategory() == ENUMS::MoveCategory::Special 
            ? ENUMS::StatID::spa 
            : ENUMS::StatID::atk;

         int boosts = attacker.GetBoosts().at(stat);
         if (attacker.HasAbility({"Contrary"})) 
         {
            boosts = std::min(6, boosts + *move.GetDropsStats());
            desc.attacker_ability = attacker.GetAbility();
         } 
         else 
         {
            boosts = std::max(-6, boosts - *move.GetDropsStats() * atk_simple);
         }
         if (atk_simple == 2) desc.attacker_ability = attacker.GetAbility();

         if (attacker.HasItem({"White Herb"}) && attacker.GetBoosts().at(stat) < 0 && !attacker_used_item) 
         {
            boosts += *move.GetDropsStats() * atk_simple;
            desc.attacker_item = attacker.GetItem();
            attacker_used_item = true;
         }

         attacker.SetBoost(stat, boosts);
         attacker.SetStat
         (
            stat, 
            GetModifiedStat
            (
               attacker.GetRawStats().at(stat), 
               defender.GetBoosts().at(stat), 
               gen
            )
         );
      }
   }

   // Do ability swap after all other effects
   if (defender.HasAbility({"Mummy", "Wandering Spirit", "Lingering Aroma"}) && 
       move.GetMoveFlags().contact) 
   {
      std::string old_attacker_ability = attacker.GetAbility();
      attacker.SetAbility(defender.GetAbility());
      // If attacker ability is notable, then ability swap is notable.
      if (desc.attacker_ability) 
      {
         desc.defender_ability = defender.GetAbility();
      }
      if (defender.HasAbility({"Wandering Spirit"})) 
      {
         defender.SetAbility(old_attacker_ability);
      }
   }

   return std::make_pair(attacker_used_item, defender_used_item);
}

void CheckItem(Pokemon::Pokemon& pokemon, bool magic_room_active) 
{
   // Pokemon with Klutz still Get their speed dropped in generation 4
   if (pokemon.GetGeneration() == ENUMS::GenerationNumber::__4 && 
       pokemon.HasItem({"Iron Ball"})) return;
   if 
   (
      pokemon.HasAbility({"Klutz"}) && 
      std::find(EV_ITEMS.begin(), EV_ITEMS.end(), pokemon.GetItem()) == EV_ITEMS.end() ||
      magic_room_active
   ) 
   {
      pokemon.SetItem("");
   }
}

void CheckDownload
(
   Pokemon::Pokemon& source, 
   Pokemon::Pokemon& target, 
   bool wonder_room_active
)
{
   if (source.HasAbility({"Download"})) 
   {
      int def = target.GetStats().at(ENUMS::StatID::def);
      int spd = target.GetStats().at(ENUMS::StatID::spd);
      // We swap the defense stats again here since Download ignores Wonder Room
      if (wonder_room_active) 
      {
         int temp_def = def;
         def = spd;
         spd = temp_def;
      }
      if (spd <= def) 
      {
         source.SetBoost(ENUMS::StatID::spa, 
                         std::min(6, source.GetBoosts().at(ENUMS::StatID::spa) + 1));
      } 
      else 
      {
         source.SetBoost(ENUMS::StatID::atk,
                         std::min(6, source.GetBoosts().at(ENUMS::StatID::atk) + 1));
      }
   }
}

int CountBoosts(const ENUMS::GenerationNumber gen, const ENUMS::StatsTable& boosts) 
{
  int sum = 0;

   std::vector<ENUMS::StatID> STATS = gen == ENUMS::GenerationNumber::__1
      ? std::vector<ENUMS::StatID>
      { 
         ENUMS::StatID::atk, 
         ENUMS::StatID::def, 
         ENUMS::StatID::spa, 
         ENUMS::StatID::spe
      }
      : std::vector<ENUMS::StatID>
      { 
         ENUMS::StatID::atk, 
         ENUMS::StatID::def, 
         ENUMS::StatID::spa, 
         ENUMS::StatID::spd,
         ENUMS::StatID::spe
      };

  for (auto stat : STATS) 
  {
    // Only positive boosts are counted
    int boost = boosts.at(stat);
    if (boost && boost > 0) sum += boost;
  }
  
  return sum;
}

void CheckWonderRoom(Pokemon::Pokemon& pokemon, bool wonder_room_active) 
{
   if (wonder_room_active) 
   {
      int temp_def = pokemon.GetRawStats().at(ENUMS::StatID::def);
      pokemon.SetRawStat(ENUMS::StatID::def, pokemon.GetRawStats().at(ENUMS::StatID::spd));
      pokemon.SetRawStat(ENUMS::StatID::spd, temp_def);
   }
}

void CheckSeedBoost(Pokemon::Pokemon& pokemon, const State::Field& field) 
{
   if (!pokemon.GetItem()) return;

   if (field.terrain && pokemon.GetItem() && 
       pokemon.GetItem().value().find("Seed") != std::string::npos) 
   {
      ENUMS::Terrain terrain_seed = Util::CSV::StringToTerrain
      (
         pokemon.GetItem().value().substr(0, pokemon.GetItem().value().find(" "))
      ).value();
      if (field.HasTerrain({terrain_seed})) 
      {
         if (terrain_seed == ENUMS::Terrain::Grassy_t || terrain_seed == ENUMS::Terrain::Electric_t) 
         {
            pokemon.SetBoost(ENUMS::StatID::def, pokemon.HasAbility({"Contrary"})
               ? std::max(-6, pokemon.GetBoosts().at(ENUMS::StatID::def) - 1)
               : std::min(6, pokemon.GetBoosts().at(ENUMS::StatID::def)  + 1));
         } 
         else 
         {
            pokemon.SetBoost(ENUMS::StatID::spd, pokemon.HasAbility({"Contrary"})
               ? std::max(-6, pokemon.GetBoosts().at(ENUMS::StatID::spd) - 1)
               : std::min(6, pokemon.GetBoosts().at(ENUMS::StatID::spd)  + 1));
         }
         pokemon.SetItem("");
      }
   }
}

void CheckInfiltrator(const Pokemon::Pokemon& pokemon, State::Side& affected_side) 
{
   if (pokemon.HasAbility({"Infiltrator"})) 
   {
      affected_side.is_reflect = false;
      affected_side.is_light_screen = false;
      affected_side.is_aurora_veil = false;
   }
}

bool IsGrounded(const Pokemon::Pokemon& pokemon, const State::Field& field) 
{
   return (field.is_gravity || pokemon.HasItem({"Iron Ball"}) ||
           (!pokemon.HasType({ENUMS::TypeName::Flying}) &&
           !pokemon.HasAbility({"Levitate"}) &&
           !pokemon.HasItem({"Air Balloon"})));
}

// "true" in "role" means attacker.
float GetWeight(const Pokemon::Pokemon& pokemon, Description::RawDescription& desc, bool role) 
{
   float weight_hg = pokemon.GetWeight() * 10;
   float ability_factor = pokemon.HasAbility({"Heavy Metal"}) ? 2
      : pokemon.HasAbility({"Light Metal"}) ? 0.5
      : 1;
   if (ability_factor != 1) 
   {
      weight_hg = std::max(static_cast<int>(std::floor(weight_hg * ability_factor)), 1);
      if (role)
      {
         desc.attacker_ability = pokemon.GetAbility();
      }
      else
      {
         desc.defender_ability = pokemon.GetAbility();
      }
   }

   if (pokemon.HasItem({"Float Stone"})) 
   {
      weight_hg = std::max(static_cast<int>(std::floor(weight_hg * 0.5)), 1);
      if (role)
      {
         desc.attacker_item = pokemon.GetItem();
      }
      else
      {
         desc.defender_item = pokemon.GetItem();
      }
   }

   // convert back to kg
   return weight_hg / 10;
}

int GetBaseDamage(const int level, const int base_power, const int attack, const int defense) 
{
  return OF32((OF32(OF32(((2 * level) / 5 + 2) * base_power) * attack) / defense) / 50 + 2);
}

int GetStabMod
(
   const Pokemon::Pokemon& pokemon, 
   const Move::Move& move, 
   Description::RawDescription& desc
) 
{
   int stab_mod = 4096;
   if (pokemon.HasOriginalType({move.GetType()})) 
   {
      stab_mod += 2048;
   } 
   else if (pokemon.HasAbility({"Protean", "Libero"}) && !pokemon.GetTeraType()) 
   {
      stab_mod += 2048;
      desc.attacker_ability = pokemon.GetAbility();
   }
   if (pokemon.GetTeraType() && 
       *pokemon.GetTeraType() == move.GetType() && 
       *pokemon.GetTeraType() != ENUMS::TypeName::Stellar) 
   {
      stab_mod += 2048;
      desc.attacker_tera = Data::Types::Instance().TypeNameENUMToString(*pokemon.GetTeraType());
   }
   if (pokemon.HasAbility({"Adaptability"}) && pokemon.HasType({move.GetType()})) 
   {
      stab_mod += *pokemon.GetTeraType() && 
                  pokemon.HasOriginalType({*pokemon.GetTeraType()}) 
                     ? 1024 : 2048;
      desc.attacker_ability = pokemon.GetAbility();
   }
   return stab_mod;
}

int GetFinalDamage
(
   const int base_amount,
   const int i,
   const float effectiveness,
   bool is_burned,
   const int stab_mod,
   const int final_mod,
   bool protect
) 
{
   int damage_amount = (OF32(base_amount * (85 + i)) / 100);
   // If the stab_mod would not accomplish anything we avoid applying it because it could cause
   // us to calculate damage overflow incorrectly (DaWoblefet)
   if (stab_mod != 4096) damage_amount = OF32(damage_amount * stab_mod) / 4096;
   damage_amount = (OF32(PokeRound(damage_amount) * effectiveness));

   if (is_burned) damage_amount = (damage_amount / 2);
   if (protect) damage_amount = PokeRound(OF32(damage_amount * 1024) / 4096);
   return OF16(PokeRound(std::max(1, OF32(damage_amount * final_mod) / 4096)));
}

void CheckTeraformZero(const Pokemon::Pokemon& pokemon, State::Field& field) 
{
   if (pokemon.HasAbility({"Teraform Zero"}) && pokemon.GetAbilityOn()) 
   {
      field.weather = std::nullopt;
      field.terrain = std::nullopt;
   }
}

void CheckIntrepidSword(Pokemon::Pokemon& source, const ENUMS::GenerationNumber gen) 
{
   if (source.HasAbility({"Intrepid Sword"}) && static_cast<int>(gen) > 7) 
   {
      source.SetBoost(ENUMS::StatID::atk, 
                      std::min(6, source.GetBoosts().at(ENUMS::StatID::atk) + 1));
   }
}

void CheckDauntlessShield(Pokemon::Pokemon& source, const ENUMS::GenerationNumber gen) 
{
   if (source.HasAbility({"Dauntless Shield"}) && static_cast<int>(gen) > 7) 
   {
      source.SetBoost(ENUMS::StatID::def, 
                      std::min(6, source.GetBoosts().at(ENUMS::StatID::def) + 1));
   }
}

void CheckWindRider(Pokemon::Pokemon& source, const State::Side& attacking_side) 
{
   if (source.HasAbility({"Wind Rider"}) && 
       attacking_side.is_tailwind && 
       *attacking_side.is_tailwind) 
   {
      source.SetBoost(ENUMS::StatID::atk, 
                      std::min(6, source.GetBoosts().at(ENUMS::StatID::atk) + 1));
   }
}

void CheckEmbody(Pokemon::Pokemon& source, const ENUMS::GenerationNumber gen)
{
   if (static_cast<int>(gen) < 9) return;

   if (source.GetAbility() == "Embody Aspect (Cornerstone)")
   {
      source.SetBoost(ENUMS::StatID::def, 
                      std::min(6, source.GetBoosts().at(ENUMS::StatID::def) + 1));
   }
   else if (source.GetAbility() == "Embody Aspect (Hearthflame)")
   {
      source.SetBoost(ENUMS::StatID::atk, 
                      std::min(6, source.GetBoosts().at(ENUMS::StatID::atk) + 1));
   }
   else if (source.GetAbility() == "Embody Aspect (Teal)")
   {
      source.SetBoost(ENUMS::StatID::spe, 
                      std::min(6, source.GetBoosts().at(ENUMS::StatID::spe) + 1));
   }
   else if (source.GetAbility() == "Embody Aspect (Wellspring)")
   {
      source.SetBoost(ENUMS::StatID::spd, 
                      std::min(6, source.GetBoosts().at(ENUMS::StatID::spd) + 1));
   }
}

/**
 * Determines which move category Shell Side Arm should behave as.
 *
 * A simplified formula can be used here compared to what the research
 * suggests as we do not want to implement the random tiebreak element of
 * move - instead we simply default to 'Special' and allow the user to override
 * this by manually adjusting the move's category.
 *
 * See also:
 * {@link https://github.com/smogon/pokemon-showdown/commit/65d2bb5d}
 *
 * @param source Attacking pokemon (after stat modifications)
 * @param target Target pokemon (after stat modifications)
 * @returns 'Physical' | 'Special'
 */
ENUMS::MoveCategory GetShellSideArmCategory
(
   const Pokemon::Pokemon& source, 
   const Pokemon::Pokemon& target
) 
{
  int physical_damage = source.GetStats().at(ENUMS::StatID::atk) / 
                        target.GetStats().at(ENUMS::StatID::def);
  int special_damage = source.GetStats().at(ENUMS::StatID::spa) / 
                       target.GetStats().at(ENUMS::StatID::spd);
  return physical_damage > special_damage ? ENUMS::MoveCategory::Physical 
                                          : ENUMS::MoveCategory::Special;
}

int GetStellarStabMod
(
   const Pokemon::Pokemon& pokemon, 
   const Move::Move& move, 
   int stab_mod, 
   int turns
) 
{
   bool is_stellar_boosted =
      pokemon.GetTeraType() && *pokemon.GetTeraType() == ENUMS::TypeName::Stellar &&
      ((move.GetIsStellarFirstUse() && turns == 0) || pokemon.Named({"Terapagos-Stellar"}));
   if (is_stellar_boosted) 
   {
      if (pokemon.HasOriginalType({move.GetType()})) 
      {
         stab_mod += 2048;
      } 
      else 
      {
         stab_mod = 4915;
      }
   }
   return stab_mod;
}

}
}