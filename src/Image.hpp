#ifndef IMAGE_H_
#define IMAGE_H_

#include <vector>

template< class T >
class Image
{
public:
    Image( const unsigned int _width=0, const unsigned int _height=0)
        : data( _height, std::vector<T>( _width, T() )), width( _width ), height( _height )
    {
    }

    ~Image()
    {
    }

    Image( const Image<T>& _copy )
    {
        this->width = _copy.width;
        this->height = _copy.height;
        this->data = _copy.data;
    }

    std::vector< std::vector<T> > data;

    unsigned int getWidth() {
        return width;
    }
    unsigned int getHeight() {
        return height;
    }

private:
    unsigned int width;
    unsigned int height;
};


#endif




