#include<iostream>
using namespace std;

int d=0;            //size of data node is 2d
int t=0;            //size of index node is 2t+1
int num_indexNode=0;
int num_leafNode=0;
int MAX=0;

class Node{
    bool is_leaf;
    int *key;
    int size;
    Node** ptr;
    friend class BPTree;

public:
    Node();    
};

class BPTree{
    Node* root;
    void insertInternal(int,Node*,Node*);
    Node* findParent(Node*, Node*);

public:
    BPTree();
    void search(int);
    void insert(int);
    void display(Node*);
    Node* getRoot();
    void print();      
};

// Constructor of Node
Node::Node(){
    key = new int[MAX];
    ptr = new Node*[MAX + 1];
}

//Initialise the BPTree
BPTree::BPTree(){
    root=NULL;
}

//Search function in BPTree
void BPTree::search(int x){
    if(root==NULL){
        cout<<"Tree is Empty"<<endl;
    }else{
        Node* cursor=root;
        //finding the leaf ptr
        while((cursor->is_leaf)==false){
           
            for(int i=0;i<cursor->size;i++){
                if(x<cursor->key[i]){
                    cursor=cursor->ptr[i];
                    break;
                }
                if(i==cursor->size-1){
                    cursor=cursor->ptr[i+1];
                    break;
                }
            }
        }
        for(int i=0;i<cursor->size;i++){
            if((cursor->key[i])==x){
                cout<<"FOUND"<<endl;
                return;
            }
        }
        cout<<"NOT FOUND"<<endl;

    }
}

void BPTree::insert(int x){
    if(root==NULL){
        root=new Node;
        root->key[0]=x;
        root->size=1;
        root->is_leaf=true;
        num_leafNode++;
    }else{
        Node* cursor = root;
        Node* parent;

        while(cursor->is_leaf==false){
            parent=cursor;             /////DOUBT

            for(int i=0;i<cursor->size;i++){
                if(x<cursor->key[i]){
                   cursor=cursor->ptr[i];
                   break;
                }
                if(i==cursor->size-1){
                    cursor=cursor->ptr[i+1];
                    break;
                }
            }
        }
        if((cursor->size)<2*d){
           int i=0;
           while(x>cursor->key[i] && i<cursor->size){
               i++;
           }
           for(int j=cursor->size;j>i;j--){
               cursor->key[j]=cursor->key[j-1];
           }
           cursor->key[i]=x;
           cursor->size++;
        }else{
           Node* newLeaf=new Node;
           newLeaf->is_leaf=true;
           num_leafNode++;
           int virtualNode[2*d+1];
           for(int i=0;i<2*d;i++){
              virtualNode[i]=cursor->key[i];
           }
           int i=0;
           while(x>virtualNode[i] && i<2*d){
               i++;
           }
           for(int j=2*d;j>i;j--){
               virtualNode[j]=virtualNode[j-1];
           }
           virtualNode[i]=x;
           cursor->size=d;
           newLeaf->size=d+1;
           for(int j=0;j<cursor->size;j++){
               cursor->key[j]=virtualNode[j];
           }
           for(int j=0;j<newLeaf->size;j++){
               newLeaf->key[j]=virtualNode[d+j];
           }

           if(cursor==root){
               Node* newRoot=new Node;
               newRoot->size=1;
               newRoot->is_leaf=false;
               newRoot->key[0]=newLeaf->key[0];
               newRoot->ptr[0]=cursor;
               newRoot->ptr[1]=newLeaf;
               root=newRoot;
               num_indexNode++;
           }else{
               insertInternal(newLeaf->key[0],parent,newLeaf);
           }
        }
    }
}


void BPTree::insertInternal(int x,Node* cursor,Node* child){     //we have to make the new child of cursor to the child
    if((cursor->size)<(2*t+1)){
        int i=0;
        while(x>cursor->key[i] && i<cursor->size){
            i++;
        }
        for(int j=cursor->size;j>i;j--){    //shifting the keys
            cursor->key[j]=cursor->key[j-1];
           
        }
        for(int j=cursor->size+1;j>i+1;j--){
            cursor->ptr[j]=cursor->ptr[j-1];
        }
        cursor->key[i]=x;
        cursor->size++;
        cursor->ptr[i+1]=child;


    }else{
        Node* newInternal = new Node;
        newInternal->is_leaf=false;
        num_indexNode++;
        int virtualKey[2*t+2];
        Node* virtualPtr[2*t+3];

        for(int i=0;i<2*t+1;i++){
            virtualKey[i]=cursor->key[i];
        }
        for(int i=0;i<2*t+2;i++){
            virtualPtr[i]=cursor->ptr[i];
        }
        int i=0;

        while(x>virtualKey[i] && i<2*t+1){
            i++;
        }
        for(int j=2*t+1;j>i;j--){
            virtualKey[j]=virtualKey[j-1];
        }
        virtualKey[i]=x;
        for(int j=2*t+2;j>(i+1);j--){
            virtualPtr[j]=virtualPtr[j-1];
        }
        virtualPtr[i]=child;

        cursor->size=t;
        newInternal->size=t+1;
        for(int j=0;j<t;j++){
            cursor->key[j]=virtualKey[j];
        }
        for(int j=0;j<=t;j++){
            cursor->ptr[j]=virtualPtr[j];
        }
        for(int j=0;j<t+1;j++){
            newInternal->key[j]=virtualKey[j+t+1];
        }
        for(int j=0;j<(t+2);j++){
            newInternal->ptr[j]=virtualPtr[j+t+1];
        }
       
       
        if(cursor==root){
           Node* newRoot=new Node;
           newRoot->is_leaf=false;
           newRoot->size=1;
           newRoot->key[0]=virtualKey[t];
           newRoot->ptr[0]=cursor;
           newRoot->ptr[1]=newInternal;
           root=newRoot;
           num_indexNode++;
        }else{
            insertInternal(virtualKey[t],findParent(root,cursor),newInternal);

        }
    }
}


Node* BPTree::findParent(Node* cursor,Node* child){
   
    Node* parent;

    // If cursor reaches the end of Tree
    if (cursor->is_leaf
        || (cursor->ptr[0])->is_leaf) {
        return NULL;
    }

    // Traverse the current node with
    // all its child
    for (int i = 0;
        i < cursor->size + 1; i++) {

        // Update the parent for the
        // child Node
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        }

        // Else recursively traverse to
        // find child node
        else {
            parent
                = findParent(cursor->ptr[i],
                            child);

            // If parent is found, then
            // return that parent node
            if (parent != NULL)
                return parent;
        }
    }

    // Return parent node
    return parent;
}


Node* BPTree::getRoot(){
    return(root);
}

void BPTree::print(){
    if(root!=NULL){
    cout<<num_indexNode<<" "<<num_leafNode<<" ";
        for(int i=0;i<root->size;i++){
            cout<<root->key[i]<<" ";
        }
    cout<<endl;
}else{
    cout<<0<<" "<<0<<endl;
}
}



int main(){
    cin>>d>>t;
    MAX=max(2*d,2*t+1);
    int query,val=0;
    BPTree tree;

     while(cin>>query){
         if(query==1){
             cin>>val;
             tree.insert(val);
         }else if(query==2){
             //Node* currRoot=tree.getRoot();
             tree.print();
         }else{
             break;
         }
     }
    // tree.insert(100);
    //  tree.insert(200);
    //   tree.insert(300);
    //    tree.insert(400);
    //     tree.insert(500);
    //      tree.insert(600);
    //       tree.insert(700);
    //        tree.insert(800);
    //         tree.insert(450);
    //       tree.print();
    return 0;
}