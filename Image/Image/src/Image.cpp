#include <iostream>
#include <cmath>
#include "Image.hpp"

Image::Image(int rows, int cols, int channels) : Image() {
	create(rows, cols, channels);
	Image_count_link = new size_t(1);
}

Image::Image(int rows, int cols, int channels, unsigned char* data) : Image() {
	create(rows, cols, channels);
	Image_data = data;
	Image_count_link = new size_t(1);
}

Image::Image(const Image& image): Image() {
	create(image.Image_rows, image.Image_cols, image.Image_channels);
	Image_data = image.Image_data;
	Image_count_link = image.Image_count_link;
	if (Image_count_link == nullptr) {
		Image_count_link = new size_t(1);
	}
	else {
		*Image_count_link += 1;
	}
}

Image::~Image() {
	release();
	if (*Image_count_link == 0) {
		delete[] Image_data;
	}
}

Image& Image::operator=(const Image& image) {
	if (&image != this) {
		Image_cols = image.Image_cols;
		Image_rows = image.Image_rows;
		Image_channels = image.Image_channels;
		Image_count_link = image.Image_count_link;
		*Image_count_link = *image.Image_count_link + 1;
		delete[] Image_data;
		Image_data = image.Image_data;
		std::memcpy(Image_data, image.Image_data, Image_rows * Image_cols * Image_channels);
	}
	return *this;
}

Image Image::clone() const {
	unsigned char* data = new unsigned char(Image_rows * Image_cols * Image_channels);
	std::memcpy(data, Image_data, Image_rows * Image_cols * Image_channels);
	Image image = { Image_rows,Image_cols,Image_channels, data };
	return image;
}

void Image::copyTo(Image& image) const {
	unsigned char* data = new unsigned char(Image_rows * Image_cols * Image_channels);
	std::memcpy(data, Image_data, Image_rows * Image_cols * Image_channels);
	image.Image_rows = Image_rows;
	image.Image_cols = Image_cols;
	image.Image_channels = Image_channels;
	image.Image_data = data;
}

void Image::create(int rows, int cols, int channels) {
	try {
		if (rows <= 0 || cols <= 0 || channels <= 0) {
			throw "Invalid create";
		}
		Image_rows = rows;
		Image_cols = cols;
		Image_channels = channels;
	}
	catch (const char* error_message) {
		std::cout << error_message;
	}
}

bool Image::empty() const {
	return (Image_rows == 0 || Image_cols == 0);
}

void Image::release() {
	if (Image_count_link == nullptr);
	else if (*Image_count_link > 0) { // default 
		*Image_count_link--;
	}
}

Image Image::col(int x) const {
	try {
		if (x <= 0 || empty()) {
			throw "Invalid function col";
		}
		unsigned char* data = new unsigned char(x * Image_channels);
		Image image{ 1, x, Image_channels, data };
		for (int i = 0; i < Image_rows; i += Image_channels) {
			for (int j = 0; j < Image_channels; ++j) image.Image_data[i * Image_channels + j] = Image_data[x + i * Image_cols + j - 1];
		}
		return image;
	}
	catch (const char* error_message) {
		std::cout << error_message;
		Image img{ 0,0,0 };
		return img;
	}
}

Image Image::row(int y) const {
	try {
		if (y <= 0 || empty()) {
			throw "Invalid function row";
		}
		unsigned char* data = new unsigned char(y * Image_channels);
		Image Image{ y, 1, Image_channels, data };
		for (int i = 0; i < Image_cols; i += Image_channels) {
			for (int j = 0; j < Image_channels; ++j) Image.Image_data[i + j] = Image_data[i + j + (y - 1) * Image_cols];
		}
		return Image;
	}
	catch (const char* error_message) {
		std::cout << error_message;
		Image img{ 0,0,0 };
		return img;
	}
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
	return  Image_cols * Image_rows;
}

int Image::channels() const {
	return  Image_channels;
}

