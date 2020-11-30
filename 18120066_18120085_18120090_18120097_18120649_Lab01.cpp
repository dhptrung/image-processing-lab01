// 18120066_18120085_18120090_18120097_18120649_Lab01.cpp

#include "Converter.h"
#include "ColorTransformer.h"

int main(int argc, char* argv[])
{
	// 1a. RGB -> GrayScale
	if (strcmp(argv[1], "--rgb2gray") == 0) 
	{
		Mat sourceImage = imread(argv[2], CV_LOAD_IMAGE_COLOR);
		Mat destinationImage;
		Converter* convert = new Converter;
		
		// 0: thành công, 1: thất bại
		if (!convert->Convert(sourceImage, destinationImage, 0))
		{
			imwrite("destinationImage.jpg", destinationImage);
			imshow("Source Image", sourceImage);
			imshow("Destination Image", destinationImage);
		}
		else
			cout << "That bai do input rong.";
	}

	// 1b. GrayScale -> RGB
	else if (strcmp(argv[1], "--gray2rgb") == 0)
	{
		Mat sourceImage = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
		Mat destinationImage;
		Converter* convert = new Converter;

		// 0: thành công, 1: thất bại
		if (!convert->Convert(sourceImage, destinationImage, 1))
		{
			imwrite("destinationImage.jpg", destinationImage);
			imshow("Source Image", sourceImage);
			imshow("Destination Image", destinationImage);
		}
		else
			cout << "That bai do input rong.";
	}

	// 2a. RGB -> HSV
	else if (strcmp(argv[1], "--rgb2hsv") == 0)
	{
		Mat sourceImage = imread(argv[2], CV_LOAD_IMAGE_COLOR);;
		Mat destinationImage;
		Converter* convert = new Converter;

		// 0: thành công, 1: thất bại
		if (!convert->Convert(sourceImage, destinationImage, 2))
		{
			imwrite("destinationImage.jpg", destinationImage);
			imshow("Source Image", sourceImage);
			imshow("Destination Image", destinationImage);

			// Lấy kết quả trên chuyển ngược lại RGB để kiểm tra
			// độ giống nhau của ảnh sourceImage và hsv2rgbImage là tương đối
			Mat hsv2rgbImage;
			convert->Convert(destinationImage, hsv2rgbImage, 3);
			imshow("hsv2rgbImage_toTest", hsv2rgbImage);
		}
		else
			cout << "That bai do input rong.";
	}

	// 2b. HSV -> RGB
	else if (strcmp(argv[1], "--hsv2rgb") == 0)
	{
		Mat sourceImage = imread(argv[2], CV_LOAD_IMAGE_COLOR);
		Mat destinationImage;
		Converter* convert = new Converter;

		Mat rgb2hsvImage;
		
		// 0: thành công, 1: thất bại
		// Vì không thể đọc ảnh ở kênh màu HSV nên ta thực hiện chuyển từ rgb2hsv trước
		// để lấy dữ liệu input cho hàm hsv2rgb
		if (!convert->Convert(sourceImage, rgb2hsvImage, 2))
		{
			convert->Convert(rgb2hsvImage, destinationImage, 3);
			imwrite("destinationImage.jpg", destinationImage);
			imshow("Source Image", sourceImage);
			imshow("Destination Image", destinationImage);
			// chứa dữ liệu của ảnh có kênh màu HSV 
			imshow("rgb2hsvImage_toGetData", rgb2hsvImage);
		}
		else
			cout << "That bai do input rong.";
	}

	// 3. Tăng giảm độ sáng cho ảnh
	else if (strcmp(argv[1], "--bright") == 0)
	{
		Mat sourceImage = imread(argv[2], CV_LOAD_IMAGE_COLOR);
		Mat destinationImage;
		ColorTransformer* transform = new ColorTransformer;

		// 1: thành công, 0: thất bại
		if (transform->ChangeBrighness(sourceImage, destinationImage, atoi(argv[3])))
		{
			imwrite("destinationImage.jpg", destinationImage);
			imshow("Source Image", sourceImage);
			imshow("Destination Image", destinationImage);
		}
		else
			cout << "That bai do input rong." << endl;
	}

	// 4. Tăng giảm độ tương phản cho ảnh
	else if (strcmp(argv[1], "--contrast") == 0)
	{
		Mat sourceImage = imread(argv[2], CV_LOAD_IMAGE_COLOR);
		Mat destinationImage;
		ColorTransformer* transform = new ColorTransformer;

		// 1: thành công, 0: thất bại
		if (transform->ChangeContrast(sourceImage, destinationImage, atoi(argv[3])))
		{
			imwrite("destinationImage.jpg", destinationImage);
			imshow("Source Image", sourceImage);
			imshow("Destination Image", destinationImage);
		}
		else
			cout << "That bai do input rong." << endl;
	}

	// 5. Tính histogram
	else if (strcmp(argv[1], "--hist") == 0)
	{
		Mat sourceImage = imread(argv[2], CV_LOAD_IMAGE_COLOR);
		ColorTransformer* transform = new ColorTransformer;
		Mat histMatrix;

		// 1: thành công, 0: thất bại
		if (transform->CalcHistogram(sourceImage, histMatrix))
		{
			cout << "Histogram: " << endl;
			cout << histMatrix;
		}
		else
			cout << "That bai do input rong." << endl;

	}

	// 6. Cân bằng histogram
	else if (strcmp(argv[1], "--equalhist") == 0)
	{
		Mat sourceImage = imread(argv[2], CV_LOAD_IMAGE_COLOR);
		Mat destinationImage;
		ColorTransformer* transform = new ColorTransformer;

		// 1: thành công, 0: thất bại
		if (transform->HistogramEqualization(sourceImage, destinationImage))
		{
			imwrite("destinationImage.jpg", destinationImage);
			imshow("Source Image", sourceImage);
			imshow("Destination Image", destinationImage);
		}
		else
			cout << "That bai do input rong." << endl;
	}

	// 7. Vẽ histogram
	else if (strcmp(argv[1], "--drawhist") == 0)
	{
		Mat sourceImage = imread(argv[2], CV_LOAD_IMAGE_COLOR);
		Mat hisMatrix, histImage;
		
		ColorTransformer* transform = new ColorTransformer;
		transform->CalcHistogram(sourceImage, hisMatrix);
	
		// 1: thành công, 0: thất bại
		if (transform->DrawHistogram(hisMatrix, histImage))
		{
			//imwrite("histImage.jpg", histImage);
			imshow("Source Image", sourceImage);
			imshow("Histogram Image", histImage);
		}
		else
			cout << "That bai do input rong." << endl;
	}

	// 8. So sánh 2 ảnh bằng histogram 
	else if (strcmp(argv[1], "--compare") == 0)
	{
		Mat image1 = imread(argv[2], CV_LOAD_IMAGE_COLOR);
		Mat image2 = imread(argv[3], CV_LOAD_IMAGE_COLOR);
		ColorTransformer* transform = new ColorTransformer;

		float diff;
		// return -1 nếu input rỗng
		diff = transform->CompareImage(image1, image2);

		if (diff == -1)
			cout << "Loi do input rong." << endl;
		else
			cout << "Do do su tuong dong giua 2 anh: " << diff << endl;
	}

	waitKey(0);
	return 0;
}
