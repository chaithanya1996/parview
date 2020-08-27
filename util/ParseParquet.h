//
// Created by chaithanya on 06/08/20.
//

#ifndef PARVIEW_PARSEPARQUET_H
#define PARVIEW_PARSEPARQUET_H

#include <arrow/api.h>
#include "string"

using arrow::Table;
using std::string;

class ParseParquet {
public:
    static string getCsv(string path);
    static void getHead(const string& path, int counH = 50);
    static void getTail(const string& path, int coun = 50);
    static std::vector<int> getTableFormatters();
    static void writeHeader(std::shared_ptr<Table> table);
    static void writeTable(std::shared_ptr<Table> table);
};


#endif //PARVIEW_PARSEPARQUET_H