unsigned char& Image::at(int index) {
	try{
		if (index <= 0 || index > Image_rows * Image_cols || empty()) {
			throw "Invalid fuction at";
		}
		return Image_data[index];
	}
	catch	(const char* error_message){
		std::cout << error_message;
	}
}

const unsigned char& Image::at(int index) const {
	try {
		if (index <= 0 || index > Image_rows * Image_cols || empty()) {
			throw "Invalid function const at";
		}
		return Image_data[index];
	}
	catch (const char* error_message) {
		std::cout << error_message;
	}
}

Image Image::zeros(int rows, int cols, int channels) const {
	try {
		if (rows <= 0 || cols <= 0 || channels <= 0) {
			throw "Invalid function zeros";
		}
		unsigned char* data = new unsigned char(rows * cols * channels);
		std::memset(data, 0, rows * cols * channels);
		Image img{ rows,cols,channels,data };
		return img;
	}
	catch (const char* error_message) {
		std::cout << error_message;
		Image img{ 0,0,0 };
		return img;
	}
}

Image Image::values(int rows, int cols, int channels, unsigned char value) const {
	try {
		if (rows <= 0 || cols <= 0 || channels <= 0) {
			throw "Invalid function values";
		}
		unsigned char* data = new unsigned char(rows * cols * channels);
		Image img{ rows,cols,channels,data };
		std::memset(img.Image_data, value, rows * cols * channels);
		return img;
	}
	catch (const char* error_message) {
		std::cout << error_message;
		Image img{ 0,0,0 };
		return img;
	}
}

void Image::Mirror(Mirror_Type type) {
	try {
		if (!empty) throw "Invalid function mirror";
		if (type == Mirror_Type::Horizontal) {
			unsigned char tmp;
			for (int k = 1; k <= Image_rows / 2; ++k) {
				for (int i = 0; i < Image_channels * Image_cols; ++i) {
					tmp = Image_data[i + Image_cols * (k - 1)];
					Image_data[i + (k - 1) * Image_cols] = Image_data[Image_channels * Image_rows * (Image_cols - k) + i];
					Image_data[Image_channels * Image_cols * (Image_rows - k) + i] = tmp;
				}
			}
		}
		if (type == Mirror_Type::Vertical) {
			unsigned char tmp;
			for (int k = 0; k < Image_rows; ++k) {
				for (int i = 0; i < Image_channels * Image_cols / 2; i += Image_channels) {
					for (int j = 0; j < Image_channels; ++j) {
						tmp = Image_data[i + j + k * Image_cols];
						Image_data[i + j + k * Image_cols] = Image_data[Image_channels * Image_cols / 2 - i - j + 1 + k * Image_cols];
						Image_data[Image_channels * Image_cols / 2 - i - j + 1 + k * Image_cols] = tmp;
					}
				}
			}
		}
	}
	catch (const char* error_message) {
		std::cout << error_message;
	}
}

void Image::Rotate(double angle) {
	try {
		if (fmod(angle, 90.0) != 0 || empty) {
			throw "Invalid function rotate";
		}
		if (angle > 270) {
			angle = (int)angle % 360;
		}
		if (angle < -270) {
			angle = -abs((int)angle) % 360;
		}
		if (angle < 0) {
			angle = 360 + angle;
		}
		unsigned char* tmp_data = new unsigned char(Image_cols * Image_rows * Image_channels);
		for (int i = 0; i < (int)(angle / 90); ++i) {
			for (int y = 0; y < Image_rows; ++y)
				for (int x = 0; x < Image_cols; x += Image_channels)
					for (int j = 0; j < Image_channels; ++j)
						tmp_data[x * Image_rows + (Image_rows - y - 1) + j] = Image_data[y * Image_cols + x + j];
			for (int i = 0; i < Image_rows * Image_channels * Image_cols; ++i)
				Image_data[i] = tmp_data[i];
			int tmp = Image_cols;
			Image_cols = Image_rows;
			Image_rows = Image_cols;

		}
	}
	catch (const char* error_message) {
		std::cout << error_message;
	}
}

size_t Image::countRef() const {
	if (Image_count_link == nullptr) return 0;
	return *Image_count_link;
}


