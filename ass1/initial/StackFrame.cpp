#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarArrSize(LOCAL_VARIABLE_ARRAY_SIZE){}

void StackFrame::run(string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string line;

        while (getline(file, line))
        {
            string cmd;
            float value;
            int len_line = line.length();
            ++line_idx;
            int i;
            for (i = 0; i < len_line; ++i)
            {
                if (line[i] == '\r')
                    break;
                if (line[i] == ' ')
                    break;
                cmd += line[i];
            }

            if (cmd == "iconst" || cmd == "fconst" || cmd == "iload" || cmd == "fload" || cmd == "istore" || cmd == "fstore" || cmd == "val")
            {
                value = stof(line.erase(0, i));
            }

            if (cmd == "iadd")
                iadd();
            else if (cmd == "fadd")
                fadd();
            else if (cmd == "isub")
                isub();
            else if (cmd == "fsub")
                fsub();
            else if (cmd == "imul")
                imul();
            else if (cmd == "fmul")
                fmul();
            else if (cmd == "idiv")
                idiv();
            else if (cmd == "fdiv")
                fdiv();
            else if (cmd == "irem")
                irem();
            else if (cmd == "ineg")
                ineg();
            else if (cmd == "fneg")
                fneg();
            else if (cmd == "iand")
                iand();
            else if (cmd == "ior")
                ior();
            else if (cmd == "ieq")
                ieq();
            else if (cmd == "feq")
                feq();
            else if (cmd == "ineq")
                ineq();
            else if (cmd == "fneq")
                fneq();
            else if (cmd == "ilt")
                ilt();
            else if (cmd == "flt")
                flt();
            else if (cmd == "igt")
                igt();
            else if (cmd == "fgt")
                fgt();
            else if (cmd == "ibnot")
                ibnot();
            else if (cmd == "iconst")
                iconst(value);
            else if (cmd == "fconst")
                fconst(value);
            else if (cmd == "iload")
                iload(value);
            else if (cmd == "fload")
                fload(value);
            else if (cmd == "istore")
                istore(value);
            else if (cmd == "fstore")
                fstore(value);
            else if (cmd == "i2f")
                i2f();
            else if (cmd == "f2i")
                f2i();
            else if (cmd == "top")
                top();
            else if (cmd == "val")
                val(value);
            else if (cmd == "print_stack")
                print_stack();
            else if (cmd == "print_array")
                print_array();
        }
    

    }
}

void StackFrame::top(){
    if (size == 0) throw StackEmpty(line_idx);
    cout<< head->data<<endl;
}

