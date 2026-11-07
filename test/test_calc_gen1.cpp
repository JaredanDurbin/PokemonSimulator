#include <iostream>

#include "./../include/mechanics/gen12.hpp"

using namespace PokemonDamageCalcCPP;

int main()
{
   auto g = ENUMS::GenerationNumber::__2;

   State::Pokemon _pokemon1 = 
   {
      .name = "Farfetch\'d",
      .moves = std::vector<std::string>
      {
         "Slash", 
         "Sand Attack",
         "Substitute",
         "Agility"
      }
   };

   State::Pokemon _pokemon2 = 
   {
      .name = "Omanyte",
      .moves = std::vector<std::string>
      {
         "Surf", 
         "Blizzard",
         "Body Slam",
         "Rest"
      }
   };

   auto pokemon1 = Pokemon::Pokemon(g, "Farfetch\'d", _pokemon1);
   auto pokemon2 = Pokemon::Pokemon(g, "Omanyte", _pokemon2);
   auto m = Move::Move(g, "Slash");
   State::Field f = {.game_type = ENUMS::GameType::Singles};

   auto result = Mechanics::GEN12::CalculateRBYGSC(g, pokemon1, pokemon2, m, f);

   std::cout << result.FullDescription();

   return 0;
}



