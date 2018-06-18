#include<Python.h>
#include<iostream>
#include<string>

#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

int vtLookupHash(std::string fileHash) {

  setenv("PYTHONPATH",".",1);
  PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *presult;
  Py_Initialize();
  
  int vtPositives;
  
  pName = PyString_FromString((char*)"vt_hash_check");
  pModule = PyImport_Import(pName);
  pDict = PyModule_GetDict(pModule);
  pFunc = PyDict_GetItemString(pDict, (char*)"lookup_hash");

  if (PyCallable_Check(pFunc))
    {
      // need to convert to a c string
      pValue=Py_BuildValue("(z)",(char*)fileHash.c_str());
      presult=PyObject_CallObject(pFunc,pValue);
    }


  int number = PyInt_AsLong(presult);

  return number;

}

int main(int argc, char** argv) {
  
  // create our sha object
  SHA_CTX ctx;
  SHA1_Init(&ctx);
  
  if(argc != 2) {
    // if there's not one argument for the file quit
    exit(0);
  }
  
  std::string fileLine;
  std::ifstream infile(argv[1]);
  
  // read our file and update sha1 object
  while(std::getline(infile, fileLine)) {
    SHA1_Update(&ctx, fileLine.c_str(), fileLine.length());
  }
  
  // put the message digest in md with 20 bytes output as per standard
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1_Final(hash, &ctx);
  
  // copy and prepend for printing
  char mdString[SHA_DIGEST_LENGTH*2 + 1];
  for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
    sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);

  }
  
  // print out our hash
  std::cout << mdString << std::endl;

  // now that we have our hash send it to virustotal
  int fileScanResults;  
  fileScanResults = vtLookupHash(mdString);                                   
  std::cout << fileScanResults << "\n";  

  return 0;
}
