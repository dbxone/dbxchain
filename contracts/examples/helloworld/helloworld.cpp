#include <dbxlib/contract.hpp>
#include <dbxlib/dispatcher.hpp>
#include <dbxlib/print.hpp>
#include <dbxlib/types.h>

using namespace graphene;

class helloworld : public contract
{
  public:
    helloworld(uint64_t id)
        : contract(id)
    {
    }

    /// @abi action
    void hi(std::string user)
    {
        for (int i = 0; i < 2; ++i) {
            print("hi, ", user, "\n");
        }
    }
};

GRAPHENE_ABI(helloworld, (hi))
