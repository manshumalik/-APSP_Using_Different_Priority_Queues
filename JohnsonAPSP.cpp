#include<bits/stdc++.h>
#include <time.h> 
using namespace std;
struct vertex;
struct edge;
struct binomialheap;
struct fibheap;
struct vertex{
  int val;                    // the value of this node / index of this node
  edge* ed[100000];             // array of edges
  int ctr;                  // total no. of edges
  int inci;                     // the no. of incident edges on this node
  int visi;                    // wether this node is visited yet or not 
  int indeg;                   
  int dist;                 // the distance of this node from the given source 
  int fintime;                  
  int posinbinheap;            // the position of this node in the binary heap array/vertex
  int funch;                    // the bellman ford value of distance from the additional node added 
  binomialheap* binomialnode;   
  fibheap* fibnode;
  
};
struct edge{
    vertex* tail;       // pointer to vertex that is at the tail 
    vertex* head;          // pointer to the vertex that is at the head
    int type;           // the type of edge i.e forward , backward etc. 
    int weight;         // the weight associated with this edge 
};
struct binomialheap{

    int rank=-1;            // rank is -1 if there are no children and rank increases as children increase 
    binomialheap* children[100];    //here throughout the code the children are stored such that if the rank[jth child] < rank[ith child]  then j < i 
    binomialheap* parent;               // pointer to parent binomial node  
    vertex* node;              // pointer to the graph vertex contained in the is binomial node  

};
struct fibheap{

    int rank=-1;            // rank is -1 if there are no children and rank increases as children increase 
    list <fibheap*> children;    //here throughout the code the children are stored such that if the rank[jth child] < rank[ith child]  then j < i 
    fibheap* parent=NULL;       // pointer to parent fibonacci node
    vertex* node;           // pointer to the graph vertex contained in the is fibonacci node 
    int loser=0;              // if one of it's child is cut then loser is 1 , else it is 0 ,and if loser is 1 and another child is cut then the entire node is cut and put in the list
    list<fibheap*>::iterator parentit;  // if parent is not NULL then this will point to the location of itself in the parent's list of children
};
//bEllman ford stuff:- 
int belford(vertex v[],int sizev,int sizee)
{

    vertex* src;
    vertex vnew;
    edge e[sizev];
    vnew.val=sizev+1;
    vnew.ctr=0;
    vnew.visi=0;
    vnew.inci=-1;
    vnew.indeg=0;
    vnew.dist=999999;
    vnew.fintime=-1;

    for(int i=0;i<sizev;i++)
    {
        e[i].tail=&vnew;
        e[i].head=&v[i];
        e[i].type=0;
        e[i].weight=0;
        v[i].ed[v[i].ctr++]=&e[i];
        vnew.ed[vnew.ctr++]=&e[i];
        v[i].indeg++;
    }

    int temp2,flag,ctr,ctr2;
    ctr2=0;
    ctr=0;
    int j;
    src=&vnew;
    for(j=0;j<=sizev+1;j++)
    {
        flag=0;
        for(int i=0;i<sizev;i++)
        {
            v[i].visi=0;
        }
        queue <vertex*> q;
        vertex* temp;
        src->visi=1;
        src->dist=0;
        q.push(src);
        while(!q.empty())
        {
            temp=q.front();
            q.pop();
            for(int i=0;i<temp->ctr;i++)
            {

                if((temp->ed[i])->head==temp)
                {
                    continue;
                }
                else if((temp->ed[i])->tail==temp)
                {
                    if((temp->ed[i])->head->visi==0)
                    {
                        (temp->ed[i])->head->visi=1;
                        q.push((temp->ed[i])->head);

                    }
                    temp2=((temp->ed[i])->head)->dist;
                    ctr2++;
                    ((temp->ed[i])->head)->dist=min(((temp->ed[i])->head)->dist,(((temp->ed[i])->tail)->dist)+(temp->ed[i]->weight));
                    if(temp2!=((temp->ed[i])->head)->dist)
                    {
                        ctr++;
                        flag=1;
                    }
                }
            }

        }
        if(flag==0)
        {
            break;
        }

    }
    if(flag==1)
    {
         return -1;
    }
    else if(flag==0)
    {

        for(int i=0;i<sizev;i++)
        {
            v[i].ctr--;
            v[i].funch=v[i].dist;
            v[i].dist=999999;
            v[i].visi=0;
        }
        
    }
    return 0;
}

// bellman ford stuff ends 

//array stuff

void dijkstraarray(vertex v[],int s,int sizev)
{
    int source=s-1;
    vector<vertex*>v1;
    vertex* temp;
    v[source].dist=0;
    for(int i=0;i<sizev;i++)
    {
        temp=&v[i];
        v1.push_back(temp);
    }
    int intermediatesize=sizev-1;
    int k=0;
    while(k!=intermediatesize+1)
    {
        vertex* temp2;
        for(int i=k;i<=intermediatesize;i++)        // simple code for sorting 
        {
            for(int j=k;j<=intermediatesize;j++)
            {
                if(j==intermediatesize)
                {
                    break;
                }
                if(v1[j]->dist>v1[j+1]->dist)
                {
                    temp2=v1[j+1];
                    v1[j+1]=v1[j];
                    v1[j]=temp2;

                }
                else if(v1[j]->dist==v1[j+1]->dist)
                {
                    if(v1[j]->val>v1[j+1]->val)
                    {
                        temp2=v1[j+1];
                        v1[j+1]=v1[j];
                        v1[j]=temp2;
                    }
                }
            }
        }
        temp=v1[k];
        temp->visi=1;
        k++;
        

        int j;

        for(int i=0;i<temp->ctr;i++)
        {
            if((temp->ed[i])->tail==temp&&(temp->ed[i])->head->visi==0)
            {
                ((temp->ed[i])->head)->dist=min(((temp->ed[i])->head)->dist,(((temp->ed[i])->tail)->dist)+(temp->ed[i]->weight));
            }

        }

        

    }
    for(int i=0;i<sizev;i++)
    {
        if(v[i].dist!=999999)
        {
            printf("%d ",v[i].dist-(v[source].funch)+v[i].funch);
        }
        else
        {
            printf("%d ",v[i].dist);
        }
    }
    printf("\n");
}


