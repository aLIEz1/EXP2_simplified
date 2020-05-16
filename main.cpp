#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>

struct Tree {
    char data;
    struct Tree *lChild;
    struct Tree *rChild;
};

Tree *CreatTree() {
    Tree *T = NULL;
    char c;
    std::cin >> c;
    if (c == '#') {
        T = NULL;
    } else {
        T = (Tree *) malloc(sizeof(Tree));
        T->data = c;
        T->lChild = CreatTree();
        T->rChild = CreatTree();
    }
    return T;
}

void PreOrder(Tree *T) {
    if (T == NULL) {
        return;
    } else {
        std::cout << T->data;
        PreOrder(T->lChild);
        PreOrder(T->rChild);
    }
}

void InOrder(Tree *T) {
    if (T == NULL) {
        return;
    } else {
        InOrder(T->lChild);
        std::cout << T->data;
        InOrder(T->rChild);
    }
}

void LaOrder(Tree *T) {
    if (T == NULL) {
        return;
    } else {
        LaOrder(T->lChild);
        LaOrder(T->rChild);
        std::cout << T->data;
    }
}

int CalcHeight(Tree *T) {
    if (T == NULL) {
        return 0;
    }
    return std::max(CalcHeight(T->lChild), CalcHeight(T->rChild)) + 1;
}

int CalcWidth(Tree *T) {
    if (T == NULL) {
        return 0;
    } else {
        int maxWidth = 0;
        if (T->lChild == NULL && T->rChild == NULL) {
            return 1;
        } else {
            maxWidth = std::max(CalcWidth(T->lChild) + CalcWidth(T->rChild), maxWidth);
        }
        return maxWidth;
    }
}

int CalcWidthByQueue(Tree *T) {
    int Last;
    int Current;
    int maxWidth = 0;
    std::queue<Tree *> tqueue;
    if (T == NULL) {
        return 0;
    } else {
        Last = 1;
        tqueue.push(T);
    }
    while (!tqueue.empty()) {
        while (Last != 0) {
            T = tqueue.front();
            tqueue.pop();
            if (T->lChild != NULL) {
                tqueue.push(T->lChild);
            }
            if (T->rChild != NULL) {
                tqueue.push(T->rChild);
            }
            Last--;
        }
        Current = tqueue.size();
        Last = Current;
        maxWidth = maxWidth > Current ? maxWidth : Current;
    }
    return maxWidth;
}

void PrintPath(std::vector<Tree *> &path) {
    for (int i = 0; i < path.size(); i++) {
        std::cout << path[i]->data;
    }

}

void FindPath(Tree *T, char data, std::vector<Tree *> &path) {
    if (T == NULL) {
        return;
    }
    path.push_back(T);
    if (T->data == data) {
        PrintPath(path);
        return;
    }
    if (T->lChild != NULL) {
        FindPath(T->lChild, data, path);
    }
    if (T->rChild != NULL) {
        FindPath(T->rChild, data, path);
    }
    path.pop_back();
}

int main() {
    Tree *root = NULL;
    root = CreatTree();
    char c;
    std::cin >> c;
    std::vector<Tree *> path;
//    PreOrder(root);
//    std::cout << "\n";
//    InOrder(root);
//    std::cout << "\n";
//    LaOrder(root);
//    std::cout << CalcHeight(root) << " " << CalcWidthByQueue(root);
    FindPath(root, c, path);
}