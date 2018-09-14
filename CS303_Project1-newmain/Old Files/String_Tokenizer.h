#ifndef STRING_TOKENIZER
#define STRING_TOKENIZER

#include <string>


class String_Tokenizer {

public:
String_Tokenizer(std::string the_source,std::string the_delim=" ") :
    source(the_source), delim(the_delim), start(0), end(0) {}

bool has_next();
std::string next_token();


private:
void find_next();
size_t start;
size_t end;
std::string delim;
std::string source;



};

#endif // STRING_TOKENIZER
