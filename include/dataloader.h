#include "basic_model.h"

// Extrating dataset which has data and label and creating dataloader
class CustomDatasetWithLabel : public torch::data::datasets::Dataset<CustomDatasetWithLabel>
{
    public:
        CustomDatasetWithLabel(std::string data_dir_path, const int batch_size)
        : data_dir_path(data_dir_path),
        batch_size(batch_size)
        {}

        torch::Tensor load_image_to_tensor(const std::string &image_path)
        {
            // read image
            cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
            if(image.empty())
            {
                throw std::runtime_error("Failed to load the image: " + image_path);
            }

            // from bgr to rgb color(which tensor recognise)
            cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

            // convert to tensor
            torch::Tensor tensor_image = torch::from_blob(image.data, {image.rows, image.cols, 3}, torch::kByte);

            tensor_image = tensor_image.permute({2, 0, 1}).to(torch::kFloat32).div(255);

            return tensor_image;
        }

        void update_image_and_label_data()
        {
            std::string image_directory = data_dir_path + "/images";
            std::string label_directory = data_dir_path + "/labels";

            int label_code = 0;
            for (auto const& img_dir_entry : std::filesystem::directory_iterator{image_directory})
            {
                // converting each image to tensor and storing it in image_data vector
                torch::Tensor tensor_image = load_image_to_tensor(img_dir_entry.path());
                image_data.push_back(tensor_image);
                
                // reading label
                std::string label_file_path = label_directory + "/" + img_dir_entry.path().stem().string() + ".txt";
                std::ifstream label_file(label_file_path);
                std::string label_value;
                label_file >> label_value;
                if(label_encoding.count(label_value) == 0)
                {
                    label_encoding[label_value] = label_code;
                    label_code++;
                }
                label.push_back(torch::tensor(label_encoding[label_value], torch::kInt32));
            }
        }

         // Get method to retrieve a sample and its corresponding label
        torch::data::Example<> get(size_t index) override {
            return {image_data[index], label[index]};
        }

        // Return the size of the dataset
        torch::optional<size_t> size() const override {
            return image_data.size();
        }

        auto create_dataloader()
        {
            update_image_and_label_data();

            return torch::data::make_data_loader(*this, torch::data::DataLoaderOptions().batch_size(batch_size)); 
        }

        std::unordered_map<int, std::string> decoding_mapping()
        {
            std::unordered_map<int, std::string> decoding_map;
            for(auto map_pair: label_encoding)
            {
                decoding_map[map_pair.second] = map_pair.first;
            }
            return decoding_map;
        }

    private:
        std::vector<torch::Tensor> image_data;
        std::vector<torch::Tensor> label;
        std::string data_dir_path;
        const int batch_size;
        std::unordered_map<std::string, int> label_encoding;
};