// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include "./../include/smorgans_demise/data_loader.hpp"

#include <iostream>

#include "./../include/util/csv_util.h"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Namespace block.
// ----------------------------------------------------------------------------
using namespace PokemonDamageCalcCPP;

namespace SmorgansDemise
{

bool DataLoader::FindFieldIDAndCreateField
(
   std::map<std::pair<std::string, std::string>, 
                      std::pair<State::Side, State::Side>>& sides_in,
   const Util::CSV::CSVLine& line_in                 
)
{
   for (auto it = sides_in.begin(); it != sides_in.end();)
   {
      if (it->first.second == line_in[0])
      {
         fields[std::make_pair(it->first.second, it->first.first)]
            = State::ConstructField(line_in, it->second.first, it->second.second);
         
         it = sides_in.erase(it);
         
         return true;
      }
      else
      {
         ++it;
      }
   }

   return false;
}

DataLoader::DataLoader(const std::string dir)
: top_directory(dir)
{
   g = Util::CSV::StringToGeneration(pokemon_csv.GetRowColumnEntry(1, 1));

   for (int i = 1; i < pokemon_csv.GetNumRows(); i++)
   {
      const auto& line = pokemon_csv.GetLineAtRow(i);
      State::Pokemon temp_state_pokemon = State::ConstructPokemon(line);
      Pokemon::Pokemon temp_pokemon(g, line.at(2), temp_state_pokemon);
      if (teams.find(line.at(0)) != teams.end())
      {
         teams[line.at(0)].push_back(temp_pokemon);
      }
      else
      {
         teams[line.at(0)] = std::vector<Pokemon::Pokemon>{temp_pokemon}; 
      }
   }

   // The first pair is the side id and associated field id.
   // In the second pair the attacker is always first in the pair.
   std::map<std::pair<std::string, std::string>, 
            std::pair<State::Side, State::Side>> sides{};
   for (int i = 1; i < sides_csv.GetNumRows(); i++)
   {
      const auto& line = sides_csv.GetLineAtRow(i);
      const auto ids = std::make_pair(line[0], line[1]);

      if (line[2] == "attacker" && sides.find(ids) == sides.end())
      {
         State::Side temp;
         sides[ids] = std::make_pair(State::ConstructSide(line), temp);
      }
      else if (line[2] == "attacker")
      {
         sides[ids].first = State::ConstructSide(line);
      }
      else if (line[2] == "defender" && sides.find(ids) == sides.end())
      {
         State::Side temp;
         sides[ids] = std::make_pair(temp, State::ConstructSide(line));
      }
      else if (line[2] == "defender")
      {
         sides[ids].second = State::ConstructSide(line);
      }
      else
      {
         std::cerr << "Neither 'attacker' nor 'defender' was specified in 'sides.csv'.\n";
      }
   }

   for (int i = 1; i < field_csv.GetNumRows(); i++)
   {
      const auto& line = field_csv.GetLineAtRow(i);

      while (FindFieldIDAndCreateField(sides, line)) {}
   }
}

const std::vector<Pokemon::Pokemon> DataLoader::GetTeam(const std::string& team) const
{
   if (teams.find(team) != teams.end())
   {
      return teams.at(team);
   }

   return {};
}

};



