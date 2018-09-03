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
#pragma once

#include <graphene/chain/protocol/types.hpp>

#include "net.hpp"
#include <string>
#include <vector>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/json.h>
using namespace std;

namespace chaind {

	class chaind
	{
	public:
		string      ms_ip;
		uint32_t    mu_port;

	public:
		chaind() : ms_ip("127.0.0.1"), mu_port(5000) {}
		~chaind() {}
		void set_url( const string& s_ip, const uint32_t u_port );
		void add_blacklist_account(const string& s_json);
		void set_asset_fee( const string& s_json, graphene::chain::share_type& fee_amount );
		void check_in_blacklist( const string& s_json );
	};

}

extern chaind::chaind g_chaind;
