#include "cdHashTable.h"

cdHashTable::cdHashTable(int sze, int bucketsize){
  size = sze;
  table = new chain_node *[size]; //ena dunamiko array apo deiktes se chain_node (buckets)
  for(unsigned int i=0; i<size; i++){
    table[i] = NULL; //arxika adeio olo
  }
  bucksize = bucketsize;
}

cdHashTable::~cdHashTable(){
  for(unsigned int i=0; i<size; i++)
    if(table[i] != NULL)
      delete table[i];
  delete[] table; //katastrofh tou pinaka apo chain nodes. To kathe chain node exei ton diko tou destructor kai kanei toso delete this oso kai delete next.
  //h c++ frontizei kai ekshgw parakatw pws

}

//leitourgei kai gia disease k gia country
void cdHashTable::recordPatientExit(std::string disease_country, std::string status){
  unsigned hval = hash_str(disease_country); //hasharei to diseaseID
  hval = hval % size; //gia na pame sth swsth thesh pinaka

  if(table[hval] == NULL){ //Auth h periptwsh de tha ginei pote sthn askhsh
    std::cout << "Den yparxei h arrwstia/xwra (akoma)\n";
    return;
  }
  else{
    chain_node * currptr = table[hval];
    while(currptr!= NULL){ //to psaxnei dieksodika wste na enhmerwthei o curr deikths
      block_entry * buroku = currptr->block;
      for(unsigned int i=0; i< currptr->block_size; i++){
        if(buroku[i].dis_name_ptr == NULL)
          continue;
        if(*(buroku[i].dis_name_ptr) == disease_country){
          if(status == "increase")
            buroku[i].currval += 1; //ksanampainei nosokomeio, auksanetai o metrhths kai telos
          if(status == "decrease")
            buroku[i].currval -= 1; //phre eksithrio, meiwnetai o metrhths kai telos
          return;
        }
      }//telos for gia block
      currptr = currptr->next ;
    }//telos while gia orizontia lista

  }//telos else
  std::cout << "De bre8hke h arrwstia/xwra\n";
  return;
}

//gia to globalDiseaseStats XWRIS orismata dates
void cdHashTable::total_recs_per_cat(){
  if(true){ //pairnei kenh sumvoloseira an den oristhke. kanei th genikh periptwsh gia kathe iwsh
    int tototal =0;
    for(unsigned int i=0; i<size; i++){
      if(table[i] == NULL) //kenh alusida
        continue;
      else{
        chain_node * currptr = table[i];
        block_entry * buroku = NULL;
        while(currptr!= NULL){ //paei sto teleutaio. ENDEIKTIKH EKTYPWSH.
          buroku = currptr->block;
          for(unsigned int j=0; j<currptr->block_size; j++){
            if(buroku[j].dis_name_ptr == NULL) //no entry edw
              continue;
            else{
              std::cout << *(buroku[j].dis_name_ptr) << " " << buroku[j].totalval << "\n";
              tototal += buroku[j].totalval;
            }
          }//telos for gia block
          currptr = currptr->next ;
        }//telos while gia orizontia lista
      }//telos else kenhs alusidas
    }//telos for gia kathe alusida
    //std::cout << "A total of " << tototal << " patients recorded.\n";
  }//telos if genikh periptwsh

}//telos sunarthshs

