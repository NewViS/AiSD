/*
 *  list.h
 *
 *  Created on: 10 окт. 2022 г.
 *      Author: Pesterev
 */

#pragma once
using namespace std;

class El {
    char e;
    El* next;
    static const int maxmup = 100000000;
    static El mem[maxmup]; //Свободная память для элементов спис-ков
    static int mup, mup0;
public:
    static bool isOutput;
    El() : e('!'), next(nullptr) { }
    El(char e, El* n = nullptr) : e(e), next(n) { if(isOutput) cout << "+" << e; }
    ~El() {
        if (this) { //Проверка обязательна
            if (next) { delete next; }
            if(isOutput) cout << "-" << e;
            e = '*';
        }
        else if(isOutput) cout << "<Пусто!>";
    }
    static void* operator new(size_t) {
        return (mup < maxmup ? &mem[mup++] : nullptr);
    }
    static void operator delete(void*, size_t) { }
    static void mark() { mup0 = mup; }   //Фиксировать состояние памяти
    static void release() { mup = mup0; }  //Сбросить до фиксированного
    static void clear() { mup = 0; }   //Очистить память полностью
    friend class Set;
    friend std::ostream& operator << (std::ostream& o, El& S);
    friend static void memOut();
};
std::ostream& operator << (std::ostream& o, El& S)
{
    for (El* p = &S; p; p = p->next) o << p->e;
    return o;
}

bool El::isOutput = false;
El El::mem[El::maxmup];  //"Свободная память"
int El::mup = 0, El::mup0 = 0;

void memOut()  //Вывод использованного содержимого "свободной памяти"
{
    cout << "\n\nПамять элементов списков (всего - " << dec << El::mup << ")\n";
    for (int i = 0; i < El::mup; ++i) cout << El::mem[i].e;
}


class Set
{
private:
    static int N, cnt;      //Порядковый номер множества
    int n;   //Мощность множества
    char S;   //Тег
    El* A;   //Список элементов
    static char univers[];

public:
    static bool isOutput;

    Set();   //Пустое множество
    Set(char *B);
    Set(const Set&);
    Set& operator = (const Set&);
    ~Set() {
        if(isOutput) cout << "Удалено " << S << "(" << std::dec << n << ") = [" << *A << "]";
        A->El::~El();
        if(isOutput) cout << std::endl;
    }

    void show();
    int power() { return n; }
    void swap(Set& other) { std::swap(S, other.S); std::swap(n, other.n); std::swap(A, other.A); }
    Set& operator |= (const Set&);
    Set& operator &= (const Set&);
    Set operator | (const Set&) const;
    Set operator & (const Set&) const;
};

int Set::N = 16;
int Set::cnt = 0;
char Set::univers[] = "0123456789abcdef";
bool Set::isOutput = false;

Set::Set() : n(0), S('A' + cnt++), A(nullptr)
{
    if(isOutput) cout << "-> Создано " << S << "(" << n << ") = [" << *A << "] \n";
}

/*Set::Set(char) : S('A' + num++), n(0)
{
    A = nullptr;
    for (int i = 0; i < N; i++)
        if (rand() % 2)
            A = new El(i + 'a', A), ++n;
    std::cout << "-> Создано " << S << "(" << n << ") = [" << *A << "] \n";
}*/

Set::Set(char *B) : n(0), S('A' + cnt++){
	A = nullptr;
	for (int i = 0; B[i]; ++i)
		{
		A = new El(B[i], A);
		++n;
		}

	if(isOutput) cout << "-> Создано " << S << "(" << n << ") = [" << *A << "] \n";
}

Set::Set(const Set& B) : n(B.n), S('A' + cnt++), A(nullptr)
{
    for (El* p = B.A; p; p = p->next) A = new El(p->e, A);
    if(isOutput) cout << "-> Создано " << S << "(" << n << ") = [" << *A << "] из " << B.S << std::endl;
}

/*Set::Set(Set&& B) : n(B.n), S('A' + num++), A(B.A)
{
    B.A = nullptr;
    std::cout << "-> ПРИНЯТО " << S << "(" << n << ") = [" << *A << "] из " << B.S << std::endl;
}*/

Set& Set::operator &= (const Set& B)
{
    Set C;
    for (El* i = A; i; i = i->next)
    {
        for (El* j = B.A; j; j = j->next)
            if (i->e == j->e)
                C.A = new El(i->e, C.A), ++C.n;
    }
    swap(C);
    if(isOutput) cout << "; Получено " << S << "(" << n << ") = [" << *A << "] = " << C.S << "&" << B.S << endl;
    return *this;
}
Set Set::operator & (const Set& B) const
{
    Set C(*this);
    if(isOutput) cout << "Вычисление " << C.S << " & " << B.S << endl;
    return C &= B;
}

Set& Set::operator |= (const Set& B)
{
    Set C(*this);
    for (El* i = B.A; i; i = i->next)
    {
        bool f = true;
        for (El* j = A; f && j; j = j->next)
            f = f && (i->e != j->e);
        if (f)
            C.A = new El(i->e, C.A), ++C.n;
    }
    swap(C);
    if(isOutput) cout << "; Получено " << S << "(" << n << ") = [" << *A << "] = " << C.S << "|" << B.S << endl;
    return *this;
}
Set Set::operator | (const Set& B) const
{
    Set C(*this);
    if(isOutput) cout << "Вычисление " << C.S << " | " << B.S << endl;
    return C |= B;
}

Set& Set::operator = (const Set& B)
{
    if (this != &B)
    {
        if(isOutput) cout << "\nУдалено " << S << "(" << n << ") = [" << *A << "]";
        delete A;
        A = nullptr;
        n = 0;
        for (El* p = B.A; p; p = p->next)
            A = new El(p->e, A), ++n;

    }
    if(isOutput) cout << "; Создано " << S << "(" << n << ") = [" << *A << "] из " << B.S << std::endl;
    return *this;
}

void Set::show()
{
    cout << S <<  " = [";
    for (El* p = A; p; p = p->next) cout << p->e << " ";
    cout << "]\n";
}
