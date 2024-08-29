// #include "training.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgread.hpp>
// #include <torch/torch.h>
#include <iostream>

const int BATCHSIZE = 1;
const int EPOCH = 100;
const double learning_rate = 0.001;


int main(int argc, char** argv) 
{

  // std::string data_path = TRAIN_DATE_DIR + "/basic_model_data/train";
  // CustomDatasetWithLabel dataset(data_path, BATCHSIZE);

  // auto data_loader = dataset.create_dataloader();
  // std::unordered_map<int, std::string> label_decoding_map = dataset.decoding_mapping();

  // // BasicModel model(label_decoding_map.size());
  // auto model = std::make_shared<BasicModel>(label_decoding_map.size());


  // auto optimizer = torch::optim::SGD(model->parameters(), torch::optim::SGDOptions(learning_rate));

  // torch::nn::CrossEntropyLoss criterion;

  // training(model, data_loader, EPOCH, learning_rate, optimizer, DEVICE, criterion);
  // Check if image file is provided
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <Image_Path>" << std::endl;
        return -1;
    }

    // Read the image file
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);

    // Check for failure
    if (image.empty())
    {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }

    // Convert the image to grayscale
    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    // Create a window
    cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Grayscale Image", cv::WINDOW_AUTOSIZE);

    // Show the images
    cv::imshow("Original Image", image);
    cv::imshow("Grayscale Image", gray_image);

    // Wait for any keystroke in the window
    cv::waitKey(0);

    // Destroy all windows
    cv::destroyAllWindows();


  return 0;
}
