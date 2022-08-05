#include<iostream>
#include<list>
#include<unordered_map>

using namespace std;

class Node
{
public:
    string key;
    int value;
    Node(string key,int value)
    {
        this->key=key;
        this->value=value;
    }
};

class LRUchache
{
    public:
        int maxSize;
        list<Node>l;
        unordered_map<string,list<Node>::iterator> map;
        LRUchache(int maxSize)
        {
           this->maxSize=maxSize > 1 ? maxSize : 1;
        }

        void inserKeyValue(string key,int value)
        {
           if (map.count(key)!=0)
           {
            //replace the old value and update
            auto it=map[key];
            it->value=value; //update
           }
           else
           {
            //check if cache if full or not
            //remove the least recently used item from cache
            if (l.size()==maxSize)
            {
                Node last=l.back();
                map.erase(last.key); //remove from hashmap
                l.pop_back(); //remove from linked List
            }
            //or in other case make new node and add it to head of the linked list
            Node n(key,value);
            l.push_front(n);
            map[key]=l.begin();

           }
        }
         int* getValue(string key)
         {
            if (map.count(key)!=0 )
            {
                auto it =map[key];
                int value=it->value;
                l.push_front(*it);
                l.erase(it);
                map[key]=l.begin();
                return &l.begin()->value;
            }
            return NULL;

         }
         string mostRecentKey()
         {
            return l.front().key ;
            // return l.front().value;
         }
};

int main()
{
    LRUchache lru(3);
    lru.inserKeyValue("mango",10);
    lru.inserKeyValue("apple",20);
    lru.inserKeyValue("guava",30);
    cout<<lru.mostRecentKey()<<endl;

    cout<<lru.mostRecentKey()<<endl;
    lru.inserKeyValue("banana",20);

    lru.inserKeyValue("mango",40);

   
    

    auto *order=lru.getValue("mango");
    if (order!=NULL)
    {
        cout<<"Order of mango "<<*order<<endl;
    }

    if (lru.getValue("apple")==NULL)
    {
        cout<<"apple doesn't exist"<<endl;
    }

    
    if (lru.getValue("guava")==NULL)
    {
        cout<<"guava doesn't exist"<<endl;
    }

     if (lru.getValue("banana")==NULL)
    {
        cout<<"banana doesn't exist"<<endl;
    }

     if (lru.getValue("mango")==NULL)
    {
        cout<<"mango doesn't exist"<<endl;
    }
    return 0;
}