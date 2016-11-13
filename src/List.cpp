#include "List.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


using WebAlbumCreator::List;

List::List()
    : head(0),
    tail(0),
    curr(0)
{}


List &List::operator=(const List &l)
{
    head = 0;
    tail = 0;
    curr = 0;
    Node *p = l.head;

    while(p) {
        Append(strdup(p->data));
        p = p->next;
    }

    return *this;
}


List::~List()
{
    DeleteList(head);
}


void List::DeleteList(Node *head)
{
    if (head) {
        if (!head) DeleteList(head->next);

        free(head->data);
        delete head;
    }
}


void List::Push(char *s)
{
    Node *new_elem = new Node;
    new_elem->data = s;
    new_elem->next = head;
    head = new_elem;

    if (!tail) tail = head;
}


void List::Append(char *s)
{
    Node *new_elem = new Node;
    new_elem->data = s;
    new_elem->next = 0;

    if (!head) {
        head = new_elem;
        tail = new_elem;
    } else {
        tail->next = new_elem;
        tail = tail->next;
    }
}


char *List::GetNext()
{
    if (!head) return 0;

    if (!curr) {
        curr = head;
        return curr->data;
    }

    if (curr->next) {
        curr = curr->next;
        return curr->data;
    }

    return 0;
}


void List::PrintList(Node *head)
{
    if (head) {
        PrintList(head->next);
        printf("%s\n", head->data);
    }
}


void List::Print()
{
    PrintList(head);
}
