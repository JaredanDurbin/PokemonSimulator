#ifndef POKEMON_DAMAGE_CALC_CPP_DESCRIPTION_HPP
#define POKEMON_DAMAGE_CALC_CPP_DESCRIPTION_HPP

#include <utility>
#include <variant>
#include <vector>

#include "enums.h"
#include "pokemon.hpp"
#include "move.hpp"
#include "data/moves.h"
#include "data/species.h"

namespace PokemonDamageCalcCPP
{
namespace Description
{

using Damage = std::variant
<
   int,
   std::vector<int>,
   std::pair<int, int>,
   std::pair<std::vector<int>, std::vector<int>>
>;

using DamageRangeResult = std::variant
<
   std::pair<int, int>,
   std::pair<std::pair<int, int>, std::pair<int, int>>
>;

struct KOChanceHelper
{
   std::optional<int> chance;
   int n = 0;
   std::string text = "";
};

const std::set<std::string> TRAPPING = 
{
   "Bind", 
   "Clamp", 
   "Fire Spin", 
   "Infestation", 
   "Magma Storm", 
   "Sand Tomb",
   "Thunder Cage", 
   "Whirlpool", 
   "Wrap", 
   "G-Max Sandblast", 
   "G-Max Centiferno"
};

struct RawDescription
{
   std::optional<std::string> hp_evs = std::nullopt;

   std::optional<int> attack_boost = std::nullopt;
   std::optional<std::string> attack_evs = std::nullopt;
   std::optional<std::string> attacker_ability = std::nullopt;
   std::optional<std::string> attacker_item = std::nullopt;
   std::string attacker_name = "";
   std::optional<std::string> attacker_tera = std::nullopt;

   std::optional<std::string> defender_ability = std::nullopt;
   std::optional<std::string> defender_item = std::nullopt;
   std::string defender_name = "";
   std::optional<std::string> defender_tera = std::nullopt;

   std::optional<int> defense_boost = std::nullopt;
   std::optional<std::string> defense_evs = std::nullopt;

   std::optional<int> hits = std::nullopt;
   std::optional<int> allies_fainted = std::nullopt;

   bool is_stellar_first_use = false;
   bool is_beads_of_ruin = false;
   bool is_sword_of_ruin = false;
   bool is_tablets_of_ruin = false;
   bool is_vessel_of_ruin = false;

   bool is_aurora_veil = false;
   bool is_flower_gift_attacker = false;
   bool is_flower_gift_defender = false;
   bool is_friend_guard = false;
   bool is_helping_hand = false;
   bool is_critical = false;
   bool is_light_screen = false;
   bool is_burned = false;
   bool is_protected = false;
   bool is_reflect = false;
   bool is_battery = false;
   bool is_power_spot = false;
   bool is_wonder_room = false;

   std::optional<std::string> is_switching = std::nullopt; // "out" | "in"

   std::optional<int> move_bp = std::nullopt;
   std::string move_name = "";
   std::optional<std::string> move_turns = std::nullopt;

   std::optional<ENUMS::TypeName> move_type = std::nullopt;

   std::optional<std::string> rivalry = std::nullopt; // "buffed" | "nerfed"

   std::optional<ENUMS::Terrain> terrain = std::nullopt;
   std::optional<ENUMS::Weather> weather = std::nullopt;

   bool is_defender_dynamaxed = false;
};

DamageRangeResult DamageRange(const Damage& damage);

int ToDisplay
(
   const std::string& notation, 
   const int a, 
   const int b, 
   const int f = 1
);

std::pair<std::string, std::string> GetDescriptionLevels
(
   const Pokemon::Pokemon& attacker, 
   const Pokemon::Pokemon& defender
);

std::string BuildDescription
(
   const RawDescription& description,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender
);

std::vector<int> Combine(const Damage& damage);

std::pair<int, std::vector<std::string>> GetHazards
(
   const ENUMS::GenerationNumber& gen,
   const Pokemon::Pokemon& defender,
   const State::Side& defender_side
);

bool IsGrounded(const Pokemon::Pokemon& pokemon, const State::Field& field);

std::pair<int, std::vector<std::string>> GetEndOfTurn
(
   const ENUMS::GenerationNumber& gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field
);

float ComputeKOChance
(
   const std::vector<int>& damage,
   const int hp,
   const int eot,
   const int hits,
   const int times_used,
   const int max_hp,
   const int toxic_counter
);

int PredictTotal
(
   const int damage,
   const int eot,
   const int hits,
   const int times_used,
   const int toxic_counter,
   const int max_hp
);

KOChanceHelper GetKOChance
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   Move::Move& move,
   const State::Field& field,
   const Damage& damage,
   bool err = true
);

std::string Display
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   Move::Move& move,
   const State::Field& field,
   const Damage& damage,
   const RawDescription& raw_description,
   const std::string& notation = "%",
   bool err = true
);

std::pair<std::pair<int, int>, std::string> GetRecovery
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const Description::Damage& damage,
   const std::string& notation = "%"
);

std::pair<std::pair<int, int>, std::string>  GetRecoil
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const Damage& damage,
   const std::string& notation
);

std::string DisplayMove
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const Damage& damage,
   const std::string& notation = "%"
);

}
}

#endif
