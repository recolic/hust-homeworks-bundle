

#include "../include/Base.h"
#include "../include/Global.h"
#include "../include/RdtSender.h"
#include "../include/RdtReceiver.h"
#include "../include/StopWaitRdtSender.h"
#include "../include/StopWaitRdtReceiver.h"

#include <rlib/scope_guard.hpp>
#include <rlib/opt.hpp>

int main(int argc, char** argv)
{
	// DO NOT delete them. Or SEGFAULT will happen.
	// rlib_defer([]{delete pUtils; delete pns;});

	rlib::opt_parser args(argc, argv);

	StopWaitRdtSender s;
	StopWaitRdtReceiver r;

	pns->init();
	pns->setRtdSender(&s);
	pns->setRtdReceiver(&r);
	pns->setInputFile(args.getValueArg("-i", "--input").c_str());
	pns->setOutputFile(args.getValueArg("-o", "--output").c_str());
	pns->start();

	return 0;
}

