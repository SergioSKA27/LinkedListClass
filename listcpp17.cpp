#include <iostream>
#include <string>
#include <cstdbool>
#include <cstdlib>
#include <vector>
#include <exception>

/*
    @autor: Sergio Lopez Martinez

    ---Implementación de Listas ligadas  Simples , Dobles y Circulares---
    
    Todos los metodos respetan los tiempos de ejecución definidos para listas:

        -Inserción  de datos en tiempo constante O(1), unicamente para  las funciónes
        push y push_back.

            ·para los metodos de inserción de datos como insert tenemos  que 
            este se ejecuta en un tiempo del orden  O(k), donde k representa
            la posicion donde queremos insertar el dato.
        
        -Los metodos de acceso como at o el operador corchete se ejcutan en un tiempo
        del orden O(k), siendo k la posición a la que queremos acceder.

            .En caso de que las posiciones a las queramos acceder sean la primera
            la  ultima  el acceso a  estas es del oreden O(1), dado  que en  todo 
            momento sabemos quien es el primero y el ultimo de la lista. 

        -Los metodos para invertir una lista son del orden de O(n).

        -El metodo clear de igual forma es del orden O(n).

            .El metodo 'del' es  del orden O(k) donde 
            k  representa  la posicion  que  queremos
            eliminar. 

        -Los metodos pop y pop back se ejecuntan en timepo constante O(1), a excepcion 
        de las listas simples en donde el metodo pop_back es del orden (n) dado que es 
        necesario localizar el penultimo elemento.


    Usa el estandar de C++17 al compilarlo :).
    Ademas debes hacer uso la bandera -fconcepts-ts al compilar.
*/
template <typename t>
class Node
{
private:
    t Data;

public:
    Node<t> *next;

    Node(t);
    Node();

    t getdata() const { return this->Data; } //Retorna el valor contenido en el nodo

    t operator()() const
    { //Operador de acceso a los datos del nodo
        return this->Data;
    }

    ~Node();
};

template <typename t>
Node<t>::Node(t Data)
{
    this->Data = Data;
    this->next = NULL;
}

template <typename t>
Node<t>::Node()
{
    this->next = NULL;
}

template <typename t>
Node<t>::~Node()
{
}

template <typename type>
class linkedlist
{
private:
    Node<type> *Head;  //Puntero al primer elemento de la lista
    Node<type> *Tail;  //Puntero al ultimo elemento de la lista
    Node<type> *Nodes; //Para crear los nodos

    size_t size; //Tamaño de la lista

    Node<type> *_reverse(Node<type> *Head); //Funcion para invertir una lista de forma recursiva

public:
    linkedlist();                              //Constructor default
    linkedlist(type init, size_t size);        //Inicializa una lista con un tamaño y un valor
    linkedlist(const linkedlist<type> &list2); //Constructor copia
    template <typename... args>
    linkedlist(args &&... params); //Constructor Expandible

    /*
        Metodos para insertar datos:
            - los metodos push y push_back se ejecutan ambos en tiempo constante 
            puesto que siempre se sabe cual es el primer y el ultimo elemento de 
            la lista.
            
            -Las funcionalidades de c++17 nos permiten crear metodos expandibles
            esto  quiere decir  que podemos  introducir un  numero arbitrario de 
            de parametros que seran los elemetos a insertar en la lista(tanto la
            funcion push y push back poseen dicha caracteristica).

            -los metodos de insercion tinen un tiempo de ejecucion del orden  de 
            O(k), donde  k representa la posicion en la  que quremos insertar el 
            nuevo dato.

    */
    void push(auto Data); //Inserta un elemento al principio de la lista
    void push(type Data); //Inserta un elemento al principio de la lista
    template <typename... args>
    void push(args &&... elements); //hacer push a multiples elementos

    void push_back(auto Data); //inserta elementos al principio de la lista
    template <typename... args>
    void push_back(args &&... elements); //hacer push a multiples elementos

    void insert(size_t index, type Data);   //Insertamos un nuevo dato en el indice señalado
    void insertAF(size_t index, type Data); //Insertamos un dato despues del indice señalado
    void insertBF(size_t index, type Data); //Insertamos un dato antes del indice señalado

    Node<type> *head() const;           //Retorna un puntero al principio de la lista
    Node<type> *tail() const;           //Retorna un puntero al final de la lista
    Node<type> *at(size_t index) const; //Retorna un puntero al elemento en el indice señalado

