#include <iostream>
#include <string>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
using std::cout;
using std::endl;
using std::string;
string run(string cmd);

typedef websocketpp::server<websocketpp::config::asio> server;

server print_server;

void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
    cout << "CMD ARRIVED>" << msg->get_payload() << endl;
    print_server.send(hdl, run(msg->get_payload()), websocketpp::frame::opcode::text);
}

int main() {
    print_server.set_message_handler(&on_message);

    print_server.init_asio();
    print_server.listen(25568);
    print_server.start_accept();
    cout << "Make sure ./chw-cli exist and permission x is on.\nServer working..." << endl;

    print_server.run();
    cout << "Server exited." << endl;
    return 0;
}
