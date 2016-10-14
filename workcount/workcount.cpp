#include<io.h>
#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<math.h>
#include<fstream> 
using namespace std;


vector<pair<string,int> > result ;


void GetAllFiles( string path, vector<string>& files)  
{  

	long   hFile   =   0;  
	//文件信息  
	struct _finddata_t fileinfo;//用来存储文件信息的结构体  
	string p;  
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)  //第一次查找
	{  
		do  
		{   
			if((fileinfo.attrib &  _A_SUBDIR))  //如果查找到的是文件夹
			{  
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  //进入文件夹查找
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					GetAllFiles( p.assign(path).append("\\").append(fileinfo.name), files ); 
				}
			}  
			else //如果查找到的不是是文件夹 
			{  
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));  //将文件路径保存，也可以只保存文件名:p.assign(fileinfo.name)     
			} 

		}while(_findnext(hFile, &fileinfo)  == 0);  

		_findclose(hFile); //结束查找
	} 

}  



// 该函数有两个参数，第一个为路径字符串(string类型，最好为绝对路径)；
// 第二个参数为文件夹与文件名称存储变量(vector类型,引用传递)。


vector<string> GetFileName() 
{
	string filePath = "F://test";  
	static vector<string> files;  
	GetAllFiles(filePath, files);
	int size = files.size(); 
	if(size == 0){
		cout << "EMPTY!!!" <<endl;
		exit(0);
	}
	return files;	
}


vector<string> OpenFile(){
	vector<string> files;
	vector<string> buffers;
	char buffer[256];
	char *filename;
	files = GetFileName();
	int size = files.size();
	for(int i = 0;i < size; i++){
		//cout << files[i] <<endl;
		ifstream in;
		filename = new char[files[i].size()+1];
		strcpy(filename,files[i].c_str());
		in.open(filename);	
		if (! in)
        { 
			cout << "Error opening file"; 
			exit (1); 
		}
		while (!in.eof() )
        {
            in.getline (buffer,100);
            buffers.push_back(buffer);    
        }	
		//cout << files[i] << endl;
	}
	return buffers;
}
vector<string> split(string a)
{
	int size = a.size();
	string temp;
	vector<string> result;
	for(int i = 0;i < size;i ++)
	{
		int sign = 0;
		if((a.at(i) >= 65&&a.at(i) <= 90)||(a.at(i) >= 97&&a.at(i) <= 122))
		{
			sign = 1;
			for(int j = i + 1;j < size;j ++)
			{
				//cout<< j<<"+";
				if(sign < 4)
				{
					if((a.at(j) >= 65&&a.at(j) <= 90)||(a.at(j) >= 97&&a.at(j) <= 122)){sign ++;}
					else {i = j;break;}
				}
				else
				{
					if(((a.at(j) >= 65&&a.at(j) <= 90)||(a.at(j) >= 97&&a.at(j) <= 122)||(a.at(j) >= 48&&a.at(j) <= 57))&&j!=size-1)
					{sign++;continue;}
					else{result.push_back(a.substr(i,sign));i = j;break;}
				}
				
			}
		}
	}
	return result;
}

bool compare(string a,string b)
{
	if(a.length() != b.length()){return false;}
	if(a == b){return true;}
	else
	{
		int l = a.length();
		for(int i = 0;i < l;i ++)
		{
			if(abs(a[i] - b[i]) == 0||abs(a[i] - b[i]) == 32){continue;}
			else{return false;}
		}
		return true;
	}
}

void identify(vector<string> a)
{
	for(int i = 0;i < a.size();i ++)
	{
		bool sign = false;
		for(int j = 0;j < result.size();j ++)
		{
			if(compare(a.at(i),result.at(j).first) == true)
			{
				result.at(j).second ++;
				sign = true;
				break;
			}
		}
		if(sign == false)
		{
			pair<string,int> temp;
			temp = make_pair(a.at(i),1);
			result.push_back(temp);
		}
	}
}
int main()
{
	
	vector<string> file_text = OpenFile();
	for(int i = 0;i < file_text.size();i ++)
	{
		vector<string> temp = split(file_text.at(i));
		identify(temp); 
	}
	for(int i = 0;i < result.size();i ++)
	{
		cout <<result.at(i).first<<"	"<<result.at(i).second<<endl;
	} 

}
