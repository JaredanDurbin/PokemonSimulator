#ifndef POKEMON_DAMAGE_CALC_CPP_STATE_HPP
#define POKEMON_DAMAGE_CALC_CPP_STATE_HPP

#include <vector>

#include "enums.h"
#include "util/csv_parser.hpp"
#include "data/moves.h"
#include "data/species.h"

namespace PokemonDamageCalcCPP
{
namespace State 
{
struct Pokemon 
{
   std::optional<std::string> name = std::nullopt;
   std::optional<int> level = std::nullopt;
   std::optional<std::string> ability = std::nullopt;
   std::optional<bool> ability_on = std::nullopt;
   std::optional<bool> is_dynamaxed = std::nullopt;
   std::optional<int> dynamax_level = std::nullopt;
   std::optional<bool> is_salt_cure = std::nullopt;
   std::optional<int> allies_fainted = std::nullopt;
   std::optional<ENUMS::StatIDExceptHP> boosted_stat = std::nullopt;
   std::optional<std::string> item = std::nullopt;
   std::optional<ENUMS::GenderName> gender = std::nullopt;
   std::optional<ENUMS::NatureName> nature = std::nullopt;
   std::optional<ENUMS::StatsTable> ivs = std::nullopt;
   std::optional<ENUMS::StatsTable> evs = std::nullopt;
   std::optional<ENUMS::StatsTable> boosts = std::nullopt;
   std::optional<int> original_cur_hp = std::nullopt;
   std::optional<int> cur_hp = std::nullopt;
   std::optional<ENUMS::StatusName> status = std::nullopt;
   std::optional<ENUMS::TypeName> tera_type = std::nullopt;
   std::optional<int> toxic_counter = std::nullopt;
   std::optional<std::vector<std::string>> moves = std::nullopt;
   std::optional<Data::Specie> overrides = std::nullopt;
};

struct Move 
{
   std::optional<std::string> name = std::nullopt;
   std::optional<bool> use_z = std::nullopt;
   std::optional<bool> use_max = std::nullopt;
   std::optional<bool> is_crit = std::nullopt;
   std::optional<bool> is_stellar_first_use = std::nullopt;
   std::optional<int> hits = std::nullopt;
   std::optional<int> times_used = std::nullopt;
   std::optional<int> times_used_with_metronome = std::nullopt;
   std::optional<Data::Move> overrides = std::nullopt;
   // Used in moves.cpp
   std::optional<std::string> species = std::nullopt;
   std::optional<std::string> ability = std::nullopt;
   std::optional<std::string> item = std::nullopt;
};

struct Side 
{
   std::optional<int> spikes = std::nullopt;
   std::optional<bool> steelsurge = std::nullopt;
   std::optional<bool> vinelash = std::nullopt;
   std::optional<bool> wildfire = std::nullopt;
   std::optional<bool> cannonade = std::nullopt;
   std::optional<bool> volcalith = std::nullopt;
   std::optional<bool> is_sr = std::nullopt;
   std::optional<bool> is_reflect = std::nullopt;
   std::optional<bool> is_light_screen = std::nullopt;
   std::optional<bool> is_protected = std::nullopt;
   std::optional<bool> is_seeded = std::nullopt;
   std::optional<bool> is_foresight = std::nullopt;
   std::optional<bool> is_tailwind = std::nullopt;
   std::optional<bool> is_helping_hand = std::nullopt;
   std::optional<bool> is_flower_gift = std::nullopt;
   std::optional<bool> is_friend_guard = std::nullopt;
   std::optional<bool> is_aurora_veil = std::nullopt;
   std::optional<bool> is_battery = std::nullopt;
   std::optional<bool> is_power_spot = std::nullopt;
   std::optional<ENUMS::Switching> is_switching = std::nullopt;
};

struct Field 
{
   ENUMS::GameType game_type = ENUMS::GameType::Singles;
   std::optional<ENUMS::Weather> weather = std::nullopt;
   std::optional<ENUMS::Terrain> terrain = std::nullopt;
   std::optional<bool> is_magic_room = std::nullopt;
   std::optional<bool> is_wonder_room = std::nullopt;
   std::optional<bool> is_gravity = std::nullopt;
   std::optional<bool> is_aura_break = std::nullopt;
   std::optional<bool> is_fairy_aura = std::nullopt;
   std::optional<bool> is_dark_aura = std::nullopt;
   std::optional<bool> is_beads_of_ruin = std::nullopt;
   std::optional<bool> is_sword_of_ruin = std::nullopt;
   std::optional<bool> is_tablets_of_ruin = std::nullopt;
   std::optional<bool> is_vessel_of_ruin = std::nullopt;
   Side attacker_side{};
   Side defender_side{};

   inline bool HasWeather(const std::initializer_list<ENUMS::Weather>& weathers) const
   {
      if (!weather) return false;
      return std::find(weathers.begin(), weathers.end(), weather.value()) != weathers.end();
   }

   inline bool HasTerrain(const std::initializer_list<ENUMS::Terrain>& terrains) const
   {
      if (!terrain) return false;
      return std::find(terrains.begin(), terrains.end(), terrain.value()) != terrains.end();
   }
};

Pokemon ConstructPokemon(const Util::CSV::CSVLine& line);
Side ConstructSide(const Util::CSV::CSVLine& line);
Field ConstructField(const Util::CSV::CSVLine& line, const Side& attacker, const Side& defender);
}
}

#endif