void StackFrame::push(float value)
{
    if (size >= opStackMaxSize)
    {
        throw StackFull(line_idx);
    }
    else if(size >0 and size <= opStackMaxSize)
    {
        Element *new_ele = new Element(value);
        new_ele->next = head;
        head = new_ele;
        ++size;
    }
    else if (size == 0)
    {
        head = new Element(value);
        ++size;
    }
    else
    {
    }
}
void StackFrame::pop()
{
    if (size == 0)
        return;
    Element *tmp;
    tmp = head;
    head = head->next;
    delete tmp;
    --size;

}
float StackFrame::top_value()
{
    if (size == 0)
    {
        throw StackEmpty(line_idx);
    }


    return (head->data);
}
void StackFrame::iadd()
{
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();

    if (type_1 == 0 and type_1 == 0)
    {
        push(0);
        push(value_0 + value_1);
        
        return;
    }
    else
        throw TypeMisMatch(line_idx);
    
}
void StackFrame::fadd()
{
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    pop();
    float value_1 = top_value();
    pop();
    pop();
    push(1);
    push(value_0 + value_1);
    return;
}
void StackFrame::isub()
{
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();

    if (type_1 == 0 and type_1 == 0)
    {
        push(0);
        push(value_0 - value_1);
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}

void StackFrame::fsub()
{
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    pop();
    float value_1 = top_value();
    pop();
    pop();
    push(1);
    push(value_0 - value_1);
    return;
}
void StackFrame::imul()
{
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();
    if (type_1 == 0 and type_1 == 0)
    {
        push(0);
        push(value_0 * value_1);
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::fmul()
{
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    pop();
    float value_1 = top_value();
    pop();
    pop();
    push(1);
    push(value_0 * value_1);
    return;
}

void StackFrame::idiv()
{
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();

    if (type_1 == 0 and type_1 == 0)
    {
        if (value_0 == 0)
            throw DivideByZero(line_idx);
        push(0);
        push(float(int(value_1 / value_0)));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::fdiv()
{
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    pop();
    float value_1 = top_value();
    pop();
    pop();
    if (value_0 == 0)
        throw DivideByZero(line_idx);
    push(1);
    push(value_1 / value_0);
    return;
}
void StackFrame::irem()
{
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();

    if (type_1 == 0 and type_1 == 0)
    {
        if (value_0 == 0)
            throw DivideByZero(line_idx);
        push(0);
        push(float(int(value_1) % int(value_0)));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::ineg()
{
    if (size < 2)
        throw StackEmpty(line_idx);
    float value = top_value();
    float type = top_value();
    if (type != 0)
        throw TypeMisMatch(line_idx);
    push(0);
    push(0 - value);
    return;
}

void StackFrame::fneg(){
    if (size < 2)
        throw StackEmpty(line_idx);
    float value = top_value();
    float type = top_value();
    push(1);
    push(0 - value);
    return;
}
void StackFrame::iand(){
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();

    if (type_1 == 0 and type_1 == 0)
    {
        push(0);
        push(float(int(value_1)&& int(value_0)));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::ior(){
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();

    if (type_1 == 0 and type_1 == 0)
    {
        push(0);
        push(float(int(value_1)|| int(value_0)));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::ieq(){
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();

    if (type_1 == 0 and type_1 == 0)
    {
        push(0);
        push(float(value_1 == value_0));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::feq(){
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    pop();
    float value_1 = top_value();
    pop();
    pop();

    if (1)
    {
        push(0);
        push(value_1 == value_0);
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::ineq(){
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();

    if (type_1 == 0 and type_1 == 0)
    {
        push(0);
        push(float(value_1 != value_0));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::fneq(){
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    pop();
    float value_1 = top_value();
    pop();
    pop();

    if (1)
    {
        push(0);
        push(float(int(value_1 != value_0)));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::ilt(){
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();

    if (type_1 == 0 and type_1 == 0)
    {
        push(0);
        push(float(value_1 < value_0));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}

void StackFrame::flt(){
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    pop();
    float value_1 = top_value();
    pop();
    pop();

    if (1)
    {
        push(0);
        push(float(int(value_1 < value_0)));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::igt(){
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();
    float value_1 = top_value();
    pop();
    float type_1 = top_value();
    pop();

    if (type_1 == 0 and type_1 == 0)
    {
        push(0);
        push(float(value_1 > value_0));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::fgt(){
    if (size < 4)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    pop();
    float value_1 = top_value();
    pop();
    pop();

    if (1)
    {
        push(0);
        push(float(int(value_1 > value_0)));
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::ibnot(){
    if (size < 2)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();

    if (type_0 == 0 )
    {
        push(0);
        if ( value_0 == 0 ) push(1);
        else push(0);
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::iconst(float value){
    push(0);
    push(value);
}

void StackFrame::fconst(float value){
    push(1);
    push(value);
}
void StackFrame::iload(float index){
    int tmp_idx = int(index);
    if(!(tmp_idx >= 0 and tmp_idx < localVarArrSize)) throw ArrayOutOfRange(line_idx);
    else{
        if(tmp_idx % 2 == 0){
            if(array[tmp_idx] != 1 and array[tmp_idx] != 0) throw UndefinedVariable(line_idx);
            float type = array[tmp_idx];
            float value = array[tmp_idx+1];
            if (type == 0 ){
                push(type);
                push(value);
                return;
            }
            throw TypeMisMatch(line_idx);
        }
    }

}
void StackFrame::fload(float index){
    int tmp_idx = int(index);
    if(!(tmp_idx >= 0 and tmp_idx < localVarArrSize)) throw ArrayOutOfRange(line_idx);
    else{
        if(tmp_idx % 2 == 0){
            if(array[tmp_idx] != 1 and array[tmp_idx] != 0) throw UndefinedVariable(line_idx);
            float type = array[tmp_idx];
            float value = array[tmp_idx+1];
            if (type == 1 ){
                push(type);
                push(value);
                return;
            }
            throw TypeMisMatch(line_idx);
        }
    }

}

void StackFrame::istore(float index){
    int tmp_idx = int(index);
    if(!(tmp_idx >= 0 and tmp_idx < localVarArrSize)) throw ArrayOutOfRange(line_idx);
    else{
        if(tmp_idx % 2 == 0){
            if(array[tmp_idx] != 1 and array [tmp_idx] != 0) throw UndefinedVariable(line_idx);
            float type = top_value();
            pop();
            float value = top_value();
            pop();
            if (type == 0 ){
                array[tmp_idx] = type;
                array[tmp_idx+1] = value;
                return;
            }
            throw TypeMisMatch(line_idx);
        }
    }

}


void StackFrame::fstore(float index){
    int tmp_idx = int(index);
    if(!(tmp_idx >= 0 and tmp_idx < localVarArrSize)) throw ArrayOutOfRange(line_idx);
    else{
        if(tmp_idx % 2 == 0){
            if(array[tmp_idx] != 1 and array [tmp_idx] != 0) throw UndefinedVariable(line_idx);
            float type = top_value();
            pop();
            float value = top_value();
            pop();
            if (type == 1 ){
                array[tmp_idx] = type;
                array[tmp_idx+1] = value;
                return;
            }
            throw TypeMisMatch(line_idx);
        }
    }

}
void StackFrame::i2f(){
    if (size < 2)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();

    if (type_0 == 0 )
    {
        push(1);
        push(value_0);
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}

void StackFrame::f2i(){
    if (size < 2)
        throw StackEmpty(line_idx);
    float value_0 = top_value();
    pop();
    float type_0 = top_value();
    pop();

    if (type_0 == 1)
    {
        push(0);
        push(value_0);
        return;
    }
    else
        throw TypeMisMatch(line_idx);
}
void StackFrame::val(float index){
     int tmp_idx = int(index);
    if(!(tmp_idx >= 0 and tmp_idx < localVarArrSize)) throw ArrayOutOfRange(line_idx);
    else{
        if(tmp_idx % 2 == 0){
            if(array[tmp_idx] != 1 and array [tmp_idx] != 0) throw UndefinedVariable(line_idx);
            cout<<array[tmp_idx]<<"\n";
            return;
        }
    }
}

void StackFrame::print_stack(){
    for(Element* ele = head; ele!=NULL; ele= ele->next){
        cout<<ele->data<<" ";
    }
}
void StackFrame::print_array(){
    for(int i =0; i< localVarArrSize;i++){
        cout<<array[i]<<" ";
    }
}