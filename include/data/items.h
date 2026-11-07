#ifndef POKEMON_DAMAGE_CALC_CPP_DATA_ITEMS_H
#define POKEMON_DAMAGE_CALC_CPP_DATA_ITEMS_H

#include <map>
#include <set>
#include <string>
#include <vector>

#include "./../enums.h"

namespace PokemonDamageCalcCPP
{
namespace Data
{
class Items
{
public:
   struct NaturalGift
   {
      ENUMS::TypeName t;
      int p;
   };

   static Items& Instance();

   [[nodiscard]]
   const std::set<std::string>& GetRBYItems() const;
   const std::set<std::string>& GetGSCItems() const;
   const std::set<std::string>& GetADVItems() const;
   const std::set<std::string>& GetDPPItems() const;
   const std::set<std::string>& GetBWItems() const;
   const std::set<std::string>& GetXYItems() const;
   const std::set<std::string>& GetSMItems() const;
   const std::set<std::string>& GetSSItems() const;
   const std::set<std::string>& GetSVItems() const;
   const std::set<std::string>& GetItemsByGeneration(const int gen) const;
   //const std::map<std::string, std::string>& GetItemsByIDByGeneration(const int gen) const;
   std::optional<ENUMS::TypeName> GetItemBoostType(const std::string& item);
   std::optional<ENUMS::TypeName> GetBerryResistType(const std::string& berry);
   int GetFlingPower(std::optional<std::string> item);
   NaturalGift GetNaturalGift(const int gen, const std::string& item);
   std::optional<ENUMS::TypeName> GetTechnoBlast(const std::string& item);
   std::optional<ENUMS::TypeName> GetMultiAttack(const std::string& item);
   const std::string& GetMegaEvolves(const int gen, const std::string& item);
   const std::optional<ENUMS::Terrain> GetTerrainFromSeed(const std::string& item) const;
   inline const ENUMS::StatID GetSeedBoostedStat(const std::string& seed) 
   { return SEED_BOOSTED_STAT.at(seed); };

private:
   struct Item
   {
      std::string kind = "Item";
      std::string id;
      std::string name;
      std::string mega_evolves;
      bool is_berry = false;
      NaturalGift natural_gift;
   };
   
   Items();
   ~Items() = default;

   static const std::set<std::string> RBY;
   static const std::set<std::string> GSC;
   static const std::set<std::string> GSC_ONLY;
   static const std::set<std::string> ADV;
   static const std::set<std::string> DPP;
   static const std::set<std::string> BW;
   static const std::map<std::string,std::string> MEGA_STONES;
   static const std::set<std::string> XY;
   static const std::set<std::string> SM;
   static const std::set<std::string> SS;
   static const std::set<std::string> SV;

   static const std::map<std::string, NaturalGift> BERRIES;

   static std::vector<std::set<std::string>> ITEMS;
   std::vector<std::map<std::string, Item>> ITEMS_BY_ID;

   static const std::map<std::string, ENUMS::StatID> SEED_BOOSTED_STAT;

   static const std::set<std::string> FLING_130;
   static const std::set<std::string> FLING_120;
   static const std::set<std::string> FLING_110;
   static const std::set<std::string> FLING_100;
   static const std::set<std::string> FLING_95;
   static const std::set<std::string> FLING_90;
   static const std::set<std::string> FLING_85;
   static const std::set<std::string> FLING_80;
   static const std::set<std::string> FLING_70;
   static const std::set<std::string> FLING_60;
   static const std::set<std::string> FLING_50;
   static const std::set<std::string> FLING_40;
   static const std::set<std::string> FLING_30;
   static const std::set<std::string> FLING_10;
};
}
}

#endif
