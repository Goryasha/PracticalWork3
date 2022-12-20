#include "huge_numbers.h"
#include <math.h>

class RSA {

private:
    number p;
    number q;
    number n;
    std::vector<number> cl_keys;

    std::vector<number> key_generation() const {
        std::vector<number> keys;
        number phi = (p - 1) * (q - 1);
        number e;
        for (int i = 4; i < phi; ++i) {
            e = i;
            if (simplicity_test(e)) {
                bool flag = true;
                for (int j = 2; j <= std::min(e, phi); ++j) {
                    if (e % j == 0 and phi % j == 0) {
                        flag = false;
                    }
                }
                if (flag) {
                    break;
                }
            }
        }
        keys.push_back(e);
        number d = reverse_element((int) phi, (int) e);
        keys.push_back(d);
        return keys;
    }


public:

    RSA(number p_, number q_) {
        p = p_;
        q = q_;
        n = p_ * q_;
        cl_keys = key_generation();
    }

    std::vector<number> encode(const std::string &s) {
        std::vector<number> ans;
        std::vector<number> formated_string = format_string(s);
        std::string temp;
        std::string res;
        for (int i = 0; i < formated_string.size(); ++i) {
            temp = "";
            number j = 0;
            while ((1 << j) <= formated_string[i]) {
                if ((1 << j) & formated_string[i]) {
                    temp = "1" + temp;
                } else {
                    temp = "0" + temp;
                }
                j++;
            }
            while (temp.size() != 5) {
                temp = "0" + temp;
            }
            res.append(temp);
        }
        temp = "";
        number t = 0;
        for (int i = 0; i < res.size(); ++i) {
            temp = res[i] + temp;
            if (temp.size() == 9 or i == res.size() - 1) {
                while (temp.size() != 9) {
                    temp = "0" + temp;
                }
                for (int j = 0; j < temp.size(); ++j) {
                    if (temp[j] == '1') {
                        t += pow(2, (8 - j));
                    }
                }
                ans.push_back(exponentiation(t, power_decomposition(cl_keys[0]), n));
                temp = "";
                t = 0;
            }
        }
        return ans;
    }

    std::string decode(std::vector<number> s) {
        std::cout << "Decode" << std::endl;
        std::string ans;
        std::string st;
        std::vector<number> formated_string;
        for (int i = 0; i < s.size(); ++i) {
            formated_string.push_back(exponentiation(s[i], power_decomposition(cl_keys[1]), n));
        }
        std::string temp = "";
        for (int i = 0; i < formated_string.size(); ++i) {
            number j = 0;
            while ((1 << j) <= formated_string[i]) {
                if ((1 << j) & formated_string[i]) {
                    temp = "1" + temp;
                } else {
                    temp = "0" + temp;
                }
                j++;
            }
            st += temp;
            temp = "";
        }
        number t = 0;
        for (int i = 0; i < st.size(); ++i) {
            temp += st[i];
            if (temp.size() == 5) {
                for (int j = 0; j < temp.size(); ++j) {
                    if (temp[j] == '1') {
                        t += pow(2, (4 - j));
                    }
                }
                ans += get_char(t);
                temp = "";
                t = 0;
            }
        }
        return ans;
    }


    static std::vector<number> attack(std::vector<number> y, number e, number n) {
        number step;
        std::vector<number> previouse;
        for (int i = 0; i < y.size(); ++i) {
            for (int j = 1; j < 100; ++j) {
                if (y[i] == exponentiation(exponentiation(y[i], power_decomposition(pow(e, j - 1)), n),
                                           power_decomposition(e), n)) {
                    step = j;
                    std::cout<<j<<std::endl;
                    break;
                }
            }
            previouse.push_back(exponentiation(y[i], power_decomposition(pow(e, step - 1)), n));
        }
        return previouse;
    }

};

