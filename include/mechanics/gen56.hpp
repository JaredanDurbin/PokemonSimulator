#ifndef POKEMON_DAMAGE_CALC_CPP_MECHANICS_GEN56_HPP
#define POKEMON_DAMAGE_CALC_CPP_MECHANICS_GEN56_HPP

#include "./../result.hpp"
#include "./../enums.h"
#include "./../pokemon.hpp"
#include "./../move.hpp"
#include "./../state.hpp"

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
);

int CalculateBasePowerBWXY
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon& attacker,
   Pokemon::Pokemon& defender,
   Move::Move& move,
   const State::Field& field,
   bool Has_ate_ability_type_change,
   Description::RawDescription& desc,
   int hit = 1
);

std::vector<int> CalculateAtModsBWXY
(
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc
);

int CalculateAttackBWXY
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical = false
);

std::vector<int> CalculateDfModsBWXY
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& defender,
   const State::Field& field,
   Description::RawDescription& desc,
   bool hits_physical = false
);

int CalculateDefenseBWXY
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical = false
);

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
   bool is_critical = false
);

std::vector<int> CalculateFinalModsBWXY
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   const float type_effectiveness,
   const bool is_critical = false,
   const int hit_count = 0
);

Result::Result CalculateBWXY
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon attacker,
   Pokemon::Pokemon defender,
   Move::Move move,
   State::Field field
);

}
}
}

#endif
