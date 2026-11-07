#ifndef SMORGANS_DEMISE_DATA_LOADER_HPP
#define SMORGANS_DEMISE_DATA_LOADER_HPP

// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include <map>
#include <memory>
#include <string>

#include "./../util/csv_parser.hpp"
#include "./../pokemon.hpp"
#include "./../state.hpp"
#include "./../result.hpp"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Namespace block.
// ----------------------------------------------------------------------------
using namespace PokemonDamageCalcCPP;

namespace SmorgansDemise
{

using Versus 
   = std::map<std::string, 
     std::map<std::string, 
     std::map<std::string, std::unique_ptr<Result::Result>>>>;

class DataLoader
{
private:
   std::string top_directory = "";

   Util::CSV::CSVLoader pokemon_csv = Util::CSV::CSVLoader(top_directory + "pokemon.csv");
   Util::CSV::CSVLoader sides_csv = Util::CSV::CSVLoader(top_directory + "sides.csv");
   Util::CSV::CSVLoader field_csv = Util::CSV::CSVLoader(top_directory + "field.csv");

   ENUMS::GenerationNumber g = ENUMS::GenerationNumber::__9;

   std::map<std::string, std::vector<Pokemon::Pokemon>> teams{};
   std::map<std::pair<std::string, std::string>, State::Field> fields{};

   bool FindFieldIDAndCreateField
   (
      std::map<std::pair<std::string, std::string>, 
                         std::pair<State::Side, State::Side>>& sides_in,
      const Util::CSV::CSVLine& id_in                 
   );
public:
   DataLoader(const std::string dir);

   const std::vector<Pokemon::Pokemon> GetTeam(const std::string& team) const;
   inline const std::map<std::pair<std::string, std::string>, State::Field>& GetFields() const
   { return fields; };
   inline ENUMS::GenerationNumber GetGeneration() const { return g; };
};

}

#endif
