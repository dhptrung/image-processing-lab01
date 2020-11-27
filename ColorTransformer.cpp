// ColorTransformer.cpp
#include "ColorTransformer.h"

// Hàm nhận vào một ảnh, thay đổi độ sáng của ảnh này và lưu kết quả vào ảnh mới
int ColorTransformer::ChangeBrighness(const Mat& sourceImage, Mat& destinationImage, short b) 
{

}

// Hàm nhận vào một ảnh, thay đổi độ tương phản của ảnh này và lưu kết quả vào ảnh mới
int ColorTransformer::ChangeContrast(const Mat& sourceImage, Mat& destinationImage, float c) 
{

}

// Hàm tính lược đồ màu tổng quát cho ảnh bất kỳ
int ColorTransformer::CalcHistogram(const Mat& sourceImage, Mat& histMatrix) {

}

// Hàm cân bằng lược đồ màu tổng quát cho ảnh bất kỳ
int ColorTransformer::HistogramEqualization(const Mat& sourceImage, Mat& destinationImage) 
{

}

// Hàm cân bằng lược đồ màu tổng quát cho ảnh bất kỳ
int ColorTransformer::DrawHistogram(const Mat& histMatrix, Mat& histImage) 
{

}

// Hàm so sánh hai ảnh
float ColorTransformer::CompareImage(const Mat& image1, Mat& image2) 
{

}

ColorTransformer::ColorTransformer() 
{
}

ColorTransformer::~ColorTransformer() 
{
}