//
// Created by Alexander Simpson on 2016-01-08.
//

#include <stddef.h>
#include "Graph.h"

void Graph::calc() {
    // Execute depth first
    if (firstChild) {
        firstChild->calc();
    }
    if (nextSibling) {
        nextSibling->calc();
    }
}

int Graph::countNodes() {
    int count = 1;

    if (firstChild) {
        count += firstChild->countNodes();
    }
    if (nextSibling) {
        count += nextSibling->countNodes();
    }

    return count;
}

void Graph::appendSibling(Graph *toInsert) {
    if (this->nextSibling) {
        this->nextSibling->prevSibling = toInsert;
    }
    toInsert->nextSibling = this->nextSibling;
    toInsert->parent = this->parent;
    this->nextSibling = toInsert;
    toInsert->prevSibling = this;
}

void Graph::setFirstChild(Graph *toInsert){
    this->firstChild = toInsert;
    toInsert->parent = this;
}

void Graph::remove() {
    if (this->firstChild) {
        this->firstChild->remove();
    }

    if (this->nextSibling != NULL && this->prevSibling != NULL) {
        this->prevSibling->nextSibling = this->nextSibling;
        this->nextSibling->prevSibling = this->prevSibling;
    } else if (this->nextSibling == NULL && this->prevSibling == NULL) {
        this->parent->firstChild = NULL;
    } else if (this->nextSibling == NULL) {
        this->prevSibling->nextSibling = NULL;
    } else { //this->prevSibling == NULL
        this->parent->firstChild = this->nextSibling;
        this->nextSibling->prevSibling = NULL;
    }

    delete this;
}