    /*
        -La funcion para invertir una lista se ejecuta en tiempo lineal O(n) es decir  la 
        funcion recursiva genera tantas instancias como nodos tenga la lista.
    */
    void reverse();                                        //Invierte la lista actual(modifica el objeto)
    std::pair<linkedlist<type>, linkedlist<type>> split(); //Divide una lista en dos y retorna un pair con ambas partes

    /*
        -La funcion clear es del orden O(n) dado el ciclo para borrar los nodos se ejecuta 
        tantas veces como nodos tenga la lista.

        -La funcion pop es del orden de O(1) dado que basta unicamente con eliminar el nodo 
        al  principio de la lista( head) y moverlo la referencia del head  al sig. del nodo 
        previamente eliminado.

        -La funcion pop_back es del orden de O(n-1) puesto que para realizar esta operacion 
        en una lista simple es necesario recorrer la lista para encontrar el nodo previo al 
        ultimo de la lista.
    */
    void clear();           //Elimina todos los elementos de la lista
    void pop();             //Elimina el elemento al principio de la lista
    void pop_back();        //Elimina el elemento al final de la lista
    void del(size_t index); //Elimina el elemento en el indice señalado

    friend std::ostream &operator<<(std::ostream &o, linkedlist<type> &list)
    {

        if (list.head() == NULL)
        {
            o << "[]";
            return o;
        }

        Node<type> *i = list.head();
        o << "[";
        while (i != NULL)
        {
            if (i->next != NULL)
                o << i->getdata() << ", ";
            else
                o << i->getdata();
            i = i->next;
        }
        o << "]";
        return o;
    }

    size_t size_list() const { return this->size; } //Retorna el tamaño de la lista
    bool empty() const { return (this->Head == NULL) ? true : false; }

    /*OPERADORES*/

    linkedlist<type> &operator=(const linkedlist<type> &list2);  //Operador de asignacion
    linkedlist<type> operator+(const linkedlist<type> &list2);   //Operador de union retorna la lista unida apartir de dos listas sin modificarlas
    linkedlist<type> &operator+=(const linkedlist<type> &list2); //Operador de union une una lista a la lista actual
    linkedlist<type> operator!();                                //Operador inversion retorna la lista invertida(no modifica el objeto )

    type operator[](const int index);                        //Operador de acceso con corchetes
    linkedlist<type> operator()(const size_t star, int end); //Operador rebanada XD reatorna un sublista en el rago del los indices señalados(inclusivo)

    //IteratorS<type> begin(); //Retorna un iterador al princio de la lista
    //IteratorS<type> end();   //Retorna un iterador al final de la lista

    ~linkedlist();
};

template <typename type>
linkedlist<type>::linkedlist()
{
    this->Head = NULL;
    this->Tail = NULL;
    this->Nodes = NULL;
    this->size = 0;
}

template <typename type>
linkedlist<type>::linkedlist(type init, size_t size)
{
    size_t k = 0;
}

template <typename type>
template <typename... args>
linkedlist<type>::linkedlist(args &&... params)
{
}

template <typename type>
void linkedlist<type>::push(auto Data)
{
    type data = Data;
    auto h = this->Head; //Guardamos una ref. al head previo

    this->Nodes = new Node<type>(data); //Creamos el nuevo nodo con los datos

    this->Head = this->Nodes; //El nodo insertado es el nuevo head
    this->Nodes->next = h;    //El sig. del elemento insertado es headn previo
    this->size += 1;          //Aumentamos el tamaño de la lista

    if (this->size == 1)
    { //Si el tamaño es uno el elemento en la lista tambie es el tail+
        this->Tail = this->Head;
    }
}

template <typename type>
void linkedlist<type>::push(type Data)
{
    auto h = this->Head; //Guardamos una ref. al head previo

    this->Nodes = new Node<type>(Data); //Creamos el nuevo nodo con los datos

    this->Head = this->Nodes; //El nodo insertado es el nuevo head
    this->Nodes->next = h;    //El sig. del elemento insertado es headn previo
    this->size += 1;          //Aumentamos el tamaño de la lista

    if (this->size == 1)
    { //Si el tamaño es uno el elemento en la lista tambie es el tail+
        this->Tail = this->Head;
    }
}

