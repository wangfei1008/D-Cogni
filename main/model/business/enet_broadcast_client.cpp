///////////////////////////////////////////////////////////////////
//功能描述： 监听局域网广播，接收客户端软件服务信息
//
//时间：2024/11/16
//作者：wangfei
//历史版本： 说明
///////////////////////////////////////////////////////////////////
#include "enet_broadcast_client.h"
#include "log/log.h"
#include "errorcode.h"
#include "packet/packpro.h"

enet_broadcast_client::enet_broadcast_client(cb_broadcast cb)\
    :m_thread(std::bind(&enet_broadcast_client::_run,this))\
    ,m_callback(cb)
{
    m_socket = 0;
    m_buffer = (char*)malloc(sizeof(char) * MAX_PACKET_SIZE);
}

enet_broadcast_client::~enet_broadcast_client()
{
    close();
    free(m_buffer);
}

int enet_broadcast_client::connect()
{
    //1、入参检测
    if (m_socket != 0) return RES_ERR_IPUT_PARM;
    int result = RES_SUCCESS;
    ENetAddress address;

    //2、监听端口
    address.port = 1234;
    address.host = ENET_HOST_BROADCAST;
    if(ENET_SOCKET_NULL == (m_socket = enet_socket_create(ENET_SOCKET_TYPE_DATAGRAM))) return RES_ERR_OPEN_IO;
    enet_socket_set_option(m_socket, ENET_SOCKOPT_REUSEADDR, 1);
  
    result = enet_socket_set_option(m_socket, ENET_SOCKOPT_NONBLOCK, 1);
    result = enet_socket_set_option(m_socket, ENET_SOCKOPT_BROADCAST, 1);
    //3、启动线程，接收数据
    m_thread.start("");

    return RES_SUCCESS;
}

int enet_broadcast_client::close()
{
    if(m_socket != NULL)
    {
        enet_socket_destroy(m_socket);
        m_socket = 0;
        m_thread.stop();
    }
    return RES_SUCCESS;
}

void enet_broadcast_client::_run()
{
    ENetBuffer scannerbuffer = { 0 };
    ENetAddress address;
    int host = 0;
    int port = 0;
    uint32_t len = 0;

    address.port = 1234;
    address.host = ENET_HOST_BROADCAST;

    char buffer[1024] = { '\0' };
    ui32toa(buffer, host);
    ui32toa(buffer + 4, port);
    netpack* pack = np_create(0x0A, 0, 8, buffer);
	scannerbuffer.data = (char*)malloc(sizeof(char) * MAX_PACKET_SIZE);
    np_serialize(pack, (char*)scannerbuffer.data, len);
    scannerbuffer.dataLength = len;
    np_release(&pack);

    enet_socket_send(m_socket, &address, &scannerbuffer, 1);
    free(scannerbuffer.data);

    std::this_thread::sleep_for(std::chrono::microseconds(500));
}
