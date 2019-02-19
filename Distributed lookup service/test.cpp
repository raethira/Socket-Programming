#include<fstream>
#include<iostream>
#include<string>
using namespace std;

string search(string x,string y){
  ifstream infile;
  string t,term = "",res = "";
  int pos;
  int n = 0;
  infile.open("/home/ee450/Downloads/backendA.txt");
  if(!y.compare("prefix")){
	
	while(infile>>t){
	  pos = t.find(x);
	  if(pos == 0){
                n=n+1;
		res.append(t);
		res.append(" ");
	  }
	}
  cout<<n<<endl;
}
  else{
  while (getline(infile,t))
  {
	pos = t.find(x);
	term = t.substr(0,pos-1);
	if(!term.compare(x)){
	res = t.substr(pos+3);
	}
        cout<<term;

  }
  }
  infile.close();
  return res;
}

int main()
{
  string keyword = "reg";
  string type = "prefix";
  cout<<search(keyword,type);
 
  
}