void dijkstraundirarray(vertex v[],int s,int sizev)
{

    int source=s-1;
    vector<vertex*>v1;
    vertex* temp;
    v[source].dist=0;
    for(int i=0;i<sizev;i++)
    {
        temp=&v[i];
        v1.push_back(temp);
    }
    int intermediatesize=sizev-1;
    int k=0;
    while(k!=intermediatesize+1)
    {
        
        vertex* temp2;
        for(int i=k;i<=intermediatesize;i++)        // simple code for sorting 
        {
            for(int j=k;j<=intermediatesize;j++)
            {
                if(j==intermediatesize)
                {
                    break;
                }
                if(v1[j]->dist>v1[j+1]->dist)
                {
                    temp2=v1[j+1];
                    v1[j+1]=v1[j];
                    v1[j]=temp2;

                }
                else if(v1[j]->dist==v1[j+1]->dist)
                {
                    if(v1[j]->val>v1[j+1]->val)
                    {
                        temp2=v1[j+1];
                        v1[j+1]=v1[j];
                        v1[j]=temp2;
                    }
                }
            }
        }
        temp=v1[k];
        temp->visi=1;
        k++;
        for(int i=0;i<temp->ctr;i++)
        {


            if((temp->ed[i])->tail==temp&&(temp->ed[i])->head->visi==0)
            {
                ((temp->ed[i])->head)->dist=min(((temp->ed[i])->head)->dist,(((temp->ed[i])->tail)->dist)+(temp->ed[i]->weight));
               
            }
            else if((temp->ed[i])->head==temp&&(temp->ed[i])->tail->visi==0)
            {
                ((temp->ed[i])->tail)->dist=min(((temp->ed[i])->tail)->dist,(((temp->ed[i])->head)->dist)+(temp->ed[i]->weight));
                
            }

            

        }
    }
    

    for(int i=0;i<sizev;i++)
    {
        printf("%d ",v[i].dist);
    }
    printf("\n");
}


//array stuff ends


// Binary Heap Stuff


struct func{
bool operator()(vertex* a,vertex* b) const{
    return (a->dist)>(b->dist);
}
};
void percolatebinheap(int loc, vector<vertex *> &v1, int downoup, int heapsize)
{

    vertex* temp2;
    if(downoup==1)      //precolating down 
    {
        while((2*loc)+1<=heapsize)  //ensures that this node has children
        {

            if((2*loc)+2>heapsize)      //if has only 1 child 
            {
                if(v1[loc]->dist<v1[(2*loc)+1]->dist)       //if the child's value is bigger
                {
                    break;
                }
                else if(v1[loc]->dist==v1[(2*loc)+1]->dist)     //if child's dist value is same then considering the lexicographically smaller one as the one to be above 
                {
                    if(v1[loc]->val<v1[(2*loc)+1]->val)
                    {
                        break;
                    }
                    else
                    {
                        temp2=v1[(2*loc)+1];
                        v1[(2*loc)+1]=v1[loc];
                        v1[loc]->posinbinheap=(2*loc)+1;
                        v1[loc]=temp2;
                        v1[loc]->posinbinheap=loc;
                        loc=(2*loc)+1;
                    }
                }
                else                        //child's dist value is smaller 
                {
                   temp2=v1[(2*loc)+1];
                   v1[(2*loc)+1]=v1[loc];
                   v1[loc]->posinbinheap=(2*loc)+1;
                   v1[loc]=temp2;
                   v1[loc]->posinbinheap=loc;
                   loc=(2*loc)+1;
                }
                continue;
                
            }
            if(v1[loc]->dist<v1[(2*loc)+1]->dist&&v1[loc]->dist<v1[(2*loc)+2]->dist) // the dist value of parent is smaller than both the children 
            {
                break;
            }
           else
           {
               if(v1[(2*loc)+1]->dist<v1[(2*loc)+2]->dist)      //looking at the child with the smaller dist value 
               {
                   
                    if(v1[loc]->dist==v1[(2*loc)+1]->dist)      //if that dist value is equal to the parent then lexicographically 
                    {
                        if(v1[loc]->val<v1[(2*loc)+1]->val)
                        {
                        break;
                        }
                        else
                        {
                        temp2=v1[(2*loc)+1];
                        v1[(2*loc)+1]=v1[loc];
                        v1[loc]->posinbinheap=(2*loc)+1;
                        v1[loc]=temp2;
                        v1[loc]->posinbinheap=loc;
                        loc=(2*loc)+1;
                        break;
                        }
                    }
                   temp2=v1[(2*loc)+1];     //if the dist value of parent is larger than the child in question
                   v1[(2*loc)+1]=v1[loc];
                   v1[loc]->posinbinheap=(2*loc)+1;
                   v1[loc]=temp2;
                   v1[loc]->posinbinheap=loc;
                   loc=(2*loc)+1;
                   
                   
               }
               else if(v1[(2*loc)+2]->dist<v1[(2*loc)+1]->dist) //if the other child's dist value is smaller 
               {
                   if(v1[loc]->dist==v1[(2*loc)+2]->dist)   // if the parent's and child's dist values are same 
                    {
                    if(v1[loc]->val<v1[(2*loc)+2]->val)     //lexicographically smaller
                        {
                            break;
                        }
                    else
                        {
                            temp2=v1[(2*loc)+2];
                            v1[(2*loc)+2]=v1[loc];
                            v1[loc]->posinbinheap=(2*loc)+2;
                            v1[loc]=temp2;
                            v1[loc]->posinbinheap=loc;
                            loc=(2*loc)+2;
                            break;
                        }
                    }
                   temp2=v1[(2*loc)+2];     // the childs dist value is smaller
                   v1[(2*loc)+2]=v1[loc];
                   v1[loc]->posinbinheap=(2*loc)+2;
                   v1[loc]=temp2;
                   v1[loc]->posinbinheap=loc;
                   loc=(2*loc)+2;
                  
               }
               else if(v1[(2*loc)+2]->dist==v1[(2*loc)+1]->dist)        // if the dist value of both the children are same 
               {
                   if(v1[loc]->dist==v1[(2*loc)+2]->dist)               // if the dist value of parents and children are equal
                   {
                        if(v1[loc]->val<v1[(2*loc)+1]->val&&v1[loc]->val<v1[(2*loc)+2]->val) //if the number of the parent is lower than both the children 
                        {
                            break;
                        }
                        else if(v1[loc]->val>v1[(2*loc)+1]->val&&v1[loc]->val>v1[(2*loc)+2]->val)   //if number greater than both the children
                        {
                            if(v1[(2*loc)+2]->val>v1[(2*loc)+1]->val)   //exchanging with the smaller numbered child
                            {
                                temp2=v1[(2*loc)+1];
                                v1[(2*loc)+1]=v1[loc];
                                v1[loc]->posinbinheap=(2*loc)+1;
                                v1[loc]=temp2;
                                v1[loc]->posinbinheap=loc;
                                loc=(2*loc)+1;
                                
                            }
                            else    // same as above 
                            {
                                temp2=v1[(2*loc)+2];
                                v1[(2*loc)+2]=v1[loc];
                                v1[loc]->posinbinheap=(2*loc)+2;
                                v1[loc]=temp2;
                                v1[loc]->posinbinheap=loc;
                                loc=(2*loc)+2;
                            }
                        }
                      else if(v1[loc]->val>v1[(2*loc)+1]->val&&v1[loc]->val<v1[(2*loc)+2]->val) // number greater than one of the child and lesser than the other 
                        {
                                temp2=v1[(2*loc)+1];
                                v1[(2*loc)+1]=v1[loc];
                                v1[loc]->posinbinheap=(2*loc)+1;
                                v1[loc]=temp2;
                                v1[loc]->posinbinheap=loc;
                                loc=(2*loc)+1;
                        }
                        else if(v1[loc]->val<v1[(2*loc)+1]->val&&v1[loc]->val>v1[(2*loc)+2]->val)
                        {
                                temp2=v1[(2*loc)+2];
                                v1[(2*loc)+2]=v1[loc];
                                v1[loc]->posinbinheap=(2*loc)+2;
                                v1[loc]=temp2;
                                v1[loc]->posinbinheap=loc;
                                loc=(2*loc)+2;
                        }  
                   }
                   else if(v1[loc]->dist>v1[(2*loc)+1]->dist)       //in case the dist value of parent is greater than children,children have same dist value 
                   {
                       if(v1[(2*loc)+1]->val<v1[(2*loc)+2]->val)
                       {
                                temp2=v1[(2*loc)+1];
                                v1[(2*loc)+1]=v1[loc];
                                v1[loc]->posinbinheap=(2*loc)+1;
                                v1[loc]=temp2;
                                v1[loc]->posinbinheap=loc;
                                loc=(2*loc)+1;
                       }
                       else 
                       {
                                temp2=v1[(2*loc)+2];
                                v1[(2*loc)+2]=v1[loc];
                                v1[loc]->posinbinheap=(2*loc)+2;
                                v1[loc]=temp2;
                                v1[loc]->posinbinheap=loc;
                                loc=(2*loc)+2;
                       }
                   }
                }
           }

        }
    }
    else if(downoup==0)         //percolating up
    {

        vertex* parent;
        int index;
        while(loc>0)    
        {
           if(loc%2==0)     //who is the parent 
           {
               parent=v1[(loc-1)/2];
               index=(loc-1)/2;
           }
           else
           {
               parent=v1[loc/2];
               index=loc/2;
           }
           if(parent->dist<v1[loc]->dist)   // if parent's dist is already lower 
           {
                break;
           }
           else if(parent->dist==v1[loc]->dist && parent->val<v1[loc]->val )        //if the parent's distance value is same but the numbering is lesser 
           {
                break;
           }
           else
           {
               
                   temp2=parent;
                   v1[index]=v1[loc];
                   v1[loc]->posinbinheap=index;
                   v1[loc]=parent;
                   v1[loc]->posinbinheap=loc;
                   loc=index;
                   continue;
               
           }

        }

    }
}


