#include<gtest/gtest.h>

#include "Image.hpp"


TEST(ImageTest_1, test_image) {
	Image* img = new Image();
	EXPECT_EQ(img->rows(), 0);
	EXPECT_EQ(img->cols(), 0);
	EXPECT_EQ(img->channels(), 0);
	EXPECT_EQ(img->data(), nullptr);
}

TEST(ImageTest_2, test_image) {
	Image* img = new Image(10, 10, 3);
	EXPECT_EQ(img->rows(), 10);
	EXPECT_EQ(img->cols(), 10);
	EXPECT_EQ(img->channels(), 3);
	EXPECT_FALSE(img->data(), nullptr);
	Image* img_1 = new Image(-190, 104, 31);
	EXPECT_EQ(img_1->rows(), 0);
	EXPECT_EQ(img_1->cols(), 0);
	EXPECT_EQ(img_1->channels(), 0);
	EXPECT_EQ(img_1->data(), nullptr);
}
TEST(ImageTest_3, test_image) {
	unsigned char* data_1 = new unsigned char();
	Image* img = new Image(10, 10, 3, data_1);
	EXPECT_EQ(img->rows(), 10);
	EXPECT_EQ(img->cols(), 10);
	EXPECT_EQ(img->channels(), 3);
	EXPECT_EQ(img->data(), data_1);
	unsigned char* data_2 = new unsigned char(3);
	Image* img_1 = new Image(-190, 104, 31, data_2);
	EXPECT_EQ(img_1->rows(), 0);
	EXPECT_EQ(img_1->cols(), 0);
	EXPECT_EQ(img_1->channels(), 0);
	EXPECT_EQ(img_1->data(), data_2);
}

TEST(ImageTest_4, test_image) {
	unsigned char* data = new unsigned char();
	const Image* img = new const Image(10, 10, 3, data);
	Image* copy_img = new Image(*img);
	EXPECT_EQ(copy_img->rows(), 10);
	EXPECT_EQ(copy_img->cols(), 10);
	EXPECT_EQ(copy_img->channels(), 3);
	EXPECT_EQ(copy_img->data(), data);
	unsigned char* data_1 = new unsigned char();
	const Image* img_1 = new Image(-10, -10, -3, data_1);
	Image* copy_img_1 = new Image(*img_1);
	EXPECT_EQ(copy_img_1->rows(), 0);
	EXPECT_EQ(copy_img_1->cols(), 0);
	EXPECT_EQ(copy_img_1->channels(), 0);
	EXPECT_EQ(copy_img_1->data(), data_1);
}

TEST(ImageTest_clone, test_image) {
	unsigned char* data = new unsigned char(3);
	data[0] = 3;
	data[1] = 100;
	data[2] = 33;
	Image* img = new Image(1, 3, 1, data);
	Image copy_img = img->clone();
	EXPECT_EQ(copy_img.rows(), 1);
	EXPECT_EQ(copy_img.cols(), 3);
	EXPECT_EQ(copy_img.channels(), 1);
	EXPECT_EQ(copy_img.data()[0], 3);
	EXPECT_EQ(copy_img.data()[1], 100);
	EXPECT_EQ(copy_img.data()[2], 33);
}

TEST(ImageTest_copyTo, test_image) {
	unsigned char* data = new unsigned char(3);
	data[0] = 3;
	data[1] = 100;
	data[2] = 33;
	Image* img = new Image(1, 3, 1, data);
	Image* copy_img  = new Image() ;
	img->copyTo(*copy_img);
	EXPECT_EQ(copy_img->rows(), 1);
	EXPECT_EQ(copy_img->cols(), 3);
	EXPECT_EQ(copy_img->channels(), 1);
	EXPECT_EQ(copy_img->data()[0], 3);
	EXPECT_EQ(copy_img->data()[1], 100);
	EXPECT_EQ(copy_img->data()[2], 33);
}

TEST(ImageTest_empty, test_image) {
	unsigned char* data = new unsigned char(3);
	data[0] = 3;
	data[1] = 100;
	data[2] = 33;
	Image* img = new Image(1, 3, 1, data);
	EXPECT_EQ(img->empty(), false);
	Image* img_1 = new Image();
	EXPECT_EQ(img_1->empty(), true);
}

