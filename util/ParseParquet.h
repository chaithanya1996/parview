//
// Created by chaithanya on 06/08/20.
//

#ifndef PARVIEW_PARSEPARQUET_H
#define PARVIEW_PARSEPARQUET_H

#include "string"

using std::string;

class ParseParquet {
public:
    static string getCsv(string path);
    static string getHead(const string& path, int counH = 50);
    static string getTail(const string& path, int coun = 50);
};


#endif //PARVIEW_PARSEPARQUET_H
