//analyzer.h

#ifndef ANALYZER_H
#define ANALYZER_H
#include "common.h"
#include "database.h"
//·µ»ØÖµ
typedef struct Analyzer_Result {
    StringItem* carBrandAnalyze;
    StringItem* carModelAnalyze;
    StringItem* carPriceAnalyze;
    StringItem* carAgeAnalyze;
    StringItem* carFaultAnalyze;
    StringItem* statusAnalyze;
    StringItem* dateAnalyze;
    StringItem* inPriceAnalyze;
    StringItem* outPriceAnalyze;
    StringItem* estimatePriceAnalyze;
    StringItem* realPriceAnalyze;
    StringItem* sellerAnalyze;
    StringItem* buyerAnalyze;
    StringItem* handlerAnalyze;
    StringItem* employeeAnalyze;
    StringItem* totalAnalyze;
} Analyzer_Result;
#define ANALYZER_RESULT_LINE_MALLOC_SIZE 256
void freeAnalyzerResult(Analyzer_Result* result);
Analyzer_Result* getAnalyzerResult(ListNode* nodelink);




#endif