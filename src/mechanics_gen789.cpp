#include "./../include/mechanics/gen789.hpp"

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
namespace GEN789
{

std::vector<int> CalculateBPModsSMSSSV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   int& base_power,
   bool has_ate_ability_type_change,
   const std::string& turn_order
) 
{
   std::vector<int> bp_mods{};

   // Move effects
   bool resisted_knock_off_damage =
      (!defender.GetItem() || CalcUtil::IsQPActive(defender, field)) ||
      (defender.Named({"Dialga-Origin"}) && defender.HasItem({"Adamant Crystal"})) ||
      (defender.Named({"Palkia-Origin"}) && defender.HasItem({"Lustrous Globe"})) ||
      // Griseous Core for gen 9, Griseous Orb otherwise
      (defender.GetName().find("Giratina-Origin") != std::string::npos && 
       defender.GetItem().value().find("Griseous") != std::string::npos) ||
      (defender.GetName().find("Arceus")  != std::string::npos && 
       defender.GetItem().value().find("Plate") != std::string::npos) ||
      (defender.GetName().find("Genesect") != std::string::npos && 
       defender.GetItem().value().find("Drive") != std::string::npos) ||
      (defender.Named({"Groudon", "Groudon-Primal"}) && defender.HasItem({"Red Orb"})) ||
      (defender.Named({"Kyogre", "Kyogre-Primal"}) && defender.HasItem({"Blue Orb"})) ||
      (defender.GetName().find("Silvally") != std::string::npos && 
       defender.GetItem().value().find("Memory") != std::string::npos) ||
      defender.GetItem().value().find(" Z") != std::string::npos ||
      (defender.Named({"Zacian"}) && defender.HasItem({"Rusted Sword"})) ||
      (defender.Named({"Zamazenta"}) && defender.HasItem({"Rusted Shield"})) ||
      (defender.GetName().find("Ogerpon-Cornerstone") != std::string::npos && 
       defender.HasItem({"Cornerstone Mask"})) ||
      (defender.GetName().find("Ogerpon-Hearthflame") != std::string::npos && 
       defender.HasItem({"Hearthflame Mask"})) ||
      (defender.GetName().find("Ogerpon-Wellspring") != std::string::npos && 
       defender.HasItem({"Wellspring Mask"})) ||
      (defender.Named({"Venomicon-Epilogue"}) && 
       defender.HasItem({"Vile Vial"}));

   // The last case only applies when the Pokemon Has the Mega Stone that matches its species
   // (or when it's already a Mega-Evolution)
   if (!resisted_knock_off_damage && defender.GetItem()) 
   {
      resisted_knock_off_damage = defender.GetName().find
      (
         Data::Items::Instance().GetMegaEvolves(static_cast<int>(gen), *defender.GetItem())
      ) != std::string::npos;
   }

   if ((move.Named({"Facade"}) && 
        attacker.HasStatus({ENUMS::StatusName::brn, 
                            ENUMS::StatusName::par, 
                            ENUMS::StatusName::psn, 
                            ENUMS::StatusName::tox})) ||
       (move.Named({"Brine"}) && defender.CurHP() <= defender.MaxHP() / 2) ||
       (move.Named({"Venoshock"}) && 
        defender.HasStatus({ENUMS::StatusName::psn, ENUMS::StatusName::tox})) ||
       (move.Named({"Lash Out"}) && (CalcUtil::CountBoosts(gen, attacker.GetBoosts()) < 0))
   ) 
   {
      bp_mods.push_back(8192);
      desc.move_bp = base_power * 2;
   } 
   else if 
   (
      move.Named({"Expanding Force"}) && 
      CalcUtil::IsGrounded(attacker, field) && 
      field.HasTerrain({ENUMS::Terrain::Psychic_t})
   ) 
   {
      move.SetTarget(ENUMS::MoveTarget::all_adjacent_foes);
      bp_mods.push_back(6144);
      desc.move_bp = base_power * 1.5;
   } 
   else if 
   (
      move.Named({"Tera Starstorm"}) && attacker.GetName() == "Terapagos-Stellar"
   ) 
   {
      move.SetTarget(ENUMS::MoveTarget::all_adjacent_foes);
      move.SetType(ENUMS::TypeName::Stellar);
   } 
   else if ((move.Named({"Knock Off"}) && !resisted_knock_off_damage) ||
            (move.Named({"Misty Explosion"}) && 
             CalcUtil::IsGrounded(attacker, field) && 
             field.HasTerrain({ENUMS::Terrain::Misty_t})) ||
            (move.Named({"Grav Apple"}) && field.is_gravity ? *field.is_gravity : false)
   ) 
   {
      bp_mods.push_back(6144);
      desc.move_bp = base_power * 1.5;
   } 
   else if (move.Named({"Solar Beam", "Solar Blade"}) &&
            field.HasWeather({ENUMS::Weather::Rain, 
                              ENUMS::Weather::HeavyRain, 
                              ENUMS::Weather::Sand, 
                              ENUMS::Weather::Hail, 
                              ENUMS::Weather::Snow})) 
   {
      bp_mods.push_back(2048);
      desc.move_bp = base_power / 2;
      desc.weather = field.weather;
   } 
   else if (move.Named({"Collision Course", "Electro Drift"})) 
   {
      bool is_ghost_revealed = attacker.HasAbility({"Scrappy", "Mind\'s Eye"}) || 
                            field.defender_side.is_foresight;
      bool is_ring_target = defender.HasItem({"Ring Target"}) && !defender.HasAbility({"Klutz"});
      std::vector<ENUMS::TypeName> types 
         = (defender.GetTeraType() && *defender.GetTeraType() != ENUMS::TypeName::Stellar)
         ? std::vector<ENUMS::TypeName>{*defender.GetTeraType()} : defender.GetTypes();
      float type_eff1 = CalcUtil::GetMoveEffectiveness
      (
         gen, 
         move, 
         defender.GetTypes().at(0),
         is_ghost_revealed,
         field.is_gravity ? *field.is_gravity : false,
         is_ring_target
      );
      float type_eff2 = defender.GetTypes().size() > 1 ? 
      CalcUtil::GetMoveEffectiveness
      (
         gen, 
         move, 
         defender.GetTypes().at(1),
         is_ghost_revealed,
         field.is_gravity ? *field.is_gravity : false,
         is_ring_target
      ) : 1;
      if (type_eff1 * type_eff2 >= 2) 
      {
         bp_mods.push_back(5461);
         desc.move_bp = base_power * (5461 / 4096);
      }
   }

   if (field.attacker_side.is_helping_hand) 
   {
      bp_mods.push_back(6144);
      desc.is_helping_hand = true;
   }

   // Field effects
   int terrain_multiplier = static_cast<int>(gen) > 7 ? 5325 : 6144;
   if (CalcUtil::IsGrounded(attacker, field)) 
   {
      if 
      (
         (field.HasTerrain({ENUMS::Terrain::Electric_t}) && 
          move.HasType({ENUMS::TypeName::Electric})) ||
         (field.HasTerrain({ENUMS::Terrain::Grassy_t}) && 
          move.HasType({ENUMS::TypeName::Grass})) ||
         (field.HasTerrain({ENUMS::Terrain::Psychic_t}) && 
          move.HasType({ENUMS::TypeName::Psychic}))
      ) 
      {
         bp_mods.push_back(terrain_multiplier);
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

   // Abilities

   // Use BasePower after moves with custom BP to determine if Technician should boost
   if ((attacker.HasAbility({"Technician"}) && base_power <= 60) ||
       (attacker.HasAbility({"Flare Boost"}) &&
        attacker.HasStatus({ENUMS::StatusName::brn}) && 
        move.GetMoveCategory() == ENUMS::MoveCategory::Special) ||
      (attacker.HasAbility({"Toxic Boost"}) &&
       attacker.HasStatus({ENUMS::StatusName::psn, ENUMS::StatusName::tox}) && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical) ||
      (attacker.HasAbility({"Mega Launcher"}) && move.GetMoveFlags().pulse) ||
      (attacker.HasAbility({"Strong Jaw"}) && move.GetMoveFlags().bite) ||
      (attacker.HasAbility({"Steely Spirit"}) && move.HasType({ENUMS::TypeName::Steel})) ||
      (attacker.HasAbility({"Sharpness"}) && move.GetMoveFlags().slicing)
   ) 
   {
      bp_mods.push_back(6144);
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

   // Sheer Force does not power up max moves or remove the effects (SadisticMystic)
   if 
   (
      (attacker.HasAbility({"Sheer Force"}) &&
       (move.GetSecondaries() || move.Named({"Jet Punch", "Order Up"})) && !move.GetIsMax()) ||
      (attacker.HasAbility({"Sand Force"}) &&
       field.HasWeather({ENUMS::Weather::Sand}) && 
       move.HasType({ENUMS::TypeName::Rock, ENUMS::TypeName::Ground, ENUMS::TypeName::Steel})) ||
      (attacker.HasAbility({"Analytic"}) &&
       (turn_order != "first" || field.defender_side.is_switching == ENUMS::Switching::out)) ||
      (attacker.HasAbility({"Tough Claws"}) && move.GetMoveFlags().contact) ||
      (attacker.HasAbility({"Punk Rock"}) && move.GetMoveFlags().sound)
   ) 
   {
      bp_mods.push_back(5325);
      desc.attacker_ability = attacker.GetAbility();
   }

   if (field.attacker_side.is_battery && move.GetMoveCategory() == ENUMS::MoveCategory::Special) 
   {
      bp_mods.push_back(5325);
      desc.is_battery = true;
   }

   if (field.attacker_side.is_power_spot) 
   {
      bp_mods.push_back(5325);
      desc.is_power_spot = true;
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

   // The -ate abilities already changed move typing earlier, so most CalcUtil::Checks are done and desc is set
   // However, Max Moves also don"t boost -ate Abilities
   if (!move.GetIsMax() && has_ate_ability_type_change) 
   {
      bp_mods.push_back(4915);
   }

   if ((attacker.HasAbility({"Reckless"}) && (move.GetRecoil() || move.GetHasCrashDamage())) ||
       (attacker.HasAbility({"Iron Fist"}) && move.GetMoveFlags().punch)
   ) 
   {
      bp_mods.push_back(4915);
      desc.attacker_ability = attacker.GetAbility();
   }

   if (attacker.HasItem({"Punching Glove"}) && move.GetMoveFlags().punch) 
   {
      bp_mods.push_back(4506);
   }

   if (static_cast<int>(gen) <= 8 && 
       defender.HasAbility({"Heatproof"}) && 
       move.HasType({ENUMS::TypeName::Fire})) 
   {
      bp_mods.push_back(2048);
      desc.defender_ability = defender.GetAbility();
   } 
   else if (defender.HasAbility({"Dry Skin"}) && move.HasType({ENUMS::TypeName::Fire})) 
   {
      bp_mods.push_back(5120);
      desc.defender_ability = defender.GetAbility();
   }

   if (attacker.HasAbility({"Supreme Overlord"}) && attacker.GetAlliesFainted()) 
   {
      std::vector<int> pow_mod{4096, 4506, 4915, 5325, 5734, 6144};
      bp_mods.push_back(pow_mod[std::min(5, *attacker.GetAlliesFainted())]);
      desc.attacker_ability = attacker.GetAbility();
      desc.allies_fainted = attacker.GetAlliesFainted();
   }

   // Items

   if (attacker.HasItem({Data::Types::Instance().TypeNameENUMToString(move.GetType()) + " Gem"})) 
   {
      bp_mods.push_back(5325);
      desc.attacker_item = attacker.GetItem();
   } 
   else if 
   (
      (((attacker.HasItem({"Adamant Crystal"}) && attacker.Named({"Dialga-Origin"})) ||
        (attacker.HasItem({"Adamant Orb"}) && attacker.Named({"Dialga"}))) &&
      move.HasType({ENUMS::TypeName::Steel, ENUMS::TypeName::Dragon})) ||
      (((attacker.HasItem({"Lustrous Orb"}) &&
         attacker.Named({"Palkia"})) ||
         (attacker.HasItem({"Lustrous Globe"}) && attacker.Named({"Palkia-Origin"}))) &&
      move.HasType({ENUMS::TypeName::Water, ENUMS::TypeName::Dragon})) ||
      (((attacker.HasItem({"Griseous Orb"}) || attacker.HasItem({"Griseous Core"})) &&
      (attacker.Named({"Giratina-Origin"}) || attacker.Named({"Giratina"}))) &&
      move.HasType({ENUMS::TypeName::Ghost, ENUMS::TypeName::Dragon})) ||
      (attacker.HasItem({"Vile Vial"}) &&
      attacker.Named({"Venomicon-Epilogue"}) &&
      move.HasType({ENUMS::TypeName::Poison, ENUMS::TypeName::Flying})) ||
      (attacker.HasItem({"Soul Dew"}) &&
      attacker.Named({"Latios", "Latias", "Latios-Mega", "Latias-Mega"}) &&
      move.HasType({ENUMS::TypeName::Psychic, ENUMS::TypeName::Dragon})) ||
      attacker.GetItem() && 
      move.HasType
      (
         {*Data::Items::Instance().GetItemBoostType(*attacker.GetItem())}
      ) ||
      (attacker.GetName().find("Ogerpon-Cornerstone") != std::string::npos && 
       attacker.HasItem({"Cornerstone Mask"})) ||
      (attacker.GetName().find("Ogerpon-Hearthflame") != std::string::npos && 
       attacker.HasItem({"Hearthflame Mask"})) ||
      (attacker.GetName().find("Ogerpon-Wellspring") != std::string::npos && 
       attacker.HasItem({"Wellspring Mask"}))
   ) 
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
   return bp_mods;
}


int CalculateBasePowerSMSSSV
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
   std::string turn_order = attacker.GetStats().at(ENUMS::StatID::spe) > 
                            defender.GetStats().at(ENUMS::StatID::spe) 
                            ? "first" 
                            : "last";

   int base_power = 0;

   if (move.GetName() == "Payback") 
   {
      base_power = move.GetBP() * (turn_order == "last" ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Bolt Beak" || move.GetName() == "Fishious Rend") 
   {
      base_power = move.GetBP() * (turn_order != "last" ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Pursuit") 
   {
      const bool switching = field.defender_side.is_switching == ENUMS::Switching::out;
      base_power = move.GetBP() * (switching ? 2 : 1);
      if (switching) desc.is_switching = "out";
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Electro Ball") 
   {
      if (defender.GetStats().at(ENUMS::StatID::spe) == 0) 
      {
         base_power = 40;
      } 
      else 
      {
         const int r = std::floor(attacker.GetStats().at(ENUMS::StatID::spe) / 
                                  defender.GetStats().at(ENUMS::StatID::spe));
         base_power = r >= 4 ? 150 :
                      r >= 3 ? 120 :
                      r >= 2 ? 80 :
                      r >= 1 ? 60 : 40;
      }
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Gyro Ball")
   {
      if (attacker.GetStats().at(ENUMS::StatID::spe) == 0) 
      {
         base_power = 1;
      } 
      else 
      {
         base_power = std::min
         (
            150,
            static_cast<int>
            (
               std::floor((25 * defender.GetStats().at(ENUMS::StatID::spe)) / 
                                attacker.GetStats().at(ENUMS::StatID::spe)) + 1
            )
         );
      }
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Punishment") 
   {
      base_power = std::min(200, 60 + 20 * CalcUtil::CountBoosts(gen, defender.GetBoosts()));
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Low Kick" || move.GetName() == "Grass Knot") 
   {
      const auto w = CalcUtil::GetWeight(defender, desc, false);
      base_power = w >= 200 ? 120 :
                   w >= 100 ? 100 :
                   w >= 50 ? 80 :
                   w >= 25 ? 60 :
                   w >= 10 ? 40 : 20;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Hex" || move.GetName() == "Infernal Parade") 
   {
      // Hex deals double damage to Pokemon with Comatose (ih8ih8sn0w)
      base_power = move.GetBP() * ((defender.HasStatus() || 
                                    defender.HasAbility({"Comatose"})) ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Barb Barrage") 
   {
      base_power = move.GetBP() * 
      (
         defender.HasStatus({ENUMS::StatusName::psn, ENUMS::StatusName::tox}) ? 2 : 1
      );
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Heavy Slam" || move.GetName() == "Heat Crash") 
   {
      const auto wr =
         CalcUtil::GetWeight(attacker, desc, true) /
         CalcUtil::GetWeight(defender, desc, false);

      base_power = wr >= 5 ? 120 :
                   wr >= 4 ? 100 :
                   wr >= 3 ? 80 :
                   wr >= 2 ? 60 : 40;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Stored Power" || move.GetName() == "Power Trip") 
   {
      base_power = 20 + 20 * CalcUtil::CountBoosts(gen, attacker.GetBoosts());
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Acrobatics") 
   {
      base_power = move.GetBP() *
         ((attacker.HasItem({"Flying Gem"}) ||
            (!attacker.GetItem() || CalcUtil::IsQPActive(attacker, field))) ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Assurance") 
   {
      base_power = move.GetBP() * (defender.HasAbility({"Parental Bond (Child)"}) ? 2 : 1);
      // NOTE: desc.attacker_ability = "Parental Bond" will already reflect this boost
   }
   else if (move.GetName() == "Wake-Up Slap") 
   {
      // Wake-Up Slap deals double damage to Pokemon with Comatose (ih8ih8sn0w)
      base_power = move.GetBP() *
         ((defender.HasStatus({ENUMS::StatusName::slp}) ||
            defender.HasAbility({"Comatose"})) ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Smelling Salts") 
   {
      base_power = move.GetBP() * (defender.HasStatus({ENUMS::StatusName::par}) ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Weather Ball") 
   {
      base_power = move.GetBP() *
         ((field.weather && !field.HasWeather({ENUMS::Weather::StrongWinds})) ? 2 : 1);

      if (field.HasWeather
            ({
               ENUMS::Weather::Sun,
               ENUMS::Weather::HarshSunshine,
               ENUMS::Weather::Rain,
               ENUMS::Weather::HeavyRain
            }) &&
         attacker.HasItem({"Utility Umbrella"})) 
      {
         base_power = move.GetBP();
      }

      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Terrain Pulse") 
   {
      base_power = move.GetBP() *
         ((CalcUtil::IsGrounded(attacker, field) && field.terrain) ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Rising Voltage") 
   {
      base_power = move.GetBP() *
         ((CalcUtil::IsGrounded(defender, field) &&
            field.HasTerrain({ENUMS::Terrain::Electric_t})) ? 2 : 1);
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Psyblade") 
   {
      base_power = move.GetBP() *
         (field.HasTerrain({ENUMS::Terrain::Electric_t}) ? 1.5 : 1);

      if (field.HasTerrain({ENUMS::Terrain::Electric_t})) 
      {
         desc.move_bp = base_power;
         desc.terrain = field.terrain;
      }
   }
   else if (move.GetName() == "Fling") 
   {
      base_power = Data::Items::Instance().GetFlingPower(attacker.GetItem());
      desc.move_bp = base_power;
      desc.attacker_item = attacker.GetItem();
   }
   else if (move.GetName() == "Dragon Energy" ||
            move.GetName() == "Eruption" ||
            move.GetName() == "Water Spout") 
   {
      base_power = std::max
      (
         1,
         static_cast<int>(std::floor((150 * attacker.CurHP()) / attacker.MaxHP()))
      );
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Flail" || move.GetName() == "Reversal") 
   {
      const int p = std::floor((48 * attacker.CurHP()) / attacker.MaxHP());

      base_power = p <= 1 ? 200 :
                   p <= 4 ? 150 :
                   p <= 9 ? 100 :
                   p <= 16 ? 80 :
                   p <= 32 ? 40 : 20;

      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Natural Gift") 
   {
      if (attacker.GetItem() && attacker.GetItem().value().ends_with("Berry"))
      {
         Data::Items::NaturalGift gift 
            = Data::Items::Instance().GetNaturalGift(gen, attacker.GetItem().value());
         base_power = gift.p;
         desc.attacker_item = attacker.GetItem();
         desc.move_bp = move.GetBP();
      } 
      else 
      {
         base_power = move.GetBP();
      }
   }
   else if (move.GetName() == "Nature Power") 
   {
      move.SetMoveCategory(ENUMS::MoveCategory::Special);
      move.SetSecondaries(true);

      if (attacker.HasAbility({"Prankster"}) &&
          defender.HasType({ENUMS::TypeName::Dark})) 
      {
         base_power = 0;
         desc.move_name = "Nature Power";
         desc.attacker_ability = "Prankster";
      } 
      else if (field.terrain)
      {
         switch (*field.terrain)
         {
            case ENUMS::TypeName::Electric:
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
            case ENUMS::TypeName::Psychic:
                  if (attacker.HasAbility({"Prankster"}) &&
                      CalcUtil::IsGrounded(defender, field)) 
                  {
                     base_power = 0;
                     desc.attacker_ability = "Prankster";
                  } 
                  else 
                  {
                     base_power = 90;
                     desc.move_name = ENUMS::TypeName::Psychic;
                  }
                  break;
            default:
                  base_power = 80;
                  desc.move_name = "Tri Attack";
                  break;
         }
      }
   }
   else if (move.GetName() == "Water Shuriken") 
   {
      base_power = attacker.Named({"Greninja-Ash"}) &&
                   attacker.HasAbility({"Battle Bond"}) ? 20 : 15;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Triple Axel") 
   {
      base_power = hit * 20;
      desc.move_bp = move.GetHits() == 2 ? 60 :
                     move.GetHits() == 3 ? 120 : 20;
   }
   else if (move.GetName() == "Triple Kick") 
   {
      base_power = hit * 10;
      desc.move_bp = move.GetHits() == 2 ? 30 :
                     move.GetHits() == 3 ? 60 : 10;
   }
   else if (move.GetName() == "Crush Grip" || move.GetName() == "Wring Out") 
   {
      base_power = 100 * std::floor((defender.CurHP() * 4096) / defender.MaxHP());
      base_power = std::floor(
         std::floor((120 * base_power + 2048 - 1) / 4096) / 100
      ) || 1;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Hard Press") 
   {
      base_power = 100 * std::floor((defender.CurHP() * 4096) / defender.MaxHP());
      base_power = std::floor(
         std::floor((100 * base_power + 2048 - 1) / 4096) / 100
      ) || 1;
      desc.move_bp = base_power;
   }
   else if (move.GetName() == "Tera Blast") 
   {
      base_power = attacker.GetTeraType() == ENUMS::TypeName::Stellar ? 100 : 80;
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
   if (move.Named
      ({
         "Breakneck Blitz", "Bloom Doom", "Inferno Overdrive", "Hydro Vortex", "Gigavolt Havoc",
         "Subzero Slammer", "Supersonic Skystrike", "Savage Spin-Out", "Acid Downpour", 
         "Tectonic Rage",
         "Continental Crush", "All-Out Pummeling", "Shattered Psyche", 
         "Never-Ending Nightmare",
         "Devastating Drake", "Black Hole Eclipse", "Corkscrew Crash", "Twinkle Tackle"
      }) || move.GetIsMax()) 
   {
      // show z-move power in description
      desc.move_bp = move.GetBP();
   }
   std::vector<int> bp_mods = CalculateBPModsSMSSSV
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
   base_power = CalcUtil::OF16(std::max(1, 
      CalcUtil::PokeRound((base_power * CalcUtil::ChainMods(bp_mods, 41, 2097152)) / 4096)));
   if 
   (
      attacker.GetTeraType() && 
      move.GetType() == attacker.GetTeraType() &&
      attacker.HasType({*attacker.GetTeraType()}) && 
      move.GetHits() == 1 && 
      !move.GetMultiAccuracy() &&
      move.GetPriority() <= 0 && move.GetBP() > 0 && 
      !move.Named({"Dragon Energy", "Eruption", "Water Spout"}) &&
      base_power < 60 && 
      static_cast<int>(gen) >= 9
   ) 
   {
      base_power = 60;
      desc.move_bp = 60;
   }
   return base_power;
}

std::vector<int> CalculateAtModsSMSSSV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc
) 
{
   std::vector<int> at_mods = {};

   // Slow Start also halves damage with special Z-moves
   if ((attacker.HasAbility({"Slow Start"}) && 
        attacker.GetAbilityOn() &&
        (move.GetMoveCategory() == ENUMS::MoveCategory::Physical || 
         (move.GetMoveCategory() == ENUMS::MoveCategory::Special && move.GetIsZ()))) ||
       (attacker.HasAbility({"Defeatist"}) && attacker.CurHP() <= attacker.MaxHP() / 2)
   ) 
   {
      at_mods.push_back(2048);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if 
   (
      (attacker.HasAbility({"Solar Power"}) &&
       field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) &&
       move.GetMoveCategory() == ENUMS::MoveCategory::Special) ||
      (attacker.Named({"Cherrim"}) &&
       attacker.HasAbility({"Flower Gift"}) &&
       field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) &&
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical)) 
   {
      at_mods.push_back(6144);
      desc.attacker_ability = attacker.GetAbility();
      desc.weather = field.weather;
   } 
   else if 
   (
      // Gorilla Tactics Has no effect during Dynamax (Anubis)
      (attacker.HasAbility({"Gorilla Tactics"}) && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical &&
       !attacker.GetIsDynamaxed())) 
   {
      at_mods.push_back(6144);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if 
   (
      field.attacker_side.is_flower_gift &&
      field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) &&
      move.GetMoveCategory() == ENUMS::MoveCategory::Physical) 
   {
      at_mods.push_back(6144);
      desc.weather = field.weather;
      desc.is_flower_gift_attacker = true;
   } 
   else if 
   (
      (attacker.HasAbility({"Guts"}) && 
       attacker.HasStatus() && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical) ||
      (attacker.CurHP() <= attacker.MaxHP() / 3 &&
       ((attacker.HasAbility({"Overgrow"}) &&
         move.HasType({ENUMS::TypeName::Grass})) ||
        (attacker.HasAbility({"Blaze"}) && 
         move.HasType({ENUMS::TypeName::Fire})) ||
        (attacker.HasAbility({"Torrent"}) && 
         move.HasType({ENUMS::TypeName::Water})) ||
        (attacker.HasAbility({"Swarm"}) && 
         move.HasType({ENUMS::TypeName::Bug})))) ||
      (move.GetMoveCategory() == ENUMS::MoveCategory::Special && 
       attacker.GetAbilityOn() && attacker.HasAbility({"Plus", "Minus"}))
   ) 
   {
      at_mods.push_back(6144);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (attacker.HasAbility({"Flash Fire"}) && 
            attacker.GetAbilityOn() && move.HasType({ENUMS::TypeName::Fire})) 
   {
      at_mods.push_back(6144);
      desc.attacker_ability = "Flash Fire";
   } 
   else if 
   (
      (attacker.HasAbility({"Steelworker"}) && 
       move.HasType({ENUMS::TypeName::Steel})) ||
      (attacker.HasAbility({"Dragon\'s Maw"}) && 
       move.HasType({ENUMS::TypeName::Dragon})) ||
      (attacker.HasAbility({"Rocky Payload"}) && 
       move.HasType({ENUMS::TypeName::Rock}))
   ) 
   {
      at_mods.push_back(6144);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (attacker.HasAbility({"Transistor"}) && move.HasType({ENUMS::TypeName::Electric})) 
   {
      at_mods.push_back(static_cast<int>(gen) >= 9 ? 5325 : 6144);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (attacker.HasAbility({"Stakeout"}) && attacker.GetAbilityOn()) 
   {
      at_mods.push_back(8192);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if 
   (
      (attacker.HasAbility({"Water Bubble"}) && move.HasType({ENUMS::TypeName::Water})) ||
      (attacker.HasAbility({"Huge Power", "Pure Power"}) && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical)
   ) 
   {
      at_mods.push_back(8192);
      desc.attacker_ability = attacker.GetAbility();
   }

   if ((defender.HasAbility({"Thick Fat"}) && 
        move.HasType({ENUMS::TypeName::Fire, ENUMS::TypeName::Ice})) ||
       (defender.HasAbility({"Water Bubble"}) && move.HasType({ENUMS::TypeName::Fire})) ||
       (defender.HasAbility({"Purifying Salt"}) && move.HasType({ENUMS::TypeName::Ghost}))) 
   {
      at_mods.push_back(2048);
      desc.defender_ability = defender.GetAbility();
   }

   if (static_cast<int>(gen) >= 9 && 
       defender.HasAbility({"Heatproof"}) && 
       move.HasType({ENUMS::TypeName::Fire})) 
   {
      at_mods.push_back(2048);
      desc.defender_ability = defender.GetAbility();
   }
   // Pokemon with "-of Ruin" Ability are immune to the opposing "-of Ruin" ability
   bool is_tablets_of_ruin_active = (defender.HasAbility({"Tablets of Ruin"}) || 
                                     field.is_tablets_of_ruin) &&
                                    !attacker.HasAbility({"Tablets of Ruin"});
   bool is_vessel_of_ruin_active = (defender.HasAbility({"Vessel of Ruin"}) || 
                                    field.is_vessel_of_ruin) &&
                                   !attacker.HasAbility({"Vessel of Ruin"});
   if 
   (
      (is_tablets_of_ruin_active && move.GetMoveCategory() == ENUMS::MoveCategory::Physical) ||
      (is_vessel_of_ruin_active && move.GetMoveCategory() == ENUMS::MoveCategory::Special)
   ) 
   {
      if (defender.HasAbility({"Tablets of Ruin"}) || 
          defender.HasAbility({"Vessel of Ruin"})) 
      {
         desc.defender_ability = defender.GetAbility();
      } 
      else 
      {
         if (move.GetMoveCategory() == ENUMS::MoveCategory::Special)
         {
            desc.is_vessel_of_ruin = true;
         }
         else
         {
            desc.is_tablets_of_ruin = true;
         }
      }
      at_mods.push_back(3072);
   }

   if (CalcUtil::IsQPActive(attacker, field)) 
   {
      if 
      (
         (move.GetMoveCategory() == ENUMS::MoveCategory::Physical && 
          CalcUtil::GetQPBoostedStat(attacker, gen) == ENUMS::StatID::atk) ||
         (move.GetMoveCategory() == ENUMS::MoveCategory::Special && 
          CalcUtil::GetQPBoostedStat(attacker, gen) == ENUMS::StatID::spa)
      ) 
      {
         at_mods.push_back(5325);
         desc.attacker_ability = attacker.GetAbility();
      }
   }

   if 
   (
      (attacker.HasAbility({"Hadron Engine"}) && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Special &&
       field.HasTerrain({ENUMS::Terrain::Electric_t})) ||
      (attacker.HasAbility({"Orichalcum Pulse"}) && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical &&
       field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) && 
       !attacker.HasItem({"Utility Umbrella"}))
   ) 
   {
      at_mods.push_back(5461);
      desc.attacker_ability = attacker.GetAbility();
   }

   if ((attacker.HasItem({"Thick Club"}) &&
        attacker.Named({"Cubone", "Marowak", "Marowak-Alola", "Marowak-Alola-Totem"}) &&
        move.GetMoveCategory() == ENUMS::MoveCategory::Physical) ||
       (attacker.HasItem({"Deep Sea Tooth"}) &&
        attacker.Named({"Clamperl"}) &&
        move.GetMoveCategory() == ENUMS::MoveCategory::Special) ||
       (attacker.HasItem({"Light Ball"}) && 
        attacker.GetName().find("Pikachu") != std::string::npos && 
        !move.GetIsZ())
   ) 
   {
      at_mods.push_back(8192);
      desc.attacker_item = attacker.GetItem();
      // Choice Band/Scarf/Specs move lock and stat boosts are ignored during Dynamax (Anubis)
   } 
   else if (!move.GetIsZ() && !move.GetIsMax() &&
            ((attacker.HasItem({"Choice Band"}) && 
              move.GetMoveCategory() == ENUMS::MoveCategory::Physical) ||
             (attacker.HasItem({"Choice Specs"}) && 
              move.GetMoveCategory() == ENUMS::MoveCategory::Special))
   ) 
   {
      at_mods.push_back(6144);
      desc.attacker_item = attacker.GetItem();
   }

   return at_mods;
}

int CalculateAttackSMSSSV
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
   int attack;
   ENUMS::StatID attack_stat =
      move.Named({"Shell Side Arm"}) &&
      CalcUtil::GetShellSideArmCategory(attacker, defender) == ENUMS::MoveCategory::Physical
         ? ENUMS::StatID::atk
         : move.Named({"Body Press"})
         ? ENUMS::StatID::def
         : move.GetMoveCategory() == ENUMS::MoveCategory::Special
            ? ENUMS::StatID::spa
            : ENUMS::StatID::atk;
   desc.attack_evs =
      move.Named({"Foul Play"})
         ? CalcUtil::GetStatDescriptionText(gen, defender, attack_stat, defender.GetNature())
         : CalcUtil::GetStatDescriptionText(gen, attacker, attack_stat, attacker.GetNature());
   Pokemon::Pokemon attack_source = move.Named({"Foul Play"}) ? defender : attacker;
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
   if (attacker.HasAbility({"Hustle"}) && move.GetMoveCategory() == ENUMS::MoveCategory::Physical)
   {
      attack = CalcUtil::PokeRound((attack * 3) / 2);
      desc.attacker_ability = attacker.GetAbility();
   }
   std::vector<int> at_mods = CalculateAtModsSMSSSV(gen, attacker, defender, move, field, desc);
   attack = CalcUtil::OF16(std::max(1, 
      CalcUtil::PokeRound((attack * CalcUtil::ChainMods(at_mods, 410, 131072)) / 4096)));
   
   return attack;
}

std::vector<int> CalculateDfModsSMSSSV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical,
   bool hits_physical
) 
{
   std::vector<int> df_mods{};
   if (defender.HasAbility({"Marvel Scale"}) && 
       defender.HasStatus() && 
       hits_physical) 
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
   else if 
   (
      defender.HasAbility({"Grass Pelt"}) &&
      field.HasTerrain({ENUMS::Terrain::Grassy_t}) &&
      hits_physical
   ) 
   {
      df_mods.push_back(6144);
      desc.defender_ability = defender.GetAbility();
   } 
   else if (defender.HasAbility({"Fur Coat"}) && hits_physical) 
   {
      df_mods.push_back(8192);
      desc.defender_ability = defender.GetAbility();
   }
   // Pokemon with "-of Ruin" Ability are immune to the opposing "-of Ruin" ability
   bool is_sword_of_ruin_active = (attacker.HasAbility({"Sword of Ruin"}) || 
                                   field.is_sword_of_ruin) &&
                                  !defender.HasAbility({"Sword of Ruin"});
   bool is_beads_of_ruin_active = (attacker.HasAbility({"Beads of Ruin"}) || 
                                   field.is_beads_of_ruin) &&
                                  !defender.HasAbility({"Beads of Ruin"});
   if 
   (
      (is_sword_of_ruin_active && hits_physical) ||
      (is_beads_of_ruin_active && !hits_physical)
   ) 
   {
      if (attacker.HasAbility({"Sword of Ruin"}) || 
          attacker.HasAbility({"Beads of Ruin"})) 
      {
         desc.attacker_ability = attacker.GetAbility();
      } 
      else 
      {
         if (hits_physical)
         {
            desc.is_sword_of_ruin = true;
         }
         else
         {
            desc.is_beads_of_ruin = true;
         }
      }
      df_mods.push_back(3072);
   }

   if (CalcUtil::IsQPActive(defender, field)) 
   {
      if 
      (
         (hits_physical && CalcUtil::GetQPBoostedStat(defender, gen) == ENUMS::StatID::def) ||
         (!hits_physical && CalcUtil::GetQPBoostedStat(defender, gen) == ENUMS::StatID::spd)
      ) 
      {
         desc.defender_ability = defender.GetAbility();
         df_mods.push_back(5324);
      }
   }

   if ((defender.HasItem({"Eviolite"}) &&
        (defender.GetName() == "Dipplin" || 
         Data::Species::Instance().GetSpeciesByGen(gen, defender.GetName()).nfe)) ||
       (!hits_physical && defender.HasItem({"Assault Vest"})))
   {
      df_mods.push_back(6144);
      desc.defender_item = defender.GetItem();
   } 
   else if 
   (
      (defender.HasItem({"Metal Powder"}) && 
       defender.Named({"Ditto"}) && 
       hits_physical) ||
      (defender.HasItem({"Deep Sea Scale"}) && 
       defender.Named({"Clamperl"}) && 
       !hits_physical)
   ) 
   {
      df_mods.push_back(8192);
      desc.defender_item = defender.GetItem();
   }

   return df_mods;
}

int CalculateDefenseSMSSSV
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
   bool hits_physical = move.GetOverrideDefensiveStat() &&
      Stats::ConvertStatID(*move.GetOverrideDefensiveStat()) == ENUMS::StatID::def || 
      move.GetMoveCategory() == ENUMS::MoveCategory::Physical ||
      (move.Named({"Shell Side Arm"}) && 
      CalcUtil::GetShellSideArmCategory(attacker, defender) == ENUMS::MoveCategory::Physical);
   ENUMS::StatID defense_stat = hits_physical ? ENUMS::StatID::def : ENUMS::StatID::spd;
   desc.defense_evs 
      = CalcUtil::GetStatDescriptionText(gen, defender, defense_stat, defender.GetNature());
   if (defender.GetBoosts().at(defense_stat) == 0 ||
       (is_critical && defender.GetBoosts().at(defense_stat) > 0) ||
        move.GetIgnoreDefense()) 
   {
      defense = defender.GetRawStats().at(defense_stat);
   } 
   else if (attacker.HasAbility({"Unaware"}))
   {
      defense = defender.GetRawStats().at(defense_stat);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else 
   {
      defense = CalcUtil::GetModifiedStat(defender.GetRawStats().at(defense_stat), 
                                          defender.GetBoosts().at(defense_stat));
      desc.defense_boost = defender.GetBoosts().at(defense_stat);
   }

   // unlike all other defense modifiers, Sandstorm SpD boost gets applied directly
   if (field.HasWeather({ENUMS::Weather::Sand}) && 
       defender.HasType({ENUMS::TypeName::Rock}) && 
       !hits_physical) 
   {
      defense = CalcUtil::PokeRound((defense * 3) / 2);
      desc.weather = field.weather;
   }
   if (field.HasWeather({ENUMS::Weather::Snow}) && 
       defender.HasType({ENUMS::TypeName::Ice}) && 
       hits_physical) 
   {
      defense = CalcUtil::PokeRound((defense * 3) / 2);
      desc.weather = field.weather;
   }

   std::vector<int> df_mods = CalculateDfModsSMSSSV
   (
      gen,
      attacker,
      defender,
      move,
      field,
      desc,
      is_critical,
      hits_physical
   );

   return CalcUtil::OF16(std::max(1, 
      CalcUtil::PokeRound((defense * CalcUtil::ChainMods(df_mods, 410, 131072)) / 4096)));
}

int CalculateBaseDamageSMSSSV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
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
      base_damage = CalcUtil::PokeRound(CalcUtil::OF32(base_damage * 1024) / 4096);
   }

   if 
   (
      field.HasWeather({ENUMS::Weather::Sun}) && 
      move.Named({"Hydro Steam"}) && 
      !attacker.HasItem({"Utility Umbrella"})
   ) 
   {
      base_damage = CalcUtil::PokeRound(CalcUtil::OF32(base_damage * 6144) / 4096);
      desc.weather = field.weather;
   } 
   else if (!defender.HasItem({"Utility Umbrella"})) 
   {
      if 
      (
         (field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) && 
          move.HasType({ENUMS::TypeName::Fire})) ||
         (field.HasWeather({ENUMS::Weather::Rain, ENUMS::Weather::HeavyRain}) && 
          move.HasType({ENUMS::TypeName::Water}))
      ) 
      {
         base_damage = CalcUtil::PokeRound(CalcUtil::OF32(base_damage * 6144) / 4096);
         desc.weather = field.weather;
      } 
      else if 
      (
         (field.HasWeather({ENUMS::Weather::Sun}) && 
          move.HasType({ENUMS::TypeName::Water})) ||
         (field.HasWeather({ENUMS::Weather::Rain}) && 
          move.HasType({ENUMS::TypeName::Fire}))
      ) 
      {
         base_damage = CalcUtil::PokeRound(CalcUtil::OF32(base_damage * 2048) / 4096);
         desc.weather = field.weather;
      }
   }

   if (is_critical) 
   {
      base_damage = std::floor(CalcUtil::OF32(base_damage * 1.5));
      desc.is_critical = is_critical;
   }

   return base_damage;
}

std::vector<int> CalculateFinalModsSMSSSV
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
   std::vector<int> final_mods{};

   if (field.defender_side.is_reflect && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Physical &&
       !is_critical && 
       !field.defender_side.is_aurora_veil) 
   {
      // doesn't stack with Aurora Veil
      final_mods.push_back(field.game_type != ENUMS::GameType::Singles ? 2732 : 2048);
      desc.is_reflect = true;
   } 
   else if 
   (
      field.defender_side.is_light_screen && 
      move.GetMoveCategory() == ENUMS::MoveCategory::Special &&
      !is_critical && 
      !field.defender_side.is_aurora_veil
   ) 
   {
      // doesn't stack with Aurora Veil
      final_mods.push_back(field.game_type != ENUMS::GameType::Singles ? 2732 : 2048);
      desc.is_light_screen = true;
   }
   if (field.defender_side.is_aurora_veil && !is_critical) 
   {
      final_mods.push_back(field.game_type != ENUMS::GameType::Singles ? 2732 : 2048);
      desc.is_aurora_veil = true;
   }

   if (attacker.HasAbility({"Neuroforce"}) && type_effectiveness > 1) 
   {
      final_mods.push_back(5120);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (attacker.HasAbility({"Sniper"}) && is_critical) 
   {
      final_mods.push_back(6144);
      desc.attacker_ability = attacker.GetAbility();
   } 
   else if (attacker.HasAbility({"Tinted Lens"}) && type_effectiveness < 1) 
   {
      final_mods.push_back(8192);
      desc.attacker_ability = attacker.GetAbility();
   }

   if (defender.GetIsDynamaxed() && 
       move.Named({"Dynamax Cannon", "Behemoth Blade", "Behemoth Bash"})) 
   {
      final_mods.push_back(8192);
   }

   if (defender.HasAbility({"Multiscale", "Shadow Shield"}) &&
       defender.CurHP() == defender.MaxHP() &&
       hit_count == 0 &&
       (!field.defender_side.is_sr && 
        (!field.defender_side.spikes || 
         defender.HasType({ENUMS::TypeName::Flying})) ||
        defender.HasItem({"Heavy-Duty Boots"})) && 
       !attacker.HasAbility({"Parental Bond (Child)"})
   ) 
   {
      final_mods.push_back(2048);
      desc.defender_ability = defender.GetAbility();
   }

   if (defender.HasAbility({"Fluffy"}) && 
       move.GetMoveFlags().contact && 
       !attacker.HasAbility({"Long Reach"})) 
   {
      final_mods.push_back(2048);
      desc.defender_ability = defender.GetAbility();
   } 
   else if 
   (
      (defender.HasAbility({"Punk Rock"}) && 
       move.GetMoveFlags().sound) ||
      (defender.HasAbility({"Ice Scales"}) && 
       move.GetMoveCategory() == ENUMS::MoveCategory::Special)
   ) 
   {
      final_mods.push_back(2048);
      desc.defender_ability = defender.GetAbility();
   }

   if (defender.HasAbility({"Solid Rock", "Filter", "Prism Armor"}) && 
       type_effectiveness > 1) 
   {
      final_mods.push_back(3072);
      desc.defender_ability = defender.GetAbility();
   }

   if (field.defender_side.is_friend_guard) 
   {
      final_mods.push_back(3072);
      desc.is_friend_guard = true;
   }

   if (defender.HasAbility({"Fluffy"}) && 
       move.HasType({ENUMS::TypeName::Fire})) 
   {
      final_mods.push_back(8192);
      desc.defender_ability = defender.GetAbility();
   }

   if (attacker.HasItem({"Expert Belt"}) && 
       type_effectiveness > 1 && 
       !move.GetIsZ()) 
   {
      final_mods.push_back(4915);
      desc.attacker_item = attacker.GetItem();
   } 
   else if (attacker.HasItem({"Life Orb"})) 
   {
      final_mods.push_back(5324);
      desc.attacker_item = attacker.GetItem();
   } 
   else if (attacker.HasItem({"Metronome"}) && move.GetTimesUsedWithMetronome() >= 1) 
   {
      if (move.GetTimesUsedWithMetronome() <= 4) 
      {
         final_mods.push_back(4096 + move.GetTimesUsedWithMetronome() * 819);
      } 
      else 
      {
         final_mods.push_back(8192);
      }
      desc.attacker_item = attacker.GetItem();
   }

   if (defender.GetItem() &&
       move.HasType({*Data::Items::Instance().GetBerryResistType(*defender.GetItem())}) &&
       (type_effectiveness > 1 || move.HasType({ENUMS::TypeName::Normal})) &&
       hit_count == 0 &&
       !attacker.HasAbility({"Unnerve", "As One (Glastrier)", "As One (Spectrier)"})) 
   {
      if (defender.HasAbility({"Ripen"})) 
      {
         final_mods.push_back(1024);
      } 
      else 
      {
         final_mods.push_back(2048);
      }
      desc.defender_item = defender.GetItem();
   }

   return final_mods;
}

bool HasTerrainSeed(const Pokemon::Pokemon& pokemon) 
{
   return pokemon.HasItem({"Electric Seed", "Misty Seed", "Grassy Seed", "Psychic Seed"});
}

Result::Result CalculateSMSSSV
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
   CalcUtil::CheckTeraformZero(attacker, field);
   CalcUtil::CheckTeraformZero(defender, field);
   CalcUtil::CheckForecast(attacker, field.weather);
   CalcUtil::CheckForecast(defender, field.weather);
   CalcUtil::CheckItem(attacker, field.is_magic_room ? *field.is_magic_room : false);
   CalcUtil::CheckItem(defender, field.is_magic_room ? *field.is_magic_room : false);
   CalcUtil::CheckWonderRoom(attacker, field.is_wonder_room ? *field.is_wonder_room : false);
   CalcUtil::CheckWonderRoom(defender, field.is_wonder_room ? *field.is_wonder_room : false);
   CalcUtil::CheckSeedBoost(attacker, field);
   CalcUtil::CheckSeedBoost(defender, field);
   CalcUtil::CheckDauntlessShield(attacker, gen);
   CalcUtil::CheckDauntlessShield(defender, gen);
   CalcUtil::CheckEmbody(attacker, gen);
   CalcUtil::CheckEmbody(defender, gen);

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
   CalcUtil::CheckDownload(attacker, defender, field.is_wonder_room ? *field.is_wonder_room : false);
   CalcUtil::CheckDownload(defender, attacker, field.is_wonder_room ? *field.is_wonder_room : false);
   CalcUtil::CheckIntrepidSword(attacker, gen);
   CalcUtil::CheckIntrepidSword(defender, gen);

   CalcUtil::CheckWindRider(attacker, field.attacker_side);
   CalcUtil::CheckWindRider(defender, field.defender_side);

   if (move.Named({"Meteor Beam", "Electro Shot"})) 
   {
      int spa_boost =
         attacker.HasAbility({"Simple"}) ? 2
         : attacker.HasAbility({"Contrary"}) ? -1
         : 1;
      // restrict to +- 6
      attacker.SetBoost(ENUMS::StatID::spa, 
                        std::min(6, std::max(-6, attacker.GetBoosts().at(ENUMS::StatID::spa))));
   }

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
      .is_wonder_room = field.is_wonder_room ? *field.is_wonder_room : false,
      .move_name = move.GetName(),
      .is_defender_dynamaxed = defender.GetIsDynamaxed() ? *defender.GetIsDynamaxed() : false
   };

   // only display tera type if it applies
   if (attacker.GetTeraType() && 
       (*attacker.GetTeraType() != ENUMS::TypeName::Stellar || 
         move.GetName() == "Tera Blast" || 
        move.GetIsStellarFirstUse())) 
   {
      // tera blast Has special behavior with tera stellar
      desc.is_stellar_first_use = attacker.GetName() != "Terapagos-Stellar" && 
                                  move.GetName() == "Tera Blast" &&
                                  attacker.GetTeraType() == ENUMS::TypeName::Stellar && 
                                  move.GetIsStellarFirstUse();
      desc.attacker_tera = Data::Types::Instance().TypeNameENUMToString(*attacker.GetTeraType());
   }
   if (defender.GetTeraType() && *defender.GetTeraType() != ENUMS::TypeName::Stellar) 
   {
      desc.defender_tera = Data::Types::Instance().TypeNameENUMToString(*defender.GetTeraType());
   }

   if (move.Named({"Photon Geyser", "Light That Burns the Sky"}) ||
       (move.Named({"Tera Blast"}) && attacker.GetTeraType())) 
   {
      move.SetMoveCategory(attacker.GetStats().at(ENUMS::StatID::atk) > 
                           attacker.GetStats().at(ENUMS::StatID::spa) 
                           ? ENUMS::MoveCategory::Physical
                           : ENUMS::MoveCategory::Special);
   }

   Result::Result result(gen, attacker, defender, move, field, 0, desc);

   if (move.GetMoveCategory() == ENUMS::MoveCategory::Status && 
       !move.Named({"Nature Power"}))
   {
      return result;
   }

   if (move.GetMoveFlags().punch && attacker.HasItem({"Punching Glove"})) 
   {
      desc.attacker_item = attacker.GetItem();
      move.SetMoveFlagContact(false);
   }

   bool breaks_protect = move.GetBreaksProtect() || 
                         move.GetIsZ() || 
                         attacker.GetIsDynamaxed() ||
                         (attacker.HasAbility({"Unseen Fist"}) && 
                          move.GetMoveFlags().contact);

   if (field.defender_side.is_protected && !breaks_protect) 
   {
      desc.is_protected = true;
      return result;
   }

   bool defender_ignores_ability = defender.HasAbility
   ({
      "Full Metal Body",
      "Prism Armor",
      "Shadow Shield",
      "Tablets of Ruin",
      "Vessel of Ruin"
   });

   bool attacker_ignores_ability 
      = attacker.HasAbility({"Mold Breaker", "Teravolt", "Turboblaze"});
   bool move_ignores_ability = move.Named
   ({
      "G-Max Drum Solo",
      "G-Max Fire Ball",
      "G-Max Hydrosnipe",
      "Light That Burns the Sky",
      "Menacing Moonraze Maelstrom",
      "Moongeist Beam",
      "Photon Geyser",
      "Searing Sunraze Smash",
      "Sunsteel Strike"
   });
   if (!defender_ignores_ability && !defender.HasAbility({"Poison Heal"}) &&
       (attacker_ignores_ability || move_ignores_ability)) 
   {
      if (attacker_ignores_ability) desc.attacker_ability = attacker.GetAbility();
      if (defender.HasItem({"Ability Shield"})) 
      {
         desc.defender_item = defender.GetItem();
      } 
      else 
      {
         defender.SetAbility("");
      }
   }

   std::vector<std::string> ignores_neutralizing_gas = 
   {
      "As One (Glastrier)", "As One (Spectrier)", "Battle Bond", "Comatose",
      "Disguise", "Gulp Missile", "Ice Face", "Multitype", "Neutralizing Gas",
      "Power Construct", "RKS System", "Schooling", "Shields Down",
      "Stance Change", "Tera Shift", "Zen Mode", "Zero to Hero", ""
   };

   if (attacker.HasAbility({"Neutralizing Gas"}) &&
       !defender.HasAbility(ignores_neutralizing_gas))
   {
      desc.attacker_ability = attacker.GetAbility();
      defender.SetAbility("");
   }

   if (defender.HasAbility({"Neutralizing Gas"}) &&
      !attacker.HasAbility(ignores_neutralizing_gas)) 
   {
      desc.defender_ability = defender.GetAbility();
      attacker.SetAbility("");
   }

   // Merciless does not ignore Shell Armor, damage dealt to a poisoned Pokemon with Shell Armor
   // will not be a critical hit (UltiMario)
   bool is_critical = !defender.HasAbility({"Battle Armor", "Shell Armor"}) &&
                      (move.GetIsCrit() || 
                       (attacker.HasAbility({"Merciless"}) && 
                        defender.HasStatus({ENUMS::StatusName::psn, ENUMS::StatusName::tox}))) &&
                      move.GetTimesUsed() == 1;

   ENUMS::TypeName type = move.GetType();
   if (move.GetOriginalName() == "Weather Ball") 
   {
      bool holding_umbrella = attacker.HasItem({"Utility Umbrella"});
      type =
         field.HasWeather({ENUMS::Weather::Sun, ENUMS::Weather::HarshSunshine}) && 
         !holding_umbrella ? ENUMS::TypeName::Fire
            : field.HasWeather({ENUMS::Weather::Rain, ENUMS::Weather::HeavyRain}) && 
            !holding_umbrella ? ENUMS::TypeName::Water
               : field.HasWeather({ENUMS::Weather::Sand}) 
               ? ENUMS::TypeName::Rock
                  : field.HasWeather({ENUMS::Weather::Hail, ENUMS::Weather::Snow}) 
                  ? ENUMS::TypeName::Ice
                     : ENUMS::TypeName::Normal;
      desc.weather = field.weather;
      desc.move_type = type;
   } 
   else if (move.Named({"Judgment"}) && attacker.GetItem() && 
            attacker.GetItem().value().find("Plate") != std::string::npos) 
   {
      type = *Data::Items::Instance().GetItemBoostType(attacker.GetItem().value());
      desc.move_type = type;
   } 
   else if (move.Named({"Techno Blast"}) && attacker.GetItem() && 
            attacker.GetItem().value().find("Drive") != std::string::npos) 
   {
      type = *Data::Items::Instance().GetTechnoBlast(attacker.GetItem().value());
      desc.move_type = type;
   } 
   else if (move.GetOriginalName() == "Multi-Attack" &&
            attacker.GetItem() && attacker.GetItem().value().find("Memory") != std::string::npos) 
   {
      type = *Data::Items::Instance().GetMultiAttack(attacker.GetItem().value());
      desc.move_type = type;
   } 
   else if (move.Named({"Natural Gift"}) && attacker.GetItem() &&
            attacker.GetItem().value().ends_with("Berry"))
   {
      Data::Items::NaturalGift gift 
         = Data::Items::Instance().GetNaturalGift(gen, attacker.GetItem().value());
      type = gift.t;
      desc.move_type = type;
      desc.attacker_item = attacker.GetItem().value();
   }
   else if 
   (
      move.Named({"Nature Power"}) ||
      (move.GetOriginalName() == "Terrain Pulse" && 
       CalcUtil::IsGrounded(attacker, field))
   ) 
   {
      type =
         field.HasTerrain({ENUMS::Terrain::Electric_t}) ? ENUMS::TypeName::Electric
         : field.HasTerrain({ENUMS::Terrain::Grassy_t}) ? ENUMS::TypeName::Grass
         : field.HasTerrain({ENUMS::Terrain::Misty_t}) ? ENUMS::TypeName::Fairy
         : field.HasTerrain({ENUMS::Terrain::Psychic_t}) ? ENUMS::TypeName::Psychic
         : ENUMS::TypeName::Normal;
      desc.terrain = field.terrain;

      if (move.GetIsMax()) 
      {
         desc.move_type = type;
      }

      // If the Nature Power user Has the ability Prankster, it cannot affect
      // Dark-types or grounded foes if Psychic Terrain is active
      if (!(move.Named({"Nature Power"}) && attacker.HasAbility({"Prankster"})) &&
          ((defender.HasType({ENUMS::TypeName::Dark}) ||
            (field.HasTerrain({ENUMS::Terrain::Psychic_t}) && 
          CalcUtil::IsGrounded(defender, field))))) 
      {
         desc.move_type = type;
      }
   } 
   else if (move.GetOriginalName() == "Revelation Dance") 
   {
      if (attacker.GetTeraType()) 
      {
         type = *attacker.GetTeraType();
      } 
      else 
      {
         type = attacker.GetTypes().at(0);
      }
   } 
   else if (move.Named({"Aura Wheel"})) 
   {
      if (attacker.Named({"Morpeko"})) 
      {
         type = ENUMS::TypeName::Electric;
      } 
      else if (attacker.Named({"Morpeko-Hangry"})) 
      {
         type = ENUMS::TypeName::Dark;
      }
   } 
   else if (move.Named({"Raging Bull"}))
   {
      if (attacker.Named({"Tauros-Paldea-Combat"})) 
      {
         type = ENUMS::TypeName::Fighting;
      } 
      else if (attacker.Named({"Tauros-Paldea-Blaze"})) 
      {
         type = ENUMS::TypeName::Fire;
      } 
      else if (attacker.Named({"Tauros-Paldea-Aqua"})) 
      {
         type = ENUMS::TypeName::Water;
      }
   } 
   else if (move.Named({"Ivy Cudgel"})) 
   {
      if (attacker.GetName().find("Ogerpon-Cornerstone") != std::string::npos) 
      {
         type = ENUMS::TypeName::Rock;
      } 
      else if (attacker.GetName().find("Ogerpon-Hearthflame") != std::string::npos) 
      {
         type = ENUMS::TypeName::Fire;
      } 
      else if (attacker.GetName().find("Ogerpon-Wellspring") != std::string::npos) 
      {
         type = ENUMS::TypeName::Water;
      }
   }

   bool has_ate_ability_type_change = false;
   bool is_aerilate = false;
   bool is_pixilate = false;
   bool is_refrigerate = false;
   bool is_normalize = false;
   bool is_galvanize = false;
   bool is_liquid_voice = false;
   bool no_type_change = move.Named
   ({
      "Revelation Dance",
      "Judgment",
      "Nature Power",
      "Techno Blast",
      "Multi-Attack",
      "Natural Gift",
      "Weather Ball",
      "Terrain Pulse",
      "Struggle",
   }) || (move.Named({"Tera Blast"}) && attacker.GetTeraType());

   if (!move.GetIsZ() && !no_type_change) 
   {
      bool normal = type == ENUMS::TypeName::Normal;
      if ((is_aerilate = attacker.HasAbility({"Aerilate"}) && normal)) 
      {
         type = ENUMS::TypeName::Flying;
      } 
      else if ((is_galvanize = attacker.HasAbility({"Galvanize"}) && normal)) 
      {
         type = ENUMS::TypeName::Electric;
      } 
      else if ((is_liquid_voice = attacker.HasAbility({"Liquid Voice"}) && 
                !!move.GetMoveFlags().sound)) 
      {
         type = ENUMS::TypeName::Water;
      } 
      else if ((is_pixilate = attacker.HasAbility({"Pixilate"}) && normal)) 
      {
         type = ENUMS::TypeName::Fairy;
      } 
      else if ((is_refrigerate = attacker.HasAbility({"Refrigerate"}) && normal)) 
      {
         type = ENUMS::TypeName::Ice;
      } 
      else if ((is_normalize = attacker.HasAbility({"Normalize"}))) 
      { // Boosts any type
         type = ENUMS::TypeName::Normal;
      }
      if (is_galvanize || is_pixilate || is_refrigerate || is_aerilate || is_normalize) {
         desc.attacker_ability = attacker.GetAbility();
         has_ate_ability_type_change = true;
      } else if (is_liquid_voice) {
         desc.attacker_ability = attacker.GetAbility();
      }
   }

   if (move.Named({"Tera Blast"}) && attacker.GetTeraType()) 
   {
      type = *attacker.GetTeraType();
   }

   move.SetType(type);

   // FIXME: this is incorrect, should be move.GetMoveFlags().heal, not move.drain
   if ((attacker.HasAbility({"Triage"}) && move.GetDrain()) ||
       (attacker.HasAbility({"Gale Wings"}) &&
        move.HasType({ENUMS::TypeName::Flying}) &&
        attacker.CurHP() == attacker.MaxHP())) 
   {
      move.SetPriority(1);
      desc.attacker_ability = attacker.GetAbility();
   }

   bool is_ghost_revealed = attacker.HasAbility({"Scrappy", "Mind\'s Eye"}) || 
                            field.defender_side.is_foresight;
   bool is_ring_target = defender.HasItem({"Ring Target"}) && !defender.HasAbility({"Klutz"});
   float type_eff1 = CalcUtil::GetMoveEffectiveness
   (
      gen, 
      move, 
      defender.GetTypes().at(0),
      is_ghost_revealed,
      field.is_gravity ? *field.is_gravity : false,
      is_ring_target
   );
   float type_eff2 = defender.GetTypes().size() > 1 ? 
   CalcUtil::GetMoveEffectiveness
   (
      gen, 
      move, 
      defender.GetTypes().at(1),
      is_ghost_revealed,
      field.is_gravity ? *field.is_gravity : false,
      is_ring_target
   ) : 1;
   float type_eff = type_eff1 * type_eff2;

   if (defender.GetTeraType() && *defender.GetTeraType() != ENUMS::TypeName::Stellar) 
   {
      type_eff = CalcUtil:: GetMoveEffectiveness
      (
         gen,
         move,
         *defender.GetTeraType(),
         is_ghost_revealed,
         field.is_gravity ? *field.is_gravity : false,
         is_ring_target
      );
   }

   if (type_eff == 0 && move.HasType({ENUMS::TypeName::Ground}) &&
       defender.HasItem({"Iron Ball"}) && !defender.HasAbility({"Klutz"})) 
   {
      type_eff = 1;
   }

   if (type_eff == 0 && move.Named({"Thousand Arrows"})) 
   {
      type_eff = 1;
   }

   if (type_eff == 0) 
   {
      return result;
   }

   if ((move.Named({"Sky Drop"}) &&
        (defender.HasType({ENUMS::TypeName::Flying}) || 
         defender.GetWeight() >= 200 || 
         field.is_gravity ? *field.is_gravity : false)) ||
       (move.Named({"Synchronoise"}) && !defender.HasType({attacker.GetTypes().at(0)}) &&
        (attacker.GetTypes().size() == 1 || !defender.HasType({attacker.GetTypes().at(1)}))) ||
       (move.Named({"Dream Eater"}) &&
        (!(defender.HasStatus({ENUMS::StatusName::slp}) || defender.HasAbility({"Comatose"})))) ||
       (move.Named({"Steel Roller"}) && !field.terrain) ||
       (move.Named({"Poltergeist"}) && (!defender.GetItem() || 
        CalcUtil::IsQPActive(defender, field)))
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

   auto effectiveness 
      = Data::Types::Instance().GetTypeEffectivenessByTypeAndGen(gen, move.GetType());
   if (field.HasWeather({ENUMS::Weather::StrongWinds}) && 
       defender.HasType({ENUMS::TypeName::Flying}) &&
       effectiveness.at(ENUMS::TypeName::Flying) == ENUMS::TypeEffectiveness::_2) 
   {
      type_eff /= 2;
      desc.weather = field.weather;
   }

   if (move.GetType() == ENUMS::TypeName::Stellar) 
   {
      desc.defender_tera 
         = Data::Types::Instance().TypeNameENUMToString(*defender.GetTeraType()); 
      // always show in this case
      type_eff = !defender.GetTeraType() ? 1 : 2;
   }

   float turn2type_eff = type_eff;

   // Tera Shell works only at full HP, but for all hits of multi-hit moves
   if (defender.HasAbility({"Tera Shell"}) &&
       defender.CurHP() == defender.MaxHP() &&
       (!field.defender_side.is_sr && 
        (!field.defender_side.spikes || defender.HasType({ENUMS::TypeName::Flying})) ||
        defender.HasItem({"Heavy-Duty Boots"}))
   ) {
      type_eff = 0.5;
      desc.defender_ability = defender.GetAbility();
   }

   if ((defender.HasAbility({"Wonder Guard"}) && type_eff <= 1) ||
       (move.HasType({ENUMS::TypeName::Grass}) && defender.HasAbility({"Sap Sipper"})) ||
       (move.HasType({ENUMS::TypeName::Fire}) && 
        defender.HasAbility({"Flash Fire", "Well-Baked Body"})) ||
       (move.HasType({ENUMS::TypeName::Water}) && 
        defender.HasAbility({"Dry Skin", "Storm Drain", "Water Absorb"})) ||
       (move.HasType({ENUMS::TypeName::Electric}) &&
        defender.HasAbility({"Lightning Rod", "Motor Drive", "Volt Absorb"})) ||
       (move.HasType({ENUMS::TypeName::Ground}) &&
        !field.is_gravity ? *field.is_gravity : false && 
        !move.Named({"Thousand Arrows"}) &&
        !defender.HasItem({"Iron Ball"}) && defender.HasAbility({"Levitate"})) ||
       (move.GetMoveFlags().bullet && defender.HasAbility({"Bulletproof"})) ||
       (move.GetMoveFlags().sound && !move.Named({"Clangorous Soul"}) && 
        defender.HasAbility({"Soundproof"})) ||
       (move.GetPriority() > 0 && 
        defender.HasAbility({"Queenly Majesty", "Dazzling", "Armor Tail"})) ||
       (move.HasType({ENUMS::TypeName::Ground}) && defender.HasAbility({"Earth Eater"})) ||
       (move.GetMoveFlags().wind && defender.HasAbility({"Wind Rider"}))
   ) 
   {
      desc.defender_ability = defender.GetAbility();
      return result;
   }

   if (move.HasType({ENUMS::TypeName::Ground}) && !move.Named({"Thousand Arrows"}) &&
       !field.is_gravity ? *field.is_gravity : false && defender.HasItem({"Air Balloon"})) 
   {
      desc.defender_item = defender.GetItem();
      return result;
   }

   if (move.GetPriority() > 0 && 
       field.HasTerrain({ENUMS::Terrain::Psychic_t}) && 
       CalcUtil::IsGrounded(defender, field)) 
   {
      desc.terrain = field.terrain;
      return result;
   }

   bool weight_based_move = move.Named({"Heat Crash", "Heavy Slam", "Low Kick", "Grass Knot"});
   if (defender.GetIsDynamaxed() && *defender.GetIsDynamaxed() && weight_based_move) 
   {
      return result;
   }

   desc.hp_evs = CalcUtil::GetStatDescriptionText(gen, defender, ENUMS::StatID::hp);

   int fixed_damage = CalcUtil::HandleFixedDamageMoves(attacker, move);
   if (fixed_damage) 
   {
      if (attacker.HasAbility({"Parental Bond"})) 
      {
         result.SetDamage(std::make_pair(fixed_damage, fixed_damage));
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

   if (move.Named({"Guardian of Alola"})) 
   {
      int z_lost_hp = std::floor((defender.CurHP() * 3) / 4);
      if (field.defender_side.is_protected && 
          attacker.GetItem() && 
          attacker.GetItem().value().find(" Z") != std::string::npos) 
      {
         z_lost_hp = std::ceil(z_lost_hp / 4 - 0.5);
      }
      result.SetDamage(z_lost_hp);
      return result;
   }

   if (move.Named({"Nature\'s Madness"})) 
   {
      int lost_hp = field.defender_side.is_protected ? 0 : std::floor(defender.CurHP() / 2);
      result.SetDamage(lost_hp);
      return result;
   }

   if (move.Named({"Spectral Thief"})) 
   {
      for (const auto& [stat, num] : defender.GetBoosts()) 
      {
         if (num > 0) 
         {
            attacker.SetBoost(stat, attacker.GetBoosts().at(stat) + 
                                     attacker.HasAbility({"Contrary"}) ? -num : num);
            if (attacker.GetBoosts().at(stat) > 6) attacker.SetBoost(stat, 6);
            if (attacker.GetBoosts().at(stat) < -6) attacker.SetBoost(stat, -6);
            attacker.SetStat(stat, CalcUtil::GetModifiedStat
            (
               attacker.GetRawStats().at(stat), 
               attacker.GetBoosts().at(stat)
            ));
            defender.SetBoost(stat, 0);
            defender.SetStat(stat, defender.GetRawStats().at(stat));
         }
      }
   }

   if (move.GetHits() > 1) 
   {
      desc.hits = move.GetHits();
   }

   std::string turn_order = attacker.GetStats().at(ENUMS::StatID::spe) > 
                            defender.GetStats().at(ENUMS::StatID::spe) 
                            ? "first" 
                            : "last";

   // #endregion
   // #region Base Power

   int base_power = CalculateBasePowerSMSSSV
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
   int attack = CalculateAttackSMSSSV(gen, attacker, defender, move, field, desc, is_critical);
   ENUMS::StatID attack_stat =
      move.Named({"Shell Side Arm"}) &&
      CalcUtil::GetShellSideArmCategory(attacker, defender) == ENUMS::MoveCategory::Physical
         ? ENUMS::StatID::atk
         : move.Named({"Body Press"})
         ? ENUMS::StatID::def
         : move.GetMoveCategory() == ENUMS::MoveCategory::Special
            ? ENUMS::StatID::spa
            : ENUMS::StatID::atk;
   // #endregion
   // #region (Special) Defense

   int defense = CalculateDefenseSMSSSV(gen, attacker, defender, move, field, desc, is_critical);
   bool hits_physical = move.GetOverrideDefensiveStat() &&
      Stats::ConvertStatID(*move.GetOverrideDefensiveStat()) == ENUMS::StatID::def || 
      move.GetMoveCategory() == ENUMS::MoveCategory::Physical ||
      (move.Named({"Shell Side Arm"}) && 
      CalcUtil::GetShellSideArmCategory(attacker, defender) == ENUMS::MoveCategory::Physical);
   ENUMS::StatID defense_stat = hits_physical ? ENUMS::StatID::def : ENUMS::StatID::spd;

   // #endregion
   // #region Damage

   int base_damage = CalculateBaseDamageSMSSSV
   (
      gen,
      attacker,
      defender,
      base_power,
      attack,
      defense,
      move,
      field,
      desc,
      is_critical
   );

   if (HasTerrainSeed(defender) &&
       field.HasTerrain({*Data::Items::Instance().GetTerrainFromSeed(*defender.GetItem())}) &&
       Data::Items::Instance().GetSeedBoostedStat(*defender.GetItem()) == defense_stat) 
   {
      // Last condition applies so the calc doesn't show a seed where it wouldn't affect the outcome
      // (like Grassy Seed when being hit by a special move)
      desc.defender_item = defender.GetItem();
   }

   // the random factor is applied between the crit mod and the stab mod, so don"t apply anything
   // below this until we"re inside the loop
   int pre_stellar_stab_mod = CalcUtil::GetStabMod(attacker, move, desc);
   int stab_mod = CalcUtil::GetStellarStabMod(attacker, move, pre_stellar_stab_mod);

   bool apply_burn =
      attacker.HasStatus({ENUMS::StatusName::brn}) &&
      move.GetMoveCategory() == ENUMS::MoveCategory::Physical &&
      !attacker.HasAbility({"Guts"}) &&
      !move.Named({"Facade"});
   desc.is_burned = apply_burn;
   std::vector<int> final_mods = CalculateFinalModsSMSSSV
   (
      gen,
      attacker,
      defender,
      move,
      field,
      desc,
      is_critical,
      type_eff
   );

   bool protect = false;
   if (field.defender_side.is_protected &&
      (attacker.GetIsDynamaxed() || 
       (move.GetIsZ() && 
        attacker.GetItem() && 
        attacker.GetItem().value().find(" Z") != std::string::npos))) 
   {
      protect = true;
      desc.is_protected = true;
   }

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
      child_damage = CalculateSMSSSV(gen, child, defender, move, field).GetDamage();
      desc.attacker_ability = attacker.GetAbility();
      child_damage_q = true;
   }

   std::vector<int> damage_out{};
   for (int i = 0; i < 16; i++) 
   {
      damage_out.push_back
      (
         CalcUtil::GetFinalDamage
         (
            base_damage, 
            i, 
            type_eff, 
            apply_burn, 
            stab_mod, 
            final_mod, 
            protect
         )
      );
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

         int new_attack = CalculateAttackSMSSSV
         (
            gen, 
            attacker, 
            defender, 
            move,
            field, 
            desc, 
            is_critical
         );

         int new_defense = CalculateDefenseSMSSSV
         (
            gen, 
            attacker, 
            defender, 
            move,
            field, 
            desc, 
            is_critical
         );

         // Check if lost -ate ability. Typing stays the same, only boost is lost
         // Cannot be regained during multihit move and no Normal moves with stat drawbacks
         has_ate_ability_type_change = has_ate_ability_type_change &&
                                       attacker.HasAbility
                                       ({
                                          "Aerilate", 
                                          "Galvanize", 
                                          "Pixilate", 
                                          "Refrigerate", 
                                          "Normalize"
                                       });

         if ((move.GetDropsStats() && move.GetTimesUsed() > 1)) 
         {
            // Adaptability does not change between hits of a multihit, only between turns
            pre_stellar_stab_mod = CalcUtil::GetStabMod(attacker, move, desc);
            // Hack to make Tera Shell with multihit moves, but not over multiple turns
            type_eff = turn2type_eff;
            // Stellar damage boost applies for 1 turn, but all hits of multihit.
            stab_mod = CalcUtil::GetStellarStabMod(attacker, move, pre_stellar_stab_mod, times);
         }

         int new_base_power = CalculateBasePowerSMSSSV
         (
            gen,
            attacker,
            defender,
            move,
            field,
            has_ate_ability_type_change,
            desc,
            times + 1
         );

         int new_base_damage = CalculateBaseDamageSMSSSV
         (
            gen,
            attacker,
            defender,
            new_base_power,
            new_attack,
            new_defense,
            move,
            field,
            desc,
            is_critical
         );

         std::vector<int> new_final_mods = CalculateFinalModsSMSSSV
         (
            gen,
            attacker,
            defender,
            move,
            field,
            desc,
            is_critical,
            type_eff,
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

