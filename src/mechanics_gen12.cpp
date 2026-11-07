#include "./../include/mechanics/gen12.hpp"

#include <array>
#include <utility>

#include "./../include/calc_util.hpp"
#include "./../include/description.hpp"
#include "./../include/data/items.h"

namespace PokemonDamageCalcCPP
{
namespace Mechanics
{
namespace GEN12
{

Result::Result CalculateRBYGSC
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon attacker,
   Pokemon::Pokemon defender,
   Move::Move move,
   State::Field field
)
{
   CalcUtil::ComputeFinalStats
   (
      gen, 
      attacker, 
      defender, 
      field, 
      std::vector<ENUMS::StatID>
      {
         ENUMS::StatID::atk, 
         ENUMS::StatID::def, 
         ENUMS::StatID::spa,
         ENUMS::StatID::spd,
         ENUMS::StatID::spe
      }
   );

   Description::RawDescription desc =
   {
      .attacker_name = attacker.GetName(),
      .defender_name = defender.GetName(),
      .move_name = move.GetName()
   };

   Result::Result result(gen, attacker, defender, move, field, 0, desc);

   if (move.GetMoveCategory() == ENUMS::MoveCategory::Status) 
   {
      return result;
   }

   if (field.defender_side.is_protected) 
   {
      desc.is_protected = true;
      return result;
   }

   // Fixed damage moves (eg. Night Shade) ignore type effectiveness in Gen 1
   if (gen == ENUMS::GenerationNumber::__1) 
   {
      const int fixed_damage = CalcUtil::HandleFixedDamageMoves(attacker, move);
      if (fixed_damage) 
      {
         result.SetDamage(fixed_damage);
         return result;
      }
   }

   const std::vector<ENUMS::TypeName> type_effectiveness_precedence_rules = 
   {
      ENUMS::TypeName::Normal,
      ENUMS::TypeName::Fire,
      ENUMS::TypeName::Water,
      ENUMS::TypeName::Electric,
      ENUMS::TypeName::Grass,
      ENUMS::TypeName::Ice,
      ENUMS::TypeName::Fighting,
      ENUMS::TypeName::Poison,
      ENUMS::TypeName::Ground,
      ENUMS::TypeName::Flying,
      ENUMS::TypeName::Psychic,
      ENUMS::TypeName::Bug,
      ENUMS::TypeName::Rock,
      ENUMS::TypeName::Ghost,
      ENUMS::TypeName::Dragon,
      ENUMS::TypeName::Dark,
      ENUMS::TypeName::Steel
   };

   std::pair<ENUMS::TypeName, ENUMS::TypeName> precedence;
   
   if (defender.GetTypes().size() > 1 && 
       defender.GetTypes().at(0) != defender.GetTypes().at(1) && 
       gen == ENUMS::GenerationNumber::__2) 
   {
      const int first_type_precedence = std::find(type_effectiveness_precedence_rules.begin(),
                                                  type_effectiveness_precedence_rules.end(),
                                                  defender.GetTypes().at(0)) -
                                        type_effectiveness_precedence_rules.begin();
      const int second_type_precedence = std::find(type_effectiveness_precedence_rules.begin(),
                                                   type_effectiveness_precedence_rules.end(),
                                                   defender.GetTypes().at(1)) -
                                        type_effectiveness_precedence_rules.begin();

      if (first_type_precedence > second_type_precedence) 
      {
         precedence = std::make_pair(defender.GetTypes().at(1), defender.GetTypes().at(0));
      }
   }


   const float type_eff1 = CalcUtil::GetMoveEffectiveness
   (
      gen, 
      move, 
      defender.GetTypes().at(0), 
      field.defender_side.is_foresight ? *field.defender_side.is_foresight : false
   );
   const float type_eff2 = defender.GetTypes().size() > 1 ? 
   CalcUtil::GetMoveEffectiveness
   (
      gen, 
      move, 
      defender.GetTypes().at(1), 
      field.defender_side.is_foresight ? *field.defender_side.is_foresight : false
   ) : 1;
   const float type_eff = type_eff1 * type_eff2;

   if (type_eff == 0) 
   {
      return result;
   }

   if (gen == ENUMS::GenerationNumber::__2) 
   {
      const int fixed_damage = CalcUtil::HandleFixedDamageMoves(attacker, move);
      if (fixed_damage) 
      {
         result.SetDamage(fixed_damage);
         return result;
      }
   }

   if (move.GetHits() > 1) 
   {
      desc.hits = move.GetHits();
   }
   // Triple Kick"s damage increases by 10 after each consecutive hit (10, 20, 30), this is a hack
   if (move.GetName() == "Triple Kick") 
   {
      move.SetBP(move.GetHits() == 2 ? 15 : move.GetHits() == 3 ? 20 : 10);
      desc.move_bp = move.GetBP();
   }

   // Flail and Reversal are variable BP and never crit
   if (move.Named({"Flail", "Reversal"})) 
   {
      move.SetCrit(false);
      const int p = ((48 * attacker.CurHP()) / attacker.MaxHP());
      move.SetBP(p <= 1 ? 200 : p <= 4 ? 150 : p <= 9 ? 100 : p <= 16 ? 80 : p <= 32 ? 40 : 20);
      desc.move_bp = move.GetBP();
   } 
   else if (move.Named({"Present"}) && !move.GetBP()) 
   {
      // Present is technically 0 BP so we default to 40 in that case, but the UI may override the
      // base power in order to simulate the scenarios where it is 80 or 120 BP.
      move.SetBP(40);
   }

   if (move.GetBP() == 0) 
   {
      return result;
   }

   bool is_physical = move.GetMoveCategory() == ENUMS::MoveCategory::Physical;
   ENUMS::StatID attack_stat = is_physical ? ENUMS::StatID::atk : ENUMS::StatID::spa;
   ENUMS::StatID defense_stat = is_physical ? ENUMS::StatID::def : ENUMS::StatID::spd;
   int at = attacker.GetStats().at(attack_stat);
   int df = defender.GetStats().at(defense_stat);

   // Whether we ignore Reflect, Light Screen, stat stages, and burns if attack is a crit differs
   // by gen - in gen 2 we also need to check that the attacker does not have stat stage advantage
   bool ignore_mods = move.GetIsCrit() &&
      (gen == ENUMS::GenerationNumber::__1 ||
      (gen == ENUMS::GenerationNumber::__2 && 
       attacker.GetBoosts().at(attack_stat) <= defender.GetBoosts().at(defense_stat)));

   int lv = attacker.GetLevel();
   if (ignore_mods) 
   {
      at = attacker.GetRawStats().at(attack_stat);
      df = defender.GetRawStats().at(defense_stat);
      if (gen == ENUMS::GenerationNumber::__1) 
      {
         lv *= 2;
         desc.is_critical = true;
      }
   } 
   else 
   {
      if (attacker.GetBoosts().at(attack_stat) != 0) desc.attack_boost = attacker.GetBoosts().at(attack_stat);
      if (defender.GetBoosts().at(defense_stat) != 0) desc.defense_boost = defender.GetBoosts().at(defense_stat);
      if (is_physical && attacker.HasStatus({ENUMS::StatusName::brn})) 
      {
         at = (at / 2);
         desc.is_burned = true;
      }
   }

   if (move.Named({"Explosion", "Self-Destruct"})) 
   {
      df = (df / 2);
   }

   if (!ignore_mods) 
   {
      if (is_physical && field.defender_side.is_reflect) 
      {
         df *= 2;
         desc.is_reflect = true;
      } 
      else if 
      (!is_physical && field.defender_side.is_light_screen) 
      {
         df *= 2;
         desc.is_light_screen = true;
      }
   }

   if ((attacker.Named({"Pikachu"}) && attacker.HasItem({"Light Ball"}) && !is_physical) ||
       (attacker.Named({"Cubone", "Marowak"}) && attacker.HasItem({"Thick Club"}) && is_physical)) 
   {
      at *= 2;
      desc.attacker_item = attacker.GetItem() ? *attacker.GetItem() : "";
   }

   if (at > 255 || df > 255) 
   {
      at = (at / 4) % 256;
      df = (df / 4) % 256;
   }

   // Gen 2 Present has a glitched damage calculation using the secondary types of the Pokemon
   // for the Attacker's Level and Defender's Defense.
   if (move.Named({"Present"})) 
   {
      std::map<ENUMS::TypeName, int> lookup = 
      {
         {ENUMS::TypeName::Normal, 0}, 
         {ENUMS::TypeName::Fighting, 1}, 
         {ENUMS::TypeName::Flying, 2}, 
         {ENUMS::TypeName::Poison, 3}, 
         {ENUMS::TypeName::Ground, 4}, 
         {ENUMS::TypeName::Rock, 5}, 
         {ENUMS::TypeName::Bug, 7},
         {ENUMS::TypeName::Ghost, 8}, 
         {ENUMS::TypeName::Steel, 9}, 
         {ENUMS::TypeName::QQQ, 19}, 
         {ENUMS::TypeName::Fire, 20}, 
         {ENUMS::TypeName::Water, 21}, 
         {ENUMS::TypeName::Grass, 22}, 
         {ENUMS::TypeName::Electric, 23},
         {ENUMS::TypeName::Psychic, 24}, 
         {ENUMS::TypeName::Ice, 25}, 
         {ENUMS::TypeName::Dragon, 26}, 
         {ENUMS::TypeName::Dark, 27}
      };

      at = 10;
      df = std::max(lookup[attacker.GetTypes().at(1) ? attacker.GetTypes().at(1) 
                                                     : attacker.GetTypes().at(0)], 1);
      lv = std::max(lookup[defender.GetTypes().at(1) ? defender.GetTypes().at(1) 
                                                     : defender.GetTypes().at(0)], 1);
   }

   if (defender.Named({"Ditto"}) && defender.HasItem({"Metal Powder"})) 
   {
      df = std::floor(df * 1.5);
      desc.defender_item = defender.GetItem() ? *defender.GetItem() : "";
   }

   int base_damage = ((((2 * lv) / 5 + 2) * std::max(1, at) * move.GetBP()) / std::max(1, df)) / 50;

   // Gen 1 handles move.isCrit above by doubling level
   if (gen == ENUMS::GenerationNumber::__2 && move.GetIsCrit()) 
   {
      base_damage *= 2;
      desc.is_critical = true;
   }

   if (move.Named({"Pursuit"}) && 
       field.defender_side.is_switching &&
       field.defender_side.is_switching.value() == ENUMS::Switching::out) 
   {
      base_damage = (base_damage * 2);
      desc.is_switching = "out";
   }

   // In Gen 2 and no other gens, Dragon Fang in a no-op and Dragon Scale erroneously has its effect
   std::optional<ENUMS::TypeName> item_boost_type =
      attacker.HasItem({"Dragon Fang"})
         ? std::nullopt
         : Data::Items::Instance().GetItemBoostType(attacker.HasItem({"Dragon Scale"}) 
            ? "Dragon Fang" 
            : attacker.GetItem() 
               ? *attacker.GetItem() 
               : "");

   if (item_boost_type && move.HasType({item_boost_type.value()})) 
   {
      base_damage = std::floor(base_damage * 1.1);
      desc.attacker_item = attacker.GetItem() ? *attacker.GetItem() : "";
   }

   base_damage = std::min(997, base_damage) + 2;

   if ((field.HasWeather({ENUMS::Weather::Sun}) && move.HasType({ENUMS::TypeName::Fire})) ||
       (field.HasWeather({ENUMS::Weather::Rain}) && move.HasType({ENUMS::TypeName::Water}))) 
   {
      base_damage = std::floor(base_damage * 1.5);
      desc.weather = field.weather;
   } 
   else if 
   (
      (field.HasWeather({ENUMS::Weather::Sun}) && move.HasType({ENUMS::TypeName::Water})) ||
      (field.HasWeather({ENUMS::Weather::Rain}) && 
       (move.HasType({ENUMS::TypeName::Fire}) || move.Named({"Solar Beam"})))
   ) 
   {
      base_damage = std::floor(base_damage / 2);
      desc.weather = field.weather;
   }

   if (move.HasType(attacker.GetTypes())) 
   {
      base_damage = std::floor(base_damage * 1.5);
   }

   if (gen == ENUMS::GenerationNumber::__1) 
   {
      base_damage = floor(base_damage * type_eff1);
      base_damage = floor(base_damage * type_eff2);
   } 
   else 
   {
      base_damage = floor(base_damage * type_eff);
   }

   // Flail and Reversal don't use random factor
   if (move.Named({"Flail", "Reversal"})) 
   {
      result.SetDamage(base_damage);
      return result;
   }

   int damage_out[39];
   for (int i = 217; i <= 255; i++) 
   {
      if (gen == ENUMS::GenerationNumber::__2) 
      { // in gen 2 damage is always rounded up to 1. TODO ADD TESTS
         damage_out[i - 217] = std::max(1, ((base_damage * i) / 255));
      } 
      else 
      {
         if (base_damage == 1) 
         { // in gen 1 the random factor multiplication is skipped if damage = 1
            damage_out[i - 217] = 1;
         } 
         else 
         {
            damage_out[i - 217] = ((base_damage * i) / 255);
         }
      }
   }

   if (move.GetHits() > 1) 
   {
      for (int times = 0; times < move.GetHits(); times++) 
      {
         int damage_multiplier = 217;

         for (auto& affected_amount : damage_out) 
         {
            if (times) 
            {
               int new_final_damage = 0;

               // In Gen 2 damage is always rounded up to 1
               if (gen == ENUMS::GenerationNumber::__2) 
               {
                  new_final_damage = std::max
                  (
                     1,
                     static_cast<int>((base_damage * damage_multiplier) / 255)
                  );
               } 
               else 
               {
                  // In Gen 1 the random factor multiplication is skipped if damage = 1
                  if (base_damage == 1) 
                  {
                     new_final_damage = 1;
                  } 
                  else 
                  {
                     new_final_damage = static_cast<int>((base_damage * damage_multiplier) / 255);
                  }
               }

               damage_multiplier++;
               affected_amount += new_final_damage;
            }
         }
      }
   }

   std::vector<int> temp_damage(std::begin(damage_out), std::end(damage_out));
   result.SetDamage(temp_damage);

   return result;
}

}
}
}

