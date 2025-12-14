#include <iostream>
#include <string>
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main()
{
    zmq::context_t ctx(1);                          
    zmq::socket_t  subscriber(ctx, zmq::socket_type::sub);
    subscriber.connect("ipc:///tmp/zmq_ipc_demo");
    subscriber.set(zmq::sockopt::subscribe, "A");
    subscriber.set(zmq::sockopt::subscribe, "B");

    while (true)
    {

        // Receive all parts of the message
        std::vector<zmq::message_t> recv_msgs;
        zmq::recv_result_t          result = zmq::recv_multipart(subscriber, std::back_inserter(recv_msgs));
        for (auto& msg : recv_msgs)
        {
            std::cout << msg.to_string() << std::endl;
        }
    }
    return 0;
}
