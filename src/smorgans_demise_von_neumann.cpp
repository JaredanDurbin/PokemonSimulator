// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include "./../include/smorgans_demise/von_neumann.hpp"

#include <iostream>

#include "./../include/mechanics/mechanics.hpp"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Namespace block.
// ----------------------------------------------------------------------------
using namespace PokemonDamageCalcCPP;

namespace SmorgansDemise
{

VonNeumann::VonNeumann()
{
   // DEBUG
   //std::cout << "Within VonNeumann!!!!!\n";

   const std::vector<Pokemon::Pokemon>& team1 = data->GetTeam("team-1");
   const std::vector<Pokemon::Pokemon>& team2 = data->GetTeam("team-2");

   const auto f = Mechanics::GetMechanics(data->GetGeneration());

   // DEBUG
   //std::cout << "DEBUG: " << "Get mechanics work?\n";

   for (const Pokemon::Pokemon& p1 : team1)
   {
      for (const Pokemon::Pokemon& p2 : team2)
      {
         for (const std::string& m : p1.GetMoves())
         {
            auto move = Move::Move(data->GetGeneration(), m);
            team1_vs_team2[p1.GetName()][p2.GetName()][m] 
               = std::make_unique<Result::Result>
               (
                  f(data->GetGeneration(), p1, p2, move, data->GetFields().at
                  (
                     std::make_pair("f1", "s1")
                  ))
               );
         }
      }
   }

   for (const Pokemon::Pokemon& p2 : team2)
   {
      for (const Pokemon::Pokemon& p1 : team1)
      {
         for (const std::string& m : p2.GetMoves())
         {
            auto move = Move::Move(data->GetGeneration(), m);
            team2_vs_team1[p2.GetName()][p1.GetName()][m] 
               = std::make_unique<Result::Result>
               (
                  f(data->GetGeneration(), p2, p1, move, data->GetFields().at
                  (
                     std::make_pair("f1", "s1")
                  ))
               );
         }
      }
   }

   TurnMatrix temp(team1_vs_team2, team2_vs_team1);
   matrix = temp;
}

}

