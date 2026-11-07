#include "./../include/description.hpp"

#include "./../include/util/util.h"
#include "./../include/data/types.h"

namespace PokemonDamageCalcCPP
{
namespace Description
{

DamageRangeResult DamageRange(const Damage& damage)
{
   return std::visit
   (
      [](const auto& d) -> DamageRangeResult
      {
         using T = std::decay_t<decltype(d)>;

         // Fixed Damage
         if constexpr (std::is_same_v<T, int>)
         {
            return std::pair<int, int>{d, d};
         }

         // Standard Damage
         else if constexpr (std::is_same_v<T, std::vector<int>>)
         {
            if (d.empty())
            {
               return std::pair<int, int>{0, 0};
            }

            if (d.front() > d.back())
            {
               auto [min_it, max_it] = std::minmax_element(d.begin(), d.end());
               return std::pair<int, int>{*min_it, *max_it};
            }

            return std::pair<int, int>{d.front(), d.back()};
         }

         // Fixed Parental Bond Damage
         else if constexpr (std::is_same_v<T, std::pair<int, int>>)
         {
            return std::pair
            <
               std::pair<int, int>,
               std::pair<int, int>
            >
            {
               {d.first, d.second},
               {d.first, d.second}
            };
         }

         // Parental Bond Damage
         else if constexpr 
         (
            std::is_same_v
            <
               T,
               std::pair<std::vector<int>, std::vector<int>>
            >
         )
         {
            auto left = d.first;
            auto right = d.second;

            if (left.front() > left.back())
            {
               std::sort(left.begin(), left.end());
            }

            if (right.front() > right.back())
            {
               std::sort(right.begin(), right.end());
            }

            return std::pair
            <
               std::pair<int, int>,
               std::pair<int, int>
            >
            {
               {left.front(), right.front()},
               {left.back(), right.back()}
            };
         }
      },
      damage
   );
}

int ToDisplay
(
   const std::string& notation, 
   const int a, 
   const int b, 
   const int f
)
{
   return notation == "%" ? (((a * (1000 / f)) / b) / 10) 
                          : (((a * (48 / f)) / b));
}

std::pair<std::string, std::string> GetDescriptionLevels
(
   const Pokemon::Pokemon& attacker, 
   const Pokemon::Pokemon& defender
)
{
   if (attacker.GetLevel() != defender.GetLevel())
   {
      return
      {
         attacker.GetLevel() == 100 ? "" : "Lvl " + std::to_string(attacker.GetLevel()),
         defender.GetLevel() == 100 ? "" : "Lvl " + std::to_string(defender.GetLevel())
      };
   }

   // There's an argument for showing any level that's not 100, but VGC and LC
   // players probably would rather not see level cruft in their calcs.
   const bool elide = attacker.GetLevel() == 100 ||
                      attacker.GetLevel() == 50 ||
                      attacker.GetLevel() == 5;

   const std::string level = elide ? "" : "Lvl " + std::to_string(attacker.GetLevel());

   return {level, level};
}

std::string BuildDescription
(
   const RawDescription& description,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender
)
{
   const auto [attacker_level, defender_level] = GetDescriptionLevels(attacker, defender);

   std::string output;
   if (description.attack_boost)
   {
      if (*description.attack_boost > 0)
      {
         output += '+';
      }

      output += std::to_string(*description.attack_boost) + " ";
   }
   if (!attacker_level.empty())
   {
      output += attacker_level + " ";
   }

   output = Util::AppendIfSet(output, description.attack_evs);
   output = Util::AppendIfSet(output, description.attacker_item);
   output = Util::AppendIfSet(output, description.attacker_ability);
   output = Util::AppendIfSet(output, description.rivalry);

   if (description.is_burned)
   {
      output += "burned ";
   }
   if (description.allies_fainted)
   {
      output += std::to_string(std::min(5, *description.allies_fainted));
      output += (*description.allies_fainted == 1)
         ? " ally fainted "
         : " allies fainted ";
   }
   if (description.attacker_tera)
   {
      output += "Tera " + *description.attacker_tera + " ";
   }
   if (description.is_stellar_first_use)
   {
      output += "(First Use) ";
   }
   if (description.is_beads_of_ruin)
   {
      output += "Beads of Ruin ";
   }
   if (description.is_sword_of_ruin)
   {
      output += "Sword of Ruin ";
   }

   output += description.attacker_name + " ";

   if (description.is_helping_hand)
   {
      output += "Helping Hand ";
   }
   if (description.is_flower_gift_attacker)
   {
      output += "with an ally's Flower Gift ";
   }
   if (description.is_battery)
   {
      output += "Battery boosted ";
   }
   if (description.is_power_spot)
   {
      output += "Power Spot boosted ";
   }
   if (description.is_switching)
   {
      output += "switching boosted ";
   }

   output += description.move_name + " ";

   if (description.move_bp && description.move_type)
   {
      output += "(" +
         std::to_string(*description.move_bp) +
         " BP " +
         Data::Types::Instance().TypeNameENUMToString(*description.move_type) +
         ") ";
   }
   else if (description.move_bp)
   {
      output += "(" +
         std::to_string(*description.move_bp) +
         " BP) ";
   }
   else if (description.move_type)
   {
      output += "(" +
         Data::Types::Instance().TypeNameENUMToString(*description.move_type) +
         ") ";
   }

   if (description.hits)
   {
      output += "(" +
         std::to_string(*description.hits) +
         " hits) ";
   }

   output = Util::AppendIfSet(output, description.move_turns);

   output += "vs. ";

   if (description.defense_boost)
   {
      if (*description.defense_boost > 0)
      {
         output += '+';
      }

      output += std::to_string(*description.defense_boost) + " ";
   }

   if (!defender_level.empty())
   {
      output += defender_level + " ";
   }

   output = Util::AppendIfSet(output, description.hp_evs);

   if (description.defense_evs)
   {
      output += "/ " + *description.defense_evs + " ";
   }

   output = Util::AppendIfSet(output, description.defender_item);
   output = Util::AppendIfSet(output, description.defender_ability);

   if (description.is_tablets_of_ruin)
   {
      output += "Tablets of Ruin ";
   }
   if (description.is_vessel_of_ruin)
   {
      output += "Vessel of Ruin ";
   }
   if (description.is_protected)
   {
      output += "protected ";
   }
   if (description.is_defender_dynamaxed)
   {
      output += "Dynamax ";
   }
   if (description.defender_tera)
   {
      output += "Tera " + *description.defender_tera + " ";
   }

   output += description.defender_name;

   if (description.weather)
   {
      if (!description.terrain)
      {
         output += " in " + ENUMS::WeatherENUMToString(*description.weather);
      }
   }
   else if (description.terrain)
   {
      output +=
         " in " +
         ENUMS::TerrainENUMToString(*description.terrain) +
         " Terrain";
   }
   if (description.is_reflect)
   {
      output += " through Reflect";
   }
   else if (description.is_light_screen)
   {
      output += " through Light Screen";
   }
   if (description.is_flower_gift_defender)
   {
      output += " with an ally's Flower Gift";
   }
   if (description.is_friend_guard)
   {
      output += " with an ally's Friend Guard";
   }
   if (description.is_aurora_veil)
   {
      output += " with an ally's Aurora Veil";
   }
   if (description.is_critical)
   {
      output += " on a critical hit";
   }
   if (description.is_wonder_room)
   {
      output += " in Wonder Room";
   }

   return output;
}

std::vector<int> Combine(const Damage& damage)
{
    return std::visit([](const auto& d) -> std::vector<int>
    {
        using T = std::decay_t<decltype(d)>;

        if constexpr (std::is_same_v<T, int>)
        {
            // Fixed Damage
            return { d };
        }
        else if constexpr (std::is_same_v<T, std::vector<int>>)
        {
            // Standard Damage
            auto result = d;

            if (result.size() > 2 &&
                result.front() > result.back())
            {
                std::sort(result.begin(), result.end());
            }

            return result;
        }
        else if constexpr (std::is_same_v<T, std::pair<int, int>>)
        {
            // Fixed Parental Bond Damage
            return { d.first + d.second };
        }
        else if constexpr (std::is_same_v<T,
            std::pair<std::vector<int>, std::vector<int>>>)
        {
            // Parental Bond Damage
            std::vector<int> combined;

            combined.reserve(d.first.size() * d.second.size());

            for (int a : d.first)
            {
                for (int b : d.second)
                {
                    combined.push_back(a + b);
                }
            }

            std::sort(combined.begin(), combined.end());
            return combined;
        }
    }, damage);
}

std::pair<int, std::vector<std::string>> GetHazards
(
   const ENUMS::GenerationNumber& gen,
   const Pokemon::Pokemon& defender,
   const State::Side& defender_side
)
{
   int damage = 0;
   std::vector<std::string> texts{};

   if (defender.HasItem({"Heavy-Duty Boots"})) 
   {
      return {damage, texts};
   }

   if (defender_side.is_sr && defender_side.is_sr.value() && 
      !defender.HasAbility({"Magic Guard", "Mountaineer"}))
   {
      const auto& rock_type 
         = Data::Types::Instance().GetTypeEffectivenessByTypeAndGen(gen, ENUMS::TypeName::Rock);

      double effectiveness = defender.GetTypes().size() > 1
         ? Data::Types::Instance().CalculateTypeEffectiveness
         (
            rock_type.at(defender.GetTypes().at(0)), 
            rock_type.at(defender.GetTypes().at(1))
         )
         : Data::Types::Instance().CalculateTypeEffectiveness
         (
            rock_type.at(defender.GetTypes().at(0))
         );

      damage += static_cast<int>(std::floor(effectiveness * defender.MaxHP() / 8.0));

      texts.push_back("Stealth Rock");
   }

   if (defender_side.steelsurge &&
       !defender.HasAbility({"Magic Guard", "Mountaineer"}))
   {
      const auto& steel_type 
         = Data::Types::Instance().GetTypeEffectivenessByTypeAndGen(gen, ENUMS::TypeName::Steel);

      double effectiveness = defender.GetTypes().size() > 1
         ? Data::Types::Instance().CalculateTypeEffectiveness
         (
            steel_type.at(defender.GetTypes().at(0)), 
            steel_type.at(defender.GetTypes().at(1))
         )
         : Data::Types::Instance().CalculateTypeEffectiveness
         (
            steel_type.at(defender.GetTypes().at(0))
         );

      damage += static_cast<int>(std::floor(effectiveness * defender.MaxHP() / 8.0));

      texts.push_back("Steelsurge");
   }

   if (!defender.HasType({ENUMS::TypeName::Flying}) &&
       !defender.HasAbility({"Magic Guard", "Levitate"}) &&
       !defender.HasItem({"Air Balloon"}))
   {
      if (defender_side.spikes == 1)
      {
         damage += defender.MaxHP() / 8;

         if (static_cast<int>(gen) == 2)
            texts.push_back("Spikes");
         else
            texts.push_back("1 layer of Spikes");
      }
      else if (defender_side.spikes == 2)
      {
         damage += defender.MaxHP() / 6;
         texts.push_back("2 layers of Spikes");
      }
      else if (defender_side.spikes == 3)
      {
         damage += defender.MaxHP() / 4;
         texts.push_back("3 layers of Spikes");
      }
   }

   // TypeScript's isNaN() guard.
   // If damage remains an int in C++, this can never happen.
   // If you switch damage to double, use std::isnan().
   return {damage, texts};
}

float ComputeKOChance
(
   const std::vector<int>& damage,
   const int hp,
   const int eot,
   const int hits,
   const int times_used,
   const int max_hp,
   int toxic_counter
) 
{
   const int n = damage.size();
   if (hits == 1) 
   {
      for (int i = 0; i < n; i++) 
      {
         if (damage[n - 1] < hp) return 0;
         if (damage[i] >= hp)
         { 
            return (static_cast<float>(n) - static_cast<float>(i)) / static_cast<float>(n); 
         }
      }
   }

   int toxic_damage = 0;
   if (toxic_counter > 0) 
   {
      toxic_damage = ((toxic_counter * max_hp) / 16.0);
      toxic_counter++;
   }
   float sum = 0.0;
   float lastc = 0.0;
   for (int i = 0; i < n; i++) 
   {
      float c;
      if (i == 0 || damage[i] != damage[i - 1]) 
      {
         c = ComputeKOChance
         (
            damage,
            hp - damage[i] + eot - toxic_damage,
            eot,
            hits - 1,
            times_used,
            max_hp,
            toxic_counter
         );
      } 
      else 
      {
         c = lastc;
      }
      
      if (c == 1) 
      {
         sum += n - i;
         break;
      } 
      else 
      {
         sum += c;
      }
      lastc = c;
   }
   return static_cast<float>(sum) / static_cast<float>(n);
}

int PredictTotal
(
   const int damage,
   const int eot,
   const int hits,
   const int times_used,
   const int toxic_counter,
   const int max_hp
) 
{
   int toxic_damage = 0;
   if (toxic_counter > 0) 
   {
      for (int i = 0; i < hits - 1; i++) 
      {
         toxic_damage += (((toxic_counter + i) * max_hp) / 16);
      }
   }
   int total = 0;
   if (hits > 1 && times_used == 1) 
   {
      total = damage * hits - eot * (hits - 1) + toxic_damage;
   } 
   else 
   {
      total = damage - eot * (hits - 1) + toxic_damage;
   }
   return total;
}

KOChanceHelper GetKOChance
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   Move::Move& move,
   const State::Field& field,
   const Damage& damage,
   bool err
) 
{
   std::vector<int> new_damage = Combine(damage);
   if (new_damage[new_damage.size() - 1] == 0) 
   {
      return {.chance = 0, .n = 0, .text = ""};
   }

   // Code doesn't really work if these aren't set.
   if (move.GetTimesUsed() == 0) move.IncrementTimesUsed();
   if (move.GetTimesUsedWithMetronome() == 0) move.IncrementTimesUsedWithMetronome();

   if (new_damage[0] >= defender.MaxHP() && move.GetTimesUsed() == 1 && move.GetTimesUsedWithMetronome() == 1) 
   {
      return {.chance = 1, .n = 1, .text = "guaranteed OHKO"};
   }

   std::pair<int, std::vector<std::string>> hazards = GetHazards(gen, defender, field.defender_side);
   std::pair<int, std::vector<std::string>> eot = GetEndOfTurn(gen, attacker, defender, move, field);
   int toxic_counter = defender.HasStatus({ENUMS::StatusName::tox}) && 
                       !defender.HasAbility({"Magic Guard"}) ? defender.GetToxicCounter() : 0;

   // multi-hit moves have too many possibilities for brute-forcing to work, so reduce it
   // to an approximate distribution
   std::string qualifier = move.GetHits() && move.GetHits().value() > 1 ? "approx. " : "";

   const std::string hazards_text = hazards.second.size() > 0
      ? " after " + Util::SerializeText(hazards.second)
      : "";

   std::string after_text;
   if (!hazards.second.empty() || !eot.second.empty()) 
   {
      std::vector<std::string> texts = hazards.second;
      texts.insert(texts.end(), eot.second.begin(), eot.second.end());

      after_text = " after " + Util::SerializeText(texts);
   }

   auto KOChance = [&]
   (
      std::optional<float> chance,
      int n,
      bool multiple_turns = false
   ) -> KOChanceHelper
   {
      if (chance.has_value() && *chance == 0.0) 
      {
         return {.chance = std::nullopt, .n = n, .text = qualifier + "not a KO"};
      }

      std::string text;

      if (!chance.has_value()) 
      {
         text = qualifier + "possible ";
      } 
      else if (*chance == 1.0) 
      {
         text = qualifier.empty() ? "guaranteed " : qualifier;
      } 
      else 
      {
         float pct = std::max(std::min(std::round(*chance * 1000.0), 999.0), 1.0) / 10.0;

         text = qualifier + std::to_string(pct) + "% chance to ";
      }

      if (n == 1) 
      {
         text += "OHKO" + hazards_text;
      } 
      else 
      {
         text += (multiple_turns
                  ? "KO in " + std::to_string(n) + " turns"
                  : std::to_string(n) + "HKO")
                  + after_text;
      }

      return {chance, n, text};
   };

   if ((move.GetTimesUsed() == 1 && move.GetTimesUsedWithMetronome() == 1) || move.GetIsZ()) 
   {
      float chance = ComputeKOChance
      (
         new_damage, 
         defender.CurHP() - hazards.first, 
         0, 
         1, 
         1, 
         defender.MaxHP(), 
         toxic_counter
      );
      // note: still not accounting for EOT due to poor eot damage handling
      if (chance > 0) return KOChance(chance, 1);

      // Parental Bond's combined first + second hit only is accurate for chance to OHKO, for
      // multihit KOs its only approximated. We should be doing squashMultihit here instead of
      // pretending we ar emore accurate than we are, but just throwing on an qualifer should be
      // sufficient.
      if (new_damage.size() == 256) 
      {
         qualifier = "approx. ";
         // damage = squashMultihit(gen, damage, move.hits, err);
      }

      for (int i = 2; i <= 4; i++) 
      {
         float chance = ComputeKOChance
         (
            new_damage, 
            defender.CurHP() - hazards.first, 
            eot.first, 
            i,
            1, 
            defender.MaxHP(), 
            toxic_counter
         );
         if (chance > 0) return KOChance(chance, i);
      }

      for (int i = 5; i <= 9; i++) 
      {
         if (PredictTotal
            (
               new_damage[0], 
               eot.first, 
               i, 
               1, 
               toxic_counter, 
               defender.MaxHP()
            ) >= defender.CurHP() - hazards.first) 
         {
            return KOChance(1, i);
         } 
         else if (PredictTotal
            (
               new_damage[new_damage.size() - 1], 
               eot.first, 
               i, 
               1, 
               toxic_counter, 
               defender.MaxHP()
            ) >= defender.CurHP() - hazards.first
         ) 
         {
            // possible but no concrete chance
            return KOChance(std::nullopt, i);
         }
      }
   } 
   else 
   {
      int chance = ComputeKOChance
      (
         new_damage, 
         defender.MaxHP() - hazards.first,
         eot.first,
         move.GetHits() ? move.GetHits().value() : 1,
         move.GetTimesUsed(),
         defender.MaxHP(),
         toxic_counter
      );
      if (chance > 0) return KOChance(chance, move.GetTimesUsed(), chance == 1);

      if (PredictTotal
         (
            new_damage[0],
            eot.first,
            1,
            move.GetTimesUsed(),
            toxic_counter,
            defender.MaxHP()
         ) >= defender.CurHP() - hazards.first
      ) 
      {
         return KOChance(1, move.GetTimesUsed(), true);
      } 
      else if (PredictTotal
         (
            new_damage[new_damage.size() - 1],
            eot.first,
            1,
            move.GetTimesUsed(),
            toxic_counter,
            defender.MaxHP()
         ) >= defender.CurHP() - hazards.first
      ) 
      {
         // possible but no real idea
         return KOChance(std::nullopt, move.GetTimesUsed(), true);
      }
      return KOChance(0, move.GetTimesUsed());
   }

   return {.chance = 0, .n = 0, .text =  ""};
}

std::string Display
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   Move::Move& move,
   const State::Field& field,
   const Damage& damage,
   const RawDescription& raw_description,
   const std::string& notation,
   bool err
)
{
   auto range = DamageRange(damage);

   int min_damage = 0;
   int max_damage = 0;

   std::visit
   (
      [&](const auto& r)
      {
         using T = std::decay_t<decltype(r)>;

         // pair<int, int>
         if constexpr (std::is_same_v<T, std::pair<int, int>>)
         {
            min_damage = r.first;
            max_damage = r.second;
         }

         // pair<pair<int,int>, pair<int,int>>
         else
         {
            min_damage = r.first.first + r.first.second;
            max_damage = r.second.first + r.second.second;
         }
      },
      range
   );

   const int min_display = ToDisplay(notation, min_damage, defender.MaxHP());
   const int max_display = ToDisplay(notation, max_damage, defender.MaxHP());
   const std::string desc = BuildDescription(raw_description, attacker, defender);

   const std::string damage_text = std::to_string(min_damage) + "-" +
                                   std::to_string(max_damage) + " (" + 
                                   std::to_string(min_display) + " - " +
                                   std::to_string(max_display) + notation + ")";

   if (move.GetMoveCategory() == ENUMS::MoveCategory::Status && !move.Named({"Nature Power"}))
   {
      return desc + ": " + damage_text;
   }

   const std::string ko_chance_text =
      GetKOChance
      (
         gen,
         attacker,
         defender,
         move,
         field,
         damage,
         err
      ).text;

   if (!ko_chance_text.empty())
   {
      return desc + ": " + damage_text + " -- " + ko_chance_text;
   }

   return desc + ": " + damage_text;
}

