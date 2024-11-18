#ifdef USE_FIFO_FILE
#include "fifo_names.hpp"
#elif defined(USE_MQ_FILE)
#include "mq_names.hpp"
#elif defined(USE_SHM_FILE)
#include "shm_names.hpp"
#endif

using namespace client_namespace;

namespace
{
    TempClient client = TempClient::get_instance(host_pid_path, identifier);
}
void client_signal_handler(int sig, siginfo_t *info, void *context)
{
    std::cout << "signal was handled" << std::endl;
    static std::string msg;
    static std::string msg_general;
    switch (sig)
    {
    case SIGUSR1:
        std::cout << info->si_pid << std::endl;
        client.read_from_host(msg);
        std::cout << msg << std::endl;
        msg.clear();
        break;
    case SIGUSR2:
        std::cout << info->si_pid << std::endl;
        client.read_from_host_general(msg_general);
        std::cout << msg_general << std::endl;
        msg_general.clear();
        break;
    default:
        std::cout << info->si_pid << std::endl;
        break;
    }
}

int main()
{
    std::cout << getpid() << std::endl;

    while (true)
    {
        std::cout << "send to host: " << client.send_to_host("client_abc") << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}