template <typename type>
void linkedlist<type>::push_back(auto Data)
{
    type data = Data;
    auto t = this->tail();

    if (this->Head == NULL) //Si la lista esta vacia hacemos push
        this->push(Data);
    else
    {
        this->Nodes = new Node<type>(Data); //Creamos el nodo
        t->next = this->Nodes;              //el sig. del tail previo es el nuevo nodo
        this->Tail = this->Nodes;           //Ahora el tail es el nuevo nodo
        this->size += 1;                    //Aumentamos el tamaño de la lista
    }
}

template <typename type>
void linkedlist<type>::insert(size_t index, type Data)
{
    size_t k = 0;
    Node<type> *tmp = this->Head, *aux = NULL;

    if (index == 0) //Insertar elementos al principio de la lista
        this->push(Data);
    else if (index == this->size - 1)
    { //Para insertar elemetos al final usamos el tamaño de la lista-1
        this->push_back(Data);
    }
    else
    {
        while (k < this->size && tmp != NULL)
        {
            if (k == index - 1)
                break;
            tmp = tmp->next;
            k++;
        }

        aux = tmp->next;
        this->Nodes = new Node<type>(Data);

        tmp->next = this->Nodes;
        this->Nodes->next = aux;
        this->size += 1;
    }
}

template <typename type>
void linkedlist<type>::insertBF(size_t index, type Data)
{
    size_t k = 0;
    Node<type> *tmp = this->Head, *aux = NULL;

    if (index == 0) //Insertar elementos al principio de la lista
        this->push(Data);
    else
    {
        while (k < this->size && tmp != NULL)
        {
            if (k == index - 2)
                break;
            tmp = tmp->next;
            k++;
        }

        aux = tmp->next;
        this->Nodes = new Node<type>(Data);

        tmp->next = this->Nodes;
        this->Nodes->next = aux;
        this->size += 1;
    }
}

template <typename type>
void linkedlist<type>::insertAF(size_t index, type Data)
{
    size_t k = 0;
    Node<type> *tmp = this->Head, *aux = NULL;

    if (index == this->size - 1) //Insertar elementos al final de la lista
        this->push_back(Data);
    else
    {
        while (k < this->size && tmp != NULL)
        {
            if (k == index)
                break;
            tmp = tmp->next;
            k++;
        }

        aux = tmp->next;
        this->Nodes = new Node<type>(Data);

        tmp->next = this->Nodes;
        this->Nodes->next = aux;
        this->size += 1;
    }
}

template <typename type>
Node<type> *linkedlist<type>::head() const { return this->Head; }

template <typename type>
Node<type> *linkedlist<type>::tail() const { return this->Tail; }

template <typename type>
Node<type> *linkedlist<type>::at(size_t index) const
{
    if (this->Head == NULL)
        throw std::invalid_argument("List is empty!");

    if (index >= this->size)
        throw std::out_of_range("invalid index!");

    size_t k = 0;
    Node<type> *it = this->Head;

    while (it != NULL)
    {
        if (k == index)
            break;
        it = it->next;
        k++;
    }
    std::cout << it->getdata() << std::endl;
    return it;
}

template <typename type>
Node<type> *linkedlist<type>::_reverse(Node<type> *head)
{ //Invierte una lista simple recursivamente

    if (head->next == NULL)
    { //Cuando el sig. sea nulo sabremos que es el final de la lista
        Node<type> *newhead = head;
        return newhead;
    }
    else
    {
        Node<type> *nwhead = this->_reverse(head->next);
        head->next = NULL;
        nwhead->next = head;
        nwhead = nwhead->next;
        return nwhead;
    }
}

template <typename type>
void linkedlist<type>::reverse()
{ //Invirte la lista(modifica el objeto)
    if (this->Head == NULL)
        throw std::invalid_argument("the list is empty!");
    else
    {
        Node<type> *nwtail = this->_reverse(this->Head);
        this->Head = this->Tail;
        this->Tail = nwtail;
    }
}

template <typename type>
std::pair<linkedlist<type>, linkedlist<type>> linkedlist<type>::split()
{
    auto it = this->Head;
    linkedlist<type> A, B;
    std::pair<linkedlist<type>, linkedlist<type>> P;
    size_t k = 0, m = this->size / 2;

    if (this->Head == NULL || this->Head->next == NULL)
    {
        A = (*this);
        P.first = A;
        P.second = B;
        return P;
    }

    while (k < m)
    {
        A.push_back(it->getdata());
        it = it->next;
        k++;
    }

    while (it != NULL)
    {
        B.push_back(it->getdata());
        it = it->next;
        k++;
    }

    P.first = A;
    P.second = B;

    return P;
}

