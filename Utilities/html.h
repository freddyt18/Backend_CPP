#ifndef HTML_H
#define HTML_H

#include <string>
#include <unordered_map>


class HTMLEntities {
    public:
        HTMLEntities() {
            entityMap = {
                {'<', "&lt;"},
                {'>', "&gt;"},
                {'&', "&amp;"},
                {'"', "&quot;"},
                {'\'', "&apos;"},
                {' ', "&nbsp;"}
                // Add more characters and entities here
            };

            for (const auto& pair : entityMap) {
                std::string entity = pair.second.substr(1, pair.second.size() - 2);
                charMap[entity] = pair.first;
            }
        }

        // Encode a string by replacing reserved characters with HTML entities
        std::string encode(const std::string& input) {
            std::string output;
            for (char c : input) {
                auto it = entityMap.find(c);
                if (it != entityMap.end()) {
                    output += it->second;
                } else {
                    output += c;
                }
            }
            return output;
        }

        // Decode a string by replacing HTML entities with their corresponding characters
        std::string decode(const std::string& input) {
            std::string output;
            for (size_t i = 0; i < input.size(); i++) {
                if (input[i] == '&') {
                    size_t j = input.find(';', i);
                    if (j != std::string::npos) {
                        std::string entity = input.substr(i + 1, j - i - 1);
                        auto it = charMap.find(entity);
                        if (it != charMap.end()) {
                            output += it->second;
                            i = j;
                            continue;
                        }
                    }
                }
                output += input[i];
            }
            return output;
        }

    private:
        // Map of characters to their corresponding HTML entities
        std::unordered_map<char, std::string> entityMap;

        // Map of HTML entities to their corresponding characters
        std::unordered_map<std::string, char> charMap;
};

#endif