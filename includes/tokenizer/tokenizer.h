#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <cstring>

#include "../Queue/MyQueue.h"
#include "../token/token.h"
#include "../token/variable.h"
#include "../token/operator.h"
#include "../token/function.h"
#include "../token/number.h"
#include "../token/special_function.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"
#include "../graph/graph_info.h"

bool is_number(string str);

class Tokenizer
{
public:
    Tokenizer(string pre_tokenized_str);

    Queue<Token *> get_tokenized_q(); //this tokenizes the string and returns it as a queue
    Queue<Token *> operator()();

    //debug
    void set_pre_tokenized_str(string str);
    string get_pre_tokenized_str();

private:
    string _pre_tokenized_str;
    Queue<Token *> _post_tokenized_q;
};

#endif /* TOKENIZER_H */
