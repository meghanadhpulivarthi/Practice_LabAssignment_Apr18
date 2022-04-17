#include<bits/stdc++.h>
using namespace std;

class page{
private:
    int size;
    int used;
    page* next;
    page* prev;
    int count;
    int free;
    vector<pair<int,int>> v;
public:
    page(int size,page* prev){
        this->size=size;
        this->used=16;
        this->next=NULL;
        this->prev=prev;
        this->count=0;
        this->free=0;

    }
    int get_size(){
        return size;
    }
    int set_next(page* next){
        this->next=next;
        return 1;
    }
    page* get_next(){
        return next;
    }
    int get_free(){
        return size-used;
    }
    int get_count(){
        return count;
    }
    bool insert(int siz,int pk){
        if(used+4+siz<=size)
        {
            v.push_back(make_pair(pk,siz));
            used+=4+siz;
            count++;
            return 1;
        }
        else{
            return 0;
        }
    }
    int search(int pk){
        for(int i=0;i<v.size();i++){
//            cout<<v[i].first<<" "<<v[i].second<<endl;
            if(v[i].first==pk){return i;}
        }
        return -1;
    }
    page* get_prev(){
        return prev;
    }
    ~page();
};

page::~page()
{
}
class Heap_file
{
private:
    page*head;
    int count;
    int size;

public:
    Heap_file(int size);
    void insert(int siz,int pk);
    pair<int,int> search_n(int pk){
        page* temp=head;
        int num=0;
        while(temp){
//            cout<<"1"<<endl;
            int i=temp->search(pk);
            if(i!=-1)
            {
                return make_pair(num,i);
            }
            temp=temp->get_next();
            num++;
        }
        return make_pair(-1,-1);
    }
    void display(){
        page* temp=head;
        vector<int> v;
        while(temp){
            v.push_back(temp->get_count());
            temp=temp->get_next();
        }
        cout<<v.size()<<" ";

        for(int i=0;i<v.size();i++)
        {
            cout<<v[i]<<" ";
        }
        cout<<endl;
    }
    ~Heap_file();
};
Heap_file::Heap_file(int size){
    head=nullptr;
    this->size=size;
    this->count=0;
}
void Heap_file::insert(int siz,int pk){
//    cout<<count<<endl;
    if(count==0){
        head=new page(size,nullptr);
        if(head->insert(siz,pk)){count++;}
        else {
            cout << "error" << endl;
        }
    }else{
        page* temp=head;
        page*prev;
        while(temp&&temp->get_free()+siz+4>temp->get_size()){
//            cout<<temp->get_free()<<endl;
            prev=temp;
            temp=temp->get_next();

//            cout<<"done"<<endl;
        }
//        cout<<"this"<<endl;
        if(temp){
            temp->insert(siz,pk);
        }else{
//            cout<<"REACHED"<<endl;
            temp=prev;
//            cout<<"HERE ALSO"<<endl;
            page* new_page=new page(size,temp);
            temp->set_next(new_page);
            temp=new_page;
//            cout<<"DONE"<<endl;
            temp->insert(siz,pk);
        }
        // insert into temp

    }


}
Heap_file::~Heap_file(){}
int main(){
    int n;
    cin>>n;
    Heap_file hp(n);
    while(1){
        int k;
        cin>>k;
        if(k==1){
            int siz,pk;
            cin>>siz>>pk;
            hp.insert(siz,pk);
        }
        else if(k==2){hp.display();}
        else if(k==3){
            int pk;
            cin>>pk;
            pair<int,int> ans=hp.search_n(pk);
                cout<<ans.first<<" "<<ans.second<<endl;
        }else{break;}
    }
}
