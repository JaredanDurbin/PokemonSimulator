// ----------------------------------------------------------------------------
// Includes block.
// ----------------------------------------------------------------------------
#include "./../include/util/csv_util.h"
#include "./../include/util/util.h"
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

std::optional<ENUMS::StatIDExceptHP> StringToStatIDExceptHP(const std::string& stat_str)
{
   if (stat_str == "atk") return ENUMS::StatIDExceptHP::atk;
   if (stat_str == "def") return ENUMS::StatIDExceptHP::def;
   if (stat_str == "spa") return ENUMS::StatIDExceptHP::spa;
   if (stat_str == "spd") return ENUMS::StatIDExceptHP::spd;
   if (stat_str == "spe") return ENUMS::StatIDExceptHP::spe;
   if (stat_str == "spc") return ENUMS::StatIDExceptHP::spc;

   return std::nullopt;
}

std::optional<ENUMS::StatID> StringToStatID(const std::string& stat_str)
{
   if (stat_str == "hp") return ENUMS::StatID::hp;
   if (stat_str == "atk") return ENUMS::StatID::atk;
   if (stat_str == "def") return ENUMS::StatID::def;
   if (stat_str == "spa") return ENUMS::StatID::spa;
   if (stat_str == "spd") return ENUMS::StatID::spd;
   if (stat_str == "spe") return ENUMS::StatID::spe;
   if (stat_str == "spc") return ENUMS::StatID::spc;

   return std::nullopt;
}

std::optional<ENUMS::GenderName> StringToGenderName(const std::string& gender_str)
{
   if (gender_str == "F") return ENUMS::GenderName::F;
   if (gender_str == "M") return ENUMS::GenderName::M;
   if (gender_str == "N") return ENUMS::GenderName::N;

   return std::nullopt;
}

std::optional<ENUMS::NatureName> StringToNatureName(const std::string& nature_str)
{
   if (nature_str == "adamant") return ENUMS::NatureName::Adamant;
   if (nature_str == "bashful") return ENUMS::NatureName::Bashful;
   if (nature_str == "bold") return ENUMS::NatureName::Bold;
   if (nature_str == "brave") return ENUMS::NatureName::Brave;
   if (nature_str == "calm") return ENUMS::NatureName::Calm;
   if (nature_str == "careful") return ENUMS::NatureName::Careful;
   if (nature_str == "docile") return ENUMS::NatureName::Docile;
   if (nature_str == "gentle") return ENUMS::NatureName::Gentle;
   if (nature_str == "hardy") return ENUMS::NatureName::Hardy;
   if (nature_str == "hasty") return ENUMS::NatureName::Hasty;
   if (nature_str == "impish") return ENUMS::NatureName::Impish;
   if (nature_str == "jolly") return ENUMS::NatureName::Jolly;
   if (nature_str == "lax") return ENUMS::NatureName::Lax;
   if (nature_str == "lonely") return ENUMS::NatureName::Lonely;
   if (nature_str == "mild") return ENUMS::NatureName::Mild;
   if (nature_str == "modest") return ENUMS::NatureName::Modest;
   if (nature_str == "naive") return ENUMS::NatureName::Naive;
   if (nature_str == "naughty") return ENUMS::NatureName::Naughty;
   if (nature_str == "quiet") return ENUMS::NatureName::Quiet;
   if (nature_str == "quirky") return ENUMS::NatureName::Quirky;
   if (nature_str == "rash") return ENUMS::NatureName::Rash;
   if (nature_str == "relaxed") return ENUMS::NatureName::Relaxed;
   if (nature_str == "sassy") return ENUMS::NatureName::Sassy;
   if (nature_str == "serious") return ENUMS::NatureName::Serious;
   if (nature_str == "timid") return ENUMS::NatureName::Timid;

   return std::nullopt;
}


std::optional<ENUMS::StatsTable> StringToStatsTable(const std::string& stats_str)
{
   ENUMS::StatsTable out{};

   std::vector<std::string> stats_split = SplitStringByDelimiter(';', stats_str);
   for (auto& stat_num_str : stats_split)
   {
      std::vector<std::string> stat_num = SplitStringByDelimiter(':', stat_num_str);
      std::optional<ENUMS::StatID> stat = StringToStatID(stat_num.at(0));
      if (stat)
      {
         out[*stat] = std::stoi(stat_num.at(1));
      }
   }

   if (out.empty())
   {
      return std::nullopt;
   }
   else
   {
      return out;
   }
}

std::optional<ENUMS::StatusName> StringToStatus(const std::string& status_str)
{
   if (status_str == "brn") return ENUMS::StatusName::brn;
   if (status_str == "frz") return ENUMS::StatusName::frz;
   if (status_str == "par") return ENUMS::StatusName::par;
   if (status_str == "psn") return ENUMS::StatusName::psn;
   if (status_str == "slp") return ENUMS::StatusName::slp;
   if (status_str == "tox") return ENUMS::StatusName::tox;

   return std::nullopt;
}

std::optional<ENUMS::Switching> StringToSwitching(const std::string& switch_str)
{
   if (switch_str == "in") return ENUMS::Switching::in;
   if (switch_str == "out") return ENUMS::Switching::out;

   return std::nullopt;
}

ENUMS::GameType StringToGameType(const std::string& game_type_str)
{
   if (game_type_str == "singles") return ENUMS::GameType::Singles;
   
   return ENUMS::GameType::Doubles;
}

std::optional<ENUMS::Weather> StringToWeather(const std::string& weather_str)
{
   if (weather_str == "hail") return ENUMS::Weather::Hail;
   if (weather_str == "harsh sunshine") return ENUMS::Weather::HarshSunshine;
   if (weather_str == "heavy rain") return ENUMS::Weather::HeavyRain;
   if (weather_str == "rain") return ENUMS::Weather::Rain;
   if (weather_str == "sand") return ENUMS::Weather::Sand;
   if (weather_str == "snow") return ENUMS::Weather::Snow;
   if (weather_str == "strong winds") return ENUMS::Weather::StrongWinds;
   if (weather_str == "sun") return ENUMS::Weather::Sun;
   
   return std::nullopt;
}

std::optional<ENUMS::Terrain> StringToTerrain(const std::string& terrain_str)
{
   auto terrain_str_ = Util::ToLower(terrain_str);
   if (terrain_str_ == "electric") return ENUMS::Terrain::Electric_t;
   if (terrain_str_ == "grassy") return ENUMS::Terrain::Grassy_t;
   if (terrain_str_ == "misty") return ENUMS::Terrain::Misty_t;
   if (terrain_str_ == "psychic") return ENUMS::Terrain::Psychic_t;

   return std::nullopt;
}


ENUMS::GenerationNumber StringToGeneration(const std::string& gen_str)
{
   if (gen_str == "1") return ENUMS::GenerationNumber::__1;
   if (gen_str == "2") return ENUMS::GenerationNumber::__2;
   if (gen_str == "3") return ENUMS::GenerationNumber::__3;
   if (gen_str == "4") return ENUMS::GenerationNumber::__4;
   if (gen_str == "5") return ENUMS::GenerationNumber::__5;
   if (gen_str == "6") return ENUMS::GenerationNumber::__6;
   if (gen_str == "7") return ENUMS::GenerationNumber::__7;
   if (gen_str == "8") return ENUMS::GenerationNumber::__8;
   
   return ENUMS::GenerationNumber::__9;
}

}
}
}