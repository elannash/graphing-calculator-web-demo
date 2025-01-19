#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>
#include <cstring>

#include "MyQueue.h"
#include "token.h"
#include "variable.h"
#include "operator.h"
#include "function.h"
#include "number.h"
#include "special_function.h"
#include "leftparen.h"
#include "rightparen.h"
#include "graph_info.h"
#include "argument_separator.h"

class Tokenizer
{
public:
    Tokenizer(string pre_tokenized_str);

    Queue<Token *> get_tokenized_q();
    Queue<Token *> operator()();

    void set_pre_tokenized_str(string str);
    string get_pre_tokenized_str();

private:
    void finalize_token(const std::string &token_str, Queue<Token *> &q);
    void parse_letter_buffer(const std::string &letters, Queue<Token*> &q, bool &justSkippedComma);

    string _pre_tokenized_str;
    Queue<Token *> _post_tokenized_q;
};

#endif /* TOKENIZER_H */
