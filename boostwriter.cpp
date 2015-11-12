#include "boostwriter.h"

BoostWriter::BoostWriter(boost::lockfree::queue<int> *q)
{
    queue = q;
}

int insert = 0;
void BoostWriter::run() {
    while (insert <= 10000000) {
        if (queue -> bounded_push(insert)) {
            insert++;
        }
    }
}

