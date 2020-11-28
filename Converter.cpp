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
	/*
	+ source image HSV
		B, G, R: [0, 255] uchar
	+ destination image BGR
		H: [0, 360) float
		S, V: [0, 1] float
	*/

	// Kiểm tra sourceImage lỗi
	if (sourceImage.data == NULL || sourceImage.channels() != 3)
		return 1;

	// Các thông số kích thước ảnh sourceImage
	int width = sourceImage.cols;
	int height = sourceImage.rows;
	int srcChannels = sourceImage.channels();

	// Tạo destinationImage có thông số thích hợp
	destinationImage = Mat(height, width, CV_32FC3, Scalar(0));
	int dstChannels = destinationImage.channels();

	/*
	for (int y = 0; y < height; y++)
	{
		const uchar* pSrcRow = sourceImage.ptr<uchar>(y);
		float* pDstRow = destinationImage.ptr<float>(y);

		for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += dstChannels)
		{
			uchar B = pSrcRow[0];
			uchar G = pSrcRow[1];
			uchar R = pSrcRow[2];

			// (0, 1)
			double r = double(R / 255.0);
			double g = double(G / 255.0);
			double b = double(B / 255.0);

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
	*/

	// Duyệt từng pixel R, G, B của sourceImage
	// Convert sang H, S, V và lưu vào destinationImage
	for (int y = 0; y < height; y++)
	{
		const uchar* pSrcRow = sourceImage.ptr<uchar>(y);
		float* pDstRow = destinationImage.ptr<float>(y);

		for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += dstChannels)
		{
			// Lấy thông số R, G, B (uchar) từ sourceImage
			uchar iB = pSrcRow[0];
			uchar iG = pSrcRow[1];
			uchar iR = pSrcRow[2];

			float fB = float(iB) / 255;
			float fG = float(iG) / 255;
			float fR = float(iR) / 255;

			// Các giá trị trung gian cần cho quá trình convert sang H, S, V
			float max, min, delta;
			// Biến chứa kết quả giá trị H, S, V
			float H = 0, S = 0, V = 0;

			// Tìm max(R, G, B)
			char flag = 'b';
			max = fB;
			if (fG > max)
			{
				max = fG;
				flag = 'g';
			}
			if (fR > max)
			{
				max = fR;
				flag = 'r';
			}

			// Tìm min(R, G, B)
			min = fB;
			if (fG < min)
				min = fG;
			if (fR < min)
				min = fR;

			// Xác định V
			V = max;
			delta = max - min;

			// Xác định S
			if (max < 0.0001)
				S = 0;
			else
				S = delta / max;

			// Xác định H
			if (delta < 0.0001)
			{
				H = 0;
			}
			else
			{
				// H được xác định tùy trường hợp max rơi vào R, G hoặc B
				if (flag == 'r')
				{
					H = 60 * (fG - fB) / delta;
				}
				else if (flag == 'g')
				{
					H = 60 * (2 + (fB - fR)) / delta;
				}
				else if (flag == 'b')
				{
					H = 60 * (4 + (fR - fG)) / delta;
				}
			}

			if (H < 0)
				H += 360;

			// Gán giá trị H, S, V cho điểm ảnh của destinationImage
			pDstRow[0] = H;
			pDstRow[1] = S;
			pDstRow[2] = V;
		}
	}

	return 0;
}

// Hàm chuyển đổi không gian màu của ảnh từ HSV sang RGB
int Converter::HSV2RGB(const Mat& sourceImage, Mat& destinationImage) 
{
	/*
	+ source image HSV
		H: [0, 360) float
		S, V: [0, 1] float
	+ destination image BGR
		B, G, R: [0, 255] uchar
	*/

	// Kiểm tra sourceImage lỗi
	if (sourceImage.data == NULL || sourceImage.channels() != 3)
	{
		return 1;
	}

	// Các thông số kích thước ảnh sourceImage
	int nRow = sourceImage.rows;
	int nCol = sourceImage.cols;
	int nChannels = sourceImage.channels();

	// Tạo destinationImage có thông số thích hợp
	destinationImage = Mat(nRow, nCol, CV_8UC3, Scalar(0));

	// Duyệt từng pixel H, S, V của sourceImage
	// Convert sang R, G, B và lưu vào destinationImage
	for (int y = 0; y < nRow; y++)
	{
		const float* pSrcRow = (float*)sourceImage.ptr(y);
		uchar* pDestRow = (uchar*)destinationImage.ptr(y);

		for (int x = 0; x < nCol; x++, pSrcRow += nChannels, pDestRow += nChannels)
		{
			// Lấy thông số H, S, V (float) từ sourceImage
			float fH = pSrcRow[0];
			float fS = pSrcRow[1];
			float fV = pSrcRow[2];

			// Tính các giá trị trung gian cần thiết
			float fHquote = fH / 60;	// H' = H/60
			float fC = fV * fS;			// C = V * S
			float fX = fC * (1 - fabs(int(fHquote) % 2 - 1));	// X = C(1 - |H' mod 2 - 1|)

			// Xác định giá trị R, G, B (float) tùy vào từng trường hợp của fHquote
			float fR = 0, fG = 0, fB = 0;
			if (fHquote < 0 || fHquote >= 6)
			{
				fR = fG = fB = 0;
			}
			else if (fHquote >= 0 && fHquote < 1)
			{
				fR = fC;
				fG = fX;
			}
			else if (fHquote >= 1 && fHquote < 2)
			{
				fR = fX;
				fG = fC;
			}
			else if (fHquote >= 2 && fHquote < 3)
			{
				fG = fC;
				fB = fX;
			}
			else if (fHquote >= 3 && fHquote < 4)
			{
				fG = fX;
				fB = fC;
			}
			else if (fHquote >= 4 && fHquote < 5)
			{
				fR = fX;
				fB = fC;
			}
			else if (fHquote >= 5 && fHquote < 6)
			{
				fR = fC;
				fB = fX;
			}

			// Hiệu chỉnh giá trị R, G, B (float)
			float m = fV - fC;
			fR += m;
			fG += m;
			fB += m;

			// Convert giá trị R, G, B sang uchar và lưu vào destinationImage
			pDestRow[0] = uchar(fB * 255);
			pDestRow[1] = uchar(fG * 255);
			pDestRow[2] = uchar(fR * 255);
		}
	}

	return 0;
}


// Hàm chuyển đổi không gian màu của ảnh
int Converter::Convert(Mat& sourceImage, Mat& destinationImage, int type) 
{
	switch (type)
	{
	case 0:
		return this->RGB2GrayScale(sourceImage, destinationImage);
	case 1:
		return this->GrayScale2RGB(sourceImage, destinationImage);
	case 2:
		return this->RGB2HSV(sourceImage, destinationImage);
	case 3:
		return this->HSV2RGB(sourceImage, destinationImage);
	default:
		break;
	}

	// Trường hợp lỗi
	return 1;
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
