#ifndef POKEMON_DAMAGE_CALC_CPP_DATA_MOVES_H
#define POKEMON_DAMAGE_CALC_CPP_DATA_MOVES_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include <optional>

#include "../enums.h"

namespace PokemonDamageCalcCPP
{
namespace Data
{
// This is actually "MoveData" but I did not see a reason to actual make a separate
// Move class.
struct Move 
{
   std::string kind = "Move";
   std::string id = "";
   std::optional<std::string> name = std::nullopt;
   std::optional<int> bp = std::nullopt;
   std::optional<bool> breaks_protect = std::nullopt;
   std::optional<bool> is_punch = std::nullopt;
   std::optional<ENUMS::MoveCategory> category = std::nullopt;
   std::optional<ENUMS::TypeName> type = std::nullopt;
   std::optional<std::pair<int, int>> drain = std::nullopt;
   std::optional<bool> ignore_defensive = std::nullopt;
   std::optional<bool> is_bite = std::nullopt;
   std::optional<bool> is_bullet = std::nullopt;
   std::optional<bool> is_max = std::nullopt;
   std::optional<bool> is_pulse = std::nullopt;
   std::optional<bool> is_slicing = std::nullopt;
   std::optional<bool> is_sound = std::nullopt;
   std::optional<bool> is_wind = std::nullopt;
   std::optional<bool> has_crash_damage = std::nullopt;
   std::optional<bool> mind_blown_recoil = std::nullopt;
   std::optional<ENUMS::StatIDExceptHP> override_offensive_stat = std::nullopt;
   std::optional<ENUMS::StatIDExceptHP> override_defensive_stat = std::nullopt;
   std::optional<ENUMS::TargetOrSource> override_offensive_pokemon = std::nullopt;
   std::optional<ENUMS::TargetOrSource> override_defensive_pokemon = std::nullopt;
   std::optional<int> priority = std::nullopt;
   std::optional<std::pair<int, int>> recoil = std::nullopt;
   std::optional<ENUMS::SelfOrSecondaryEffect> self = std::nullopt;
   std::optional<bool> makes_contact = std::nullopt;
   std::optional<std::vector<int>> multihit = std::nullopt;
   std::optional<bool> multiaccuracy = std::nullopt;
   std::optional<bool> secondaries = std::nullopt;
   std::optional<bool> struggle_recoil = std::nullopt;
   std::optional<ENUMS::MoveTarget> target = std::nullopt;
   std::optional<bool> will_crit = std::nullopt;
   std::optional<bool> is_z = std::nullopt;
   std::optional<int> zp = std::nullopt;
   std::optional<int> max_power = std::nullopt;
   std::optional<std::string> max_move = std::nullopt;
   std::optional<std::string> z_move = std::nullopt;
   std::optional<ENUMS::MoveFlags> flags = std::nullopt;
};

class Moves
{
public:
   static Moves& Instance();

   [[nodiscard]]
   const std::map<std::string, Move>& GetRBYMoves() const;
   const std::map<std::string, Move>& GetGSCMoves() const;
   const std::map<std::string, Move>& GetADVMoves() const;
   const std::map<std::string, Move>& GetDPPMoves() const;
   const std::map<std::string, Move>& GetBWMoves() const;
   const std::map<std::string, Move>& GetXYMoves() const;
   const std::map<std::string, Move>& GetSMMoves() const;
   const std::map<std::string, Move>& GetSSMoves() const;
   const std::map<std::string, Move>& GetSVMoves() const;
   const Move& GetMoveByGen(const int gen, const std::string& move_name) const;
   const Move& GetMoveByGen_ID(const int gen, const std::string& move_id) const;
   Move ExtendMove(const Move& output, const std::optional<Move>& input = std::nullopt);

private:
   static std::map<std::string, Move> EraseMapOfMoveEntry
   (
      const std::map<std::string, Move>& move_list,
      const std::string& entry
   );
   static std::map<std::string, Move> EraseMapOfMoveEntries
   (
      const std::map<std::string, Move>& move_list,
      const std::vector<std::string>& entries
   );
   static void UpdateMoveValues(Move& output, const Move& input);
   static std::map<std::string, Move> ExtendMapOfMove
   (
      const std::vector<std::map<std::string, Move>>& move_list
   );
   
   Moves();
   ~Moves() = default;

   static const std::map<std::string, Move> RBY;
   static const std::map<std::string, Move> GSC_PATCH;
   static const std::map<std::string, Move> GSC;
   static const std::map<std::string, Move> ADV_PATCH;
   static const std::map<std::string, Move> ADV;
   static const std::map<std::string, Move> DPP_PATCH;
   static const std::map<std::string, Move> DPP;
   static const std::map<std::string, Move> BW_PATCH;
   static const std::map<std::string, Move> BW;
   static const std::map<std::string, Move> XY_PATCH;
   static const std::map<std::string, Move> XY;
   static const std::map<std::string, Move> SM_PATCH;
   static const std::map<std::string, Move> SM;
   static const std::map<std::string, Move> SS_PATCH;
   static const std::map<std::string, Move> SS;
   static const std::vector<std::string> LGPE_MOVES;
   static const std::map<std::string, Move> SV_PATCH;
   static const std::map<std::string, Move> SV;

   static std::vector<std::map<std::string, Move>> MOVES;
   std::vector<std::map<std::string, Move>> MOVES_BY_ID;
};
}
}

#endif
