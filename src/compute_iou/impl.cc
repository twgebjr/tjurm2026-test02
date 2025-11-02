// #include "impls.h"
// #include <algorithm>

// float compute_iou(const cv::Rect& a, const cv::Rect& b) {
//     /**
//      * 要求：
//      *      有一个重要的指标叫做“交并比”，简称“IOU”，可以用于衡量
//      * 两个矩形的重合程度，本练习要求自行学习交并比的计算方式，计算输入
//      * 的两个矩形的交并比。
//      * 
//      * 提示：
//      * (1) 注意OpenCV中规定的xy坐标系方向跟平常的xy坐标系不一样。
//      * (2) 注意矩形的x, y, width, height四个属性在坐标系内的含义。
//      * (3) 注意分母不要除以0（不过我们不会测试这一点）
//      * 
//      * 通过条件：
//      * 运行测试点，显示通过就行，不通过会告诉你哪一组矩形错了。
//     */
//     // IMPLEMENT YOUR CODE HERE
//     return 0.f;
// }





#include "impls.h"
#include <algorithm>

float compute_iou(const cv::Rect& a, const cv::Rect& b) {
    int a_left = a.x;
    int a_right = a.x + a.width;
    int a_top = a.y;
    int a_bottom = a.y + a.height;
    
    int b_left = b.x;
    int b_right = b.x + b.width;
    int b_top = b.y;
    int b_bottom = b.y + b.height;
    
    int inter_left = std::max(a_left, b_left);
    int inter_right = std::min(a_right, b_right);
    int inter_top = std::max(a_top, b_top);
    int inter_bottom = std::min(a_bottom, b_bottom);
    
    int inter_width = std::max(0, inter_right - inter_left);
    int inter_height = std::max(0, inter_bottom - inter_top);
    float inter_area = static_cast<float>(inter_width * inter_height);
    
    float area_a = static_cast<float>(a.width * a.height);
    float area_b = static_cast<float>(b.width * b.height);
    
    float union_area = area_a + area_b - inter_area;
    
    if (union_area <= 0) {
        return 0.f;
    }
    
    return inter_area / union_area;
}