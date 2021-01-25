#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <fstream.h>
#include <iostream.h>
#include <string.h>  /* for memset () */
#include <unistd.h>  /* for close () */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Sort_Info.h"                       

template <class T>
class Connector
{
  public:
    Connector(Sort_Info<T>& data, const char *const SERVER_HOST = 
"127.0.0.1", const int SERVER_PORT = 3420);
    ~Connector();
    void send_to_server();
    void get_data(Array<T>&);
  private:
    int sockfd;
    Sort_Info<T>* Data_;
    const char *const SORT_SERVER_HOST_;
    const int SORT_SERVER_PORT_;
    struct sockaddr_in serv_addr;
};

#endif
