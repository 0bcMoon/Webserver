#include "CGIProcess.hpp"
#include "Event.hpp"
#include "Tokenizer.hpp"
#include <csignal>
#include <cstdio> 
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <unistd.h>

#include <cstring>

#define MAX_EVENTS 128
#define MAX_CONNECTIONS_QUEUE 128
#define CONF_FILE_PATH "webserv.conf"

ServerContext *LoadConfig(const char *path)
{
	ServerContext *ctx = new ServerContext();
	;
	try
	{
		Tokenizer tokenizer;
		tokenizer.readConfig(path);
		tokenizer.CreateTokens();
		tokenizer.parseConfig(ctx);
		ctx->init();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		delete ctx;
		return (NULL);
	}
	return (ctx);
}

static void ctrl_c(int)
{
	Event::Running(1);
}

static void handelSignal()
{
	signal(SIGINT, ctrl_c);
	signal(SIGPIPE, SIG_IGN);
	srand(time(NULL));
}
int main(int ac, char **argv)
{
	handelSignal();
	ServerContext *ctx = NULL;
	if (ac > 2)
	{
		std::cerr << "usage: webserv confile\n";
		return (1);
	}
	else if (ac == 2)
		ctx = LoadConfig(argv[1]);
	else
		ctx = LoadConfig(CONF_FILE_PATH);
	if (!ctx)
		return 1;
	try
	{
		Event event(MAX_CONNECTIONS_QUEUE, MAX_EVENTS, ctx);
		event.init();
		event.Listen();
		event.initIOmutltiplexing();
#ifdef __APPLE__
		event.eventLoop();
#endif // __APPLE__
	}
	catch (const CGIProcess::ChildException &e)
	{
		delete ctx;
		return (1);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << "\n";
	}

	delete ctx;
}
