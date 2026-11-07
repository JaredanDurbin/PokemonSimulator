#include "./../include/util/util.h"

#include <iostream>
#include <vector>


namespace PokemonDamageCalcCPP
{
namespace Util
{

void ErrorCheckingDoWhile(std::string statement, 
                           auto &in, 
                           std::function<bool()> condition)
{
   do
   {
      std::cout << statement;
      std::cin >> in;
   } 
   while (condition());      
}

std::string ToID(const std::string& text)
{
   std::string result;

   for (char c : text) 
   {
      c = std::tolower(static_cast<unsigned char>(c));

      if (std::isalnum(static_cast<unsigned char>(c))) 
      {
         result += c;
      }
   }

   return result;
}

uint32_t tr(double num, int bits)
{
   uint32_t value = static_cast<uint32_t>(num);

   if (bits) 
   {
      return value % (1u << bits);
   }

   return value;
}

std::string AppendIfSet
(
   std::string str,
   const std::optional<std::string>& to_append
)
{
   return to_append ? str + *to_append + " " : str;
}

std::string SerializeText(std::vector<std::string>& arr)
{
   if (arr.size() == 0) 
   {
      return "";
   } 
   else if (arr.size() == 1) 
   {
      return arr[0];
   } else if (arr.size() == 2) 
   {
      return arr[0] + " and " + arr[1];
   } 
   else 
   {
      std::string text = "";
      for (int i = 0; i < arr.size() - 1; i++) 
      {
         text += arr[i] + ", ";
      }
      return text + "and " + arr[arr.size() - 1];
   }

   return "";
}

std::string ToLower(std::string s)
{
    std::transform
    (
      s.begin(),
      s.end(),
      s.begin(),
      [](unsigned char c) 
      {
         return std::tolower(c);
      }
    );

    return s;
}

}
}

