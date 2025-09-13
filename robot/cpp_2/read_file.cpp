#include <iostream>
#include <fstream>
#include <string>

bool printFile(const std::string &filename)
{
    std::ifstream file(filename);

    // 检查文件是否成功打开
    if (!file.is_open())
    {
        std::cerr << "Error: Can not Open file: \"" << filename << "\"." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        size_t firstNonSpace = line.find_first_not_of(" \t");

        // 跳过空行
        if (firstNonSpace == std::string::npos)
        {
            continue;
        }

        // 检查从第一个非空白字符开始是否是 "//"
        // 跳过注释行
        if (line.substr(firstNonSpace, 2) == "//")
        {
            continue;
        }

        std::cout << line << std::endl;
    }

    file.close();
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage:\n"
                  << argv[0] << " <file-name> [<file-name1> ...]" << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        std::string filename = argv[i];
        printFile(filename);
    }

    return 0;
}