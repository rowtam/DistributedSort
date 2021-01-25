#ifndef SORT_VIEWER_ADAPTER_C
#define SORT_VIEWER_ADAPTER_C

#include "Sort_Viewer_Adapter.h"

Sort_Viewer_Adapter::Sort_Viewer_Adapter()
{
  if (connect_to_viewer(sockfd, fs)) {
    cout << "Sort_Viewer_Client: Viewer Not Detected.\n"
         << "Continuing with text-only representation." << endl;
	viewer_status_ = Sort_Viewer_Adapter::JAVA_VIEWER_NOT_DETECTED;
  } else {
	viewer_status_ = Sort_Viewer_Adapter::JAVA_VIEWER_DETECTED;
  }
}

Sort_Viewer_Adapter::~Sort_Viewer_Adapter()
{
  if (viewer_status_ != Sort_Viewer_Adapter::JAVA_VIEWER_NOT_DETECTED) {
    if (disconnect_from_viewer (sockfd, fs)) {
      cout << "Sort_Viewer_Client; disconnect_from_viewer error" << endl;
      viewer_status_ = Sort_Viewer_Adapter::JAVA_VIEWER_NOT_DETECTED;
    }
  }
}

void Sort_Viewer_Adapter::Send(const Sort_Info_Base &sort_observation)
{
  if (viewer_status_ == Sort_Viewer_Adapter::JAVA_VIEWER_DETECTED) {
    if (send_to_viewer (fs, sort_observation)) {
      cout <<"\nSort_Viewer_Client: send_to_viewer error" << endl;
      viewer_status_ = Sort_Viewer_Adapter::SEND_TO_VIEWER_FAILURE;
    }
  }                                 
}

#endif
