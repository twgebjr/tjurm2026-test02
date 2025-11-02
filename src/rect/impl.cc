// #include "impls.h"


// std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
//     /**
//      * 要求：
//      * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
//      * 最小面积外接矩形。所需要的函数自行查找。
//      * 
//      * 通过条件：
//      * 运行测试点，你找到的矩形跟答案一样就行。
//     */
//     std::pair<cv::Rect, cv::RotatedRect> res;
//     // IMPLEMENT YOUR CODE HERE
//     return res;
// }

#include "impls.h"
#include <opencv2/imgproc.hpp>
#include <vector>

#include "impls.h"
#include <opencv2/imgproc.hpp>
#include <vector>

std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    std::pair<cv::Rect, cv::RotatedRect> res;

    
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    
    cv::Mat binary;
    cv::adaptiveThreshold(gray, binary, 255,
                          cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                          cv::THRESH_BINARY_INV, 15, 5); 

    
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, kernel); 

    
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    
    for (const auto& contour : contours) {
        
        double area = cv::contourArea(contour);
        if (area < 100) continue; 
        double perimeter = cv::arcLength(contour, true);
        std::vector<cv::Point> approx;
        
        cv::approxPolyDP(contour, approx, 0.04 * perimeter, true);

        
        if (approx.size() >= 3 && approx.size() <= 5 && cv::isContourConvex(approx)) {
            cv::Rect bounding_rect = cv::boundingRect(contour);
            cv::RotatedRect rotated_rect = cv::minAreaRect(contour);
            res = std::make_pair(bounding_rect, rotated_rect);
            break;
        }
    }

    return res;
}
    