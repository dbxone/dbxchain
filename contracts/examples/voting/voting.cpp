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
    void vote(uint64_t id, std::string name)
    {
        persons.emplace(_self, [&](auto &person) {
            person.id = id ;
            person.name = name;
            person.count++;
			print("name=", name, ", id=" , id, ", count=" , person.count,"\n");
        });
    }

    /// @abi action
    void remove(uint64_t id)
    {
        const auto &it = persons.find(id);
        if ( it == persons.end() )
        {
			print("can not find name=", id, "\n");
            return ;
        }

		print("remove name=", it->name, "\n");
        persons.erase(it);
    }

    /// @abi action
    void list()
    {
        for( auto it : persons ) {
			print("id=", it.id, ", name=", it.name, ", count=" , it.count,"\n");
        }
    }

    /// @abi action
    void count(uint64_t id)
    {
        const auto &it = persons.find(id);
        if ( it == persons.end() )
        {
			print("can not find name=", id, "\n");
            return ;
        }

		print("id=", it->id, ", name=", it->name, ", count=" , it->count,"\n");
    }

private:
    struct person {
        uint64_t id;
        std::string name;
        uint32_t count;

        uint64_t primary_key() const { return id; }

		GRAPHENE_SERIALIZE(person, (id)(name)(count));
    };

    typedef graphene::multi_index<N(person), person> person_index;

    person_index persons;
};

GRAPHENE_ABI(voting, (vote)(remove)(list)(count))
