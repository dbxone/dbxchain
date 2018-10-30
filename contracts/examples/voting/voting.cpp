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
		, candidates(_self, _self)
    {
    }

    /// @abi action
    void vote(uint64_t id, std::string name)
    {
		auto it = candidates.find(id) ;
		if ( it == candidates.end() ) {
			candidates.emplace(_self, [&](auto &candidate) {
				candidate.id = id ;
				candidate.name = name;
				candidate.count = 1;
				print("id=" , id, ", name=", name,  ", count=" , candidate.count,"\n");
			});
		}
		else {
			candidates.modify(it, _self, [&](auto &candidate) {
				candidate.count++ ;
			});
			print("id=" , it->id, ", name=", it->name,  ", count=" , it->count,"\n");
		}
    }

    /// @abi action
    void remove(uint64_t id)
    {
		const auto &it = candidates.find(id);
		if ( it == candidates.end() )
        {
			print("can not find name=", id, "\n");
            return ;
        }

		print("remove name=", it->name, "\n");
		candidates.erase(it);
    }

    /// @abi action
    void list()
    {
		for( auto it : candidates ) {
			print("id=", it.id, ", name=", it.name, ", count=" , it.count,"\n");
        }
    }

    /// @abi action
    void count(uint64_t id)
    {
		const auto &it = candidates.find(id);
		if ( it == candidates.end() )
        {
			print("can not find name=", id, "\n");
            return ;
        }

		print("id=", it->id, ", name=", it->name, ", count=" , it->count,"\n");
    }

private:
	struct candidate {
        uint64_t id;
        std::string name;
        uint32_t count;

        uint64_t primary_key() const { return id; }

		GRAPHENE_SERIALIZE(candidate, (id)(name)(count));
    };

	typedef graphene::multi_index<N(candidate), candidate> candidate_index;

	candidate_index candidates;
};

GRAPHENE_ABI(voting, (vote)(remove)(list)(count))
