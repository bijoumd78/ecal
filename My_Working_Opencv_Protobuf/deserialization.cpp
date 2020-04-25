#include <iostream>
#include <fstream>
#include <ecal/ecal.h>
#include <ecal/msg/protobuf/subscriber.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "image.pb.h"

using namespace std;
using namespace cv;

void OnImage(const char* /*topic_name_*/, const opencv::OcvMat& deserializableMat)
{
    std::cout << "Id: " << deserializableMat.id() << std::endl;
    std::cout << "Height: " << deserializableMat.rows() << "   Width: " << deserializableMat.cols() << std::endl;

    //create an empty OpenCV matrix
    Mat m;

    //allocate the matrix
    m.create(deserializableMat.rows(),
             deserializableMat.cols(),
             deserializableMat.elt_type());

    //set the matrix's data
    size_t dataSize = deserializableMat.rows() *  deserializableMat.cols() * deserializableMat.elt_size();

    std::copy(reinterpret_cast<unsigned char *>(
                  const_cast<char *>(deserializableMat.mat_data().data())),
              reinterpret_cast<unsigned char *>(
                  const_cast<char *>(deserializableMat.mat_data().data()) + dataSize), m.data);

    imshow("Live", m);
    waitKey(100);
}


int main(int argc, char **argv)
{
    // initialize eCAL API
    eCAL::Initialize(argc, argv, "image subscriber");

    // set process state
    eCAL::Process::SetState(proc_sev_healthy, proc_sev_level1, "I feel good !");

    // create a subscriber (topic name "person")
    eCAL::protobuf::CSubscriber<opencv::OcvMat> sub("image");

    // add receive callback function (_1 = topic_name, _2 = msg, _3 = time)
    auto callback = std::bind(OnImage, std::placeholders::_1, std::placeholders::_2);
    sub.AddReceiveCallback(callback);

    while(eCAL::Ok())
    {
        // sleep 100 ms
        eCAL::Process::SleepMS(100);
    }

    // finalize eCAL API
    eCAL::Finalize();

    return 0;
}
