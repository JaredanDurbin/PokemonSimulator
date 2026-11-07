#include "./../include/data/items.h"

int main()
{
   auto inst = PokemonDamageCalcCPP::Data::Items::Instance().GetItemsByGeneration(3);

   return 0;
}



