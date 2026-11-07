#ifndef POKEMON_DAMAGE_CALC_CPP_POKEMON_HPP
#define POKEMON_DAMAGE_CALC_CPP_POKEMON_HPP

#include <vector>

#include "enums.h"
#include "state.hpp"

namespace PokemonDamageCalcCPP
{
namespace Pokemon
{
const std::vector<ENUMS::StatID> STATS = 
{
   ENUMS::StatID::hp, 
   ENUMS::StatID::atk, 
   ENUMS::StatID::def, 
   ENUMS::StatID::spa, 
   ENUMS::StatID::spd, 
   ENUMS::StatID::spe
};
//const SPC = new Set(['spc']);


class Pokemon
{
private:
   ENUMS::GenerationNumber gen = ENUMS::GenerationNumber::__9;
   std::string name = "";
   Data::Specie species{};

   std::vector<ENUMS::TypeName> types{};
   float weightkg = 0;

   int level = 100;
   std::optional<ENUMS::GenderName> gender = std::nullopt;
   std::optional<std::string> ability = std::nullopt;
   std::optional<bool> ability_on = std::nullopt;
   std::optional<bool> is_dynamaxed = std::nullopt;
   std::optional<int> dynamax_level = std::nullopt;
   std::optional<bool> is_salt_cure = std::nullopt;
   std::optional<int> allies_fainted = std::nullopt;
   std::optional<ENUMS::StatIDExceptHP> boosted_stat = std::nullopt;
   std::optional<std::string> item = std::nullopt;
   std::optional<ENUMS::TypeName> tera_type = std::nullopt;

   ENUMS::NatureName nature = ENUMS::NatureName::Serious;
   ENUMS::StatsTable ivs{};
   ENUMS::StatsTable evs{};
   ENUMS::StatsTable boosts{};
   ENUMS::StatsTable raw_stats{};
   ENUMS::StatsTable stats{};

   int original_cur_hp = 0;
   ENUMS::StatusName status = ENUMS::StatusName::_;
   int toxic_counter = 0;

   std::vector<std::string> moves{};

   static ENUMS::StatsTable WithDefault
   (
      ENUMS::GenerationNumber gen_in,
      ENUMS::StatsTable current,
      int val,
      bool match = true
   );

public:
   Pokemon
   (
      const ENUMS::GenerationNumber gen_in,
      const std::string& name_in,
      const State::Pokemon& options = {}
   );

   inline void SetStat(const ENUMS::StatID stat, const int num) { stats[stat] = num; };
   inline void SetType(const std::vector<ENUMS::TypeName> types_in) { types = types_in; };
   inline void SetBoost(const ENUMS::StatID stat, const int num) { boosts[stat] = num; };
   inline void SetAbility(const std::string ability_in) { ability = ability_in; };
   inline void SetItem(const std::string& item_in) { item = item_in; };
   inline void SetRawStat(const ENUMS::StatID stat, const int num) { raw_stats[stat] = num; };
   inline void SetEV(const ENUMS::StatID stat, const int num) { evs[stat] = num; };

   inline std::string GetName() const { return name; };
   inline const int GetLevel() const { return level; };
   inline const std::vector<ENUMS::TypeName>& GetTypes() const { return types; };
   inline const std::string GetAbility() const { return ability ? *ability : ""; };
   inline bool GetIsSaltCure() const { return is_salt_cure ? *is_salt_cure : false; };
   inline std::optional<ENUMS::TypeName> GetTeraType() const { return tera_type; };
   inline int GetToxicCounter() const { return toxic_counter; };
   inline const ENUMS::StatsTable& GetRawStats() const { return raw_stats; };
   inline const ENUMS::StatsTable& GetBoosts() const { return boosts; };
   inline bool GetAbilityOn() const { return ability_on? *ability_on: false; };
   inline std::optional<ENUMS::StatIDExceptHP> GetBoostedStat() const { return boosted_stat; };
   inline const ENUMS::StatsTable& GetStats() const { return stats; };
   inline std::optional<std::string> GetItem() const { return item; };
   inline const ENUMS::StatsTable& GetEVs() const { return evs; };
   inline const ENUMS::StatsTable& GetIVs() const { return ivs; };
   inline ENUMS::NatureName GetNature() const { return nature; };
   inline float GetWeight() const { return weightkg; };
   inline const std::vector<std::string>& GetMoves() const { return moves; };
   inline ENUMS::GenerationNumber GetGeneration() const { return gen; };
   inline std::optional<ENUMS::GenderName> GetGender() const { return gender; };
   inline std::optional<bool> GetIsDynamaxed() const { return is_dynamaxed; };
   inline std::optional<int> GetAlliesFainted() const { return allies_fainted; };

   int MaxHP(bool original = false) const;
   int CurHP(bool original = false) const;
   bool HasAbility(const std::initializer_list<std::string>& abilities) const;
   bool HasAbility(const std::vector<std::string>& abilities) const;
   bool HasItem(const std::initializer_list<std::string>& items) const;
   bool HasItem(const std::vector<std::string>& items) const;
   bool HasStatus(const std::initializer_list<ENUMS::StatusName>& statuses) const;
   inline bool HasStatus() const { return status != ENUMS::StatusName::_; };
   bool HasType(const std::initializer_list<ENUMS::TypeName>& types_in) const;
   bool HasOriginalType(const std::initializer_list<ENUMS::TypeName>& types_in) const;
   bool Named(const std::initializer_list<std::string>& names) const;
   int CalcStat(const ENUMS::GenerationNumber gen_in, const ENUMS::StatID stat_in);

   static std::string GetForme
   (
      const ENUMS::GenerationNumber gen,
      const std::string& species_name,
      const std::optional<std::string> item,
      const std::optional<std::string> move_name
   );

   inline void TurnAbilityOn() { ability_on = true; };

};

}
}


#endif
