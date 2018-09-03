
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

#include <iostream>
#include <vector>
#include <string>

namespace chaind {

	namespace net {

		int select_rdset( const int i_socket, const int i_second )
		{
			timeval tv ;
			tv.tv_sec = i_second ;
			tv.tv_usec = 0L ;

			fd_set rdset;
			FD_ZERO( &rdset );
			FD_SET( i_socket, &rdset );

			int ret = ::select( i_socket + 1, &rdset, NULL, NULL, &tv ) ;

			if( ret < 0 )
			{
				std::cerr << "select(" << i_socket << ") error : " << strerror( errno )  << std::endl ;
				return	RNET_ERROR ;
			}

			if( ret == 0 )
			{
				std::cerr << "select(" << i_socket << ") timeout" << std::endl ;
				return	RNET_TIMEOUT ;
			}

			return RNET_SMOOTH ;
		}

		int select_wrset( const int i_socket, const int i_second )
		{
			timeval tv ;
			tv.tv_sec = i_second ;
			tv.tv_usec = 0L ;

			fd_set wrset;
			FD_ZERO( &wrset );
			FD_SET( i_socket, &wrset );

			int ret = ::select( i_socket + 1, NULL, &wrset, NULL, &tv ) ;

			if( ret < 0 )
			{
				std::cerr << "select(" << i_socket << ") error : " << strerror(errno)  << std::endl ;
				return	RNET_ERROR ;
			}

			if( ret == 0 )
			{
				std::cerr << "select(" << i_socket << ") timeout" << std::endl ;
				return	RNET_TIMEOUT ;
			}

			return RNET_SMOOTH ;
		}

		bool connect( int& i_socket, const std::string& ip, const short& port, const int i_second )
		{
			i_socket = ::socket( AF_INET, SOCK_STREAM, 0 ) ;
			if( i_socket < 0 )
			{
				std::cerr << "socket() error : " << strerror(errno)  << std::endl ;
				return	false ;
			}

			sockaddr_in serv_addr = { 0x00 } ;
			bzero(&serv_addr, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET ;
			serv_addr.sin_port = htons( port ) ;
			serv_addr.sin_addr.s_addr = inet_addr( ip.c_str( ) ) ;

			timeval tv ;
			tv.tv_sec = i_second ;
			tv.tv_usec = 0L ;
			::setsockopt( i_socket, SOL_SOCKET, SO_SNDTIMEO, &tv,sizeof(tv) );

			if ( ::connect( i_socket, reinterpret_cast<sockaddr*>( &serv_addr ), sizeof( sockaddr ) ) < 0 )
			{
				std::cerr << "connect(" << i_socket << ") error : " << strerror(errno)  << std::endl ;
				return	false ;
			}

			return	true ;
		}

		bool set_nonblocking( const int i_socket )
		{
			int opts;
			opts = fcntl( i_socket, F_GETFL );
			if( opts < 0 )
			{
				std::cerr << "fcntl(" << i_socket << ") error : " << strerror(errno) << std::endl;
				return	false;
			}
			opts = opts | O_NONBLOCK;
			if( fcntl( i_socket, F_SETFL, opts ) < 0 )
			{
				std::cerr << "fcntl(" << i_socket << ") non-block error : " << strerror(errno) << std::endl;
				return false ;
			}

			return	true ;
		}

		void close(const int i_socket )
		{
			::close(i_socket);
		}

		int read( const int i_socket, std::vector<char>& v_data, const int i_second )
		{
			while ( true )
			{
				if ( i_second != 0 )
				{
					int ret = chaind::net::select_rdset( i_socket, i_second ) ;
					if ( ret < RNET_SMOOTH )
					{
						std::cerr << "chaind::net::select_rdset(" << i_socket << ") error" << std::endl ;
						return ret ;
					}
				}

				char buffer[SOCKET_BUFFER_SIZE] = { 0x00 } ;
				int ret = ::read( i_socket, buffer, SOCKET_BUFFER_SIZE ) ;
				if( ret < 0 )
				{
					std::cerr << "read(" << i_socket << ") error : " << strerror(errno) << std::endl;

					if( errno == EINTR )
						continue ;

					if( errno == EAGAIN )
						continue;

					return	RNET_ERROR ;
				}

				if ( ret == 0 )
				{
					std::cerr << "read(" << i_socket << ") peer closed" << std::endl ;
					return	RNET_CLOSE ;
				}

				copy( buffer, buffer+ret, back_inserter( v_data ) ) ;
				break ;
			}

			return	RNET_SMOOTH ;
		}

		int write( const int i_socket, const std::vector<char>& v_data )
		{
			if (v_data.empty())
			{
				std::cerr << "data empty" << std::endl ;
				return  RNET_ERROR;
			}

			return write( i_socket, &v_data[0], v_data.size()) ;
		}

		int write( const int i_socket, const std::string& s_data )
		{
			if (s_data.empty())
			{
				std::cerr << "data empty" << std::endl ;
				return  RNET_ERROR;
			}

			return write( i_socket, s_data.c_str(), s_data.size()) ;
		}

		int write( const int i_socket, const char* p_data, const size_t length )
		{
			if (p_data == NULL)
			{
				std::cerr << "data empty" << std::endl ;
				return  RNET_ERROR;
			}

			std::size_t numbytes = 0 ;
			for( std::size_t i = 0 ; numbytes < length; ++i )
			{
				int ret = ::write( i_socket, p_data+numbytes, length-numbytes ) ;
				if( ret == -1 )
				{
					if( errno == EINTR )
						continue ;

					if( errno == EAGAIN )
						continue ;

					std::cerr << "write(" << i_socket << ") error : " << strerror( errno )  << std::endl ;
					return	RNET_ERROR ;
				}
				numbytes += ret ;
			}

			return	numbytes ;
		}
	}