//gia to globalDiseaseStats ME orismata date1, date2
void cdHashTable::total_recs_per_cat(std::string date1, std::string date2){
    int tototal=0;
    for(unsigned int i=0; i<size; i++){
      if(table[i] == NULL) //kenh alusida
        continue;
      else{
        chain_node * currptr = table[i];
        block_entry * buroku = NULL;
        while(currptr!= NULL){ //paei sto teleutaio. ENDEIKTIKH EKTYPWSH. MONO MERIKA PEDIA ALLA MPORW KAI OLA
          buroku = currptr->block;
          for(unsigned int j=0; j<currptr->block_size; j++){
            if(buroku[j].dis_name_ptr == NULL) //no entry edw
              continue;
            else{
              //EDW GINETAI H DOULITSA ME TO DENDRO
              search_containter querycontainer(buroku[j].totalval); //to megisto plhthos eggrafwn einai o sunolikos arithmos eggrafwn auths ths atheneias/xwras
              //twra o container exei oles tis eggrafes ths astheneias/xwras me entrydate <= date2. H parakatw entolh ftiaxnei kai thn allh proypothesh
              buroku[j].tree_ptr->collect_dated_reclists(buroku[j].tree_ptr, date2, &querycontainer); //o container exei tis eggrafes gia authn thn astheneia/xwra me entrydate <= Date2. Ekmetalleuetai th dendrikh domh gia kalyterh polyplokothta
              int number_to_present = querycontainer.count_exit_limit(date1);
              std::cout << *(buroku[j].dis_name_ptr) << " " << number_to_present << "\n";
              tototal += number_to_present;
            }
          }//telos for gia block
          currptr = currptr->next ;
        }//telos while gia orizontia lista
      }//telos else kenhs alusidas
    }//telos for gia kathe alusida
  //telos if genikh periptwsh
  //std::cout << "A total of " << tototal << " patients recorded within dates provided.\n";
}//telos sunarthshs


//dikh moy ektypwsh
void cdHashTable::print_contents(){
  for(unsigned int i=0; i<size; i++){
    std::cout << "anoigw thn " << i << " thesh tou pinaka\n";
    if(table[i] == NULL) //kenh alusida
      continue;
    else{
      chain_node * currptr = table[i];
      int blockorder =1;
      while(currptr!= NULL){ //paei sto teleutaio. ENDEIKTIKH EKTYPWSH. MONO MERIKA PEDIA ALLA MPORW KAI OLA
        std::cout << "\t"<< "koitazw to block " << blockorder << "\n\t\t";
        currptr->print_contents();
        std::cout << "\n\n";
        currptr = currptr->next ;
        blockorder++;
      }//telos while gia orizontia lista
    }//telos else
  }//telos for gia kathe alusida

}

//DISEASE
//derived parametrized constructor
diseaseHashTable::diseaseHashTable(int sze, int bucketsize) : cdHashTable(sze, bucketsize){
}

//h virtual gia disease
int diseaseHashTable::insert_record(record* rec){
  unsigned hval = hash_str(rec->get_diseaseID()); //hasharei to diseaseID
  hval = hval % size; //gia na pame sth swsth thesh pinaka

  if(table[hval] == NULL){ //ean den yparxei alusida ekei, th ftiaxnoyme
    table[hval] = new chain_node(bucksize);
    table[hval]->insert_record(rec, rec->get_diseaseID());
    return 0;
  }
  else{
    chain_node * currptr = table[hval];
    bool done = false;
    while(!done){ //prospathei na to valei se kapoio ths alusidas. to kathena koitaei ton pinaka tou
      done = currptr->insert_record(rec, rec->get_diseaseID());
      if((done==false)&&(currptr->next == NULL)){ //an den exei kataferei na th valei kai den exoume epomeno komvo, ftiaxnume k paei ekei.
        currptr->next = new chain_node(bucksize);
        currptr->next->insert_record(rec, rec->get_diseaseID());
        return 0;
      }//telos if
      currptr = currptr->next ;
    }//telos while done eisagwghs
  }//telos else

  return 0;
}
//gia to omwnumo erwthma
void diseaseHashTable::numCurrentPatients(std::string disease){
  if(disease == ""){ //pairnei kenh sumvoloseira an den oristhke. kanei th genikh periptwsh gia kathe iwsh
    int curtotal =0;
    for(unsigned int i=0; i<size; i++){
      if(table[i] == NULL) //kenh alusida
        continue;
      else{
        chain_node * currptr = table[i];
        block_entry * buroku = NULL;
        while(currptr!= NULL){ //paei sto teleutaio. ENDEIKTIKH EKTYPWSH. MONO MERIKA PEDIA ALLA MPORW KAI OLA
          buroku = currptr->block;
          for(unsigned int j=0; j<currptr->block_size; j++){
            if(buroku[j].dis_name_ptr == NULL) //no entry edw
              continue;
            else{
              std::cout << *(buroku[j].dis_name_ptr) << " " << buroku[j].currval << "\n";
              curtotal += buroku[j].currval ;
            }
          }//telos for gia block
          currptr = currptr->next ;
        }//telos while gia orizontia lista
      }//telos else kenhs alusidas
    }//telos for gia kathe alusida
    //std::cout << "A total of " << curtotal << " patients still in hospital\n";
  }//telos if genikh periptwsh
  else{
    unsigned hv = hash_str(disease); //hasharei to onoma ths
    hv = hv % size; //gia thesh pinaka
    if(table[hv] == NULL){  //kenh alusida
      //std::cout << "Disease specified does not exist.\n";
      std::cout << disease << " " << 0 << "\n";
      return;
    }
    else{ //h alusida den ein adeia
      chain_node * currptr = table[hv];
      block_entry * buroku = NULL;
      while(currptr!= NULL){ //paei sto teleutaio. ENDEIKTIKH EKTYPWSH. MONO MERIKA PEDIA ALLA MPORW KAI OLA
        buroku = currptr->block;
        for(unsigned int j=0; j<currptr->block_size; j++){
          if(buroku[j].dis_name_ptr == NULL) //no entry edw
            continue;
          if(*(buroku[j].dis_name_ptr) == disease){
            std::cout << *(buroku[j].dis_name_ptr) << " " <<buroku[j].currval << "\n";
            return;
          }
        }//telos for gia block
        currptr = currptr->next ;
      }//telos while gia orizontia lista
    }//telos else kenhs alusidas
    std::cout << disease << " " << 0 << "\n";
  }//telos else periptwshs poy exoume orisma disease
}//telos sunarthshs

