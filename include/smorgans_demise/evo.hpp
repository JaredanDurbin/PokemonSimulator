#ifndef SMORGANS_DEMISE_EVO_HPP
#define SMORGANS_DEMISE_EVO_HPP

// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include <memory>

#include "./data_loader.hpp"
#include "./../mechanics/mechanics.hpp"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Namespace block.
// ----------------------------------------------------------------------------
using namespace PokemonDamageCalcCPP;

namespace SmorgansDemise
{

class EffortValueOptimizer
{
private:
   const std::unique_ptr<DataLoader> data = std::make_unique<DataLoader>("./input/evo/");

   std::vector<Pokemon::Pokemon> opt_atk = data->GetTeam("attack");
   std::vector<Pokemon::Pokemon> opt_def = data->GetTeam("defense");
   std::vector<Pokemon::Pokemon> threats = data->GetTeam("threat");

   const std::function
   <
      Result::Result
      (
         const ENUMS::GenerationNumber,
         Pokemon::Pokemon,
         Pokemon::Pokemon,
         Move::Move,
         State::Field
      )
   >  f = Mechanics::GetMechanics(data->GetGeneration());

   std::pair<bool, bool> DeterminePhysOrSpecAtker(const Pokemon::Pokemon& pokemon) const;
   std::pair<int, int> DeterminePhysOrSpecThreats() const;

   std::set<int> GetThreatsSpeeds() const;
   std::pair<std::set<int>, std::set<int>> GetThreatsDefenses() const;
   int OptimizeSpeed(Pokemon::Pokemon& pokemon, const std::set<int>& speeds, int evs_left = 252);
   int OptimizeAttack
   (
      Pokemon::Pokemon& pokemon, 
      const std::pair<std::set<int>, std::set<int>>& defenses,
      int evs_left
   );
   int OptimizeDefenses(Pokemon::Pokemon& pokemon, int evs_left);
   int OptimizeHP(Pokemon::Pokemon& pokemon, int evs_left, bool attacker = true);
   
   void OptimizeAttackers();
   void OptimizeDefenders();

public:
   EffortValueOptimizer();

   inline const std::vector<Pokemon::Pokemon>& GetOptAtk() const { return opt_atk; };
   inline const std::vector<Pokemon::Pokemon>& GetOptDef() const { return opt_def; };
};

}

#endif
