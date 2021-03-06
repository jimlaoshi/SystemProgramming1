#include "utils.h"

//h sunarthsh epistrefei to katallhlo apotelesma gia to an to date1 einai megalutero, iso h mikrotero tou date2
std::string dates_compare(std::string date1, std::string date2){

  if(is_date_ok(date1) == false)
    return "problem";
  if(is_date_ok(date2) == false)
    return "problem";
  if(date1 == "-") //de ginetai na mhn exei entry date
    return "problem";
  int params_count =0;
  std::string intermediate;
  std::stringstream check1(date1);
  int date1_parts[3]; //mia thesh gia mera, mia gia mhna mia gia xronia.
  while(getline(check1, intermediate, '-')) {
        date1_parts[params_count] = stoi(intermediate);
        params_count++;
  } //telos while eksagwghs gnwrismatwn apo date1
  //date2
  if(date2 == "-")
    return "smaller"; //den exei bgei akoma, eimaste ok me thn paula.

  int params_count2 =0;
  std::stringstream check2(date2);
  int date2_parts[3]; //mia thesh gia mera, mia gia mhna mia gia xronia.
  while(getline(check2, intermediate, '-')) {
        date2_parts[params_count2] = stoi(intermediate);
        params_count2++;
  }//telos while eksagwghs gnwrismatwn apo date2


  if(params_count2 != params_count)//problhmatiko input. de tha eprepe na dothei etsi sumfwna me ekfwnhsh
    return "kakws orismena dates. shouldn't happen kata ekfwnhsh";

  if(date1_parts[2] > date2_parts[2]) //megaluterh xronia
    return "bigger";
  if(date1_parts[2] == date2_parts[2]){ //ish xronia
    if(date1_parts[1] > date2_parts[1]) //megaluteros mhnas me ish xronia
      return "bigger";
    if(date1_parts[1] == date2_parts[1]){ //isos mhnas me ish xronia
      if(date1_parts[0] > date2_parts[0]) //megaluterh mera me iso mhna kai xronia
        return "bigger";
      if(date1_parts[0] == date2_parts[0]) //ola isa
        return "equal";
      if(date1_parts[0] < date2_parts[0]) //ish xronia isos mhnas mikroterh mera
        return "smaller";
    }
    if(date1_parts[1] < date2_parts[1]) //mikroteros mhnas me ish xronia
      return "smaller";
  }
  if(date1_parts[2] < date2_parts[2]) //mikroterh xronia
    return "smaller";
}

//https://stackoverflow.com/questions/16075271/hashing-a-string-to-an-integer-in-c - hash function gia strings
//prosarmosmenh sta dika moy dedomena

unsigned hash_str(std::string str)
{
   uint32_t hash = 0x811c9dc5;
   uint32_t prime = 0x1000193;
   for(int i = 0; i < str.size(); ++i) {
        uint8_t value = str[i];
        hash = hash ^ value;
        hash *= prime;
    }
   return hash;
}

//elegxw an ena date einai ok
bool is_date_ok(std::string dato){
  if(dato == "-")
    return true;
  int params_count =0;
  std::string intermediate;
  std::stringstream check1(dato);
  int date1_parts[3]; //mia thesh gia mera, mia gia mhna mia gia xronia.
  while(getline(check1, intermediate, '-')) {
        //std::cout << intermediate;
        date1_parts[params_count] = stoi(intermediate);
        params_count++;
  } //telos while eksagwghs gnwrismatwn apo dato
  if(params_count != 3) //den to zorizoume. einai lathos
    return false;
  if((date1_parts[1] == 1) || (date1_parts[1] == 3) || (date1_parts[1] == 5) || (date1_parts[1] == 7) || (date1_parts[1] == 8) || (date1_parts[1] == 10) || (date1_parts[1] == 12)){
    if((date1_parts[0] <= 31)&&(date1_parts[0] >= 1))
      return true;
  }
  else if((date1_parts[1] == 4) || (date1_parts[1] == 6) || (date1_parts[1] == 9) || (date1_parts[1] == 11) ){
    if((date1_parts[0] <= 30)&&(date1_parts[0] >= 1))
      return true;
  }
  else if(date1_parts[1] == 2){
    if((date1_parts[0] <= 29)&&(date1_parts[0] >= 1))
      return true;
  }
  return false;
}