//gia to diseaseFrequency xwris country
void diseaseHashTable::total_recs_for_cat(std::string diseasename, std::string date1, std::string date2){
  unsigned hval = hash_str(diseasename); //hasharei to diseaseID
  hval = hval % size; //gia na pame sth swsth thesh pinaka

  if(table[hval] == NULL){ //Auth h periptwsh de tha ginei pote sthn askhsh
    std::cout <<  diseasename << " " << 0 << "\n";
    return;
  }
  else{
    chain_node * currptr = table[hval];
    while(currptr!= NULL){ //to psaxnei dieksodika wste na brethei h astheneia
      block_entry * buroku = currptr->block;
      for(unsigned int i=0; i< currptr->block_size; i++){
        if(buroku[i].dis_name_ptr == NULL)
          continue;
        if(*(buroku[i].dis_name_ptr) == diseasename){
          //EDW GINETAI H DOULITSA ME TO DENDRO
          search_containter querycontainer(buroku[i].totalval); //to megisto plhthos eggrafwn einai o sunolikos arithmos eggrafwn auths ths atheneias/xwras
          //twra o container exei oles tis eggrafes ths astheneias/xwras me entrydate <= date2. H parakatw entolh ftiaxnei kai thn allh proypothesh
          buroku[i].tree_ptr->collect_dated_reclists(buroku[i].tree_ptr, date2, &querycontainer); //o container exei tis eggrafes gia authn thn astheneia/xwra me entrydate <= Date2. Ekmetalleuetai th dendrikh domh gia kalyterh polyplokothta
          int number_to_present = querycontainer.count_exit_limit(date1);
          std::cout << *(buroku[i].dis_name_ptr) << " " << number_to_present << "\n";
          return;
        }
      }//telos for gia block
      currptr = currptr->next ;
    }//telos while gia orizontia lista

  }//telos else
  std::cout << diseasename << " " << 0 << "\n";
  return;
}

