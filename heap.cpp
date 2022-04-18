#include<iostream>
 #include<bits/stdc++.h>
 using namespace std;
 #define ll long long

int num_page=0;
int page_size=0;

class Node{
    vector<int> data;
    int num_data;
    int size_left;
    Node* next_page;
    Node* prev_page;
    friend class heap_file;

    public:
    Node();

};

class heap_file{
    Node* head;

    public:
    heap_file();
    void insert(int,int);
    void search(int);
    void status();

};

Node::Node(){
    num_data=0;
    next_page=NULL;
    prev_page=NULL;
    size_left=page_size-16;

}

heap_file::heap_file(){
    head=NULL;
}

void heap_file::insert(int size,int val){
    if(head==NULL){
        Node* new_head=new Node;
       
            new_head->data.push_back(val);
            num_page++;
            new_head->num_data++;
            new_head->size_left=new_head->size_left-(size+4);
            head=new_head;
       
       
    }else{
        Node* cursor=head;
        Node* parent=NULL;
        int i=0;
       
        while(1){  
              //
            if((cursor->size_left)<(size+4)){
                cursor=cursor->next_page;
                if(cursor==NULL){
                    break;
                }
            }else{
                break;
            }
           
           
        }
        //cout<<"y"<<endl;
       
        if(cursor==NULL){
            //cout<<"y"<<endl;
            int j=0;
            Node* last_page=head;
            //cout<<"y"<<endl;
            while(j<(num_page-1)){
                last_page=last_page->next_page;
                j++;
            }
            Node* new_page=new Node;
            new_page->data.push_back(val);
            num_page++;
            new_page->num_data++;
            new_page->size_left=new_page->size_left-(size+4);
            last_page->next_page=new_page;
            new_page->prev_page=last_page;
           


        }else{
            cursor->num_data++;
            cursor->data.push_back(val);
            cursor->size_left=cursor->size_left-(size+4);
        }

    }
}

void heap_file::search(int val){
    Node* cursor=head;
    int i=0;
    bool chk=false;
    while(i<num_page){
        for(int j=0;j<cursor->num_data;j++){
            if(cursor->data[j]==val){
                cout<<i<<" "<<j<<endl;
                return;
               
            }
        }
        cursor=cursor->next_page;
        i++;
    }
    cout<<-1<<" "<<-1<<endl;
    return;
}
void heap_file::status(){
   
    Node* cursor=head;
    if(head==NULL){
        cout<<0<<endl;
    }else{
        cout<<num_page<<" ";
        for(int i=0;i<num_page;i++){
            cout<<cursor->num_data<<" ";
            cursor=cursor->next_page;
        }
        cout<<endl;
    }
}


int main(){
   
    int query,val,size;
    cin>>page_size;
    heap_file file;

    while(cin>>query){
        if(query==1){
           
            cin>>size>>val;
            file.insert(size,val);
        }else if(query==2){
            //status
            file.status();
        }else if(query==3){
            //search
            cin>>val;
            file.search(val);
        }else if(query==4){
            break;
        }
    }
    return 0;
}