#include "dataloader.h"

void training(auto &model, auto &data_loader_with_unique, const int EPOCH, const double learning_rate, auto &optimizer, auto device, auto &loss_function)
{
    auto& data_loader = *data_loader_with_unique;
    for (int epoch = 0; epoch < EPOCH; epoch++)
    {
        model->train();
        size_t batch_idx = 0;
        for (auto &batch : data_loader)
        {
            for(auto &example : batch)
            {
                auto data = example.data.to(device), targets = example.target.to(device);
                optimizer.zero_grad();
                auto output = model->forward(data);
                auto loss = loss_function(output, targets);
                loss.backward();
                optimizer.step();

                if (batch_idx++ % 5 == 0)
                {
                    std::cout << "Train Epoch: " << epoch << " [" << batch_idx << "/" << example.data.size(0) << "]\tLoss: " << loss.item() << std::endl;
                }
            }
        }
    }
}