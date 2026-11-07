#ifndef POKEMON_DAMAGE_CALC_CPP_MECHANICS_GEN4_HPP
#define POKEMON_DAMAGE_CALC_CPP_MECHANICS_GEN4_HPP

#include "./../result.hpp"
#include "./../enums.h"
#include "./../pokemon.hpp"
#include "./../move.hpp"
#include "./../state.hpp"
#include "./../description.hpp"

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
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   int hit = 1
);

void CalculateBPModsDPP
(
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   int& base_power
);

int GetSimpleModifiedStat(const int stat, const int mod);

int CalculateAttackDPP
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical = false
);

int CalculateDefenseDPP
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical = false
);

void CalculateFinalModsDPP
(
   int& base_damage,
   const Pokemon::Pokemon& attacker,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical = false
);

Result::Result CalculateDPP
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
