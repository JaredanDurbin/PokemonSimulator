#ifndef SMORGANS_DEMISE_TURN_MATRIX_HPP
#define SMORGANS_DEMISE_TURN_MATRIX_HPP

// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include <memory>

#include "./../result.hpp"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Namespace block.
// ----------------------------------------------------------------------------
using namespace PokemonDamageCalcCPP;

namespace SmorgansDemise
{

class TurnMatrix
{
private:
   // Attacking team or main team.
   std::vector<std::string> row_titles{};
   // Defending team or main team.
   std::vector<std::string> column_titles{};
   // The main matrix.
   // Row then column for the numbers. And this is the utility value.
   // So attacking team then defending team.
   std::vector<std::vector<std::pair<float, float>>> matrix{};

   void AppendRows
   (
      std::vector<std::vector<std::pair<float, float>>>& dst,
      const std::vector<std::vector<std::pair<float, float>>>& src
   );

   void AddRows
   (
    std::vector<std::vector<std::pair<float, float>>>& dst,
    const std::vector<std::vector<std::pair<float, float>>>& src
   );

public:
   TurnMatrix() {};

   TurnMatrix
   (
      const std::map<std::string, 
      std::map<std::string, 
      std::map<std::string, std::unique_ptr<Result::Result>>>>& team1_in,
      const std::map<std::string, 
      std::map<std::string, 
      std::map<std::string, std::unique_ptr<Result::Result>>>>& team2_in
   );

   std::string ToString() const;
   void ToCSV() const;
};

}

#endif