//gia to diseaseFrequency ME country
void diseaseHashTable::total_recs_for_cat(std::string diseasename, std::string date1, std::string date2, std::string country){
  unsigned hval = hash_str(diseasename); //hasharei to diseaseID
  hval = hval % size; //gia na pame sth swsth thesh pinaka

  if(table[hval] == NULL){ //Auth h periptwsh de tha ginei pote sthn askhsh
    std::cout << diseasename << " " << 0 << "\n";
    return;
  }
  else{
    chain_node * currptr = table[hval];
    while(currptr!= NULL){ //to psaxnei dieksodika wste na brethei h astheneia
      block_entry * buroku = currptr->block;
      for(unsigned int i=0; i< currptr->block_size; i++){
        if(buroku[i].dis_name_ptr == NULL)
          continue;
        if(*(buroku[i].dis_name_ptr) == diseasename){
          //EDW GINETAI H DOULITSA ME TO DENDRO
          search_containter querycontainer(buroku[i].totalval); //to megisto plhthos eggrafwn einai o sunolikos arithmos eggrafwn auths ths atheneias/xwras
          //twra o container exei oles tis eggrafes ths astheneias/xwras me entrydate <= date2. H parakatw entolh ftiaxnei kai thn allh proypothesh
          buroku[i].tree_ptr->collect_dated_reclists(buroku[i].tree_ptr, date2, &querycontainer); //o container exei tis eggrafes gia authn thn astheneia/xwra me entrydate <= Date2. Ekmetalleuetai th dendrikh domh gia kalyterh polyplokothta
          int number_to_present = querycontainer.count_exit_limit(date1, country);
          std::cout << *(buroku[i].dis_name_ptr) << " " << number_to_present << "\n";
          return;
        }
      }//telos for gia block
      currptr = currptr->next ;
    }//telos while gia orizontia lista

  }//telos else
  std::cout <<  diseasename << " " << 0 << "\n";
  return;
}

//gia topk XWRIS date1 date2
void diseaseHashTable::topk_countries(int k, std::string disease){
  unsigned hval = hash_str(disease); //hasharei to country
  hval = hval % size; //gia na pame sth swsth thesh pinaka
  if(table[hval] == NULL){ //ean den yparxei alusida ekei, den yparxei h xwra
    std::cout << "Disease specified does not exist (yet).\n";
    return;
  }
  else{ //h xwra yparxei
    chain_node * currptr = table[hval];
    while(currptr!= NULL){ //to psaxnei dieksodika wste na brethei h xwra
      block_entry * buroku = currptr->block;
      for(unsigned int i=0; i< currptr->block_size; i++){
        if(buroku[i].dis_name_ptr == NULL)
          continue;
        if(*(buroku[i].dis_name_ptr) == disease){
          //extract eggrafes apo dentro
          simple_cd_HT simplcntht(buroku[i].totalval, "country"); //DES README gia topk
          buroku[i].tree_ptr->populate_simpleht(&simplcntht); //twra oi komvoi tou simple ht exoun kathe astheneia sth xwra kai ton arithmo krousmatwn ths
          maxBinaryHeap mheap(buroku[i].totalval); //ena maxheap gia krousmata xwrwn
          //gemizei o swros apo to dentro twn krousmatwn auths ths astheneias
          simplcntht.populate_heap(&mheap);
          //std::cout << "Top " << k << " countries for " << disease << " :\n";
          for(unsigned int ka=0; ka<k; ka++){
            if(mheap.root == NULL){
              //std::cout << "-\n"; //de ginontai alla extractions.
              continue;
            }
            heapnode ophelia(mheap.extract() ); //eksagwgh rizas apo swro kai diathrhsh
            std::cout << ophelia.cat_name << " " << ophelia.krousmata << "\n";
          }
          return;
        }
      }//telos for gia block
      currptr = currptr->next ;
    }//telos while gia orizontia lista

  }//telos else
  std::cout << "Disease specified does not exist (yet).\n";
}//telos sunarthshs


