#ifndef AES_H
#define AES_H

// 计算轮秘钥
void cal_round_key(std::vector<std::vector<unsigned short int> >& m);

// 切分矩阵
std::vector<std::vector<std::vector<unsigned short>>> splitMatrix(const std::vector<std::vector<unsigned short>>& input, int block_size);


// 字节代换
void byte_substitution(std::vector<std::vector<unsigned short int> > &m);
// 行移位
void row_shift(std::vector<std::vector<unsigned short int> > &m);
// 列混淆
void column_confusion(std::vector<std::vector<unsigned short int> > &m);
// 轮秘钥加， 其中m2是秘钥，不能写反
void add_key(std::vector<std::vector<unsigned short int> > &, std::vector<std::vector<unsigned short int> > &);

// 字节代换逆函数
void byte_substitution_inv(std::vector<std::vector<unsigned short int> > &m);
// 行移位的逆函数
void row_shift_inv(std::vector<std::vector<unsigned short int>> &m);
// 列混淆逆函数
void column_confusion_inv(std::vector<std::vector<unsigned short int>> &m);


#endif //AES_H
