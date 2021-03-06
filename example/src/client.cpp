#include <iostream>
#include <opencv2/opencv.hpp>

#include <RedisImageHelper.hpp>
#include "ImageUtils.hpp"

int main(int argc, char** argv)
{
    RedisImageHelper client;
    //RedisCameraClient client;
    if (!client.connect()) { std::cerr << "Client could not connect to redis server" << std::endl; }
    client.setCameraKey("custom:image");

    cv::Mat frame, displayFrame;
    Image* cFrame;
    while (true)
    {
        cFrame = client.getImage();
        if (cFrame == NULL) { std::cerr << "Error: Could not get camera frame, exiting..." << std::endl; return EXIT_FAILURE;}
        frame = cv::Mat(cFrame->height(), cFrame->width(), CV_8UC3, (void*)cFrame->data());
        cv::cvtColor(frame, displayFrame, CV_RGB2BGR);

        cv::imshow("frame", displayFrame);
        if (cv::waitKey(30) >= 0)
        {
            break;
        }
        delete cFrame;
    }

    frame.release();
    displayFrame.release();
}
