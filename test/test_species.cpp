#include "./../include/data/species.h"

int main()
{
   auto inst = PokemonDamageCalcCPP::Data::Species::Instance().GetSpeciesIDsByGeneration(3);

   return 0;
}



