#include "./../include/data/types.h"

#include <set>
#include <string>

#include "./../include/util/util.h"
#include "./../include/enums.h"

namespace PokemonDamageCalcCPP
{
namespace Data
{
TypeChart Types::ExtendTypeChart(const TypeChart& original, const TypeChart& additional)
{
   TypeChart out = original;
   for (const auto& [type1, chart] : additional)
   {
      for (const auto& [type2, eff] : chart)
      {
         out[type1][type2] = eff;
      }
   }

   return out;
}

const TypeChart Types::RBY = 
{
   {
      ENUMS::TypeName::QQQ,
      {
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
      }
   },
   {
      ENUMS::TypeName::Normal, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_0},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
      }
   },
   {
      ENUMS::TypeName::Grass, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_05},
      }
   },
   {
      ENUMS::TypeName::Fire, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_05},
      }
   },
   {
      ENUMS::TypeName::Water, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_05},
      }
   },
   {
      ENUMS::TypeName::Electric, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_0},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_05},
      }
   },
   {
      ENUMS::TypeName::Ice, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_2},
      }
   },
   {
      ENUMS::TypeName::Flying, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
      }
   },
   {
      ENUMS::TypeName::Bug, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
      }
   },
   {
      ENUMS::TypeName::Poison, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
      }
   },
   {
      ENUMS::TypeName::Ground, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_0},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
      }
   },
   {
      ENUMS::TypeName::Rock, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
      }
   },
   {
      ENUMS::TypeName::Fighting, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_0},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
      }
   },
   {
      ENUMS::TypeName::Psychic, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
      }
   },
   {
      ENUMS::TypeName::Ghost, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_0},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_0},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
      }
   },
   {
      ENUMS::TypeName::Dragon, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_2},
      }
   }
};

const TypeChart Types::GSC_PATCH = 
{
   {
      ENUMS::TypeName::QQQ, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_1}
      }
   },
   {
      ENUMS::TypeName::Normal, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
   {
      ENUMS::TypeName::Grass, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
   {  
      ENUMS::TypeName::Fire, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_2}
      }
   },
   {
      ENUMS::TypeName::Water, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_1}
      }
   },
   {
      ENUMS::TypeName::Electric, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_1}
      }
   },
   {
      ENUMS::TypeName::Ice, 
      {
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_05}, 
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
   {
      ENUMS::TypeName::Flying, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
   {
      ENUMS::TypeName::Bug, 
      {
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_05}, 
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_2}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
   {
      ENUMS::TypeName::Poison, 
      {
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_0}
      }
   },
   {
      ENUMS::TypeName::Ground, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_2}
      }
   },
   {
      ENUMS::TypeName::Rock, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
   {
      ENUMS::TypeName::Fighting, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_2}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_2}
      }
   },
   {
      ENUMS::TypeName::Psychic, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_0}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
   {
      ENUMS::TypeName::Ghost, 
      {
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_2}, 
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_05}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
   {
      ENUMS::TypeName::Dragon, 
      {
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
   {
      ENUMS::TypeName::Dark, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
   {
      ENUMS::TypeName::Steel, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05}
      }
   },
};

const TypeChart Types::GSC = Types::ExtendTypeChart(Types::RBY, Types::GSC_PATCH);

const TypeChart Types::ADV = Types::GSC;

const TypeChart Types::DPP = Types::GSC;

const TypeChart Types::BW = Types::GSC;

