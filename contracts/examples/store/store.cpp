#include <graphenelib/graphene.hpp>
#include <graphenelib/contract.hpp>
#include <graphenelib/dispatcher.hpp>
#include <graphenelib/print.hpp>
#include <graphenelib/types.h>

using namespace graphene;

class store : public contract
{
  public:
    store(uint64_t id)
        : contract(id)
    {
	user="aaaaaaaa";
    }

    /// @abi action
    void hi()
    {
            print("hi, ", user, "\n");
    }

    std::string user;
};

GRAPHENE_ABI(store, (hi))
