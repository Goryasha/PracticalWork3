#ifndef PRACTICALWORK3_HUGE_NUMBERS_H
#define PRACTICALWORK3_HUGE_NUMBERS_H

#include <vector>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <string>

typedef unsigned long long number;
const unsigned long long iter_number=100;
const std::string ALPHABET = " abcdefghijklmnopqrstuvwxyz-',:.";


number exponentiation(number a,std::vector<int> k,number n);

bool simplicity_test(number n);

std::vector<int> power_decomposition (number n);

int reverse_element(int a,int b);

std::vector<number> format_string(const std::string &s);

char get_char(number n);

#endif
