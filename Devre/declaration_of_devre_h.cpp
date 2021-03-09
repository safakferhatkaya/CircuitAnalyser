#include "devre_classes_init.h"

double voltage;//global variables
double rezonans;
double frekans;

Component::Component()
{
	//	cout << "Component Createde "<< endl;
};
void Component::setComponent()
{
	cout << "Oz Deger gir" << "\n> ";
	cin >> value;
	cout << "Isim gir" << "\n";
	cout <<"Direnc (1)	" << "Bobin (2)	" << "Kapasitor (3)" << endl;
	cin >> type;
	if ( type == 1 )
	{
		cout << "Direnc olusturuldu. " << endl;
		name = "Resistor";
	}
	else if ( type == 2 )
	{
		cout << "Bobin olusturuldu. " << endl;
		name = "Coil";
	}
	else if ( type == 3 )
	{
		cout << "Kapasitor olusturuldu. "<< endl;
		name = "Capacitor";
	}
};
double Component::getValue()
{
	return value;
}
int Component::getType()
{
	return type;
}
Node::Node()
{
		//	cout <<k<<". node created " << endl;
		//	k++;
}
void Node::setNode(int numOfComps , int isSerial)
{
	compNum = numOfComps;
	seriality = isSerial;
}
int Node::getSeriality()
{
	return seriality;
}
double Node::analiz(double frekans)
{
	double total;//düzenlenmeden	
	double direnctotal=0.0;
	double bobintotal=0.0;
	double kapasitortotal=0;
	double totalempedans=0;
	double rezonansbobin=0;
	double rezonanskapasitor=0;
	if(seriality==1)
	{

	for(int i=0;i<compNum;i++){
	
			if(	obj[i].getType()==1)
			{
			
			direnctotal+=obj[i].getValue();
			
		}
		if(	obj[i].getType()==2)
			{
				
			bobintotal+=0.001*(2*pi*frekans*(obj[i].getValue()));		//wL
			rezonansbobin=+obj[i].getValue();//esdeger bobin hesabý

		}
		if(	obj[i].getType()==3)
			{
			kapasitortotal+=((1/(2*pi*frekans*(obj[i].getValue()*0.000000001))));	//1/wc
			rezonanskapasitor=+obj[i].getValue();
		}
		}
		rezonanskapasitor=1/rezonanskapasitor;
		rezonans=1/(2*pi*sqrt(rezonansbobin*rezonanskapasitor));
		totalempedans=sqrt(pow(direnctotal,2)+pow((bobintotal-kapasitortotal),2));
		return totalempedans;
	
	}
	
		if(seriality==0)
	{
	int direnc=0;
	int bobin=0;
	int kapasitor=0;
	double rezonansbobin=0;
	double rezonanskapasitor=0;
	for(int i=0;i<compNum;i++){
	
		if(	obj[i].getType()==1)
			{
			
			direnctotal+=1/(obj[i].getValue());
			direnc++;
			rezonans=0;
		}
		
		else if(	obj[i].getType()==2)
			{
				
			bobintotal+=0.001*(2*pi*frekans*(obj[i].getValue()));		//wL
			bobin++;
			rezonansbobin=+obj[i].getValue();
		}
		
		else if(	obj[i].getType()==3)
			{
			kapasitortotal+=(1/(2*pi*frekans*(obj[i].getValue()*0.000000001)));	//1/wc
			kapasitor++;
			rezonanskapasitor=+obj[i].getValue();
		};
		
		}
		rezonanskapasitor=1/rezonanskapasitor;
		rezonans=1/(2*pi*sqrt(rezonansbobin*rezonanskapasitor));//paralel rezonans hesabý,
		direnctotal=1/direnctotal;								//varken calýsýr, cunku esdeger direncleri atama yaparken hesaplattýk 

		totalempedans=1/sqrt(1/pow(direnctotal,2)+pow((1/bobintotal)-(1/kapasitortotal),2));
		
		if(direnc!=0 && bobin ==0 && kapasitor==0){		//sadece direncli devre			R
			return direnctotal;
			rezonans=0;
		}
		
		else if(direnc==0 && bobin !=0 && kapasitor==0){	//sadece bobinli devre		L
			return bobintotal;
		}
		
		else if(direnc==0 && bobin ==0 && kapasitor!=0){		//sadece kapasitorlu devre	C
			return kapasitortotal;
		}
		else if(direnc!=0 && bobin !=0 && kapasitor==0){			//RL devresi
			return direnctotal*bobintotal/(sqrt(pow(direnctotal,2)+pow(bobintotal,2)));
		}					

		else if(direnc!=0 && bobin !=0 && kapasitor==0){			//RC devresi
			return direnctotal*kapasitortotal/(sqrt(pow(direnctotal,2)+pow(kapasitortotal,2)));
		}
		
		else if(direnc!=0 && bobin !=0 && kapasitor!=0){		//rlc devresi
			return totalempedans;
		}
		

		}	
	//rlc devresiyken toplam empedans calýsýyor fakat, ayrý ayrýlarken sorun cýkarýyordu,
	//bu sebeple yalnýzlarken sadece kendi sonuçlarýný döndürüyoruz.
	//bobin ve kapastir degeri girilmemisse 1/0 belirsizliginden nan yazdýrýyordu..
}
void Node::makeComp()
{
	obj = new Component[compNum];
	for (int i=0;i<compNum;i++)
	{
		obj[i].setComponent();
	}
}
Devre::Devre()
{
	cout << "Devre olusuturuldu. " << endl;
}
void Devre::insertNodes(Node *dugum,int size)
{
	node = (Node*)malloc(sizeof(class Node) * size);
	for(int i=0;i<size;i++)
	{
		node[i] = dugum[i];
	}
}
double Devre::analyse(double frekans)
{
	int nodetoplam=0;
	for(int i=0;i<nodess;i++)
	{
	nodetoplam+=node[i].analiz(frekans);
	}
	return nodetoplam;
}
void Devre::getNodes(Node *obj,int nodes)
{
	node=obj;
	nodess=nodes;
}
void intro()
{
	system("cls");
	cout << "\n                 5ohm   40ohm";
	cout << "\n *--------R----*---R----*---R";
	cout << "\n |        5ohm     |        |";
	cout << "\n |                 *        |";
	cout << "\n___                |        |";
	cout << "\n _ 25V       15ohm R        |";
	cout << "\n |                 |        |";
	cout << "\n |                 *        |";
	cout << "\n |                 |        |";
	cout << "\n *-----------------R--------*";
	cout << "\n                  20ohm      ";
	cout << "\n\n"<<endl;
	cout << "sekildeki devrede her bir yildiz bir dugumu ifade eder "<<endl;
	cout << "ve goruldugu uzere 5 Resistor vardir es deger direncleri ise 25ohm"<<endl;
	cout << "olup anakol akimi 1A dir ."<<endl;
	cout << "\n\n"<<endl;
	cout << "Program sizden kac tane dugum noktasi oldugunu soracaktir "<<endl;
	cout << "ve her 2 dugum noktasi icin kac komponent ve bu komponentlerin "<<endl;
	cout << "oz degerlerini, direnc icin ohm, bobin için milihenry, kapasitor"<<endl;
	cout << "icinse nanoFarad cinsinden istenecek ardýndan node'un kendi icinde"<<endl;
	cout << "seriligi hakkinda bilgi isteyecektir" << endl;
	cout << "Bu serilik bilgisi ise :"<<endl;
	cout << "(1) mevcut dugum noktalari arasindaki butun komponentler seri "<<endl;
	cout << "(0) mevcut dugum noktalari arasindaki butun komponentler paralel"<<endl;
	cout << "kolay gelsin ..."<<endl;
	system("pause");
};

