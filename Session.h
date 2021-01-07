#ifndef SESSION_H
#define SESSION_H

#include "Utility.h"
#include "Storage.h"

#include <iostream>
#include <queue>

#include <boost/asio.hpp>
#include <boost/bind.hpp>


namespace io = boost::asio;
using tcp = io::ip::tcp;
using error_code = boost::system::error_code;

using message_handler = std::function<void(std::string)>;
using error_handler = std::function<void()>;


class Session : public std::enable_shared_from_this<Session>
{
public:
	typedef tcp::socket					socket_t;
	typedef io::streambuf				buf_t;
	typedef std::shared_ptr<Session>	pointer_t;

public:
	Session(socket_t&& socket);

	void start(message_handler&& on_message, error_handler&& on_error);

	void post(const std::string& command);
	void asyncRead();
	void asyncWrite();
	void onRead(error_code error, size_t bytes);
	void onWrite(error_code error, size_t bytes);

private:
	socket_t				m_socket;
	buf_t					m_buffer;
	std::queue<std::string>	m_outgoing;
	message_handler			on_message;
	error_handler			on_error;

};

#endif