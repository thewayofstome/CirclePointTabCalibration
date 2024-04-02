#include <iostream>
#include <filesystem>
#include <vector>

#include "opencv2/opencv.hpp"



std::vector<std::string> list_files(const std::string& path)
{
    namespace fs=std::filesystem;
    if(!std::filesystem::exists(path))
    {
        std::cout<<"not find path!\n";
        return std::vector<std::string>();
    }
    std::vector<std::string> files;
    for(const auto& entry:fs::directory_iterator(path))
    {
        files.push_back(entry.path().string());
    }
    return files;
}

int sort_files(std::vector<std::string>& files)
{
    std::sort(files.begin(),files.end(),[](const auto&first,const auto&second){
        namespace fs=std::filesystem;
        fs::file_time_type ft1=fs::last_write_time(first);
        fs::file_time_type ft2=fs::last_write_time(second);

        return ft1<ft2;
    });
    return 0;
}

int main()
{
    std::vector<std::string> files=list_files(R"(F:\test\circle_point_calibration\pics\calibtab)");
    sort_files(files);
    for(const auto& file:files)
    {
        std::cout<<file<<'\n';
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}