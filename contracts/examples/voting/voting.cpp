#include <graphenelib/print.hpp>
#include <graphenelib/contract.hpp>
#include <graphenelib/dispatcher.hpp>
#include <graphenelib/multi_index.hpp>
#include <graphenelib/types.h>
#include <string>

using namespace graphene;

class voting: public contract
{
public:
    voting(uint64_t self)
        : contract(self), persons(_self, _self)
    {
    }

    /// @abi action
    bool vote(std::string name)
    {
        persons.emplace(_self, [&](auto &person) {
            person.name = name;
            person.count++;
        });

        return true ;
    }

    /// @abi action
    bool remove(std::string name)
    {
        auto it = persons.find(name);
        if( it == persons.end() )
        {
            print("can not find the candidate = ${name}\n", ("name", name));
            return false ;
        }

        persons.erase(it);
        print("remove the candidate = ${name}\n", ("name", name));
        return true ;
    }

    /// @abi action
    void list()
    {
        for( auto it : persons ) {
           print("${name}, ${count}\n", ("name", it->name), ("count", it->count));
        }
    }

    /// @abi action
    uint32_t count(std::string name)
    {
        auto it = persons.find(name);
        if( it == persons.end() )
        {
            print("can not find the candidate = ${name}\n", ("name", name));
            return 0 ;
        }

        print("${name}, ${count}\n", ("name", it->name), ("count", it->count));

        return it->count;
    }

private:
    struct person {
        std::string name;
        uint32_t count;

        std::string primary_key() const { return name; }

        GRAPHENE_SERIALIZE(person, (name)(count))
    };

    typedef graphene::multi_index<N(person), person> person_index;

    person_index persons;
};

GRAPHENE_ABI(voting, (hi))
