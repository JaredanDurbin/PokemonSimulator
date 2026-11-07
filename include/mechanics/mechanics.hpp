#ifndef POKEMON_DAMAGE_CALC_CPP_MECHANICS_MECHANICS_HPP
#define POKEMON_DAMAGE_CALC_CPP_MECHANICS_MECHANICS_HPP

#include <functional>

#include "./../result.hpp"

namespace PokemonDamageCalcCPP
{
namespace Mechanics
{

std::function
<
   Result::Result
   (
      const ENUMS::GenerationNumber,
      Pokemon::Pokemon,
      Pokemon::Pokemon,
      Move::Move,
      State::Field
   )
> 
GetMechanics(const ENUMS::GenerationNumber gen);

}
}

#endif
