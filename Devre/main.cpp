#include "devre_classes_init.h"

int main()
{
	char sel;
	cout << "Aciklamayi okumak ister misin ? (y/n)"<<endl;
	cout <<"> ";
	cin >> sel;
	if (sel == 'y' || sel == 'Y')
	{
		intro();
	}
	else if (sel == 'n' || sel == 'N')
	{
		cout << "Devre analizine baþlamak icin herhangi bir tusa basiniz.." <<endl;
		system("pause");
	}
	system("cls");
	int dugumler;
	int serilik;
	double empedans=0;
	int komponentler;
//	double frekans,voltage;
	Node *nodes = new Node[dugumler] ;		// Node classýndan dugum arrayi olusturd
	
	cout<<"Devrenizin guc kaynaginin gerilimini ve frekansini giriniz."<<"\n>";
	cin>>voltage;
	cout<<"\n>";
	cin>>frekans;
	
	
	cout << "Devrede kac dugum olacak ?" << "\n> ";
	cin >> dugumler;		//hata analizinde,,, dugumler 1 olursa devre olamaz en az 2 olmalý.
	try{
		if(dugumler<2)
		throw 0;
	}
	catch(int x){
		cout<<"Hata! Devrede dugum sayisi en az 2 olmalidir.\n Program kapaniyor.";
	}
	for (int i=0;i<dugumler-1;i++)  // 4 dugum varsa 3 devrecik vardýr [dugumler-1]
	{
		cout << i+1 <<". ve "<< i+2 << ". dugumler arasi ..." << endl;
		cout << "Komponent sayisini giriniz " << "\n> ";
		cin >> komponentler;
		cout << "serilik ? (0/1) " << "\n> ";
		cin >> serilik;
		nodes[i].setNode(komponentler,serilik);
		cout << i+1 << ". ve " << i+2 << ". dugumleri baglandi ..." << endl;
		cout << "Simdi komponentleri ayarlayin !" << endl;
		nodes[i].makeComp();
		cout << "Tebrikler devre tasarimi bitti." << endl;
		empedans+=(nodes[i].analiz(frekans));
	}
	//cout << dugum[0]->getCompValue(0) << endl;
	Devre devre;

	
	devre.insertNodes(nodes,dugumler);
	double akim=0;
	double guc=0;
	akim=voltage/empedans;
	guc=akim*akim*empedans;//i'2*r
//	empedans=(nodes[1].analiz())+(nodes[0].analiz());
	cout<<"\n\n";
	cout <<"*********************************************"<<endl;
	cout <<"*********************************************"<<endl;
	cout <<"*************Analiz sonuclari****************"<<endl;
	cout <<"*********************************************"<<endl;
	cout <<"*********************************************\n"<<endl;
	cout << "	Devredeki toplam empedans: " << empedans << " Ohm"<<endl;
	cout << "	Devredeki toplam akim: " << akim << " Amper"<<endl;
	cout << "	Devrede toplam harcanan guc: " << guc << " Watt"<<endl;
	cout << "	Devrenin rezonans frekansi : " << rezonans << " Hertz"<< endl;
	
	cout<<"\n\n";
	
	
	//catch(...){
	//	cout<<"sorun yok";
	//}
}
