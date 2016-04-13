#ifndef LIST_H_SENTRY
#define LIST_H_SENTRY

struct Node
{
    Node *next;
    char *data;
};


class List
{
public:
    Node *head;
    Node *tail;
    Node *curr;

    static void DeleteList(Node *head);
    static void PrintList(Node *head);

public:
    List();
    List &operator=(const List &);
    ~List();

    void Push(char *);
    void Append(char *);

    char *GetNext();

    void Print();
    void ResetCurr() { curr = 0; }
};

#endif
