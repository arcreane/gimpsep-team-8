#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Image.h"

class Transformation {
public:
    virtual void apply(Image& image) const = 0;
};

#endif // TRANSFORMATION_H
