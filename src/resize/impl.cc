// #include "impls.h"


// cv::Mat my_resize(const cv::Mat& input, float scale) {
//     /**
//      * 要求：
//      *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
//      * 用cv::resize。resize算法的内容自行查找学习，不是很难。
//      * 
//      * 提示：
//      * 无。
//      * 
//      * 通过条件：
//      * 运行测试点，你的结果跟答案长的差不多就行。
//      */
//     int new_rows = input.rows * scale, new_cols = input.cols * scale;
//     // IMPLEMENT YOUR CODE HERE
//     return cv::Mat::zeros(new_rows, new_cols, input.type());
// }


#include "impls.h"
#include <opencv2/core.hpp>

cv::Mat my_resize(const cv::Mat& input, float scale) {
    
    int new_rows = static_cast<int>(input.rows * scale);
    int new_cols = static_cast<int>(input.cols * scale);
    
    
    cv::Mat output(new_rows, new_cols, input.type(), cv::Scalar(0));
    
    
    int channels = input.channels();
    
    
    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
           
            float original_y = i / scale;
            float original_x = j / scale;
            
            
            int x1 = static_cast<int>(original_x);
            int y1 = static_cast<int>(original_y);
            int x2 = x1 + 1;
            int y2 = y1 + 1;
            
            
            x2 = std::min(x2, input.cols - 1);
            y2 = std::min(y2, input.rows - 1);
            
            
            float u = original_x - x1;  
            float v = original_y - y1;  
            
           
            for (int c = 0; c < channels; ++c) {
                
                uchar q11 = input.at<cv::Vec3b>(y1, x1)[c];  
                uchar q21 = input.at<cv::Vec3b>(y1, x2)[c]; 
                uchar q12 = input.at<cv::Vec3b>(y2, x1)[c];  
                uchar q22 = input.at<cv::Vec3b>(y2, x2)[c];  
                
                
                float interpolated = 
                    (1 - u) * (1 - v) * q11 +  
                    u * (1 - v) * q21 +        
                    (1 - u) * v * q12 +        
                    u * v * q22;              
                
               
                output.at<cv::Vec3b>(i, j)[c] = static_cast<uchar>(interpolated);
            }
        }
    }
    
    return output;
}