#include <iostream>
#include <iomanip>
#include <vector>
#include "AES.h"

int main() {
    // 明文
    std::vector<std::vector<unsigned short int> > a = {
        {'E', 'a', 'r', 'f'},
        {'g', 'r', 'e', 'o'},
        {'g', 'e', 'a', 'o'},
        {'s', 'g', 't', 'd'},
    };

    std::cout << "a: " << std::endl;
    for (auto& i : a) {
        for (auto& j : i) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << j << " ";
        }
        std::cout << std::endl;
    }

    // 种子秘钥,随机生成
    std::vector<std::vector<unsigned short int> > m = {
        {0x6A, 0x74, 0x65, 0x6E},
        {0x69, 0x61, 0x69, 0x69},
        {0x6E, 0x69, 0x6A, 0x74},
        {0x69, 0x6D, 0x69, 0x61},
    };

    // 计算轮秘钥
    cal_round_key(m);

    // 划分为十一个秘钥
    std::vector<std::vector<std::vector<unsigned short>>> mix_key = splitMatrix(m, 4);

    // 密文
    std::vector<std::vector<unsigned short int> > c = a;

    // 加密过程
    add_key(c, mix_key[0]);
    for (int i=1; i<=9; i++) {
        byte_substitution(c);
        row_shift(c);
        column_confusion(c);
        add_key(c, mix_key[i]);
    }
    byte_substitution(c);
    row_shift(c);
    add_key(c, mix_key[10]);

    std::cout << "ciphertext: " << std::endl;
    for (auto& i : c) {
        for (auto& j : i) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << j << " ";
        }
        std::cout << std::endl;
    }

    // 解密过程
    add_key(c, mix_key[10]);
    for (int i=9; i>=1; i--) {
        row_shift_inv(c);
        byte_substitution_inv(c);
        add_key(c, mix_key[i]);
        column_confusion_inv(c);
    }
    row_shift_inv(c);
    byte_substitution_inv(c);
    add_key(c, mix_key[0]);


    // 最终解密数据
    std::cout << "all done: " << std::endl;
    for (auto& i : c) {
        for (auto& j : i) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << j << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
