#pragma once

#include <string>
#include <vector>
#include <net.h>
#include "Bbox.h"
#include "opencv2/opencv.hpp"

class MTCNN 
{
public:
    MTCNN();
    ~MTCNN();
	
	//算法模型初始化
    void load(const std::string& model_path,
              int num_thread = 1);
	
	//算法单帧处理
    void detect(const cv::Mat& img_, 
                std::vector<Bbox>& finalBbox, 
                float scale = 1.0f, 
                cv::Rect detRegion = cv::Rect());

private:
	//网络 base model
    Inference_engine Pnet, Rnet, Onet;
	
    void generateBbox(cv::Mat score, cv::Mat location, std::vector<Bbox>& boundingBox_, float scale);
    void nms(std::vector<Bbox> &boundingBox_, const float overlap_threshold, std::string modelname = "Union");
	void refine(std::vector<Bbox>& vecBbox, const int& height, const int& width, bool square);
    void detectInternal(cv::Mat& img_, std::vector<Bbox>& finalBbox_);
    void PNet();
    void RNet();
    void ONet();
    std::vector<float> scales_;
    std::vector<Bbox> firstBbox_, secondBbox_, thirdBbox_;
    cv::Mat img;
    const float threshold[3] = {0.6f, 0.7f, 0.8f};
};