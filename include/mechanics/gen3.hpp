#ifndef POKEMON_DAMAGE_CALC_CPP_MECHANICS_GEN3_HPP
#define POKEMON_DAMAGE_CALC_CPP_MECHANICS_GEN3_HPP

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
);

int CalculateDefenseADV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   Description::RawDescription& desc,
   bool is_critical = false
);

int CalculateAttackADV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   Description::RawDescription& desc,
   bool is_critical = false
);  

void CalculateBPModsADV
(
   const Pokemon::Pokemon& attacker,
   const Move::Move& move,
   Description::RawDescription& desc,
   int& base_power
);

int CalculateBasePowerADV
(
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   Move::Move& move,
   Description::RawDescription& desc,
   int hit = 1
);

Result::Result CalculateADV
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
