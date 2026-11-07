#include <set>
#include <ranges>
#include <vector>
#include <list>
#include <iostream>

template <typename T>
std::set<T> SetUnion(const std::set<T>& a, const std::set<T>& b)
{
   std::set<T> result = a;
   result.insert(std::begin(b), std::end(b));

   return result;
}

int main() {
   std::set<std::string> s = {"AASD", "ASDA", "TSFDG"};

   std::vector<std::string> v = {"SDAFSD", "SADFAS", "TSFDSBFS"};
   std::list<std::string> l = {"ADVASX", "AAFDSAHGD", "KJHFDSA"};

   //auto r1 = SetUnion(s, v);
   //auto r2 = SetUnion(s, l);
   auto r3 = SetUnion(s, std::set<std::string>{"YTDDSAF", "ASDFAFSSDF", "SADFACS"});

   for (auto x : r3) {
      std::cout << x << " ";
   }
}