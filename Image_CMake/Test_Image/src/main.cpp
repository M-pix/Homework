
#include "test_image.hpp"
#include "Image.hpp"

TEST(TEST_CONSTRUCTOR_1, test_image) {
	Image* img = new Image();
	ASSERT_EQ(img->rows(), 0);
	ASSERT_EQ(img->cols(), 0);
	ASSERT_EQ(img->channels(), 0);
	ASSERT_EQ(img->data(), nullptr);
}

TEST(TEST_CONSTRUCTOR_2, test_image) {
	Image* img = new Image(10, 10, 3);
	ASSERT_EQ(img->rows(), 10);
	ASSERT_EQ(img->cols(), 10);
	ASSERT_EQ(img->channels(), 3);
	ASSERT_EQ(img->data(), nullptr);
	img->~Image();
	Image* img_1 = new Image(190, 104, 31);
	ASSERT_EQ(img_1->rows(), 190);
	ASSERT_EQ(img_1->cols(), 104);
	ASSERT_EQ(img_1->channels(), 31);
	ASSERT_EQ(img_1->data(), nullptr);
	img->~Image();
}

TEST(TEST_CONSTRUCTOR_3, test_image) {
	unsigned char* data_1 = new unsigned char();
	Image* img = new Image(10, 10, 3, data_1);
	ASSERT_EQ(img->rows(), 10);
	ASSERT_EQ(img->cols(), 10);
	ASSERT_EQ(img->channels(), 3);
	ASSERT_EQ(img->data(), data_1);
	img->~Image();
	unsigned char* data_2 = new unsigned char();
	//const char* tmp[3] = "33";
	//data_2 = &tmp;
	Image* img_1 = new Image(190, 104, 31, data_2);
	ASSERT_EQ(img_1->rows(), 190);
	ASSERT_EQ(img_1->cols(), 104);
	ASSERT_EQ(img_1->channels(), 31);
	ASSERT_EQ(img_1->data(), data_2);
	img->~Image();
}

TEST(TEST_CONSTRUCTOR_4, test_image_constructor_4) {
	unsigned char* data = new unsigned char();
	Image* img = new Image(10, 10, 3, data);
}


int main() {
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}