void dijkstrabinary(vertex v[],int s,int sizev)
{
    int source=s-1;
    vector<vertex*>v1;
    vertex* temp;
    v[source].dist=0;
    for(int i=0;i<sizev;i++)
    {
        temp=&v[i];
        v1.push_back(temp);
    }
    make_heap(v1.begin(),v1.end(),func());      // just to make initial heap
    auto it = v1.begin();
    for(int i=0;i<sizev;i++)
    {
        temp=*it;
        temp->posinbinheap=i;
        it++;
    }
    int intermediatesize=sizev-1;
    
    while(!v1.empty())
    {
        temp=v1.front();
        temp->visi=1;
        v1[0]=v1[intermediatesize--];
        v1.pop_back();
        vertex* temp2;
        v1[0]->posinbinheap=0;
        
        percolatebinheap(0,v1,1,intermediatesize);  //Starting from root to percolate down

        int j;

        for(int i=0;i<temp->ctr;i++)
        {
            if((temp->ed[i])->tail==temp&&(temp->ed[i])->head->visi==0)
            {
                ((temp->ed[i])->head)->dist=min(((temp->ed[i])->head)->dist,(((temp->ed[i])->tail)->dist)+(temp->ed[i]->weight));
                j=((temp->ed[i])->head)->posinbinheap;
                percolatebinheap(j,v1,0,intermediatesize);  //Starting from updated distance to percolate up
            }

        }

        

    }
    for(int i=0;i<sizev;i++)
    {
        if(v[i].dist!=999999)
        {
            printf("%d ",v[i].dist-(v[source].funch)+v[i].funch);
        }
        else
        {
            printf("%d ",v[i].dist);
        }
    }
    printf("\n");
}


