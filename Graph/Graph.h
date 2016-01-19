//
// Created by Alexander Simpson on 2016-01-08.
//

#ifndef VIDEOSYNTH_GRAPH_H
#define VIDEOSYNTH_GRAPH_H

class Graph {
public:
    Graph* parent;
    Graph* firstChild;
    Graph* nextSibling;
    Graph* prevSibling;

    virtual void calc();
    void insertGraphAfter(Graph *toInsert, Graph *afterGraph);
    void remove();
    void insertAsFirstChildOf(Graph *toInsert, Graph *parent);
    int countNodes();
    virtual ~Graph(){}
};

#endif //VIDEOSYNTH_GRAPH_H