	namespace json {

		int read( const int i_socket, std::vector<char>& v_data, const int i_second )
		{
			v_data.clear() ;

			int length = 0 ;

			while ( true )
			{
				if ( i_second != 0 )
				{
					int ret = chaind::net::select_rdset( i_socket, i_second ) ;
					if ( ret < net::RNET_SMOOTH )
					{
						std::cerr << "chaind::net::select_rdset(" << i_socket << ") error" << std::endl ;
						return ret ;
					}
				}

				char buffer[5] = { 0x00 } ;
				int ret = ::read( i_socket, buffer, 4 ) ;
				if( ret < 0 )
				{
					std::cerr << "read(" << i_socket << ") error : " << strerror( errno ) << std::endl;

					if( errno == EINTR )
						continue ;

					if( errno == EAGAIN )
						continue ;

					return	net::RNET_ERROR ;
				}

				if ( ret == 0 )
				{
					std::cerr << "read(" << i_socket << ") peer closed" << std::endl ;
					return	net::RNET_CLOSE ;
				}

				memcpy( (char*)&length, buffer, 4 ) ;
				break ;
			}


			while ( true )
			{
				if ( i_second != 0 )
				{
					int ret = chaind::net::select_rdset( i_socket, i_second ) ;
					if ( ret < net::RNET_SMOOTH )
					{
						std::cerr << "chaind::net::select_rdset(" << i_socket << ") error" << std::endl ;
						return ret ;
					}
				}

				char buffer[SOCKET_BUFFER_SIZE] = { 0x00 } ;
				int ret = ::read( i_socket, buffer, length ) ;
				if( ret < 0 )
				{
					std::cerr << "read(" << i_socket << ") error : " << strerror( errno ) << std::endl;

					if( errno == EINTR )
						continue ;

					if( errno == EAGAIN )
						continue ;

					return	net::RNET_ERROR ;
				}

				if ( ret == 0 )
				{
					std::cerr << "read(" << i_socket << ") peer closed" << std::endl ;
					return	net::RNET_CLOSE ;
				}

				copy( buffer, buffer+ret, back_inserter( v_data ) ) ;

				length -= ret ;
				if ( length > 0 )
					continue ;

				break ;
			}

			return	net::RNET_SMOOTH ;
		}

		int write( const int i_socket, const std::string& s_data )
		{
			if (s_data.empty())
			{
				std::cerr << "data empty" << std::endl ;
				return  net::RNET_ERROR;
			}

			char buffer[SOCKET_BUFFER_SIZE] = { 0x00 } ;
			unsigned int length = s_data.size() ;
			memcpy( buffer, (char*)&length, 4 ) ;
			memcpy( buffer+4, s_data.c_str(), length ) ;

			return chaind::net::write( i_socket, buffer, length+4 ) ;
		}

		bool write_failure( const int i_socket, const std::string& s_data )
		{
			if (s_data.empty())
			{
				std::cerr << "data empty" << std::endl ;
				return false;
			}

			Json::Value root;
			root["error_reason"] = s_data ;
			std::string json = root.toStyledString();
			if ( chaind::json::write( i_socket, json ) < 0  )
			{
				std::cerr << "chaind::json::write(" << i_socket << ") error" << std::endl ;
				return false ;
			}

			std::cerr << "chaind::json::write(" << i_socket << ") failure data" << std::endl << json << std::endl;

			return true ;
		}

		bool write_success( const int i_socket )
		{
			Json::Value root;
			root["success"] = JSON_SUCCESS;
			std::string json = root.toStyledString();
			if ( chaind::json::write( i_socket, json ) < 0  )
			{
				std::cerr << "chaind::json::write(" << i_socket << ")error" << std::endl ;
				return false ;
			}

			std::cerr << "chaind::json::write(" << i_socket << ") success data" << std::endl << json << std::endl;

			return true ;
		}
	}
}
