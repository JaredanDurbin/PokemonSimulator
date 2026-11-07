#include "./../include/data/abilities.h"

int main()
{
   auto inst = PokemonDamageCalcCPP::Data::Abilities::Instance().GetAbilitiesByGeneration(3);

   return 0;
}



