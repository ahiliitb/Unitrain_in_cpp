#include "training.h"
#include <iostream>

const int BATCHSIZE = 1;
const int EPOCH = 100;
const double learning_rate = 0.001;


int main() 
{

  std::string data_path = TRAIN_DATE_DIR + "/basic_model_data/train";
  CustomDatasetWithLabel dataset(data_path, BATCHSIZE);

  auto data_loader = dataset.create_dataloader();
  std::unordered_map<int, std::string> label_decoding_map = dataset.decoding_mapping();

  // BasicModel model(label_decoding_map.size());
  auto model = std::make_shared<BasicModel>(label_decoding_map.size());


  auto optimizer = torch::optim::SGD(model->parameters(), torch::optim::SGDOptions(learning_rate));

  torch::nn::CrossEntropyLoss criterion;

  training(model, data_loader, EPOCH, learning_rate, optimizer, DEVICE, criterion);

  return 0;
}