bool IsGrounded(const Pokemon::Pokemon& pokemon, const State::Field& field)
{
   return 
   (
      field.is_gravity || 
      pokemon.HasItem({"Iron Ball"}) ||
      (
         !pokemon.HasType({ENUMS::TypeName::Flying}) &&
         !pokemon.HasAbility({"Levitate"}) &&
         !pokemon.HasItem({"Air Balloon"})
      )
   );
}

std::pair<int, std::vector<std::string>> GetEndOfTurn
(
   const ENUMS::GenerationNumber& gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field
)
{
   int g = static_cast<int>(gen);
   
   int damage = 0;
   std::vector<std::string> texts{};

   auto hp_frac = [](const Pokemon::Pokemon& p, int denom) -> int 
   {
      return p.MaxHP() / denom;
   };

   // Weather
   if (field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine})) 
   {
      if (defender.HasAbility({"Dry Skin", "Solar Power"})) 
      {
         damage -= hp_frac(defender, 8);
         texts.push_back(defender.GetAbility() + " damage");
      }
   }
   else if (field.HasWeather({ENUMS::Weather::Rain, ENUMS::Weather::HeavyRain})) 
   {
      if (defender.HasAbility({"Dry Skin"})) 
      {
         damage += hp_frac(defender, 8);
         texts.push_back("Dry Skin recovery");
      }
      else if (defender.HasAbility({"Rain Dish"})) 
      {
         damage += hp_frac(defender, 16);
         texts.push_back("Rain Dish recovery");
      }
   }
   else if (field.HasWeather({ENUMS::Weather::Sand})) 
   {
      if (!defender.HasType({ENUMS::TypeName::Rock, 
                             ENUMS::TypeName::Ground, 
                             ENUMS::TypeName::Steel}) &&
          !defender.HasAbility({"Magic Guard", 
                                "Overcoat",
                                "Sand Force", 
                                "Sand Rush", 
                                "Sand Veil"}) &&
         !defender.HasItem({"Safety Goggles"}))
      {
         damage -= hp_frac(defender, g == 2 ? 8 : 16);
         texts.push_back("sandstorm damage");
      }
   }
   else if (field.HasWeather({ENUMS::Weather::Hail, ENUMS::Weather::Snow})) 
   {
      if (defender.HasAbility({"Ice Body"})) 
      {
         damage += hp_frac(defender, 16);
         texts.push_back("Ice Body recovery");
      }
      else if (!defender.HasType({ENUMS::TypeName::Ice}) &&
               !defender.HasAbility({"Magic Guard", "Overcoat", "Snow Cloak"}) &&
               !defender.HasItem({"Safety Goggles"}) &&
               field.HasWeather({ENUMS::Weather::Hail}))
      {
         damage -= hp_frac(defender, 16);
         texts.push_back("hail damage");
      }
   }

   // Items
   bool lose_item = move.Named({"Knock Off"}) && !defender.HasAbility({"Sticky Hold"});

   if (defender.HasItem({"Leftovers"}) && !lose_item) 
   {
      damage += hp_frac(defender, 16);
      texts.push_back("Leftovers recovery");
   }
   else if (defender.HasItem({"Black Sludge"}) && !lose_item) 
   {
      if (defender.HasType({ENUMS::TypeName::Poison})) 
      {
         damage += hp_frac(defender, 16);
         texts.push_back("Black Sludge recovery");
      }
      else if (!defender.HasAbility({"Magic Guard", "Klutz"})) 
      {
         damage -= hp_frac(defender, 8);
         texts.push_back("Black Sludge damage");
      }
   }
   else if (defender.HasItem({"Sticky Barb"})) 
   {
      damage -= hp_frac(defender, 8);
      texts.push_back("Sticky Barb damage");
   }

   // Leech Seed
   if (field.defender_side.is_seeded) 
   {
      if (!defender.HasAbility({"Magic Guard"})) 
      {
         damage -= hp_frac(defender, g >= 2 ? 8 : 16);
         texts.push_back("Leech Seed damage");
      }
   }

   if (field.attacker_side.is_seeded &&
      !attacker.HasAbility({"Magic Guard"}))
   {
      int recovery = hp_frac(attacker, g >= 2 ? 8 : 16);

      if (defender.HasItem({"Big Root"})) 
      {
         recovery = static_cast<int>(std::trunc(recovery * 5324.0 / 4096.0));
      }

      if (attacker.HasAbility({"Liquid Ooze"})) 
      {
         damage -= recovery;
         texts.push_back("Liquid Ooze damage");
      } 
      else 
      {
         damage += recovery;
         texts.push_back("Leech Seed recovery");
      }
   }

   // Terrain
   if (field.HasTerrain({ENUMS::Terrain::Grassy_t}) &&
       IsGrounded(defender, field))
   {
      damage += hp_frac(defender, 16);
      texts.push_back("Grassy Terrain recovery");
   }

   // Status
   if (defender.HasStatus({ENUMS::StatusName::psn})) 
   {
      if (defender.HasAbility({"Poison Heal"})) 
      {
         damage += hp_frac(defender, 8);
         texts.push_back("Poison Heal");
      }
      else if (!defender.HasAbility({"Magic Guard"})) 
      {
         damage -= hp_frac(defender, g == 1 ? 16 : 8);
         texts.push_back("poison damage");
      }
   }
   else if (defender.HasStatus({ENUMS::StatusName::tox})) 
   {
      if (defender.HasAbility({"Poison Heal"})) 
      {
         damage += hp_frac(defender, 8);
         texts.push_back("Poison Heal");
      }
      else if (!defender.HasAbility({"Magic Guard"})) 
      {
         texts.push_back("toxic damage");
      }
   }
   else if (defender.HasStatus({ENUMS::StatusName::brn})) 
   {
      if (defender.HasAbility({"Heatproof"})) 
      {
         damage -= hp_frac(defender, g > 6 ? 32 : 16);
         texts.push_back("reduced burn damage");
      }
      else if (!defender.HasAbility({"Magic Guard"})) 
      {
         damage -= hp_frac(defender,(g == 1 || g > 6) ? 16 : 8);
         texts.push_back("burn damage");
      }
   }
   else if ((defender.HasStatus({ENUMS::StatusName::slp}) ||
             defender.HasAbility({"Comatose"})) &&
             attacker.HasAbility({"Bad Dreams"}) &&
             !defender.HasAbility({"Magic Guard"}))
   {
      damage -= hp_frac(defender, 8);
      texts.push_back("Bad Dreams");
   }

   // Trapping
   if (!defender.HasAbility({"Magic Guard"}) &&
      TRAPPING.contains(move.GetName()))
   {
      if (attacker.HasItem({"Binding Band"})) 
      {
         damage -= g > 5 ? hp_frac(defender, 6) : hp_frac(defender, 8);
      }
      else 
      {
         damage -= g > 5 ? hp_frac(defender, 8) : hp_frac(defender, 16);
      }

      texts.push_back("trapping damage");
   }

   // Salt Cure
   if (defender.GetIsSaltCure() && !defender.HasAbility({"Magic Guard"}))
   {
      bool is_water_or_steel =
         defender.HasType({ENUMS::TypeName::Water, ENUMS::TypeName::Steel}) ||
         (defender.GetTeraType() == ENUMS::TypeName::Water || 
          defender.GetTeraType() == ENUMS::TypeName::Steel);

      damage -= hp_frac(defender, is_water_or_steel ? 4 : 8);

      texts.push_back("Salt Cure");
   }

   // Sea of Fire
   if (!defender.HasType({ENUMS::TypeName::Fire}) &&
       !defender.HasAbility({"Magic Guard"}) &&
       move.Named({"Fire Pledge (Grass Pledge Boosted)",
                   "Grass Pledge (Fire Pledge Boosted)"}))
   {
      damage -= hp_frac(defender, 8);
      texts.push_back("Sea of Fire damage");
   }

   // G-Max residuals
   if (!defender.HasAbility({"Magic Guard"}) &&
      !defender.HasType({ENUMS::TypeName::Grass}) &&
      (field.defender_side.vinelash ||
       move.Named({"G-Max Vine Lash"})))
   {
      damage -= hp_frac(defender, 6);
      texts.push_back("Vine Lash damage");
   }

   if (!defender.HasAbility({"Magic Guard"}) &&
       !defender.HasType({ENUMS::TypeName::Fire}) &&
       (field.defender_side.wildfire ||
        move.Named({"G-Max Wildfire"})))
   {
      damage -= hp_frac(defender, 6);
      texts.push_back("Wildfire damage");
   }

   if (!defender.HasAbility({"Magic Guard"}) &&
       !defender.HasType({ENUMS::TypeName::Water}) &&
       (field.defender_side.cannonade ||
        move.Named({"G-Max Cannonade"})))
   {
      damage -= hp_frac(defender, 6);
      texts.push_back("Cannonade damage");
   }

   if (!defender.HasAbility({"Magic Guard"}) &&
       !defender.HasType({ENUMS::TypeName::Rock}) &&
       (field.defender_side.volcalith ||
        move.Named({"G-Max Volcalith"})))
   {
      damage -= hp_frac(defender, 6);
      texts.push_back("Volcalith damage");
   }

   return std::make_pair(damage, texts);
}