//gia topk ME date1 date2
void diseaseHashTable::topk_countries(int k, std::string disease, std::string date1, std::string date2){
  unsigned hval = hash_str(disease); //hasharei to country
  hval = hval % size; //gia na pame sth swsth thesh pinaka
  if(table[hval] == NULL){ //ean den yparxei alusida ekei, den yparxei h xwra
    std::cout << "Disease specified does not exist (yet).\n";
    return;
  }
  else{ //h xwra yparxei
    chain_node * currptr = table[hval];
    while(currptr!= NULL){ //to psaxnei dieksodika wste na brethei h xwra
      block_entry * buroku = currptr->block;
      for(unsigned int i=0; i< currptr->block_size; i++){
        if(buroku[i].dis_name_ptr == NULL)
          continue;
        if(*(buroku[i].dis_name_ptr) == disease){
          //extract eggrafes apo dentro
          simple_cd_HT simplcntht(buroku[i].totalval, "country"); //DES README gia topk
          search_containter querycontainer(buroku[i].totalval); //to megisto plhthos eggrafwn einai o sunolikos arithmos eggrafwn auths ths atheneias/xwras
          //me thn apo katw entolh o container exei oles tis eggrafes ths astheneias/xwras me entrydate <= date2.
          buroku[i].tree_ptr->collect_dated_reclists(buroku[i].tree_ptr, date2, &querycontainer); //o container exei tis eggrafes gia authn thn astheneia/xwra me entrydate <= Date2. Ekmetalleuetai th dendrikh domh gia kalyterh polyplokothta
          //twra gia date 1:disqualify dates passing date2 test but not date1 and pass them to simpleht
          querycontainer.populate_simpleht(&simplcntht, date1); //twra oi komvoi tou simple ht exoun kathe astheneia sth xwra kai ton arithmo krousmatwn ths kai me ta swsta dates
          maxBinaryHeap mheap(buroku[i].totalval); //ena maxheap gia krousmata xwrwn
          //gemizei o swros apo to dentro twn krousmatwn auths ths arrwstias
          simplcntht.populate_heap(&mheap);
          //std::cout << "Top " << k << " countries for " << disease << " for dates provided:\n";
          for(unsigned int ka=0; ka<k; ka++){
            if(mheap.root == NULL){
              //std::cout << "-\n"; //de ginontai alla extractions.
              continue;
            }
            heapnode ophelia(mheap.extract() ); //eksagwgh rizas apo swro kai diathrhsh
            std::cout << ophelia.cat_name << " " << ophelia.krousmata << "\n";
          }
          return;
        }
      }//telos for gia block
      currptr = currptr->next ;
    }//telos while gia orizontia lista

  }//telos else
  std::cout << "Disease specified does not exist (yet).\n";
}//telos sunarthshs



//COUNTRY
//derived parametrized constructor
countryHashTable::countryHashTable(int sze, int bucketsize) : cdHashTable(sze, bucketsize){
}

//h virtual gia country
int countryHashTable::insert_record(record* rec){
  unsigned hval = hash_str(rec->get_country()); //hasharei to countr
  hval = hval % size; //gia na pame sth swsth thesh pinaka

  if(table[hval] == NULL){ //ean den yparxei alusida ekei, th ftiaxnoyme
    table[hval] = new chain_node(bucksize);
    table[hval]->insert_record(rec, rec->get_country());
    return 0;
  }
  else{
    chain_node * currptr = table[hval];
    bool done = false;
    while(!done){ //prospathei na to valei se kapoio ths alusidas. to kathena koitaei ton pinaka tou
      done = currptr->insert_record(rec, rec->get_country());
      if((done==false)&&(currptr->next == NULL)){ //an den exei kataferei na th valei kai den exoume epomeno komvo, ftiaxnume k paei ekei.
        currptr->next = new chain_node(bucksize);
        currptr->next->insert_record(rec, rec->get_country());
        return 0;
      }//telos if
      currptr = currptr->next ;
    }//telos while done eisagwghs
  }//telos else

  return 0;
}

