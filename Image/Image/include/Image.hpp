enum class Mirror_Type {
    Vertical,
    Horizontal
};

class Image {

private:
    int Image_rows{ 0 };
    int Image_cols{ 0 };
    int Image_channels{ 0 };
    size_t* Image_count_link = nullptr;
    unsigned char* Image_data = nullptr;

public:
    Image() = default;
    Image(int rows, int cols, int channels);
    Image(int rows, int cols, int channels, unsigned char* data);
    Image(const Image& image);
    virtual ~Image();

public:
    Image& operator=(const Image& image);

public:
    void copyTo(Image& image) const;
    void create(int rows, int cols, int channels);
    void release();
    void Mirror(Mirror_Type type);
    void Rotate(double angle);

    bool empty() const;

    unsigned char* data();
    unsigned char& at(int index);

    size_t countRef() const;

public:
    const unsigned char* data() const;
    const unsigned char& at(int index) const;

public:
    int rows() const;
    int cols() const;
    int total() const;
    int channels() const;

public:
    Image zeros(int rows, int cols, int channels) const;
    Image values(int rows, int cols, int channels, unsigned char value) const;
    Image col(int x) const;
    Image row(int y) const;
    Image clone() const;

};