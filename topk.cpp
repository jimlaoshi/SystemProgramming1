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

maxBinaryHeap::maxBinaryHeap(int total){
  root = NULL;
  number_of_nodes = 0;
  maxsize = total;
}

//destructor. TO DELETE STH RIZA LEITOURGEI SE OLO TO HEAP LOGW C++
maxBinaryHeap::~maxBinaryHeap(){
  delete root;
}

//vazei sto heap ena zeugos xwra/astheneia - arithmo krousmatwn
void maxBinaryHeap::insert(std::string cntdis, int numofkrousmata){
  if(root == NULL){ //prwto stoixeio sto heap
    root = new heapnode();
    root->cat_name = cntdis;
    root->krousmata = numofkrousmata;
    number_of_nodes++; //anebainei o arithmos komvwn tou heap
    return;
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
    heapnode * last = NULL;
    bool insert_done = false;
    heapnode * currnode = root;
    while(true){ //arxizei while mexri na ginei insert
      if(path[path_index] == 1){ //1 shmainei pame deksia
        if(currnode->right == NULL){ //ekei tha einai o teleutaios komvos
          currnode->right = new heapnode();
          currnode->right->cat_name = cntdis;
          currnode->right->krousmata = numofkrousmata;
          currnode->right->parent = currnode;
          last = currnode->right;
          number_of_nodes++;
          break;
        }//telos if null deksi
        else{
          currnode = currnode->right;
          path_index++;
        }//telos else deksi not null
      }//telos if deksia
      else{ //0 shmainei pame aristera
        if(currnode->left == NULL){ //ekei tha ienai o teleutaios komvos
          currnode->left = new heapnode();
          currnode->left->cat_name = cntdis;
          currnode->left->krousmata = numofkrousmata;
          currnode->left->parent = currnode;
          last = currnode->left;
          number_of_nodes++;
          break;
        }//telos if null aristero
        else{
          currnode = currnode->left;
          path_index++;
        }//telos else aristero not null
      }//telos else aristera
    }//telos while gia insert
    delete[] path;
    //ARXIZEI TO HEAPIFY == SWIMMING UP
    currnode = last; //arxizei twra swimming apo katw pros panw
    while(true){
      if(currnode->parent == NULL)
        break; //ftasame riza
      
    }//telos while gia swimming up
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

//gia gemisma heap
void simple_cd_HT::populate_heap(maxBinaryHeap * heaptr){
  for(unsigned int i=0; i<size; i++){
    if(table[i] == NULL)
      continue; //adeio bucket
    else{
      simple_cd_HT_node * currptr = table[i];
      while(currptr!= NULL){ //paei sto teleutaio. ENDEIKTIKH EKTYPWSH. MONO MERIKA PEDIA ALLA MPORW KAI OLA
        heaptr->insert(currptr->cd_name, currptr->krousmata);
        currptr = currptr->next ;
      }//telos while gia orizontia lista
    }//telos else
  }//telos for
}//telos sunarthshs

//h mageia ths c++ diagrafei olo to bucketlist gt h delete kalei destructors
simple_cd_HT_node::~simple_cd_HT_node(){
  delete next;
}
