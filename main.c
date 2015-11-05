/*
*File Transfer tools
* Author:ZYY
* date:2015-11-03
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config_socket.h"

#define MAX_CLIENTS_NUM (1000)

int clients[MAX_CLIENTS_NUM];


void set_fds(fd_set *preadset, int *pmax_fd)
{
    *pmax_fd = -1;
    FD_ZERO(preadset);

    if (sock_fd >= 0)
    {
        FD_SET(sock_fd, preadset);
        *pmax_fd = sock_fd;
    }


    for (i = 0; i < MAX_CLIENTS_NUM; i++) {
        if (clients[i] >= 0) {
            FD_SET(clients[i], preadset);
            if (*pmax_fd < clients[i])
            {
                *pmax_fd = clients[i];
            }
        }
    }
}



int main(int argc, char *arg[])
{
    int i, nready, max_fd;
    int quit_flag = 0;

    for (i = 0;i < MAX_CLIENTS_NUM; i++) {
        clients[i] = -1;
    }

    fd_set readset;
    sock_fd = confg_socket_create();

    max_fd = sock_fd;

    printf("max fd num %d\n",FD_SETSIZE);

    while (!quit_flag) {


        //开始监听描述符，是异步的，不会阻塞
        ready = select(max_fd+1, &readset, NULL, NULL, NULL);



    close(sock_fd);
    return 0;
}

void process_request(fd_set *fdset)
{
    if (FD_ISSET(listen_fd, &readset)) {
        conn_fd = accept(sock_fd, (struct sockaddr *)&addr_client, &client_size);
        if (conn_fd < 0) {
            perror("accept failed");
            exit(1);
        }

        FD_SET(conn_fd, &readset);
        FD_CLR(sock_fd, &readset);

        if (conn_fd > max_fd) {
            max_fd = conn_fd;
        }
        client[conn_fd] = 1;
    }

    //检查所有的描述符，查看可读的是哪个，针对它进行IO读写
    for (i = 0; i < FD_SETSIZE; i ++) {
        if (FD_ISSET(i, &readset)) {

            recv_num = recv(i, recv_buf, sizeof(recv_buf), 0);
            if (recv_num <= 0) {
                FD_CLR(i, &readset);
                client[i] = -1;
            }
            recv_buf[recv_num] = '\0';
            memset(send_buf,0,sizeof(send_buf));
            sprintf(send_buf, "server proc got %d bytes\n", recv_num);
            send_num = send(i, send_buf, strlen(send_buf), 0);
            if (send_num <= 0) {
                FD_CLR(i, &readset);
                client[i] = -1;
            }
        }
    }

}
