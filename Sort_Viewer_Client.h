/*
 * $Id: Sort_Viewer_Client.h,v 1.2 2000/03/20 22:38:43 cs342 Exp $
 */

#ifndef SORT_VIEWER_CLIENT_H
#define SORT_VIEWER_CLIENT_H

#include "Sort_Info_Base.h"
#include <fstream.h>

const int JAVA_VIEWER_PORT = 3420;
const char *const JAVA_VIEWER_HOST = "127.0.0.1"; /* localhost */

/*
 * Connects to the Java viewer on the host, at the given port.
 * fs is an fstream that can be used to send messages to the
 *  viewer, using send_to_viewer ().
 * sockfd is set to the socket's file descriptor.  It must be
 *   closed by the caller, using disconnect_from_viewer (),
 *   when the viewer connection is no longer needed.
 * Returns 0 on success, -1 on failure.
 */
int connect_to_viewer (int &sockfd,
                       fstream *&fs,
                       const char *const host = JAVA_VIEWER_HOST,
                       const int port = JAVA_VIEWER_PORT);

/*
 * Sends a Sort_Info_Base to a sort viewer, over a stream
 * established by connect_to_viewer.
 */
int send_to_viewer (fstream *fs, const Sort_Info_Base &sort_info);

/*
 * Tears down a socket connection and stream that were set up by
 * connect_to_viewer ().
 */
int disconnect_from_viewer (const int sockfd, fstream *fs);

#endif /* SORT_VIEWER_CLIENT_H */
