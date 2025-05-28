#ifndef ENET_BROADCAST_CLIENT_H
#define ENET_BROADCAST_CLIENT_H
#include <functional>
#include "thread/CThread.h"
#include "enet/enet.h"

class enet_broadcast_client
{
public:
    typedef std::function<int(char* ip, uint32_t port)> cb_broadcast;
    enet_broadcast_client(cb_broadcast cb);
    ~enet_broadcast_client();
    int connect();
    int close();
private:
    void _run();
private:
    CThread              m_thread;              //线程
    cb_broadcast         m_callback;            //回调函数
    ENetSocket           m_socket;              //socket值
    char                 *m_buffer;             //接收数据的缓存地址
};

#endif // ENET_BROADCAST_CLIENT_H
