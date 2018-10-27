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
        , persons(_self, _self)
    {
    }

    /// @abi action
    void vote(std::string name)
    {
        persons.emplace(_self, [&](auto &person) {
            person.name = name;
            person.count++;
            print("candidate=", name, ", count=" , it->count,"\n");
        });
    }

    /// @abi action
    void remove(std::string name)
    {
        auto it = persons.begin() ;
        for( ; it->name != name ; it++ ) ;
        if ( it == persons.end() )
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
        for( auto it : persons ) {
            print("candidate=", it.name, ", count=" , it.count,"\n");
        }
    }

    /// @abi action
    void count(std::string name)
    {
        auto it = persons.begin() ;
        for( ; it->name != name ; it++ ) ;
        if ( it == persons.end() )
        {
            print("can not find candidate=", name, "\n");
            return ;
        }

        print("candidate=", it->name, ", count=" , it->count,"\n");
    }

private:
    struct person {
        std::string name;
        uint32_t count;

        uint64_t primary_key() const { return 0; }

        GRAPHENE_SERIALIZE(person, (name)(count));
    };

    typedef graphene::multi_index<N(person), person> person_index;

    person_index persons;
};

GRAPHENE_ABI(voting, (vote)(remove)(list)(count))
