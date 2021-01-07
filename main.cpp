#include "Server.h"


int main()
{
	boost::asio::io_context io_context;
	Server srv(io_context, 15001);
	srv.asyncAccept();
	io_context.run();
	return 0;
}