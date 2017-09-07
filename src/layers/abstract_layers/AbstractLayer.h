//
// Created by Amr on 8/22/17.
//

#ifndef INFERENCEENGINE_LAYER_H
#define INFERENCEENGINE_LAYER_H

#include <vector>
#include <string>
#include "../../Matrix.h"

class AbstractLayer {
public:
    std::string name;

    explicit AbstractLayer(std::string name) : name(name) {};

    virtual ~AbstractLayer() = default;

    virtual void calculateOutput(Matrix &input_mat) = 0;
};

#endif //INFERENCEENGINE_LAYER_H