//gia to antistoixo erwthma XWRIS date1 date2
void countryHashTable::topk_diseases(int k, std::string country){
  unsigned hval = hash_str(country); //hasharei to country
  hval = hval % size; //gia na pame sth swsth thesh pinaka
  if(table[hval] == NULL){ //ean den yparxei alusida ekei, den yparxei h xwra
    std::cout << "Country specified does not exist (yet).\n";
    return;
  }
  else{ //h xwra yparxei
    chain_node * currptr = table[hval];
    while(currptr!= NULL){ //to psaxnei dieksodika wste na brethei h xwra
      block_entry * buroku = currptr->block;
      for(unsigned int i=0; i< currptr->block_size; i++){
        if(buroku[i].dis_name_ptr == NULL)
          continue;
        if(*(buroku[i].dis_name_ptr) == country){
          //extract eggrafes apo dentro
          simple_cd_HT simpldiseaseht(buroku[i].totalval, "disease"); //DES README gia topk
          buroku[i].tree_ptr->populate_simpleht(&simpldiseaseht); //twra oi komvoi tou simple ht exoun kathe astheneia sth xwra kai ton arithmo krousmatwn ths
          maxBinaryHeap mheap(buroku[i].totalval); //ena maxheap gia krousmata astheneiwn
          //gemizei o swros apo to dentro twn krousmatwn auths ths xwras
          simpldiseaseht.populate_heap(&mheap);
          //std::cout << "Top " << k << " diseases for " << country << " :\n";
          for(unsigned int ka=0; ka<k; ka++){
            if(mheap.root == NULL){
              //std::cout << "-\n"; //de ginontai alla extractions.
              continue;
            }
            heapnode ophelia(mheap.extract() ); //eksagwgh rizas apo swro kai diathrhsh
            std::cout << ophelia.cat_name << " " << ophelia.krousmata << "\n";
          }
          return;
        }
      }//telos for gia block
      currptr = currptr->next ;
    }//telos while gia orizontia lista

  }//telos else
  std::cout << "Country specified does not exist (yet).\n";
}//telos sunarthshs

//gia to antistoixo erwthmata ME date1 date2
void countryHashTable::topk_diseases(int k, std::string country, std::string date1, std::string date2){
  unsigned hval = hash_str(country); //hasharei to country
  hval = hval % size; //gia na pame sth swsth thesh pinaka
  if(table[hval] == NULL){ //ean den yparxei alusida ekei, den yparxei h xwra
    std::cout << "Country specified does not exist (yet).\n";
    return;
  }
  else{ //h xwra yparxei
    chain_node * currptr = table[hval];
    while(currptr!= NULL){ //to psaxnei dieksodika wste na brethei h xwra
      block_entry * buroku = currptr->block;
      for(unsigned int i=0; i< currptr->block_size; i++){
        if(buroku[i].dis_name_ptr == NULL)
          continue;
        if(*(buroku[i].dis_name_ptr) == country){
          //extract eggrafes apo dentro
          simple_cd_HT simpldiseaseht(buroku[i].totalval, "disease"); //DES README gia topk
          search_containter querycontainer(buroku[i].totalval); //to megisto plhthos eggrafwn einai o sunolikos arithmos eggrafwn auths ths atheneias/xwras
          //me thn apo katw entolh o container exei oles tis eggrafes ths astheneias/xwras me entrydate <= date2.
          buroku[i].tree_ptr->collect_dated_reclists(buroku[i].tree_ptr, date2, &querycontainer); //o container exei tis eggrafes gia authn thn astheneia/xwra me entrydate <= Date2. Ekmetalleuetai th dendrikh domh gia kalyterh polyplokothta
          //twra gia date 1:disqualify dates passing date2 test but not date1 and pass them to simpleht
          querycontainer.populate_simpleht(&simpldiseaseht, date1); //twra oi komvoi tou simple ht exoun kathe astheneia sth xwra kai ton arithmo krousmatwn ths kai me ta swsta dates
          maxBinaryHeap mheap(buroku[i].totalval); //ena maxheap gia krousmata astheneiwn
          //gemizei o swros apo to dentro twn krousmatwn auths ths xwras
          simpldiseaseht.populate_heap(&mheap);
          //std::cout << "Top " << k << " diseases for " << country << " for dates provided :\n";
          for(unsigned int ka=0; ka<k; ka++){
            if(mheap.root == NULL){
              //std::cout << "-\n"; //de ginontai alla extractions.
              continue;
            }
            heapnode ophelia(mheap.extract() ); //eksagwgh rizas apo swro kai diathrhsh
            std::cout << ophelia.cat_name << " " << ophelia.krousmata << "\n";
          }//telos for ektypwshs topk
          return;
        }//telos if brethhke xwra
      }//telos for gia block
      currptr = currptr->next ;
    }//telos while gia orizontia lista

  }//telos else
  std::cout << "Country specified does not exist (yet).\n";
}//telos sunarthshs



