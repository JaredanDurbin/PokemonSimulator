#ifndef POKEMON_DAMAGE_CALC_CPP_UTIL_H
#define POKEMON_DAMAGE_CALC_CPP_UTIL_H

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <functional>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <vector>
#include <optional>

namespace PokemonDamageCalcCPP
{
namespace Util
{

/// @brief This function will do some error checking for us.
/// @param statement The statement to say to the user.
/// @param in The variable they will write into.
/// @param condition The condition to check for.
void ErrorCheckingDoWhile(std::string statement, 
                           auto &in, 
                           std::function<bool()> condition);

std::string ToID(const std::string& text);

template <typename T, typename Any>
inline std::set<T> GetMapKeys(const std::map<T, Any>& a)
{
   std::set<T> keys;
   for (typename std::map<T, Any>::const_iterator it = a.begin(); it != a.end(); ++it) 
   {
      keys.insert(it->first);
   }

   return keys;
}

template <typename T>
inline std::set<T> SetDifference(const std::set<T>& a, const std::set<T>& b)
{
   std::set<T> result = a;
   std::set_difference(std::begin(a), std::end(a), 
                       std::begin(b), std::end(b),
                       std::inserter(result, result.end()));

   return result;
}

template <typename T>
inline std::set<T> SetUnion(const std::set<T>& a, const std::set<T>& b)
{
   std::set<T> result = a;
   result.insert(std::begin(b), std::end(b));

   return result;
}

uint32_t tr(double num, int bits = 0);

std::string AppendIfSet
(
   std::string str,
   const std::optional<std::string>& to_append
);

std::string SerializeText(std::vector<std::string>& arr);

std::string ToLower(std::string s);

}
}



#endif
