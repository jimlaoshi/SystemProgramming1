#include "record.h"


record::record(std::string *params){ //constructor basei twn gnwrismatwn poy ekshxthhsan apo grammh input
  //std::cout << "i am construcotrrrrr";
  /*recordID = new std::string(params[0]);
  patientFirstName = new std::string(params[1]);
  patientLastName = new std::string(params[2]);
  diseaseID = new std::string(params[3]);
  country = new std::string(params[4]);
  entryDate = new std::string(params[5]);
  exitDate = new std::string(params[6]);*/
  recordID = params[0];
  patientFirstName = params[1];
  patientLastName = params[2];
  diseaseID = params[3];
  country = params[4];
  entryDate = params[5];
  exitDate = params[6];
}

//destructor, sxoliasmeno eswteriko gt to eixa dokimasei kai me pointers alla de xreiasthke
record::~record(){
  /*delete recordID;
  delete patientFirstName;
  delete patientLastName;
  delete diseaseID;
  delete country;
  delete entryDate;
  delete exitDate;*/

}

//setters
void record::set_recordID(std::string newid){
  recordID = newid;
}

void record::set_patientFirstName(std::string newfn){
  patientFirstName = newfn;
}

void record::set_patientLastName(std::string newln){
  patientLastName = newln;
}

void record::set_diseaseID(std::string newid){
  diseaseID = newid;
}

void record::set_country(std::string newc){
  country = newc;
}

void record::set_entryDate(std::string newed){
  entryDate = newed;
}

void record::set_exitDate(std::string newed){
  exitDate = newed;
}

//getters
std::string record::get_recordID(){
  return recordID;
}

std::string record::get_patientFirstName(){
  return patientFirstName;
}

std::string record::get_patientLastName(){
  return patientLastName;
}

std::string record::get_diseaseID(){
  return diseaseID;
}

std::string record::get_country(){
  return country;
}

std::string record::get_entryDate(){
  return entryDate;
}

std::string record::get_exitDate(){
  return exitDate;
}
