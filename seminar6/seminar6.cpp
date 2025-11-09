#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <map>
#include <set>

std::vector<std::string> tokenize_line(const std::string &line, bool &in_block_comment)
{
    std::vector<std::string> tokens;
    std::string current_token;
    bool in_string = false;

    std::set<char> single_char_tokens = {
        '(', ')', '{', '}', '[', ']',
        ';', ',', '=', '+', '-', '*', '/',
        '&', '|', '^', '!', '~', '<', '>',
        '?', ':', '.', '#', '%'};

    for (size_t i = 0; i < line.length(); ++i)
    {
        char c = line[i];

        if (in_block_comment)
        {
            if (c == '*' && i + 1 < line.size() && line[i + 1] == '/')
            {
                in_block_comment = false;
                i++; // skip '/'
            }
            continue;
        }

        if (c == '/' && i + 1 < line.size() && line[i + 1] == '*')
        {
            in_block_comment = true;
            i++;
            continue;
        }

        if (c == '/' && i + 1 < line.size() && line[i + 1] == '/')
        {
            break;
        }

        if (c == '"')
        {
            if (!current_token.empty())
            {
                tokens.push_back(current_token);
                current_token.clear();
            }
            in_string = !in_string;
            continue;
        }

        if (in_string)
            continue;

        if (std::isspace(static_cast<unsigned char>(c)))
        {
            if (!current_token.empty())
            {
                tokens.push_back(current_token);
                current_token.clear();
            }
            continue;
        }

        std::string two_chars;
        if (i + 1 < line.size())
            two_chars = std::string() + c + line[i + 1];

        static const std::set<std::string> multi_ops = {
            "++", "--", "+=", "-=", "*=", "/=",
            "<<", ">>", "<=", ">=", "==", "!=",
            "&&", "||"};

        if (multi_ops.count(two_chars))
        {
            if (!current_token.empty())
            {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.push_back(two_chars);
            i++;
            continue;
        }

        if (single_char_tokens.count(c))
        {
            if (!current_token.empty())
            {
                tokens.push_back(current_token);
                current_token.clear();
            }
            tokens.push_back(std::string(1, c));
            continue;
        }

        current_token += c;
    }

    if (!current_token.empty())
        tokens.push_back(current_token);

    return tokens;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::map<std::string, int> token_counts = {
        {"main", 0},
        {"()", 0},
        {"{}", 0},
        {"int", 0},
        {"scanf", 0},
        {"&", 0},
        {"=", 0},
        {"+", 0},
        {"/", 0},
        {"printf", 0},
        {",", 0},
        {";", 0},
        {"++", 0},
        {"--", 0},
        {"+=", 0},
        {"-=", 0},
        {"/=", 0},
        {"*=", 0},
        {"<<", 0},
        {">>", 0},
        {"<", 0},
        {">", 0},
        {"<=", 0},
        {">=", 0},
        {"==", 0},
        {"!=", 0},
        {"&&", 0},
        {"||", 0},
        {"return", 0},
        {"for", 0},
        {"while", 0},
        {"if", 0},
        {"else", 0},
        {"struct", 0},
        {"enum", 0},
        {"typedef", 0}};

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::string str;
    std::vector<std::string> all_tokens;
    bool in_block_comment = false;

    while (std::getline(file, str))
    {
        std::vector<std::string> tokens = tokenize_line(str, in_block_comment);
        all_tokens.insert(all_tokens.end(), tokens.begin(), tokens.end());
    }

    int open_paren = 0, close_paren = 0;
    int open_brace = 0, close_brace = 0;

    for (size_t i = 0; i < all_tokens.size(); ++i)
    {
        std::string t = all_tokens[i];

        if (t == "(")
            open_paren++;
        else if (t == ")")
            close_paren++;
        else if (t == "{")
            open_brace++;
        else if (t == "}")
            close_brace++;
        else if (token_counts.count(t))
            token_counts[t]++;
    }
    std::map<std::string, int> operand_counts = {};
    for (size_t i = 0; i < all_tokens.size(); ++i)
    {
        std::set<char> single_char_tokens = {
            '(', ')', '{', '}', '[', ']',
            ';', ',', '=', '+', '-', '*', '/',
            '&', '|', '^', '!', '~', '<', '>',
            '?', ':', '.', '#', '%'};
        if (all_tokens[i][0] == '"')
        {
            std::cout << "found quote here " << std::endl;
            all_tokens[i] = all_tokens[i].substr(1, all_tokens[i].size() - 1);
        }
        else if (all_tokens[i].empty())
        {
            std::cout << "empty string here" << std::endl;
            continue;
        }
        else if (all_tokens[i][all_tokens.size() - 1] == '"')
        {
            all_tokens[i] = all_tokens[i].substr(0, all_tokens[i].size() - 2);
        }
        else if (all_tokens[i].size() == 1 && all_tokens[i][0] == '%')
        {
            // is_output = true;
        }
        else if (single_char_tokens.find(all_tokens[i][0]) != single_char_tokens.end())
        {
            continue;
        }
        else if (!all_tokens[i].empty() && std::isdigit(all_tokens[i][0]))
        {
            if (operand_counts.find(all_tokens[i]) == operand_counts.end())
            {
                operand_counts.insert({all_tokens[i], 1});
            }
            else
            {
                operand_counts[all_tokens[i]]++;
            }
        }
        else if (token_counts.find(all_tokens[i]) == token_counts.end())
        {
            if (operand_counts.find(all_tokens[i]) == operand_counts.end())
            {
                operand_counts.insert({all_tokens[i], 1});
            }
            else
            {
                operand_counts[all_tokens[i]]++;
            }
        }
        // std::cout << all_tokens[i] << std::endl;
    }

    for (const auto &pair : operand_counts)
    {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }

    // Count pairs
    token_counts["()"] += std::min(open_paren, close_paren);
    token_counts["{}"] += std::min(open_brace, close_brace);

    int total_occurrences = 0, distinct_types = 0;
    for (auto &[token, count] : token_counts)
    {
        if (count > 0)
        {
            total_occurrences += count;
            distinct_types++;
        }
    }

    std::cout << "\n--- Token Statistics ---\n";
    std::cout << "Distinct Token Types: " << distinct_types << "\n";
    std::cout << "Total Occurrences: " << total_occurrences << "\n";

    std::cout << "\n--- Token Counts ---\n";
    for (auto &[token, count] : token_counts)
    {
        if (count != 0)
            std::cout << token << " = " << count << "\n";
    }
    return 0;
}
