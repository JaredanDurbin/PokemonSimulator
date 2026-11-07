#include "./../include/mechanics/gen3.hpp"

#include "./../include/calc_util.hpp"
#include "./../include/description.hpp"
#include "./../include/data/items.h"

namespace PokemonDamageCalcCPP
{
namespace Mechanics
{
namespace GEN3
{

void CalculateFinalModsADV
(
   int& base_damage,
   const Pokemon::Pokemon& attacker,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical
) 
{
   bool is_physical = move.GetMoveCategory() == ENUMS::MoveCategory::Physical;
   if (attacker.HasStatus({ENUMS::StatusName::brn}) && 
       is_physical && 
       !attacker.HasAbility({"Guts"}))
   {
      base_damage = (base_damage / 2);
      desc.is_burned = true;
   }

   if (!is_critical) 
   {
      float screen_multiplier = field.game_type != ENUMS::GameType::Singles ? 2 / 3 : 1 / 2;
      if (is_physical && field.defender_side.is_reflect) 
      {
         base_damage = std::floor(base_damage * screen_multiplier);
         desc.is_reflect = true;
      } 
      else if (!is_physical && field.defender_side.is_light_screen) 
      {
         base_damage = std::floor(base_damage * screen_multiplier);
         desc.is_light_screen = true;
      }
   }

   if (move.Named({"Pursuit"}) && field.defender_side.is_switching == ENUMS::Switching::out) 
   {
      base_damage = (base_damage * 2);
      desc.is_switching = "out";
   }

   if (field.game_type != ENUMS::GameType::Singles && move.GetTarget() == ENUMS::MoveTarget::all_adjacent_foes) 
   {
      base_damage = (base_damage / 2);
   }

   if ((field.HasWeather({ENUMS::Weather::Sun}) && move.HasType({ENUMS::TypeName::Fire})) ||
       (field.HasWeather({ENUMS::Weather::Rain}) && move.HasType({ENUMS::TypeName::Water}))) 
   {
      base_damage = std::floor(base_damage * 1.5);
      desc.weather = field.weather;
   } 
   else if 
   (
      (field.HasWeather({ENUMS::Weather::Sun}) && move.HasType({ENUMS::TypeName::Water})) ||
      (field.HasWeather({ENUMS::Weather::Rain}) && move.HasType({ENUMS::TypeName::Fire})) ||
      (move.Named({"Solar Beam"}) && 
       field.HasWeather({ENUMS::Weather::Rain, ENUMS::Weather::Sand, ENUMS::Weather::Hail}))
   ) 
   {
      base_damage = floor(base_damage / 2);
      desc.weather = field.weather;
   }

   if (attacker.HasAbility({"Flash Fire"}) && attacker.GetAbilityOn() && move.HasType({ENUMS::TypeName::Fire})) 
   {
      base_damage = std::floor(base_damage * 1.5);
      desc.attacker_ability = "Flash Fire";
   }

   base_damage = (move.GetMoveCategory() == ENUMS::MoveCategory::Physical 
      ? std::max(1, base_damage) : base_damage) + 2;
   if (is_critical) 
   {
      base_damage *= 2;
      desc.is_critical = true;
   }

   if (move.Named({"Weather Ball"}) && field.weather) 
   {
      base_damage *= 2;
      desc.move_bp = move.GetBP() * 2;
   }

   if (field.attacker_side.is_helping_hand) 
   {
      base_damage = std::floor(base_damage * 1.5);
      desc.is_helping_hand = true;
   }

   if (move.HasType(attacker.GetTypes()))
   {
      base_damage = std::floor(base_damage * 1.5);
   }
}

int CalculateDefenseADV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   Description::RawDescription& desc,
   bool is_critical
) 
{
   bool is_physical = move.GetMoveCategory() == ENUMS::MoveCategory::Physical;
   ENUMS::StatID defense_stat = is_physical ? ENUMS::StatID::def : ENUMS::StatID::spd;
   desc.defense_evs = CalcUtil::GetStatDescriptionText(gen, defender, defense_stat, defender.GetNature());

   int df = defender.GetRawStats().at(defense_stat);

   if (!is_physical && defender.HasItem({"Soul Dew"}) && defender.Named({"Latios", "Latias"})) 
   {
      df = std::floor(df * 1.5);
      desc.defender_item = defender.GetItem();
   } 
   else if 
   (
      (!is_physical && defender.HasItem({"Deep Sea Scale"}) && defender.Named({"Clamperl"})) ||
      (is_physical && defender.HasItem({"Metal Powder"}) && defender.Named({"Ditto"}))
   ) 
   {
      df *= 2;
      desc.defender_item = defender.GetItem();
   }

   if (is_physical && defender.HasAbility({"Marvel Scale"}) && defender.HasStatus()) 
   {
      df = std::floor(df * 1.5);
      desc.defender_ability = defender.GetAbility();
   }

   if (move.Named({"Explosion", "Self-Destruct"})) 
   {
      df = (df / 2);
   }

   int defense_boost = defender.GetBoosts().at(defense_stat);
   if (defense_boost < 0 || (!is_critical && defense_boost > 0)) 
   {
      df = CalcUtil::GetModifiedStat(df, defense_boost);
      desc.defense_boost = defense_boost;
   }

   return df;
}   

int CalculateAttackADV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   Description::RawDescription& desc,
   bool is_critical
) 
{
   bool is_physical = move.GetMoveCategory() == ENUMS::MoveCategory::Physical;
   ENUMS::StatID attack_stat = is_physical ? ENUMS::StatID::atk : ENUMS::StatID::spa;
   desc.attack_evs = CalcUtil::GetStatDescriptionText(gen, attacker, attack_stat, attacker.GetNature());

   int at = attacker.GetRawStats().at(attack_stat);

   if (is_physical && attacker.HasAbility({"Huge Power", "Pure Power"})) 
   {
      at *= 2;
      desc.attacker_ability = attacker.GetAbility();
   }

   if (!attacker.HasItem({"Sea Incense"}) && attacker.GetItem() &&
       Data::Items::Instance().GetItemBoostType(attacker.GetItem().value()) &&
       move.HasType({Data::Items::Instance().GetItemBoostType(
          attacker.GetItem().value()).value()})) 
   {
      at = std::floor(at * 1.1);
      desc.attacker_item = attacker.GetItem();
   } 
   else if (attacker.HasItem({"Sea Incense"}) && move.HasType({ENUMS::TypeName::Water})) 
   {
      at = std::floor(at * 1.05);
      desc.attacker_item = attacker.GetItem();
   } 
   else if 
   (
      (is_physical && attacker.HasItem({"Choice Band"})) ||
      (!is_physical && attacker.HasItem({"Soul Dew"}) && attacker.Named({"Latios", "Latias"}))
   ) 
   {
      at = std::floor(at * 1.5);
      desc.attacker_item = attacker.GetItem();
   } 
   else if 
   (
      (!is_physical && attacker.HasItem({"Deep Sea Tooth"}) && attacker.Named({"Clamperl"})) ||
      (!is_physical && attacker.HasItem({"Light Ball"}) && attacker.Named({"Pikachu"})) ||
      (is_physical && attacker.HasItem({"Thick Club"}) && attacker.Named({"Cubone", "Marowak"}))
   ) 
   {
      at *= 2;
      desc.attacker_item = attacker.GetItem();
   }

   if (defender.HasAbility({"Thick Fat"}) && 
       (move.HasType({ENUMS::TypeName::Fire, ENUMS::TypeName::Ice}))) 
   {
      at = std::floor(at / 2);
      desc.defender_ability = defender.GetAbility();
   }

   if ((is_physical &&
        (attacker.HasAbility({"Hustle"}) || 
         (attacker.HasAbility({"Guts"}) && 
          attacker.HasStatus()))) ||
      (!is_physical && attacker.GetAbilityOn() && attacker.HasAbility({"Plus", "Minus"}))
   ) 
   {
      at = std::floor(at * 1.5);
      desc.attacker_ability = attacker.GetAbility();
   }

   int attack_boost = attacker.GetBoosts().at(attack_stat);
   if (attack_boost > 0 || (!is_critical && attack_boost < 0)) {
      at = CalcUtil::GetModifiedStat(at, attack_boost);
      desc.attack_boost = attack_boost;
   }
   return at;
}

void CalculateBPModsADV
(
   const Pokemon::Pokemon& attacker,
   const Move::Move& move,
   Description::RawDescription& desc,
   int& base_power
) 
{
   if (attacker.CurHP() <= attacker.MaxHP() / 3 &&
       ((attacker.HasAbility({"Overgrow"}) && move.HasType({ENUMS::TypeName::Grass})) ||
      (attacker.HasAbility({"Blaze"}) && move.HasType({ENUMS::TypeName::Fire})) ||
      (attacker.HasAbility({"Torrent"}) && move.HasType({ENUMS::TypeName::Water})) ||
      (attacker.HasAbility({"Swarm"}) && move.HasType({ENUMS::TypeName::Bug})))
   ) 
   {
      base_power = std::floor(base_power * 1.5);
      desc.attacker_ability = attacker.GetAbility();
   }
}

int CalculateBasePowerADV
(
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   Move::Move& move,
   Description::RawDescription& desc,
   int hit
)
{
   int bp = move.GetBP();

   if (move.GetName() == "Flail" ||move.GetName() == "Reversal")
   {
      int p = std::floor((48 * attacker.CurHP()) / attacker.MaxHP());
      bp = p <= 1 ? 200 : p <= 4 ? 150 : p <= 9 ? 100 : p <= 16 ? 80 : p <= 32 ? 40 : 20;
      desc.move_bp = bp;
   }
   if (move.GetName() == "Eruption" ||move.GetName() == "Water Spout")
   {
      bp = std::max(1, ((150 * attacker.CurHP()) / attacker.MaxHP()));
      desc.move_bp = bp;
   }
   if (move.GetName() == "Low Kick")
   {
      float w = defender.GetWeight();
      bp = w >= 200 ? 120 : w >= 100 ? 100 : w >= 50 ? 80 : w >= 25 ? 60 : w >= 10 ? 40 : 20;
      desc.move_bp = bp;
   }
   if (move.GetName() == "Facade")
   {
      if (attacker.HasStatus({ENUMS::StatusName::par, 
         ENUMS::StatusName::psn, 
         ENUMS::StatusName::tox, 
         ENUMS::StatusName::brn})) 
      {
         bp = move.GetBP() * 2;
         desc.move_bp = bp;
      }
   }
   if (move.GetName() == "Nature Power")
   {
      move.SetMoveCategory(ENUMS::MoveCategory::Physical);
      bp = 60;
      desc.move_name = "Swift";
   }
   if (move.GetName() == "Triple Kick")
   {
      bp = hit * 10;
      desc.move_bp = move.GetHits() == 2 ? 30 : move.GetHits() == 3 ? 60 : 10;
   }

   return bp;
}

Result::Result CalculateADV
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon attacker,
   Pokemon::Pokemon defender,
   Move::Move move,
   State::Field field
) 
{
   CalcUtil::CheckAirLock(attacker, field);
   CalcUtil::CheckAirLock(defender, field);
   CalcUtil::CheckForecast(attacker, field.weather);
   CalcUtil::CheckForecast(defender, field.weather);
   CalcUtil::CheckIntimidate(gen, attacker, defender);
   CalcUtil::CheckIntimidate(gen, defender, attacker);
   attacker.SetStat(ENUMS::StatID::spe, 
                    CalcUtil::GetFinalSpeed(gen, attacker, field, field.attacker_side));
   defender.SetStat(ENUMS::StatID::spe,
                    CalcUtil::GetFinalSpeed(gen, defender, field, field.defender_side));

   Description::RawDescription desc = 
   {
      .attacker_name = attacker.GetName(),
      .defender_name = defender.GetName(),
      .move_name = move.GetName(),
   };

   Result::Result result(gen, attacker, defender, move, field, 0, desc);

   if (move.GetMoveCategory() == ENUMS::MoveCategory::Status && !move.Named({"Nature Power"}))
   {
      return result;
   }

   if (field.defender_side.is_protected) 
   {
      desc.is_protected = true;
      return result;
   }

   if (move.Named({"Weather Ball"})) 
   {
      move.SetType
      (
         field.HasWeather({ENUMS::Weather::Sun}) ? ENUMS::TypeName::Fire
         : field.HasWeather({ENUMS::Weather::Rain}) ? ENUMS::TypeName::Water
         : field.HasWeather({ENUMS::Weather::Sand}) ? ENUMS::TypeName::Rock
         : field.HasWeather({ENUMS::Weather::Hail}) ? ENUMS::TypeName::Ice
         : ENUMS::TypeName::Normal
      );
      move.SetMoveCategory(move.GetType() == ENUMS::TypeName::Rock 
         ? ENUMS::MoveCategory::Physical : ENUMS::MoveCategory::Special);
      desc.weather = field.weather;
      desc.move_type = move.GetType();
      desc.move_bp = move.GetBP();
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
       defender.GetTypes().at(0) != defender.GetTypes().at(1)) 
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

   if ((defender.HasAbility({"Flash Fire"}) && move.HasType({ENUMS::TypeName::Fire})) ||
       (defender.HasAbility({"Levitate"}) && move.HasType({ENUMS::TypeName::Ground})) ||
       (defender.HasAbility({"Volt Absorb"}) && move.HasType({ENUMS::TypeName::Electric})) ||
       (defender.HasAbility({"Water Absorb"}) && move.HasType({ENUMS::TypeName::Water})) ||
       (defender.HasAbility({"Wonder Guard"}) && !move.HasType({ENUMS::TypeName::QQQ}) && type_eff <= 1) ||
       (defender.HasAbility({"Soundproof"}) && move.GetMoveFlags().sound)
   ) 
   {
      desc.defender_ability = defender.GetAbility();
      return result;
   }

   desc.hp_evs = CalcUtil::GetStatDescriptionText(gen, defender, ENUMS::StatID::hp);

   int fixed_damage = CalcUtil::HandleFixedDamageMoves(attacker, move);
   if (fixed_damage) 
   {
      result.SetDamage(fixed_damage);
      return result;
   }

   if (move.GetHits() > 1) 
   {
      desc.hits = move.GetHits();
   }

   int bp = CalculateBasePowerADV(attacker, defender, move, desc);

   if (bp == 0) 
   {
      return result;
   }
   CalculateBPModsADV(attacker, move, desc, bp);

   bool is_critical = move.GetIsCrit() && !defender.HasAbility({"Battle Armor", "Shell Armor"});
   int at = CalculateAttackADV(gen, attacker, defender, move, desc, is_critical);
   int df = CalculateDefenseADV(gen, defender, move, desc, is_critical);

   int lv = attacker.GetLevel();
   int base_damage = (((((2 * lv) / 5 + 2) * at * bp) / df) / 50);

   CalculateFinalModsADV(base_damage, attacker, move, field, desc, is_critical);

   base_damage = std::floor(base_damage * type_eff);
   int damage_out[16];
   for (int i = 85; i <= 100; i++) 
   {
      damage_out[i - 85] = std::max(1, ((base_damage * i) / 100));
   }

   if ((move.GetDropsStats() && move.GetTimesUsed() > 1) || move.GetHits() > 1) 
   {
      // store boosts so intermediate boosts don't show.
      int orig_def_boost = desc.defense_boost ? *desc.defense_boost : 0;
      int orig_atk_boost = desc.attack_boost ? *desc.attack_boost : 0;
      int num_attacks = 1;
      if (move.GetDropsStats() && move.GetTimesUsed() > 1) 
      {
         desc.move_turns = "over " + std::to_string(move.GetTimesUsed()) + " turns";
         num_attacks = move.GetTimesUsed();
      } 
      else 
      {
         num_attacks = move.GetHits() ? *move.GetHits() : 1;
      }
      std::pair<bool, bool> used_items{false, false};
      for (int times = 1; times < num_attacks; times++) 
      {
         used_items = CalcUtil::CheckMultihitBoost
         (
            gen, 
            attacker, 
            defender, 
            move,
            field, 
            desc, 
            used_items.first, 
            used_items.second
         );
         int new_at = CalculateAttackADV(gen, attacker, defender, move, desc, is_critical);
         int new_bp = CalculateBasePowerADV(attacker, defender, move, desc);
         CalculateBPModsADV(attacker, move, desc, new_bp);
         int new_base_dmg = (((((2 * lv) / 5 + 2) * new_at * new_bp) / df) / 50);
         CalculateFinalModsADV(new_base_dmg, attacker, move, field, desc, is_critical);
         new_base_dmg = std::floor(new_base_dmg * type_eff);

         int damage_multiplier = 85;
         for (auto& affected_amount : damage_out) 
         {
            int new_final_damage = std::max
            (
               1,
               static_cast<int>(std::floor((new_base_dmg * damage_multiplier) / 100.0))
            );

            damage_multiplier++;

            affected_amount += new_final_damage;
         }
      }
      desc.defense_boost = orig_def_boost;
      desc.attack_boost = orig_atk_boost;
   }

   std::vector<int> temp_damage(std::begin(damage_out), std::end(damage_out));
   result.SetDamage(temp_damage);

   return result;
}

}
}
}