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
int ColorTransformer::CalcHistogram(const Mat& sourceImage, Mat& histMatrix) 
{
	if (sourceImage.data == NULL)
	{
		return 0;
	}

	int nChannels = sourceImage.channels();

	// Khởi tạo ma trận histogram (nChannel x 256), giá trị mặc định là 0
	histMatrix = Mat(nChannels, 256, CV_16UC1, Scalar(0));
	int widthStep = histMatrix.step[0];		// khoảng cách byte giữa các dòng
	ushort* pHistData = (ushort*)histMatrix.data;

	// duyệt qua các dòng pixel của ảnh source
	for (int y = 0; y < sourceImage.rows; y++)
	{
		// lấy con trỏ đầu dòng
		const uchar* pRow = sourceImage.ptr<uchar>(y);

		//for (int x = 0; x < sourceImage.cols * nChannels; x++)
		//{
		//	// Nếu nChannel = 1, i = 0, chỉ có 1 kênh 
		//	// Nếu nChannel = 3, i = 0, 1, 2 tương ứng với điểm ảnh thuộc kênh B, G, R
		//	int i = x % nChannels;

		//	/* Đếm số lượng điểm ảnh
		//	nChannel = 1, histMatrix chỉ có 1 dòng
		//	nChannel = 3, histMatrix có các dòng 1, 2, 3 lần lược tương ứng kênh B, G, R
		//	*/
		//	// Công thức truy cập pData[rowIdx*matF.step1() + colIdx]
		//	pHistData[i * widthStep + pRow[x]]++; // (pHistData + i*widthStep)[pRow[x]]++;
		//}

		for (int x = 0; x < sourceImage.cols; x++, pRow += nChannels)
		{
			// Nếu nChannel = 1, i = 0, chỉ có 1 kênh
			// Nếu nChannel = 3, i = 0, 1, 2 tương ứng với điểm ảnh thuộc kênh B, G, R
			if (nChannels == 1)
			{
				pHistData[pRow[0]]++;
			}
			else if (nChannels == 3)
			{
				// Công thức truy cập pData[rowIdx*matF.step1() + colIdx]
				pHistData[pRow[0]]++;
				pHistData[widthStep + pRow[1]]++;
				pHistData[widthStep * 2 + pRow[2]]++;
			}
		}
	}

	return 1;
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
