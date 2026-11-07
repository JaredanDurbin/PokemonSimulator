#include <map>
#include <optional>
#include <string>

class foo
{
private:
   struct MoveData
   {
      std::optional<std::string> a = std::nullopt;
      std::optional<std::string> b = std::nullopt;
      std::optional<std::string> c = std::nullopt;
      std::optional<std::string> d = std::nullopt;
   };

   static std::map<std::string, MoveData> RBY;
public:
   foo();
   ~foo();
};

foo::foo() {};
foo::~foo() {};

std::map<std::string, foo::MoveData> foo::RBY = 
{
   {"absorb", {.a = "sadf", .c = "dsaf"}},
   {"aso", {.b = "af", .d = "df"}}
};

int main()
{
   return 0;
}