#include <torch/torch.h>
#include "basic_model.h"

int main() {
  torch::Tensor tensor = torch::rand({2, 3});
  std::cout << tensor << std::endl;
}