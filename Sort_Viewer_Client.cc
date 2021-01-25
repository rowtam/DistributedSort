/*
 * $Id: Sort_Viewer_Client.cc,v 1.6 2000/03/20 22:38:57 cs342 Exp $
 *
 * Based on the example TCP client in Steven's Unix Network Programming,
 * p. 286.
 *
 * To test:
 * On Solaris, be sure to link with the socket and nsl libraries, e.g.,
 *  $(CXX) -DTEST Sort_Viewer_Client.cc Sort_Info_Base.cc \
 *    -o Sort_Viewer_Client -lsocket -lnsl
 * (On Linux, remove the -lsocket.)
 */

#include "Sort_Viewer_Client.h"
#include "Sort_Info.h"

#include <string.h>  /* for memset () */
#include <unistd.h>  /* for close () and sleep () */
#include <stdio.h>   /* for perror () */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int
connect_to_viewer (int &sockfd,
                   fstream *&fs,
                   const char *const host,
                   const int port)
{
  struct sockaddr_in serv_addr;
  ::memset ((char *) &serv_addr, 0, sizeof serv_addr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr (host);
  serv_addr.sin_port = htons ((unsigned short) port);

  if ((sockfd = ::socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
      return -1;
    }

  if (::connect (sockfd, (struct sockaddr *) &serv_addr, sizeof serv_addr) < 0)
    {
      return -1;
    }

  fs = new fstream (sockfd);

  return fs  ?  0  :  -1;
}

int
send_to_viewer (fstream *fs, const Sort_Info_Base &sort_info)
{
  sort_info.print (*fs);
  return 0;
}

int
disconnect_from_viewer (const int sockfd, fstream *fs)
{
  if (close (sockfd))
    {
      perror ("close");
      return -1;
    }

  delete fs;

  return 0;
}

#if defined (TEST)
#include "Array.h"
#include <stdlib.h>  /* for rand () */

int
main (int, char *[])
{
  int sockfd;
  fstream *fs = 0;

  if (connect_to_viewer (sockfd, fs))
    {
      perror ("Sort_Viewer_Client; connect_to_viewer");
      return -1;
    }

  Array<int> a1 (50);
  for (int i = 0; i < 50; ++i)
    {
      a1.set (rand (), i);
    }
  const Sort_Info<int> sr1 (Sort_Info_Base::SELECTION_SORT, a1);

  if (send_to_viewer (fs, sr1))
    {
      perror ("Sort_Viewer_Client; send_to_viewer");
      return -1;
    }
  ::sleep (1);

  if (disconnect_from_viewer (sockfd, fs))
    {
      perror ("Sort_Viewer_Client; disconnect_from_viewer");
      return -1;
    }

  return 0;
}
#endif /* TEST */
