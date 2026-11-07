#include "./../include/mechanics/mechanics.hpp"


#include "./../include/mechanics/gen12.hpp"
#include "./../include/mechanics/gen3.hpp"
#include "./../include/mechanics/gen4.hpp"
#include "./../include/mechanics/gen56.hpp"
#include "./../include/mechanics/gen789.hpp"

namespace PokemonDamageCalcCPP
{
namespace Mechanics
{

std::function
<
   Result::Result
   (
      const ENUMS::GenerationNumber,
      Pokemon::Pokemon,
      Pokemon::Pokemon,
      Move::Move,
      State::Field
   )
> 
GetMechanics(const ENUMS::GenerationNumber gen)
{
   switch (gen)
   {
      case ENUMS::GenerationNumber::__1:
      case ENUMS::GenerationNumber::__2: return GEN12::CalculateRBYGSC;
      case ENUMS::GenerationNumber::__3: return GEN3::CalculateADV;
      case ENUMS::GenerationNumber::__4: return GEN4::CalculateDPP;
      case ENUMS::GenerationNumber::__5:
      case ENUMS::GenerationNumber::__6: return GEN56::CalculateBWXY;
      case ENUMS::GenerationNumber::__7:
      case ENUMS::GenerationNumber::__8:
      case ENUMS::GenerationNumber::__9: return GEN789::CalculateSMSSSV;

   }

   return []
   (
      const ENUMS::GenerationNumber gen,
      Pokemon::Pokemon attacker,
      Pokemon::Pokemon defender,
      Move::Move move,
      State::Field field
   )
   {
      Description::RawDescription desc =
      {
         .attacker_name = attacker.GetName(),
         .defender_name = defender.GetName(),
         .move_name = move.GetName()
      };

      Result::Result result(gen, attacker, defender, move, field, 0, desc);
      return result;
   };
}

}
}

