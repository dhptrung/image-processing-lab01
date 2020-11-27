// Converter.cpp
#include "Converter.h"

// Hàm chuyển đổi không gian màu của ảnh từ RGB sang GrayScale
int Converter::RGB2GrayScale(const Mat& sourceImage, Mat& destinationImage) 
{
	if (sourceImage.data == NULL)
		return 1;

	int width = sourceImage.cols;
	int height = sourceImage.rows;
	int srcChannels = sourceImage.channels();

	destinationImage = Mat(height, width, CV_8UC1);
	int dstChannels = destinationImage.channels();

	for (int y = 0; y < height; y++) 
	{
		const uchar* pSrcRow = sourceImage.ptr<uchar>(y);
		uchar* pDstRow = destinationImage.ptr<uchar>(y);

		for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += dstChannels) 
		{
			uchar B = pSrcRow[0];
			uchar G = pSrcRow[1];
			uchar R = pSrcRow[2];
			uchar gray_val = uchar(0.3 * R + 0.59 * G + 0.11 * B);
			pDstRow[0] = gray_val;
		}
	}

	return 0;
}

// Hàm chuyển đổi không gian màu của ảnh từ GrayScale sang RGB
int Converter::GrayScale2RGB(const Mat& sourceImage, Mat& destinationImage) 
{
	if (sourceImage.data == NULL)
		return 1;

	int width = sourceImage.cols;
	int height = sourceImage.rows;
	int srcChannels = sourceImage.channels();

	destinationImage = Mat(height, width, CV_8UC3);
	int dstChannels = destinationImage.channels();

	for (int y = 0; y < height; y++) 
	{
		const uchar* pSrcRow = sourceImage.ptr<uchar>(y);
		uchar* pDstRow = destinationImage.ptr<uchar>(y);

		for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += dstChannels) 
		{
			uchar gray_val = pSrcRow[0];
			pDstRow[0] = gray_val;
			pDstRow[1] = gray_val;
			pDstRow[2] = gray_val;
		}
	}

	return 0;
}

// Hàm chuyển đổi không gian màu của ảnh từ RGB sang HSV
int Converter::RGB2HSV(const Mat& sourceImage, Mat& destinationImage) 
{
	if (sourceImage.data == NULL)
		return 1;

	int width = sourceImage.cols;
	int height = sourceImage.rows;
	int srcChannels = sourceImage.channels();

	destinationImage = Mat(height, width, CV_32FC3);
	int dstChannels = destinationImage.channels();

	for (int y = 0; y < height; y++)
	{
		const uchar* pSrcRow = sourceImage.ptr<uchar>(y);
		uchar* pDstRow = destinationImage.ptr<uchar>(y);

		for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += dstChannels)
		{
			uchar B = pSrcRow[0];
			uchar G = pSrcRow[1];
			uchar R = pSrcRow[2];

			// (0, 1)
			double r = double(R / 255);
			double g = double(G / 255);
			double b = double(B / 255);

			double min, max, delta;
			double h, s, v;

			// min(r, g, b)
			min = r < g ? r : g;
			min = min < b ? min : b;

			// max(r, g, b)
			max = r > g ? r : g;
			max = max > b ? max : b;

			delta = max - min;

			v = max;
			if (delta > 0)
			{
				if (max == r)
					h = (g - b) / delta;
				else if (max == g)
					h = 2.0 + (b - r) / delta;
				else
					h = 4.0 + (r - g) / delta;

				if (max > 0)
					s = delta / max;
				else
					s = 0;
			}
			else
			{
				s = 0;
				h = NAN;
			}

			h *= 60;
			if (h < 0.0)
				h += 360;

			//
			pDstRow[0] = v;
			pDstRow[1] = s;
			pDstRow[2] = h;
		}
	}

	return 0;
}

// Hàm chuyển đổi không gian màu của ảnh từ HSV sang RGB
int Converter::HSV2RGB(const Mat& sourceImage, Mat& destinationImage) 
{

}


// Hàm chuyển đổi không gian màu của ảnh
int Converter::Convert(Mat& sourceImage, Mat& destinationImage, int type) 
{

}

int Converter::Convert(IplImage* sourceImage, IplImage* destinationImage, int type) 
{

}

Converter::Converter() 
{
}

Converter::~Converter() 
{
}
