#include <regex>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <boost/asio.hpp>

#include "random.h"
#include "GamblingMachine.h"

using boost::asio::ip::tcp;

void game::server::worker()
{
	boost::asio::io_service io_service;
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), game::port));

	// wait only on single connection
	tcp::socket sock(io_service);
	a.accept(sock);
	std::thread(&game::server::session, this, std::move(sock)).detach();
}

static std::vector<int> machine_set {1, 2, 3};

void game::server::session(tcp::socket sock)
{
	try
	{
		for (;;)
		{
			char data[max_length] = {0, };
			char response[max_length] = {0, };

			boost::system::error_code error;

			std::fill(data, data + max_length, 0);
			std::fill(response, response + max_length, 0);
			size_t length = sock.read_some(boost::asio::buffer(data), error);

			if (error == boost::asio::error::eof)
				// clean close
				break;
			else if (error)
				throw boost::system::system_error(error);

			std::string cmd(data);
			// transform to lowercase to achieve case insensitive
			std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

			// command parsing
			std::regex randCmd ("^losuj$");
			std::regex exitCmd ("^zamknij$");

			if ( std::regex_match ( cmd.begin(), cmd.end(), randCmd ) )
			{
				auto v = std::vector<int>(3, 0);
				std::transform(v.begin(), v.end(), v.begin(),
						[](auto x) {return *select_randomly(machine_set.begin(), machine_set.end());}
				);
				bool win = std::all_of(v.begin(), v.end(), [&](auto x){return x == v[0];});
				auto print = [](const int& n) { std::cout << " " << n; };

				std::cout << serverTag << " wynik losowania -";
				std::for_each(v.begin(), v.end(), print);
				std::cout << std::endl;

				if (win) {
					std::ostringstream os;
					auto os_print = [&](const int& n) { os << " " << n; };

					os << "wygrana";
					std::for_each(v.begin(), v.end(), os_print);
					os << std::endl;

					// copy win response
					auto result = os.str();
					result.copy(response, result.length());
				}
			}
			else if ( std::regex_match(cmd.begin(), cmd.end(), exitCmd ) )
			{
				// quit thread
				exit(EXIT_SUCCESS);
			}
			else {
				std::cout << "[SERVER]: Unknown command = " << cmd << std::endl;
			}
			boost::asio::write(sock, boost::asio::buffer(response, max_length));
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void game::client::worker()
{
	boost::asio::io_service io_service;

	tcp::socket s(io_service);
	tcp::resolver resolver(io_service);

	try {
		boost::asio::connect(s, resolver.resolve({"127.0.0.1", std::to_string(game::port)}));

		for (;;) {
			std::cout << "[CLIENT]>> ";
			char request[max_length];
			std::cin.getline(request, max_length);
			size_t request_length = std::strlen(request);
			boost::asio::write(s, boost::asio::buffer(request, request_length));

			char reply[max_length];
			size_t reply_length = boost::asio::read(s,
					boost::asio::buffer(reply, max_length));
			if (reply_length != 0) {
				std::string resp(reply);
				if (!resp.empty()) {
					std::cout << "[CLIENT]>> ";
					std::cout.write(reply, reply_length);
				}
			}
		}
	}
	catch (std::exception& e)
	{
		//
		//		std::cerr << "Exception: " << e.what() << "\n";
	}
	finished = true;
}

void game::entity::run()
{
	th = std::thread(&game::entity::worker, this);
}

bool game::entity::isStopped()
{
	return finished;
}

game::entity::~entity()
{
	if (th.joinable())
		th.join();
}
