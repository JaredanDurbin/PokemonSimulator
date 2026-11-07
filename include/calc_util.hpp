#ifndef POKEMON_DAMAGE_CALC_CPP_CALC_UTIL_HPP
#define POKEMON_DAMAGE_CALC_CPP_CALC_UTIL_HPP

#include <cmath>

#include "./enums.h"
#include "./pokemon.hpp"
#include "./stats.hpp"
#include "./move.hpp"
#include "./util/util.h"
#include "./data/natures.h"
#include "./description.hpp"

namespace PokemonDamageCalcCPP
{
namespace CalcUtil
{

const std::vector<std::string> EV_ITEMS = 
{
  "Macho Brace",
  "Power Anklet",
  "Power Band",
  "Power Belt",
  "Power Bracer",
  "Power Lens",
  "Power Weight",
};

// 16-bit Overflow
inline int OF16(int n) { return n > 65535 ? n % 65536 : n; }
// 32-bit Overflow
inline int OF32(int n) { return n > 4294967295 ? n % 4294967296 : n; }
// Game Freak rounds DOWN on .5
inline int PokeRound(float num) 
{ return std::fmod(num, 1) > 0.5 ? std::ceil(num) : std::floor(num); }

int GetModifiedStat
(
   const int stat, 
   const int mod, 
   const std::optional<ENUMS::GenerationNumber> gen = std::nullopt
);

bool IsQPActive
(
   const Pokemon::Pokemon pokemon,
   const State::Field field
);

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
);

int ChainMods(std::vector<int> mods, int lower_bound, int upper_bound);

int GetFinalSpeed
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& pokemon,
   const State::Field& field,
   const State::Side& side
);

void ComputeFinalStats
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon& attacker,
   Pokemon::Pokemon& defender,
   State::Field& field,
   std::vector<ENUMS::StatID> stats
);

int HandleFixedDamageMoves(const Pokemon::Pokemon attacker, const Move::Move move);

float GetMoveEffectiveness
(
   const ENUMS::GenerationNumber gen,
   const Move::Move& move,
   const ENUMS::TypeName type,
   bool is_ghost_revealed = false,
   bool is_gravity = false,
   bool is_ring_target = false
);

std::string GetStatDescriptionText
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& pokemon,
   const ENUMS::StatID stat,
   const std::optional<ENUMS::NatureName> nature_name = std::nullopt
);

void CheckAirLock(const Pokemon::Pokemon& pokemon, State::Field& field);

void CheckForecast
(
   Pokemon::Pokemon& pokemon, 
   std::optional<ENUMS::Weather> weather = std::nullopt
);

void CheckIntimidate
(
   const ENUMS::GenerationNumber gen, 
   const Pokemon::Pokemon& source, 
   Pokemon::Pokemon& target
);

// NOTE: We only need to handle guaranteed, damage-relevant boosts here for multi-hit accuracy
std::pair<bool, bool> CheckMultihitBoost
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon& attacker,
   Pokemon::Pokemon& defender,
   const Move::Move& move,
   State::Field& field,
   Description::RawDescription& desc,
   bool attacker_used_item = false,
   bool defender_used_item = false
);

void CheckItem(Pokemon::Pokemon& pokemon, bool magic_room_active = false);

void CheckDownload
(
   Pokemon::Pokemon& source, 
   Pokemon::Pokemon& target, 
   bool wonder_room_active = false
);

int CountBoosts(const ENUMS::GenerationNumber gen, const ENUMS::StatsTable& boosts);
void CheckWonderRoom(Pokemon::Pokemon& pokemon, bool wonder_room_active = false);
void CheckSeedBoost(Pokemon::Pokemon& pokemon, const State::Field& field);
void CheckInfiltrator(const Pokemon::Pokemon& pokemon, State::Side& affected_side);
bool IsGrounded(const Pokemon::Pokemon& pokemon, const State::Field& field);
float GetWeight(const Pokemon::Pokemon& pokemon, Description::RawDescription& desc, bool role);
int GetBaseDamage(const int level, const int base_power, const int attack, const int defense);

int GetStabMod
(
   const Pokemon::Pokemon& pokemon, 
   const Move::Move& move, 
   Description::RawDescription& desc
);

int GetFinalDamage
(
   const int base_amount,
   const int i,
   const float effectiveness,
   bool is_burned,
   const int stab_mod,
   const int final_mod,
   bool protect = false
);

void CheckTeraformZero(const Pokemon::Pokemon& pokemon, State::Field& field);
void CheckIntrepidSword(Pokemon::Pokemon& source, const ENUMS::GenerationNumber gen);
void CheckDauntlessShield(Pokemon::Pokemon& source, const ENUMS::GenerationNumber gen);
void CheckWindRider(Pokemon::Pokemon& source, const State::Side& attacking_side);
void CheckEmbody(Pokemon::Pokemon& source, const ENUMS::GenerationNumber gen);
void CheckInfiltrator(const Pokemon::Pokemon& pokemon, State::Side& affected_side);

ENUMS::MoveCategory GetShellSideArmCategory
(
   const Pokemon::Pokemon& source, 
   const Pokemon::Pokemon& target
);

int GetStellarStabMod
(
   const Pokemon::Pokemon& pokemon, 
   const Move::Move& move, 
   int stab_mod = 1, 
   int turns = 0
);

}
}

#endif
