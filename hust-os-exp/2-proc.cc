#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <rlib/stdio.hpp>
#include <rlib/opt.hpp>
#include <cassert>

constexpr int msgsize = sizeof(int) / sizeof(char);

struct r_msgbuf {
    long mtype = 1;       /* message type, must be > 0 */
    char mtext[msgsize];    /* message data */
};

void adder(int qid) {
    int a = 0;
    for(auto cter = 1; cter < 101; ++cter) {
        a += cter;

        r_msgbuf buf;
        std::memcpy(buf.mtext, &a, sizeof(a));
        assert(msgsnd(qid, (void *)&buf, msgsize, IPC_NOWAIT) != -1);
    }
    r_msgbuf buf {2}; // EOF message
    assert(msgsnd(qid, (void *)&buf, msgsize, IPC_NOWAIT) != -1);
}

void printer(int qid) {
    while(true) {
        r_msgbuf buf;
        msgrcv(qid, (void *)&buf, msgsize, 0, NULL);

        if(buf.mtype == 2) break; //EOF message type is 2.
        auto a = *(int *)(buf.mtext);
        rlib::println("Current a is", a);
    }
}

int main(int argc, char **argv) {
    rlib::opt_parser args(argc, argv);
    auto key = args.getValueArg("--key", false, "25501").as<key_t>();
    auto qid = msgget(key, IPC_CREAT | 0666);
    assert(qid != -1);

    if(args.getBoolArg("--adder"))
        adder(qid);
    else if(args.getBoolArg("--printer"))
        printer(qid);
    else
        rlib::println("Usage: this --adder/--printer");
}