void dijkstraundirbinary(vertex v[],int s,int sizev)
{

    int source=s-1;
    vector<vertex*>v1;
    vertex* temp;
    v[source].dist=0;
    for(int i=0;i<sizev;i++)
    {
        temp=&v[i];
        v1.push_back(temp);
    }
    make_heap(v1.begin(),v1.end(),func());  //making min heap
    auto it = v1.begin();
    for(int i=0;i<sizev;i++)
    {
        temp=*it;
        temp->posinbinheap=i;
        it++;
    }
    int intermediatesize=sizev-1;
    while(!v1.empty())
    {
        temp=v1.front();
        temp->visi=1;
        v1[0]=v1[intermediatesize--];
        int i=0;
        v1.pop_back();
        vertex* temp2;
        v1[0]->posinbinheap=0;
        
        percolatebinheap(0,v1,1,intermediatesize);  //Starting from root to percolate down

        int j;
        for(int i=0;i<temp->ctr;i++)
        {


            if((temp->ed[i])->tail==temp&&(temp->ed[i])->head->visi==0)
            {
                ((temp->ed[i])->head)->dist=min(((temp->ed[i])->head)->dist,(((temp->ed[i])->tail)->dist)+(temp->ed[i]->weight));
                j=((temp->ed[i])->head)->posinbinheap;
                percolatebinheap(j,v1,0,intermediatesize);  //Starting from updated distance to percolate up
            }
            else if((temp->ed[i])->head==temp&&(temp->ed[i])->tail->visi==0)
            {
                ((temp->ed[i])->tail)->dist=min(((temp->ed[i])->tail)->dist,(((temp->ed[i])->head)->dist)+(temp->ed[i]->weight));
                j=((temp->ed[i])->tail)->posinbinheap;
                percolatebinheap(j,v1,0,intermediatesize);  //Starting from updated distance to percolate up
            }

            

        }
    }
    

    for(int i=0;i<sizev;i++)
    {
        printf("%d ",v[i].dist);
    }
    printf("\n");
}


// Binary heap stuff ends 

//binomial heap stuff starts :-

void joinbinomialheap(list<binomialheap*> &l1,list<binomialheap*> &l2)  // just joins the 2 binomial heaps into a single linked list in ascending order of rank
{
    
    for(auto it1=l1.begin();it1!=l1.end();it1++)
    {
        if(l2.empty())
       {
           break;
       }
       else 
       {    
           auto it2=l2.begin();
           while((*it2)->rank<=(*it1)->rank)
           {
               l1.insert(it1,(*it2));
               l2.pop_front();
               if(l2.empty())
               {
                   break;
               }
               it2=l2.begin();
           }
       }
    }
   if(l2.empty()!=1)       //if the original list is finished and the rank of the remaining items in list 2 is higher then inserting all of them in the end
    {
        while(l2.empty()!=1)
        {
            binomialheap* temporaary=*(l2.begin());
            l1.push_back(temporaary);
            auto ita=l2.begin();
           l2.erase(ita);
        }
    }
}
void fixjointbinomialheap(list<binomialheap*> &l1)
{
   
    for(auto it=l1.begin();it!=l1.end();it++)
    {  
        auto tempit2=it;
        auto tempit=it;
        tempit++;                               //tempit is the pointer to the next binomial tree
        if(tempit==l1.end())
        {
            break;
        }
        if((*it)->rank<(*(tempit))->rank)       // if the rank of the next bin tree is larger
        {
            continue;
        }
        else if((*it)->rank==(*tempit)->rank)   //if the rank of the next and the current binary trees are equal 
        {
            tempit++;
            if(tempit!=l1.end())
            {
                if((*it)->rank==(*tempit)->rank)    // if the rank of the next->next binary tree is also equal then skip 
                {
                    continue;
                }
                else if((*it)->rank!=(*tempit)->rank)    // if the rank of the current and the next binary trees are same but the next next is different 
               {
                    tempit--;
                    if((*tempit)->node->dist<(*it)->node->dist) //now checking which one to make whose parents 
                    {
                        (*it)->parent=(*tempit);
                        (*tempit)->rank++;
                        (*tempit)->children[(*tempit)->rank]=(*it);
                        tempit2=it;
                        tempit2--;
                        l1.erase(it);
                        it=tempit2;
                    }
                    else if((*tempit)->node->dist>(*it)->node->dist)
                    {
                        (*tempit)->parent=(*it);
                        (*it)->rank++;
                        (*it)->children[(*it)->rank]=(*tempit);
                        l1.erase(tempit);
                        it--;
                    }      
                    else if((*tempit)->node->dist==(*it)->node->dist)   // if the dist value is dijkstra is same then we would check and put smaller index for lexicographic order 
                    {
                        if((*tempit)->node->val<(*it)->node->val)
                        {
                            (*it)->parent=(*tempit);
                            (*tempit)->rank++;
                            (*tempit)->children[(*tempit)->rank]=(*it);
                            tempit2=it;
                            tempit2--;
                            l1.erase(it);
                            it=tempit2;
                        }
                        else
                        {
                            (*tempit)->parent=(*it);
                            (*it)->rank++;
                            (*it)->children[(*it)->rank]=(*tempit);
                            l1.erase(tempit);
                            it--;
                        }       // in all of the above if-else when the trees are merged then the arrangement is made such that the same merged tree is encountered in the next iteration as well 
                    }
                }
            }
            else   // if there is no next next node in list  
            {
                tempit--;
                if((*tempit)->node->dist<(*it)->node->dist) //now checking which one to make whose parents 
                {
                    (*it)->parent=(*tempit);
                    (*tempit)->rank++;
                    (*tempit)->children[(*tempit)->rank]=(*it);
                    tempit2=it;
                    tempit2--;
                    l1.erase(it);
                    it=tempit2;
                }
                else if((*tempit)->node->dist>(*it)->node->dist)
                {
                    (*tempit)->parent=(*it);
                    (*it)->rank++;
                    (*it)->children[(*it)->rank]=(*tempit);
                    l1.erase(tempit);
                    it--;
                }
                else if((*tempit)->node->dist==(*it)->node->dist)   // if the dist value is dijkstra is same then we would check and put smaller index for lexicographic order 
                {
                    if((*tempit)->node->val<(*it)->node->val)
                    {
                        (*it)->parent=(*tempit);
                        (*tempit)->rank++;
                        (*tempit)->children[(*tempit)->rank]=(*it);
                        tempit2=it;
                        tempit2--;
                        l1.erase(it);
                        it=tempit2;
                    }
                    else
                    {
                        (*tempit)->parent=(*it);
                        (*it)->rank++;
                        (*it)->children[(*it)->rank]=(*tempit);
                        l1.erase(tempit);
                        it--;
                    }       // in all of the above if-else when the trees are merged then the arrangement is made such that the same merged tree is encountered in the next iteration as well 
                    
                }
            }
        }
    }
}
vertex* extractminbinomialheap(list<binomialheap*> &l1,list<binomialheap*> &l2)  // l2 is a completely empty list 
{
    int min = 9999999;
    auto pointertomin=l1.begin();
    for(auto it=l1.begin();it!=l1.end();it++)// loop to find the min element in the list of binomial heap 
    {
        if((*it)->node->dist<min)    //if the dist of current tree is less then update min
        {
            min=(*it)->node->dist;
            pointertomin=it;
        }
        else if((*it)->node->dist==min)         // if we find a min distance equal then we check for index for lexicographic ordering 
        {
            if((*pointertomin)->node->val<(*it)->node->val)
            {
                continue;
            }
            else 
            {
                pointertomin=it;
            }
        }                               
        else                //if the distance is greater than the current min.
        {
            continue;
        }

    }
    for(int i=0;i<=(*pointertomin)->rank;i++)       // now making a seperate list of the children of the extracted node 
    {
        (*pointertomin)->children[i]->parent=NULL;
        l2.push_back((*pointertomin)->children[i]);
    }
    vertex* temp;
    temp=(*pointertomin)->node;
    l1.erase(pointertomin);
    return temp;                        // returning the vertex with the minimum dist.

}
void percolateupbinomialheap(vertex* v)     // percolating up after decrease key 
{
    binomialheap* temp;
    vertex*  temp2;
    temp=v->binomialnode;
    while(temp->parent!=NULL)               // till there are parents to percolate up to 
    {
        if(temp->node->dist<temp->parent->node->dist)       // if the dist of parent is more then swap
        {
            temp2=temp->node;
            temp->node=temp->parent->node;
            temp->node->binomialnode=temp;
            temp->parent->node=temp2;
            temp->parent->node->binomialnode=temp->parent;
            temp=temp->parent;
        }
        else if(temp->node->dist>temp->parent->node->dist)          // if the dist of parent is less then break 
        {
            break;
        }
        else if(temp->node->dist==temp->parent->node->dist)     // if the dist of parent is same as child then check index for lexicographic
        {
            if(temp->node->val<temp->parent->node->val)         // if the index of the child is less then swapping 
            {
                temp2=temp->node;
                temp->node=temp->parent->node;
                temp->node->binomialnode=temp;
                temp->parent->node=temp2;
                temp->parent->node->binomialnode=temp->parent;
                temp=temp->parent;   
            }
            else if(temp->node->val>temp->parent->node->val)        // else no need to swap
            {
                break;
            }
        }
    }
}


