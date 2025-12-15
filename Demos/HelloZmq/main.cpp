#include <iostream>
#include <string>
#include <zmq.hpp>
#include <zmq_addon.hpp>

int main()
{
    zmq::context_t context(1);                          
    zmq::socket_t     subscriber(context, zmq::socket_type::sub);
    const std::string address = "tcp://127.0.0.1:5555";
    subscriber.connect(address);
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
