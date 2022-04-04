#include<bits/stdc++.h>
using namespace std;

int global_depth=0;
int num_buk;
int bucket_cap=0;
int ttime=0;                          ////////////////////////////////////////////


class buck{
    public:
        vector <int> v;
        int local_depth;
        int curr_cap;
        int creation_time;              ///////////////////////////////////////
};
vector <buck*> dir;

int hashfun(int n){
    int ans=((1<<global_depth)-1)&(n);
    return(ans);
}
int hashloc(int n,int c)
{
    int ans=((1<<c)-1)&(n);
    return(ans);
}

void double_dir(){
    int n=dir.size();
    global_depth++;
    for(int i=0;i<n;i++){
        dir.push_back(dir[i]);
    }
}

void split(int val){

    int n=hashfun(val);
    int c=dir[n]->local_depth;
    c++;
    num_buk++;
    buck* p=NULL;
    p=new buck();
    p->curr_cap=0;
    p->creation_time=ttime;             //////////////////////////
    ttime++;                           ///////////////////////////
    // swap(p->creation_time,dir[n]->creation_time);
    dir[n]->local_depth++;
    (p->local_depth)=(dir[n]->local_depth);
     

    for(int i=0;i<bucket_cap;i++){         //here bucket_cap is always equal to dir[n]->curr_cap
        if(hashloc(dir[n]->v[i],c)==hashloc(val,c)){
            p->v.push_back(dir[n]->v[i]);
            p->curr_cap++;
            dir[n]->v[i]=-1;  //dir[n]->v.begin() + i
            dir[n]->curr_cap--;  //value of curr_cap decrease karo!!
        }
    }
        auto it = dir[n]->v.begin();
        while(it != dir[n]->v.end())
        {
            if(*it == -1)
            {
                it = dir[n]->v.erase(it);
            }
            else
                it++;
        }
    
    // if(p->v.size()==bucket_cap)swap(p->creation_time,dir[n]->creation_time);
    // if(hashfun(val)!=hashloc(val,c))swap(p->creation_time,dir[n]->creation_time);
    bool ok=1;
    if( (c-1)<<1&val)
    {
        ;
    }
    else{
        swap(p->creation_time,dir[n]->creation_time);
    }
    int var=pow(2,global_depth);
    for(int i=0;i<var;i++)
    {
        if(hashloc(i,c)==hashloc(val,c))
        {
            dir[i]=p;
        }
    }
} 

void insert(int val){
    int n=hashfun(val);
    if((dir[n]->curr_cap)<bucket_cap){
        dir[n]->v.push_back(val);
        dir[n]->curr_cap++;
        return;
    }
    if((dir[n]->local_depth)==global_depth){
        double_dir();
    }
    split(val);
    insert(val);
    
    
}

bool search(int val){
    int n=hashfun(val);
    for(int i=0;i<dir[n]->curr_cap;i++){
        if((dir[n]->v[i])==val){
            return(true);
        }
    }
    return(false);
}

void delete_val_lazy(int val){
    int n=hashfun(val);
    if(search(val)==true){
        for(int i=0;i<dir[n]->curr_cap;i++){
            if((dir[n]->v[i])==val){
                dir[n]->v.erase(dir[n]->v.begin() + i);
                dir[n]->curr_cap--;
                break;
            }
        }  
    }
}

void delete_val_merge(int val){
    ///if empty after deletion merge with its split bucket and decrease the local depth of the split bucket
    ///half the directory and decrease the global depth by 1
}

void print_buck(){
    cout<<global_depth<<endl;
    cout<<num_buk<<endl;
    for(int i=0;i<ttime;i++){
        for(int j=0;j<dir.size();j++){
            if((dir[j]->creation_time)==i){
                cout<<dir[j]->curr_cap<<" "<<dir[j]->local_depth<<endl;
                break;
            }
        }
                
    }
}
 
int main(){
    int query=0;
    int val=0;
    cin>>global_depth>>bucket_cap;
    num_buk=pow(2,global_depth);
    for(int i=0;i<pow(2,global_depth);i++){
        buck *p=NULL;
        p= new buck();
        p->curr_cap=0;
        p->local_depth=global_depth;
        p->creation_time=ttime;               ///////////////////////////////
        ttime++;                              ////////////////////////////////
        dir.push_back(p);
    }
   

    while(cin>>query){
        if(query==2){
            cin>>val;
            insert(val);
        }else if(query==3){
            cin>>val;
            if(search(val)==true){
                cout<<val<<" is there in a bucket"<<endl;
            }else{
                cout<<"NOT FOUND"<<endl;
            }
        }else if(query==4){
            cin>>val;
            delete_val_lazy(val);
        }else if(query==5){
           




                    print_buck();



           }
           else{
            break;
        }
    }
    return 0;
}