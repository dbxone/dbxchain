#include <graphenelib/contract.hpp>
#include <graphenelib/dispatcher.hpp>
#include <graphenelib/print.hpp>
#include <graphenelib/types.h>
#include <graphenelib/action.h>
#include <graphenelib/global.h>
#include <graphenelib/asset.h>

using namespace graphene;

class transfer : public contract
{
	public:
		transfer(uint64_t id)
			: contract(id)
		{
		}

		void show(std::string account_to, std::string asset, uint64_t amount)
		{
			print("get_head_block_num=", get_head_block_num(), "\n");
			print("get_head_block_time=", get_head_block_time(), "\n");
			print("get_trx_sender=", get_trx_sender(), "\n");

			print("current_receiver=", current_receiver(), "\n");
			print("get_action_asset_id=", get_action_asset_id(), "\n");
			print("get_action_asset_amount=", get_action_asset_amount(), "\n");
			print("get_balance=", get_balance(current_receiver(), get_action_asset_id()), "\n");

			print("account_to=", account_to, ", id=", get_account_id(account_to.c_str(),account_to.length()), "\n");
			print("asset=", asset, ", id=", get_asset_id(asset.c_str(), asset.length()), "\n");
			print("amount=", amount, "\n");
		}

		/// @abi action
		void recept(std::string account_to, std::string asset, uint64_t amount)
		{
			print("get_head_block_num=", get_head_block_num(), "\n");
			print("get_head_block_time=", get_head_block_time(), "\n");
			print("get_trx_sender=", get_trx_sender(), "\n");

			print("current_receiver=", current_receiver(), "\n");
			print("get_action_asset_id=", get_action_asset_id(), "\n");
			print("get_action_asset_amount=", get_action_asset_amount(), "\n");
			print("get_balance=", get_balance(current_receiver(), get_action_asset_id()), "\n");

			print("account_to=", account_to, ", id=", get_account_id(account_to.c_str(),account_to.length()), "\n");
			print("asset=", asset, ", id=", get_asset_id(asset.c_str(), asset.length()), "\n");
			print("amount=", amount, "\n");

			printf("------- start transfer -----\n");
			withdraw_asset(current_receiver(), get_account_id(account_to.c_str(),account_to.length()),  get_asset_id(asset.c_str(), asset.length()), amount);
		}
};

GRAPHENE_ABI(transfer, (recept)(show))
