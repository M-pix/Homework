enum class Mirror_Type {
    Vertical,
    Horizontal
};

class Image {
private:
    int Image_rows;
    int Image_cols;
    int Image_channels;
    size_t Image_count_link;
    unsigned char* Image_data;
public:
    Image();
    Image(int rows, int cols, int channels);
    Image(int rows, int cols, int channels, unsigned char* data);
    Image(const Image& image);
    virtual ~Image();

    Image& operator=(const Image& image);

    // Вернуть клон изборажения
    Image clone();
    //Скопировать изображение.
    void copyTo(Image& image);
    void create(int rows, int cols, int channels);
    bool empty();

    //декрементирует счетчик ссылок и в случае необходимости освобождает ресурсы (память).
    void release();

    Image col(int x);

    Image row(int y);

    const unsigned char* data() const;
    unsigned char* data();

    int rows();
    int cols();
    int total();
    int channels();

    //Вернуть ЧАСТЬ пикселя
    unsigned char& at(int index);
    const unsigned char& at(int index) const;

    Image zeros(int rows, int cols, int channels);
    Image values(int rows, int cols, int channels, unsigned char value);

    //Отразить изображение по вертикали или по горизонтали
    void Mirror(Mirror_Type type);

    //Повернуть на угол кратный 90
    void Rotate(double angle);

    //Возвращает текущее количество ссылок на изображение.
    //Т.е. количество объектов, которые ссылаются на данное изображение. Этот метод нужен для unit test'ов.
    size_t countRef();

};