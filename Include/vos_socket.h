/******************************************************************************
###############################################################################
#   Copyright (c) [2017-2020] [ICT/CAS]                                        #
#   Licensed under the ORAN Software License v1.0 (License)             #
###############################################################################
******************************************************************************/



#ifndef	__VOS_SOCKET_H__
#define	__VOS_SOCKET_H__

#ifdef	__cplusplus
extern "C"{
#endif

#include "vos_types.h"
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netpacket/packet.h>
#include "vos_sctp.h"
#include "vos_linklist.h"

/**
 * socket地址联合体，可用于IPv4，IPv6，和unix类型的socket
 */
typedef union vos_sockaddr_u
{
    struct sockaddr         sa;     ///< 通用结构 
    struct sockaddr_in      sin;    ///< IPv4 结构 
    struct sockaddr_in6     sin6;   ///< IPv6 结构
    struct sockaddr_un      un;     ///< unix 结构 
    struct sockaddr_ll      raw;    ///< raw 结构
}vos_sockaddr_t;

/**
 * 协议族
*/
typedef enum vos_domain_e{
    VOS_AF_UNIX  = AF_UNIX,     ///< unix socket
    VOS_AF_INET  = AF_INET,     ///< ipv4
    VOS_AF_INET6 = AF_INET6,    ///< ipv6
    VOS_AF_PACKET= AF_PACKET,   ///< 用于raw socket
}vos_domain_t;

/**
 * socket类型
*/
typedef enum vos_socktype_e{
    VOS_SOCK_STREAM = SOCK_STREAM,  ///< TCP
    VOS_SOCK_DGRAM  = SOCK_DGRAM,   ///< UDP
    VOS_SOCK_RAW    = SOCK_RAW,     ///< raw socket
    VOS_SOCK_SEQPACKET    = SOCK_SEQPACKET,     ///< sctp one2many
}vos_socktype_t;


/**
 * 将IP地址结构转换成IP地址字符串
 * @param[in ]   af           协议族,VOS_AF_INET 或 VOS_AF_INET6
 * @param[in ]   src          IP地址结构
 * @param[out]   dst          用于存储转换结果的buf，
 * @param[in ]   size         buf的大小
 * @return       成功返回指向dst的指针，失败返回 NULL
*/
const CHAR *vos_inet_ntop(LONG af, const vos_sockaddr_t *src,CHAR *dst, socklen_t size);


/**
 * 将IP地址字符串转换成IP地址结构
 * @param[in ]   af           协议族,VOS_AF_INET 或 VOS_AF_INET6
 * @param[in ]   src          IP地址字符串
 * @param[out]   dst          用于存储转换结果的IP地址结构，
 * @return       成功返回 VOS_OK，失败则返回其他
*/
LONG vos_inet_pton(LONG af, const CHAR *src, vos_sockaddr_t *dst);



/**
 * 创建socket
 * @param[in ]   domain        协议族
 * @param[in ]   type          socket类型
 * @param[out]   protocol      协议，一般填0
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_socket(vos_domain_t domain,vos_socktype_t type,LONG protocol);

/**
 * 为socket绑定地址
 * @param[in ]   sockfd        要绑定的socket
 * @param[in ]   my_addr       地址结构
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_bind(LONG sockfd,vos_sockaddr_t *my_addr);



/**
 * 为socket绑定地址
 * @param[in ]   sockfd        要绑定的socket
 * @param[in ]   family        协议族
 * @param[in ]   port          端口号，当family为 VOS_AF_INET 和 VOS_AF_INET6 有效
 * @param[in ]   addrStr       地址字符串，
                                    当family为 VOS_AF_INET 和 VOS_AF_INET6 时为IP地址字符串，
                                    当family为 VOS_AF_UNIX 时 为本地文件路径字符串
 * @param[in ]   protocol      协议，当family为 VOS_AF_PACKET 时有效，为协议类型
 * @param[in ]   ifName        网口名，当family为 VOS_AF_PACKET 时有效，为绑定的网口名
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_bind_str(LONG sockfd,vos_domain_t family,SHORT port,const CHAR *addrStr,SHORT protocol,const CHAR *ifName);


/**
 * 监听socket
 * @param[in ]   sockfd        欲监听的socket
 * @param[in ]   maxClient     最大连接数
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_listen(LONG sockfd, LONG maxClient);


/**
 * 获得连接请求
 * @param[in ]   sockfd        被监听的socket
 * @param[in ]   addr          客户端地址
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_accept(LONG sockfd,vos_sockaddr_t *addr);



/**
 * 建立与指定socket的连接
 * @param[in ]   sockfd        欲建立连接的socket
 * @param[in ]   con_addr      服务端地址
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_connect(LONG sockfd,vos_sockaddr_t *con_addr);



/**
 * 建立与指定socket的连接
 * @param[in ]   sockfd        欲建立连接的socket
 * @param[in ]   family        协议族
 * @param[in ]   port          端口号，当family为 VOS_AF_INET 和 VOS_AF_INET6 有效
 * @param[in ]   addrStr       服务端地址字符串，
                                    当family为 VOS_AF_INET 和 VOS_AF_INET6 时为IP地址字符串，
                                    当family为 VOS_AF_UNIX 时 为本地文件路径字符串
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_connect_str(LONG sockfd,vos_domain_t family,SHORT port,const CHAR *addrStr);


/**
 * 从已连接的socket的接收数据
 * @param[in ]   sockfd        已建立连接的socket
 * @param[in ]   buf           存储数据的缓冲区
 * @param[in ]   len           buf的大小
 * @param[in ]   flags         参考 系统 recv 函数
 * @return       成功返回 接收的字节数 ，失败则返回 VOS_ERROR
*/
LONG vos_recv(LONG sockfd, VOID *buf, size_t len, LONG flags);

/**
 * 向已连接的socket的发送数据
 * @param[in ]   sockfd        已建立连接的socket
 * @param[in ]   buf           存储数据的缓冲区
 * @param[in ]   len           buf的大小
 * @param[in ]   flags         参考 系统 recv 函数
 * @return       成功返回 发送的字节数 ，失败则返回 VOS_ERROR
*/
LONG vos_send(LONG sockfd, const VOID *buf, size_t len, LONG flags);

/**
 * 从socket中接收数据
 * @param[in ]   sockfd        socket
 * @param[in ]   buf           存储数据的缓冲区
 * @param[in ]   len           buf的大小
 * @param[in ]   flags         参考 系统 recv 函数
 * @param[in ]   src_addr      数据来源端的地址
 * @return       成功返回 接收的字节数 ，失败则返回 VOS_ERROR
*/
LONG vos_recvfrom(LONG sockfd, void *buf, size_t len, LONG flags,vos_sockaddr_t *src_addr);

/**
 * 向socket中发送数据
 * @param[in ]   sockfd        socket
 * @param[in ]   buf           存储数据的缓冲区
 * @param[in ]   len           buf的大小
 * @param[in ]   flags         参考 系统 sendto 函数
 * @param[in ]   dest_addr     数据发送的目的地址
 * @return       成功返回 发送的字节数 ，失败则返回 VOS_ERROR
*/
LONG vos_sendto(LONG sockfd, const void *buf, size_t len, LONG flags,const vos_sockaddr_t *dest_addr);



/**
 * 获取 本地的 IP 地址
 * @param[in ]   sockfd        socket
 * @param[out]   addr          用于存放地址
 * @return       成功返回 地址个数，失败则返回 VOS_ERROR
*/
LONG vos_getsockname(LONG sockfd,vos_sockaddr_t *addr);

/**
 * 获取 对端的 IP 地址
 * @param[in ]   sockfd       socket
 * @param[out]   addr         用于存放地址
 * @return       成功返回 地址个数，失败则返回 VOS_ERROR
*/
LONG vos_getpeername(LONG sockfd, vos_sockaddr_t *addr);


/**
 * 向raw socket中发送数据
 * @param[in ]   sockfd        socket
 * @param[in ]   ifName        用于数据发送的网口名
 * @param[in ]   buf           存储数据的缓冲区
 * @param[in ]   len           buf的大小
 * @param[in ]   flags         参考 系统 sendto 函数
 * @return       成功返回 发送的字节数 ，失败则返回 VOS_ERROR
*/
LONG vos_raw_sendto(LONG sockfd,const CHAR *ifName, const void *buf, size_t len, LONG flags);


/**
 * 填充vos_sockaddr_t地址结构
 * @param[in ]   socket        相关的socket，当family 为VOS_AF_PACKET时有效
 * @param[out]   my_addr       被填充的 vos_sockaddr_t 变量
 * @param[in ]   family        协议族
 * @param[in ]   port          端口号，当family为 VOS_AF_INET 和 VOS_AF_INET6 有效
 * @param[in ]   addrStr       地址字符串，
                                    当family为 VOS_AF_INET 和 VOS_AF_INET6 时为IP地址字符串，
                                    当family为 VOS_AF_UNIX 时 为本地文件路径字符串
 * @param[in ]   protocol      协议，当family为 VOS_AF_PACKET 时有效，为协议类型
 * @param[in ]   ifName        网口名，当family为 VOS_AF_PACKET 时有效，为绑定的网口名
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_addr_fill(LONG socket,vos_sockaddr_t *my_addr,vos_domain_t family,SHORT port,const CHAR *addrStr,SHORT protocol,const CHAR *ifName);


/**
 * 获取本机网口的MAC地址
 * @param[in ]   ifName        网口名
 * @param[out]   addr          MAC 地址
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_get_if_mac_addr(const CHAR *ifName,UCHAR addr[6]);

/**
 * 创建unix udp socket，包含创建、绑定和监听
 * @param[in ]   local_path       本地文件路径
 * @param[in ]   isbind           是否绑定端口
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_unix_udp_socket_create(const CHAR *local_path,BOOL isbind);


/**
 * 创建unix tcp socket，包含创建、绑定和监听
 * @param[in ]   local_path       本地文件路径
 * @param[in ]   maxClient        最大连接数
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_unix_tcp_server_socket_create(const CHAR *local_path, LONG maxClient);


/**
 * 创建unix tcp socket，包含创建和连接
 * @param[in ]   local_path       本地文件路径
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_unix_tcp_client_socket_create(const CHAR *local_path);


/**
 * 创建tcp socket，包含创建、绑定和监听
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   addrStr       IPv4/IPv6 地址
 * @param[in ]   port          端口号
 * @param[in ]   maxClient     最大连接数
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_tcp_server_socket_create(vos_domain_t family,const CHAR *addrStr,SHORT port, LONG maxClient);

/**
 * 创建tcp socket，包含创建和连接
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   addrStr       IPv4/IPv6 地址
 * @param[in ]   port          端口号
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_tcp_client_socket_create(vos_domain_t family,const CHAR *addrStr,SHORT port);

/**
 * 创建udp socket，包含创建、绑定
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   addrStr       IPv4/IPv6 地址
 * @param[in ]   port          端口号
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_udp_server_socket_create(vos_domain_t family,const CHAR *addrStr,SHORT port);

/**
 * 创建udp socket，包含创建并返回server 地址结构
 * @param[in ]   family          VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   s_addrStr       IPv4/IPv6 地址
 * @param[in ]   s_port          端口号
 * @param[out]   s_addr          s_addr 由s_addrStr和s_port生成的地址结构
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_udp_client_socket_create(vos_domain_t family,const CHAR *s_addrStr,SHORT s_port,vos_sockaddr_t *s_addr);


/**
 * 创建raw socket，包含创建、绑定
 * @param[in ]   protocol      协议
 * @param[in ]   ifName        网口名
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_raw_server_socket_create(SHORT protocol,const CHAR *ifName);


/**
 * 创建sctp socket 绑定，可以指定多个地址，
 * 如果 sock 参数为 IPv4 套接字，则传送给 sctp_bindx() 函数的地址必须为 IPv4 地址。
 * 如果 sock 参数为 IPv6 套接字，则传送给 sctp_bindx() 函数的地址可以为 IPv4 或 IPv6 地址。
 * @param[in ]   sockfd        要绑定的socket
 * @param[in ]   addrs         地址数组
 * @param[in ]   addrcnt       地址个数
 * @param[in ]   flags         有如下取值：
 *                  SCTP_BINDX_ADD_ADDR 指示 SCTP 将给定地址添加到关联中
 *                  SCTP_BINDX_REM_ADDR 指示 SCTP 从关联中删除给定地址
 * @return       成功返回 VOS_OK，失败则返回 其他
*/
LONG vos_sctp_bindx(LONG sockfd, vos_sockaddr_t *addrs, LONG addrcnt, LONG flags);


/**
 * 创建sctp socket 绑定，可以指定多个地址，
 * 如果 sock 参数为 IPv4 套接字，则传送给 sctp_bindx() 函数的地址必须为 IPv4 地址。
 * 如果 sock 参数为 IPv6 套接字，则传送给 sctp_bindx() 函数的地址可以为 IPv4 或 IPv6 地址。
 * @param[in ]   sockfd        要绑定的socket
 * @param[in ]   family        协议族，VOS_AF_INET 和 VOS_AF_INET6 有效
 * @param[in ]   port          端口号 
 * @param[in ]   addrStr       地址字符串数组
 * @param[in ]   addrcnt       地址个数
 * @param[in ]   flags         有如下取值：
 *                  SCTP_BINDX_ADD_ADDR 指示 SCTP 将给定地址添加到关联中
 *                  SCTP_BINDX_REM_ADDR 指示 SCTP 从关联中删除给定地址
 * @return       成功返回 VOS_OK，失败则返回 其他
*/
LONG vos_sctp_bindx_str(LONG sockfd,vos_domain_t family,SHORT port,CHAR *addrStr[], LONG addrcnt, LONG flags);



/**
 * 建立与指定socket的连接
 * @param[in ]   sockfd        欲建立连接的socket
 * @param[in ]   addrs         地址数组
 * @param[in ]   addrcnt       地址个数
 * @param[out]   id            关联ID
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_sctp_connectx(LONG sockfd, vos_sockaddr_t *addrs, LONG addrcnt,sctp_assoc_t *id);


/**
 * 建立与指定socket的连接
 * @param[in ]   sockfd        欲建立连接的socket
 * @param[in ]   family        协议族
 * @param[in ]   port          端口号，当family为 VOS_AF_INET 和 VOS_AF_INET6 有效
 * @param[in ]   addrStr       地址字符串数组
 * @param[in ]   addrcnt       地址个数
 * @param[out]   id            关联ID
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_sctp_connectx_str(LONG sockfd,vos_domain_t family,SHORT port,CHAR *addrStr[], LONG addrcnt,sctp_assoc_t *id);


/**
 * 向socket发送数据
 * @param[in ]   sockfd        socket
 * @param[in ]   msg           存储数据的缓冲区
 * @param[in ]   len           msg的大小
 * @param[in ]   sinfo         包含用于发送消息的参数。可以指定，流、ppid、TTL、关联 ID等。
 * @param[in ]   flags         此值在将逻辑运算 OR 以按位形式应用于以下零个或多个标志位时形成：
 *                              MSG_UNORDERED :设置此标志之后，vos_sctp_sendmsg() 函数将无序传送消息。
 *                              MSG_ADDR_OVER:设置此标志之后，vos_sctp_sendmsg() 函数将使用 to 参数中的地址，而不使用关联的主要目标地址。此标志仅用于一对多风格 SCTP 套接字。
 *                              MSG_ABORT:设置此标志之后，指定的关联将异常中止，同时向其对等方发送 ABORT 信号。此标志仅用于一对多风格 SCTP 套接字。
 *                              MSG_EOF:设置此标志之后，指定的关联将进入正常关闭状态。此标志仅用于一对多风格 SCTP 套接字。
 * @return       成功返回 发送的字节数 ，失败则返回 VOS_ERROR
*/
LONG vos_sctp_send(LONG sockfd, const void *msg, size_t len,const struct sctp_sndrcvinfo *sinfo, LONG flags);



/**
 * 向socket发送数据
 * @param[in ]   sockfd        socket
 * @param[in ]   msg           存储数据的缓冲区
 * @param[in ]   len           msg的大小
 * @param[in ]   to            目的地址
 * @param[in ]   ppid          协议无关的一个自定义值，一般填0即可
 * @param[in ]   flags         同vos_sctp_send
 * @param[in ]   stream_no     此消息的目标流
 * @param[in ]   timetolive    TTL 以毫秒为单位，0表示无限生命期。
 * @param[in ]   context       一个本地标志，用于检测无法发送到对端的消息，一般填0即可
 * @return       成功返回 发送的字节数 ，失败则返回 VOS_ERROR
*/
LONG vos_sctp_sendmsg(LONG sockfd, const void *msg, size_t len, vos_sockaddr_t *to,
                        LONG ppid, LONG flags,
                        LONG stream_no, LONG timetolive, LONG context);



/**
 * 从socket接收数据
 * @param[in ]   sockfd        socket
 * @param[out]   msg           存储数据的缓冲区
 * @param[in ]   len           msg的大小
 * @param[in ]   from          源地址
 * @param[out]   sinfo         包含接收消息的参数。包含流、ppid、TTL、关联 ID等。
 * @param[out]   msg_flags     同vos_sctp_send
 * @return       成功返回 接收的字节数 ，失败则返回 VOS_ERROR
*/
LONG vos_sctp_recvmsg(LONG sockfd, void *msg, size_t len, vos_sockaddr_t *from,
                        struct sctp_sndrcvinfo *sinfo,
                        LONG *msg_flags);

/**
 * 获取 socket 选项参数
 * @param[in ]   sockfd        sctp socket
 * @param[in ]   level         选项定义的层次；支持SOL_SOCKET、IPPROTO_SCTP、IPPROTO_TCP、IPPROTO_IP和IPPROTO_IPV6。
 * @param[in ]   optname       需获取的选项
 * @param[out]   optval        存放获取的值
 * @param[in ]   optlen        optval的大小
 * @param[out]   optlen        获取的大小
 * @return       成功返回 VOS_OK，失败则返回 其他
*/
LONG vos_getsockopt(LONG sockfd, LONG level, LONG optname,void *optval, socklen_t *optlen);


/**
 * 设置 socket 选项参数
 * @param[in ]   sockfd        sctp socket
 * @param[in ]   level         同 vos_getsockopt
 * @param[in ]   optname       需设置的选项
 * @param[in ]   optval        要设置的值
 * @param[in ]   optlen        optval的大小
 * @return       成功返回 VOS_OK，失败则返回 其他
*/
LONG vos_setsockopt(LONG sockfd, LONG level, LONG optname,const void *optval, socklen_t optlen);


/**
 * 关闭文件描述符
 * @param[in ]   sockfd        socket
 * @return       成功返回 VOS_OK，失败则返回 其他
*/
LONG vos_close(LONG sockfd);


/**
 * 从一对多式socket的关联标识id中抽取一个一对一式socket
 * @param[in ]   sockfd        一对多式socket
 * @param[in ]   assoc_id      关联标识id
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_sctp_peeloff(LONG sockfd, sctp_assoc_t assoc_id);


/**
 * 获取 SCTP 相关的 socket 选项参数
 * @param[in ]   sockfd        sctp socket
 * @param[in ]   assoc_id      关联标识id
 * @param[in ]   opt           SCTP 相关的 socket 选项
 * @param[out]   arg           用于存放参数
 * @param[out]   size          参数的大小
 * @return       成功返回 VOS_OK，失败则返回 其他
*/
LONG vos_sctp_opt_info(LONG sockfd, sctp_assoc_t assoc_id, LONG opt, void *arg, socklen_t *size);


/**
 * 获取 对端的 IP 地址，使用完需要调用 vos_sctp_freepaddrs 释放资源
 * @param[in ]   sockfd        sctp socket
 * @param[in ]   assoc_id      关联标识id
 * @param[out]   addrs         用于存放地址
 * @return       成功返回 地址个数，失败则返回 VOS_ERROR
*/
LONG vos_sctp_getpaddrs(LONG sockfd, sctp_assoc_t assoc_id,vos_sockaddr_t **addrs);


/**
 * 释放由 vos_sctp_getpaddrs 函数分配的资源,获取到 0 个时不需要释放
 * @param[out]   addrs         vos_sctp_getpaddrs 返回的地址
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_sctp_freepaddrs(vos_sockaddr_t *addrs);

/**
 * 获取 本地的 IP 地址，使用完需要调用 vos_sctp_freepaddrs 释放资源
 * @param[in ]   sockfd        sctp socket
 * @param[in ]   assoc_id      关联标识id
 * @param[out]   addrs         用于存放地址
 * @return       成功返回 地址个数，失败则返回 VOS_ERROR
*/
LONG vos_sctp_getladdrs(LONG sockfd, sctp_assoc_t assoc_id,vos_sockaddr_t **addrs);

/**
 * 释放由 vos_sctp_getladdrs 函数分配的资源,获取到 0 个时不需要释放
 * @param[out]   addrs         vos_sctp_getladdrs 返回的地址
 * @return       成功返回 VOS_OK ，失败则返回 其他
*/
LONG vos_sctp_freeladdrs(vos_sockaddr_t *addrs);

/**
 * 判断字符串是否为IPv4地址
 * @param[in ]   str        待判断字符串
 * @return       是返回 TRUE ，否返回 FALSE
*/
BOOL vos_is_ipv4_addr(CHAR *str);

/**
 * 判断字符串是否为IPv6地址
 * @param[in ]   str        待判断字符串
 * @return       是返回 TRUE ，否返回 FALSE
*/
BOOL vos_is_ipv6_addr(char *str);

/**
 * 判断两个addr是否相等
 * @param[in ]   addr1        待判断地址结构
 * @param[in ]   addr2        待判断地址结构
 * @param[in ]   ignPort      是否忽略端口号
 * @return       相等则返回0，不相等返回非0
*/
LONG vos_sock_addr_cmp(vos_sockaddr_t *addr1,vos_sockaddr_t *addr2,BOOL ignPort);


/**
 * addr 地址结构转换成用于打印的字符串
 * @param[in ]   addr        地址结构
 * @param[in ]   str         用于存放生成的字符串
 * @param[in ]   size        str大小
 * @return       返回指向str的指针
*/
CHAR *vos_addr_showstr(vos_sockaddr_t *addr,CHAR *str,LONG size);


/**
 * 创建sctp 一对一 socket，包含创建、绑定和监听
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   addrs         地址数组
 * @param[in ]   addrcnt       地址个数
 * @param[in ]   port          端口号
 * @param[in ]   maxClient     最大连接数
 * @param[in ]   initmsg       sctp 相关信息
 * @param[in ]   events        sctp 事件，如果传入 NULL 则默认监听 data_io
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_sctp_server_one2one_create(vos_domain_t family,vos_sockaddr_t *addrs,LONG addrcnt, SHORT port, LONG maxClient,struct sctp_initmsg *initmsg,struct sctp_event_subscribe *events);

/**
 * 创建sctp 一对一 socket，包含创建 和 连接
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   s_addrs       地址数组
 * @param[in ]   s_addrcnt     地址个数
 * @param[in ]   s_port        端口号
 * @param[in ]   initmsg       sctp 相关信息
 * @param[in ]   events        sctp 事件，如果传入 NULL 则默认监听 data_io
 * @param[out]   id            sctp_assoc id
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_sctp_client_one2one_create(vos_domain_t family,vos_sockaddr_t *s_addrs,LONG s_addrcnt, SHORT s_port,
                                                    struct sctp_initmsg *initmsg,struct sctp_event_subscribe *events,sctp_assoc_t *id);


/**
 * 通过字符串地址创建sctp 一对一 socket，包含创建 和 连接
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   s_addrStr     地址数组
 * @param[in ]   s_addrcnt     地址个数
 * @param[in ]   s_port        端口号
 * @param[in ]   initmsg       sctp 相关信息
 * @param[in ]   events        sctp 事件，如果传入 NULL 则默认监听 data_io
 * @param[out]   id            sctp_assoc id
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_sctp_client_one2one_str_create(vos_domain_t family,CHAR *s_addrStr[],LONG s_addrcnt, SHORT s_port,
                                                    struct sctp_initmsg *initmsg,struct sctp_event_subscribe *events,sctp_assoc_t *id);


/**
 * 创建sctp 一对一 socket，包含创建、绑定和监听
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   addrStr       地址字符串数组
 * @param[in ]   addrcnt       地址个数
 * @param[in ]   port          端口号
 * @param[in ]   maxClient     最大连接数
 * @param[in ]   initmsg       sctp 相关信息
 * @param[in ]   events        sctp 事件，如果传入 NULL 则默认监听 data_io
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_sctp_server_one2one_str_create(vos_domain_t family,CHAR *addrStr[],LONG addrcnt, SHORT port, LONG maxClient,struct sctp_initmsg *initmsg,struct sctp_event_subscribe *events);


/**
 * 创建sctp 一对多 socket，包含创建、绑定和监听
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   addrs         地址数组
 * @param[in ]   addrcnt       地址个数
 * @param[in ]   port          端口号
 * @param[in ]   maxClient     最大连接数
 * @param[in ]   initmsg       sctp 相关信息
 * @param[in ]   events        sctp 事件，如果传入 NULL 则默认监听 data_io
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_sctp_server_one2many_create(vos_domain_t family,vos_sockaddr_t *addrs,LONG addrcnt, SHORT port, LONG maxClient,struct sctp_initmsg *initmsg,struct sctp_event_subscribe *events);

/**
 * 创建sctp 一对多 socket，包含创建
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   s_addrs       地址数组
 * @param[in ]   s_addrcnt     地址个数
 * @param[in ]   s_port        端口号
 * @param[in ]   initmsg       sctp 相关信息
 * @param[in ]   events        sctp 事件，如果传入 NULL 则默认监听 data_io
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_sctp_client_one2many_create(vos_domain_t family,vos_sockaddr_t *s_addrs,LONG s_addrcnt, SHORT s_port,
                                               struct sctp_initmsg *initmsg,struct sctp_event_subscribe *events);

/**
 * 创建sctp 一对多 socket，包含创建、绑定和监听
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   addrStr       地址字符串数组
 * @param[in ]   addrcnt       地址个数
 * @param[in ]   port          端口号
 * @param[in ]   maxClient     最大连接数
 * @param[in ]   initmsg       sctp 相关信息
 * @param[in ]   events        sctp 事件，如果传入 NULL 则默认监听 data_io
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_sctp_server_one2many_str_create(vos_domain_t family,CHAR *addrStr[],LONG addrcnt, SHORT port, LONG maxClient,struct sctp_initmsg *initmsg,struct sctp_event_subscribe *events);

/**
 * 通过字符串地址创建sctp 一对多 socket，包含创建
 * @param[in ]   family        VOS_AF_INET 和 VOS_AF_INET6
 * @param[in ]   s_addrStr     地址数组
 * @param[in ]   s_addrcnt     地址个数
 * @param[in ]   s_port        端口号
 * @param[in ]   initmsg       sctp 相关信息
 * @param[in ]   events        sctp 事件，如果传入 NULL 则默认监听 data_io
 * @return       成功返回 文件描述符，失败则返回 其他
*/
LONG vos_sctp_client_one2many_str_create(vos_domain_t family,CHAR *s_addrStr[],LONG s_addrcnt, SHORT s_port,
                                                     struct sctp_initmsg *initmsg,struct sctp_event_subscribe *events);


LONG vos_udp_client_socket_create_bind(vos_domain_t family,const CHAR *s_addrStr,SHORT s_port,vos_sockaddr_t *s_addr,vos_sockaddr_t *my_addr);

LONG vos_tcp_client_socket_create_bind(vos_domain_t family,const CHAR *addrStr,SHORT port,vos_sockaddr_t *my_addr);

LONG vos_sctp_client_one2one_create_bind(vos_domain_t family,vos_sockaddr_t *s_addrs,LONG s_addrcnt, SHORT s_port,
                                                    struct sctp_initmsg *initmsg,struct sctp_event_subscribe *events,sctp_assoc_t *id,
                                                    vos_sockaddr_t *my_addrs,LONG my_addrcnt);

LONG vos_sctp_client_one2many_create_bind(vos_domain_t family,vos_sockaddr_t *s_addrs,LONG s_addrcnt, SHORT s_port,
                                               struct sctp_initmsg *initmsg,struct sctp_event_subscribe *events,
                                               vos_sockaddr_t *my_addrs,LONG my_addrcnt);


#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif	/* end of __VOS_SOCKET_H__ */

