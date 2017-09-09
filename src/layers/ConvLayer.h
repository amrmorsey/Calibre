//
// Created by Amr on 8/21/17.
//

#ifndef INFERENCEENGINE_CONVLAYER_H
#define INFERENCEENGINE_CONVLAYER_H

#include <string>
#include <memory>
#include <chrono>
#include "abstract_layers/AbstractLayer.h"
#include "abstract_layers/AbstractWeightedLayer.h"

#include "../utils.h"

class ConvLayer : public AbstractWeightedLayer {

private:
    int kernel_size;
    int stride;
    int padding;

public:
    ConvLayer(std::string name, int num_of_outputs, std::unique_ptr<MatrixAVX> weights, std::unique_ptr<MatrixAVX> bias,
              int kernel_size, int stride, int padding) : AbstractWeightedLayer(name, std::move(weights),
                                                                                std::move(bias),
                                                                                num_of_outputs),
                                                          kernel_size(kernel_size), stride(stride),
                                                          padding(padding) {};

    ~ConvLayer() {};

    void calculateOutput(MatrixAVX &input_mat) {
        int pad = padding;

        std::vector<int> filter_shape = this->weights.get()->shape;
        int x = input_mat.shape[0];
        x = x - filter_shape[0] + 2 * pad;
        x = floor(float(x) / float(stride));
        x = x + 1;

        int x_row = x * x;
        int x_col = 1;
        std::vector<int> X_col_shape;
        std::vector<int> W_row_shape;
        for (int i = 0; i < filter_shape.size() - 1; i++) {
            x_col *= filter_shape[i];
        }
        X_col_shape.push_back(x_col);
        X_col_shape.push_back(x_row);
        int xx = filter_shape.at(filter_shape.size() - 1);
        W_row_shape.push_back(xx);
        W_row_shape.push_back(x_col);

        //(x, y, z) = Z*(Dim_Y*Dim_X) + y*DIM_X + x
        std::vector<int> out_shape = {X_col_shape.at(0), X_col_shape.at(1)};
        MatrixAVX out(out_shape), out_dot({26, 26, 5}), out_bias(out_shape);

        im2col(input_mat, weights.get()->shape, out, stride, padding, x);
            auto start = std::chrono::system_clock::now();
    for (size_t counter = 0; counter < 10000; ++counter) {
        weights.get()->reshape({9, 5});
        out.reshape({676, 9});
        out.dot_product(*weights.get(), out_dot);
    }

    auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start) / 10000;

    std::cout << "Completed function in " << duration.count() << " microseconds." << std::endl;

//            std::cout << out_dot << std::endl;
        //out_dot.add(*bias, out_bias);
          //  std::cout << out_bias;
        input_mat = out_bias;
    };
};


#endif //INFERENCEENGINE_CONVLAYER_H
