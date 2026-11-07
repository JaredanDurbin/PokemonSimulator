#include "./../include/smorgans_demise/evo.hpp"

#include <iostream>
#include <set>
#include <string>

int main()
{
   SmorgansDemise::EffortValueOptimizer evo;

   std::cout << "\n";

   auto a_pokemons = evo.GetOptAtk();

   for (const auto& pokemon : a_pokemons)
   {
      std::cout << pokemon.GetName() << " speed evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::spe) << "\n";
      std::cout << pokemon.GetName() << " attack evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::atk) << "\n";
      std::cout << pokemon.GetName() << " special attack evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::spa) << "\n";
      std::cout << pokemon.GetName() << " defense evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::def) << "\n";
      std::cout << pokemon.GetName() << " special defense evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::spd) << "\n";
      std::cout << pokemon.GetName() << " hp evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::hp) << "\n";
      std::cout << "\n";
   }

   auto d_pokemons = evo.GetOptDef();

   for (const auto& pokemon : d_pokemons)
   {
      std::cout << pokemon.GetName() << " speed evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::spe) << "\n";
      std::cout << pokemon.GetName() << " attack evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::atk) << "\n";
      std::cout << pokemon.GetName() << " special attack evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::spa) << "\n";
      std::cout << pokemon.GetName() << " defense evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::def) << "\n";
      std::cout << pokemon.GetName() << " special defense evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::spd) << "\n";
      std::cout << pokemon.GetName() << " hp evs: " 
                << pokemon.GetEVs().at(ENUMS::StatID::hp) << "\n";
      std::cout << "\n";
   }

   return 0;
}

