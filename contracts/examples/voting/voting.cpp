#include <graphenelib/print.hpp>
#include <graphenelib/contract.hpp>
#include <graphenelib/dispatcher.hpp>
#include <graphenelib/multi_index.hpp>
#include <graphenelib/types.h>
#include <string>
#include <map>

using namespace graphene;

std::string g_str ;

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
        str=name;
        g_str = name ;
        print("voting candidate=", name, "\n");
        auto it = persons.find(name) ;
        if ( it == persons.end() )
        {
            print("create candidate=", name, "\n");
            persons[name] = 1;
            return ;
        }

        it->second++;
        print("candidate=", name, ", count=" , it->second,"\n");
    }

    /// @abi action
    void remove(std::string name)
    {
        auto it = persons.find(name);
        if( it == persons.end() )
        {
            print("can not find candidate=", name, "\n");
            return ;
        }

        persons.erase(it);
        print("remove candidate=", name, "\n");
    }

    /// @abi action
    void list()
    {
        print("str=", str, "\n");
        print("g_str=", g_str, "\n");
        for( auto it : persons ) {
            print("candidate=", it.first, ", count=" , it.second,"\n");
        }
    }

    /// @abi action
    void count(std::string name)
    {
        auto it = persons.find(name);
        if( it == persons.end() )
        {
            print("can not find candidate=", name, "\n");
            return ;
        }

        print("candidate=", it->first, ", count=" , it->second,"\n");
    }

private:
    std::map<std::string, int> persons;

    std::string str;
};

GRAPHENE_ABI(voting, (vote)(remove)(list)(count))
