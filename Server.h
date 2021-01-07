#ifndef SERVER_H
#define SERVER_H

#include "Session.h"

#include <memory>
#include <unordered_set>
#include <unordered_map>

#include <boost/optional.hpp>


class Server
{
public:
	typedef boost::asio::ip::tcp::acceptor acceptor_t;
	typedef boost::asio::ip::tcp::endpoint endpoint_t;

public:
	Server(boost::asio::io_context& io_context, short port);

	void post(const std::string& message);

	void asyncAccept();

private:
	boost::asio::io_context&				m_ctx;
	acceptor_t								m_acceptor;
	boost::optional<Session::socket_t>		m_socket;
	std::unordered_set<Session::pointer_t>	m_clients;
	//std::unordered_map<Utility::Data>		m_storage;
};


#endif