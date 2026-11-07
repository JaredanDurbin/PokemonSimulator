#ifndef SMORGANS_DEMISE_VON_NEUMANN_HPP
#define SMORGANS_DEMISE_VON_NEUMANN_HPP

// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include <memory>

#include "./data_loader.hpp"
#include "./turn_matrix.hpp"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Namespace block.
// ----------------------------------------------------------------------------
using namespace PokemonDamageCalcCPP;

namespace SmorgansDemise
{

class VonNeumann
{
private:
   std::unique_ptr<DataLoader> data = std::make_unique<DataLoader>("./input/von_neumann/");

   Versus team1_vs_team2{};
   Versus team2_vs_team1{};
   TurnMatrix matrix;

public:
   VonNeumann();

   inline const DataLoader& GetData() const { return *data; };
   inline const std::pair<const Versus&, const Versus&> GetVersuses() const 
   { return {team1_vs_team2, team2_vs_team1}; };
   inline const TurnMatrix& GetTurnMatrix() const { return matrix; };
};

}

#endif
