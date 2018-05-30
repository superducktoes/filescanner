#include<Python.h>
#include<iostream>
#include<string>

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

int main() {
  
  std::string fileToScan;
  int fileScanResults;

  std::cout << "Enter the file: ";
  std::cin >> fileToScan;
  
  fileScanResults = vtLookupHash(fileToScan);
  std::cout << fileScanResults;
  return 0;
}
