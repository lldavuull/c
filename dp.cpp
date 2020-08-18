#include<iostream>
#include <vector> 
using namespace std;

struct pipe_alloc{
  int* type;
  int residual;
  int* type_count;
  pipe_alloc(int r):type(),type_count(),residual(r){
    type=new int[5]{-1,-1,-1,-1,-1};
    type_count=new int[8]{0,0,0,0,0,0,0,0};
  }
  ~pipe_alloc(){
    delete []type;
    delete []type_count;
  }
};
typedef vector<pipe_alloc*> VECTOR_PIPE_ALLOC;

void record_alloc(int residual, int type, int layer, VECTOR_PIPE_ALLOC* Alloc){
  pipe_alloc* e=new pipe_alloc(residual);
  if(layer>0){
    for(int i=0;i<layer;i++){
      e->type[i]=(*Alloc).back()->type[i];
    }
  }
  e->type[layer]=type;

  for(int i=0;i<=layer;i++){
    e->type_count[e->type[i]]++;
  }
//   cout<<&e<<"\n";
  (*Alloc).push_back(e);
}

void find_available_alloc(int pipe, int cut[], int type, int layer,VECTOR_PIPE_ALLOC* Alloc){
  int residual;
  while(type<8){
    residual=pipe-cut[type];
    if(residual>0){
      record_alloc(residual,type,layer,Alloc);
      //continue to dfs
      if(residual>cut[7])
	find_available_alloc(residual,cut,type,layer+1,Alloc);
    }
    type++;
  }
}
//--------------//
int find_first_type(int* num, int* used){
  int type=0;
  while(type<8 & num[type]-used[type]<=0)
    type++;
  return type;
}

void align_to_type( int* num, int* used,int type,VECTOR_PIPE_ALLOC::iterator* iter){
//   cout<<"**iter:  "<<**iter<<"\n";
  if(type<8 & used[type]<num[type]){
    while((**iter)->type[0]!=type){
      (*iter)++;
    }
  }
}

void check_type_cout_less_than_empty(int* num, int type,int* used,VECTOR_PIPE_ALLOC::iterator* iter,VECTOR_PIPE_ALLOC* Alloc){
  //數量可行性檢查，若超過就itype++
  for(int i=type;i<8;i++){
    int residual=num[i]-used[i];
    while((**iter)->type_count[i]>residual && *iter<Alloc->end()){
      (*iter)++;
//       i=type;
//       cout<<"check type:";
//       for(int i=0;i<5;i++)
// 	cout<< (**iter)->type[i]<<",";
//       cout<<"\n";
    }
  }
}

void record(int* used,int type,VECTOR_PIPE_ALLOC::iterator* iter, VECTOR_PIPE_ALLOC* hand){
  (*hand).push_back(**iter);
  for(int i=type;i<8;i++){
    used[i]+=(**iter)->type_count[i];
  }
}
void put_into_pocket_if_best(VECTOR_PIPE_ALLOC* hand, VECTOR_PIPE_ALLOC* solution){
  VECTOR_PIPE_ALLOC::iterator iter;
  for(iter=hand->begin();iter<hand->end();iter++)
  {
    for(int i=0;i<8;i++)
      cout<< (*iter)->type_count[i]<<",";
    cout<<(*iter)->residual<<"\n";
  }
  cout<<"\n";
}

void backtracking(int* used,int type, VECTOR_PIPE_ALLOC* hand){
  //remove
  for(int i=type;i<8;i++){
    used[i]-=(*hand).back()->type_count[i];
  }
  (*hand).pop_back();
}

void WorldEnd(int pipe, int cut[], int* num, int* used,  VECTOR_PIPE_ALLOC::iterator iter, VECTOR_PIPE_ALLOC* Alloc, VECTOR_PIPE_ALLOC* hand, VECTOR_PIPE_ALLOC* solution){
//   cout<<*iter<<"\n";
  int type=find_first_type(num,used);
  align_to_type(num,used,type,&iter);
//   cout<<*itype<<"\n";
  while(type<8 &(*iter)->type[0]==type && iter<Alloc->end()){
    check_type_cout_less_than_empty(num,type,used,&iter,Alloc);
    if((*iter)->type[0]==type && iter<Alloc->end()){
      record(used,type,&iter,hand);

//       cout<<"\nused: ";
//       for(int i=0;i<8;i++)
// 	cout<<used[i]<<",";
//       cout<<"\n";
      put_into_pocket_if_best(hand,solution);
      WorldEnd(pipe, cut, num, used, iter, Alloc, hand, solution);
//       cout<<"end\n\n";
      backtracking(used,type,hand);
    }
//     if(type==2){
//       cout<<"record: ";
//       for(int i=0;i<5;i++)
// 	cout<< (*iter)->type[i]<<",";
//       cout<<"\n";
//     }
    iter++;
  }
//   itype=hand->begin();

//   for(int i=0;i<8;i++)
//     cout<< (*iter)->type_count[i]<<",";
//   cout<<(*iter)->residual<<"\n";
  
//   cout<<*itype<<"\n";
//   cout<<(*itype)->
}
//------------------//
int main(){
  int pipe=12192;
  int cut[8]={4417,4133,3824,3529,3109,2791,2523,2317};
  int num[8]={4,4,4,4,4,4,4,4};
  VECTOR_PIPE_ALLOC* Alloc;
  Alloc=new VECTOR_PIPE_ALLOC;
  VECTOR_PIPE_ALLOC::iterator iter;
  
  find_available_alloc(pipe,cut,0,0,Alloc);
//   cout<< (*Alloc).size()<<"...";
//   for(iter=Alloc->begin();iter<Alloc->end();iter++)
//   {
//     for(int i=0;i<8;i++)
//       cout<< (*iter)->type_count[i]<<",";
//     cout<<(*iter)->residual<<"\n";
//   }
  
  
  iter=Alloc->begin();
  
  
  
  while(iter<Alloc->end())
    if((*iter)->residual>cut[(*iter)->type[0]])
    {
      iter=Alloc->erase(iter);
    }
    else
    {
      iter++;
    }
//     else{
//       for(int i=0;i<5;i++)
// 	cout<< (*iter)->type[i]<<",";
//       cout<<(*iter)->residual<<"<"<<cut[(*iter)->type[0]]<<"\n";
//     }

  cout<< (*Alloc).size()<<"...\n";
  iter=Alloc->begin();
  VECTOR_PIPE_ALLOC::iterator itype;
  itype=iter;
  itype=itype+1;
//   cout<<(*itype)->residual;
//   cout<<(*iter)->residual;
  
  VECTOR_PIPE_ALLOC* hand;
  VECTOR_PIPE_ALLOC* solution;
  hand=new VECTOR_PIPE_ALLOC;
  solution=new VECTOR_PIPE_ALLOC;
  
  iter=Alloc->begin();
//   cout<<*iter<<"\n";
  int* used=new int[8]{0,0,0,0,0,0,0,0};
  WorldEnd(pipe, cut, num, used, iter, Alloc, hand, solution);
//   cout<< (*Alloc).size()<<"...\n";
}