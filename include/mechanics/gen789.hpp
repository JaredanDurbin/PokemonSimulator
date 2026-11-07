#ifndef POKEMON_DAMAGE_CALC_CPP_MECHANICS_GEN789_HPP
#define POKEMON_DAMAGE_CALC_CPP_MECHANICS_GEN789_HPP

#include "./../result.hpp"
#include "./../enums.h"
#include "./../pokemon.hpp"
#include "./../move.hpp"
#include "./../state.hpp"

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
);

int CalculateBasePowerSMSSSV
(
   const ENUMS::GenerationNumber gen,
   Pokemon::Pokemon& attacker,
   Pokemon::Pokemon& defender,
   Move::Move& move,
   const State::Field& field,
   bool has_ate_ability_type_change,
   Description::RawDescription& desc,
   int hit = 1
);

std::vector<int> CalculateAtModsSMSSSV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc
);

int CalculateAttackSMSSSV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical = false
);

std::vector<int> CalculateDfModsSMSSSV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical = false,
   bool hits_physical = false
);

int CalculateDefenseSMSSSV
(
   const ENUMS::GenerationNumber gen,
   const Pokemon::Pokemon& attacker,
   const Pokemon::Pokemon& defender,
   const Move::Move& move,
   const State::Field& field,
   Description::RawDescription& desc,
   bool is_critical = false
);

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
   bool is_critical = false
);

std::vector<int> CalculateFinalModsSMSSSV
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

bool HasTerrainSeed(const Pokemon::Pokemon& pokemon);

Result::Result CalculateSMSSSV
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