std::pair<std::pair<int, int>, std::string> GetRecovery
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const Damage& damage,
   const std::string& notation
)
{
   const int g = static_cast<int>(gen);
   auto range = DamageRange(damage);

   std::vector<int> min_damage;
   std::vector<int> max_damage;

   std::visit
   (
      [&](const auto& r)
      {
         using T = std::decay_t<decltype(r)>;

         // pair<int, int>
         if constexpr (std::is_same_v<T, std::pair<int, int>>)
         {
            min_damage.push_back(r.first);
            max_damage.push_back(r.second);
         }
         // pair<pair<int,int>, pair<int,int>>
         else
         {
            min_damage.push_back(r.first.first);
            min_damage.push_back(r.first.second);

            max_damage.push_back(r.second.first);
            max_damage.push_back(r.second.second);
         }
      },
      range
   );

   std::pair<int, int> recovery{0, 0};
   std::string text;

   const bool ignores_shell_bell = g == 3 && move.Named({"Doom Desire", "Future Sight"});

   if (attacker.HasItem({"Shell Bell"}) && !ignores_shell_bell)
   {
      const int max = static_cast<int>(std::lround(defender.MaxHP() / 8.0));

      for (std::size_t i = 0; i < min_damage.size(); ++i)
      {
         recovery.first +=
            std::min
            (
               static_cast<int>(std::lround(min_damage[i] * 
                  (move.GetHits() ? move.GetHits().value() : 1) / 
                  8.0)),
               max
            );

         recovery.second +=
            std::min
            (
               static_cast<int>(std::lround(max_damage[i] * 
                  (move.GetHits() ? move.GetHits().value() : 1) / 
                  8.0)),
               max
            );
      }
   }

   if (move.Named({"G-Max Finale"}))
   {
      const int heal = static_cast<int>(std::lround(attacker.MaxHP() / 6.0));

      recovery.first = heal;
      recovery.second = heal;
   }

   if (move.GetDrain())
   {
      const auto [numerator, denominator] = move.GetDrain().value();
      const double percent_healed = static_cast<double>(numerator) / denominator;
      const int max = static_cast<int>(std::lround(defender.MaxHP() * percent_healed));

      for (std::size_t i = 0; i < min_damage.size(); ++i)
      {
         const int range_values[2] = { min_damage[i], max_damage[i] };

         for (int j = 0; j < 2; ++j)
         {
            int drained = static_cast<int>(std::lround(range_values[j] * percent_healed));

            if (attacker.HasItem({"Big Root"}))
            {
               drained = static_cast<int>(std::trunc(drained * 5324.0 / 4096.0));
            }

            const int recovered 
               = std::min(drained * (move.GetHits() ? move.GetHits().value() : 1), max);
            if (j == 0)
            {
               recovery.first += recovered;
            }
            else
            {
               recovery.second += recovered;
            }
         }
      }
   }

   if (recovery.second == 0)
   {
      return {recovery, text};
   }

   const int min_health_recovered = ToDisplay(notation, recovery.first, attacker.MaxHP());

   const int max_health_recovered = ToDisplay(notation, recovery.second, attacker.MaxHP());

   text = std::to_string(min_health_recovered) + " - " + 
          std::to_string(max_health_recovered) + notation + " recovered";

   return {recovery, text};
}

