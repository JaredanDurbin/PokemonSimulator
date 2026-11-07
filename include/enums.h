#ifndef POKEMON_DAMAGE_CALC_CPP_ENUMS_H
#define POKEMON_DAMAGE_CALC_CPP_ENUMS_H

#include <algorithm>
#include <map>
#include <optional>
#include <ranges>
#include <set>
#include <string>
#include <unordered_map>

namespace PokemonDamageCalcCPP
{

namespace ENUMS
{

enum GenerationNumber
{
   __1 = 1,
   __2 = 2,
   __3 = 3,
   __4 = 4,
   __5 = 5,
   __6 = 6,
   __7 = 7,
   __8 = 8,
   __9 = 9
};

enum GenderName
{
   M,
   F,
   N
};

enum class StatID
{
   hp,
   atk,
   def,
   spa,
   spd,
   spe,
   spc
};

enum StatIDExceptHP
{
   atk,
   def,
   spa,
   spd,
   spe,
   spc, // Only used for generation 1.
   _auto
};

using StatsTable = std::unordered_map<StatID, int>;

struct SelfOrSecondaryEffect
{
   std::optional<StatsTable> boosts;
};

enum StatusName
{
   slp,
   psn,
   brn,
   frz,
   par,
   tox,
   _
};

enum GameType
{
   Singles,
   Doubles
};

enum Terrain
{
   Electric_t,
   Grassy_t,
   Psychic_t,
   Misty_t
};

inline std::string TerrainENUMToString(Terrain terrain)
{
   switch (terrain)
   {
      case Electric_t: return "Electric";
      case Grassy_t:   return "Grassy";
      case Psychic_t:  return "Psychic";
      case Misty_t:    return "Misty";
   }

   return "";
}

enum Weather
{
   Sand,
   Sun,
   Rain,
   Hail,
   Snow,
   HarshSunshine,
   HeavyRain,
   StrongWinds
};

inline std::string WeatherENUMToString(Weather weather)
{
   switch (weather)
   {
      case Sand:          return "Sand";
      case Sun:           return "Sun";
      case Rain:          return "Rain";
      case Hail:          return "Hail";
      case Snow:          return "Snow";
      case HarshSunshine: return "Harsh Sunshine";
      case HeavyRain:     return "Heavy Rain";
      case StrongWinds:   return "Strong Winds";
   }

   return "";
}

enum NatureName
{
   Adamant,
   Bashful,
   Bold,
   Brave,
   Calm,
   Careful,
   Docile,
   Gentle,
   Hardy,
   Hasty,
   Impish,
   Jolly,
   Lax,
   Lonely,
   Mild,
   Modest,
   Naive,
   Naughty,
   Quiet,
   Quirky,
   Rash,
   Relaxed,
   Sassy,
   Serious,
   Timid
};

enum TypeName
{
   Normal,
   Fighting,
   Flying,
   Poison,
   Ground,
   Rock,
   Bug,
   Ghost,
   Steel,
   Fire,
   Water,
   Grass,
   Electric,
   Psychic,
   Ice,
   Dragon,
   Dark,
   Fairy,
   Stellar,
   QQQ,
};

enum MoveCategory
{
   Physical,
   Special,
   Status
};

enum MoveTarget
{
   adjacent_ally,
   adjacent_ally_or_self,
   adjacent_foe,
   all,
   all_adjacent,
   all_adjacent_foes,
   allies,
   ally_side,
   ally_team,
   any,
   foe_side,
   normal,
   random_normal,
   scripted,
   self
};

enum DataKind
{
   Ability,
   Item,
   Move,
   Species,
   Type,
   Nature
};

enum TypeEffectiveness
{
   _0,
   _05,
   _1,
   _2
};

enum TargetOrSource
{
   target,
   source
};

enum Switching
{
   in,
   out
};

struct MoveFlags 
{
   std::optional<bool> contact = std::nullopt;
   std::optional<bool> bite = std::nullopt;
   std::optional<bool> sound = std::nullopt;
   //std::optional<bool> // TODO: heal;
   std::optional<bool> punch = std::nullopt;
   std::optional<bool> bullet = std::nullopt;
   std::optional<bool> pulse = std::nullopt;
   std::optional<bool> slicing = std::nullopt;
   std::optional<bool> wind = std::nullopt;
};

}
}


#endif
