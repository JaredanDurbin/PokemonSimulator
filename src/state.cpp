#include "./../include/state.hpp"

#include "./../include/util/csv_util.h"
#include "./../include/data/types.h"
#include "./../include/util/csv_parser.hpp"

namespace PokemonDamageCalcCPP
{
namespace State 
{

Pokemon ConstructPokemon(const Util::CSV::CSVLine& line)
{
   Pokemon pokemon_out;

   if (line.at(2) != "")
   {
      pokemon_out.name = line.at(2);
   }
   if (line.at(3) != "")
   {
      pokemon_out.level = std::stoi(line.at(3));
   }
   if (line.at(4) != "")
   {
      pokemon_out.ability = line.at(4);
   }
   if (line.at(5) != "")
   {
      pokemon_out.ability_on = std::stoi(line.at(5));
   }
   if (line.at(6) != "")
   {
      pokemon_out.is_dynamaxed = std::stoi(line.at(6));
   }
   if (line.at(7) != "")
   {
      pokemon_out.dynamax_level = std::stoi(line.at(7));
   }
   if (line.at(8) != "")
   {
      pokemon_out.is_salt_cure = std::stoi(line.at(8));
   }
   if (line.at(9) != "")
   {
      pokemon_out.allies_fainted = std::stoi(line.at(9));
   }
   if (line.at(10) != "")
   {
      pokemon_out.boosted_stat = Util::CSV::StringToStatIDExceptHP(line.at(10));
   }
   if (line.at(11) != "")
   {
      pokemon_out.item = line.at(11);
   }
   if (line.at(12) != "")
   {
      pokemon_out.gender = Util::CSV::StringToGenderName(line.at(12));
   }
   if (line.at(13) != "")
   {
      pokemon_out.nature = Util::CSV::StringToNatureName(line.at(13));
   }
   if (line.at(14) != "")
   {
      pokemon_out.ivs = Util::CSV::StringToStatsTable(line.at(14));
   }
   if (line.at(15) != "")
   {
      pokemon_out.evs = Util::CSV::StringToStatsTable(line.at(15));
   }
   if (line.at(16) != "")
   {
      pokemon_out.boosts = Util::CSV::StringToStatsTable(line.at(16));
   }
   if (line.at(17) != "")
   {
      pokemon_out.original_cur_hp = std::stoi(line.at(17));
   }
   if (line.at(18) != "")
   {
      pokemon_out.cur_hp = std::stoi(line.at(18));
   }
   if (line.at(19) != "")
   {
      pokemon_out.status = Util::CSV::StringToStatus(line.at(19));
   }
   if (line.at(20) != "")
   {
      pokemon_out.tera_type = Data::Types::Instance().StringToTypeNameENUM(line.at(20));
   }
   if (line.at(21) != "")
   {
      pokemon_out.toxic_counter = std::stoi(line.at(21));
   }
   if (line.at(22) != "")
   {
      pokemon_out.moves = Util::CSV::SplitStringByDelimiter(';', line.at(22));
   }

   return pokemon_out;
}

Side ConstructSide(const Util::CSV::CSVLine& line)
{
   Side side_out;

   if (line.at(3) != "")
   {
      side_out.spikes = std::stoi(line.at(1));
   }
   if (line.at(4) != "")
   {
      side_out.steelsurge = std::stoi(line.at(2));
   }
   if (line.at(5) != "")
   {
      side_out.vinelash = std::stoi(line.at(3));
   }
   if (line.at(6) != "")
   {
      side_out.wildfire = std::stoi(line.at(4));
   }
   if (line.at(7) != "")
   {
      side_out.cannonade = std::stoi(line.at(5));
   }
   if (line.at(8) != "")
   {
      side_out.volcalith = std::stoi(line.at(6));
   }
   if (line.at(9) != "")
   {
      side_out.is_sr = std::stoi(line.at(7));
   }
   if (line.at(10) != "")
   {
      side_out.is_reflect = std::stoi(line.at(8));
   }
   if (line.at(11) != "")
   {
      side_out.is_light_screen = std::stoi(line.at(9));
   }
   if (line.at(12) != "")
   {
      side_out.is_protected = std::stoi(line.at(10));
   }
   if (line.at(13) != "")
   {
      side_out.is_seeded = std::stoi(line.at(11));
   }
   if (line.at(14) != "")
   {
      side_out.is_foresight = std::stoi(line.at(12));
   }
   if (line.at(15) != "")
   {
      side_out.is_tailwind = std::stoi(line.at(13));
   }
   if (line.at(16) != "")
   {
      side_out.is_helping_hand = std::stoi(line.at(14));
   }
   if (line.at(17) != "")
   {
      side_out.is_flower_gift = std::stoi(line.at(15));
   }
   if (line.at(18) != "")
   {
      side_out.is_friend_guard = std::stoi(line.at(16));
   }
   if (line.at(19) != "")
   {
      side_out.is_aurora_veil = std::stoi(line.at(17));
   }
   if (line.at(20) != "")
   {
      side_out.is_battery = std::stoi(line.at(18));
   }
   if (line.at(21) != "")
   {
      side_out.is_power_spot = std::stoi(line.at(19));
   }
   if (line.at(22) != "")
   {
      side_out.is_switching = Util::CSV::StringToSwitching(line.at(20));
   }

   return side_out;
}

Field ConstructField(const Util::CSV::CSVLine& line, const Side& attacker, const Side& defender)
{
   Field field_out;

   if (line.at(1) != "")
   {
      field_out.game_type = Util::CSV::StringToGameType(line.at(0));
   }
   if (line.at(2) != "")
   {
      field_out.weather = Util::CSV::StringToWeather(line.at(1));
   }
   if (line.at(3) != "")
   {
      field_out.terrain = Util::CSV::StringToTerrain(line.at(2));
   }
   if (line.at(4) != "")
   {
      field_out.is_magic_room = std::stoi(line.at(3));
   }
   if (line.at(5) != "")
   {
      field_out.is_wonder_room = std::stoi(line.at(4));
   }
   if (line.at(6) != "")
   {
      field_out.is_gravity = std::stoi(line.at(5));
   }
   if (line.at(7) != "")
   {
      field_out.is_aura_break = std::stoi(line.at(6));
   }
   if (line.at(8) != "")
   {
      field_out.is_fairy_aura = std::stoi(line.at(7));
   }
   if (line.at(9) != "")
   {
      field_out.is_dark_aura = std::stoi(line.at(8));
   }
   if (line.at(10) != "")
   {
      field_out.is_beads_of_ruin = std::stoi(line.at(9));
   }
   if (line.at(11) != "")
   {
      field_out.is_sword_of_ruin = std::stoi(line.at(10));
   }
   if (line.at(12) != "")
   {
      field_out.is_tablets_of_ruin = std::stoi(line.at(11));
   }
   if (line.at(13) != "")
   {
      field_out.is_vessel_of_ruin = std::stoi(line.at(12));
   }

   field_out.attacker_side = attacker;
   field_out.defender_side = defender;

   return field_out;
}

}
}

