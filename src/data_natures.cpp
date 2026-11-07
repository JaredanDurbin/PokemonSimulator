#include "./../include/data/natures.h"

#include <set>
#include <string>

#include "./../include/enums.h"
#include "./../include/util/util.h"

namespace PokemonDamageCalcCPP
{
namespace Data
{
const std::map<std::string, 
               std::pair<ENUMS::StatIDExceptHP, 
                         ENUMS::StatIDExceptHP>> Natures::NATURES = 
{
   {"Adamant", {std::make_pair<ENUMS::StatIDExceptHP, 
                               ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::atk, 
                                                      ENUMS::StatIDExceptHP::spa)}},
   {"Bashful", {std::make_pair<ENUMS::StatIDExceptHP, 
                               ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spa, 
                                                      ENUMS::StatIDExceptHP::spa)}},
   {"Bold", {std::make_pair<ENUMS::StatIDExceptHP, 
                            ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::def, 
                                                   ENUMS::StatIDExceptHP::atk)}},
   {"Brave", {std::make_pair<ENUMS::StatIDExceptHP, 
                             ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::atk, 
                                                    ENUMS::StatIDExceptHP::spe)}},
   {"Calm", {std::make_pair<ENUMS::StatIDExceptHP, 
                            ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spd, 
                                                   ENUMS::StatIDExceptHP::atk)}},
   {"Careful", {std::make_pair<ENUMS::StatIDExceptHP, 
                               ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spd, 
                                                      ENUMS::StatIDExceptHP::spa)}},
   {"Docile", {std::make_pair<ENUMS::StatIDExceptHP, 
                              ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::def, 
                                                     ENUMS::StatIDExceptHP::def)}},
   {"Gentle", {std::make_pair<ENUMS::StatIDExceptHP, 
                              ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spd, 
                                                     ENUMS::StatIDExceptHP::def)}},
   {"Hardy", {std::make_pair<ENUMS::StatIDExceptHP, 
                             ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::atk, 
                                                    ENUMS::StatIDExceptHP::atk)}},
   {"Hasty", {std::make_pair<ENUMS::StatIDExceptHP, 
                             ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spe, 
                                                    ENUMS::StatIDExceptHP::def)}},
   {"Impish", {std::make_pair<ENUMS::StatIDExceptHP, 
                              ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::def, 
                                                     ENUMS::StatIDExceptHP::spa)}},
   {"Jolly", {std::make_pair<ENUMS::StatIDExceptHP, 
                             ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spe, 
                                                    ENUMS::StatIDExceptHP::spa)}},
   {"Lax", {std::make_pair<ENUMS::StatIDExceptHP, 
                           ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::def, 
                                                  ENUMS::StatIDExceptHP::spd)}},
   {"Lonely", {std::make_pair<ENUMS::StatIDExceptHP, 
                              ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::atk, 
                                                     ENUMS::StatIDExceptHP::def)}},
   {"Mild", {std::make_pair<ENUMS::StatIDExceptHP, 
                            ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spa, 
                                                   ENUMS::StatIDExceptHP::def)}},
   {"Modest", {std::make_pair<ENUMS::StatIDExceptHP, 
                              ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spa, 
                                                     ENUMS::StatIDExceptHP::atk)}},
   {"Naive", {std::make_pair<ENUMS::StatIDExceptHP, 
                             ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spe, 
                                                    ENUMS::StatIDExceptHP::spd)}},
   {"Naughty", {std::make_pair<ENUMS::StatIDExceptHP, 
                               ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::atk, 
                                                      ENUMS::StatIDExceptHP::spd)}},
   {"Quiet", {std::make_pair<ENUMS::StatIDExceptHP, 
                             ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spa, 
                                                    ENUMS::StatIDExceptHP::spe)}},
   {"Quirky", {std::make_pair<ENUMS::StatIDExceptHP, 
                              ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spd, 
                                                     ENUMS::StatIDExceptHP::spd)}},
   {"Rash", {std::make_pair<ENUMS::StatIDExceptHP, 
                            ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spa, 
                                                   ENUMS::StatIDExceptHP::spd)}},
   {"Relaxed", {std::make_pair<ENUMS::StatIDExceptHP, 
                               ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::def, 
                                                      ENUMS::StatIDExceptHP::spe)}},
   {"Sassy", {std::make_pair<ENUMS::StatIDExceptHP, 
                             ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spd, 
                                                    ENUMS::StatIDExceptHP::spe)}},
   {"Serious", {std::make_pair<ENUMS::StatIDExceptHP, 
                               ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spe, 
                                                      ENUMS::StatIDExceptHP::spe)}},
   {"Timid", {std::make_pair<ENUMS::StatIDExceptHP, 
                             ENUMS::StatIDExceptHP>(ENUMS::StatIDExceptHP::spe, 
                                                    ENUMS::StatIDExceptHP::atk)}}
};

Natures::Natures()
{
   for (const auto& [nature, stat] : Natures::NATURES) 
   {
      std::string nature_id = Util::ToID(nature);
      Natures::NATURES_BY_ID[nature_id].id = nature_id;
      Natures::NATURES_BY_ID[nature_id].name = nature;
      Natures::NATURES_BY_ID[nature_id].plus = stat.first;
      Natures::NATURES_BY_ID[nature_id].minus = stat.second;
   }
}

Natures& Natures::Instance()
{
   static Natures instance;
   return instance;
}

const std::map<std::string, 
                  std::pair<ENUMS::StatIDExceptHP, 
                            ENUMS::StatIDExceptHP>>& Natures::GetNatures() const
{
   return Natures::NATURES;
}

const std::set<std::string> Natures::GetNatureIDs() const
{
   auto out = Util::GetMapKeys(Natures::NATURES_BY_ID);
   return out;
}

std::string Natures::NatureEnumToString(const ENUMS::NatureName name) const
{
   switch (name)
   {
      case ENUMS::NatureName::Adamant: return "Adamant";
      case ENUMS::NatureName::Bashful: return "Bashful";
      case ENUMS::NatureName::Bold:    return "Bold";
      case ENUMS::NatureName::Brave:   return "Brave";
      case ENUMS::NatureName::Calm:    return "Calm";
      case ENUMS::NatureName::Careful: return "Careful";
      case ENUMS::NatureName::Docile:  return "Docile";
      case ENUMS::NatureName::Gentle:  return "Gentle";
      case ENUMS::NatureName::Hardy:   return "Hardy";
      case ENUMS::NatureName::Hasty:   return "Hasty";
      case ENUMS::NatureName::Impish:  return "Impish";
      case ENUMS::NatureName::Jolly:   return "Jolly";
      case ENUMS::NatureName::Lax:     return "Lax";
      case ENUMS::NatureName::Lonely:  return "Lonely";
      case ENUMS::NatureName::Mild:    return "Mild";
      case ENUMS::NatureName::Modest:  return "Modest";
      case ENUMS::NatureName::Naive:   return "Naive";
      case ENUMS::NatureName::Naughty: return "Naughty";
      case ENUMS::NatureName::Quiet:   return "Quiet";
      case ENUMS::NatureName::Quirky:  return "Quirky";
      case ENUMS::NatureName::Rash:    return "Rash";
      case ENUMS::NatureName::Relaxed: return "Relaxed";
      case ENUMS::NatureName::Sassy:   return "Sassy";
      case ENUMS::NatureName::Serious: return "Serious";
      case ENUMS::NatureName::Timid:   return "Timid";
   }

   return "";
}
}
}