void dijkstrabinomial(vertex v[],int s,int sizev)
{

    binomialheap *h= new binomialheap[sizev];
    list <binomialheap*> original;
    list<binomialheap*> secondary;
    original.clear();
    secondary.clear();
    int source=s-1;
    v[source].dist=0;

    for(int i=0;i<sizev;i++)
    {
        h[i].parent=NULL;
        h[i].node=&v[i];
        v[i].binomialnode=&h[i];
        secondary.push_back(&h[i]);
        joinbinomialheap(original,secondary);
        fixjointbinomialheap(original);
        secondary.clear();
    }
    secondary.clear();    
    
    vertex* temp;

    while(original.empty()!=1)
    {
        secondary.clear();
        temp=extractminbinomialheap(original,secondary);
        joinbinomialheap(original,secondary);
        fixjointbinomialheap(original);

        for(int i=0;i<temp->ctr;i++)
        {
            if((temp->ed[i])->tail==temp&&(temp->ed[i])->head->visi==0)
            {
                ((temp->ed[i])->head)->dist=min(((temp->ed[i])->head)->dist,(((temp->ed[i])->tail)->dist)+(temp->ed[i]->weight));

                percolateupbinomialheap(((temp->ed[i])->head));  //Starting from updated distance to percolate up
            }

        }

        

    }
    for(int i=0;i<sizev;i++)
    {
        if(v[i].dist!=999999)
        {
            printf("%d ",v[i].dist-(v[source].funch)+v[i].funch);
        }
        else
        {
            printf("%d ",v[i].dist);
        }
    }
    printf("\n");
}


void dijkstraundirbinomial(vertex v[],int s,int sizev)
{

    int source=s-1;
    vertex* temp;
    v[source].dist=0;
    binomialheap *h= new binomialheap[sizev];
    list <binomialheap*> original;
    list<binomialheap*> secondary;
    original.clear();
    secondary.clear();

    for(int i=0;i<sizev;i++)
    {
        h[i].parent=NULL;
        h[i].node=&v[i];
        v[i].binomialnode=&h[i];
        secondary.push_back(&h[i]);
        joinbinomialheap(original,secondary);
        fixjointbinomialheap(original);
        secondary.clear();
    }
    secondary.clear();    
    

    while(original.empty()!=1)
    {
        secondary.clear();
        temp=extractminbinomialheap(original,secondary);
        joinbinomialheap(original,secondary);
        fixjointbinomialheap(original);

        for(int i=0;i<temp->ctr;i++)
        {

            if((temp->ed[i])->tail==temp&&(temp->ed[i])->head->visi==0)
            {
                ((temp->ed[i])->head)->dist=min(((temp->ed[i])->head)->dist,(((temp->ed[i])->tail)->dist)+(temp->ed[i]->weight));
                percolateupbinomialheap(((temp->ed[i])->head));  //Starting from updated distance to percolate up
            }
            else if((temp->ed[i])->head==temp&&(temp->ed[i])->tail->visi==0)
            {
                ((temp->ed[i])->tail)->dist=min(((temp->ed[i])->tail)->dist,(((temp->ed[i])->head)->dist)+(temp->ed[i]->weight));
                percolateupbinomialheap(((temp->ed[i])->tail));  //Starting from updated distance to percolate up
            }
        }
    }
    
    for(int i=0;i<sizev;i++)
    {
        printf("%d ",v[i].dist);
    }
    printf("\n");
}

