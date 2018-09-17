#include <dbxlib/action.h>
#include <dbxlib/action.hpp>
#include <dbxlib/contract.hpp>
#include <dbxlib/dispatcher.hpp>
#include <dbxlib/print.hpp>

using namespace graphene;

class contractb : public contract
{
  public:
    contractb(uint64_t uname)
        : contract(uname)
    {
    }

    /// @abi action
    void hi()
    {
        printf("hi");
    }
};

GRAPHENE_ABI(contractb, (hi))
