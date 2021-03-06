/*
 * Entry.cc
 *
 *  Created on: Nov 23, 2014
 *      Author: xyz
 */

#include "Entry.h"
#include "Gradient.h"
#include <set>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

using namespace std;

Entry::Entry(string type, long timestamp, int source, int dataRate,
        long duration, int neighbour) {
    this->type = type;
    this->timestamp = timestamp;
    this->source = source;
    this->addGradient(dataRate, duration, neighbour, timestamp);
}

Gradient* Entry::addGradient(int dataRate, long duration, int neighbour,
        long currTime) {
    Gradient g = Gradient(dataRate, duration, neighbour, currTime);
    set<Gradient>::iterator prevG = gradients.find(g);
    if (prevG != gradients.end()) {
        Gradient *tmp = new Gradient(*prevG);
        gradients.erase(prevG);
        gradients.insert(g);
        return tmp;
    } else {
        gradients.insert(g);
        return NULL;
    }
}

vector<int> Entry::getPaths(long currTime) {
    vector<int> paths;
    set<Gradient>::iterator it = gradients.begin();
    int min = min_element(gradients.begin(), gradients.end())->getDataRate();
    while (it != gradients.end()) {
        if (currTime > it->getExpiry()) {
            gradients.erase(it++);
            continue;
        }
        if (it->getDataRate() == min) {
            paths.insert(paths.begin(), it->getNeighbour());
        }
        it++;
    }
    return paths;
}

int Entry::getMinInterval() {
    if (gradients.empty()) {
        return 0;
    }
    return min_element(gradients.begin(), gradients.end())->getDataRate();
}

long Entry::getTimestamp() const {
    return timestamp;
}

const string Entry::getType() const {
    return type;
}

string Entry::toString() {
    stringstream ss;
    ss << "Entry [type: " << type << " timestamp: " << timestamp
            << " gradients: ";
    for (auto it = gradients.begin(); it != gradients.end(); ++it) {
        ss << it->toString() << ", ";
    }
    ss << "]";
    return ss.str();
}

int cmp(const Entry &a, const Entry &b) {
    if (a.getType().compare(b.getType()) == 0) {
        return 1;
    } else {
        return 0;
    }
}

bool operator==(const Entry& a, const Entry& b) {
    return cmp(a, b) == 1;
}

int Entry::getSource() const {
    return source;
}