template <typename type>
void linkedlist<type>::clear()
{
    if (this->Head == NULL)
    {
        std::cout << "the list is empty!";
        return;
    }
    else
    {
        Node<type> *i = this->head();

        while (i != NULL)
        {
            Node<type> *tmp = i;
            i = i->next;
            delete tmp;
        }
    }
    this->Head = NULL;
    this->Tail = NULL;
    this->Nodes = NULL;
    this->size = 0;
}

template <typename type>
void linkedlist<type>::pop()
{
    if (this->Head == NULL)
        throw std::invalid_argument("List is empty!");

    Node<type> *nodeD = this->Head, *nwhead = this->Head->next;

    this->Head = nwhead;
    delete nodeD;
    this->size -= 1;

    if (this->size == 1) // Si solo queda un elemento en la lista
        this->Tail = this->Head;
}

template <typename type>
void linkedlist<type>::pop_back()
{
    if (this->Head == NULL)
        throw std::invalid_argument("List is empty!");

    Node<type> *prev = NULL, *it = this->Head, *nodeD = this->Tail;
    size_t k = 0;

    while (it != NULL)
    { //Buscamos el nodo previo al ultimo de la lista
        if (k == this->size - 2)
            break;
        it = it->next;
        k++;
    }

    prev = it;
    prev->next = NULL;

    delete nodeD; //Eliminamos el ultimo nodo

    this->Tail = prev;
    this->size -= 1;

    if (this->size == 1) // Si solo queda un elemento en la lista
        this->Head = this->Tail;
}

template <typename type>
void linkedlist<type>::del(size_t index)
{
    if (this->Head == NULL)
        throw std::invalid_argument("List is empty!");

    if (index >= this->size)
        throw std::out_of_range("invalid index!");

    if (index == 0)
    {
        this->pop();
        return;
    }
    if (index == this->size - 1)
    {
        this->pop_back();
        return;
    }

    Node<type> *nodeD = NULL, *prev = NULL, *it = this->Head;
    size_t k = 0;

    while (it != NULL)
    {
        if (k == index - 1)
            prev = it;
        if (k == index)
            break;
        it = it->next;
        k++;
    }
    nodeD = it;

    prev->next = it->next;

    delete nodeD;

    this->size -= 1;
}

template <typename type>
linkedlist<type> &linkedlist<type>::operator=(const linkedlist<type> &list2)
{
    Node<type> *it = list2.head();

    while (it != NULL)
    {
        this->push_back(it->getdata());
        it = it->next;
    }

    return (*this);
}

template <typename type>
linkedlist<type> &linkedlist<type>::operator+=(const linkedlist<type> &list2)
{
    auto it = list2.Head;

    while (it != NULL)
    {
        this->push_back(it->getdata());
        it = it->next;
    }

    return (*this);
}

template <typename type>
linkedlist<type> linkedlist<type>::operator+(const linkedlist<type> &list2)
{
    Node<type> *s = list2.head();
    linkedlist<type> result;

    result = (*this);

    while (s != NULL)
    {
        result.push_back(s->getdata());
        s = s->next;
    }

    return result;
}

template <typename type>
linkedlist<type> linkedlist<type>::operator!()
{
    linkedlist<type> revers;
    Node<type> *it = this->Head;

    while (it != NULL)
    {
        revers.push(it->getdata());
        it = it->next;
    }

    return revers;
}

template <typename type>
linkedlist<type> linkedlist<type>::operator()(size_t start, int end)
{
    size_t k = 0;

    Node<type> *it = this->Head;

    linkedlist<type> sublist;

    if (((start >= this->size || end >= this->size) || (start < 0 || end < 0)) && end != -1)
        throw std::out_of_range("Invalid index!");

    if (end == -1) //al usar menos uno nos referimos al final de la lista
        end = this->size;

    while (it != NULL)
    {
        if (k > end)
            break;
        if (k >= start)
            sublist.push_back(it->getdata());

        it = it->next;
        k++;
    }

    return sublist;
}

