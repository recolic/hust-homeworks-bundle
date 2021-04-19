

#include "Global.h"

#include "GBNSender.hpp"
#include "GBNReceiver.hpp"

#include <rlib/scope_guard.hpp>
#include <rlib/opt.hpp>
#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
	// DO NOT delete them. Or SEGFAULT will happen.
	// rlib_defer([]{delete pUtils; delete pns;});
    //rlib_defer([]{std::this_thread::sleep_for(1s);});

	rlib::opt_parser args(argc, argv);
	if(args.getBoolArg("-d", "--debug"))
		rlog.set_log_level(rlib::log_level_t::DEBUG);
	if(args.getBoolArg("-v", "--verbose"))
		rlog.set_log_level(rlib::log_level_t::VERBOSE);


	auto winSize = args.getValueArg("-w", "--win", false, "128").as<size_t>();
	GBNSender s(winSize);
	GBNReceiver r(winSize);

	pns->init();
	pns->setRtdSender(&s);
	pns->setRtdReceiver(&r);
	pns->setInputFile(args.getValueArg("-i", "--input").c_str());
	pns->setOutputFile(args.getValueArg("-o", "--output").c_str());
	pns->start();

	return 0;
}

