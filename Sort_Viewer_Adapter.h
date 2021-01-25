#ifndef SORT_VIEWER_ADAPTER_H
#define SORT_VIEWER_ADAPTER_H

#include <unistd.h>
#include <fstream.h>
#include "Sort_Info_Base.h"
#include "Sort_Viewer_Client.h"

class Sort_Viewer_Adapter
{
  public:
 
  enum Viewer_Status { JAVA_VIEWER_DETECTED,
					   JAVA_VIEWER_NOT_DETECTED,
                       SEND_TO_VIEWER_FAILURE};

  Viewer_Status viewer_status_;

  int sockfd;

  fstream *fs;

  Sort_Viewer_Adapter();

  ~Sort_Viewer_Adapter();

  void Send(const Sort_Info_Base& sort_observation);  

};


#endif
