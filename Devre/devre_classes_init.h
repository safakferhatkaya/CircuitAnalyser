#ifndef _DEVRE_H_
#define _DEVRE_H_
#include <iostream>
#include <string>
#include <cstdlib>
#include <new>
#define MAX 10
#include<math.h>
#include<exception>
#define pi 3.14
using namespace std;

extern double frekans;
extern double voltage;//global variables
extern double rezonans;

class Component
{
	friend class Node;
	public :
		Component();
		void setComponent();
		Component* operator=(Component *obj) //Node class�nda obj uyesine komponentleri esitlemek icin kullanacagiz
		{
			return this;
		}
		 //Node class�nda obj uyesine komponentleri esitlemek icin kullanacagiz
		double getValue();  // analiz ederken kullanacaksin komponentlerin degerlerini dondurur
		int getType(); // bir komponentin turunun ne oldugunu bununla kontrol edebilirsin
		
	private :
		double value;
		string name;
		int type;
};
class Node
{
	friend class Devre;  // Devre classi dugumlerle ilgili seylere ulasabilsin diyedir
	
	public :
	//	double voltaj,frekans;
		
		Node();
		void setNode(int numOfComps , int isSerial);
		int getSeriality();  // dugumdeki komponentlerin seriligini dondurur
							// analiz fonksiyonunu yazarken kullanacaksin
		double analiz(double frekans);
				//rlc devresiyken toplam empedans cal�s�yor fakat, ayr� ayr�larken sorun c�kar�yordu,
				//bu sebeple yaln�zlarken sadece kendi sonu�lar�n� d�nd�r�yoruz.
				//bobin ve kapastir degeri girilmemisse 1/0 belirsizliginden nan yazd�r�yordu..	
		
		
		void makeComp();  	// dugumu main'de olsutururken icindeki komponentleri olusturur 
	private : 
		int compNum;
		int seriality;
		Component *obj;
};
class Devre
{
	public :
		Devre();
		void insertNodes(Node *dugum,int size);
		  // olusturulan dugumleri bunyesine aktarir
		  // bu fonskyion devredeki herhangi bir dugumu  
		  // ozellikle secebilmek icin elzemdir
		  // Node getNode(int index) : return node[i] ; 
		  // seklinde fonskiyon yazman lazim once buraya biyere 
		double analyse(double frekans);
		void getNodes(Node *obj,int nodes);
		void print();
	private :
		Node *node;
		int nodess;
};
void intro();			// Introduction
#endif /// DEVRE HEADER ENDS
