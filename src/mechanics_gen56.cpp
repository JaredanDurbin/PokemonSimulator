#include "./../include/mechanics/gen56.hpp"

#include <array>
#include <iostream>
#include <utility>

#include "./../include/calc_util.hpp"
#include "./../include/description.hpp"
#include "./../include/data/items.h"
#include "./../include/data/types.h"


namespace PokemonDamageCalcCPP
{
namespace Mechanics
{
namespace GEN56
{

std::vector<int> CalculateBPModsBWXY
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   int& base_power,
   bool has_ate_ability_type_change,
   const std::string& turn_order
) 
{
   std::vector<int> bp_mods = {};

   bool resisted_knock_off_damage =
      !defender.GetItem() ||
      (defender.Named({"Giratina-Origin"}) && defender.HasItem({"Griseous Orb"})) ||
      (defender.GetName().find("Arceus") != std::string::npos && 
       defender.GetItem().value().find("Plate")) ||
      (defender.GetName().find("Genesect") != std::string::npos && 
       defender.GetItem().value().find("Drive") != std::string::npos) ||
      (defender.Named({"Groudon", "Groudon-Primal"}) && defender.HasItem({"Red Orb"})) ||
      (defender.Named({"Kyogre", "Kyogre-Primal"}) && defender.HasItem({"Blue Orb"}));

   // The last case only applies when the Pokemon is holding the Mega Stone that matches its species
   // (or when it"s already a Mega-Evolution)
   if (!resisted_knock_off_damage && defender.GetItem()) 
   {
      resisted_knock_off_damage = defender.GetName().find
      (
         Data::Items::Instance().GetMegaEvolves(static_cast<int>(gen), *defender.GetItem())
      ) != std::string::npos;
   }


   // Use BasePower after moves with custom BP to determine if Technician should boost
   if ((attacker.HasAbility({"Technician"}) && base_power <= 60) ||
       (attacker.HasAbility({"Flare Boost"}) &&
        attacker.HasStatus({ENUMS::StatusName::brn}) && 
        move.GetMoveCategory() == ENUMS::MoveCategory::Special) ||
       (attacker.HasAbility({"Toxic Boost"}) &&
        attacker.HasStatus({ENUMS::StatusName::psn, ENUMS::StatusName::tox}) && 
        move.GetMoveCategory() == ENUMS::MoveCategory::Physical)
   ) 
   {
      bp_mods.push_back(6144);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (attacker.HasAbility({"Analytic"}) && turn_order != "first") 
   {
      bp_mods.push_back(5325);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if 
   (
      attacker.HasAbility({"Sand Force"}) &&
      field.HasWeather({ENUMS::Weather::Sand}) &&
      move.HasType({ENUMS::TypeName::Rock, 
                    ENUMS::TypeName::Ground, 
                    ENUMS::TypeName::Steel})
   ) 
   {
      bp_mods.push_back(5325);
      desc.attacker_ability = attacker.GetAbility();
      desc.weather = field.weather;
   } 
   else if 
   (
      (attacker.HasAbility({"Reckless"}) && 
       (move.GetRecoil() || move.GetHasCrashDamage())) ||
      (attacker.HasAbility({"Iron Fist"}) && move.GetMoveFlags().punch)
   ) 
   {
      bp_mods.push_back(4915);
      desc.attacker_ability = attacker.GetAbility();
   }

   if (defender.HasAbility({"Heatproof"}) && 
       move.HasType({ENUMS::TypeName::Fire})) 
   {
      bp_mods.push_back(2048);
      desc.defender_ability = defender.GetAbility();
   } 
   else if (defender.HasAbility({"Dry Skin"}) && 
            move.HasType({ENUMS::TypeName::Fire})) 
   {
      bp_mods.push_back(5120);
      desc.defender_ability = defender.GetAbility();
   }

   if (attacker.HasAbility({"Sheer Force"}) && move.GetSecondaries()) 
   {
      bp_mods.push_back(5325);
      desc.attacker_ability = attacker.GetAbility();
   }

   if (attacker.HasAbility({"Rivalry"}) && 
       (!attacker.GetGender() || 
        (attacker.GetGender() && *attacker.GetGender() != ENUMS::GenderName::N)) && 
       (!defender.GetGender() || 
        (defender.GetGender() && *defender.GetGender() != ENUMS::GenderName::N)))
   {
      if (*attacker.GetGender() == defender.GetGender()) 
      {
         bp_mods.push_back(5120);
         desc.rivalry = "buffed";
      } 
      else 
      {
         bp_mods.push_back(3072);
         desc.rivalry = "nerfed";
      }
      desc.attacker_ability = attacker.GetAbility();
   }

   if (attacker.GetItem() && 
       Data::Items::Instance().GetItemBoostType(*attacker.GetItem()) == move.GetType())
   {
      bp_mods.push_back(4915);
      desc.attacker_item = attacker.GetItem();
   } 
   else if 
   (
      (attacker.HasItem({"Muscle Band"}) && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical) ||
      (attacker.HasItem({"Wise Glasses"}) && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Special)
   ) 
   {
      bp_mods.push_back(4505);
      desc.attacker_item = attacker.GetItem();
   } 
   else if 
   (
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
      bp_mods.push_back(4915);
      desc.attacker_item = attacker.GetItem();
   } else if (attacker.HasItem
      (
         {Data::Types::Instance().TypeNameENUMToString(move.GetType()) + " Gem"}
      ))
   {
      bp_mods.push_back(static_cast<int>(gen) > 5 ? 5325 : 6144);
      desc.attacker_item = attacker.GetItem();
   }

   if ((move.Named({"Facade"}) && attacker.HasStatus({ENUMS::StatusName::brn, 
                                                      ENUMS::StatusName::par, 
                                                      ENUMS::StatusName::psn, 
                                                      ENUMS::StatusName::tox})) ||
         (move.Named({"Brine"}) && defender.CurHP() <= defender.MaxHP() / 2) ||
         (move.Named({"Venoshock"}) && defender.HasStatus({ENUMS::StatusName::psn, 
                                                           ENUMS::StatusName::tox}))) 
   {
      bp_mods.push_back(8192);
      desc.move_bp = base_power * 2;
   } 
   else if (static_cast<int>(gen) > 5 && move.Named({"Knock Off"}) && !resisted_knock_off_damage) 
   {
      bp_mods.push_back(6144);
      desc.move_bp = base_power * 1.5;
   } 
   else if (move.Named({"Solar Beam"}) && field.HasWeather({ENUMS::Weather::Rain, 
                                                            ENUMS::Weather::HeavyRain, 
                                                            ENUMS::Weather::Sand, 
                                                            ENUMS::Weather::Hail})) 
   {
      bp_mods.push_back(2048);
      desc.move_bp = base_power / 2;
      desc.weather = field.weather;
   }

   if (field.attacker_side.is_helping_hand) 
   {
      bp_mods.push_back(6144);
      desc.is_helping_hand = true;
   }

   if (has_ate_ability_type_change) 
   {
      bp_mods.push_back(5325);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if 
   (
      (attacker.HasAbility({"Mega Launcher"}) && move.GetMoveFlags().pulse) ||
      (attacker.HasAbility({"Strong Jaw"}) && move.GetMoveFlags().bite)
   ) 
   {
      bp_mods.push_back(6144);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (attacker.HasAbility({"Tough Claws"}) && move.GetMoveFlags().contact) 
   {
      bp_mods.push_back(5325);
      desc.attacker_ability = attacker.GetAbility();
   }

   std::string aura = Data::Types::Instance().TypeNameENUMToString(move.GetType()) + " Aura";
   bool is_attacker_aura = attacker.HasAbility({aura});
   bool is_defender_aura = defender.HasAbility({aura});
   bool is_user_aura_break = attacker.HasAbility({"Aura Break"}) || 
                           defender.HasAbility({"Aura Break"});
   bool is_field_aura_break = field.is_aura_break ? *field.is_aura_break : false;
   bool is_field_fairy_aura = field.is_fairy_aura && 
                           *field.is_fairy_aura &&
                           move.GetType() == ENUMS::TypeName::Fairy;
   bool is_field_dark_aura = field.is_dark_aura && 
                          *field.is_dark_aura && 
                          move.GetType() == ENUMS::TypeName::Dark;
   bool aura_active = is_attacker_aura || is_defender_aura || is_field_fairy_aura || is_field_dark_aura;
   bool aura_break = is_field_aura_break || is_user_aura_break;
   if (aura_active) 
   {
      if (aura_break) 
      {
         bp_mods.push_back(3072);
         desc.attacker_ability = attacker.GetAbility();
         desc.defender_ability = defender.GetAbility();
      } 
      else 
      {
         bp_mods.push_back(5448);
         if (is_attacker_aura) desc.attacker_ability = attacker.GetAbility();
         if (is_defender_aura) desc.defender_ability = defender.GetAbility();
      }
   }

   // It's not actually clear if the terrain modifiers are base damage mods like weather or are
   // base power mods like in Gen 7+, but the research doesn't exist for this yet so we match PS here
   if (CalcUtil::IsGrounded(attacker, field)) 
   {
      if 
      (
         (field.HasTerrain({ENUMS::Terrain::Electric_t}) && 
           move.HasType({ENUMS::TypeName::Electric})) ||
         (field.HasTerrain({ENUMS::Terrain::Grassy_t}) && 
          move.HasType({ENUMS::TypeName::Grass}))
      ) 
      {
         bp_mods.push_back(6144);
         desc.terrain = field.terrain;
      }
   }
   if (CalcUtil::IsGrounded(defender, field)) 
   {
      if 
      (
         (field.HasTerrain({ENUMS::Terrain::Misty_t}) && 
          move.HasType({ENUMS::TypeName::Dragon})) ||
         (field.HasTerrain({ENUMS::Terrain::Grassy_t}) && 
          move.Named({"Bulldoze", "Earthquake"}))
      ) 
      {
         bp_mods.push_back(2048);
         desc.terrain = field.terrain;
      }
   }

   return bp_mods;
}

int CalculateBasePowerBWXY
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon& attacker,
   Pokemon::Pokemon& defender,
   Move::Move& move,
   const State::Field& field,
   bool has_ate_ability_type_change,
   Description::RawDescription& desc,
   int hit
) 
{
   int base_power = 0;
   std::string turn_order = attacker.GetStats().at(ENUMS::StatID::spe) > 
                            defender.GetStats().at(ENUMS::StatID::spe) 
                            ? "first" 
                            : "last";

   if (move.GetName() == "Payback")
   {
      base_power = move.GetBP() * (turn_order == "last" ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Pursuit")
   {
      bool switching = field.defender_side.is_switching &&
         field.defender_side.is_switching == ENUMS::Switching::out;
      base_power = move.GetBP() * (switching ? 2 : 1);
      if (switching) desc.is_switching = "out";
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Electro Ball")
   {
      if (defender.GetStats().at(ENUMS::StatID::spe) == 0) 
      {
         defender.SetStat(ENUMS::StatID::spe, 1);
      }
      int r = (attacker.GetStats().at(ENUMS::StatID::spe) / 
               defender.GetStats().at(ENUMS::StatID::spe));
      base_power = r >= 4 ? 150 : r >= 3 ? 120 : r >= 2 ? 80 : r >= 1 ? 60 : 40;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Gyro Ball")
   {
      if (attacker.GetStats().at(ENUMS::StatID::spe) == 0) attacker.SetStat(ENUMS::StatID::spe, 1);
      base_power = std::min(150, ((25 * defender.GetStats().at(ENUMS::StatID::spe)) / 
                                        attacker.GetStats().at(ENUMS::StatID::spe)));
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Punishment")
   {
      base_power = std::min(200, 60 + 20 * CalcUtil::CountBoosts(gen, defender.GetBoosts()));
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Low Kick" ||
            move.GetName() == "Grass Knot")
   {
      float w = CalcUtil::GetWeight(defender, desc, "defender");
      base_power = w >= 200 ? 120 : w >= 100 ? 100 : w >= 50 ? 80 : w >= 25 ? 60 : w >= 10 ? 40 : 20;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Hex")
   {
      base_power = move.GetBP() * (defender.HasStatus() ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Heavy Slam" ||
            move.GetName() == "Heat Crash")
   {
      float wr = CalcUtil::GetWeight(attacker, desc, true) / 
                 CalcUtil::GetWeight(defender, desc, false);
      base_power = wr >= 5 ? 120 : wr >= 4 ? 100 : wr >= 3 ? 80 : wr >= 2 ? 60 : 40;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Stored Power" ||
            move.GetName() == "Power Trip")
   {
      base_power = 20 + 20 * CalcUtil::CountBoosts(gen, attacker.GetBoosts());
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Acrobatics")
   {
      base_power = move.GetBP() * (attacker.HasItem({"Flying Gem"}) || attacker.GetItem() ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Assurance")
   {
      base_power = move.GetBP() * (defender.HasAbility({"Parental Bond (Child)"}) ? 2 : 1);
      // NOTE: desc.attacker_ability = "Parental Bond" will already reflect this boost
   }
   else if (move.GetName() == "Wake-Up Slap")
   {
      base_power = move.GetBP() * (defender.HasStatus({ENUMS::StatusName::slp}) ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Smelling Salts")
   {
      base_power = move.GetBP() * (defender.HasStatus({ENUMS::StatusName::par}) ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Weather Ball")
   {
      base_power = move.GetBP() * (field.weather && 
                                   !field.HasWeather({ENUMS::Weather::StrongWinds}) ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Fling")
   {
      base_power = Data::Items::Instance().GetFlingPower(attacker.GetItem());
      desc.move_bp = base_power;
      desc.attacker_item = attacker.GetItem() ? *attacker.GetItem() : "";
   }
   else if (move.GetName() == "Eruption" ||
            move.GetName() == "Water Spout")
   {
      base_power = std::max(1, ((150 * attacker.CurHP()) / attacker.MaxHP()));
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Flail" ||
            move.GetName() == "Reversal")
   {
      int p = ((48 * attacker.CurHP()) / attacker.MaxHP());
      base_power = p <= 1 ? 200 : p <= 4 ? 150 : p <= 9 ? 100 : p <= 16 ? 80 : p <= 32 ? 40 : 20;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Nature Power")
   {
      if (gen == ENUMS::GenerationNumber::__5) 
      {
         move.SetMoveCategory(ENUMS::MoveCategory::Physical);
         move.SetTarget(ENUMS::MoveTarget::all_adjacent);
         base_power = 100;
         desc.move_name = "Earthquake";
      } 
      else 
      {
         move.SetMoveCategory(ENUMS::MoveCategory::Special);
         move.SetSecondaries(true);
         if (field.terrain)
         {
            switch (*field.terrain) 
            {
               case ENUMS::Terrain::Electric_t:
                  base_power = 90;
                  desc.move_name = "Thunderbolt";
                  break;

               case ENUMS::Terrain::Grassy_t:
                  base_power = 90;
                  desc.move_name = "Energy Ball";
                  break;

               case ENUMS::Terrain::Misty_t:
                  base_power = 95;
                  desc.move_name = "Moonblast";
                  break;
            }
         }
         else
         {
            base_power = 80;
            desc.move_name = "Tri Attack";
         }
      }
   }
   // Triple Kick"s damage increases after each consecutive hit (10, 20, 30)
   else if (move.GetName() == "Triple Kick")
   {
      base_power = hit * 10;
      desc.move_bp = move.GetHits() 
         ? *move.GetHits() == 2 
            ? 30 
            : *move.GetHits() == 3 
            ? 60 
            : 10 
         : 10;
   }
   else if (move.GetName() == "Crush Grip" ||
            move.GetName() == "Wring Out")
   {
      base_power = 100 * std::floor((defender.CurHP() * 4096) / defender.MaxHP());
      base_power = (((120 * base_power + 2048 - 1) / 4096) / 100) || 1;
      desc.move_bp = base_power;
   }
   else
   {
      base_power = move.GetBP();
   }

   if (base_power == 0) 
   {
      return 0;
   }

   std::vector<int> bp_mods = CalculateBPModsBWXY
   (
      gen,
      attacker,
      defender,
      move,
      field,
      desc,
      base_power,
      has_ate_ability_type_change,
      turn_order
   );

   base_power = CalcUtil::OF16(std::max(1, CalcUtil::PokeRound
      ((
         base_power * CalcUtil::ChainMods(bp_mods, 41, 2097152)) / 4096
      )));
   return base_power;
}


std::vector<int> CalculateAtModsBWXY
(
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc
) 
{
   std::vector<int> at_mods = {};
   if (defender.HasAbility({"Thick Fat"}) && 
       move.HasType({ENUMS::TypeName::Fire, ENUMS::TypeName::Ice})) 
   {
      at_mods.push_back(2048);
      desc.defender_ability = defender.GetAbility();
   }

   if ((attacker.HasAbility({"Guts"}) && 
        attacker.HasStatus() && 
        move.GetMoveCategory() == ENUMS::MoveCategory::Physical) ||
       (attacker.CurHP() <= attacker.MaxHP() / 3 &&
        ((attacker.HasAbility({"Overgrow"}) && move.HasType({ENUMS::TypeName::Grass})) ||
         (attacker.HasAbility({"Blaze"}) && move.HasType({ENUMS::TypeName::Fire})) ||
         (attacker.HasAbility({"Torrent"}) && move.HasType({ENUMS::TypeName::Water})) ||
         (attacker.HasAbility({"Swarm"}) && move.HasType({ENUMS::TypeName::Bug})))) ||
       (move.GetMoveCategory() == ENUMS::MoveCategory::Special && 
        attacker.GetAbilityOn() && 
        attacker.HasAbility({"Plus", "Minus"}))
   ) 
   {
      at_mods.push_back(6144);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (attacker.HasAbility({"Flash Fire"}) && 
            attacker.GetAbilityOn() && 
            move.HasType({ENUMS::TypeName::Fire})) 
   {
      at_mods.push_back(6144);
      desc.attacker_ability = "Flash Fire";
   } 
   else if 
   (
      (attacker.HasAbility({"Solar Power"}) &&
       field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) &&
       move.GetMoveCategory() == ENUMS::MoveCategory::Special) ||
      (attacker.Named({"Cherrim"}) &&
       attacker.HasAbility({"Flower Gift"}) &&
       field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) &&
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical)
   ) 
   {
      at_mods.push_back(6144);
      desc.attacker_ability = attacker.GetAbility();
      desc.weather = field.weather;
   } 
   else if 
   (
      field.attacker_side.is_flower_gift &&
      field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) &&
      move.GetMoveCategory() == ENUMS::MoveCategory::Physical
   ) 
   {
      at_mods.push_back(6144);
      desc.weather = field.weather;
      desc.is_flower_gift_attacker = true;
   } 
   else if 
   (
      (attacker.HasAbility({"Defeatist"}) && 
       attacker.CurHP() <= attacker.MaxHP() / 2) ||
      (attacker.HasAbility({"Slow Start"}) && 
       attacker.GetAbilityOn() && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical)
   ) 
   {
      at_mods.push_back(2048);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (attacker.HasAbility({"Huge Power", "Pure Power"}) && 
            move.GetMoveCategory() == ENUMS::MoveCategory::Physical) 
   {
      at_mods.push_back(8192);
      desc.attacker_ability = attacker.GetAbility();
   }

   if ((attacker.HasItem({"Thick Club"}) &&
        attacker.Named({"Cubone", "Marowak", "Marowak-Alola"}) &&
        move.GetMoveCategory() == ENUMS::MoveCategory::Physical) ||
       (attacker.HasItem({"Deep Sea Tooth"}) &&
        attacker.Named({"Clamperl"}) &&
        move.GetMoveCategory() == ENUMS::MoveCategory::Special) ||
       (attacker.HasItem({"Light Ball"}) && attacker.GetName().starts_with("Pikachu") && !move.GetIsZ())
   ) 
   {
      at_mods.push_back(8192);
      desc.attacker_item = attacker.GetItem();
   } 
   else if 
   (
      (attacker.HasItem({"Soul Dew"}) &&
         attacker.Named({"Latios", "Latias", "Latios-Mega", "Latias-Mega"}) &&
         move.GetMoveCategory() == ENUMS::MoveCategory::Special) ||
      (attacker.HasItem({"Choice Band"}) && move.GetMoveCategory() == ENUMS::MoveCategory::Physical) ||
      (attacker.HasItem({"Choice Specs"}) && move.GetMoveCategory() == ENUMS::MoveCategory::Special)
   ) 
   {
      at_mods.push_back(6144);
      desc.attacker_item = attacker.GetItem();
   }

   return at_mods;
}

int CalculateAttackBWXY
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
   int attack = 0;
   const auto& attack_source = move.Named({"Foul Play"}) ? defender : attacker;
   ENUMS::StatID attack_stat = move.GetMoveCategory() == ENUMS::MoveCategory::Special 
      ? ENUMS::StatID::spa 
      : ENUMS::StatID::atk;
   desc.attack_evs =
      move.Named({"Foul Play"})
         ? CalcUtil::GetStatDescriptionText(gen, defender, attack_stat, defender.GetNature())
         : CalcUtil::GetStatDescriptionText(gen, attacker, attack_stat, attacker.GetNature());

   if (attack_source.GetBoosts().at(attack_stat) == 0 ||
       (is_critical && attack_source.GetBoosts().at(attack_stat) < 0)) 
   {
      attack = attack_source.GetRawStats().at(attack_stat);
   } 
   else if (defender.HasAbility({"Unaware"})) 
   {
      attack = attack_source.GetRawStats().at(attack_stat);
      desc.defender_ability = defender.GetAbility();
   } 
   else 
   {
      attack = CalcUtil::GetModifiedStat(attack_source.GetRawStats().at(attack_stat), 
                                         attack_source.GetBoosts().at(attack_stat));
      desc.attack_boost = attack_source.GetBoosts().at(attack_stat);
   }

   // unlike all other attack modifiers, Hustle gets applied directly
   if (attacker.HasAbility({"Hustle"}) && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical) 
   {
      attack = CalcUtil::PokeRound((attack * 3) / 2);
      desc.attacker_ability = attacker.GetAbility();
   }

   std::vector<int> at_mods = CalculateAtModsBWXY(attacker, defender, move, field, desc);
   attack = CalcUtil::OF16(std::max(1, CalcUtil::PokeRound
      ((
         attack * CalcUtil::ChainMods(at_mods, 410, 131072)) / 4096
      )));
   
   return attack;
}

std::vector<int> CalculateDfModsBWXY
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& defender,
   const State::Field& field,
   Description::RawDescription& desc,
   bool hits_physical
) 
{
   std::vector<int> df_mods = {};
   if (defender.HasAbility({"Marvel Scale"}) && defender.HasStatus() && hits_physical) 
   {
      df_mods.push_back(6144);
      desc.defender_ability = defender.GetAbility();
   } 
   else if 
   (
      defender.Named({"Cherrim"}) &&
      defender.HasAbility({"Flower Gift"}) &&
      field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) &&
      !hits_physical
   ) 
   {
      df_mods.push_back(6144);
      desc.defender_ability = defender.GetAbility();
      desc.weather = field.weather;
   } 
   else if 
   (
      field.defender_side.is_flower_gift &&
      field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) &&
      !hits_physical
   ) 
   {
      df_mods.push_back(6144);
      desc.weather = field.weather;
      desc.is_flower_gift_defender = true;
   }

   if (field.HasTerrain({ENUMS::Terrain::Grassy_t}) && 
       defender.HasAbility({"Grass Pelt"}) &&
       hits_physical) 
   {
      df_mods.push_back(6144);
      desc.defender_ability = defender.GetAbility();
   }

   if ((!hits_physical && defender.HasItem({"Soul Dew"}) &&
        defender.Named({"Latios", "Latias", "Latios-Mega", "Latias-Mega"})) ||
       (defender.HasItem({"Eviolite"}) && 
         Data::Species::Instance().GetSpeciesByGen(gen, defender.GetName()).nfe) ||
       (!hits_physical && defender.HasItem({"Assault Vest"}))) 
   {
      df_mods.push_back(6144);
      desc.defender_item = defender.GetItem();
   }

   if ((defender.HasItem({"Metal Powder"}) && defender.Named({"Ditto"}) && hits_physical) ||
       (defender.HasItem({"Deep Sea Scale"}) && defender.Named({"Clamperl"}) && !hits_physical)) 
   {
      df_mods.push_back(8192);
      desc.defender_item = defender.GetItem();
   }

   if (defender.HasAbility({"Fur Coat"}) && hits_physical) 
   {
      df_mods.push_back(8192);
      desc.defender_ability = defender.GetAbility();
   }

   return df_mods;
}

int CalculateDefenseBWXY
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
   int defense = 0;
   ENUMS::StatID defender_stat = move.GetOverrideDefensiveStat() || 
                                 move.GetMoveCategory() == ENUMS::MoveCategory::Physical 
                                    ? ENUMS::StatID::def 
                                    : ENUMS::StatID::spd;
   bool hits_physical = defender_stat == ENUMS::StatID::def;
   desc.defense_evs = CalcUtil::GetStatDescriptionText(gen, defender, defender_stat, defender.GetNature());
   if (defender.GetBoosts().at(defender_stat) == 0 ||
       (is_critical && defender.GetBoosts().at(defender_stat) > 0) ||
       move.GetIgnoreDefense()) 
   {
      defense = defender.GetRawStats().at(defender_stat);
   } 
   else if (attacker.HasAbility({"Unaware"})) 
   {
      defense = defender.GetRawStats().at(defender_stat);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else 
   {
      defense = CalcUtil::GetModifiedStat(defender.GetRawStats().at(defender_stat), 
                                          defender.GetBoosts().at(defender_stat));
      desc.defense_boost = defender.GetBoosts().at(defender_stat);
   }

   // unlike all other defense modifiers, Sandstorm SpD boost gets applied directly
   if (field.HasWeather({ENUMS::Weather::Sand}) && 
       defender.HasType({ENUMS::TypeName::Rock}) && 
       !hits_physical) 
   {
      defense = CalcUtil::PokeRound((defense * 3) / 2);
      desc.weather = field.weather;
   }

   std::vector<int> df_mods = CalculateDfModsBWXY
   (
      gen,
      defender,
      field,
      desc,
      hits_physical
   );
   defense = CalcUtil::OF16(std::max(1, CalcUtil::PokeRound
      ((
         defense * CalcUtil::ChainMods(df_mods, 410, 131072)) / 4096
      )));

   return defense;
}

int CalculateBaseDamageBWXY
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const int base_power,
   const int attack,
   const int defense,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical
) 
{
   int base_damage = CalcUtil::GetBaseDamage(attacker.GetLevel(), base_power, attack, defense);

   bool is_spread = field.game_type != ENUMS::GameType::Singles &&
      (move.GetTarget() == ENUMS::MoveTarget::all_adjacent ||
       move.GetTarget() == ENUMS::MoveTarget::all_adjacent_foes);
   
   if (is_spread) 
   {
      base_damage = CalcUtil::PokeRound(CalcUtil::OF32(base_damage * 3072) / 4096);
   }

   if (attacker.HasAbility({"Parental Bond (Child)"})) 
   {
      base_damage = CalcUtil::PokeRound(CalcUtil::OF32(base_damage * 2048) / 4096);
   }

   if ((field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) && 
        move.HasType({ENUMS::TypeName::Fire})) ||
       (field.HasWeather({ENUMS::Weather::Rain, ENUMS::Weather::HeavyRain}) && 
        move.HasType({ENUMS::TypeName::Water}))) 
   {
      base_damage = CalcUtil::PokeRound(CalcUtil::OF32(base_damage * 6144) / 4096);
      desc.weather = field.weather;
   } 
   else if 
   (
      (field.HasWeather({ENUMS::Weather::Sun}) && move.HasType({ENUMS::TypeName::Water})) ||
      (field.HasWeather({ENUMS::Weather::Rain}) && move.HasType({ENUMS::TypeName::Fire}))
   ) {
      base_damage = CalcUtil::PokeRound(CalcUtil::OF32(base_damage * 2048) / 4096);
      desc.weather = field.weather;
   }

   if (is_critical) 
   {
      base_damage = std::floor(CalcUtil::OF32(
         base_damage * (static_cast<int>(gen) > 5 ? 1.5 : 2)));
      desc.is_critical = is_critical;
   }

   return base_damage;
}

std::vector<int> CalculateFinalModsBWXY
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   const float type_effectiveness,
   const bool is_critical,
   const int hit_count
) 
{
   std::vector<int> final_mods = {};

   if (field.defender_side.is_reflect && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical && 
       !is_critical) 
   {
      final_mods.push_back(field.game_type != ENUMS::GameType::Singles 
         ? (static_cast<int>(gen) > 5 
            ? 2732 
            : 2703) 
         : 2048);
      desc.is_reflect = true;
   } 
   else if (field.defender_side.is_light_screen && 
            move.GetMoveCategory() == ENUMS::MoveCategory::Special && 
            !is_critical) 
   {
      final_mods.push_back(field.game_type != ENUMS::GameType::Singles 
         ? (static_cast<int>(gen) > 5 
            ? 2732 
            : 2703) 
         : 2048);
      desc.is_light_screen = true;
   }

   if (defender.HasAbility({"Multiscale"}) && defender.CurHP() == defender.MaxHP() &&
         hit_count == 0 &&
         !field.defender_side.is_sr && (!field.defender_side.spikes || 
                                        defender.HasType({ENUMS::TypeName::Flying})) &&
         !attacker.HasAbility({"Parental Bond (Child)"})) 
   {
      final_mods.push_back(2048);
      desc.defender_ability = defender.GetAbility();
   }

   if (attacker.HasAbility({"Tinted Lens"}) && 
       (type_effectiveness < 1.0)) 
   {
      final_mods.push_back(8192);
      desc.attacker_ability = attacker.GetAbility();
   }

   if (field.defender_side.is_friend_guard) 
   {
      final_mods.push_back(3072);
      desc.is_friend_guard = true;
   }

   if (attacker.HasAbility({"Sniper"}) && is_critical) 
   {
      final_mods.push_back(6144);
      desc.attacker_ability = attacker.GetAbility();
   }

   if (defender.HasAbility({"Solid Rock", "Filter"}) && 
       type_effectiveness > 1.0) 
   {
      final_mods.push_back(3072);
      desc.defender_ability = defender.GetAbility();
   }

   if (attacker.HasItem({"Metronome"}) && move.GetTimesUsedWithMetronome() >= 1) 
   {
      int times_used_with_metronome = std::floor(move.GetTimesUsedWithMetronome());
      if (times_used_with_metronome <= 4) 
      {
         final_mods.push_back(4096 + times_used_with_metronome * 819);
      } 
      else 
      {
         final_mods.push_back(8192);
      }
      desc.attacker_item = attacker.GetItem();
   }

   if (attacker.HasItem({"Expert Belt"}) && type_effectiveness > 1.0 && !move.GetIsZ()) 
   {
      final_mods.push_back(4915);
      desc.attacker_item = attacker.GetItem();
   } 
   else if (attacker.HasItem({"Life Orb"})) 
   {
      final_mods.push_back(5324);
      desc.attacker_item = attacker.GetItem();
   }

   std::optional<ENUMS::TypeName> resist = defender.GetItem() 
      ? Data::Items::Instance().GetBerryResistType(*defender.GetItem())
      : std::nullopt;
   if (resist && move.HasType({*resist}) &&
         (type_effectiveness > 1.0 || 
          move.HasType({ENUMS::TypeName::Normal})) &&
         hit_count == 0 &&
         !attacker.HasAbility({"Unnerve"})) 
   {
      final_mods.push_back(2048);
      desc.defender_item = defender.GetItem();
   }

   return final_mods;
}

Result::Result CalculateBWXY
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
   CalcUtil::CheckItem(attacker, field.is_magic_room ? *field.is_magic_room : false);
   CalcUtil::CheckItem(defender, field.is_magic_room ? *field.is_magic_room : false);
   CalcUtil::CheckWonderRoom(attacker, field.is_wonder_room ? *field.is_wonder_room : false);
   CalcUtil::CheckWonderRoom(defender, field.is_wonder_room ? *field.is_wonder_room : false);
   CalcUtil::CheckSeedBoost(attacker, field);
   CalcUtil::CheckSeedBoost(defender, field);

   CalcUtil::ComputeFinalStats
   (
      gen, 
      attacker, 
      defender, 
      field, 
      std::vector<ENUMS::StatID>
      {  
         ENUMS::StatID::def, 
         ENUMS::StatID::spd, 
         ENUMS::StatID::spe
      }
   );

   CalcUtil::CheckIntimidate(gen, attacker, defender);
   CalcUtil::CheckIntimidate(gen, defender, attacker);
   CalcUtil::CheckDownload(attacker, 
                           defender, 
                           field.is_wonder_room ? *field.is_wonder_room : false);
   CalcUtil::CheckDownload(defender,
                           attacker, 
                           field.is_wonder_room ? *field.is_wonder_room : false);

   CalcUtil::ComputeFinalStats
   (
      gen, 
      attacker, 
      defender, 
      field, 
      std::vector<ENUMS::StatID>
      {  
         ENUMS::StatID::atk, 
         ENUMS::StatID::spa
      }
   );

   CalcUtil::CheckInfiltrator(attacker, field.defender_side);
   CalcUtil::CheckInfiltrator(defender, field.attacker_side);

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

   if (field.defender_side.is_protected && !move.GetBreaksProtect()) 
   {
      desc.is_protected = true;
      return result;
   }

   if (attacker.HasAbility({"Mold Breaker", "Teravolt", "Turboblaze"})) 
   {
      defender.SetAbility("");
      desc.attacker_ability = attacker.GetAbility();
   }

   bool is_critical =
      move.GetIsCrit() && 
      !defender.HasAbility({"Battle Armor", "Shell Armor"}) && 
      move.GetTimesUsed() == 1;

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
   else if (move.Named({"Techno Blast"}) && attacker.GetItem() && 
            attacker.GetItem().value().find("Drive") != std::string::npos) 
   {
      move.SetType(*Data::Items::Instance().GetTechnoBlast(attacker.GetItem().value()));
   } 
   else if (move.Named({"Natural Gift"}) && attacker.GetItem() &&
            attacker.GetItem().value().ends_with("Berry"))
   {
      Data::Items::NaturalGift gift 
         = Data::Items::Instance().GetNaturalGift(gen, attacker.GetItem().value());
      move.SetType(gift.t);
      move.SetBP(gift.p);
      desc.attacker_item = attacker.GetItem().value();
      desc.move_bp = move.GetBP();
      desc.move_type = move.GetType();
   }
   else if (move.Named({"Nature Power"})) 
   {
      if (gen == ENUMS::GenerationNumber::__5) 
      {
         move.SetType(ENUMS::TypeName::Ground);
      } 
      else 
      {
         move.SetType
         (
            field.HasTerrain({ENUMS::Terrain::Electric_t}) ? ENUMS::TypeName::Electric
            : field.HasTerrain({ENUMS::Terrain::Grassy_t}) ? ENUMS::TypeName::Grass
            : field.HasTerrain({ENUMS::Terrain::Misty_t}) ? ENUMS::TypeName::Fairy
            : ENUMS::TypeName::Normal
         );
      }
   }

   bool has_ate_ability_type_change = false;
   bool is_aerilate = false;
   bool is_pixilate = false;
   bool is_refrigerate = false;
   bool is_normalize = false;
   bool no_type_change =
      move.Named
      ({
         "Judgment", 
         "Nature Power", 
         "Techo Blast", 
         "Natural Gift", 
         "Weather Ball",
         "Struggle"
      });

   if (!move.GetIsZ() && !no_type_change) {
      bool normal = move.HasType({ENUMS::TypeName::Normal});
      if ((is_aerilate = attacker.HasAbility({"Aerilate"}) && normal)) 
      {
         move.SetType({ENUMS::TypeName::Flying});
      } 
      else if ((is_pixilate = attacker.HasAbility({"Pixilate"}) && normal)) 
      {
         move.SetType({ENUMS::TypeName::Fairy});
      } 
      else if ((is_refrigerate = attacker.HasAbility({"Refrigerate"}) && normal)) 
      {
         move.SetType({ENUMS::TypeName::Ice});
      } 
      else if ((is_normalize = attacker.HasAbility({"Normalize"}))) 
      {
         move.SetType({ENUMS::TypeName::Normal});
      }
      if (is_pixilate || is_refrigerate || is_aerilate || is_normalize) 
      {
         desc.attacker_ability = attacker.GetAbility();
      }
      if (is_pixilate || is_refrigerate || is_aerilate) 
      {
         has_ate_ability_type_change = true;
      }
   }

   if (attacker.HasAbility({"Gale Wings"}) && move.HasType({ENUMS::TypeName::Flying})) 
   {
      move.SetPriority(1);
      desc.attacker_ability = attacker.GetAbility();
   }

   bool is_ghost_revealed = attacker.HasAbility({"Scrappy"}) || field.defender_side.is_foresight;

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

   auto effectiveness 
      = Data::Types::Instance().GetTypeEffectivenessByTypeAndGen(gen, move.GetType());
   if (type_eff == 0 && move.Named({"Thousand Arrows"})) 
   {
      type_eff = 1;
   } 
   else if (type_eff == 0 && 
            move.HasType({ENUMS::TypeName::Ground}) &&
            defender.HasItem({"Iron Ball"}) && 
            !defender.HasAbility({"Klutz"})) 
   {
      type_eff = 1;
   } 
   else if (type_eff == 0 && defender.HasItem({"Ring Target"})) 
   {
      if (effectiveness[defender.GetTypes().at(0)] == ENUMS::TypeEffectiveness::_0) 
      {
         type_eff = type_eff2;
      } 
      else if (defender.GetTypes().size() > 0 && 
               effectiveness[defender.GetTypes().at(1)] == ENUMS::TypeEffectiveness::_0) 
      {
         type_eff = type_eff1;
      }
   }

   if (type_eff == 0) 
   {
      return result;
   }

   if ((move.Named({"Sky Drop"}) &&
        (defender.HasType({ENUMS::TypeName::Flying}) || 
         defender.GetWeight() >= 200 || 
         field.is_gravity)) ||
       (move.Named({"Synchronoise"}) && 
        !defender.HasType({attacker.GetTypes().at(0)}) &&
        (!attacker.GetTypes().size() > 0 || 
         !defender.HasType({attacker.GetTypes().at(1)}))) ||
       (move.Named({"Dream Eater"}) && !defender.HasStatus({ENUMS::StatusName::slp}))
   ) 
   {
      return result;
   }

   if 
   (
      (field.HasWeather({ENUMS::Weather::HarshSunshine}) && 
       move.HasType({ENUMS::TypeName::Water})) ||
      (field.HasWeather({ENUMS::Weather::HeavyRain}) && 
       move.HasType({ENUMS::TypeName::Fire}))
   ) 
   {
      desc.weather = field.weather;
      return result;
   }

   if (field.HasWeather({ENUMS::Weather::StrongWinds}) && 
       defender.HasType({ENUMS::TypeName::Flying}) &&
       effectiveness.at(ENUMS::TypeName::Flying) == ENUMS::TypeEffectiveness::_2) 
   {
      type_eff /= 2;
      desc.weather = field.weather;
   }

   if ((defender.HasAbility({"Wonder Guard"}) && type_eff <= 1) ||
       (move.HasType({ENUMS::TypeName::Grass}) && defender.HasAbility({"Sap Sipper"})) ||
         (move.HasType({ENUMS::TypeName::Fire}) && defender.HasAbility({"Flash Fire"})) ||
         (move.HasType({ENUMS::TypeName::Water}) && 
          defender.HasAbility({"Dry Skin", "Storm Drain", "Water Absorb"})) ||
         (move.HasType({ENUMS::TypeName::Electric}) &&
          defender.HasAbility({"Lightning Rod", "Motor Drive", "Volt Absorb"})) ||
         (move.HasType({ENUMS::TypeName::Ground}) &&
          !field.is_gravity && !move.Named({"Thousand Arrows"}) &&
          !defender.HasItem({"Iron Ball"}) && defender.HasAbility({"Levitate"})) ||
         (move.GetMoveFlags().bullet && defender.HasAbility({"Bulletproof"})) ||
         (move.GetMoveFlags().sound && defender.HasAbility({"Soundproof"}))
   ) 
   {
      desc.defender_ability = defender.GetAbility();
      return result;
   }

   if (move.HasType({ENUMS::TypeName::Ground}) && 
       !move.Named({"Thousand Arrows"}) &&
       !field.is_gravity && defender.HasItem({"Air Balloon"})) 
   {
      desc.defender_item = *defender.GetItem();
      return result;
   }

   if (move.GetPriority() > 0 && 
       field.HasTerrain({ENUMS::Terrain::Psychic_t}) && 
       CalcUtil::IsGrounded(defender, field)) 
   {
      desc.terrain = field.terrain;
      return result;
   }

   desc.hp_evs = CalcUtil::GetStatDescriptionText(gen, defender, ENUMS::StatID::hp);

   int fixed_damage = CalcUtil::HandleFixedDamageMoves(attacker, move);
   if (fixed_damage) 
   {
      if (attacker.HasAbility({"Parental Bond"})) 
      {
         result.SetDamage(std::vector<int>{fixed_damage, fixed_damage});
         desc.attacker_ability = attacker.GetAbility();
      } 
      else 
      {
         result.SetDamage(fixed_damage);
      }
      return result;
   }

   if (move.Named({"Final Gambit"})) 
   {
      result.SetDamage(attacker.CurHP());
      return result;
   }

   if (move.GetHits() && *move.GetHits() > 1) 
   {
      desc.hits = *move.GetHits();
   }

   // #endregion
   // #region Base Power

   int base_power = CalculateBasePowerBWXY
   (
      gen,
      attacker,
      defender,
      move,
      field,
      has_ate_ability_type_change,
      desc
   );
   if (base_power == 0) 
   {
      return result;
   }

   // #endregion
   // #region (Special) Attack

   int attack = CalculateAttackBWXY(gen, attacker, defender, move, field, desc, is_critical);
   ENUMS::StatID attack_stat = move.GetMoveCategory() == ENUMS::MoveCategory::Special 
      ? ENUMS::StatID::spa 
      : ENUMS::StatID::atk;

   // #endregion
   // #region (Special) Defense

   int defense = CalculateDefenseBWXY(gen, attacker, defender, move, field, desc, is_critical);

   // #endregion
   // #region Damage

   int base_damage = CalculateBaseDamageBWXY
   (
      gen,
      attacker,
      base_power,
      attack,
      defense,
      move,
      field,
      desc,
      is_critical
   );

   // the random factor is applied between the crit mod and the stab mod, so don"t apply anything
   // below this until we're inside the loop
   int stab_mod = CalcUtil::GetStabMod(attacker, move, desc);

   bool apply_burn =
      attacker.HasStatus({ENUMS::StatusName::brn}) &&
      move.GetMoveCategory() == ENUMS::MoveCategory::Physical &&
      !attacker.HasAbility({"Guts"}) &&
      !(move.Named({"Facade"}) && gen == ENUMS::GenerationNumber::__6);
   desc.is_burned = apply_burn;

   std::vector<int> final_mods = CalculateFinalModsBWXY
   (
      gen,
      attacker,
      defender,
      move,
      field,
      desc,
      type_eff,
      is_critical
   );
   int final_mod = CalcUtil::ChainMods(final_mods, 41, 131072);

   bool is_spread = field.game_type != ENUMS::GameType::Singles &&
      (move.GetTarget() == ENUMS::MoveTarget::all_adjacent ||
       move.GetTarget() == ENUMS::MoveTarget::all_adjacent_foes);

   bool child_damage_q = false;
   Description::Damage child_damage;
   if (attacker.HasAbility({"Parental Bond"}) && move.GetHits() == 1 && !is_spread) 
   {
      Pokemon::Pokemon child = attacker;
      child.SetAbility("Parental Bond (Child)");
      CalcUtil::CheckMultihitBoost(gen, child, defender, move, field, desc);
      child_damage = CalculateBWXY(gen, child, defender, move, field).GetDamage();
      desc.attacker_ability = attacker.GetAbility();
      child_damage_q = true;
   }

   std::vector<int> damage_out{};
   for (int i = 0; i < 16; i++) 
   {
      damage_out.push_back(CalcUtil::GetFinalDamage
      (
         base_damage, 
         i, 
         type_eff, 
         apply_burn, 
         stab_mod, 
         final_mod
      ));
   }

   desc.attack_boost = move.Named({"Foul Play"}) 
      ? defender.GetBoosts().at(attack_stat) 
      : attacker.GetBoosts().at(attack_stat);

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
         num_attacks = move.GetHits() ? *move.GetHits() : num_attacks;
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
         int new_atk = CalculateAttackBWXY(gen, attacker, defender, move, field, desc, is_critical);
         int new_def = CalculateDefenseBWXY(gen, attacker, defender, move, field, desc, is_critical);
         // Check if lost -ate ability. Typing stays the same, only boost is lost
         // Cannot be regained during multihit move and no Normal moves with stat drawbacks
         has_ate_ability_type_change = has_ate_ability_type_change &&
            attacker.HasAbility({"Aerilate", "Galvanize", "Pixilate", "Refrigerate"});

         if (move.GetDropsStats() && move.GetTimesUsed() > 1)  
         {
            // Adaptability does not change between hits of a multihit, only between turns
            stab_mod = CalcUtil::GetStabMod(attacker, move, desc);
         }

         int new_base_power = CalculateBasePowerBWXY
         (
            gen,
            attacker,
            defender,
            move,
            field,
            has_ate_ability_type_change,
            desc
         );
         int new_base_damage 
            = CalcUtil::GetBaseDamage(attacker.GetLevel(), new_base_power, new_atk, new_def);
         std::vector<int> new_final_mods = CalculateFinalModsBWXY
         (
            gen,
            attacker,
            defender,
            move,
            field,
            desc,
            type_eff,
            is_critical,
            times
         );
         int new_final_mod = CalcUtil::ChainMods(new_final_mods, 41, 131072);

         int damage_multiplier = 0;
         for (auto& affected_amount : damage_out)
         {
            int new_final_damage = CalcUtil::GetFinalDamage
            (
               new_base_damage,
               damage_multiplier,
               type_eff,
               apply_burn,
               stab_mod,
               new_final_mod
            );

            damage_multiplier++;

            affected_amount += new_final_damage;
         }
      }
      desc.defense_boost = orig_def_boost;
      desc.attack_boost = orig_atk_boost;
   }

   std::vector<int> child_damage_out{};
   if (child_damage_q)
   {
      std::visit([&child_damage_out](const auto& value)
      {
         using T = std::decay_t<decltype(value)>;

         if constexpr (std::is_same_v<T, int>)
         {
            std::cerr << "Probably should not have an 'int'. May need to check this.\n";
         }
         else if constexpr (std::is_same_v<T, std::vector<int>>)
         {
            child_damage_out = value;
         }
         else if constexpr (std::is_same_v<T, std::pair<int, int>>)
         {
            std::cerr << "Probably should not have a pair of 'int's. May need to check this.\n";
         }
         else if constexpr (std::is_same_v<T, std::pair<std::vector<int>, std::vector<int>>>)
         {
            std::cerr << "Probably should not have a pair of vectors of 'int's. "
                     << "May need to check this.\n";
         }
      }, child_damage);
   }

   //childDamage ? [damage, childDamage] : damage;
   child_damage_out.empty() ? result.SetDamage(damage_out) 
                            : result.SetDamage(std::make_pair(damage_out, child_damage_out));

   // #endregion

   return result;
}

}
}
}