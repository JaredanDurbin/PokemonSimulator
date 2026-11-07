#include "./../include/mechanics/gen4.hpp"

#include <iostream>

#include "./../include/calc_util.hpp"
#include "./../include/description.hpp"
#include "./../include/data/items.h"

namespace PokemonDamageCalcCPP
{
namespace Mechanics
{
namespace GEN4
{

int CalculateBasePowerDPP
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   int hit = 1
)
{
   int base_power = move.GetBP();
   std::string turn_order = attacker.GetStats().at(ENUMS::StatID::spe) > 
                            defender.GetStats().at(ENUMS::StatID::spe) 
                            ? "first" 
                            : "last";
   if (move.GetName() == "Brine")
   {
      if (defender.CurHP() <= defender.MaxHP() / 2) 
      {
         base_power *= 2;
         desc.move_bp = base_power;
      }
   }
   else if (move.GetName() == "Eruption" ||
       move.GetName() == "Water Spout")
   {
      base_power = std::max(1, ((base_power * attacker.CurHP()) / attacker.MaxHP()));
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Facade")
   {
      if (attacker.HasStatus({ENUMS::StatusName::par, 
                              ENUMS::StatusName::psn, 
                              ENUMS::StatusName::tox, 
                              ENUMS::StatusName::brn})) 
      {
         base_power = move.GetBP() * 2;
         desc.move_bp = base_power;
      }
   }
   else if (move.GetName() == "Flail" ||
       move.GetName() == "Reversal")
   {
      int p = ((64 * attacker.CurHP()) / attacker.MaxHP());
      base_power = p <= 1 ? 200 : p <= 5 ? 150 : p <= 12 ? 100 : p <= 21 ? 80 : p <= 42 ? 40 : 20;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Fling")
   {
      base_power = Data::Items::Instance().GetFlingPower(attacker.GetItem());
      desc.move_bp = base_power;
      desc.attacker_item = attacker.GetItem();
   }
   else if (move.GetName() == "Grass Knot" ||
       move.GetName() == "Low Kick")
   {
      float w = defender.GetWeight();
      base_power = w >= 200 ? 120 : w >= 100 ? 100 : w >= 50 ? 80 : w >= 25 ? 60 : w >= 10 ? 40 : 20;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Gyro Ball")
   {
      base_power = std::min(150, ((25 * defender.GetStats().at(ENUMS::StatID::spe)) / 
                                        attacker.GetStats().at(ENUMS::StatID::spe)));
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Payback")
   {
      if (turn_order != "first") 
      {
         base_power *= 2;
         desc.move_bp = base_power;
      }
   }
   else if (move.GetName() == "Punishment")
   {
      base_power = std::min(200, 60 + 20 * CalcUtil::CountBoosts(gen, defender.GetBoosts()));
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Wake-Up Slap")
   {
      if (defender.HasStatus({ENUMS::StatusName::slp})) 
      {
         base_power *= 2;
         desc.move_bp = base_power;
      }
   }
   else if (move.GetName() == "Nature Power")
   {
      move.SetMoveCategory(ENUMS::MoveCategory::Special);
      move.SetSecondaries(true);
      base_power = 80;
      desc.move_name = "Tri Attack";
   }
   else if (move.GetName() == "Crush Grip" ||
       move.GetName() == "Wring Out")
   {
      base_power = std::floor((defender.CurHP() * 120) / defender.MaxHP()) + 1;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Triple Kick")
   {
      base_power = hit * 10;
      desc.move_bp = move.GetHits() == 2 ? 30 : move.GetHits() == 3 ? 60 : 10;
   }
   else if (move.GetName() == "Weather Ball")
   {
      base_power = move.GetBP() * (field.weather ? 2 : 1);
      desc.move_bp = base_power;
   }
   else
   {
      base_power = move.GetBP();
   }

   return base_power;
}

void CalculateBPModsDPP
(
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   int& base_power
) 
{
   if (field.attacker_side.is_helping_hand) 
   {
      base_power = std::floor(base_power * 1.5);
      desc.is_helping_hand = true;
   }

   bool is_physical = move.GetMoveCategory() == ENUMS::MoveCategory::Physical;
   if ((attacker.HasItem({"Muscle Band"}) && is_physical) ||
       (attacker.HasItem({"Wise Glasses"}) && !is_physical)) 
   {
      base_power = std::floor(base_power * 1.1);
      desc.attacker_item = attacker.GetItem();
   } else if (attacker.GetItem() && 
              move.HasType({*Data::Items::Instance().GetItemBoostType(*attacker.GetItem())}) ||
              (attacker.HasItem({"Adamant Orb"}) &&
               attacker.Named({"Dialga"}) &&
               move.HasType({ENUMS::TypeName::Steel, ENUMS::TypeName::Dragon})) ||
              (attacker.HasItem({"Lustrous Orb"}) &&
               attacker.Named({"Palkia"}) &&
               move.HasType({ENUMS::TypeName::Water, ENUMS::TypeName::Dragon})) ||
              (attacker.HasItem({"Griseous Orb"}) &&
               attacker.Named({"Giratina-Origin"}) &&
               move.HasType({ENUMS::TypeName::Ghost, ENUMS::TypeName::Dragon}))
   ) 
   {
      base_power = std::floor(base_power * 1.2);
      desc.attacker_item = attacker.GetItem();
   }

   if ((attacker.HasAbility({"Reckless"}) && (move.GetRecoil() || move.GetHasCrashDamage())) ||
       (attacker.HasAbility({"Iron Fist"}) && move.GetMoveFlags().punch)) 
   {
      base_power = std::floor(base_power * 1.2);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if ((attacker.CurHP() <= attacker.MaxHP() / 3 &&
             ((attacker.HasAbility({"Overgrow"}) && move.HasType({ENUMS::TypeName::Grass})) ||
              (attacker.HasAbility({"Blaze"}) && move.HasType({ENUMS::TypeName::Fire})) ||
              (attacker.HasAbility({"Torrent"}) && move.HasType({ENUMS::TypeName::Water})) ||
              (attacker.HasAbility({"Swarm"}) && move.HasType({ENUMS::TypeName::Bug})))) ||
            (attacker.HasAbility({"Technician"}) && base_power <= 60)
   ) {
      base_power = std::floor(base_power * 1.5);
      desc.attacker_ability = attacker.GetAbility();
   }

   if ((defender.HasAbility({"Heatproof"}) && move.HasType({ENUMS::TypeName::Fire})) ||
       (defender.HasAbility({"Thick Fat"}) && 
        (move.HasType({ENUMS::TypeName::Fire, ENUMS::TypeName::Ice})))) 
   {
      base_power = std::floor(base_power * 0.5);
      desc.defender_ability = defender.GetAbility();
   } 
   else if (defender.HasAbility({"Dry Skin"}) && move.HasType({ENUMS::TypeName::Fire})) 
   {
      base_power = std::floor(base_power * 1.25);
      desc.defender_ability = defender.GetAbility();
   }
}

int GetSimpleModifiedStat(const int stat, const int mod) 
{
   int simple_mod = std::min(6, std::max(-6, mod * 2));
   return simple_mod > 0
      ? std::floor((stat * (2 + simple_mod)) / 2)
      : simple_mod < 0 
         ? std::floor((stat * 2) / (2 - simple_mod)) 
         : stat;
}

int CalculateAttackDPP
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical
) 
{
   bool is_physical = move.GetMoveCategory() == ENUMS::MoveCategory::Physical;
   ENUMS::StatID attack_stat = is_physical ? ENUMS::StatID::atk : ENUMS::StatID::spa;
   desc.attack_evs = CalcUtil::GetStatDescriptionText(gen, attacker, attack_stat, attacker.GetNature());
   int attack = 0;
   int attack_boost = attacker.GetBoosts().at(attack_stat);
   int raw_attack = attacker.GetRawStats().at(attack_stat);
   if (attack_boost == 0 || (is_critical && attack_boost < 0)) 
   {
      attack = raw_attack;
   } 
   else if (defender.HasAbility({"Unaware"})) 
   {
      attack = raw_attack;
      desc.defender_ability = defender.GetAbility();
   } 
   else if (attacker.HasAbility({"Simple"})) 
   {
      attack = GetSimpleModifiedStat(raw_attack, attack_boost);
      desc.attacker_ability = attacker.GetAbility();
      desc.attack_boost = attack_boost;
   } 
   else 
   {
      attack = CalcUtil::GetModifiedStat(raw_attack, attack_boost);
      desc.attack_boost = attack_boost;
   }

   if (is_physical && attacker.HasAbility({"Pure Power", "Huge Power"})) 
   {
      attack *= 2;
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (field.HasWeather({ENUMS::Weather::Sun}) &&
            (attacker.HasAbility({is_physical ? "Flower Gift" : "Solar Power"}))) 
   {
      attack = std::floor(attack * 1.5);
      desc.attacker_ability = attacker.GetAbility();
      desc.weather = field.weather;
   } 
   else if (field.attacker_side.is_flower_gift && 
            field.HasWeather({ENUMS::Weather::Sun}) && 
            is_physical) 
   {
      attack = std::floor(attack * 1.5);
      desc.weather = field.weather;
      desc.is_flower_gift_attacker = true;
   } 
   else if 
   (
      (is_physical &&
       (attacker.HasAbility({"Hustle"}) || 
        (attacker.HasAbility({"Guts"}) && attacker.HasStatus())) ||
       (!is_physical && attacker.GetAbilityOn() && attacker.HasAbility({"Plus", "Minus"})))
   ) 
   {
      attack = std::floor(attack * 1.5);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (is_physical && attacker.HasAbility({"Slow Start"}) && attacker.GetAbilityOn()) 
   {
      attack = std::floor(attack / 2);
      desc.attacker_ability = attacker.GetAbility();
   }

   if ((is_physical ? attacker.HasItem({"Choice Band"}) : attacker.HasItem({"Choice Specs"})) ||
       (!is_physical && attacker.HasItem({"Soul Dew"}) && attacker.Named({"Latios", "Latias"}))) 
   {
      attack = std::floor(attack * 1.5);
      desc.attacker_item = attacker.GetItem();
   } 
   else if 
   (
      (attacker.HasItem({"Light Ball"}) && attacker.Named({"Pikachu"})) ||
      (attacker.HasItem({"Thick Club"}) && attacker.Named({"Cubone", "Marowak"}) && is_physical) ||
      (attacker.HasItem({"Deep Sea Tooth"}) && attacker.Named({"Clamperl"}) && !is_physical)
   ) 
   {
      attack *= 2;
      desc.attacker_item = attacker.GetItem();
   }

   return attack;
}

int CalculateDefenseDPP
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical
) 
{
   bool is_physical = move.GetMoveCategory() == ENUMS::MoveCategory::Physical;
   ENUMS::StatID defense_stat = is_physical ? ENUMS::StatID::def : ENUMS::StatID::spd;
   desc.defense_evs 
      = CalcUtil::GetStatDescriptionText(gen, defender, defense_stat, defender.GetNature());
   int defense = 0;
   int defense_boost = defender.GetBoosts().at(defense_stat);
   int raw_defense = defender.GetRawStats().at(defense_stat);
   if (defense_boost == 0 || (is_critical && defense_boost > 0)) {
      defense = raw_defense;
   } else if (attacker.HasAbility({"Unaware"})) 
   {
      defense = raw_defense;
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (defender.HasAbility({"Simple"})) 
   {
      defense = GetSimpleModifiedStat(raw_defense, defense_boost);
      desc.defender_ability = defender.GetAbility();
      desc.defense_boost = defense_boost;
   } 
   else 
   {
      defense = CalcUtil::GetModifiedStat(raw_defense, defense_boost);
      desc.defense_boost = defense_boost;
   }

   if (defender.HasAbility({"Marvel Scale"}) && defender.HasStatus() && is_physical) 
   {
      defense = std::floor(defense * 1.5);
      desc.defender_ability = defender.GetAbility();
   } 
   else if (defender.HasAbility({"Flower Gift"}) && 
            field.HasWeather({ENUMS::Weather::Sun}) && 
            !is_physical) 
   {
      defense = std::floor(defense * 1.5);
      desc.defender_ability = defender.GetAbility();
      desc.weather = field.weather;
   } 
   else if (field.defender_side.is_flower_gift && 
            field.HasWeather({ENUMS::Weather::Sun}) && 
            !is_physical) 
   {
      defense = std::floor(defense * 1.5);
      desc.weather = field.weather;
      desc.is_flower_gift_defender = true;
   }

   if (defender.HasItem({"Soul Dew"}) && 
       defender.Named({"Latios", "Latias"}) && 
       !is_physical) 
   {
      defense = std::floor(defense * 1.5);
      desc.defender_item = defender.GetItem();
   } 
   else if 
   (
      (defender.HasItem({"Deep Sea Scale"}) && 
       defender.Named({"Clamperl"}) && 
       !is_physical) ||
      (defender.HasItem({"Metal Powder"}) && 
       defender.Named({"Ditto"}) && 
       is_physical)
   ) 
   {
      defense *= 2;
      desc.defender_item = defender.GetItem();
   }

   if (field.HasWeather({ENUMS::Weather::Sand}) && 
       defender.HasType({ENUMS::TypeName::Rock}) && 
       !is_physical) 
   {
      defense = std::floor(defense * 1.5);
      desc.weather = field.weather;
   }

   if (move.Named({"Explosion"}) || move.Named({"Self-Destruct"})) 
   {
      defense = std::floor(defense * 0.5);
   }

   if (defense < 1) 
   {
      defense = 1;
   }

   return defense;
}

void CalculateFinalModsDPP
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

   if (field.game_type != ENUMS::GameType::Singles &&
       (move.GetTarget() == ENUMS::MoveTarget::all_adjacent ||
        move.GetTarget() == ENUMS::MoveTarget::all_adjacent_foes))
   {
      base_damage = std::floor((base_damage * 3) / 4);
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
      (move.Named({"Solar Beam"}) && field.HasWeather({ENUMS::Weather::Rain, 
                                                       ENUMS::Weather::Sand, 
                                                       ENUMS::Weather::Hail}))
   ) 
   {
      base_damage = std::floor(base_damage * 0.5);
      desc.weather = field.weather;
   }

   if (attacker.HasAbility({"Flash Fire"}) && 
       attacker.GetAbilityOn() && 
       move.HasType({ENUMS::TypeName::Fire})) 
   {
      base_damage = std::floor(base_damage * 1.5);
      desc.attacker_ability = "Flash Fire";
   }

   base_damage += 2;

   if (is_critical) 
   {
      if (attacker.HasAbility({"Sniper"})) 
      {
         base_damage *= 3;
         desc.attacker_ability = attacker.GetAbility();
      } 
      else 
      {
         base_damage *= 2;
      }
      desc.is_critical = is_critical;
   }

   if (attacker.HasItem({"Life Orb"})) 
   {
      base_damage = std::floor(base_damage * 1.3);
      desc.attacker_item = attacker.GetItem();
   }

   if (move.Named({"Pursuit"}) && field.defender_side.is_switching == ENUMS::Switching::out) 
   {
      // technician negates switching boost, thanks DaWoblefet
      if (attacker.HasAbility({"Technician"})) 
      {
         base_damage = std::floor(base_damage * 1);
      } 
      else 
      {
         base_damage = std::floor(base_damage * 2);
         desc.is_switching = "out";
      }
   }
}

Result::Result CalculateDPP
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon attacker,
   Pokemon::Pokemon defender,
   Move::Move move,
   State::Field field
)
{
   // #region Initial

   CalcUtil::CheckAirLock(attacker, field);
   CalcUtil::CheckAirLock(defender, field);
   CalcUtil::CheckForecast(attacker, field.weather);
   CalcUtil::CheckForecast(defender, field.weather);
   CalcUtil::CheckItem(attacker);
   CalcUtil::CheckItem(defender);
   CalcUtil::CheckIntimidate(gen, attacker, defender);
   CalcUtil::CheckIntimidate(gen, defender, attacker);
   CalcUtil::CheckDownload(attacker, defender);
   CalcUtil::CheckDownload(defender, attacker);
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

   // DEBUG
   //std::cout << "DEBUG: " << "First return.\n";

   if (move.GetMoveCategory() == ENUMS::MoveCategory::Status && !move.Named({"Nature Power"}))
   {
      return result;
   }

   if (field.defender_side.is_protected && !move.GetBreaksProtect()) 
   {
      desc.is_protected = true;
      return result;
   }

   if (attacker.HasAbility({"Mold Breaker"})) 
   {
      defender.SetAbility("");
      desc.attacker_ability = attacker.GetAbility();
   }

   bool is_critical = move.GetIsCrit() && !defender.HasAbility({"Battle Armor", "Shell Armor"});

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
      desc.weather = field.weather;
      desc.move_type = move.GetType();
   } 
   else if (move.Named({"Judgment"}) && attacker.GetItem() && 
            attacker.GetItem().value().find("Plate") != std::string::npos) 
   {
      move.SetType(*Data::Items::Instance().GetItemBoostType(attacker.GetItem().value()));
   } 
   else if (move.Named({"Natural Gift"}) && attacker.GetItem() &&
            attacker.GetItem().value().ends_with("Berry"))
   {
      Data::Items::NaturalGift gift = Data::Items::Instance().GetNaturalGift(gen, attacker.GetItem().value());
      move.SetType(gift.t);
      move.SetBP(gift.p);
      desc.attacker_item = attacker.GetItem().value();
      desc.move_bp = move.GetBP();
      desc.move_type = move.GetType();
   }

   if (attacker.HasAbility({"Normalize"}) && !move.Named({"Struggle"})) 
   {
      move.SetType(ENUMS::TypeName::Normal);
      desc.attacker_ability = attacker.GetAbility();
   }

   bool is_ghost_revealed = attacker.HasAbility({"Scrappy"}) || field.defender_side.is_foresight;

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

   float type_eff1 = CalcUtil::GetMoveEffectiveness
   (
      gen, 
      move, 
      defender.GetTypes().at(0),
      is_ghost_revealed,
      field.is_gravity ? *field.is_gravity : false
   );
   float type_eff2 = defender.GetTypes().size() > 1 ? 
   CalcUtil::GetMoveEffectiveness
   (
      gen, 
      move, 
      defender.GetTypes().at(1),
      is_ghost_revealed,
      field.is_gravity ? *field.is_gravity : false
   ) : 1;
   float type_eff = type_eff1 * type_eff2;

   // Klutz doesn't let Iron Ball ground in generation 4
   if (type_eff == 0 && move.HasType({ENUMS::TypeName::Ground}) &&
       (defender.HasItem({"Iron Ball"}) && !defender.HasAbility({"Klutz"}))) 
   {
      if (type_eff1 == 0) 
      {
         type_eff1 = 1;
      } 
      else if (defender.GetTypes().size() > 1 && 
               type_eff2 == 0) 
      {
         type_eff2 = 1;
      }
      type_eff = type_eff1 * type_eff2;
   }

   // DEBUG
   //std::cout << "DEBUG: " << "Type effectiveness 0?\n";

   if (type_eff == 0) 
   {
      return result;
   }

   bool ignores_wonder_guard = move.HasType({ENUMS::TypeName::QQQ}) || move.Named({"Fire Fang"});
   if ((!ignores_wonder_guard && defender.HasAbility({"Wonder Guard"}) && type_eff <= 1) ||
       (move.HasType({ENUMS::TypeName::Fire}) && 
        defender.HasAbility({"Flash Fire"})) ||
       (move.HasType({ENUMS::TypeName::Water}) && 
        defender.HasAbility({"Dry Skin", "Water Absorb"})) ||
       (move.HasType({ENUMS::TypeName::Electric}) && 
        defender.HasAbility({"Motor Drive", "Volt Absorb"})) ||
       (move.HasType({ENUMS::TypeName::Ground}) && 
        !field.is_gravity &&
        !defender.HasItem({"Iron Ball"}) && 
        defender.HasAbility({"Levitate"})) ||
       (move.GetMoveFlags().sound && defender.HasAbility({"Soundproof"}))
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

   bool is_physical = move.GetMoveCategory() == ENUMS::MoveCategory::Physical;

   // #endregion
   // #region Base Power

   int base_power = CalculateBasePowerDPP(gen, attacker, defender, move, field, desc);
   if (base_power == 0) 
   {
      return result;
   }
   CalculateBPModsDPP(attacker, defender, move, field, desc, base_power);

   // #endregion
   // #region (Special) Attack
   int attack = CalculateAttackDPP(gen, attacker, defender, move, field, desc, is_critical);

   // #endregion
   // #region (Special) Defense
   int defense = CalculateDefenseDPP(gen, attacker, defender, move, field, desc, is_critical);

   // #endregion
   // #region Damage

   int base_damage = (((((2 * attacker.GetLevel()) / 5 + 2) * base_power * attack) / 50) / defense);

   if (attacker.HasStatus({ENUMS::StatusName::brn}) && 
       is_physical && 
       !attacker.HasAbility({"Guts"})) 
   {
      base_damage = std::floor(base_damage * 0.5);
      desc.is_burned = true;
   }

   CalculateFinalModsDPP(base_damage, attacker, move, field, desc, is_critical);

   // the random factor is applied between the LO mod and the STAB mod, so don"t apply anything
   // below this until we're inside the loop
   float stab_mod = 1;
   if (move.HasType(attacker.GetTypes())) 
   {
      if (attacker.HasAbility({"Adaptability"})) 
      {
         stab_mod = 2;
         desc.attacker_ability = attacker.GetAbility();
      } 
      else 
      {
         // DEBUG
         //std::cout << "DEBUG: " << "Applying stab mod?\n";

         stab_mod = 1.5;
      }
   }

   float filter_mod = 1;
   if (defender.HasAbility({"Filter", "Solid Rock"}) && type_eff > 1) 
   {
      filter_mod = 0.75;
      desc.defender_ability = defender.GetAbility();
   }
   float ebelt_mod = 1;
   if (attacker.HasItem({"Expert Belt"}) && type_eff > 1) 
   {
      ebelt_mod = 1.2;
      desc.attacker_item = attacker.GetItem();
   }
   int tinted_mod = 1;
   if (attacker.HasAbility({"Tinted Lens"}) && type_eff < 1) 
   {
      tinted_mod = 2;
      desc.attacker_ability = attacker.GetAbility();
   }
   float berry_mod = 1;
   auto temp = Data::Items::Instance().GetBerryResistType(defender.GetItem() 
      ? *defender.GetItem() 
      : "");
   if (move.HasType({temp ? *temp : ENUMS::TypeName::QQQ}) &&
      (type_eff > 1 || move.HasType({ENUMS::TypeName::Normal}))) 
   {
      berry_mod = 0.5;
      desc.defender_item = defender.GetItem();
   }

   // DEBUG
   //std::cout << "DEBUG: " << "Near damage out.\n";

   int damage_out[16];
   for (int i = 0; i < 16; i++) 
   {
      damage_out[i] = std::floor((base_damage * (85 + i)) / 100);
      damage_out[i] = std::floor(damage_out[i] * stab_mod);
      damage_out[i] = std::floor(damage_out[i] * type_eff1);
      damage_out[i] = std::floor(damage_out[i] * type_eff2);
      damage_out[i] = std::floor(damage_out[i] * filter_mod);
      damage_out[i] = std::floor(damage_out[i] * ebelt_mod);
      damage_out[i] = std::floor(damage_out[i] * tinted_mod);
      damage_out[i] = std::floor(damage_out[i] * berry_mod);
      damage_out[i] = std::max(1, damage_out[i]);
   }

   if ((move.GetDropsStats() && move.GetTimesUsed() > 1) || move.GetHits() > 1) {
      // store boosts so intermediate boosts don"t show.
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
         num_attacks = move.GetHits() ? *move.GetHits() : 0;
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
         int new_base_power = CalculateBasePowerDPP(gen, attacker, defender, move, field, desc);
         CalculateBPModsDPP(attacker, defender, move, field, desc, new_base_power);
         int new_atk = CalculateAttackDPP(gen, attacker, defender, move, field, desc, is_critical);
         int base_damage = (((((2 * attacker.GetLevel()) / 5 + 2) * 
                              new_base_power * new_atk) / 50) / defense);
         if (attacker.HasStatus({ENUMS::StatusName::brn}) && 
             is_physical && 
             !attacker.HasAbility({"Guts"})) 
         {
            base_damage = std::floor(base_damage * 0.5);
            desc.is_burned = true;
         }
         CalculateFinalModsDPP(base_damage, attacker, move, field, desc, is_critical);

         int damage_multiplier = 0;
         for (auto& affected_amount : damage_out)
         {
            int new_final_damage = 0;

            new_final_damage = std::floor((base_damage * (85 + damage_multiplier)) / 100.0);
            new_final_damage = std::floor(new_final_damage * stab_mod);
            new_final_damage = std::floor(new_final_damage * type_eff1);
            new_final_damage = std::floor(new_final_damage * type_eff2);
            new_final_damage = std::floor(new_final_damage * filter_mod);
            new_final_damage = std::floor(new_final_damage * ebelt_mod);
            new_final_damage = std::floor(new_final_damage * tinted_mod);

            new_final_damage = std::max(1, new_final_damage);

            ++damage_multiplier;

            affected_amount += new_final_damage;
         }
      }
      desc.defense_boost = orig_def_boost;
      desc.attack_boost = orig_atk_boost;
   }

   // #endregion
   std::vector<int> temp_damage(std::begin(damage_out), std::end(damage_out));
   result.SetDamage(temp_damage);

   return result;
}

}
}
}