#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string &source) {
  /* TODO: Implement this method */
  // 步骤1: 找出所有空白字符的迭代器
  auto spaceIt = find_all(source.begin(), source.end(), ::isspace);

  // 步骤2: 生成 Token 对象
  Corpus tokens;
  std::transform(
      spaceIt.begin(), std::prev(spaceIt.end()), std::next(spaceIt.begin()),
      std::inserter(tokens, tokens.end()),
      [&source](auto it1, auto it2) { return Token(source, it1, it2); });

  // 步骤3: 使用 std::erase_if 移除空 Token
  std::erase_if(tokens,
                [](const Token &token) { return token.content.empty(); });
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus &source,
                                 const Dictionary &dictionary) {
  /* TODO: Implement this method */
  namespace rv = std::ranges::views;

  auto view = source
              // 步骤1: 跳过正确拼写的单词
              | rv::filter([&dictionary](const Token &token) {
                  return dictionary.find(token.content) == dictionary.end();
                })
              // 步骤2: 为每个拼写错误的单词找出字典中编辑距离为 1 的建议词
              |
              rv::transform([&dictionary](const Token &token) {
                auto suggestions_view =
                    dictionary | rv::filter([&token](const std::string &word) {
                      return levenshtein(token.content, word) == 1;
                    });
                std::set<std::string> suggestions(suggestions_view.begin(),
                                                  suggestions_view.end());
                return Misspelling{token, suggestions};
              })
              // 步骤3: 移除没有建议词的拼写错误项
              | rv::filter([](const Misspelling &misspelling) {
                  return !misspelling.suggestions.empty();
                });

  // 将视图转换为 std::set<Misspelling>
  return std::set<Misspelling>(view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"