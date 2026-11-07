#ifndef POKEMON_DAMAGE_CALC_CPP_CALC_UTIL_CSV_CSV_UTIL_H
#define POKEMON_DAMAGE_CALC_CPP_CALC_UTIL_CSV_CSV_UTIL_H

// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include "./enums.h"
#include "./csv_parser.hpp"
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Namespace block.
// ----------------------------------------------------------------------------
namespace PokemonDamageCalcCPP
{
namespace Util
{
namespace CSV
{

std::optional<ENUMS::StatIDExceptHP> StringToStatIDExceptHP(const std::string& stat_str);
std::optional<ENUMS::StatID> StringToStatID(const std::string& stat_str);
std::optional<ENUMS::GenderName> StringToGenderName(const std::string& gender_str);
std::optional<ENUMS::NatureName> StringToNatureName(const std::string& nature_str);
std::optional<ENUMS::StatsTable> StringToStatsTable(const std::string& stats_str);
std::optional<ENUMS::StatusName> StringToStatus(const std::string& status_str);
std::optional<ENUMS::Switching> StringToSwitching(const std::string& switch_str);
ENUMS::GameType StringToGameType(const std::string& game_type_str);
std::optional<ENUMS::Weather> StringToWeather(const std::string& weather_str);
std::optional<ENUMS::Terrain> StringToTerrain(const std::string& terrain_str);
ENUMS::GenerationNumber StringToGeneration(const std::string& gen_str);

}
}
}

#endif
