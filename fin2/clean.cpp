
#include <string>
#include "miniPandas.h"
int main () {
    CSVHandler csv;
    csv.cleanData("data.csv", "cleaned.csv");
    return 0;
}
