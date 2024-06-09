#ifndef DILATATIONEROSION_H
#define DILATATIONEROSION_H

#include "Transformation.h"

class DilatationErosion : public Transformation {
public:
    DilatationErosion(bool dilate, int size);
    void apply(Image& image) override;

private:
    bool dilate;
    int size;
};

#endif
