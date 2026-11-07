#ifndef POKEMON_DAMAGE_CALC_CPP_RESULT_HPP
#define POKEMON_DAMAGE_CALC_CPP_RESULT_HPP

#include <variant>
#include <vector>
#include <utility>

#include "enums.h"
#include "state.hpp"
#include "pokemon.hpp"
#include "move.hpp"
#include "description.hpp"

namespace PokemonDamageCalcCPP
{
namespace Result
{

class Result 
{
private:
   ENUMS::GenerationNumber gen;
   Pokemon::Pokemon attacker;
   Pokemon::Pokemon defender;
   Move::Move move;
   State::Field field;
   Description::Damage damage;
   Description::RawDescription raw_desc;

public:
   Result
   (
      ENUMS::GenerationNumber gen_in,
      Pokemon::Pokemon attacker_in,
      Pokemon::Pokemon defender_in,
      Move::Move move_in,
      State::Field field_in,
      Description::Damage damage_in,
      Description::RawDescription raw_desc_in
   )
   : gen(gen_in)
   , attacker(attacker_in)
   , defender(defender_in)
   , move(move_in)
   , field(field_in)
   , damage(damage_in)
   , raw_desc(raw_desc_in)
   {};

   inline void SetDamage(const int damage_in) { damage = damage_in; };
   inline void SetDamage(const std::vector<int> damage_in) { damage = damage_in; };
   inline void SetDamage(const std::pair<int, int> damage_in) { damage = damage_in; };
   inline void SetDamage(const std::pair<std::vector<int>, std::vector<int>> damage_in) 
   { damage = damage_in; };

   inline Description::Damage GetDamage() { return damage; };
   std::vector<int> GetDamageSpread(const std::string& notation = "%") const;

   std::pair<int, int> Range();
   std::string FullDescription(std::string notation = "%", bool err = true);
   std::string MoveDescription(std::string notation = "%");

   std::pair<std::pair<int, int>, std::string> Recovery(const std::string& notation = "%") const;
   std::pair<std::pair<int, int>, std::string> Recoil(const std::string& notation = "%") const;

   Description::KOChanceHelper KOChance(bool err = true);

   float GetUtility() const;
};


}
}

#endif


