#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// 从 utils.cpp 复制 find_all 函数
template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred) {
  std::vector<Iterator> its{begin};
  for (auto it = begin; it != end; ++it) {
    if (pred(*it))
      its.push_back(it);
  }
  its.push_back(end);
  return its;
}

int main() {
    // 示例输入字符串
    std::string source = "Hello world! This is a test.";

    // 调用 find_all 函数，以 std::isspace 作为谓词查找空白字符
    auto result = find_all(source.begin(), source.end(), ::isspace);

    // 输出结果
    std::cout << "Positions of whitespace characters (including begin and end):" << std::endl;
    for (size_t i = 0; i < result.size(); ++i) {
        if (i == 0) {
            std::cout << "Begin: " << std::distance(source.begin(), result[i]) << std::endl;
        } else if (i == result.size() - 1) {
            std::cout << "End: " << std::distance(source.begin(), result[i]) << std::endl;
        } else {
            std::cout << "Whitespace at index " << std::distance(source.begin(), result[i]) 
                      << " with character '" << *result[i] << "'" << std::endl;
        }
    }

    return 0;
}
