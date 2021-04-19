

#include "Global.h"

#include "SRSender.hpp"
#include "SRReceiver.hpp"

#include <rlib/scope_guard.hpp>
#include <rlib/opt.hpp>

int main(int argc, char** argv)
{
	// DO NOT delete them. Or SEGFAULT will happen.
	// rlib_defer([]{delete pUtils; delete pns;});

	rlib::opt_parser args(argc, argv);
	if(args.getBoolArg("-d", "--debug"))
		rlog.set_log_level(rlib::log_level_t::DEBUG);
	if(args.getBoolArg("-v", "--verbose"))
		rlog.set_log_level(rlib::log_level_t::VERBOSE);

	auto winSize = args.getValueArg("-w", "--win", false, "128").as<size_t>();
	SRSender s(winSize);
	SRReceiver r(winSize);

	pns->init();
	pns->setRtdSender(&s);
	pns->setRtdReceiver(&r);
	pns->setInputFile(args.getValueArg("-i", "--input").c_str());
	pns->setOutputFile(args.getValueArg("-o", "--output").c_str());
	pns->start();

	return 0;
}

