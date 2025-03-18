namespace linus {
    namespace calculator {
        std::string input = "0";
        char lastOp = 0;
        bool newInput = true;
        double result = 0.0;

        void calculate(char op) {
            static double storedValue = 0.0;
            double currentValue = std::stod(input);

            if (lastOp) {
                switch (lastOp) {
                case '+': storedValue += currentValue; break;
                case '-': storedValue -= currentValue; break;
                case '*': storedValue *= currentValue; break;
                case '/': storedValue = (currentValue != 0) ? storedValue / currentValue : 0.0; break;
                }
            }
            else {
                storedValue = currentValue;
            }

            if (storedValue == static_cast<int>(storedValue)) {
                input = std::to_string(static_cast<int>(storedValue));
            }
            else {
                input = std::to_string(storedValue);
                input.erase(input.find_last_not_of('0') + 1, std::string::npos);
                if (input.back() == '.') input.pop_back();
            }

            lastOp = (op == '=') ? 0 : op;
            newInput = true;
        }
    }
}