#include <iostream>
#include "Image.hpp"

Image::Image() {

}
Image::Image(int rows, int cols, int channels) : Image_rows(rows), Image_cols(cols), Image_channels(channels) {
	Image_data = new unsigned char[rows * cols * channels];
	Image_count_link += 1;
}

Image::Image(int rows, int cols, int channels, unsigned char* data) : Image_rows(rows), Image_cols(cols), Image_channels(channels), Image_data(data) {
	Image_count_link += 1;
}

Image::Image(const Image& image) : Image_rows(image.Image_rows), Image_cols(image.Image_cols), Image_channels(image.Image_channels), Image_data(image.Image_data) {
	Image_count_link += 1;
}

Image::~Image() {
	this->release();
	if (Image_count_link == 0) {
		delete[] Image_data;
	}
}

Image& Image::operator=(const Image& image) {
	if (&image != this) {
		this = Image(image);
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
	Image image = {rows, cols, channels };
}

bool Image::empty() const {
	if (Image_rows != 0 || Image_cols != 0) return false;
	return true;
}

void Image::release() {
	if (Image_count_link > 0) {
		Image_count_link--;
		if (Image_count_link == 0) delete this;
	}
}

Image Image::col(int x) const {
	Image Image{ 1, x, Image_channels };
	for (int i = 0; i < Image_rows; i++) {
		Image.Image_data[i] = Image_data[i * Image_channels * Image_cols];
		Image.Image_data[i + 1] = Image_data[i * Image_channels * Image_cols + 1];
		Image.Image_data[i + 2] = Image_data[i * Image_channels * Image_cols + 2];
	}
	return Image;
}

Image Image::row(int y) const {
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

unsigned char* Image::data() const {
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

unsigned char& Image::at(int index) const {
	return Image_data[Image_channels * index];
}

const unsigned char& Image::at(int index) const {
	return Image_data[Image_channels * index];
}

Image Image::zeros(int rows, int cols, int channels) {
	for (int i = 0; i < Image_rows * Image_cols * Image_channels; i++) {
		Image_data[i] = 0;
	}
	return *this;
}

Image Image::values(int rows, int cols, int channels, unsigned char value) {
	for (int i = 0; i < Image_rows * Image_cols * Image_channels; i++) {
		Image_data[i] = value;
	}
	return *this;
}

void Image::Mirror(Mirror_Type type) {
	if (type == Mirror_Type::Horizontal) {
		unsigned char tmp[2];
		for (int i = 0; i < Image_channels * Image_cols * Image_rows / 2; i += 3) {
			tmp[0] = Image_data[i];
			tmp[1] = Image_data[i + 1];
			tmp[2] = Image_data[i + 2];
			Image_data[i] = Image_data[Image_channels * Image_cols * Image_rows - 2 - i];
			Image_data[i + 1] = Image_data[Image_channels * Image_cols * Image_rows - 1 - i];
			Image_data[i + 2] = Image_data[Image_channels * Image_cols * Image_rows - i];
			Image_data[Image_channels * Image_cols * Image_rows - 2 - i] = tmp[0];
			Image_data[Image_channels * Image_cols * Image_rows - 1 - i] = tmp[1];
			Image_data[Image_channels * Image_cols * Image_rows - i] = tmp[2];
		}
	}
	if (type == Mirror_Type::Vertical) {
		unsigned char tmp[2];
		for (int i = 0; i < Image_channels * Image_cols * Image_rows / 2; i += 3) {
			tmp[0] = Image_data[i];
			tmp[1] = Image_data[i + 1];
			tmp[2] = Image_data[i + 2];
			Image_data[i] = Image_data[Image_channels * Image_cols * Image_rows - 2 - i];
			Image_data[i + 1] = Image_data[Image_channels * Image_cols * Image_rows - 1 - i];
			Image_data[i + 2] = Image_data[Image_channels * Image_cols * Image_rows - i];
			Image_data[Image_channels * Image_cols * Image_rows - 2 - i] = tmp[0];
			Image_data[Image_channels * Image_cols * Image_rows - 1 - i] = tmp[1];
			Image_data[Image_channels * Image_cols * Image_rows - i] = tmp[2];
		}
	}
}

void Image::Rotate(double angle) {
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
	return Image_count_link;
}