//CHAIN NODE
chain_node::chain_node(int sz){
  next = NULL;
  //SUMPERILAMVENTAI STO BUCKETSIZE KAI O DEIKTHS STO NEXT KAI O AKERAIOS POY KRATAW
  block_size = (sz-sizeof(chain_node *)-sizeof(int)) / sizeof(block_entry); //stathero megethos dioti exw deiktes sth domh block entry
  if(block_size < 1)
    block_size = 1; //toulaxiston ena element mesa
  block = new block_entry[block_size]; //toses theseis oses leei h ekfwnhsh
}

chain_node::~chain_node(){
  //std::cout << "ffOTO";
  delete[] block;
  delete next; //KATASTREFETAI ANADROMIKA. STH C++ H DELETE KALEI TON DESTRUCTOR EAN YPARXEI. THA KALESEI LOIPON GIA TO NEXT TON DESTRUCTOR O OPOIOS KALEI GIA TO NEXT KTL KTL.
  //delete this; //to epitrepei h C++. To kalw mono edw giati ta chain nodes yparxoyn se pinaka (ton zhtoumeno ht) gia na glitwsw th loupa

}

bool chain_node::insert_record(record* rec, std::string key){
  for(unsigned int i=0; i<block_size; i++){
    if(block[i].dis_name_ptr == NULL){ //einai h 1h adeia thesh, valto ekei
      block[i].insert_record(rec, key);
      return true; //komple
    }
    if( *(block[i].dis_name_ptr) == key ){ //h astheneia/xwra yparxei. proxwrame edw.
      block[i].insert_record(rec, key);
      return true; //komple
    }
  }
  return false;
}

void chain_node::print_contents(){
  std::cout << "to block exei " << block_size << " theseis\n\t\t\t";
  for(unsigned int i=0; i<block_size; i++){
    if(block[i].dis_name_ptr == NULL)
      continue;
    std::cout << *(block[i].dis_name_ptr) << " curr " << block[i].currval << " total " << block[i].totalval << " ";
    std::cout << "to dentro moy: ";
    block[i].tree_ptr->print_contents();
    std::cout << "--";
  }
}


//BLOCK ENTRY
block_entry::block_entry(){
  dis_name_ptr = NULL;
  tree_ptr = NULL;
  currval =0;
  totalval =0;
}

block_entry::~block_entry(){
  //std::cout << "watashi wa, BUROKU!";
  delete dis_name_ptr;
  delete tree_ptr; //KATASTREFETAI ANADROMIKA. STH C++ H DELETE KALEI TON DESTRUCTOR EAN EXEI ORISTEI. DES DESTRUCTOR BBST sto bbst.cpp
}

int block_entry::insert_record(record * rec, std::string key){
  if(dis_name_ptr == NULL)
    dis_name_ptr = new std::string(key);
  //de xreiazetai else. an den einai null shmainei oti h astheneia/xwra yparxei hdh kai de xreiazetai ksana to idio string
  //sunexizoume me aukshsh metrhth kai eisagwgh se dentro
  if(rec->get_exitDate() == "-") //den exei bgei, increase current!
    currval++;
  totalval++;
  if(tree_ptr == NULL) //den yparxei dentro, to ftiaxnw k eisagw eggrafh
    tree_ptr = new BBST(rec); // o constructor basei orismatos tou bbst frontizei ta ypoloipa
  else //yparxei dentro. eisagw eggrafh
    tree_ptr->insert_record(rec);

  return 0;
}
