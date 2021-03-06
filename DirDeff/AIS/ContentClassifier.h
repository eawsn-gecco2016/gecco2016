/*
 * ContentClassifier.h
 *
 *  Created on: Jan 18, 2015
 *      Author: xyz
 */

#ifndef CONTENTCLASSIFIER_H_
#define CONTENTCLASSIFIER_H_

#include "RandomNumberGenerator.h"
#include "packet_m.h"

enum class Class {
    BENIGN, MALICIOUS
};

/**
 * Class that is used to classify incoming packets into two classes.
 * For the purpose of this project the classification is mocked with an 80%
 * accuracy.
 */
class ContentClassifier {
    public:
        /**
         * @param row The row to read the seed from
         * @param column The column to read the seed from
         */
        ContentClassifier(int row, int column);
        Class classify(Packet* p);
    private:
        RandomNumberGenerator generator;
};

#endif /* CONTENTCLASSIFIER_H_ */
