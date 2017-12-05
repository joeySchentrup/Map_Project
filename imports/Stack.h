#ifndef STACK_H
#define STACK_H

template < class T > 
class Stack {
    private:
        T array [10]; 
        int pointer; 

    public:
    Stack() {
        pointer = 0; 
    }; 
    
    void push(T object); 
    T pop(); 
    bool isEmpty(); 
    void clear(); 
}; 

template < class T > 
void Stack< T > ::push(T object) {
    if(!(pointer + 1 == sizeof(array))) array[++pointer] = object; 
}; 

template < class T > 
T Stack < T > ::pop() {
    return array[pointer--]; 
}; 

template < class T > 
bool Stack < T > ::isEmpty() {
    return pointer == 0; 
}; 

template < class T > 
void Stack < T > ::clear() {
    pointer = 0; 
}; 

#endif