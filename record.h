#ifndef _RECORD_H_
#define _RECORD_H_

#include <iostream>
#include <string> //EPITREPETAI EIPWTHHKE STO PIAZZA

class record{

  private: //dedomena ekfwnhshs
    std::string recordID;
    std::string patientFirstName;
    std::string patientLastName;
    std::string diseaseID;
    std::string country;
    std::string entryDate;
    std::string exitDate;

  public:
    record(){}; //enas empty contrusctor
    record(std::string *);                            // o conustructor basei pinaka strings
    //setters
    void set_recordID(std::string );
    void set_patientFirstName(std::string );
    void set_patientLastName(std::string );
    void set_diseaseID(std::string );
    void set_country(std::string );
    void set_entryDate(std::string );
    void set_exitDate(std::string );
    //getters
    std::string get_recordID();
    std::string get_patientFirstName();
    std::string get_patientLastName();
    std::string get_diseaseID();
    std::string get_country();
    std::string get_entryDate();
    std::string get_exitDate();
    ~record(); //destructor

};


#endif