const TypeChart Types::XY_PATCH = 
{
   {
      ENUMS::TypeName::QQQ, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Normal, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Grass, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Fire, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Water, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Electric, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Ice, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Flying, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Bug, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_05}}
   },
   {
      ENUMS::TypeName::Poison, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_2}}
   },
   {
      ENUMS::TypeName::Ground, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Rock, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Fighting, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_05}}
   },
   {
      ENUMS::TypeName::Psychic, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Ghost, 
      {
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}
      }
   },
   {
      ENUMS::TypeName::Dragon, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_0}}
   },
   {
      ENUMS::TypeName::Dark, 
      {
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_1}, 
         {ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_05}
      }
   },
   {
      ENUMS::TypeName::Steel, {{ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_2}}
   },
   {
      ENUMS::TypeName::Fairy, 
      {
         {ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Normal, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Grass, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fire, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Water, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Electric, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ice, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Flying, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Bug, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Poison, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Ground, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Rock, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Fighting, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Psychic, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Ghost, ENUMS::TypeEffectiveness::_1},
         {ENUMS::TypeName::Dragon, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Dark, ENUMS::TypeEffectiveness::_2},
         {ENUMS::TypeName::Steel, ENUMS::TypeEffectiveness::_05},
         {ENUMS::TypeName::Fairy, ENUMS::TypeEffectiveness::_1}
      }
   }
};

const TypeChart Types::XY = Types::ExtendTypeChart(Types::GSC, Types::XY_PATCH);

const TypeChart Types::SM = XY;

const TypeChart Types::SS = SM;

const TypeChart Types::SV_PATCH = 
{
   {
      ENUMS::TypeName::QQQ, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Normal, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Grass, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Fire, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Water, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Electric, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Ice, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Flying, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Bug, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Poison, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Ground, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Rock, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Fighting, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Psychic, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Ghost, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Dragon, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Dark, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Steel, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Fairy, {{ENUMS::TypeName::Stellar, ENUMS::TypeEffectiveness::_1}}
   },
   {
      ENUMS::TypeName::Stellar, {{ENUMS::TypeName::QQQ, ENUMS::TypeEffectiveness::_1}}
   }
};

const TypeChart Types::SV = Types::ExtendTypeChart(Types::XY, Types::SV_PATCH);

std::vector<TypeChart> Types::TYPES = 
{
   {}, 
   Types::RBY, 
   Types::GSC, 
   Types::ADV, 
   Types::DPP, 
   Types::BW, 
   Types::XY, 
   Types::SM, 
   Types::SS, 
   Types::SV
};

Types::Types()
{
   for (auto& type_chart : Types::TYPES) 
   {
      std::map<std::string, Types::Type> temp_map;

      for (auto& [type_name, types] : type_chart) 
      {
         std::string name = Types::TypeNameENUMToString(type_name);
         std::string type_id = Util::ToID(name);
         temp_map[type_id].id = type_id;
         temp_map[type_id].name = name;
         temp_map[type_id].effectiveness = types;
      }

      Types::TYPES_BY_ID.push_back(temp_map);
   }
}

Types& Types::Instance()
{
   static Types instance;
   return instance;
}

const std::set<std::string> Types::GetTypeIDsByGeneration(const int gen) const
{
   return Util::GetMapKeys(Types::TYPES_BY_ID.at(gen));
}


std::string Types::TypeNameENUMToString(ENUMS::TypeName type)
{
   switch (type)
   {
   case ENUMS::TypeName::Normal:
      return "Normal";
      break;

   case ENUMS::TypeName::Fighting:
      return "Fighting";
      break;

   case ENUMS::TypeName::Flying:
      return "Flying";
      break;

   case ENUMS::TypeName::Poison:
      return "Poison";
      break;

   case ENUMS::TypeName::Ground:
      return "Ground";
      break;

   case ENUMS::TypeName::Rock:
      return "Rock";
      break;

   case ENUMS::TypeName::Bug:
      return "Bug";
      break;

   case ENUMS::TypeName::Ghost:
      return "Ghost";
      break;

   case ENUMS::TypeName::Steel:
      return "Steel";
      break;

   case ENUMS::TypeName::Fire:
      return "Fire";
      break;

   case ENUMS::TypeName::Water:
      return "Water";
      break;

   case ENUMS::TypeName::Grass:
      return "Grass";
      break;

   case ENUMS::TypeName::Electric:
      return "Electric";
      break;

   case ENUMS::TypeName::Psychic:
      return "Psychic";
      break;

   case ENUMS::TypeName::Ice:
      return "Ice";
      break;

   case ENUMS::TypeName::Dragon:
      return "Dragon";
      break;

   case ENUMS::TypeName::Dark:
      return "Dark";
      break;

   case ENUMS::TypeName::Fairy:
      return "Fairy";
      break;

   case ENUMS::TypeName::Stellar:
      return "Stellar";
      break;

   case ENUMS::TypeName::QQQ:
      return "QQQ";
      break;

   default:
      return "";
      break;
   }

   return "";
}