//binomial heap stuff ends 

//fibonacci heap stuff starts :- 

void joinfibheap(list<fibheap*> &l1,list<fibheap*> &l2)     // simply puts elements of l2 into list l1
{
    for(auto it=l2.begin();it!=l2.end();it++)
    {
        l1.push_front((*it));
    }
    l2.clear();
   
}
void decreasefibkey(vertex* v1,list <fibheap*> &l1)     // cuts the different nodes and puts it into the list passed as argument 
{
    fibheap* temp=v1->fibnode;
    fibheap* temp2;
    if(temp->parent!=NULL)
    {
        if(temp->node->dist<temp->parent->node->dist)       // if the dist of current node is less than parent then cutting the current node  
        {
            temp->loser=0;
            l1.push_front(temp);
            temp->parent->children.erase(temp->parentit);
            temp->parent->rank--;
            temp2=temp->parent;
            temp->parent=NULL;
            temp=temp2;
        }
        else if(temp->node->dist==temp->parent->node->dist)     //if equal then checking for lexicographic ordering 
        {
            if(temp->node->val<temp->parent->node->val)
            {
                temp->loser=0;
                l1.push_front(temp);
                temp->parent->children.erase(temp->parentit);
                temp->parent->rank--;
                temp2=temp->parent;
                temp->parent=NULL;
                temp=temp2;
            }
            else 
            {
                return;
            }
        }
        else if(temp->node->dist>temp->parent->node->dist)
        {
            return;
        }
    }
    else if(temp->parent==NULL) 
    {
        return;
    }
    while(temp->parent!=NULL)       // now checkign for those nodes which have already had a child cut 
    {
        
        if(temp->loser==1)      // if one node has been already cut then removing this node as well and then checking for parent 
        {
            temp->loser=0;
            l1.push_front(temp);
            temp->parent->children.erase(temp->parentit);
            temp->parent->rank--;
            temp2=temp->parent;
            temp->parent=NULL;
            temp=temp2;
        }
        else if(temp->loser==0)     // else doing nothing just marking this node , because one of its child has been cut 
        {
            temp->loser=1;
            break;
        }
    }

    return;
}
vertex* extractfibmin(list<fibheap*> &l1,list<fibheap*> &l2 )    // deletes the min entry from l1 and puts its children into l2 and then we later call the function to merger l1 and l2 
{
    int min=(*(l1.begin()))->node->dist;
    auto minit=l1.begin();
    for(auto it = l1.begin();it!=l1.end();it++)
    {
        if(min>(*it)->node->dist)
        {
            minit=it;
            min=(*minit)->node->dist;
        }
        else if(min==(*it)->node->dist)
        {
            if((*it)->node->val<(*minit)->node->val)
            {
                minit=it;
                min=(*minit)->node->dist;
            }
        }
    }
    fibheap* temp=(*minit);
    for(auto it=temp->children.begin();it!=temp->children.end();it++)          //putting all the children of the min node into a seperate list which will later be joined and cleanup will be performed
    {
        (*it)->parent=NULL;
        l2.push_front((*it));
    }
    l1.erase(minit);    // erasing the entry of the minimum node from the original list 
    return (temp->node);    // returning a pointer to the min node 
}
void cleanup(list<fibheap*> &l1)
{
    unordered_map<int,fibheap*> fibmap;
    fibheap* temp;
    fibheap* temp2;
    while(l1.empty()!=1)
    {
        auto it1=l1.begin();
        if(fibmap.count((*it1)->rank)==0)           // if no tree of the given rank already exists in our hash map
        {
            fibmap[(*it1)->rank]=(*it1);            // then simply add the pointer to this tree to our map
            l1.pop_front();
        }
        else if(fibmap.count((*it1)->rank)==1)      // if there already exists a tree with the same rank then we will replace after combining 
        {
            temp=fibmap[(*it1)->rank];              
            fibmap.erase((*it1)->rank);             // removing the node at the current rank in our map and then combining and later reinserting at a different location in our map
            temp2=(*it1);
            l1.pop_front();

            if(temp->node->dist<temp2->node->dist)          // now seeing how to combine , i.e which node to make whos child/parent
            {
                temp->rank++;
                temp->children.push_front(temp2);
                temp2->parent=temp;
                temp2->parentit=temp->children.begin();
                if(fibmap.count(temp->rank)==0)
                {
                    fibmap[temp->rank]=temp;
                }
                else if(fibmap.count(temp->rank)==1)
                {
                    l1.push_front(temp);
                }
                
            }
            else if(temp->node->dist>temp2->node->dist)     
            {
                temp2->rank++;
                temp2->children.push_front(temp);
                temp->parent=temp2;
                temp->parentit=temp2->children.begin();
                if(fibmap.count(temp2->rank)==0)
                {
                    fibmap[temp2->rank]=temp2;
                }
                else if(fibmap.count(temp2->rank)==1)
                {
                    l1.push_front(temp2);
                }
                
            }
            else if(temp->node->dist==temp2->node->dist)        // if the distances are same then seeing index to ensure lexicographic ordering
            {
                if(temp->node->val<temp2->node->val)    
                {
                    temp->rank++;
                    temp->children.push_front(temp2);
                    temp2->parent=temp;
                    temp2->parentit=temp->children.begin();
                    if(fibmap.count(temp->rank)==0)
                    {
                        fibmap[temp->rank]=temp;
                    }
                    else if(fibmap.count(temp->rank)==1)
                    {
                        l1.push_front(temp);
                    }
                    
                }
                else if(temp->node->val>temp2->node->val)
                {
                    temp2->rank++;
                    temp2->children.push_front(temp);
                    temp->parent=temp2;
                    temp->parentit=temp2->children.begin();
                    if(fibmap.count(temp2->rank)==0)
                    {
                        fibmap[temp2->rank]=temp2;
                    }
                    else if(fibmap.count(temp2->rank)==1)
                    {
                        l1.push_front(temp2);
                    }

                }
            }
        }
    }
    l1.clear();

    for(auto it=fibmap.begin();it!=fibmap.end();it++)       // inserting elements from our map back to the original list 
    {
        l1.push_front(it->second);
    }
     
}

