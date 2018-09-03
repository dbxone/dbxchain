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


#include <string>
#include <vector>


namespace chaind {

	namespace net {

#ifndef SOCKET_BUFFER_SIZE
#define SOCKET_BUFFER_SIZE 87380
#endif

		enum RNET_STATUS
		{
			RNET_PROTOCOL = -4,
			RNET_TIMEOUT = -3,
			RNET_CLOSE = -2,
			RNET_ERROR = -1,
			RNET_SMOOTH = 0
		} ;

		int select_rdset( const int i_socket, const int i_second = 20 ) ;
		int select_wrset( const int i_socket, const int i_second = 20 ) ;
		bool connect( int& i_socket, const std::string& ip, const short& port, const int i_second = 20 ) ;
		bool set_nonblocking( const int i_socket );
		void close(const int i_socket );

		int read( const int i_socket, std::vector<char>& v_data, const int i_second = 20 ) ;
		int write( const int i_socket, const std::vector<char>& v_data ) ;
		int write( const int i_socket, const std::string& s_data ) ;
		int write( const int i_socket, const char* p_data, const size_t length ) ;
	}


	namespace json {
		enum JSON_STATUS
		{
			JSON_FAILURE = 0,
			JSON_SUCCESS = 1
		} ;

		int read( const int i_socket, std::vector<char>& v_data, const int i_second = 20 ) ;
		int write( const int i_socket, const std::string& s_data );
		bool write_failure(const int i_socket, const std::string& s_data );
		bool write_success(const int i_socket) ;
	}
}
