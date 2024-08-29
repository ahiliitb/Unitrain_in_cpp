#include <torch/torch.h>
#include "constants.h"
#include <opencv2/opencv.hpp>

class BasicModel : public torch::nn::Module
{
    public:
        BasicModel(const unsigned int number_of_classes)
        : conv1(torch::nn::Conv2dOptions(3, 8, 4)),
        conv2(torch::nn::Conv2dOptions(8, 16, 4)),
        linear1(16*8*8, 64),
        linear2(64, number_of_classes),
        number_of_classes(number_of_classes)
        {
            register_module("conv1", conv1);
            register_module("conv2", conv2);
            register_module("linear1", linear1);
            register_module("linear2", linear2);
        }

       torch::Tensor forward(torch::Tensor input)
       {
            input = conv1->forward(input);
            input = torch::relu(input);
            input = torch::max_pool2d(input, 4);
            input = conv2->forward(input);
            input = torch::relu(input);
            input = torch::max_pool2d(input, 2);
            input = torch::flatten(input, 1);
            input = linear1->forward(input);
            input = torch::relu(input);
            input = linear2->forward(input);

            return torch::argmax(input);
       }



        torch::nn::Conv2d conv1;
        torch::nn::Conv2d conv2;
        torch::nn::Linear linear1;
        torch::nn::Linear linear2;
        const unsigned int number_of_classes;

    private:
};