// TODO: return recoil damage as exact HP
std::pair<std::pair<int, int>, std::string>  GetRecoil
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const Damage& damage,
   const std::string& notation
) 
{
   const int g = static_cast<int>(gen);
   auto range = DamageRange(damage);

   std::pair<int, int> min_max_damage = std::visit
   (
      [&](const auto& d) -> std::pair<int, int>
      {
         using T = std::decay_t<decltype(d)>;

         if constexpr (std::is_same_v<T, std::pair<int, int>>)
         {
            return std::make_pair(d.first * (move.GetHits() ? move.GetHits().value() : 1),
                                  d.second * (move.GetHits() ? move.GetHits().value() : 1));
         }
         // Standard Damage
         else if constexpr (std::is_same_v<T, std::pair<std::pair<int, int>, std::pair<int, int>>>)
         {
            return std::make_pair<int, int>
            (
               (d.first.first + d.first.second) * (move.GetHits() ? move.GetHits().value() : 1), 
               (d.second.first + d.second.second) * (move.GetHits() ? move.GetHits().value() : 1)
            );
         }
      },
      range
   );

   std::pair<int, int> recoil{0, 0};
   int recoil_i = 0;
   bool use_recoil_i = false;
   std::string text = "";

   const bool damage_overflow = min_max_damage.first > defender.CurHP() || 
                                min_max_damage.second > defender.CurHP();
   if (move.GetRecoil()) 
   {
      const int mod = static_cast<double>(move.GetRecoil().value().first) / move.GetRecoil().value().second * 100;
      int min_recoil_damage, max_recoil_damage;
      if (damage_overflow) 
      {
         min_recoil_damage =
            ToDisplay(notation, defender.CurHP() * mod, attacker.MaxHP(), 100);
         max_recoil_damage =
            ToDisplay(notation, defender.CurHP() * mod, attacker.MaxHP(), 100);
      } 
      else 
      {
         min_recoil_damage = ToDisplay
         (
            notation, 
            std::min(min_max_damage.first, defender.CurHP()) * mod, 
            attacker.MaxHP(), 
            100
         );
         max_recoil_damage = ToDisplay
         (
            notation, 
            std::min(min_max_damage.second, defender.CurHP()) * mod, 
            attacker.MaxHP(), 
            100
         );
      }
      if (!attacker.HasAbility({"Rock Head"})) 
      {
         recoil = std::make_pair(min_recoil_damage, max_recoil_damage);
         text = std::to_string(min_recoil_damage) +
                " - " +
                std::to_string(max_recoil_damage) +
                notation +
                " recoil damage";
      }
   } 
   else if (move.GetHasCrashDamage()) 
   {
      const double gen_multiplier = g == 2 ? 12.5 : g >= 3 ? 50 : 1;

      int min_recoil_damage, max_recoil_damage;
      if (damage_overflow && g != 2) 
      {
         min_recoil_damage =
            ToDisplay(notation, defender.CurHP() * gen_multiplier, attacker.MaxHP(), 100);
         max_recoil_damage =
            ToDisplay(notation, defender.CurHP() * gen_multiplier, attacker.MaxHP(), 100);
      } else {
         min_recoil_damage = ToDisplay
         (
            notation, 
            std::min(min_max_damage.first, defender.MaxHP()) * gen_multiplier, 
            attacker.MaxHP(), 
            100
         );
         max_recoil_damage = ToDisplay
         (
            notation, 
            std::min(min_max_damage.second, defender.MaxHP()) * gen_multiplier,
            attacker.MaxHP(), 
            100
         );
      }

      recoil = std::make_pair(min_recoil_damage, max_recoil_damage);
      switch (gen) 
      {
      case ENUMS::GenerationNumber::__1:
         recoil_i = ToDisplay(notation, 1, attacker.MaxHP());
         text = "1hp damage on miss";
         use_recoil_i = true;
         break;
      case 2: case 3: case 4:
         if (defender.HasType({ENUMS::TypeName::Ghost})) 
         {
            use_recoil_i = true;
            if (g == 4) 
            {
               const int gen_4_crash_damage = (((defender.MaxHP() * 0.5) / attacker.MaxHP()) * 100);
               recoil_i = notation == "%" ? gen_4_crash_damage : ((gen_4_crash_damage / 100) * 48);
               text = std::to_string(gen_4_crash_damage) + " crash damage";
            } 
            else 
            {
               recoil_i = 0;
               text = "no crash damage on Ghost types";
            }
         } 
         else 
         {
            text = std::to_string(min_recoil_damage) +
                   " - " +
                   std::to_string(max_recoil_damage) + 
                   notation + " crash damage on miss";
         }
         break;
      default:
         recoil_i = notation == "%" ? 24 : 50;
         text = "50% crash damage";
         use_recoil_i = true;
      }
   } 
   else if (move.GetStruggleRecoil()) 
   {
      recoil_i = notation == "%" ? 12 : 25;
      text = "25% struggle damage";
      // Struggle recoil is actually rounded down in Gen 4 per DaWoblefet's research, but until we
      // return recoil damage as exact HP the best we can do is add some more text to this effect
      if (g == 4) text += " (rounded down)";
      use_recoil_i = true;
   } 
   else if (move.GetMindBlownRecoil()) 
   {
      recoil_i = notation == "%" ? 24 : 50;
      text = "50% recoil damage";
      use_recoil_i = true;
   }

   if (use_recoil_i)
   {
      recoil.first = recoil_i;
   }

   return {recoil, text};
}