TEST(ImageTest_realese, test_image) {
	unsigned char* data = new unsigned char(3);
	data[0] = 3;
	data[1] = 100;
	data[2] = 33;
	Image* img = new Image(1, 3, 1, data);
	Image img_1 = *img;
	Image img_2{ img_1 };
	EXPECT_EQ(img->countRef(), 3);
}

TEST(ImageTest_col, test_image) {
	unsigned char* data = { new unsigned char[] { 1,2,3,4,5,6,7,8,9 } };
	Image* img = new Image(3, 3, 1, data);
	Image img_1 = img->col(1);
	EXPECT_EQ(img_1.data()[0], 1);
	EXPECT_EQ(img_1.data()[1], 4);
	EXPECT_EQ(img_1.data()[2], 7);
	Image img_2 = img->col(2);
	EXPECT_EQ(img_2.data()[0], 2);
	EXPECT_EQ(img_2.data()[1], 5);
	EXPECT_EQ(img_2.data()[2], 8);
}

TEST(ImageTest_row, test_image) {
	unsigned char* data = { new unsigned char[] { 1,2,3,4,5,6,7,8,9 } };
	Image* img = new Image(3, 3, 1, data);
	Image img_1 = img->row(1);
	EXPECT_EQ(img_1.data()[0], 1);
	EXPECT_EQ(img_1.data()[1], 2);
	EXPECT_EQ(img_1.data()[2], 3);
	Image img_2 = img->row(2);
	EXPECT_EQ(img_2.data()[0], 4);
	EXPECT_EQ(img_2.data()[1], 5);
	EXPECT_EQ(img_2.data()[2], 6);
}

TEST(ImageTest_zeros, test_image) {
	Image* img = new Image();
	Image* img_1 = new Image();
	*img_1 = img->zeros(3, 4, 1);
	for (int i = 0; i < 12; ++i) EXPECT_EQ(img_1->data()[i], 0);
}

TEST(ImageTest_values, test_image) {
	Image* img = new Image();
	Image* img_1 = new Image();
	*img_1 = img->values(6, 10, 1, 5);
	for (int i = 0; i < 60; ++i) EXPECT_EQ(img_1->data()[i], 5);
}

TEST(ImageTest_Mirror_horrizontal, test_image) {

	unsigned char* data = { new unsigned char[] { 1,2,3,4,
												  5,6,7,8,
												  9,10,11,12,
												  13,14,15,16} 
	};

	unsigned char* horizontal = { new unsigned char[] { 13,14,15,16,
														9,10,11,12,
														5,6,7,8,
														1,2,3,4} 
	};
	Image* img_1 = new Image(4, 4, 1, data);
	img_1->Mirror(Mirror_Type::Horizontal);
	for (int i = 0; i < 16; ++i) {
		EXPECT_EQ(img_1->data()[i], horizontal[i]);
	}
}

TEST(ImageTest_Mirror_vertical, test_image) {

	unsigned char* data = { new unsigned char[] { 1,2,3,4,
												  5,6,7,8,
												  9,10,11,12,
												  13,14,15,16}
	};

	unsigned char* vertical = { new unsigned char[] { 4,3,2,1,
													  8,7,6,5,
													  12,11,10,9,
													  16,15,14,13}
	};
	Image* img_1 = new Image(4, 4, 1, data);
	img_1->Mirror(Mirror_Type::Vertical);
	for (int i = 0; i < 16; ++i) {
		EXPECT_EQ(img_1->data()[i], vertical[i]);
	}
}

TEST(ImageTest_Rotate, test_image) {
	unsigned char* data = { new unsigned char[] { 1,2,3,4,
												  5,6,7,8,
												  9,10,11,12,
												  13,14,15,16,
												  17,18,19,20} };

	unsigned char* rotate = { new unsigned char[] { 17,13,9,5,1,
													  18,14,10,6,2,
													  19,15,11,7,3,
													  20, 16,12,8,4,} };

	Image* img = new Image(5, 4, 1, data);
	img->Rotate(90);
	for (int i=0; i<20;++i)
	EXPECT_EQ(img->data()[i], rotate[i]);
}






