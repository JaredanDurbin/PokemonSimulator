#ifndef POKEMON_DAMAGE_CALC_CPP_MOVES_HPP
#define POKEMON_DAMAGE_CALC_CPP_MOVES_HPP

#include <vector>

#include "enums.h"
#include "state.hpp"

namespace PokemonDamageCalcCPP
{
namespace Move
{
const std::set<ENUMS::TypeName> SPECIAL = 
{
   ENUMS::TypeName::Fire, 
   ENUMS::TypeName::Water, 
   ENUMS::TypeName::Grass, 
   ENUMS::TypeName::Electric, 
   ENUMS::TypeName::Ice, 
   ENUMS::TypeName::Psychic, 
   ENUMS::TypeName::Dark, 
   ENUMS::TypeName::Dragon
};

const std::map<ENUMS::TypeName, std::string> MAXMOVES_TYPING = 
{
   {ENUMS::TypeName::Bug, "Flutterby"},
   {ENUMS::TypeName::Dark, "Darkness"},
   {ENUMS::TypeName::Dragon, "Wyrmwind"},
   {ENUMS::TypeName::Electric, "Lightning"},
   {ENUMS::TypeName::Fairy, "Starfall"},
   {ENUMS::TypeName::Fighting, "Knuckle"},
   {ENUMS::TypeName::Fire, "Flare"},
   {ENUMS::TypeName::Flying, "Airstream"},
   {ENUMS::TypeName::Ghost, "Phantasm"},
   {ENUMS::TypeName::Grass, "Overgrowth"},
   {ENUMS::TypeName::Ground, "Quake"},
   {ENUMS::TypeName::Ice, "Hailstorm"},
   {ENUMS::TypeName::Normal, "Strike"},
   {ENUMS::TypeName::Poison, "Ooze"},
   {ENUMS::TypeName::Psychic, "Mindstorm"},
   {ENUMS::TypeName::Rock, "Rockfall"},
   {ENUMS::TypeName::Steel, "Steelspike"},
   {ENUMS::TypeName::Water, "Geyser"},
};

const std::map<ENUMS::TypeName, std::string> ZMOVES_TYPING = 
{
   {ENUMS::TypeName::Bug, "Savage Spin-Out"},
   {ENUMS::TypeName::Dark, "Black Hole Eclipse"},
   {ENUMS::TypeName::Dragon, "Devastating Drake"},
   {ENUMS::TypeName::Electric, "Gigavolt Havoc"},
   {ENUMS::TypeName::Fairy, "Twinkle Tackle"},
   {ENUMS::TypeName::Fighting, "All-Out Pummeling"},
   {ENUMS::TypeName::Fire, "Inferno Overdrive"},
   {ENUMS::TypeName::Flying, "Supersonic Skystrike"},
   {ENUMS::TypeName::Ghost, "Never-Ending Nightmare"},
   {ENUMS::TypeName::Grass, "Bloom Doom"},
   {ENUMS::TypeName::Ground, "Tectonic Rage"},
   {ENUMS::TypeName::Ice, "Subzero Slammer"},
   {ENUMS::TypeName::Normal, "Breakneck Blitz"},
   {ENUMS::TypeName::Poison, "Acid Downpour"},
   {ENUMS::TypeName::Psychic, "Shattered Psyche"},
   {ENUMS::TypeName::Rock, "Continental Crush"},
   {ENUMS::TypeName::Steel, "Corkscrew Crash"},
   {ENUMS::TypeName::Water, "Hydro Vortex"},
};

std::string GetZMoveName
(
   const std::string& move_name, 
   const ENUMS::TypeName move_type, 
   const std::optional<std::string>& item
);

std::string GetMaxMoveName
(
   const ENUMS::TypeName move_type,
   const std::optional<std::string>& move_name,
   const std::optional<std::string>& pokemon_species,
   const bool is_status,
   const std::optional<std::string>& pokemon_ability
);

class Move //implements State.Move 
{
private:
   ENUMS::GenerationNumber gen = ENUMS::GenerationNumber::__9;
   std::string name = "";

   std::string original_name = "";
   std::optional<std::string> ability = std::nullopt;
   std::optional<std::string> item = std::nullopt;
   std::optional<std::string> species = std::nullopt;
   std::optional<bool> use_z = std::nullopt;
   std::optional<bool> use_max = std::nullopt;
   std::optional<Data::Move> overrides = std::nullopt;

