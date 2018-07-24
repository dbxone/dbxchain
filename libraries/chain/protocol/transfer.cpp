/*
 * Copyright (c) 2015 Cryptonomex, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <graphene/chain/protocol/transfer.hpp>

//liruigang 20180724 add
#include <graphene/chain/database.hpp>
#include <iostream>
#include <string>
#include <rnet.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/json.h>

namespace graphene { namespace chain {

share_type transfer_operation::calculate_fee( const fee_parameters_type& schedule )const
{
   share_type core_fee_required = schedule.fee;
   if( memo )
      core_fee_required += calculate_data_fee( fc::raw::pack_size(memo), schedule.price_per_kbyte );
   return core_fee_required;
}


void transfer_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0 );
   FC_ASSERT( from != to );
   FC_ASSERT( amount.amount > 0 );

   const database& d = db();

   const account_object& from_account    = from(d);
   const account_object& to_account      = to(d);
   const asset_object&   asset_type      = amount.asset_id(d);

   //liruigang 20180724 add
   Json::Value root ;
   root[0] = 1 ;
   root[1] = from_account.name ;
   root[2] = to_account.name ;

   std::cout << "-------------" << from_account.name << std::endl ;
   std::cout << "-------------" << to_account.name << std::endl ;
   std::cout << asset_type.amount_to_string(op.amount) << std::endl ;
   //root[3] = "DBX" ;
   std::string s_write = root.toStyledString() ;
/*
   //liruigang 20180724 add
   Json::Value root ;
   root[0] = 1 ;
   root[1] = std::string(from.operator object_id_type()) ;
   root[2] = std::string(to.operator object_id_type()) ;

   std::cout << std::string(from.operator object_id_type()) << std::endl ;
   std::cout << std::string(to.operator object_id_type()) << std::endl ;
   std::cout << std::string( amount.asset_id.operator object_id_type() ) << std::endl ;
   //root[3] = "DBX" ;
   std::string s_write = root.toStyledString() ;
*/
}



share_type override_transfer_operation::calculate_fee( const fee_parameters_type& schedule )const
{
   share_type core_fee_required = schedule.fee;
   if( memo )
      core_fee_required += calculate_data_fee( fc::raw::pack_size(memo), schedule.price_per_kbyte );
   return core_fee_required;
}


void override_transfer_operation::validate()const
{
   FC_ASSERT( fee.amount >= 0 );
   FC_ASSERT( from != to );
   FC_ASSERT( amount.amount > 0 );
   FC_ASSERT( issuer != from );
}

} } // graphene::chain
