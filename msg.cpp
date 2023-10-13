#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>

#define p(x) std::cout << x << std::endl;

class QA {
public:
    std::string question;
    std::string answer;
};

class Ask_ai {
private:
    static const int max_questions = 4000;
    std::array<QA, max_questions> qa_pairs;

public:
    void OpenFile() {
        std::ifstream open_file("record.txt");
        if (!open_file) {
            std::cerr << "Failed to open file\n";
            return;
        }

        int i = 0;
        std::string line;
        while (getline(open_file, line)) {
            std::istringstream ss(line);
            getline(ss, qa_pairs[i].question, '|');
            getline(ss, qa_pairs[i].answer);
            i++;
        }
    }

    void Ai_ans(const std::string& qtn) {
        bool found = false;
        std::istringstream ss(qtn);
        std::string word;
        std::vector<std::string> words;

        while (ss >> word) {
            words.push_back(word);
        }

        for (int i = 0; i < max_questions; i++) {
            bool matches = true;
            for (const auto& word : words) {
                if (qa_pairs[i].question.find(word) == std::string::npos) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                p("Ask_ai:")
                p(qa_pairs[i].answer)
                found = true;
                break;
            }
        }

        if (!found) {
            p("Ask_ai: Question is not valid.\nMake sure always put a question mark at the end of your question.")
        }
    }
};

int main() {

    Ask_ai Ai;
    Ai.OpenFile();

    std::string input;

    p("Ask_ai: hello world, ask something about my creator. \n\n")
    while (true) {
        p("you: ")
        getline(std::cin, input);

        if (input.back() != '?') {
            input.push_back(' ');
            input.push_back('?');
        }
        Ai.Ai_ans(input);
    }
    return 0;
}
