#include "Server.h"


Server::Server(boost::asio::io_context& io_context, short port) :
	m_ctx(io_context),
	m_acceptor(m_ctx, endpoint_t(boost::asio::ip::tcp::v4(), port))
{
}

void Server::post(const std::string& message)
{
	for (auto& client : m_clients)
	{
		client->post(message);
	}
}

void Server::asyncAccept()
{
	m_socket.emplace(m_ctx);

	m_acceptor.async_accept(*m_socket, [&](error_code ec)
		{
			auto client = std::make_shared<Session>(std::move(*m_socket));
			client->post("Welcome to the server\n\r");
			post("We have a new user\n\r");
			m_clients.insert(client);
			logInfo(client->getEndpointString() + " connected to the server");
			client->start
			(
				boost::bind(&Server::post, this, _1),
				[&, shared = client->shared_from_this()]
				{
					if (shared && m_clients.erase(shared))
					{
						post("We are one less\n\r");
					}
				}
			);

			asyncAccept();
		});
}