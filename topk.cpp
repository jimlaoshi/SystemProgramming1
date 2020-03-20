#include "topk.h"
//https://stackoverflow.com/questions/31577866/c-convert-integer-to-binary-array
//SUNARTHSH METATROPHS INT SE ARRAY APO BITS
void int_to_bin_digit(unsigned int in, int count, int* out)
{
    /* assert: count <= sizeof(int)*CHAR_BIT */
    unsigned int mask = 1U << (count-1);
    int i;
    for (i = 0; i < count; i++) {
        out[i] = (in & mask) ? 1 : 0;
        in <<= 1;
    }
}

//sunarthsh swap periexomenou komvou
void swap_nodes_info(heapnode * node1, heapnode * node2){
  heapnode temp;
  temp.cat_name = node1->cat_name;
  temp.krousmata = node1->krousmata;
  node1->cat_name = node2->cat_name;
  node1->krousmata = node2->krousmata;
  node2->cat_name = temp.cat_name;
  node2->krousmata = temp.krousmata;
}


//SUNARTHSEIS MAXHEAP
maxBinaryHeap::maxBinaryHeap(){
  root = NULL;
  number_of_nodes = 0;
}

maxBinaryHeap::maxBinaryHeap(int total, std::string cat){
  category = cat;
  root = NULL;
  number_of_nodes = 0;
  maxsize = total;
}

//destructor. TO DELETE STH RIZA LEITOURGEI SE OLO TO HEAP LOGW C++
maxBinaryHeap::~maxBinaryHeap(){
  delete root;
}

//gemizei to heap apo ena bbst
void maxBinaryHeap::insert_krousma(record * rec){
  if(root == NULL){ //prwto stoixeio sto heap
    root = new heapnode();
    if(category == "disease"){ //an eimaste gia topk_diseases
      root->cat_name = rec->get_diseaseID();
      root->krousmata += 1;
      return;
    }
    if(category == "country"){ //an eimaste gia topk_countries
      root->cat_name = rec->get_country();
      root->krousmata += 1;
      return;
    }
    number_of_nodes++; //anebainei o arithmos komvwn tou heap
  }
  else{ //yparxei riza
    //ftiaxnw bitpath. Kanw ton arithmo ths theshs binary kai 1 shmainei deksia, 0 aristera
    int * path = new int[maxsize]; //megistos arithmos bits gia to path to last
    int_to_bin_digit(number_of_nodes+1, maxsize, path); //twra to outta exei to bitpath poy prepei na akoloythhsw gia ton last kovmo
    int path_index = 0; //Tha broume thesh most significant bit.prepei na agnohsoume ton prwto asso giati einai h riza
    for(unsigned int i=0; i<maxsize; i++){
      if(path[i] == 1){
        path_index = i+1;
        break;
      }
    }//telos for most significant
    heapnode * currnode = root;
    while(currnode != NULL){

    }
    delete[] path;
  }//telos else yparxei riza
}//telos sunarthshs


//SUNARTHSEIS HEAPNODE
//empty constr
heapnode::heapnode(){
  left = NULL;
  right = NULL;
  parent = NULL;
  krousmata = 0;
}

//constructor gia klhsh apo gonio
heapnode::heapnode(heapnode * par){
  left = NULL;
  right = NULL;
  parent = par;
  krousmata = 0;
}

//destructor. DOULEUEI ANADROMIKA LOGW DELETE POY STH C++ KALEI TOUS DESTRUCTORS
heapnode::~heapnode(){
  delete left;
  delete right;
  delete parent; //isws de xreiastei
}



//SUNARTHSEIS SIMPLEHT
simple_cd_HT::simple_cd_HT(int sz, std::string ctg){
  categ_name = ctg;
  size = sz;
  table = new simple_cd_HT_node *[size]; //ena dunamiko array apo deiktes se ht_nodes (buckets)
  for(unsigned int i=0; i<size; i++){
    table[i] = NULL; //arxika adeio olo
  }
}

//destructor
simple_cd_HT::~simple_cd_HT(){
  for(unsigned int i=0; i<size; i++)
    if(table[i] != NULL)
      delete table[i];
  delete[] table; //katastrofh tou pinaka apo chain nodes. To kathe chain node exei ton diko tou destructor kai kanei toso delete this oso kai delete next.
}

//constructor simple node basei record
int simple_cd_HT::insert_krousma(record * rec){
  if(categ_name == "disease"){
    unsigned hval = hash_str(rec->get_diseaseID()); //hasharei to disease
    hval = hval % size; //gia na pame sth swsth thesh pinaka

    if(table[hval] == NULL){ //ean den yparxei alusida ekei, th ftiaxnoyme
      table[hval] = new simple_cd_HT_node();
      table[hval]->krousmata += 1;
      table[hval]->cd_name = rec->get_diseaseID();
      return 0;
    }
    else{ //yparxei alusida, pame sto telos ENW KOITAZOUME OTI DEN YPARXEI IDIO ID
      simple_cd_HT_node * currptr = table[hval];
      while(currptr->next != NULL){ //paei sto teleutaio
        if(currptr->cd_name == rec->get_diseaseID()){ //brethhke h idia astheneia. aplws aukshsh krousmatwn k telos
          currptr->krousmata += 1;
          return 0;
        }
        currptr = currptr->next ;
      }//telos while buckets
      if(currptr->cd_name == rec->get_diseaseID()){ //brethhke h idia astheneia. aplws aukshsh krousmatwn k telos
        currptr->krousmata += 1;
        return 0;
      }
      currptr->next = new simple_cd_HT_node();
      currptr->krousmata += 1;
      currptr->cd_name = rec->get_diseaseID();
      return 0; //ola ok
    }//telos else alusidas
  }//telos if disease
  else if(categ_name == "country"){
    unsigned hval = hash_str(rec->get_country()); //hasharei to disease
    hval = hval % size; //gia na pame sth swsth thesh pinaka

    if(table[hval] == NULL){ //ean den yparxei alusida ekei, th ftiaxnoyme
      table[hval] = new simple_cd_HT_node();
      table[hval]->krousmata += 1;
      table[hval]->cd_name = rec->get_country();
      return 0;
    }
    else{ //yparxei alusida, pame sto telos ENW KOITAZOUME OTI DEN YPARXEI IDIO ID
      simple_cd_HT_node * currptr = table[hval];
      while(currptr->next != NULL){ //paei sto teleutaio
        if(currptr->cd_name == rec->get_country()){ //brethhke h idia astheneia. aplws aukshsh krousmatwn k telos
          currptr->krousmata += 1;
          return 0;
        }
        currptr = currptr->next ;
      }//telos while buckets
      if(currptr->cd_name == rec->get_country()){ //brethhke h idia astheneia. aplws aukshsh krousmatwn k telos
        currptr->krousmata += 1;
        return 0;
      }
      currptr->next = new simple_cd_HT_node();
      currptr->krousmata += 1;
      currptr->cd_name = rec->get_country();
      return 0; //ola ok
    }//telos else alusidas
  }//telos else if country
  return 0;
}

//h mageia ths c++ diagrafei olo to bucketlist gt h delete kalei destructors
simple_cd_HT_node::~simple_cd_HT_node(){
  delete next;
}