void printfibtree(fibheap* root)        // just used for testing purposes to see if the heap was working correctly in the backend 
{
    printf("%d ",root->node->dist);
    for(auto it=root->children.begin();it!=root->children.end();it++)
    {
        
        printfibtree((*it));
    }
}



void dijkstrafib(vertex v[],int s,int sizev)
{

    fibheap *h= new fibheap[sizev];
    list <fibheap*> original;
    list<fibheap*> secondary;
    original.clear();
    secondary.clear();
    int source=s-1;
    v[source].dist=0;


    for(int i=0;i<sizev;i++)
    {
        h[i].parent=NULL;
        h[i].node=&v[i];
        v[i].fibnode=&h[i];
        secondary.push_back(&h[i]);
        joinfibheap(original,secondary);
        secondary.clear();
    }

    secondary.clear();    
    
    vertex* temp;

    while(original.empty()!=1)
    {
        secondary.clear();

        temp=extractfibmin(original,secondary);
        joinfibheap(original,secondary);
        cleanup(original);

        for(int i=0;i<temp->ctr;i++)
        {
            if((temp->ed[i])->tail==temp&&(temp->ed[i])->head->visi==0)
            {
                ((temp->ed[i])->head)->dist=min(((temp->ed[i])->head)->dist,(((temp->ed[i])->tail)->dist)+(temp->ed[i]->weight));

                decreasefibkey(((temp->ed[i])->head),original); //Starting from updated distance to decrease key
            }

        }

        

    }
    for(int i=0;i<sizev;i++)
    {
        if(v[i].dist!=999999)
        {
            printf("%d ",v[i].dist-(v[source].funch)+v[i].funch);
        }
        else
        {
            printf("%d ",v[i].dist);
        }
    }
    printf("\n");
}


void dijkstraundirfib(vertex v[],int s,int sizev)
{

    fibheap *h= new fibheap[sizev];
    list <fibheap*> original;
    list<fibheap*> secondary;
    original.clear();
    secondary.clear();
    int source=s-1;
    v[source].dist=0;


    for(int i=0;i<sizev;i++)
    {
        h[i].parent=NULL;
        h[i].node=&v[i];
        v[i].fibnode=&h[i];
        secondary.push_back(&h[i]);
        joinfibheap(original,secondary);
        secondary.clear();
    }

    secondary.clear();    
    
    vertex* temp;  
    

    while(original.empty()!=1)
    {
        secondary.clear();
        temp=extractfibmin(original,secondary);
        joinfibheap(original,secondary);
        cleanup(original);

        for(int i=0;i<temp->ctr;i++)
        {

            if((temp->ed[i])->tail==temp&&(temp->ed[i])->head->visi==0)
            {
                ((temp->ed[i])->head)->dist=min(((temp->ed[i])->head)->dist,(((temp->ed[i])->tail)->dist)+(temp->ed[i]->weight));
                decreasefibkey(((temp->ed[i])->head),original);  //Starting from updated distance to percolate up
            }
            else if((temp->ed[i])->head==temp&&(temp->ed[i])->tail->visi==0)
            {
                ((temp->ed[i])->tail)->dist=min(((temp->ed[i])->tail)->dist,(((temp->ed[i])->head)->dist)+(temp->ed[i]->weight));
                decreasefibkey(((temp->ed[i])->tail),original);  //Starting from updated distance to percolate up
            }
        }
    }
    
    for(int i=0;i<sizev;i++)
    {
        printf("%d ",v[i].dist);
    }
    printf("\n");
}



// fibonacci heap stuff ends 

// reading the matrix
int flag69;
void mtolistundir(int n,vertex v[],edge e[],int &sizee)
{
    int i=0;
    sizee=0;
    for(i=0;i<n;i++)
    {
        v[i].val=i+1;
        v[i].ctr=0;
        v[i].visi=0;
        v[i].inci=-1;
        v[i].indeg=0;
        v[i].dist=999999;
        v[i].fintime=-1;
    }
    int temp2;
    edge temp3;
    for(i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&temp2);
            if(j<=i)
            {
                continue;
            }
            if(temp2<0)
            {
                flag69=1;
            }
            if(temp2!=999999)
            {
                e[sizee].tail=&v[i];
                e[sizee].head=&v[j];
                e[sizee].type=0;
                e[sizee].weight=temp2;
                v[i].ed[v[i].ctr++]=&e[sizee];

                v[j].ed[v[j].ctr++]=&e[sizee];
                v[j].indeg++;
                sizee++;
            }
        }
    }
}
void mtolist(int n,vertex v[],edge e[],int &sizee)
{
    int i=0;
    sizee=0;
    for(i=0;i<n;i++)
    {
        v[i].val=i+1;
        v[i].ctr=0;
        v[i].visi=0;
        v[i].inci=-1;
        v[i].indeg=0;
        v[i].dist=999999;
        v[i].fintime=-1;
    }
    int temp2;
    edge temp3;
    for(i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&temp2);
            if(i==j)
            {
                continue;
            }
            if(temp2<0)
            {
                flag69=1;
            }
            if(temp2!=999999)
            {
                e[sizee].tail=&v[i];
                e[sizee].head=&v[j];
                e[sizee].type=0;
                e[sizee].weight=temp2;
                v[i].ed[v[i].ctr++]=&e[sizee];

                v[j].ed[v[j].ctr++]=&e[sizee];
                v[j].indeg++;
                sizee++;
            }
        }
    }

}

