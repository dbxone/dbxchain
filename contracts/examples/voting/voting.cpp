#include <graphenelib/print.hpp>
#include <graphenelib/contract.hpp>
#include <graphenelib/dispatcher.hpp>
#include <graphenelib/multi_index.hpp>
#include <graphenelib/types.h>
#include <string>
#include <map>

using namespace graphene;

class voting: public contract
{
public:
    voting(uint64_t self)
        : contract(self)
    {
    }

    /// @abi action
    void vote(std::string name)
    {
        auto it = persons.find(name) ;
        if ( it == persons.end() )
        {
            persons[name] = 1;
            return ;
        }

        it->second++;
    }

    /// @abi action
    void remove(std::string name)
    {
        auto it = persons.find(name);
        if( it == persons.end() )
        {
            print("can not find the candidate = ${name}\n", ("name", name));
            return ;
        }

        persons.erase(it);
        print("remove the candidate = ${name}\n", ("name", name));
    }

    /// @abi action
    void list()
    {
        for( auto it : persons ) {
           print("${name}, ${count}\n", ("name", it.first), ("count", it.second));
        }
    }

    /// @abi action
    void count(std::string name)
    {
        auto it = persons.find(name);
        if( it == persons.end() )
        {
            print("can not find the candidate = ${name}\n", ("name", name));
        }

        print("${name}, ${count}\n", ("name", it->first), ("count", it->second));
    }

private:
    std::map<std::string, int> persons;
};

GRAPHENE_ABI(voting, (vote)(remove)(list)(count))
