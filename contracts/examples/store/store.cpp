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
    }
    
	/// @abi action
    void set()
    {
		i=3;
    }

	
    /// @abi action
    void show()
    {
		print("i=", i, "\n");
    }

	uint32_t i;
};

GRAPHENE_ABI(store, (set)(show))
