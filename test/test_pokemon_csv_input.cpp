#include <iostream>

#include "./../include/mechanics/gen3.hpp"
#include "./../include/csv_parser.hpp"

using namespace PokemonDamageCalcCPP;

int main()
{
   Util::CSV::CSVLoader pokemon("./../input/test/test_pokemon_csv_input.csv");
   Util::CSV::CSVLoader sides("./../input/test/test_side_csv_input.csv");
   Util::CSV::CSVLoader field("./../input/test/test_field_csv_input.csv");

   auto g = ENUMS::GenerationNumber::__3;

   State::Pokemon _pokemon1 = State::ConstructPokemon(pokemon.GetLineAtRow(1));
   State::Pokemon _pokemon2 = State::ConstructPokemon(pokemon.GetLineAtRow(2));

   auto p1 = Pokemon::Pokemon(g, "Farfetch\'d", _pokemon1);
   auto p2 = Pokemon::Pokemon(g, "Omanyte", _pokemon2);
   auto m = Move::Move(g, "Slash");
   
   State::Side a = State::ConstructSide(sides.GetLineAtRow(1));
   State::Side d = State::ConstructSide(sides.GetLineAtRow(2));
   State::Field f = State::ConstructField(field.GetLineAtRow(1), a, d);

   auto result = Mechanics::GEN3::CalculateADV(g, p1, p2, m, f);

   std::cout << result.FullDescription();

   return 0;
}



