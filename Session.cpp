#include "Session.h"
#include "Logger.h"

#include <boost/lexical_cast.hpp>

Session::Session(socket_t&& socket) :
	m_socket(std::move(socket))
{
	LOG_INFO(getEndpointString() + " connected to the server\n");
}

void Session::start(message_handler&& on_message, error_handler&& on_error)
{
	this->on_message = std::move(on_message);
	this->on_error = std::move(on_error);
	asyncRead();
}

std::string Session::getEndpointString()
{
	return m_socket.remote_endpoint().address().to_string() + ":" + boost::lexical_cast<std::string>(m_socket.remote_endpoint().port());
}

void Session::post(const std::string& command)
{
	bool idle = m_outgoing.empty();
	m_outgoing.push(command);

	if (idle)
		asyncWrite();
}

void Session::asyncRead()
{
	io::async_read_until(m_socket, m_buffer, "\n",
		[self = shared_from_this()](error_code error, size_t bytes)
	{
		self->onRead(error, bytes);
	});
}

void Session::asyncWrite()
{
	io::async_write(m_socket, io::buffer(m_outgoing.front()),
		[self = shared_from_this()](error_code error, size_t bytes)
	{
		self->onWrite(error, bytes);
	});
}

void Session::onRead(error_code error, size_t bytes)
{
	if (!error)
	{
		std::ostringstream command;
		command << &m_buffer;
		auto result = Utility::parse(command.str());
		if (Utility::validateCommand(result))
		{
			if (Utility::toLowerCase(result.at(0)) == "put")
			{
				Data d(result.at(2), result.at(3));
				Storage::getInstance().add(Utility::trim(result.at(1)), d);
				post("OK\n\r");
			}
			else if (Utility::toLowerCase(result.at(0)) == "get")
			{
				auto message = Storage::getInstance().get(result.at(1));
				post(message);
				post("OK\n\r");
			}
			else
			{
				LOG_DEBUG("Unknown command: " + command.str());
				post("Error: Unknown command\n\r");
			}
		}
		else
		{
			LOG_DEBUG("Unknown command: " + command.str());
			post("Error: Unknown command\n\r");
		}

		asyncRead();
	}
	else
	{
		LOG_ERROR("Error: " + error.message());
		m_socket.close(error);
		on_error();
	}
}

void Session::onWrite(error_code error, size_t bytes)
{
	if (!error)
	{
		m_outgoing.pop();

		if (!m_outgoing.empty())
			asyncWrite();
	}
}