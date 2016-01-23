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
    void appendSibling(Graph *toInsert);
    void setFirstChild(Graph *toInsert);
    void remove();
    int countNodes();
    virtual ~Graph(){}
};

#endif //VIDEOSYNTH_GRAPH_H