std::string DisplayMove
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const Damage& damage,
   const std::string& notation
)
{
   const DamageRangeResult min_max_damage = DamageRange(damage);
   const std::pair<int, int> min_max = std::visit
   (
      [](const auto& d) -> std::pair<int, int>
      {
         using T = std::decay_t<decltype(d)>;

         if constexpr (std::is_same_v<T, std::pair<int, int>>)
         {
            return std::make_pair(d.first, d.second);
         }
         // Standard Damage
         else if constexpr (std::is_same_v<T, std::pair<std::pair<int, int>, std::pair<int, int>>>)
         {
            return std::make_pair<int, int>(d.first.first + d.first.second, 
                                            d.second.first + d.second.second);
         }

         return std::make_pair(0, 0);
      },
      min_max_damage
   );

   const int min_display = ToDisplay(notation, min_max.first, defender.MaxHP());
   const int max_display = ToDisplay(notation, min_max.second, defender.MaxHP());

   const std::string recovery_text = GetRecovery(gen, attacker, defender, move, damage, notation).second;
   const std::string recoil_text = GetRecoil(gen, attacker, defender, move, damage, notation).second;

   return std::to_string(min_display) + " - " +
          std::to_string(max_display) + notation + 
          recovery_text + recoil_text;
}

}
}