int main(int argc,char* argv[])
{
    int t;
    int k=0;

    int type;
    scanf("%d",&type);
    
    scanf("%d",&t);
    
    /*
    if(argc==2)
    {
    	if(atoi(argv[1])==1)
    	{
    		type=1;
    	}
    	else if(atoi(argv[1])==2)
    	{
    		type=2;
    	
    	}
    	else if(atoi(argv[1])==3)
    	{
    		type=3;
    	
    	}
    	else if(atoi(argv[1])==4)
    	{
    		type=4;
    	}
    
    }*/
    double time_taken[t];
    while(k<t)
    {
        int q,n,d,s;
        scanf("%d",&n);
        scanf("%d",&d);
        int sizee;
        vertex *v= new vertex[n];
        edge *e = new edge[n*n];
        flag69=0;
        if(type==1)
        {
            if(d==1)
            {
                int flag;
                mtolist(n,v,e,sizee);
                clock_t timetemp; 
                timetemp = clock();
                flag=belford(v,n,sizee);
                if(flag==-1)
                {
                    printf("-1\n");
            
                }
                else 
                {
                    for(int i=0;i<sizee;i++)
                    {
                        e[i].weight=e[i].weight+(e[i].tail->funch)-(e[i].head->funch);
                    }
                    for(int s=1;s<=n;s++)
                    {
                        for(int i=0;i<n;i++)
                        {
                            v[i].dist=999999;
                            v[i].visi=0;
                        }
                        dijkstraarray(v,s,n);
                    }
                }
                timetemp = clock() - timetemp; 
                time_taken[k] = ((double)timetemp)/CLOCKS_PER_SEC;

            }
            else
            {
                mtolistundir(n,v,e,sizee);
                clock_t timetemp; 
                timetemp = clock();
                if(flag69==1)
                {
                    printf("-1\n");
                }
                else 
                {
                    
                    for(int s=1;s<=n;s++)
                    {
                        for(int i=0;i<n;i++)
                        {
                            v[i].visi=0;
                            v[i].dist=999999;
                            
                        }
                        dijkstraundirarray(v,s,n);
                    }
                }
                timetemp = clock() - timetemp; 
                time_taken[k] = ((double)timetemp)/CLOCKS_PER_SEC;
            }
            
        }
        if(type==2)
        {
            if(d==1)
            {
                int flag;
                mtolist(n,v,e,sizee);
                clock_t timetemp; 
                timetemp = clock();
                flag=belford(v,n,sizee);
                if(flag==-1)
                {
                    printf("-1\n");
            
                }
                else 
                {
                    for(int i=0;i<sizee;i++)
                    {
                        e[i].weight=e[i].weight+(e[i].tail->funch)-(e[i].head->funch);
                    }
                    for(int s=1;s<=n;s++)
                    {
                        for(int i=0;i<n;i++)
                        {
                            v[i].dist=999999;
                            v[i].visi=0;
                        }
                        dijkstrabinary(v,s,n);
                    }
                }
                timetemp = clock() - timetemp; 
                time_taken[k] = ((double)timetemp)/CLOCKS_PER_SEC;

            }
            else
            {
                mtolistundir(n,v,e,sizee);
                clock_t timetemp; 
                timetemp = clock();
                if(flag69==1)
                {
                    printf("-1\n");
                }
                else 
                {
                    for(int s=1;s<=n;s++)
                    {
                        for(int i=0;i<n;i++)
                        {
                            v[i].dist=999999;
                            v[i].visi=0;
                        }
                        dijkstraundirbinary(v,s,n);
                    }
                }
                timetemp = clock() - timetemp; 
                time_taken[k] = ((double)timetemp)/CLOCKS_PER_SEC;
            }
        }
        if(type==3)
        {
            if(d==1)
            {
                int flag;
                mtolist(n,v,e,sizee);
                clock_t timetemp; 
                timetemp = clock();
                flag=belford(v,n,sizee);
                if(flag==-1)
                {
                    printf("-1\n");
            
                }
                else 
                {
                    for(int i=0;i<sizee;i++)
                    {
                        e[i].weight=e[i].weight+(e[i].tail->funch)-(e[i].head->funch);
                    }
                    for(int s=1;s<=n;s++)
                    {
                        for(int i=0;i<n;i++)
                        {
                            v[i].dist=999999;
                            v[i].visi=0;
                        }
                        dijkstrabinomial(v,s,n);
                    }
                }
                timetemp = clock() - timetemp; 
                time_taken[k] = ((double)timetemp)/CLOCKS_PER_SEC;

            }
            else
            {
                mtolistundir(n,v,e,sizee);
                clock_t timetemp; 
                timetemp = clock();
                if(flag69==1)
                {
                    printf("-1\n");
                }
                else 
                {
                    for(int s=1;s<=n;s++)
                    {
                        for(int i=0;i<n;i++)
                        {
                            v[i].dist=999999;
                            v[i].visi=0;
                        }
                        dijkstraundirbinomial(v,s,n);
                    }
                }
                timetemp = clock() - timetemp; 
                time_taken[k] = ((double)timetemp)/CLOCKS_PER_SEC;
            }
        }
        if(type==4)
        {
            if(d==1)
            {
                int flag;
                mtolist(n,v,e,sizee);
                clock_t timetemp; 
                timetemp = clock();
                flag=belford(v,n,sizee);
                if(flag==-1)
                {
                    printf("-1\n");
            
                }
                else 
                {
                    for(int i=0;i<sizee;i++)
                    {
                        e[i].weight=e[i].weight+(e[i].tail->funch)-(e[i].head->funch);
                    }
                    for(int s=1;s<=n;s++)
                    {
                        for(int i=0;i<n;i++)
                        {
                            v[i].dist=999999;
                            v[i].visi=0;
                        }
                        dijkstrafib(v,s,n);
                    }
                }
                timetemp = clock() - timetemp; 
                time_taken[k] = ((double)timetemp)/CLOCKS_PER_SEC;

            }
            else
            {
                mtolistundir(n,v,e,sizee);
                clock_t timetemp; 
                timetemp = clock();
                if(flag69==1)
                {
                    printf("-1\n");
                }
                else 
                {
                    
                    for(int s=1;s<=n;s++)
                    {
                        for(int i=0;i<n;i++)
                        {
                            v[i].dist=999999;
                            v[i].visi=0;
                        }
                        dijkstraundirfib(v,s,n);
                    }
                }
                timetemp = clock() - timetemp; 
                time_taken[k] = ((double)timetemp)/CLOCKS_PER_SEC;
                
            }
        }
        
        k++;
    }
    for(int i=0;i<t;i++)
    {
        printf("%lf ",time_taken[i]);
    }

    return 0;
}
