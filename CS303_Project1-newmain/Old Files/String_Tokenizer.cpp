#include "String_Tokenizer.h"
using std::string;

// function for setting the indicies of next token
void String_Tokenizer::find_next() {
    //get the index of the first non delimiter
    start = source.find_first_not_of(delim, end);
    // get the index of the first instance of delimiter after
    // start of token
    end = source.find_first_of(delim, start);
}

// returns if it had reached end of string
bool String_Tokenizer::has_next() {
    return start != string::npos;
}

// function that returns the next token in string
string String_Tokenizer::next_token() {
    if(!has_next()) {
        return "";
    }
    // assing token substring to token variable
    std::string token = source.substr(start, end - start);
    // get next token ready to be read
    find_next();
    return token;
}
