
#include <fc/exception/exception.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/json.h>

#include "net.hpp"
#include "chaind.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std ;

chaind::chaind g_chaind;

namespace chaind {

	void chaind::set_url( const string& s_ip, const uint32_t u_port )
	{
		this->ms_ip = s_ip;
		this->mu_port = u_port;
	}

	void chaind::add_blacklist_account(const string& s_json)
	{
		std::cout << "net::connect server(" << ms_ip << ":" << mu_port << ")" << std::endl;

		int i_socket = -1;
		if( !net::connect( i_socket, ms_ip, mu_port ) )
		{
			std::cerr << "net::connect server(" << ms_ip << ":" << mu_port << ") error" << std::endl;
			if ( i_socket != -1 )
				net::close(i_socket);
			FC_ASSERT( false, "connect chaind service error" );
		}

		if( json::write( i_socket, s_json ) < 0 )
		{
			std::cerr << "json::write server(" << i_socket << ") error" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "write chaind service error" );
		}

		std::vector<char> v_read ;
		int ret = json::read( i_socket, v_read, 0 ) ;
		if ( ret != net::RNET_SMOOTH )
		{
			std::cerr << "json::read() failure" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "read chaind service error" );
		}

		string s_read(v_read.begin(), v_read.end());
		std::cout << "s_read = " << std::endl << s_read << std::endl;

		Json::Value parse_root ;
		Json::Reader reader ;

		if ( !reader.parse( s_read, parse_root ) )
		{
			std::cerr << "rjson::parse json error" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "rjson::parse json error" );
		}

		if( parse_root[0].asInt() != 1 )
		{
			std::cerr << "blacklistd service record error" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "chaind service error : ${error}", ("error", parse_root[1].asString()) );
		}

		net::close(i_socket);
	}

	void chaind::set_asset_fee( const string& s_json, graphene::chain::share_type& fee_amount )
	{
		std::cout << "net::connect server(" << ms_ip << ":" << mu_port << ")" << std::endl;

		int i_socket = -1;
		if( !net::connect( i_socket, ms_ip, mu_port ) )
		{
			std::cerr << "net::connect server(" << ms_ip << ":" << mu_port << ") error" << std::endl;
			if ( i_socket != -1 )
				net::close(i_socket);
			FC_ASSERT( false, "connect blacklistd service error" );
		}

		if( json::write( i_socket, s_json ) < 0 )
		{
			std::cerr << "json::write server(" << i_socket << ") error" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "write blacklistd service error" );
		}

		std::vector<char> v_read ;
		int ret = json::read( i_socket, v_read, 0 ) ;
		if ( ret != net::RNET_SMOOTH )
		{
			std::cerr << "json::read() failure" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "read blacklistd service error" );
		}

		string s_read(v_read.begin(), v_read.end());
		std::cout << "s_read = " << std::endl << s_read << std::endl;

		Json::Value parse_root ;
		Json::Reader reader ;

		if ( !reader.parse( s_read, parse_root ) )
		{
			std::cerr << "rjson::parse json error" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "rjson::parse json error" );
		}

		if( parse_root[0].asInt() != 1 )
		{
			std::cerr << "blacklistd service record error" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "blacklistd service error : ${error}", ("error", parse_root[1].asString()) );
		}

		net::close(i_socket);

		fee_amount.value = parse_root[1].asInt64();
	}

	void chaind::check_in_blacklist( const string& s_json )
	{
		std::cout << "net::connect server(" << ms_ip << ":" << mu_port << ")" << std::endl;

		int i_socket = -1;
		if( !net::connect( i_socket, ms_ip, mu_port ) )
		{
			std::cerr << "net::connect server(" << ms_ip << ":" << mu_port << ") error" << std::endl;
			if ( i_socket != -1 )
				net::close(i_socket);
			FC_ASSERT( false, "connect blacklistd service error" );
		}

		if( json::write( i_socket, s_json ) < 0 )
		{
			std::cerr << "json::write server(" << i_socket << ") error" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "write blacklistd service error" );
		}

		std::vector<char> v_read ;
		int ret = json::read( i_socket, v_read, 0 ) ;
		if ( ret != net::RNET_SMOOTH )
		{
			std::cerr << "json::read() failure" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "read blacklistd service error" );
		}

		std::string s_read(v_read.begin(), v_read.end());
		std::cout << "s_read = " << std::endl << s_read << std::endl;

		Json::Value parse_root ;
		Json::Reader reader ;

		if ( !reader.parse( s_read, parse_root ) )
		{
			std::cerr << "rjson::parse json error" << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "rjson::parse json error" );
		}

		if( parse_root[0].asInt() != 1 )
		{
			std::cerr << "blacklistd service error : " << parse_root[1].asString() << std::endl ;
			net::close(i_socket);
			FC_ASSERT( false, "blacklistd service error : ${error}", ("error", parse_root[1].asString()) );
		}

		net::close(i_socket);
	}
}
