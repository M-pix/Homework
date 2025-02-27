#include <iostream>
#include "Image.hpp"

Image::Image(int rows, int cols, int channels) : Image_rows(rows), Image_cols(cols), Image_channels(channels) {
	if (rows <= 0 || cols <= 0 || channels <= 0) {
		std::cout << "Non valid argument";
		std::abort();
	}

	Image_data = new unsigned char[rows * cols * channels];
	*Image_count_link += 1;
}

Image::Image(int rows, int cols, int channels, unsigned char* data) : Image_rows(rows), Image_cols(cols), Image_channels(channels), Image_data(data) {
	if (rows <= 0 || cols <= 0 || channels <= 0) {
		std::cout << "Non valid argument";
		std::abort();
	}
	*Image_count_link += 1;
}

Image::Image(const Image& image) : Image_rows(image.Image_rows), Image_cols(image.Image_cols), Image_channels(image.Image_channels), Image_data(image.Image_data) {
	if (image.Image_rows <= 0 || image.Image_cols <= 0 || image.Image_channels <= 0) {
		std::cout << "Non valid argument";
		std::abort();
	}
	*Image_count_link += 1;
}

Image::~Image() {
	this->release();
	if (*Image_count_link == 0) {
		delete[] Image_data;
	}
}

Image& Image::operator=(const Image& image) {
	if (&image != this) {
		Image_cols = image.Image_cols;
		Image_rows = image.Image_rows;
		Image_channels = image.Image_channels;
		*Image_count_link = *image.Image_count_link;
		delete [] Image_data;
		Image_data = image.Image_data;
		std::memcpy(Image_data, image.Image_data, Image_rows * Image_cols * Image_channels);
	}
	return *this;
}

Image Image::clone() const {
	Image image = { Image_rows,Image_cols,Image_channels };
	std::memcpy(image.Image_data, Image_data, Image_rows * Image_cols * Image_channels);
	return image;
}

void Image::copyTo(Image& image) const {
	image.Image_rows = Image_rows;
	image.Image_cols = Image_cols;
	image.Image_channels = Image_channels;
	std::memcpy(image.Image_data, Image_data, Image_rows * Image_cols * Image_channels);
}

void Image::create(int rows, int cols, int channels) const {
	rows = Image_rows;
	cols = Image_cols;
	channels = Image_channels;
}

bool Image::empty() const {
	return (Image_rows != 0 || Image_cols != 0) ?  false : true;
}

void Image::release() {
	if (*Image_count_link > 0) {
		*Image_count_link--;
		if (*Image_count_link == 0) delete this;
	}
}

Image Image::col(int x) const {
	if (x<=0) {
		std::cout << "Non valid argument";
		std::abort();
	}
	Image Image{ 1, x, Image_channels };
	for (int i = 0; i < Image_rows; i++) {
		Image.Image_data[i] = Image_data[i * Image_channels * Image_cols];
		Image.Image_data[i + 1] = Image_data[i * Image_channels * Image_cols + 1];
		Image.Image_data[i + 2] = Image_data[i * Image_channels * Image_cols + 2];
	}
	return Image;
}

Image Image::row(int y) const {
	if (y <= 0) {
		std::cout << "Non valid argument";
		std::abort();
	}
	Image Image = { y, 1,Image_channels };
	for (int i = 0; i < Image_cols; i += 3) {
		Image.Image_data[i] = Image_data[i * Image_channels * Image_rows];
		Image.Image_data[i + 1] = Image_data[i * Image_channels * Image_rows + 1];
		Image.Image_data[i + 2] = Image_data[i * Image_channels * Image_rows + 2];
	}
	return Image;

}

const unsigned char* Image::data() const {
	return Image_data;
}

unsigned char* Image::data() {
	return Image_data;
}

int Image::rows() const {
	return Image_rows;
}

int Image::cols() const {
	return Image_cols;
}

int Image::total() const {
	return Image_cols * Image_rows;
}

int Image::channels() const {
	return Image_channels;
}

unsigned char& Image::at(int index) {
	if (index <= 0 || index > Image_rows * Image_cols) {
		std::cout << "Non valid argument";
		std::abort();
	}
	return Image_data[Image_channels * index];
}

const unsigned char& Image::at(int index) const {
	if (index <= 0 || index > Image_rows * Image_cols) {
		std::cout << "Non valid argument";
		std::abort();
	}
	return Image_data[Image_channels * index];
}

Image Image::zeros(int rows, int cols, int channels) {
	if (rows <= 0 || cols <= 0 || channels <= 0) {
		std::cout << "Non valid argument";
		std::abort();
	}
	std::memset(Image_data, 0, rows * cols * channels);
	return *this;
}

Image Image::values(int rows, int cols, int channels, unsigned char value) {
	if (rows <= 0 || cols <= 0 || channels <= 0) {
		std::cout << "Non valid argument";
		std::abort();
	}
	for (int i = 0; i < Image_rows * Image_cols * Image_channels; i++) {
		Image_data[i] = value;
	}
	return *this;
}

void Image::Mirror(Mirror_Type type) {
	if (type == Mirror_Type::Horizontal) {
		unsigned char* tmp = new unsigned char(Image_channels);
		for (int i = 0; i < Image_channels * Image_cols * Image_rows / 2; i += Image_channels) {
			for (int j = 0; j < Image_channels; j++) {
				tmp[j] = Image_data[i+j];
				Image_data[i + j] = Image_data[Image_channels * Image_cols * Image_rows - i - j];
				Image_data[Image_channels * Image_cols * Image_rows - j - i] = tmp[j];
			}
		}
	}
	if (type == Mirror_Type::Vertical) {

		unsigned char *tmp = new unsigned char(Image_channels);
		for (int i = 0; i < Image_channels * Image_cols * Image_rows / 2; i += Image_channels) {
			for (int j = 0; j < Image_channels; j++) {
				tmp[j] = Image_data[i+j];
				Image_data[i+j] = Image_data[Image_channels * Image_cols * Image_rows - i - j];
				Image_data[Image_channels * Image_cols * Image_rows - i - j] = tmp[j];
			}
		}
	}
}

void Image::Rotate(double angle) {
	if (angle <=0) {
		std::cout << "Non valid argument";
		std::abort();
	}
	for (int i = 0; i < (int)(angle / 90); i++) {
		for (int y = 0; y < Image_rows; y++) {
			for (int x = 0; x < Image_cols; x++) {
				unsigned char tmp_data = Image_data[x * Image_rows + (Image_rows - y + 1)];
				Image_data[x * Image_rows + (Image_rows - y + 1)] = Image_data[y * Image_cols + x];
				Image_data[y * Image_cols + x] = tmp_data;
			}
		}
		int tmp = Image_cols;
		Image_cols = Image_rows;
		Image_rows = Image_cols;
	}
}

size_t Image::countRef() const {
	return Image_size;
}