ENUMS::TypeName Types::StringToTypeNameENUM(const std::string type)
{
   if (type == "Normal")
   {
      return ENUMS::TypeName::Normal;
   }

   if (type == "Fighting")
   {
      return ENUMS::TypeName::Fighting;
   }

   if (type == "Flying")
   {
      return ENUMS::TypeName::Flying;
   }

   if (type == "Poison")
   {
      return ENUMS::TypeName::Poison;
   }

   if (type == "Ground")
   {
      return ENUMS::TypeName::Ground;
   }

   if (type == "Rock")
   {
      return ENUMS::TypeName::Rock;
   }

   if (type == "Bug")
   {
      return ENUMS::TypeName::Bug;
   }

   if (type == "Ghost")
   {
      return ENUMS::TypeName::Ghost;
   }

   if (type == "Steel")
   {
      return ENUMS::TypeName::Steel;
   }

   if (type == "Fire")
   {
      return ENUMS::TypeName::Fire;
   }

   if (type == "Water")
   {
      return ENUMS::TypeName::Water;
   }

   if (type == "Grass")
   {
      return ENUMS::TypeName::Grass;
   }

   if (type == "Electric")
   {
      return ENUMS::TypeName::Electric;
   }

   if (type == "Psychic")
   {
      return ENUMS::TypeName::Psychic;
   }

   if (type == "Ice")
   {
      return ENUMS::TypeName::Ice;
   }

   if (type == "Dragon")
   {
      return ENUMS::TypeName::Dragon;
   }

   if (type == "Dark")
   {
      return ENUMS::TypeName::Dark;
   }

   if (type == "Fairy")
   {
      return ENUMS::TypeName::Fairy;
   }

   if (type == "Stellar")
   {
      return ENUMS::TypeName::Stellar;
   }

   return ENUMS::TypeName::QQQ;
}

const std::unordered_map<ENUMS::TypeName, ENUMS::TypeEffectiveness>& Types::GetTypeEffectivenessByTypeAndGen
(
   const ENUMS::GenerationNumber gen,
   const ENUMS::TypeName type
) const
{
   return TYPES.at(static_cast<int>(gen)).at(type);
}

float Types::CalculateTypeEffectiveness
(
   const ENUMS::TypeEffectiveness eff1,
   const ENUMS::TypeEffectiveness eff2
)
{
   switch (eff1)
   {
   case ENUMS::TypeEffectiveness::_05:
      switch (eff2)
      {
      case ENUMS::TypeEffectiveness::_05: return 0.25;
      case ENUMS::TypeEffectiveness::_1: return 0.5;
      case ENUMS::TypeEffectiveness::_2: return 1; 
      }

   case ENUMS::TypeEffectiveness::_1:
      switch (eff2)
      {
      case ENUMS::TypeEffectiveness::_05: return 0.5;
      case ENUMS::TypeEffectiveness::_1: return 1;
      case ENUMS::TypeEffectiveness::_2: return 2; 
      }

   case ENUMS::TypeEffectiveness::_2:
      switch (eff2)
      {
      case ENUMS::TypeEffectiveness::_05: return 1;
      case ENUMS::TypeEffectiveness::_1: return 2;
      case ENUMS::TypeEffectiveness::_2: return 4; 
      }
   }

   return 0;
}

}
}
