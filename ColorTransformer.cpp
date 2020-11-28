﻿// ColorTransformer.cpp
#include "ColorTransformer.h"

// Hàm nhận vào một ảnh, thay đổi độ sáng của ảnh này và lưu kết quả vào ảnh mới
int ColorTransformer::ChangeBrighness(const Mat& sourceImage, Mat& destinationImage, short b) 
{
	if (sourceImage.data == nullptr)
		return 0;
	int width = sourceImage.cols, height = sourceImage.rows, srcchannels = sourceImage.channels();
	destinationImage = Mat(height, width, CV_8UC3);
	int dstchannels = destinationImage.channels();
	uchar lookup[256];
	for (int i = 0; i < 256; i++)
		lookup[i] = min(255, max(0, i + b));

	for (int y = 0; y < height; y++)
	{
		const uchar* srcpRows = sourceImage.ptr<uchar>(y);
		uchar* dstpRows = destinationImage.ptr<uchar>(y);

		for (int x = 0; x < width; x++, srcpRows += srcchannels, dstpRows += dstchannels)
		{
			uchar B = srcpRows[0];
			uchar G = srcpRows[1];
			uchar R = srcpRows[2];

			dstpRows[0] = lookup[B];
			dstpRows[1] = lookup[G];
			dstpRows[2] = lookup[R];
		}
	}
	if (destinationImage.data == nullptr)
		return 0;
	else
		return 1;
}

// Hàm nhận vào một ảnh, thay đổi độ tương phản của ảnh này và lưu kết quả vào ảnh mới
int ColorTransformer::ChangeContrast(const Mat& sourceImage, Mat& destinationImage, float c) 
{
	if (sourceImage.data == nullptr)
		return 0;
	int width = sourceImage.cols, height = sourceImage.rows, srcchannels = sourceImage.channels();
	destinationImage = Mat(height, width, CV_8UC3);
	int dstchannels = destinationImage.channels();
	uchar lookup[256];
	for (int i = 0; i < 256; i++)
		lookup[i] = min(255, max(0, i * c));

	for (int y = 0; y < height; y++)
	{
		const uchar* srcpRows = sourceImage.ptr<uchar>(y);
		uchar* dstpRows = destinationImage.ptr<uchar>(y);

		for (int x = 0; x < width; x++, srcpRows += srcchannels, dstpRows += dstchannels)
		{
			uchar B = srcpRows[0];
			uchar G = srcpRows[1];
			uchar R = srcpRows[2];

			dstpRows[0] = lookup[B];
			dstpRows[1] = lookup[G];
			dstpRows[2] = lookup[R];
		}
	}
	if (destinationImage.data == nullptr)
		return 0;
	else
		return 1;
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
	if (sourceImage.data == NULL)
		return 0;

	Mat histMatrix;
	CalcHistogram(sourceImage, histMatrix);

	int width = sourceImage.cols, height = sourceImage.rows;
	int srcChannels = sourceImage.channels();
	cout << srcChannels << endl;
	if (srcChannels == 1)
		destinationImage = Mat(height, width, CV_8UC1);
	else
		destinationImage = Mat(height, width, CV_8UC3);

	vector<vector<long long>> T(srcChannels, vector<long long>(256));

	for (int y = 0; y < srcChannels; y++) {
		uchar* pHistRow = histMatrix.ptr<uchar>(y);
		T[y][0] = int(pHistRow[0]);
		for (int x = 1; x < 256; x++) {
			T[y][x] = T[y][x - 1] + pHistRow[x];
		}
	}

	for (int y = 0; y < srcChannels; y++) {
		uchar* pHistRow = histMatrix.ptr<uchar>(y);
		int minVal = T[y][0];
		int maxVal = T[y][255];
		for (int x = 1; x < 256; x++) {
			T[y][x] = uchar(((1.0 * (T[y][x] - minVal)) / (maxVal - minVal)) * 255.0);
		}
	}

	for (int y = 0; y < height; y++) {
		const uchar* pSrcRow = sourceImage.ptr<uchar>(y);
		uchar* pDstRow = destinationImage.ptr<uchar>(y);
		for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += srcChannels) {
			if (srcChannels == 1) {
				pDstRow[0] = T[0][pSrcRow[0]];
			}
			else {
				pDstRow[0] = T[0][pSrcRow[0]];
				pDstRow[1] = T[1][pSrcRow[1]];
				pDstRow[2] = T[2][pSrcRow[2]];
			}
		}
	}

	return 1;
}

// Hàm cân bằng lược đồ màu tổng quát cho ảnh bất kỳ
int ColorTransformer::DrawHistogram(const Mat& histMatrix, Mat& histImage) 
{
	Mat histMatrix_cl = histMatrix.clone(); //clone histMatrix for later usage
	
	if (!Normalize(histMatrix_cl)) //normalize the (cloned) histogram matrix
		return 0;

	int height = 300;
	int width = 260;
	uint16_t* pHistData = (uint16_t*)histMatrix_cl.data;
	
	//the histogram images array
	Mat* histImageArray = new Mat[histMatrix_cl.rows];

	if (histMatrix_cl.rows == 1) {
		Point_<int> text_pos = Point_<int>(90, 20); //set up the text position in the image 
		char name[10] = "GRAYSCALE"; 
		histImageArray[0] = Mat(300, 260, CV_8UC1, Scalar(0)); 
		putText(histImageArray[0], //writing text into the image
			name,
			text_pos,
			FONT_HERSHEY_PLAIN,
			0.8,
			Scalar(255, 255, 255),
			1,
			LINE_8);
		histImage = Mat(height, width, CV_8UC1);
	}
	else { //same as above
		char name[4][2] = { "B","G","R" };
		Point_<int> text_pos = Point_<int>(120, 20);
		for (int i = 0; i < histMatrix_cl.rows; i++) { //initialize histogram images for each color channel 
			histImageArray[i] = Mat(300, 260, CV_8UC1, Scalar(0));
			putText(histImageArray[i],
				name[i],
				text_pos,
				FONT_HERSHEY_PLAIN,
				0.8,
				Scalar(255, 255, 255),
				1,
				LINE_8);
		}
		histImage = Mat(height,width*3,CV_8UC1);
	}

	//drawing the histogram image(s)
	for (int i = 0; i < histMatrix_cl.rows; i++) {
		for (int j = 0; j < histMatrix_cl.cols; j++) {
				int index = i * histMatrix_cl.cols + j;
				uchar value = pHistData[index];
				Point_<int> begin = Point_<int>(index % 256, height);
				Point_<int> end = Point_<int>(index % 256, height - value);
				line(histImageArray[i], begin, end, (255, 255, 255), 1);
		}
	}
	//merge histogram image(s) together
	for (int i = 0; i < histMatrix_cl.rows; i++) {
		histImageArray[i].copyTo(histImage(Rect(i*width, 0, width, height)));
	}

	return 1;
}
//Hàm chuẩn hoá các giá trị trong histogram matrix về khoảng 0-255
//this function normalize the histogram matrix values into range (0-255)
int ColorTransformer::Normalize(Mat& histMatrix)
{
	if (histMatrix.empty()) { //check if the histogram matrix is empty
		return 0;
	}

	int height = histMatrix.rows;
	int width = histMatrix.cols;
	uint16_t* pHistData = (uint16_t*)histMatrix.data;
	int max = 0;

	//find max value
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int index = i * width+ j;
			if (pHistData[index] > max)
				max = pHistData[index];
		}
	}

	//normalize
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int index = i * width + j;
			pHistData[index] = (uchar)(255 * (float)pHistData[index] / (float)max);
		}
	}

	return 1;
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
