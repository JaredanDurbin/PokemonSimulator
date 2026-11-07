#ifndef POKEMON_DAMAGE_CALC_CPP_MECHANICS_GEN12_HPP
#define POKEMON_DAMAGE_CALC_CPP_MECHANICS_GEN12_HPP

#include "./../result.hpp"
#include "./../enums.h"
#include "./../pokemon.hpp"
#include "./../move.hpp"
#include "./../state.hpp"

namespace PokemonDamageCalcCPP
{
namespace Mechanics
{
namespace GEN12
{

Result::Result CalculateRBYGSC
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