   std::optional<int> hits = std::nullopt;
   int times_used = 0;
   int times_used_with_metronome = 0;
   int bp = 0;
   ENUMS::TypeName type = ENUMS::TypeName::QQQ;
   ENUMS::MoveCategory category = ENUMS::MoveCategory::Status;
   ENUMS::MoveFlags flags{};
   bool secondaries = false;
   ENUMS::MoveTarget target = ENUMS::MoveTarget::normal;
   std::optional<std::pair<int, int>> recoil = std::nullopt;
   bool has_crash_damage = false;
   bool mind_blown_recoil = false;
   bool struggle_recoil = false;
   bool is_crit = false;
   bool is_stellar_first_use = false;
   std::optional<std::pair<int, int>> drain = std::nullopt;
   int priority = 1;
   std::optional<int> drops_stats = std::nullopt;
   bool ignore_defensive = false;
   std::optional<ENUMS::StatIDExceptHP> override_offensive_stat = std::nullopt;
   std::optional<ENUMS::StatIDExceptHP> override_defensive_stat = std::nullopt;
   std::optional<ENUMS::TargetOrSource> override_offensive_pokemon = std::nullopt;
   std::optional<ENUMS::TargetOrSource> override_defensive_pokemon = std::nullopt;
   bool breaks_protect = false;
   bool is_z = false;
   bool is_max = false;
   bool multiaccuracy = false;

public:
   Move
   (
      const ENUMS::GenerationNumber gen_in,
      const std::string name_in,
      const State::Move options = {}
   );

   inline void SetBP(const int bp_in) { bp = bp_in; };
   inline void SetCrit(const bool crit_in) { is_crit = crit_in; };
   inline void SetMoveCategory(const ENUMS::MoveCategory cat) { category = cat; };
   inline void SetType(const ENUMS::TypeName type_in) { type = type_in; };
   inline void SetSecondaries(const bool secondaries_in) { secondaries = secondaries_in; };
   inline void SetPriority(const int priority_in) { priority = priority_in; };
   inline void SetTarget(const ENUMS::MoveTarget target_in) { target = target_in; };
   inline void SetMoveFlagContact(const bool in) { flags.contact = in; };

   inline const std::string& GetName() const { return name; };
   inline std::optional<int> GetHits() const { return hits; };
   inline std::optional<std::pair<int, int>> GetDrain() const { return drain; };
   inline ENUMS::MoveCategory GetMoveCategory() const { return category; };
   inline int GetTimesUsed() const { return times_used; };
   inline int GetTimesUsedWithMetronome() const { return times_used_with_metronome; };
   inline bool GetIsZ() const { return is_z; };
   inline std::optional<std::pair<int, int>> GetRecoil() const { return recoil; };
   inline bool GetHasCrashDamage() const { return has_crash_damage; };
   inline bool GetMindBlownRecoil() const { return mind_blown_recoil; };
   inline bool GetStruggleRecoil() const { return struggle_recoil; };
   inline ENUMS::TypeName GetType() const { return type; };
   inline int GetBP() const { return bp; };
   inline bool GetIsCrit() const { return is_crit; };
   inline ENUMS::MoveTarget GetTarget() const { return target; };
   inline const ENUMS::MoveFlags& GetMoveFlags() const { return flags; };
   inline std::optional<int> GetDropsStats() const { return drops_stats; };
   inline bool GetBreaksProtect() const { return breaks_protect; };
   inline int GetPriority() const { return priority; };
   inline bool GetSecondaries() const { return secondaries; };
   inline std::optional<ENUMS::StatIDExceptHP> GetOverrideDefensiveStat() const 
   { return override_defensive_stat; };
   inline bool GetIgnoreDefense() const { return ignore_defensive; };
   inline bool GetIsStellarFirstUse() const { return is_stellar_first_use; };
   inline const std::string& GetOriginalName() const { return original_name; };
   inline bool GetIsMax() const { return is_max; };
   inline bool GetMultiAccuracy() const { return multiaccuracy; };

   inline void IncrementTimesUsed() { times_used++; };
   inline void IncrementTimesUsedWithMetronome() { times_used_with_metronome++; };

   bool Named(std::initializer_list<std::string> names) const;
   bool HasType(const std::initializer_list<ENUMS::TypeName>& types_in) const;
   bool HasType(const std::vector<ENUMS::TypeName>& types_in) const;
};
}
}

#endif