template <typename type>
type linkedlist<type>::operator[](const int index)
{
    if ((index >= this->size || index < 0) && index != -1)
        throw std::out_of_range("Invalid index!");

    if (index == -1)
        index = this->size - 1;

    return (this->at(index)->getdata());
}

template <typename type>
linkedlist<type>::~linkedlist()
{
    if (this->Head != NULL) //Si la lista no esta vacia borramos su contenido
        this->clear();
}

/*
    ---ITERADORES PARA LISTAS SIMPLEMENTE LIGADAS---

    Con el uso  de dichos  iteradores es  posible recorrer  una lista 
    simple sin necesidad  de  hacer uso de  los  operadores de acceso
    de la clase dado  que  estos  al tener que recorrer la lista para
    acceder a la posicion  hacen  ineficiente el hecho de recorrer la 
    estructura haciendo uso de de este metodo.

    Ademas de  ello esta  implementacion permite el uso de ciclos for 
    y while para recorrer la lista.

    EJEMPLO:

    for(IteratorS iter = list.begin(); iter != list.end(); iter++)
    {
        cout << iter()<< endl;
    }

    en el ejemplo recorremos una lista haciendo uso de los iteradores
    begin y end, que señalan respectivamente el principio y el  final 
    de la lista.

    Ademas  de  esto es  posible  comenzar el ciclo (o terminarlo) en 
    cualquier posicion, haciendo uso del iterador begin y el operador
    '+' sumando el numero de posiciones que nos queremos  mover desde
    el principio de la lista.

*/
template <typename istype>
class IteratorS
{
private:
    Node<istype> *iterator;

public:
    IteratorS(Node<istype> *it);
    IteratorS();

    istype operator()() const { return this->iterator->getdata(); } //retorna el valor del iterador

    IteratorS<istype> &operator=(const IteratorS<istype> &iter2); //Operador de asignación
    IteratorS<istype> &operator++();                              //iterar de uno en uno (++iterator)
    IteratorS<istype> &operator++(istype);                        //iterar de uno en uno (iterator++)
    IteratorS<istype> &operator+(const size_t value);             //aumentar el valor de la iteración en mas de uno

    bool operator==(const IteratorS<istype> &iter2) const;
    bool operator!=(const IteratorS<istype> &iter2) const;

    ~IteratorS();
};

template <typename istype>
IteratorS<istype>::IteratorS(Node<istype> *iter)
{
    this->iterator = iter;
}

template <typename istype>
IteratorS<istype>::IteratorS()
{
    this->iterator = NULL;
}

template <typename istype>
IteratorS<istype> &IteratorS<istype>::operator=(const IteratorS<istype> &iter2)
{
    this->iterator = iter2.iterator;
    return *this;
}

template <typename istype>
IteratorS<istype> &IteratorS<istype>::operator++()
{
    this->iterator = this->iterator->next;
    return *this;
}

template <typename istype>
IteratorS<istype> &IteratorS<istype>::operator++(istype)
{
    this->iterator = this->iterator->next;
    return *this;
}

template <typename istype>
IteratorS<istype>::~IteratorS()
{
}

int main(int argc, char const *argv[])
{
    linkedlist<int> A, B, C;
    linkedlist<std::string> slist;

    std::string s[7] = {"hi", "world", "flower", "cluod", "sun", "moon", ":)"};

    slist.push(s[0]);
    slist.push(s[1]);
    slist.push(s[2]);
    slist.push(s[3]);
    slist.push(s[4]);
    slist.push(s[5]);
    slist.push(s[6]);
    slist.push("a");
    slist.push("Hola mundo");
    slist.push("12");

    std::cout << slist << std::endl;

    A.push(1);
    A.push(2);
    A.push_back(15);
    A.push(20);
    A.push_back(-1);
    std::cout << A << std::endl;

    A.insertAF(0, -100);
    std::cout << A << std::endl;
    A.reverse();
    std::cout << A << std::endl;

    A.pop_back();
    std::cout << A << std::endl;

    A.push_back(100000);
    A.push(12);
    std::cout << A << std::endl;

    A.at(3);

    A.split();

    A.del(1);
    std::cout << A << std::endl;

    C.push(1);
    C.push(13);
    C.push(15);
    C.push(16);
    C.push(189);
    std::cout << C << std::endl;
    std::cout << A << std::endl;

    (B.empty()) ? std::cout << "v\n" : std::cout << "f\n";
    B = A(3, -1);
    std::cout << B << std::endl;

    return 0;
}