#include <dbxlib/contract.hpp>
#include <dbxlib/crypto.h>
#include <dbxlib/dispatcher.hpp>
#include <dbxlib/print.hpp>
#include <dbxlib/types.h>
#include <dbxlib/global.h>

using namespace graphene;

class verify_sign : public contract
{
  public:
    verify_sign(uint64_t id)
        : contract(id)
    {
    }

    void verify(std::string raw_string, std::string pub_key, signature sig)
    {
        print("string, ", raw_string, "\n");
        print(pub_key, "\n");
        bool flag = verify_signature(raw_string.c_str(), raw_string.length(), &sig, pub_key.c_str(), pub_key.length());
        print("ret code, ", flag, "\n");
    }
};

GRAPHENE_ABI(verify_sign, (verify))
