#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>

/*
StackFrame declaration
*/

class StackFrame
{
    int opStackMaxSize;  // max size of operand stack
    int localVarArrSize; // size of local variable array
public:
    class Element;

protected:
    float *array = new float[localVarArrSize];
    int line_idx = 0;
    int size = 0;
    Element *head = NULL;

public:
    /*
    Constructor of StackFrame
    */
    StackFrame();
    void push(float value);
    void top();
    void pop();
    float top_value();
    void iadd();
    void fadd();
    void isub();
    void fsub();
    void imul();
    void fmul();
    void idiv();
    void fdiv();
    void irem();
    void ineg();
    void fneg();
    void iand();
    void ior();
    void ieq();
    void feq();
    void ineq();
    void fneq();
    void ilt();
    void flt();
    void igt();
    void fgt();
    void ibnot();
    void iconst(float value);
    void fconst(float value);
    void iload(float index);
    void fload(float index);
    void istore(float index);
    void fstore(float index);
    void i2f();
    void f2i();
    void val(float index);
    void print_stack();
    void print_array();
    /*
Run the method written in the testcase
@param filename name of the file
*/
    void run(std::string filename);

public:
    class Element
    {
        friend class StackFrame;

    private:
        float data;
        Element *next;

    public:
        Element(float value)
        {
            this->data = value;
            this->next = NULL;
        }
    };
};

#endif // !__STACK_FRAME_H__