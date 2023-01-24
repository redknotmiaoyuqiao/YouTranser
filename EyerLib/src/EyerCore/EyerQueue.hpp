#ifndef	EYER_QUEUE_H
#define	EYER_QUEUE_H
#include "EyerLinkedEle.hpp"

namespace Eyer {
    template <typename T>
    class EyerQueue
    {
    private:
        EyerLinkedEle<T> * head;
        EyerLinkedEle<T> * rear;
        int size = 0;
    public:
        EyerQueue(/* args */);
        ~EyerQueue();
        bool isEmpty();
        int clear();
        int enQueue(const T& data);
        int deQueue(T& data);
        int getSize();
        int getHead(T& data);
    };

    template <typename T>
    int EyerQueue<T>::clear()
    {
        EyerLinkedEle<T>* temp;
        while (head != nullptr) {
            temp = head;
            head = temp->next;
            delete temp;
            temp = nullptr;
            size--;
        }
        return 0;
    }

    template <typename T>
    int EyerQueue<T>::enQueue(const T& data)
    {
        EyerLinkedEle<T> * newEle = new EyerLinkedEle<T>(data);
        if (head == nullptr) {
            head = rear = newEle;
            size++;
        }else {
            rear->next = newEle;
            rear = newEle;
            size++;
        }
        return 0;
    }

    template <typename T>
    int EyerQueue<T>::deQueue(T& data)
    {
        if (head == nullptr) {
            return -1;
        }

        EyerLinkedEle<T> * temp = head;
        data = temp->data;
        head = temp->next;
        delete temp;
        temp = nullptr;
        size--;
        return 0;
    }

    template <typename T>
    bool EyerQueue<T>::isEmpty() {
        return head == nullptr;
    }

    template <typename T>
    int EyerQueue<T>::getSize() {
        return size;
    }


    template <typename T>
    EyerQueue<T>::EyerQueue()
    {
        head = nullptr;
        rear = nullptr;
    }

    template <typename T>
    EyerQueue<T>::~EyerQueue()
    {
        clear();
    }

    template <typename T>
    int EyerQueue<T>::getHead(T& data)
    {
        return 0;
    }

}

#endif
